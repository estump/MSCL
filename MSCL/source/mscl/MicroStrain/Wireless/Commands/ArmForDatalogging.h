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

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{

#ifndef SWIG

	//Class: ArmForDatalogging
	//	Contains logic for the Arm For Datalogging Node command.
	class ArmForDatalogging
	{
	private:
		ArmForDatalogging();									//disabled default constructor
		ArmForDatalogging(const ArmForDatalogging&);			//disabled copy constructor
		ArmForDatalogging& operator=(const ArmForDatalogging&);	//disabled assignment operator

	public:
		//=====================================================================================================
		//Constants: Packet Information
		//	COMMAND_ID	- 0x000D		- The Command ID for the ArmForDatalogging command
		//=====================================================================================================
		static const uint16 COMMAND_ID = 0x000D;

		//Function: buildCommand
		//	Builds the ArmForDatalogging command packet.
		//
		//Parameters:
		//	nodeAddress - The address of the Node to build the command for.
		//	message - A message, up to 50 characters, to send with the arm command. This message can be downloaded with the data. Will be trimmed to 50 chars if longer. (Default of "")
		//
		//Returns:
		//	A <ByteStream> containing the command packet.
		static ByteStream buildCommand(NodeAddress nodeAddress, const std::string& message = "");

		//Class: Response
		//	Handles the response to the ArmForDatalogging Node command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates an ArmForDatalogging Response object
			//
			//Parameters:
			//	nodeAddress - the node address to check for
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

		private:
			//Variable: m_nodeAddress
			//	The node address to look for in the response
			NodeAddress m_nodeAddress;

		public:
			//Function: match
			//	Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
			//
			//Parameters:
			//	packet - The <WirelessPacket> in which to try to find the pattern
			//
			//Returns:
			//	true if the packet matches a response pattern, false otherwise
			virtual bool match(const WirelessPacket& packet) override;
		};
	};

#endif

}