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
#include "NodeFeatures_tclink6ch.h"

#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "AvailableSampleRates.h"

namespace mscl
{
	NodeFeatures_tclink6ch::NodeFeatures_tclink6ch(const NodeInfo& info) :
		NodeFeatures(info)
	{
		addCalCoeffChannelGroup(1, NodeEepromMap::CH_ACTION_SLOPE_1, NodeEepromMap::CH_ACTION_ID_1);
		addCalCoeffChannelGroup(2, NodeEepromMap::CH_ACTION_SLOPE_2, NodeEepromMap::CH_ACTION_ID_2);
		addCalCoeffChannelGroup(3, NodeEepromMap::CH_ACTION_SLOPE_3, NodeEepromMap::CH_ACTION_ID_3);
		addCalCoeffChannelGroup(4, NodeEepromMap::CH_ACTION_SLOPE_4, NodeEepromMap::CH_ACTION_ID_4);
		addCalCoeffChannelGroup(5, NodeEepromMap::CH_ACTION_SLOPE_5, NodeEepromMap::CH_ACTION_ID_5);
		addCalCoeffChannelGroup(6, NodeEepromMap::CH_ACTION_SLOPE_6, NodeEepromMap::CH_ACTION_ID_6);
		addCalCoeffChannelGroup(7, NodeEepromMap::CH_ACTION_SLOPE_7, NodeEepromMap::CH_ACTION_ID_7);

		static const ChannelMask THERMOCPL_CHS(BOOST_BINARY(00111111)); //ch1 - ch6
		m_channelGroups.emplace_back(THERMOCPL_CHS, "Thermocouple Channels", 
									 ChannelGroup::SettingsMap{
										 {WirelessTypes::chSetting_hardwareGain, NodeEepromMap::HW_GAIN_1},
										 {WirelessTypes::chSetting_filterSettlingTime, NodeEepromMap::FILTER_1},
										 {WirelessTypes::chSetting_thermocoupleType, NodeEepromMap::THERMOCPL_TYPE}}
		);

		//Channels
		m_channels.emplace_back(1, WirelessChannel::channel_1, WirelessTypes::chType_diffTemperature);	//temp (thermocouple)
		m_channels.emplace_back(2, WirelessChannel::channel_2, WirelessTypes::chType_diffTemperature);	//temp (thermocouple)
		m_channels.emplace_back(3, WirelessChannel::channel_3, WirelessTypes::chType_diffTemperature);	//temp (thermocouple)
		m_channels.emplace_back(4, WirelessChannel::channel_4, WirelessTypes::chType_diffTemperature);	//temp (thermocouple)
		m_channels.emplace_back(5, WirelessChannel::channel_5, WirelessTypes::chType_diffTemperature);	//temp (thermocouple)
		m_channels.emplace_back(6, WirelessChannel::channel_6, WirelessTypes::chType_diffTemperature);	//temp (thermocouple)
		m_channels.emplace_back(7, WirelessChannel::channel_7, WirelessTypes::chType_temperature);		//cjc temp
		
		if(info.model != WirelessModels::node_tcLink_6ch_ip67)
		{
			m_channels.emplace_back(8, WirelessChannel::channel_8, WirelessTypes::chType_rh);			//% RH

			addCalCoeffChannelGroup(8, NodeEepromMap::CH_ACTION_SLOPE_8, NodeEepromMap::CH_ACTION_ID_8);
		}
	}

	const WirelessTypes::SamplingModes NodeFeatures_tclink6ch::samplingModes() const
	{
		//build and return the sampling modes that are supported
		WirelessTypes::SamplingModes result;

		result.push_back(WirelessTypes::samplingMode_sync);
		result.push_back(WirelessTypes::samplingMode_nonSync);

		//no support for burst
		//no support for armed datalogging

		return result;
	}

	const WirelessTypes::DataFormats NodeFeatures_tclink6ch::dataFormats() const
	{
		//build and return the data formats that are supported
		WirelessTypes::DataFormats result;

		result.push_back(WirelessTypes::dataFormat_4byte_float);

		//no support for uint16

		return result;
	}

	const WirelessTypes::WirelessSampleRates NodeFeatures_tclink6ch::sampleRates(WirelessTypes::SamplingMode samplingMode) const
	{
		//the list of sample rates varies for each sampling mode
		switch(samplingMode)
		{
			case WirelessTypes::samplingMode_nonSync:
			case WirelessTypes::samplingMode_sync:
				return AvailableSampleRates::continuous_tclink;

			default:
				throw Error("Invalid SamplingMode");
		}
	}

	WirelessTypes::SettlingTime NodeFeatures_tclink6ch::maxFilterSettlingTime(const SampleRate& rate) const
	{
		return maxFilterSettlingTime_A(rate);
	}
}