/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#include "stdafx.h"
#include "BaseStation_Impl.h"

#include "Configuration/EepromLocation.h"
#include "Configuration/BaseStationEeprom.h"
#include "Configuration/BaseStationEepromMap.h"
#include "Configuration/BaseStationConfig.h"
#include "Features/BaseStationFeatures.h"
#include "mscl/Utils.h"
#include "BaseStationInfo.h"
#include "BaseStation.h"

//Base Station commands
#include "Commands/BaseStation_Ping.h"
#include "Commands/BaseStation_ReadEeprom.h"
#include "Commands/BaseStation_WriteEeprom.h"
#include "Commands/BaseStation_SetBeacon.h"

//Node commands
#include "Commands/ArmForDatalogging.h"
#include "Commands/AutoCal.h"
#include "Commands/ShortPing.h"
#include "Commands/LongPing.h"
#include "Commands/ReadEeprom.h"
#include "Commands/ReadEeprom_v2.h"
#include "Commands/WriteEeprom.h"
#include "Commands/WriteEeprom_v2.h"
#include "Commands/PageDownload.h"
#include "Commands/StartNonSyncSampling.h"
#include "Commands/StartSyncSampling.h"
#include "Commands/SetToIdle.h"
#include "Commands/Sleep.h"
#include "Commands/TriggerArmedDatalogging.h"
#include "Commands/Erase.h"

namespace mscl
{
	//Constructor
	BaseStation_Impl::BaseStation_Impl(Connection connection, uint64 baseTimeout):
		m_connection(connection),
		m_responseCollector(std::make_shared<ResponseCollector>()),
		m_baseCommandsTimeout(baseTimeout),
		m_nodeCommandsTimeout(BaseStation::NODE_COMMANDS_DEFAULT_TIMEOUT),
		m_frequency(WirelessTypes::freq_unknown),
		m_eeprom(new BaseStationEeprom(this)),
		m_eepromHelper(new BaseStationEepromHelper(this))
	{
		//build the parser with the base station's packet collector and response collector
		m_parser.reset(new WirelessParser(m_packetCollector, m_responseCollector));

		//register the parse function with the connection
		m_connection.registerParser(std::bind(&BaseStation_Impl::parseData, this, std::placeholders::_1));
	}

	//Destructor
	BaseStation_Impl::~BaseStation_Impl()
	{
		//unregister the parse functions with the connection, which stops the IO Thread
		m_connection.unregisterParser();
	}

	BaseStationEepromHelper& BaseStation_Impl::eeHelper() const
	{
		return *(m_eepromHelper.get());
	}

	const BaseStationFeatures& BaseStation_Impl::features() const
	{
		//if the features variable hasn't been set yet
		if(m_features == NULL)
		{
			//create the BaseStationInfo to give to the features
			BaseStationInfo info(*this);

			//set the features variable by creating a new BaseStationFeatures pointer
			m_features = BaseStationFeatures::create(info);
		}

		return *(m_features.get());
	}

	const Timestamp& BaseStation_Impl::lastCommunicationTime() const
	{
		return m_lastCommTime;
	}

	void BaseStation_Impl::parseData(DataBuffer& data)
	{
		//send the readBuffer to the parser to parse all the bytes
		m_parser->parse(data, m_frequency);

		//shift any extra bytes that weren't parsed, back to the front of the buffer
		data.shiftExtraToStart();
	}

	void BaseStation_Impl::useEepromCache(bool useCache)
	{
		m_eeprom->useCache(useCache);
	}

	void BaseStation_Impl::clearEepromCache()
	{
		m_eeprom->clearCache();
	}

	WirelessTypes::Frequency BaseStation_Impl::frequency() const
	{
		//if the frequency is unknown
		if(m_frequency == WirelessTypes::freq_unknown)
		{
			//read the frequency from eeprom
			m_frequency = static_cast<WirelessTypes::Frequency>(readEeprom(BaseStationEepromMap::FREQUENCY).as_uint16());
		}

		return m_frequency;
	}

	WirelessTypes::RegionCode BaseStation_Impl::regionCode() const
	{
		return m_eepromHelper->read_regionCode();
	}

