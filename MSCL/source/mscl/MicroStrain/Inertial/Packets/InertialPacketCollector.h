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

#include <condition_variable>
#include <boost/circular_buffer.hpp>

#include "InertialDataPacket.h"

namespace mscl
{
	//Class: InertialPacketCollector
	//	Class that sets/matches expected responses, and stores all the Inertial packets
	class InertialPacketCollector
	{
	public:
		//Constructor: InertialPacketCollector
		//	The default constructor for the InertialPacketCollector
		InertialPacketCollector();

		//Destructor: InertialPacketCollector
		//	The destructor for the InertialPacketCollector
		~InertialPacketCollector();

	private:
		InertialPacketCollector(const InertialPacketCollector&);				//copy constructor disabled
		InertialPacketCollector& operator=(const InertialPacketCollector&);		//assignment operator disabled

	private:
		//Typedef: circular_data_buffer
		//	Typedef for a circular buffer of a <InertialDataPacket>
		typedef boost::circular_buffer_space_optimized<InertialDataPacket> circular_data_buffer;

		//Constant: MAX_DATA_BUFFER_SIZE = 1024 * 100	
		//	The maximum number of data packets that can be stored in the circular buffer
		static const int MAX_DATA_BUFFER_SIZE		= 1024 * 100; 

	private:
		//Variable: m_dataPackets
		//	A circular buffer that holds <InertialDataPacket>s 
		circular_data_buffer m_dataPackets;

		//Variable: m_packetMutex
		//	A mutex used for thread safety when accessing/modifying the m_dataPackets buffer
		std::mutex m_packetMutex;

		//Variable: m_emptyBufferCondition
		//	Allows the write to buffer thread to tell the reading thread when data is available
		std::condition_variable m_emptyBufferCondition;

	public:
		//Function: addDataPacket
		//	Adds a data packet to the data packets circular buffer
		//
		//Parameters:
		//	packet - The <InertialPacket> to be added to the buffer
		void addDataPacket(const InertialPacket& packet);

		//Function: getNextDataPacket
		//	Gets the next <InertialDataPacket> in the buffer.
		//
		//Parameters:
		//	packet - The <InertialDataPacket> to hold the result.
		//	timeout - the timeout, in milliseconds, to wait for the next data packet if necessary.
		//
		//Exceptions:
		//	- <Error_NoData>: No data was collected.
		void getNextDataPacket(InertialDataPacket& packet, uint32 timeout);

		//Function: getDataPackets
		//	Gets up to the requested amount of data packets that have been collected.
		//
		//Parameters:
		//	packets - A vector of <InertialDataPacket> to hold the result.
		//	maxPackets - The maximum number of packets to return. If this is 0 (default), all sweeps will be returned.
		void getDataPackets(std::vector<InertialDataPacket>& packets, uint32 timeout=0, uint32 maxPackets=0);

		//Function: totalPackets
		//	Gets the total number of data packets that are currently in the buffer.
		//
		//Returns:
		//	The total number of data packets that are currently in the buffer.
		uint32 totalPackets();
	};
}