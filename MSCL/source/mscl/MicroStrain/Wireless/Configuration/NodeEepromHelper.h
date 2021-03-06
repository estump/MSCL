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
#pragma once

#include <memory>
#include "EepromLocation.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/RadioFeatures.h"
#include "mscl/MicroStrain/Wireless/LinearEquation.h"
#include "mscl/TimeSpan.h"
#include "mscl/Version.h"
#include "mscl/Value.h"

namespace mscl
{
	//forward declarations
	class WirelessNode_Impl;
	class FatigueOptions;
	class HistogramOptions;

	//Class: NodeEepromHelper
	//	A helper class for reading and writing to a Wireless Node's Eeprom.
	//	This class provides eeprom specific parsing so that high-level objects can
	//	be converted to their low-level eeprom value equivelent and vice-versa.
	class NodeEepromHelper
	{
	public:
		//Constants: Eeprom Limits
		//	TIME_BETWEEN_BURSTS_MAX_SECS	- 32767 - The max number of seconds before we have to switch to saving as minutes (Note: this is because we use the most significant bit to signify seconds or minutes)
		//	BYTES_PER_DATALOG_PAGE			- 264	- The number of bytes for a single datalogging page on a Wireless Node.
		//	MIN_SLEEP_INTERVAL_EEVAL		- 512	- The minimum sleep interval eeprom value.
		//	MAX_SLEEP_INTERVAL_EEVAL		- 7680	- The maximum sleep interval eeprom value.
		//	MIN_LOST_BEACON_TIMEOUT			- 2		- The minimum lost beacon timeout in minutes.
		//	MAX_LOST_BEACON_TIMEOUT			- 600	- The maximum lost beacon timeout in minutes.
		//	LOST_BEACON_TIMEOUT_DISABLED	- 0		- The value to use for disabling the lost beacon timeout.
		static const uint16 TIME_BETWEEN_BURSTS_MAX_SECS;
		static const uint16 BYTES_PER_DATALOG_PAGE;
		static const uint16 MIN_SLEEP_INTERVAL_EEVAL;
		static const uint16 MAX_SLEEP_INTERVAL_EEVAL;
		static const uint16 MIN_LOST_BEACON_TIMEOUT;
		static const uint16 MAX_LOST_BEACON_TIMEOUT;
		static const uint16 LOST_BEACON_TIMEOUT_DISABLED;

	public:
		//Constructor: NodeEepromHelper
		//	Creates a NodeEepromHelper object with a <WirelessNode_Impl>.
		//
		//Parameters:
		//	node - The <WirelessNode_Impl> that will be read from and written to.
		NodeEepromHelper(WirelessNode_Impl* node);

	private:
		NodeEepromHelper();										//default constructor disabled

	private:
		//Variable: m_node
		//	The <WirelessNode_Impl> used by this eeprom helper.
		WirelessNode_Impl* m_node;

	private:
		Value read(const EepromLocation& location) const;
		void write(const EepromLocation& location, const Value& val);

	public:
		//Function: nodeAddress
		//	Gets the node address for this Node.
		//
		//Returns:
		//	The node address of the Node.
		uint16 nodeAddress() const;

		//Function: read_frequency
		//	Reads the frequency from the Node.
		//
		//Returns
		//	The <WirelessTypes::Frequency> of the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::Frequency read_frequency() const;

		//Function: read_regionCode
		//	Reads the region code from the Node.
		//
		//Returns:
		//	The <WirelessTypes::RegionCode> set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::RegionCode read_regionCode() const;

		//Function: read_fwVersion
		//	Gets the firmware version of the Node. 
		//
		//Returns:
		//	A <Version> representing the firmware version of the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		Version read_fwVersion() const;

		//Function: read_model
		//	Gets the model of the Node.
		//
		//Returns:
		//	A <WirelessModels::NodeModel> representing the model of the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessModels::NodeModel read_model() const;

		//Function: read_serial
		//	Gets the serial number of the Node.
		//
		//Returns:
		//	A string representing the serial number of the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		std::string read_serial() const;

		//Function: read_microcontroller
		//	Gets the microcontroller of the Node.
		//
		//Returns:
		//	A <WirelessTypes::MicroControllerType> representing the microcontroller of the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::MicroControllerType read_microcontroller() const;

		//Function: read_radioFeatures
		//	Gets the <RadioFeatures> of the Node.
		//
		//Returns:
		//	The <RadioFeatures> of the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		RadioFeatures read_radioFeatures() const;