	Version BaseStation_Impl::firmwareVersion() const
	{
		//Note: this function can never use the BaseStaionFeatures/BaseStationInfo call, as BaseStationInfo relies on this function.

		//read the firmware version eeprom
		uint16 fwValue1 = readEeprom(BaseStationEepromMap::FIRMWARE_VER).as_uint16();

		uint8 major = Utils::msb(fwValue1);

		//firmware versions < 10 use the scheme [Major].[Minor]
		if(major < 10)
		{
			uint8 minor = Utils::lsb(fwValue1);

			return Version(major, minor);
		}
		//firmware versions >= 10 use the scheme [Major].[svnRevision]
		else
		{
			uint16 fwValue2 = readEeprom(BaseStationEepromMap::FIRMWARE_VER2).as_uint16();

			//make the svn revision from the lsb of the first fw value, and the entire second fw value 
			uint32 svnRevision = Utils::make_uint32(0, Utils::lsb(fwValue1), Utils::msb(fwValue2), Utils::lsb(fwValue2));

			return Version(major, svnRevision);
		}
	}

	WirelessModels::BaseModel BaseStation_Impl::model() const
	{
		//Note: this function can never use the BaseStaionFeatures/BaseStationInfo call, as BaseStationInfo relies on this function.

		//read the model number from eeprom
		uint16 model = readEeprom(BaseStationEepromMap::MODEL_NUMBER).as_uint16();

		//if the model stored in eeprom is invalid (uninitialized)
		if(model == 0xFFFF || model == 0xAAAA || model == 0)
		{
			//this basestation uses the legacy model number

			//read the model from the legacy model eeprom location
			model = readEeprom(BaseStationEepromMap::LEGACY_MODEL_NUMBER).as_uint16();

			//convert the legacy model to the new model number and return it
			return WirelessModels::baseFromLegacyModel(model);
		}
		else
		{
			//read the model option from eeprom
			uint16 modelOption = readEeprom(BaseStationEepromMap::MODEL_OPTION).as_uint16();

			//build the model and model class together to form the model number
			return static_cast<WirelessModels::BaseModel>((model * 10000) + modelOption);
		}
	}

	std::string BaseStation_Impl::serial() const
	{
		//read the serial number 
		uint32 serial = readEeprom(BaseStationEepromMap::SERIAL_ID).as_uint32();

		//if the serial stored in eeprom is invalid (uninitialized)
		if(serial == 0xFFFFFFFF || serial == 0xAAAAAAAA || serial == 0)
		{
			//this basestation uses the legacy serial number

			//read the serial from the legacy serial id eeprom location
			serial = readEeprom(BaseStationEepromMap::LEGACY_SERIAL_ID).as_uint16();
		}

		//get the model number of the basestation
		WirelessModels::BaseModel fullModel = model();

		//split the model into its 2 pieces
		uint16 model = static_cast<uint16>(fullModel / 10000);
		uint16 modelClass = fullModel % 10000;

		//build the string result
		std::stringstream modelStr;
		modelStr << std::setfill('0') << std::setw(4) << model;

		std::stringstream modelClassStr;
		modelClassStr << std::setfill('0') << std::setw(4) << modelClass;

		std::stringstream serialStr;
		serialStr << std::setfill('0') << std::setw(5) << serial;

		return modelStr.str() + "-" + modelClassStr.str() + "-" + serialStr.str();
	}

	WirelessTypes::MicroControllerType BaseStation_Impl::microcontroller() const
	{
		//read the value from eeprom
		return static_cast<WirelessTypes::MicroControllerType>(readEeprom(BaseStationEepromMap::MICROCONTROLLER).as_uint16());
	}

	void BaseStation_Impl::getNextData(DataSweep& sweep, uint32 timeout)//timeout = 0
	{
		//check if a connection error has occurred
		m_connection.throwIfError();

		return m_packetCollector.getNextDataSweep(sweep, timeout);
	}

	void BaseStation_Impl::getData(std::vector<DataSweep>& sweeps, uint32 timeout, uint32 maxSweeps)
	{
		//check if a connection error has occurred
		m_connection.throwIfError();

		return m_packetCollector.getDataSweeps(sweeps, timeout, maxSweeps);
	}

	uint32 BaseStation_Impl::totalData()
	{
		return m_packetCollector.totalSweeps();
	}

	NodeDiscoveries BaseStation_Impl::getNodeDiscoveries()
	{
		//check if a connection error has occurred
		m_connection.throwIfError();

		return m_packetCollector.getNodeDiscoveries();
	}

