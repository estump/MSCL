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

#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
	//API Class: HistogramOptions
	//	Contains all of the Histogram options that can be configured for a WirelessNode.
	class HistogramOptions
	{
	public:
		//API Default Constructor: HistogramOptions
		//	Creates a default constructed HistogramOptions object.
		HistogramOptions();

	private:
		//Variable: m_transmitRate
		//	The transmit rate of the Histogram.
		WirelessTypes::WirelessSampleRate m_transmitRate;

		//Variable: m_binStart
		//	The start of the first bin in the Histogram.
		uint16 m_binStart;

		//Variable: m_binSize
		//	The size of each bin in the Histogram.
		uint16 m_binSize;

	public:
		//API Function: transmitRate
		//	Gets the transmit rate set in this options object, as a <WirelessTypes::WirelessSampleRate>.
		WirelessTypes::WirelessSampleRate transmitRate() const;

		//API Function: transmitRate
		//	Sets the transmit rate in this options object.
		//
		//Parameters:
		//	rate - The transmit rate (as a <WirelessTypes::WirelessSampleRate>) to set.
		void transmitRate(WirelessTypes::WirelessSampleRate rate);

		//API Function: binsStart
		//	Gets the bins start set in this options object.
		uint16 binsStart() const;

		//API function: binsStart
		//	Sets the bins start in this options object.
		//
		//Parameters:
		//	start - The start of the first bin in the Histogram.
		void binsStart(uint16 start);

		//API Function: binsSize
		//	Gets the bins size set in this options object.
		uint16 binsSize() const;

		//API function: binsSize
		//	Sets the bins size in this options object.
		//
		//Parameters:
		//	size - The size of each bin in the Histogram.
		void binsSize(uint16 size);
	};
}