		//Function: read_dataStorageSize
		//	Gets the total number of bytes available for data storage on the Node.
		//	This is an overall count and does not take into account data that is already stored on the Node.
		//
		//Returns:
		//	The total number of bytes available for data storage on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint64 read_dataStorageSize() const;

		//Function: read_filter1
		//	Reads the specific filter 1 eeprom location.
		//	Note: this should be used by the SyncSamplingNetwork only, as it bypasses the ChannelMask logic.
		WirelessTypes::SettlingTime read_filter1() const;

		//Function: read_filter2
		//	Reads the specific filter 2 eeprom location.
		//	Note: this should be used by the SyncSamplingNetwork only, as it bypasses the ChannelMask logic.
		WirelessTypes::SettlingTime read_filter2() const;

		//Function: write_channelMask
		//	Writes the channel mask to the Node, representing which channels are active or not.
		//
		//Parameters:
		//	channels - The <ChannelMask> representing which channels are active and which are not.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_channelMask(const ChannelMask& channels);

		//Function: read_channelMask
		//	Reads the current channel mask from the Node, representing which channels are active or not.
		//
		//Returns:
		//	A <ChannelMask> object representing which channels are active or not.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		ChannelMask read_channelMask() const;

		//Function: write_numSweeps
		//	Writes the number of sweeps which affects the duration of sampling. In the case of Burst sampling, this is the number of sweeps per burst
		//	This function assumes the number of sweeps has already been normalized (multiple of 100 and within min/max).
		//
		//Parameters:
		//	sweeps - The number of sweeps to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_numSweeps(uint32 sweeps);

		//Function: read_numSweeps
		//	Reads the current number of sweeps which affects the duration of sampling.
		//
		//Returns:
		//	The number of sweeps currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint32 read_numSweeps() const;

		//Function: write_unlimitedDuration
		//	Writes the unlimited duration flag. This is a different eeprom location depending on the sampling mode.
		//
		//Parameters:
		//	unlimitedDuration - Whether unlimited duration should be enabled (true) or disabled (false).
		//	samplingMode - The <WirelessTypes::SamplingMode> to set unlimited duration for.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_unlimitedDuration(bool unlimitedDuration, WirelessTypes::SamplingMode samplingMode);

		//Function: read_unlimitedDuration
		//	Reads the current unlimited duration flag set on the Node. This is a different eeprom location depending on the sampling mode.
		//
		//Parameters:
		//	samplingMode - The <WirelessTypes::SamplingMode> to get the unlimited duration flag for.
		//
		//Returns:
		//	true if the Node is set to unlimited duration, false otherwise
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		bool read_unlimitedDuration(WirelessTypes::SamplingMode samplingMode) const;

		//Function: write_sampleRate
		//	Writes the sample rate. This is a different eeprom location depending on the sampling mode.
		//
		//Parameters:
		//	rate - The <WirelessTypes::WirelessSampleRate> to set.
		//	samplingMode - The <WirelessTypes::SamplingMode> to set unlimited duration for.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_sampleRate(WirelessTypes::WirelessSampleRate rate, WirelessTypes::SamplingMode samplingMode);

		//Function: read_sampleRate
		//	Reads the current sample rate set on the Node. This is a different eeprom location depending on the sampling mode.
		//
		//Parameters:
		//	samplingMode - The <WirelessTypes::SamplingMode> to get the unlimited duration flag for.
		//
		//Returns:
		//	A <WirelessTypes::WirelessSampleRate> representing the sample rate that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::WirelessSampleRate read_sampleRate(WirelessTypes::SamplingMode samplingMode) const;

		//Function: write_dataFormat
		//	Writes the data format to the Node.
		//
		//Parameters:
		//	dataFormat - The <WirelessTypes::DataFormat> to set.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_dataFormat(WirelessTypes::DataFormat dataFormat);

		//Function: read_dataFormat
		//	Reads the current data format set on the Node.
		//
		//Returns:
		//	The <WirelessTypes::DataFormat> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::DataFormat read_dataFormat() const;

		//Function: write_collectionMode
		//	Writes the data collection mode to the Node.
		//
		//Parameters:
		//	collectionMode - The <WirelessTypes::DataCollectionMethod> to set.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_collectionMode(WirelessTypes::DataCollectionMethod collectionMode);

		//Function: read_collectionMode
		//	Reads the current data collection mode set on the Node.
		//
		//Returns:
		//	The <WirelessTypes::DataCollectionMethod> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::DataCollectionMethod read_collectionMode() const;

