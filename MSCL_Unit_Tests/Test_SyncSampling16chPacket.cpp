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
#include "mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket_16ch.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Sync16chPacket_Test)

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_4ByteFloat)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x12);	//sample mode / data type - 4 byte float
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2
	payloadBytes.push_back(0);		//channel data b3
	payloadBytes.push_back(0);		//channel data b4
	payloadBytes.push_back(1);		//channel data b1
	payloadBytes.push_back(1);		//channel data b2
	payloadBytes.push_back(1);		//channel data b3
	payloadBytes.push_back(1);		//channel data b4

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//call the addDataPacket() function to parse the packet as an LDC Packet
	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 0);
	
	//check that the sweep data matches the packet we added
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
	BOOST_CHECK_EQUAL(sweep.tick(), 1);
	BOOST_CHECK_EQUAL(sweep.timestamp().nanoseconds(), 0);
	BOOST_CHECK_EQUAL(sweep.nanoseconds(), 0);
	BOOST_CHECK_EQUAL(sweep.sampleRate().prettyStr(), "2Hz");
	BOOST_CHECK_EQUAL(sweep.nodeRssi(), 1);
	BOOST_CHECK_EQUAL(sweep.baseRssi(), 1);
	BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);

	collector.getNextDataSweep(sweep, 0);
	
	//check that the sweep data matches the packet we added
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
	BOOST_CHECK_EQUAL(sweep.tick(), 2);	//check that the tick incremented (by MSCL, not by the packet)
	BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_float);
	BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling_Burst);

	//check that calling getNextDataSweep now throws an Error_NoData exception
	BOOST_CHECK_THROW(collector.getNextDataSweep(sweep, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_2ByteUint)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x23);	//sample mode / data type - 2 byte uint
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(254);	//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//call the addDataPacket() function to parse the packet as an LDC Packet
	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 0);
	
	//check that the sweep data matches the packet we added
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
	BOOST_CHECK_EQUAL(sweep.tick(), 1);
	BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling);
	BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint16);
	BOOST_CHECK_EQUAL(sweep.data()[0].as_uint16(), 254);

	//check that calling getNextDataSweep now throws an Error_NoData exception
	BOOST_CHECK_THROW(collector.getNextDataSweep(sweep, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_2ByteUintShifted)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x21);	//data type - 2 byte uint shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(254);	//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//call the addDataPacket() function to parse the packet as an LDC Packet
	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 0);
	
	//check that the sweep data matches the packet we added
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
	BOOST_CHECK_EQUAL(sweep.tick(), 1);
	BOOST_CHECK_EQUAL(sweep.data()[0].storedAs(), valueType_uint16);
	BOOST_CHECK_EQUAL(sweep.data()[0].as_uint16(), 127);	//check that the data was shifted (divided by 2)

	//check that calling getNextDataSweep now throws an Error_NoData exception
	BOOST_CHECK_THROW(collector.getNextDataSweep(sweep, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_Constructor_NoChannelMask)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(0);		//channel mask - NO CHANNELS
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x23);	//sample mode / data type - 2 byte uint
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//call the addDataPacket() function to parse the packet as an LDC Packet
	WirelessPacketCollector collector;
	collector.addDataPacket(packet);

	DataSweep sweep;
	collector.getNextDataSweep(sweep, 0);
	
	//check that the sweep data matches the packet we added
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 345);
	BOOST_CHECK_EQUAL(sweep.tick(), 1);
	BOOST_CHECK_EQUAL(sweep.samplingType(), DataSweep::samplingType_SyncSampling);
	BOOST_CHECK_EQUAL(sweep.data().size(), 0);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_Valid)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x22);	//app id / data type - 2 byte uint32 shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_SmallPayload)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadAppID)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x32);	//BAD app id / data type - 2 byte uint32 shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadStopFlags)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);		//channel mask
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x23);	//app id / data type - 2 byte uint32 shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(15));	//INVALID DELIVERY STOP FLAGS
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadDataType)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x28);	//(INVALID DATA TYPE)
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_BadPacketType)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);
	payloadBytes.push_back(1);		//channel mask - 1 channel
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x23);	//data type - 2 byte uint32 shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_LDC); //INVALID packet type
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_NoChannelsActive)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);
	payloadBytes.push_back(0);		//channel mask (NO CHANNELS)
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x23);	//data type - 2 byte uint32 shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_CASE(Sync16chPacket_IntegrityCheck_InvalidPayloadBytes)
{
	Bytes payloadBytes;
	payloadBytes.push_back(0);
	payloadBytes.push_back(3);		//channel mask - 2 channels but not enough data for 2 channels
	payloadBytes.push_back(112);	//sample rate
	payloadBytes.push_back(0x23);	//data type - 2 byte uint32 shifted
	payloadBytes.push_back(0);		//tick msb
	payloadBytes.push_back(1);		//tick lsb
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		
	payloadBytes.push_back(0);		//channel data b1
	payloadBytes.push_back(0);		//channel data b2

	//build a WirelessPacket
	WirelessPacket packet;
	packet.nodeAddress(345);
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0));
	packet.type(WirelessPacket::packetType_SyncSampling_16ch);
	packet.nodeRSSI(1);
	packet.baseRSSI(1);
	packet.payload(payloadBytes);	//give the packet the payload bytes we created

	//check that the integrity check failed
	BOOST_CHECK_EQUAL(SyncSamplingPacket_16ch::integrityCheck(packet), false);
}

BOOST_AUTO_TEST_SUITE_END()