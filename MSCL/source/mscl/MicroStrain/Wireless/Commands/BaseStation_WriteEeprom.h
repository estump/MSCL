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

#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{
#ifndef SWIG

	//Class: BaseStation_WriteEeprom
	//	Contains logic for the base station write eeprom command
	class BaseStation_WriteEeprom
	{
	private:
		BaseStation_WriteEeprom();											//default constructor disabled
		BaseStation_WriteEeprom(const BaseStation_WriteEeprom&);			//copy constructor disabled
		BaseStation_WriteEeprom& operator=(const BaseStation_WriteEeprom&);	//assignement operator disabled

	public:
		//=====================================================================================================
		//Constants: Packet Information
		//	COMMAND_BYTE	- 0x78	- The Command ID byte of the write eeprom command
		//	FAIL_BYTE		- 0x21	- The Fail Response ID byte for the write eeprom command
		//=====================================================================================================
		static const short COMMAND_BYTE			= 0x78;
		static const short FAIL_BYTE			= 0x21;

		//Function: buildCommand
		//	Builds the eeprom write command packet
		//
		//Parameters:
		//	eepromAddress - The eeprom address to write to on the base station
		//	valueToWrite - The value to write to the specified eeprom address
		//
		//Returns:
		//	A <ByteStream> containing the base station write eeprom command
		static ByteStream buildCommand(uint16 eepromAddress, uint16 valueToWrite);

		//Class: Response
		//	Handles the response to the base station write eeprom command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a write eeprom Response object
			//
			//Parameters:
			//	valueToWrite - The value that is expected to be written to eeprom from the associated command
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(uint16 valueToWrite, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_valueWritten
			//	The value that is expected to be written to eeprom from the associated command
			uint16 m_valueWritten;

		public:
			//Function: match
			//	Checks if the bytes passed in match the response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the response pattern was found, false otherwise
			virtual bool match(DataBuffer& data) override;

		private:
			//Function: matchSuccessResponse
			//	Checks if the bytes passed in match the success response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the success response pattern was found, false otherwise
			bool matchSuccessResponse(DataBuffer& data);

			//Function: matchFailResponse
			//	Checks if the bytes passed in match the failure response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the failure response pattern was found, false otherwise
			bool matchFailResponse(DataBuffer& data);
		};
	};

#endif

}