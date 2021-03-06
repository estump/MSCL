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

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialChannel.h"

namespace mscl
{
	//Title: EstFilter_Commands

	//Class: GetEstFilterDataRateBase
	//	Contains the logic for the "Get Estimation Filter Data Rate Base" command
	class GetEstFilterDataRateBase
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID				- CMD_GET_EF_RATE_BASE		- The <InertialTypes::Command> for this command
		//  FIELD_DATA_BYTE		- 0x8A						- The Data Field Descriptor byte
		static const InertialTypes::Command CMD_ID	= InertialTypes::CMD_GET_EF_RATE_BASE;
		static const uint8 FIELD_DATA_BYTE			= 0x8A;

	private:
		GetEstFilterDataRateBase();	//private default constructor

	public:
		//Function: buildCommand
		//	Builds the bytes in the command
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the command
		//
		//See Also:
		//	<GenericInertialCommand::Response>
		class Response : public GenericInertialCommand::Response
		{
		protected:
			//Function: fieldId
			//	Gets the <InertialTypes::Command>
			virtual InertialTypes::Command commandId() const { return CMD_ID; }

			//Function: fieldDataByte
			//	Gets the data field descriptor byte
			virtual uint8 fieldDataByte() const	{ return FIELD_DATA_BYTE; }

		public:
			//Constructor: Response
			//	Creates the Response object
			Response(std::weak_ptr<ResponseCollector> collector);

			//Function: parseData
			//	Parses the response, getting the data rate base result
			//
			//Parameters:
			//	response - The <GenericInertialCommandResponse> holding the response to parse
			//
			//Returns:
			//	The data rate base result
			uint16 parseData(const GenericInertialCommandResponse& response) const;
		};
	};

	//Class: EstFilterMessageFormat
	//	Contains the logic for the "Estimation Filter Message Format" command
	class EstFilterMessageFormat
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID				- CMD_EF_MESSAGE_FORMAT	- The <InertialTypes::Command> for this command
		//  FIELD_DATA_BYTE		- 0x82					- The Data Field Descriptor byte
		static const InertialTypes::Command CMD_ID	= InertialTypes::CMD_EF_MESSAGE_FORMAT;
		static const uint8 FIELD_DATA_BYTE			= 0x82;

	private:
		EstFilterMessageFormat();	//disabled default constructor

	public:
		//Function: buildCommand_get
		//	Builds the bytes for the "get" command
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command
		static ByteStream buildCommand_get();

		//Function: buildCommand_set
		//	Builds the bytes for the "set" command. 
		//
		//Parameters:
		//	channels - The <InertialChannels> holding the channels to be set. This should only contain channels that are in the Estimation Filter (0x82) descriptor set 
		//	sampleRateBase - The base sample rate for the estimation filter command set.
		//
		//Returns:
		//	A <ByteStream> that holds the bytes that make up the command
		//
		//Exceptions:
		//	- <Error>: An <InertialChannel> in the channels parameter is not part of the Sensor descriptor set
		static ByteStream buildCommand_set(const InertialChannels& channels, uint16 sampleRateBase);

		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const { return CMD_ID; }
			virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

		public:
			Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
			InertialChannels parseData(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const;
		};
	};
}