	//getTimeForBeacon
	//	Gets the system time in seconds, as close to 0 milliseconds as possible
	uint32 BaseStation_Impl::getTimeForBeacon()
	{
		//get the current system time in UTC nanoseconds
		uint64 timeNow = Utils::getCurrentSystemTime();

		//get the current milliseconds of the time
		int milliseconds = (timeNow % TimeSpan::NANOSECONDS_PER_SECOND) / TimeSpan::NANOSECONDS_PER_MILLISECOND;

		//keep track of the closest milliseconds value to 0 milliseconds
		int closestMilli = milliseconds;

		bool sendCommand = false;
		int currentMilli;

		while(!sendCommand)
		{
			//get the current system time again
			timeNow = Utils::getCurrentSystemTime();
			
			//get the current milliseconds of the time again
			currentMilli = (timeNow % TimeSpan::NANOSECONDS_PER_SECOND) / TimeSpan::NANOSECONDS_PER_MILLISECOND;

			//if we got closer to 0 milliseconds
			if(currentMilli >= closestMilli)
			{
				//keep track of this new millisecond value
				closestMilli = currentMilli;

				//sleep for 1 millisecond
				Utils::threadSleep(1);
			}
			else
			{
				//we got as close as possible to 0 milliseconds, so send the command
				sendCommand = true;
			}
		}

		//get the current time in seconds
		uint32 timeNowInSeconds = static_cast<uint32>(timeNow / 1000000000);

		return timeNowInSeconds;
	}

	void BaseStation_Impl::baseCommandsTimeout(uint64 timeout)
	{
		m_baseCommandsTimeout = timeout;
	}

	void BaseStation_Impl::nodeCommandsTimeout(uint64 timeout)
	{
		m_nodeCommandsTimeout = timeout;
	}

	uint64 BaseStation_Impl::baseCommandsTimeout() const
	{
		return m_baseCommandsTimeout;
	}

	uint64 BaseStation_Impl::nodeCommandsTimeout() const
	{
		return m_nodeCommandsTimeout;
	}


	//================================================================================================
	//									BASE STATION COMMANDS
	//================================================================================================

	//Function: ping
	//	pings the base station
	bool BaseStation_Impl::ping()
	{
		//create the response for the BaseStation_Ping command
		BaseStation_Ping::Response response(m_responseCollector);

		//send the ping command to the base station
		m_connection.write(BaseStation_Ping::buildCommand());

		//wait for the response or a timeout
		response.wait(m_baseCommandsTimeout);

		if(response.success()) 
		{ 
			//update basestation last comm time
			m_lastCommTime.setTimeNow();
		}

		//return the result of the response
		return response.success();
	}

	bool BaseStation_Impl::read(uint16 eepromAddress, uint16& result)
	{
		//create the response for the BaseStation_ReadEeprom command
		BaseStation_ReadEeprom::Response response(m_responseCollector);

		//send the command to the base station
		m_connection.write(BaseStation_ReadEeprom::buildCommand(eepromAddress));

		//wait for the response or a timeout
		response.wait(m_baseCommandsTimeout);

		//if the command was a success
		if(response.success())
		{
			//get the eeprom value that we read
			result = response.result();

			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			return true;
		}

		//the read eeprom command failed
		return false;
	}

	//writeEeprom
	//	Writes the base station EEPROM address
	bool BaseStation_Impl::write(uint16 eepromAddress, uint16 value)
	{
		//create the response for the BaseStation_WriteEeprom command
		BaseStation_WriteEeprom::Response response(value, m_responseCollector);

		//send the command to the base station
		m_connection.write(BaseStation_WriteEeprom::buildCommand(eepromAddress, value));

		//wait for the response or a timeout
		response.wait(m_baseCommandsTimeout);

		//if the write command failed
		if(!response.success())
		{
			return false;
		}

		//update basestation last comm time
		m_lastCommTime.setTimeNow();

		return true;
	}

	Value BaseStation_Impl::readEeprom(const EepromLocation& location) const
	{
		return m_eeprom->readEeprom(location);
	}

	void BaseStation_Impl::writeEeprom(const EepromLocation& location, const Value& val)
	{
		m_eeprom->writeEeprom(location, val);
	}

	uint16 BaseStation_Impl::readEeprom(uint16 eepromAddress) const
	{
		return m_eeprom->readEeprom(eepromAddress);
	}

	void BaseStation_Impl::writeEeprom(uint16 eepromAddress, uint16 value)
	{
		m_eeprom->writeEeprom(eepromAddress, value);
	}

	Timestamp BaseStation_Impl::enableBeacon()
	{
		//return the result of the enableBeacon function given the current system time as the start time
		return enableBeacon(getTimeForBeacon());
	}