		//Function: write_syncSamplingMode
		//	Writes the sync sampling mode to the Node.
		//
		//Parameters:
		//	syncMode - The <WirelessTypes::SyncSamplingMode> to set.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_syncSamplingMode(WirelessTypes::SyncSamplingMode syncMode);

		//Function: read_syncSamplingMode
		//	Reads the current sync sampling mode set on the Node.
		//
		//Returns:
		//	The <WirelessTypes::SyncSamplingMode> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::SyncSamplingMode read_syncSamplingMode() const;

		//Function: write_samplingDelay
		//	Writes the sampling delay to the Node.
		//
		//Parameters:
		//	delay - The <TimeSpan> representing the sampling delay to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_samplingDelay(TimeSpan delay);

		//Function: read_samplingDelay
		//	Reads the current sampling delay set on the Node.
		//
		//Returns:
		//	A <TimeSpan> representing the sampling delay that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		TimeSpan read_samplingDelay() const;

		//Function: write_retransmission
		//	Writes the retransmission option to the Node.
		//
		//Parameters:
		//	reTx - The <WirelessTypes::NodeRetransmission> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_retransmission(WirelessTypes::NodeRetransmission reTx);

		//Function: read_retransmission
		//	Reads the current retransmission option set on the Node.
		//
		//Returns:
		//	The <WirelessTypes::NodeRetransmission> representing the retransmission option that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::NodeRetransmission read_retransmission() const;

		//Function: write_settlingTime
		//	Writes the settling time to the Node for the given <ChannelMask>.
		//
		//Parameters:
		//	mask - The <ChannelMask> to set the filter setting time for.
		//	settlingTime - The <WirelessTypes::SettlingTime> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Filter Settling Time is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_settlingTime(const ChannelMask& mask, WirelessTypes::SettlingTime settlingTime);

		//Function: read_settlingTime
		//	Reads the current filter settling time on the Node for the given <ChannelMask>.
		//
		//Parameters:
		//	mask - The <ChannelMask> to read the filter settling time for.
		//
		//Returns:
		//	The <WirelessTypes::SettlingTime> representing the settling time that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Filter Settling Time is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::SettlingTime read_settlingTime(const ChannelMask& mask) const;

		//Function: write_timeBetweenBursts
		//	Writes the time between each burst to the Node.
		//	This function assumes the time between bursts value has been normalized.
		//
		//Parameters:
		//	timespan - The <TimeSpan> representing the time between each burst. This can be in the range of 1 second to 24 hours.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_timeBetweenBursts(const TimeSpan& timespan);

		//Function: read_timeBetweenBursts
		//	Reads the time between each burst from the Node.
		//
		//Returns:
		//	The <TimeSpan> representing the time between each burst.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		TimeSpan read_timeBetweenBursts() const;

		//Function: write_samplingMode
		//	Writes the <WirelessTypes::SamplingMode> to the Node.
		//
		//Parameters:
		//	samplingMode - The <WirelessTypes::SamplingMode> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_samplingMode(WirelessTypes::SamplingMode samplingMode);

		//Function: read_samplingMode
		//	Reads the current <WirelessTypes::SamplingMode> from the Node.
		//
		//Returns:
		//	A <WirelessTypes::SamplingMode> object representing the sampling mode.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::SamplingMode read_samplingMode() const;

		//Function: write_channelLinearEquation
		//	Writes the slope and offset for the specified <ChannelMask> on the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to write the linear equation for.
		//	equation - The <LinearEquation> containing the slope and offset to write.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Linear Equation is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_channelLinearEquation(const ChannelMask& mask, const LinearEquation& equation);

		//Function: read_channelLinearEquation()
		//	Reads the slope and offset for the specified <ChannelMask> from the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to read the linear equation for.
		//	result - The <LinearEquation> that will hold the result.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Linear Equation is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void read_channelLinearEquation(const ChannelMask& mask, LinearEquation& result);

		//Function: write_channelUnit
		//	Writes the unit for the specified <ChannelMask> to the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to write the unit for.
		//	unit - The <WirelessTypes::CalCoef_Unit> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Unit setting is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_channelUnit(const ChannelMask& mask, WirelessTypes::CalCoef_Unit unit);

		//Function: write_channelEquation
		//	Writes the equation id for the specified <ChannelMask> to the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to write the equation id for.
		//	equation - The <WirelessTypes::CalCoef_EquationType> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Equation ID setting is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_channelEquation(const ChannelMask& mask, WirelessTypes::CalCoef_EquationType equation);

