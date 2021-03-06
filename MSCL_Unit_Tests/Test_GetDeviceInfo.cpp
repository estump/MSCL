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
#include "mscl/MicroStrain/Inertial/Commands/GetDeviceInfo.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace mscl;

BOOST_AUTO_TEST_SUITE(GetDeviceInfo_Test)

BOOST_AUTO_TEST_CASE(GetDeviceInfo_BuildCommand)
{
	//create the GetDeviceInfo command
	ByteStream b = GetDeviceInfo::buildCommand();

	BOOST_CHECK_EQUAL(b.read_uint8(0), 0x75);
	BOOST_CHECK_EQUAL(b.read_uint8(1), 0x65);
	BOOST_CHECK_EQUAL(b.read_uint8(2), 0x01);
	BOOST_CHECK_EQUAL(b.read_uint8(3), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(4), 0x02);
	BOOST_CHECK_EQUAL(b.read_uint8(5), 0x03);
	BOOST_CHECK_EQUAL(b.read_uint8(6), 0xE2);
	BOOST_CHECK_EQUAL(b.read_uint8(7), 0xC8);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_GetResponseResult)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	GenericInertialCommandResponse r = response.result();

	//check that the the response result is what it should be
	BOOST_CHECK_EQUAL(r.success(), false);
	BOOST_CHECK_EQUAL(r.errorCode(), InertialPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Fail_DescSet)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	Bytes fieldData1;
	fieldData1.push_back(0x03);
	fieldData1.push_back(0x00);
	InertialDataField field1(0x02F1, fieldData1); //invalid descriptor set

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field1), false);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Fail_FieldDataLen)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	Bytes fieldData;
	fieldData.push_back(0x03);
	InertialDataField field(0x01F1, fieldData); //bad field data length

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Fail_FieldDesc)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	Bytes fieldData;
	fieldData.push_back(0x03);
	fieldData.push_back(0x00);
	InertialDataField field(0x0101, fieldData); //invalid field descriptor

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Fail_CommandEcho)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	Bytes fieldData;
	fieldData.push_back(0x01);	//bad command echo
	fieldData.push_back(0x00);
	InertialDataField field(0x01F1, fieldData);

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field), false);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_FailWithErrorCode)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	Bytes fieldData;
	fieldData.push_back(0x03);
	fieldData.push_back(mscl::InertialPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
	InertialDataField field(0x01F1, fieldData); //good field, but with error code

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field), true);
	BOOST_CHECK_EQUAL(response.result().success(), false);
	BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::InertialPacket::MIP_ACK_NACK_ERROR_UNKNOWN_COMMAND);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Success_NotFullyMatched)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	Bytes fieldData1;
	fieldData1.push_back(0x03);
	fieldData1.push_back(0x00);
	InertialDataField field1(0x01F1, fieldData1); //good field

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field1), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), false);	//not yet fully matched
	BOOST_CHECK_EQUAL(response.result().success(), false);	//only got the ACK/NACK, so not fully complete
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Success_OnlyDeviceInfo)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	ByteStream bytes;
	bytes.append_uint16(1117);	//firmware version
	
	//add the 5 strings to the payload
	for(int x = 0; x < 5; x++)
	{
		//add 16 bytes to make a string
		for(int i = 0; i < 4; i++)
		{
			bytes.append_uint8(0x41);	//A
			bytes.append_uint8(0x42);	//B
			bytes.append_uint8(0x43);	//C
			bytes.append_uint8(0x44);	//D
		}
	}

	InertialDataField field2(0x0181, bytes.data()); //good device info field

	//check that the match succeeds
	BOOST_CHECK_EQUAL(response.match(field2), true); 
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);	//even though we didnt get an ACK/NACK, we still fully matched because the device info is enough to match
	BOOST_CHECK_EQUAL(response.result().success(), true);
	BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::InertialPacket::MIP_ACK_NACK_ERROR_NONE);
}

BOOST_AUTO_TEST_CASE(GetDeviceInfo_Match_Success)
{
	std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
	GetDeviceInfo::Response response(rc);

	ByteStream bytes;
	bytes.append_uint16(1117);	//firemware version
	
	//add the 5 strings to the payload
	for(int x = 0; x < 5; x++)
	{
		//add 16 bytes to make a string
		for(int i = 0; i < 4; i++)
		{
			bytes.append_uint8(0x41);	//A
			bytes.append_uint8(0x42);	//B
			bytes.append_uint8(0x43);	//C
			bytes.append_uint8(0x44);	//D
		}
	}

	Bytes fieldData1;
	fieldData1.push_back(0x03);
	fieldData1.push_back(0x00);
	InertialDataField field1(0x01F1, fieldData1); //good field

	//check that the match fails
	BOOST_CHECK_EQUAL(response.match(field1), true);
	BOOST_CHECK_EQUAL(response.fullyMatched(), false);	//not yet fully matched

	InertialDataField field2(0x0181, bytes.data()); //good device info field

	//check that the match succeeds
	BOOST_CHECK_EQUAL(response.match(field2), true); 
	BOOST_CHECK_EQUAL(response.fullyMatched(), true);	//we  fully matched because the device info is enough to match
	BOOST_CHECK_EQUAL(response.result().success(), true);
	BOOST_CHECK_EQUAL(response.result().errorCode(), mscl::InertialPacket::MIP_ACK_NACK_ERROR_NONE);

	mscl::InertialDeviceInfo resultInfo = response.parseData(response.result());

	BOOST_CHECK_EQUAL(resultInfo.fwVersion.str(), "1.1.17");
}

BOOST_AUTO_TEST_SUITE_END()