	Timestamp BaseStation_Impl::enableBeacon(uint32 utcTime)
	{
		//create the response for the BaseStation_SetBeacon command
		BaseStation_SetBeacon::Response response(utcTime, m_responseCollector);

		//send the command to the base station
		m_connection.write(BaseStation_SetBeacon::buildCommand(utcTime));

		//wait for the response or a timeout
		response.wait(m_baseCommandsTimeout);

		//if the enable beacon command failed
		if(!response.success())
		{
			//throw an exception so that the user cannot ignore a failure
			throw Error_Communication("The Enable Beacon command has failed");
		}

		//update basestation last comm time
		m_lastCommTime.setTimeNow();

		return response.beaconStartTime();
	}

	void BaseStation_Impl::disableBeacon()
	{
		try
		{
			//call the enableBeacon command with 0xFFFFFFFF for the timestamp
			enableBeacon(0xFFFFFFFF);
		}
		catch(Error_Connection&)
		{
			//rethrow the exception
			throw;
		}
		//catch the exception that could be thrown from the enableBeacon command (so we can throw a custom one from here)
		catch(Error&)
		{
			//throw an exception so that the user cannot ignore a failure
			throw Error_Communication("The Disable Beacon command has failed");
		}
	}

	void BaseStation_Impl::cyclePower()
	{
		static const uint16 RESET_BASE = 0x01;

		//store the original timeout that is currently set
		uint64 originalTimeout = baseCommandsTimeout();

		try
		{
			//this command doesn't have a response, change to a quick timeout
			baseCommandsTimeout(0);

			//write a 0x01 to the CYCLE_POWER eeprom location on the base station
			writeEeprom(BaseStationEepromMap::CYCLE_POWER, Value::UINT16(RESET_BASE));
		}
		catch(mscl::Error_Communication&)
		{
			//an exception will be thrown due to no response, just continue on
		}

		//set the timeout back to what it was
		baseCommandsTimeout(originalTimeout);
	}

	void BaseStation_Impl::resetRadio()
	{
		static const uint16 RESET_RADIO = 0x02;

		//write a 0x02 to the CYCLE_POWER eeprom location on the base station
		writeEeprom(BaseStationEepromMap::CYCLE_POWER, Value::UINT16(RESET_RADIO));
	}

	void BaseStation_Impl::changeFrequency(WirelessTypes::Frequency frequency)
	{
		//make sure the frequency is within the correct range, change if not
		Utils::checkBounds_min(frequency, WirelessTypes::freq_11);
		Utils::checkBounds_max(frequency, WirelessTypes::freq_26);

		//write the new frequency value to the base station
		writeEeprom(BaseStationEepromMap::FREQUENCY, Value::UINT16(static_cast<uint16>(frequency)));

		//reset the radio on the base station to commit the change
		resetRadio();

		//update the cached frequency
		m_frequency = frequency;
	}

	bool BaseStation_Impl::verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const
	{
		return config.verify(features(), eeHelper(), outIssues);
	}

	void BaseStation_Impl::applyConfig(const BaseStationConfig& config)
	{
		config.apply(features(), eeHelper());
	}

	WirelessTypes::TransmitPower BaseStation_Impl::getTransmitPower() const
	{
		return m_eepromHelper->read_transmitPower();
	}

	BaseStationButton BaseStation_Impl::getButtonLongPress(uint8 buttonNumber) const
	{
		return m_eepromHelper->read_button(buttonNumber, BaseStationButton::action_longPress);
	}

	BaseStationButton BaseStation_Impl::getButtonShortPress(uint8 buttonNumber) const
	{
		return m_eepromHelper->read_button(buttonNumber, BaseStationButton::action_shortPress);
	}

	bool BaseStation_Impl::getAnalogPairingEnabled() const
	{
		return m_eepromHelper->read_analogPairingEnabled();
	}

	uint16 BaseStation_Impl::getAnalogTimeoutTime() const
	{
		return m_eepromHelper->read_analogTimeoutTime();
	}

	float BaseStation_Impl::getAnalogTimeoutVoltage() const
	{
		return m_eepromHelper->read_analogTimeoutVoltage();
	}

	bool BaseStation_Impl::getAnalogExceedanceEnabled() const
	{
		return m_eepromHelper->read_analogExceedanceEnabled();
	}

	BaseStationAnalogPair BaseStation_Impl::getAnalogPair(uint8 portNumber) const
	{
		return m_eepromHelper->read_analogPair(portNumber);
	}

	//================================================================================================
	//										NODE COMMANDS
	//================================================================================================

