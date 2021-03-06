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
#include "mscl/MicroStrain/Wireless/Commands/AutoCal.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ResponseCollector.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

WirelessPacket buildAutoCalNodeRecResponse(int nodeAddress)
{
	ByteStream payload;
	payload.append_uint16(0x0064);	//cmd id
	payload.append_uint8(0x00);	//status flag
	payload.append_float(5.0f);	//time to completion

	WirelessPacket packet;
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
	packet.type(WirelessPacket::packetType_NodeReceived);
	packet.nodeAddress(nodeAddress);
	packet.payload(payload.data());

	return packet;
}

WirelessPacket buildAutoCalCompletionResponse(int nodeAddress)
{
	ByteStream payload;
	payload.append_uint16(0x0064);	//cmd id
	payload.append_uint8(0x00);	//completion flag
	payload.append_uint8(0x00);	//ch1 error flag
	payload.append_float(0.0f);	//ch1 offset
	payload.append_uint8(0x00);	//ch2 error flag
	payload.append_float(0.0f);	//ch2 offset
	payload.append_uint8(0x00);	//ch3 error flag
	payload.append_float(0.0f);	//ch3 offset
	payload.append_float(20.5f);//temperature

	//build the correct packet response first
	WirelessPacket packet;
	packet.deliveryStopFlags(DeliveryStopFlags::fromByte(0x07));
	packet.type(WirelessPacket::packetType_reply);
	packet.nodeAddress(nodeAddress);
	packet.payload(payload.data());

	return packet;
}

BOOST_AUTO_TEST_SUITE(AutoCal_Test)

BOOST_AUTO_TEST_SUITE(AutoCal_shmLink_Test)

BOOST_AUTO_TEST_CASE(AutoCalResult_shmLink_Constructor)
{
	AutoCalResult_shmLink r;
	
	//check that the default constructor initialized correctly
	BOOST_CHECK_EQUAL(r.completionFlag(), WirelessTypes::autocal_notComplete);
	BOOST_CHECK_EQUAL(r.errorFlagCh1(), WirelessTypes::autocalError_none);
	BOOST_CHECK_EQUAL(r.errorFlagCh2(), WirelessTypes::autocalError_none);
	BOOST_CHECK_EQUAL(r.errorFlagCh3(), WirelessTypes::autocalError_none);
	BOOST_CHECK_CLOSE(r.offsetCh1(), 0.0, 0.1);
	BOOST_CHECK_CLOSE(r.offsetCh2(), 0.0, 0.1);
	BOOST_CHECK_CLOSE(r.offsetCh3(), 0.0, 0.1);
	BOOST_CHECK_CLOSE(r.temperature(), 0.0, 0.1);
}

BOOST_AUTO_TEST_CASE(AutoCal_shmLink_BuildCommand)
{
	ByteStream b = AutoCal::buildCommand_shmLink(824);

	//Check all the bytes in the ByteStream
	BOOST_CHECK_EQUAL(b.read_uint8(0), 0xAA);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x05);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x00);
	BOOST_CHECK_EQUAL(b.read_uint16(3), 0x0338);	//node address
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x02);		//payload len
	BOOST_CHECK_EQUAL(b.read_uint16(6), 0x0064);	//cmd id
	BOOST_CHECK_EQUAL(b.read_uint16(8), 0x00A6);
}

BOOST_AUTO_TEST_CASE(AutoCal_MatchNodeReceived_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	AutoCal::Response response(123, WirelessModels::node_shmLink2, Version(9, 0), rc);

	WirelessPacket packet = buildAutoCalNodeRecResponse(123);

	BOOST_CHECK_EQUAL(response.match(packet), true);
	BOOST_CHECK_EQUAL(response.calStarted(), true);
	BOOST_CHECK_CLOSE(response.calTime(), 5.0, 0.1);
	BOOST_CHECK_EQUAL(response.success(), false);
	BOOST_CHECK_EQUAL(response.completionFlag(), WirelessTypes::autocal_notComplete);
	BOOST_CHECK_EQUAL(response.fullyMatched(), false);
	BOOST_CHECK_EQUAL(response.infoBytes().size(), 0);
}

BOOST_AUTO_TEST_CASE(AutoCal_MatchNodeReceived_Error)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	AutoCal::Response response(123, WirelessModels::node_shmLink2, Version(9, 0), rc);

	ByteStream payload;
	payload.append_uint16(0x0064);	//cmd id
	payload.append_uint8(0x01);	//failed to parse the payload
	payload.append_float(0.0f);	//time to completion

	WirelessPacket packet = buildAutoCalNodeRecResponse(123);
	packet.payload(payload.data());

	BOOST_CHECK_EQUAL(response.match(packet), true);
	BOOST_CHECK_EQUAL(response.calStarted(), false);
	BOOST_CHECK_CLOSE(response.calTime(), 0.0, 0.1);
	BOOST_CHECK_EQUAL(response.success(), false);
	BOOST_CHECK_EQUAL(response.completionFlag(), WirelessTypes::autocal_notComplete);
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response.infoBytes().size(), 0);
}

BOOST_AUTO_TEST_CASE(AutoCal_MatchShmLink_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	AutoCal::Response response(123, WirelessModels::node_shmLink2, Version(9, 0), rc);

	WirelessPacket nodeReceivedPacket = buildAutoCalNodeRecResponse(123);

	BOOST_CHECK_EQUAL(response.match(nodeReceivedPacket), true);
	BOOST_CHECK_EQUAL(response.calStarted(), true);
	BOOST_CHECK_CLOSE(response.calTime(), 5.0, 0.1);
	BOOST_CHECK_EQUAL(response.success(), false);
	BOOST_CHECK_EQUAL(response.completionFlag(), WirelessTypes::autocal_notComplete);
	BOOST_CHECK_EQUAL(response.fullyMatched(), false);
	BOOST_CHECK_EQUAL(response.infoBytes().size(), 0);

	WirelessPacket completionPacket = buildAutoCalCompletionResponse(123);

	BOOST_CHECK_EQUAL(response.match(completionPacket), true);
	BOOST_CHECK_EQUAL(response.calStarted(), true);
	BOOST_CHECK_CLOSE(response.calTime(), 5.0, 0.1);
	BOOST_CHECK_EQUAL(response.success(), true);
	BOOST_CHECK_EQUAL(response.completionFlag(), WirelessTypes::autocal_success);
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);
	BOOST_CHECK_EQUAL(response.infoBytes().size(), 19);
}

BOOST_AUTO_TEST_SUITE_END()	//end autocal_shmLink
BOOST_AUTO_TEST_SUITE_END()