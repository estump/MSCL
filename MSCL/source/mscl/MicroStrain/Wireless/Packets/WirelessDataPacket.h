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

#include <vector>

#include "WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/WirelessChannel.h"
#include "mscl/MicroStrain/Wireless/WirelessDataPoint.h"
#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/Types.h"

namespace mscl
{
#ifndef SWIG
	//Class: WirelessDataPacket
	//	A class representing a Wireless Data Packet.
	class WirelessDataPacket : public WirelessPacket
	{
	public:
		//Constructor: WirelessDataPacket
		//	The default constructor for a Wireless Data Packet
		WirelessDataPacket();

		virtual ~WirelessDataPacket() {};

	private:
		//Variable: m_dataSweeps
		//	Contains one or more data sweeps 
		std::vector<DataSweep> m_dataSweeps;

		//Variable: m_sweepPos
		//	The current position into m_dataSweeps to get the next sweep at
		uint32 m_sweepPos;

	protected:
		//Variable: m_dataType
		//	The type of data that is present in the packet
		WirelessTypes::DataType m_dataType;

		//Variable: m_sweepSize
		//	The size of a single sweep within this packet
		uint32 m_sweepSize;

		//Variable: m_numSweeps
		//	The number of sweeps within this packet
		std::size_t m_numSweeps;

		//Variable: m_payloadOffsetChannelData
		//	The offset into the payload of the data packet where channel data starts.
		uint16 m_payloadOffsetChannelData;

	protected:
		//Function: addSweep
		//	Adds a single <DataSweep> to the data packet
		//
		//Parameters:
		//	sweep - The <DataSweep> to add to the data packet
		void addSweep(const DataSweep& sweep);

		//Function: addDataPoint
		//	Adds a <WirelessDataPoint> from a payload to the given <ChannelData> container.
		//
		//Parameters:
		//	container - The <ChannelData> container to add the data point to.
		//	channelNumber - The channel number to set (ch1 = 1, ch8 = 8).
		//	channelDataIndex - The index into the channel data (not the actual channel index). ex. if channel 1 and 3 are active, channel 1 = index 0 and channel 3 = index 1.
		//	sweepIndex - The index of the sweep into the packet starting at index 0.
		//	channelName - The <WirelessChannel::ChannelId> to give to the WirelessDataPoint.
		void addDataPoint(ChannelData& container, uint8 channelNumber, int channelDataIndex, int sweepIndex, WirelessChannel::ChannelId channelName) const;

		//Function: wirelessChannelFromChNum
		//	Converts a channel number to a <WirelessChannel>
		//
		//Parameters:
		//	channelNum - The channel number to convert (starting at index 1, so channel 1 = 1, channel 8 = 8)
		//
		//Returns:
		//	The <WirelessChannel> representing the passed in channel number
		virtual WirelessChannel::ChannelId wirelessChannelFromChNum(int channelNum);

		//Function: getPayloadData
		//	Reads a value out of the packet's payload based on the given position and the data's <DataType>.
		//
		//Parameters:
		//	payloadPosition - The position into the payload to read from.
		//	result - The anyType to hold the resulting payload data.
		void getPayloadData(size_t payloadPosition, anyType& result) const;

	public:
		//Function: getNextSweep
		//	Gets the next <DataSweep> in the packet
		//
		//Parameters:
		//	sweepResult - The <DataSweep> to hold the result.
		void getNextSweep(DataSweep& sweepResult);

		//Function: numSweeps
		//	Gets the total number of <DataSweep>s that are in this data packet
		//
		//Returns:
		//	The total number of <DataSweep>s that are in this data packet
		std::size_t numSweeps() const;

		//Function: numSweepsRemaining
		//	Gets the number of remaining <DataSweep>s that have not been obtained by the user
		//
		//Returns:
		//	The number of remaining <DataSweep>s that have not been obtained by the user
		std::size_t numSweepsRemaining() const;

		//Function: moreSweeps
		//	Whether or not there are more <DataSweep>s in the data packet
		//
		//Returns:
		//	true if there are more <DataSweep>s available, false otherwise
		bool moreSweeps() const;
	};
#endif
}