	const Timestamp& BaseStation_Impl::node_lastCommunicationTime(NodeAddress nodeAddress)
	{
		return m_nodesLastCommTime[nodeAddress];
	}

	bool BaseStation_Impl::node_shortPing(NodeAddress nodeAddress)
	{
		//create the response for the short ping command
		ShortPing::Response response(m_responseCollector);

		//send the short ping command to the base station
		m_connection.write(ShortPing::buildCommand(nodeAddress));

		//wait up to 50 milliseconds for the response
		response.wait(50);

		if(response.success())
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		//return the result of the response
		return response.success();
	}

	PingResponse BaseStation_Impl::node_ping(NodeAddress nodeAddress)
	{
		//create the response for the LongPing command with the node address
		LongPing::Response response(nodeAddress, m_responseCollector);
		
		//TODO: perform a short ping first
		//TODO: if short ping fails, create and return a PingResponse with ResponseFail() and short ping fail status

		//send the long ping command to the base station
		m_connection.write(LongPing::buildCommand(nodeAddress));

		//wait for the response or timeout
		response.wait(m_nodeCommandsTimeout);

		if(response.result().success())
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		//return the result of the response
		return response.result();
	}

	bool BaseStation_Impl::node_sleep(NodeAddress nodeAddress)
	{
		//make sure we have good node communication by attempting to ping the node
		if(!node_ping(nodeAddress).success())
		{
			//don't attempt a sleep command
			return false;
		}

		//send the sleep command to the base station
		m_connection.write(Sleep::buildCommand(nodeAddress));

		//we don't have a success packet for this command
		return true;
	}

	SetToIdleStatus BaseStation_Impl::node_setToIdle(NodeAddress nodeAddress, const BaseStation& base)
	{
		//create the response for the Set to Idle command
		std::shared_ptr<SetToIdle::Response> response(std::make_shared<SetToIdle::Response>(nodeAddress, m_responseCollector, base));

		//build the set to idle command to send
		ByteStream setToIdleCmd = SetToIdle::buildCommand(nodeAddress);

		//send the command to the base station
		m_connection.write(setToIdleCmd);

		//build the status to return to the user
		SetToIdleStatus status(response);

		return status;
	}

	bool BaseStation_Impl::node_readEeprom(uint8 readVersion, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue)
	{
		bool success = false;

		if(readVersion == 2)
		{
			//create the response for the ReadEeprom command
			ReadEeprom_v2::Response response(nodeAddress, eepromAddress, m_responseCollector);

			//build the command to send
			ByteStream readCommand = ReadEeprom_v2::buildCommand(nodeAddress, eepromAddress);

			//send the command to the base station
			m_connection.write(readCommand);

			//wait for the response
			response.wait(m_nodeCommandsTimeout);

			success = response.success();
			if(success)
			{
				//set the eeprom value to the result
				eepromValue = response.eepromValue();
			}
		}
		else if(readVersion == 1)
		{
			//create the response for the ReadEeprom command
			ReadEeprom::Response response(nodeAddress, m_responseCollector);

			//build the command to send
			ByteStream readCommand = ReadEeprom::buildCommand(nodeAddress, eepromAddress);

			//send the command to the base station
			m_connection.write(readCommand);

			//wait for the response
			response.wait(m_nodeCommandsTimeout);

			success = response.success();
			if(success)
			{
				//set the eeprom value to the result
				eepromValue = response.eepromValue();
			}
		}

		if(success)
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		return success;
	}

	bool BaseStation_Impl::node_writeEeprom(uint8 writeVersion, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value)
	{
		bool success = false;

		if(writeVersion == 2)
		{
			//create the response for the WriteEeprom_v2 command
			WriteEeprom_v2::Response response(nodeAddress, eepromAddress, value, m_responseCollector);

			//build the command to send
			ByteStream writeCommand = WriteEeprom_v2::buildCommand(nodeAddress, eepromAddress, value);

			//send the command to the base station
			m_connection.write(writeCommand);

			//wait for the response
			response.wait(m_nodeCommandsTimeout);

			//return the result of the response
			success = response.success();
		}
		else if(writeVersion == 1)
		{
			//create the response for the WriteEeprom command
			WriteEeprom::Response response(nodeAddress, m_responseCollector);

			//build the command to send
			ByteStream writeCommand = WriteEeprom::buildCommand(nodeAddress, eepromAddress, value);

			//send the command to the base station
			m_connection.write(writeCommand);

			//wait for the response
			response.wait(m_nodeCommandsTimeout);

			//return the result of the response
			success = response.success();
		}

		if(success)
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		return success;
	}