		//Function: write_channelUnitAndEquation
		//	Writes the unit and equation for the specified <ChannelMask> to the Node.
		//
		//Parameters:
		//	channelNumber - The channel number to save the configuration to (channel 1 = 1, channel 8 = 8).
		//	unit - The <WirelessTypes::CalCoef_Unit> to write to the Node.
		//	equation - The <WirelessTypes::CalCoef_EquationType> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Unit / Equation ID setting is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_channelUnitAndEquation(const ChannelMask& mask, WirelessTypes::CalCoef_Unit unit, WirelessTypes::CalCoef_EquationType equation);

		//Function: read_channelUnit
		//	Reads the <WirelessTypes::CalCoef_Unit> for the specified <ChannelMask> from the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to read the unit for.
		//
		//Returns:
		//	The <WirelessTypes::CalCoef_Unit> for the given channel.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Unit setting is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::CalCoef_Unit read_channelUnit(const ChannelMask& mask) const;

		//Function: read_channelEquation
		//	Reads the <WirelessTypes::CalCoef_EquationType> for the specified channel from the Node.
		//	This assumes the channel is supported by the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to read the equation id for.
		//
		//Returns:
		//	The <WirelessTypes::CalCoef_EquationType> for the given channel.
		//
		//Exceptions:
		//	- <Error_NotSupported>: The Equation ID setting is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::CalCoef_EquationType read_channelEquation(const ChannelMask& mask) const;

		//Function: read_transmitPower
		//	Reads the <WirelessTypes::TransmitPower> that is currently set on the Node.
		//
		//Returns:
		//	The <WirelessTypes::TransmitPower> that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::TransmitPower read_transmitPower() const;

		//Function: write_transmitPower
		//	Writes the <WirelessTypes::TransmitPower> to the Node.
		//
		//Parameters:
		//	power - The <WirelessTypes::TransmitPower> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_transmitPower(WirelessTypes::TransmitPower power);

		//Function: read_inactivityTimeout
		//	Reads the user inactivity timeout that is currently set on the Node.
		//	This controls how many seconds before the Node goes to sleep when idle.
		//
		//Returns:
		//	The user inactivity timeout (in seconds) that is currently set on the Node.
		//	Note: A value of 65535 (0xFFFF) disables the inactivity timeout so that the Node never goes to sleep.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 read_inactivityTimeout() const;

		//Function: write_inactivityTimeout
		//	Writes the user inactivity timeout to the Node.
		//	This function assumes the inactivity timeout has already been set to be above the minimum.
		//
		//Parameters:
		//	timeout - The user inactivity timeout (in seconds) to write to the Node.
		//	Note: A value of 65535 (0xFFFF) disables the inactivity timeout so that the Node never goes to sleep.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_inactivityTimeout(uint16 timeout);

		//Function: read_checkRadioInterval
		//	Reads the check radio interval that is currently set on the Node.
		//	This controls how often the node wakes up from sleep to check for commands.
		//
		//Returns:
		//	The interval (in seconds) that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint8 read_checkRadioInterval() const;

		//Function: write_checkRadioInterval
		//	Writes the check radio interval to the Node.
		//	This controls how often the node wakes up from sleep to check for commands.
		//	This function assumes the interval is within the acceptable range.
		//
		//Parameters:
		//	interval - The check radio interval (in seconds) to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_checkRadioInterval(uint8 interval);

		//Function: read_defaultMode
		//	Reads the <WirelessTypes::DefaultMode> that is currently set on the Node.
		//
		//Returns:
		//	The default mode that is currently set on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::DefaultMode read_defaultMode() const;

		//Function: write_defaultMode
		//	Writes the given <WirelessTypes::DefaultMode> to the Node.
		//
		//Parameters:
		//	mode - The <WirelessTypes::DefaultMode> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write to the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_defaultMode(WirelessTypes::DefaultMode mode);

		//Function: read_logPage
		//	Reads the next flash page that to be used for datalogging.
		//
		//Returns:
		//	The next flash page that to be used for datalogging.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 read_logPage() const;

		//Function: read_logPageOffset
		//	Reads the byte offset into the log page for the next datalogging session.
		//
		//Returns:
		//	The byte offset into the log page for the next datalogging session.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 read_logPageOffset() const;

		//Function: read_numDatalogSessions
		//	Reads the number of datalog sessions that are currently stored on the Node.
		//
		//Returns:
		//	The number of datalog sessions that are stored on the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 read_numDatalogSessions() const;

