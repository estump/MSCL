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
#include "Erase.h"

namespace mscl
{
	ByteStream Erase::buildCommand(NodeAddress nodeAddress)
	{
		//build the command ByteStream
		ByteStream cmd;
		cmd.append_uint8(0x06);				//Start of Packet
		cmd.append_uint16(nodeAddress);		//Node address	(2 bytes)
		cmd.append_uint32(0x08100CFF);		//Command Bytes (4 bytes)

		return cmd;
	}

	Erase::Response::Response(std::weak_ptr<ResponseCollector> collector):
		ResponsePattern(collector)
	{
	}

	bool Erase::Response::match(DataBuffer& data)
	{
		const uint16 TOTAL_BYTES = 1;

		//if there aren't enough bytes in the buffer to match the response
		if(data.bytesRemaining() < TOTAL_BYTES)
		{
			//not a good response
			m_success = false;
			return false;
		}

		//create a save point with the data
		ReadBufferSavePoint savePoint(&data);

		uint8 resultByte = data.read_uint8();

		//single byte 0x21 is a fail response
		if(resultByte == 0x21)
		{
			//legitimate fail response
			m_success = false;
		}
		//single byte 0x06 is a success response
		else if(resultByte == 0x06)
		{
			//success response
			m_success = true;
		}
		else
		{
			//non-matching response
			m_success = false;
			return false;
		}

		//if we made it this far, the bytes match the expected response (success or fail)

		//commit the current read position
		savePoint.commit();

		//we have fully matched the response
		m_fullyMatched = true;

		//notify that the response was matched
		m_matchCondition.notify();

		return true;
	}
}