	bool BaseStation_Impl::node_pageDownload(NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data)
	{
		//create the response for the PageDownload command
		PageDownload::Response response(m_responseCollector);

		//build the command to send
		ByteStream pageDownloadCommand = PageDownload::buildCommand(nodeAddress, pageIndex);

		//send the command to the base station
		m_connection.write(pageDownloadCommand);

		//wait for the response
		response.wait(m_nodeCommandsTimeout);

		//if the page download was a success
		if(response.success())
		{
			//get the data points and store them in the data parameter
			data = response.dataPoints();

			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();

			return true;
		}

		//page download command failed
		return false;
	}

	bool BaseStation_Impl::node_startSyncSampling(NodeAddress nodeAddress)
	{
		//create the response for the StartSyncSampling command
		StartSyncSampling::Response response(nodeAddress, m_responseCollector);

		//build the command to send
		ByteStream command = StartSyncSampling::buildCommand(nodeAddress);

		//send the command to the base station
		m_connection.write(command);

		//wait for the response
		response.wait(m_nodeCommandsTimeout);

		if(response.success())
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		//return the result of the response
		return response.success();
	}

	void BaseStation_Impl::node_startNonSyncSampling(NodeAddress nodeAddress)
	{
		//build the command to send
		ByteStream command = StartNonSyncSampling::buildCommand(nodeAddress);

		//send the command to the base station
		m_connection.write(command);
		
		//no response for this command
	}

	bool BaseStation_Impl::node_armForDatalogging(NodeAddress nodeAddress, const std::string& message)
	{
		//create the response for the ArmForDatalogging command
		ArmForDatalogging::Response response(nodeAddress, m_responseCollector);

		//build the command to send
		ByteStream command = ArmForDatalogging::buildCommand(nodeAddress, message);

		//send the command to the base station
		m_connection.write(command);

		//wait for the response
		response.wait(m_nodeCommandsTimeout);

		if(response.success())
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		//return the result of the response
		return response.success();
	}

	void BaseStation_Impl::node_triggerArmedDatalogging(NodeAddress nodeAddress)
	{
		//build the command to send
		ByteStream command = TriggerArmedDatalogging::buildCommand(nodeAddress);

		//send the command to the base station
		m_connection.write(command);

		//no response for this command
	}

	bool BaseStation_Impl::node_erase(NodeAddress nodeAddress)
	{
		//create the response for the Erase command
		Erase::Response response(m_responseCollector);

		//send the erase command to the base station
		m_connection.write(Erase::buildCommand(nodeAddress));

		//wait for the response or timeout
		response.wait(m_nodeCommandsTimeout);

		if(response.success())
		{
			//update basestation last comm time
			m_lastCommTime.setTimeNow();

			//update node last comm time
			m_nodesLastCommTime[nodeAddress].setTimeNow();
		}

		//return the result of the response
		return response.success();
	}

	bool BaseStation_Impl::node_autocal(NodeAddress nodeAddress, WirelessModels::NodeModel model, const Version& fwVersion, AutoCalResult& result)
	{
		//create the response for the AutoCal command
		AutoCal::Response response(nodeAddress, model, fwVersion, m_responseCollector);

		//build the AutoCal command bytes
		ByteStream cmd;
		switch(model)
		{
			case WirelessModels::node_shmLink2:
			default:
				cmd = AutoCal::buildCommand_shmLink(nodeAddress);
				break;
		}

		//send the command
		m_connection.write(cmd);

		//wait for the response or timeout
		response.wait(m_nodeCommandsTimeout);

		//if the autocal process has started, but not completed
		if(response.calStarted() && !response.fullyMatched())
		{
			//update last comm times
			m_lastCommTime.setTimeNow();
			m_nodesLastCommTime[nodeAddress].setTimeNow();

			//the Node tells us how much time it takes to complete, so ask for that and
			//convert the seconds to milliseconds, and add some extra buffer time
			uint64 timeToWait = static_cast<uint64>(response.calTime() * 1000.0) + 500;

			response.wait(timeToWait);
		}

		//if the autocal process has finished
		if(response.fullyMatched())
		{
			//update last comm times
			m_lastCommTime.setTimeNow();
			m_nodesLastCommTime[nodeAddress].setTimeNow();

			//give the response data to the result object
			result.m_completionFlag = response.completionFlag();
			result.parse(response.infoBytes());
		}

		return response.success();
	}
}