		//Function: write_txPerGroup
		//	Writes the transmissions per group to the Node.
		//
		//Parameters:
		//	txPerGroup - The number of transmissions per group to write.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_txPerGroup(uint16 txPerGroup);

		//Function: write_groupSize
		//	Writes the group size to the Node.
		//
		//Parameters:
		//	groupSize - The group size to write.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_groupSize(uint16 groupSize);

		//Function: write_tdmaAddress
		//	Writes the TDMA address to the Node.
		//
		//Parameters:
		//	address - The TDMA address to write.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_tdmaAddress(uint16 address);

		//Function: write_maxRetransPerBurst
		//	Writes the max retransmissions per burst to the Node.
		//
		//Parameters:
		//	maxReTxPerBurst - The value to write.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read from the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_maxRetransPerBurst(uint16 maxReTxPerBurst);

		//Function: read_hardwareGain
		//	Reads the hardware gain for the specified <ChannelMask> from the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to read the hardware gain for.
		//
		//Returns:
		//	The hardware gain for the given <ChannelMask>.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Hardware gain is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		double read_hardwareGain(const ChannelMask& mask) const;

		//Function: write_hardwareGain
		//	Writes the hardware gain value for the specified <ChannelMask> to the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to write the hardware gain for.
		//	gain - The hardware gain value to write to the Node.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Hardware gain is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_hardwareGain(const ChannelMask& mask, double gain);

		//Function: read_thermoType
		//	Reads the <WirelessTypes::ThermocoupleType> from the Node.
		//
		//Parameters:
		//	mask - The <ChannelMask> to read the thermocouple type for.
		//
		//Returns:
		//	The <WirelessTypes::ThermocoupleType> for the given <ChannelMask>.
		//
		//Exceptions:
		//	- <Error_NotSupported>: Thermocouple Type is not supported for the given <ChannelMask> or Node.
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		WirelessTypes::ThermocoupleType read_thermoType(const ChannelMask& mask) const;

		//Function: write_thermoType
		//	Writes the <WirelessTypes::ThermocoupleType> to the Node.
		//	This assumes thermocouple type is supported.
		//
		//Parameters:
		//	mask - The <ChannelMask> to write the thermocouple type for.
		//	thermocouple - The <WirelessTypes::ThermocoupleType> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_thermoType(const ChannelMask& mask, WirelessTypes::ThermocoupleType thermocouple);

		//Function: read_fatigueOptions
		//	Reads the <FatigueOptions> from the Node.
		//	This assumes fatigue options configuration is supported by the Node.
		//
		//Parameters:
		//	result - Will hold the result of the <FatigueOptions> read from the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void read_fatigueOptions(FatigueOptions& result) const;

		//Function: write_fatigueOptions
		//	Writes the <FatigueOptions> to the Node.
		//	This assumes fatigue options configuration is supported by the Node.
		//
		//Parameters:
		//	options - The <FatigueOptions> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_fatigueOptions(const FatigueOptions& options);

		//Function: read_histogramOptions
		//	Reads the <HistogramOptions> from the Node.
		//	This assumes histogram options configuration is supported by the Node.
		//
		//Parameters:
		//	result - Will hold the result of the <HistogramOptions> read from the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void read_histogramOptions(HistogramOptions& result) const;

		//Function: write_histogramOptions
		//	Writes the <HistogramOptions> to the Node.
		//	This assumes histogram options configuration is supported by the Node and all options are valid.
		//
		//Parameters:
		//	options - The <HistogramOptions> to write to the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_histogramOptions(const HistogramOptions& options);

		//Function: clearHistogram
		//	Clears the Histogram on the Node.
		//	This assumes histogram options configuration is supported by the Node.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void clearHistogram();

		//Function: read_lostBeaconTimeout
		//	Reads the lost beacon timeout value from the Node.
		//	A value of 0 means the timeout is disabled.
		//
		//Returns:
		//	The lost beacon timeout in minutes.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		uint16 read_lostBeaconTimeout() const;

		//Function: write_lostBeaconTimeout
		//	Writes the lost beacon timeout value, in minutes, to the Node.
		//	This assumes the value is within range of a valid value. 
		//
		//Parameters:
		//	minutes - The lost beacon timeout value in minutes.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to communicate with the Node.
		//	- <Error_Connection>: A connection error has occurred with the parent BaseStation.
		void write_lostBeaconTimeout(uint16 minutes);
	};
}