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
#include "mscl/MicroStrain/Inertial/InertialParser.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialDataPacket.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketCollector.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"
#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialParser_Test)

BOOST_AUTO_TEST_SUITE(InertialParser_parseAsPacket)

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_NotEnoughData)
{
	//not enough bytes to be any MIP packet
	ByteStream b;
	b.append_uint16(0x7565);

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	//check that the result is inertialParserResult_notEnoughData b/c there isn't enough data to be a MIP packet 
	BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_notEnoughData);

	b.append_uint8(0x80);
	b.append_uint8(0xAB);	//payload length
	b.append_uint16(0x0102);
	b.append_uint16(0x0102);

	DataBuffer buffer2(b.data());

	//check that the result is inertialParserResult_notEnoughData b/c there isn't enough data in the payload
	BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer2, packet), inertialParserResult_notEnoughData);
}

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_InvalidPacket)
{
	ByteStream b;
	b.append_uint16(0x0165);	//not a start of MIP packet
	b.append_uint16(0x0000);
	b.append_uint16(0x0000);
	b.append_uint16(0x0000);

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	//check that the result is inertialParserResult_invalidPacket b/c the first bytes aren't the start of a packet
	BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_invalidPacket);
}

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_BadChecksum)
{
	ByteStream b;
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint16(0x0000);	//bad checksum

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	//check that the result is inertialParserResult_badChecksum b/c the checksum is invalid
	BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_badChecksum);
}

BOOST_AUTO_TEST_CASE(InertialParser_parseAsPacket_CompletePacket)
{
	ByteStream b;
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	
	ChecksumBuilder check;
	check.appendByteStream(b);
	uint16 checksum = check.fletcherChecksum();
	b.append_uint16(checksum);//append valid checksum

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	//check that the result is inertialParserResult_completePacket b/c the packet is valid
	BOOST_CHECK_EQUAL(parser.parseAsPacket(buffer, packet), inertialParserResult_completePacket);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(InertialParser_ParseSuite)

BOOST_AUTO_TEST_CASE(InertialParser_parse_validDataPacket_AfterBadBytes)
{
	ByteStream b;
	b.append_uint16(0x0104);
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint16(b.calculateFletcherChecksum(2, 19));

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	InertialDataPacket dataPacket;

	//check that calling getNextDataPacket currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(buffer);

	//calling getNextDataPacket now should return a legitimate InertialDataPacket
	packetCollector.getNextDataPacket(dataPacket, 0);

	BOOST_CHECK_EQUAL(dataPacket.isDataPacket(), true);
	BOOST_CHECK_EQUAL(dataPacket.descriptorSet(), DescriptorSet::DESC_SET_DATA_SENSOR);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_validDataPacket)
{
	ByteStream b;
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	
	ChecksumBuilder check;
	check.appendByteStream(b);
	uint16 checksum = check.fletcherChecksum();
	b.append_uint16(checksum);//append valid checksum

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	InertialDataPacket dataPacket;

	//check that calling getNextDataPacket currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(buffer);

	//calling getNextDataPacket now should return a legitimate InertialDataPacket
	packetCollector.getNextDataPacket(dataPacket, 0);

	BOOST_CHECK_EQUAL(dataPacket.isDataPacket(), true);
	BOOST_CHECK_EQUAL(dataPacket.descriptorSet(), DescriptorSet::DESC_SET_DATA_SENSOR);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_responsePacket_notExpected)
{
	ByteStream b;
	b.append_uint16(0x7565);
	b.append_uint8(0x01);
	b.append_uint8(0x04);	//payload length
	b.append_uint8(0x04);
	b.append_uint8(0xF1);
	b.append_uint8(0x01);
	b.append_uint8(0x00);
	
	ChecksumBuilder check;
	check.appendByteStream(b);
	uint16 checksum = check.fletcherChecksum();
	b.append_uint16(checksum);//append valid checksum

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	InertialDataPacket dataPacket;

	//check that calling getNextDataPacket currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(buffer);

	//check that calling getNextDataPacket still throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_badChecksum)
{
	ByteStream b;
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint16(0x0102);	//bad checksum

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	InertialDataPacket dataPacket;

	//check that calling getNextDataPacket currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(buffer);

	//check that calling getNextDataPacket still throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_notEnoughData)
{
	ByteStream b;
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);

	ChecksumBuilder check;
	check.appendByteStream(b);
	uint16 checksum = check.fletcherChecksum();
	b.append_uint16(checksum);//append the valid checksum 

	//add another part of a valid packet, but missing the checksum
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	InertialDataPacket dataPacket;

	//check that calling getNextDataPacket currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(buffer);

	//check that calling getNextDataPacket doesn't throw an exception as there is legitimate data
	BOOST_CHECK_NO_THROW(packetCollector.getNextDataPacket(dataPacket, 0));

	//check that calling getNextDataPacket now throws an Error_NoData exception again
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);	
}

BOOST_AUTO_TEST_CASE(InertialParser_parse_validDataPacket_AfterNotEnoughData)
{
	ByteStream b;
	b.append_uint16(0x7565);	//make it look like a valid packet by putting random SOP bytes here
	b.append_uint16(0x7565);
	b.append_uint8(0x80);
	b.append_uint8(0x0E);	//payload length
	b.append_uint8(0x0E);
	b.append_uint8(0x04);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint32(0x00000000);
	b.append_uint16(b.calculateFletcherChecksum(2, 19));

	DataBuffer buffer(b.data());

	std::shared_ptr<ResponseCollector> responseCollector(new ResponseCollector);
	InertialPacketCollector packetCollector;
	InertialParser parser(&packetCollector, responseCollector);
	InertialPacket packet;

	InertialDataPacket dataPacket;

	//check that calling getNextDataPacket currently throws an Error_NoData exception as there are no packets
	BOOST_CHECK_THROW(packetCollector.getNextDataPacket(dataPacket, 0), Error_NoData);

	//call the parse() function, sending the DataBuffer we created
	parser.parse(buffer);

	//calling getNextDataPacket now should return a legitimate InertialDataPacket
	packetCollector.getNextDataPacket(dataPacket, 0);

	BOOST_CHECK_EQUAL(dataPacket.isDataPacket(), true);
	BOOST_CHECK_EQUAL(dataPacket.descriptorSet(), DescriptorSet::DESC_SET_DATA_SENSOR);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE_END()