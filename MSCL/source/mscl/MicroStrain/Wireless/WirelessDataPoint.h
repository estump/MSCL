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
//PUBLIC_HEADER
#pragma once

#include "WirelessChannel.h"
#include "mscl/MicroStrain/DataPoint.h"

namespace mscl
{
	//API Class: WirelessDataPoint
	//	Represents a single channel's data point within a sweep
	//
	//See Also: 
	//	<DataPoint>, <Value>
	class WirelessDataPoint : public DataPoint
	{
	public:
		//Default Constructor: WirelessDataPoint
		//	Builds a WirelessDataPoint object
		WirelessDataPoint();

#ifndef SWIG
		//Constructor: WirelessDataPoint
		//	Builds a WirelessDataPoint object.
		//	The channel name will be automatically generated from the given channel id.
		//	
		//Parameters:
		//	channelId - The <WirelessChannel::ChannelId> of the the data point
		//	channelNumber - The channel number associated with the data point (ch1 = 1, ch8 = 8).
		//	type - The <ValueType> of the value to be stored
		//	value - The value to store
		WirelessDataPoint(WirelessChannel::ChannelId channelId, uint8 channelNumber, ValueType type, const anyType& value);

		//Constructor: WirelessDataPoint
		//	Builds a WirelessDataPoint object.
		//	The channel name will be automatically generated from the given channel id.
		//	
		//Parameters:
		//	channelId - The <WirelessChannel::ChannelId> of the the data point
		//	channelNumber - The channel number associated with the data point (ch1 = 1, ch8 = 8).
		//	channelName - The channel name associated with the data point.
		//	type - The <ValueType> of the value to be stored
		//	value - The value to store
		WirelessDataPoint(WirelessChannel::ChannelId channelId, uint8 channelNumber, const std::string& channelName, ValueType type, const anyType& value);
#endif

	private:
		//Variable: m_channelId
		//	The <WirelessChannel::ChannelId> representing information about the channel this data point is associated with
		WirelessChannel::ChannelId m_channelId;

		//Variable: m_channelNumber
		//	The channel number associated with the data point (ch1 = 1, ch8 = 8).
		uint8 m_channelNumber;

		//Variable: m_channelName
		//	The channel name associated with the data point.
		std::string m_channelName;

	public:
		//API Function: channelId
		//	Gets the <WirelessChannel::ChannelId> associated with the data point.
		//
		//Returns:
		//	A <WirelessChannel::ChannelId> representing which channel this data corresponds with.
		WirelessChannel::ChannelId channelId() const;

		//API Function: channelNumber
		//	Gets the channel number associated with the data point (ch1 = 1, ch8 = 8), when applicable.
		//	Otherwise, this will return a 0 (for example, a Structural Health data point doesn't relate
		//	an actual channel on the Wireless Node, so this will be a 0).
		//	This number can be used to relate to the Node's <WirelessChannel> in the 
		//	map returned from calling <WirelessNode::channels>().
		//
		//Returns:
		//	The channel number associated with the data point.
		uint8 channelNumber() const;

		//API Function: channelName
		//	Gets the name of the channel. 
		//	This is the universal channel name that should be used for uploading to SensorCloud.
		//
		//Returns:
		//	The name of the channel.
		//
		//Exceptions:
		//	- <Error>: Unknown channel.
		const std::string& channelName() const;
	};

	//API Typedef: ChannelData
	//	A typedef for a collection (vector) of <WirelessDataPoint>s
	typedef std::vector<WirelessDataPoint> ChannelData;
}