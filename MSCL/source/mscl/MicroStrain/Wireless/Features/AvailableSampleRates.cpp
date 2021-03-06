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

#include "AvailableSampleRates.h"

namespace mscl
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//NOTE: These sample rates must always been in order from fastest to slowest rate.
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous = {
			{WirelessTypes::sampleRate_512Hz},
			{WirelessTypes::sampleRate_256Hz},
			{WirelessTypes::sampleRate_128Hz},
			{WirelessTypes::sampleRate_64Hz},
			{WirelessTypes::sampleRate_32Hz},
			{WirelessTypes::sampleRate_16Hz},
			{WirelessTypes::sampleRate_8Hz},
			{WirelessTypes::sampleRate_4Hz},
			{WirelessTypes::sampleRate_2Hz},
			{WirelessTypes::sampleRate_1Hz},
			{WirelessTypes::sampleRate_2Sec},
			{WirelessTypes::sampleRate_5Sec},
			{WirelessTypes::sampleRate_10Sec},
			{WirelessTypes::sampleRate_30Sec},
			{WirelessTypes::sampleRate_1Min},
			{WirelessTypes::sampleRate_2Min},
			{WirelessTypes::sampleRate_5Min},
			{WirelessTypes::sampleRate_10Min},
			{WirelessTypes::sampleRate_30Min},
			{WirelessTypes::sampleRate_60Min}};

	const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst = {
			{WirelessTypes::sampleRate_4096Hz},
			{WirelessTypes::sampleRate_2048Hz},
			{WirelessTypes::sampleRate_1024Hz},
			{WirelessTypes::sampleRate_512Hz},
			{WirelessTypes::sampleRate_256Hz},
			{WirelessTypes::sampleRate_128Hz},
			{WirelessTypes::sampleRate_64Hz},
			{WirelessTypes::sampleRate_32Hz}};

	const WirelessTypes::WirelessSampleRates AvailableSampleRates::armedDatalog = AvailableSampleRates::burst;	//same as burst



	const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_glink2 = {
			{WirelessTypes::sampleRate_512Hz},
			{WirelessTypes::sampleRate_256Hz},
			{WirelessTypes::sampleRate_128Hz},
			{WirelessTypes::sampleRate_64Hz},
			{WirelessTypes::sampleRate_32Hz}};

	const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_glink2 = {
			{WirelessTypes::sampleRate_10kHz},
			{WirelessTypes::sampleRate_9kHz},
			{WirelessTypes::sampleRate_8kHz},
			{WirelessTypes::sampleRate_7kHz},
			{WirelessTypes::sampleRate_6kHz},
			{WirelessTypes::sampleRate_5kHz},
			{WirelessTypes::sampleRate_4kHz},
			{WirelessTypes::sampleRate_3kHz},
			{WirelessTypes::sampleRate_2kHz},
			{WirelessTypes::sampleRate_1kHz},
			{WirelessTypes::sampleRate_512Hz},
			{WirelessTypes::sampleRate_256Hz},
			{WirelessTypes::sampleRate_128Hz},
			{WirelessTypes::sampleRate_64Hz},
			{WirelessTypes::sampleRate_32Hz}};

	const WirelessTypes::WirelessSampleRates AvailableSampleRates::armedDatalog_glink2 = AvailableSampleRates::burst_glink2; //same as burst



	const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_vlink = {
			{WirelessTypes::sampleRate_10kHz},
			{WirelessTypes::sampleRate_9kHz},
			{WirelessTypes::sampleRate_8kHz},
			{WirelessTypes::sampleRate_7kHz},
			{WirelessTypes::sampleRate_6kHz},
			{WirelessTypes::sampleRate_5kHz},
			{WirelessTypes::sampleRate_4kHz},
			{WirelessTypes::sampleRate_3kHz},
			{WirelessTypes::sampleRate_2kHz},
			{WirelessTypes::sampleRate_1kHz},
			{WirelessTypes::sampleRate_512Hz},
			{WirelessTypes::sampleRate_256Hz},
			{WirelessTypes::sampleRate_128Hz},
			{WirelessTypes::sampleRate_64Hz},
			{WirelessTypes::sampleRate_32Hz}};

	const WirelessTypes::WirelessSampleRates AvailableSampleRates::armedDatalog_vlink = AvailableSampleRates::burst_vlink;	//same as burst


	const WirelessTypes::WirelessSampleRates AvailableSampleRates::burst_iepeLink = {
			{WirelessTypes::sampleRate_104170Hz},
			{WirelessTypes::sampleRate_78125Hz},
			{WirelessTypes::sampleRate_62500Hz},
			{WirelessTypes::sampleRate_50kHz},
			{WirelessTypes::sampleRate_25000Hz},
			{WirelessTypes::sampleRate_12500Hz},
			{WirelessTypes::sampleRate_10kHz},
			{WirelessTypes::sampleRate_1kHz}};


	const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_tclink = {
			{WirelessTypes::sampleRate_8Hz},
			{WirelessTypes::sampleRate_4Hz},
			{WirelessTypes::sampleRate_2Hz},
			{WirelessTypes::sampleRate_1Hz},
			{WirelessTypes::sampleRate_2Sec},
			{WirelessTypes::sampleRate_5Sec},
			{WirelessTypes::sampleRate_10Sec},
			{WirelessTypes::sampleRate_30Sec},
			{WirelessTypes::sampleRate_1Min},
			{WirelessTypes::sampleRate_2Min},
			{WirelessTypes::sampleRate_5Min},
			{WirelessTypes::sampleRate_10Min},
			{WirelessTypes::sampleRate_30Min},
			{WirelessTypes::sampleRate_60Min}};



	const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_tclink1ch = {
			{WirelessTypes::sampleRate_64Hz},
			{WirelessTypes::sampleRate_32Hz},
			{WirelessTypes::sampleRate_16Hz},
			{WirelessTypes::sampleRate_8Hz},
			{WirelessTypes::sampleRate_4Hz},
			{WirelessTypes::sampleRate_2Hz},
			{WirelessTypes::sampleRate_1Hz},
			{WirelessTypes::sampleRate_2Sec},
			{WirelessTypes::sampleRate_5Sec},
			{WirelessTypes::sampleRate_10Sec},
			{WirelessTypes::sampleRate_30Sec},
			{WirelessTypes::sampleRate_1Min},
			{WirelessTypes::sampleRate_2Min},
			{WirelessTypes::sampleRate_5Min},
			{WirelessTypes::sampleRate_10Min},
			{WirelessTypes::sampleRate_30Min},
			{WirelessTypes::sampleRate_60Min}};



	const WirelessTypes::WirelessSampleRates AvailableSampleRates::continuous_envlink = {
			{WirelessTypes::sampleRate_2Hz},
			{WirelessTypes::sampleRate_1Hz},
			{WirelessTypes::sampleRate_2Sec},
			{WirelessTypes::sampleRate_5Sec},
			{WirelessTypes::sampleRate_10Sec},
			{WirelessTypes::sampleRate_30Sec},
			{WirelessTypes::sampleRate_1Min},
			{WirelessTypes::sampleRate_2Min},
			{WirelessTypes::sampleRate_5Min},
			{WirelessTypes::sampleRate_10Min},
			{WirelessTypes::sampleRate_30Min},
			{WirelessTypes::sampleRate_60Min}};
}