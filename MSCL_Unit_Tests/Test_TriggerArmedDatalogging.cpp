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
#include "mscl/MicroStrain/Wireless/Commands/TriggerArmedDatalogging.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(TriggerArmedDatalogging_Test)

BOOST_AUTO_TEST_CASE(TriggerArmedDatalogging_buildCommand)
{
	ByteStream result = TriggerArmedDatalogging::buildCommand(35567);

	BOOST_CHECK_EQUAL(result.size(), 18);

	uint8 sop = WirelessPacket::ASPP_START_OF_PACKET_BYTE;

	BOOST_CHECK_EQUAL(result.read_uint8(0), sop);
	BOOST_CHECK_EQUAL(result.read_uint8(1), 0x05);
	BOOST_CHECK_EQUAL(result.read_uint8(2), 0x00);
	BOOST_CHECK_EQUAL(result.read_uint16(3), 35567);
	BOOST_CHECK_EQUAL(result.read_uint8(5), 0x0A);
	BOOST_CHECK_EQUAL(result.read_uint16(6), 0x000E);
}

BOOST_AUTO_TEST_SUITE_END()