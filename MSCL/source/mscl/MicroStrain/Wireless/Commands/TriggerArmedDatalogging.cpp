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
#include "mscl/Utils.h"
#include "TriggerArmedDatalogging.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{

	ByteStream TriggerArmedDatalogging::buildCommand(NodeAddress nodeAddress)
	{
		//get the current system time
		uint64 timeNow = Utils::getCurrentSystemTime();
		uint32 secondsPart = static_cast<uint32>(timeNow / 1000000000);
		uint32 nanosPart = static_cast<uint32>(timeNow % 1000000000);

		//build the command ByteStream
		ByteStream cmd;
		cmd.append_uint8(WirelessPacket::ASPP_START_OF_PACKET_BYTE);	//Start of Packet
		cmd.append_uint8(0x05);											//Delivery Stop Flag
		cmd.append_uint8(0x00);											//App Data Type
		cmd.append_uint16(nodeAddress);									//Node Address
		cmd.append_uint8(0x0A);											//Payload Length
		cmd.append_uint16(COMMAND_ID);									//Command ID
		cmd.append_uint32(secondsPart);									//UTC Timestamp (seconds)
		cmd.append_uint32(nanosPart);									//UTC Timestamp (nanoseconds)

		//calculate the checksum of bytes 2-8
		uint16 checksum = cmd.calculateSimpleChecksum(1, 15);

		cmd.append_uint16(checksum);									//Checksum		(2 bytes)

		return cmd;
	}
}