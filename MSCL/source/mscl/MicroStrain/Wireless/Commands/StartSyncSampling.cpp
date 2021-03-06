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
#include "StartSyncSampling.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{

	ByteStream StartSyncSampling::buildCommand(NodeAddress nodeAddress)
	{
		//build the command ByteStream
		ByteStream cmd;
		cmd.append_uint8(WirelessPacket::ASPP_START_OF_PACKET_BYTE);	//Start of Packet
		cmd.append_uint8(0x05);											//Delivery Stop Flag
		cmd.append_uint8(0x00);											//App Data Type
		cmd.append_uint16(nodeAddress);									//Node Address
		cmd.append_uint8(0x02);											//Payload Length
		cmd.append_uint16(COMMAND_ID);									//Command ID

		//calculate the checksum of bytes 2-8
		uint16 checksum = cmd.calculateSimpleChecksum(1, 7);

		cmd.append_uint16(checksum);		//Checksum		(2 bytes)

		return cmd;
	}

	StartSyncSampling::Response::Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector),
		m_nodeAddress(nodeAddress)
	{
	}

	bool StartSyncSampling::Response::match(const WirelessPacket& packet)
	{
		WirelessPacket::Payload payload = packet.payload();

		//check the main bytes of the packet
		if( packet.deliveryStopFlags().toByte() != 0x07			||	//delivery stop flag
			packet.type() != WirelessPacket::packetType_command ||	//app data type
			packet.nodeAddress() != m_nodeAddress				||	//node address
			payload.size() != 0x03								||	//payload length
			payload.read_uint16(0) != COMMAND_ID					//Command ID
			)			
		{
			//failed to match some of the bytes
			return false;
		}

		//if we made it here, the packet matches the response pattern
		m_success = true;

		//we have fully matched the response
		m_fullyMatched = true;

		//notify that the response was matched
		m_matchCondition.notify();

		return true;
	}
}