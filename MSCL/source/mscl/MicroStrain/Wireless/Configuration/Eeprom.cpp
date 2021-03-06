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
#include "Eeprom.h"
#include "mscl/Utils.h"

namespace mscl
{
	Eeprom::Eeprom(bool useCache) :
		m_useCache(useCache)
	{ }

	void Eeprom::useCache(bool enable)
	{
		m_useCache = enable;
	}

	void Eeprom::clearCache()
	{
		m_eepromCache.clear();
	}

	bool Eeprom::readCache(uint16 location, uint16& result)
	{
		EepromMap::iterator itr;

		//look up the eeprom in the cache
		itr = m_eepromCache.find(location);

		//if we found the eeprom in the cache
		if(itr != m_eepromCache.end())
		{
			//store the result
			result = itr->second;

			return true;
		}
		
		//we failed to find the eeprom in the cache
		return false;
	}

	void Eeprom::updateCache(uint16 location, uint16 value)
	{
		//try to find the value in the map to see if it already exists
		EepromMap::iterator itr = m_eepromCache.find(location);

		//if we couldn't find the value in the map
		if(itr == m_eepromCache.end())
		{
			//insert the value into the map
			m_eepromCache.insert(std::pair<uint16, uint16>(location, value));
		}
		//if we found the value in the map
		else
		{
			//update the value in the map
			itr->second = value;
		}
	}

	void Eeprom::clearCacheLocation(uint16 location)
	{
		//try to find the value in the map to verify it exists
		EepromMap::iterator itr = m_eepromCache.find(location);

		//if the location does exist in the map
		if(itr != m_eepromCache.end())
		{
			//remove the value from the map
			m_eepromCache.erase(itr);
		}
	}

	Value Eeprom::readEeprom(const EepromLocation& location)
	{
		//get the type and location from the EepromLocation object
		ValueType type = location.valueType();
		uint16 eepromLoc = location.location();

		//determine which readEeprom function to call, based on the valueType
		switch(type)
		{
			case valueType_uint16:
				return Value(type, readEeprom(eepromLoc));

			case valueType_float:
				return Value(type, readEeprom_float(eepromLoc));

			case valueType_uint32:
				return Value(type, readEeprom_uint32(eepromLoc));

			default:
				assert(false);	//we are trying to read a value with an invalid type? 
				return Value(type, readEeprom(eepromLoc));	//just default to uint16
		}
	}

	void Eeprom::writeEeprom(const EepromLocation& location, const Value& val)
	{
		//get the type and location from the EepromLocation object
		ValueType type = location.valueType();
		uint16 eepromLoc = location.location();

		//determine which writeEeprom function to call, based on the valueType
		switch(type)
		{
			case valueType_uint16:
				writeEeprom(eepromLoc, val.as_uint16());
				break;

			case valueType_float:
				writeEeprom_float(eepromLoc, val.as_float());
				break;

			case valueType_uint32:
				writeEeprom_uint32(eepromLoc, val.as_uint32());
				break;

			default:
				assert(false);	//we are trying to write a value with an invalid type? 
				writeEeprom(eepromLoc, val.as_uint16());	//just default to uint16
		}
	}

	float Eeprom::readEeprom_float(uint16 location)
	{
		//try to read the first part of the float
		uint16 msw = readEeprom(location);

		//try to read the second part of the float
		uint16 lsw = readEeprom(location + 2);

		//split the words into bytes
		uint8 b1, b2, b3, b4;
		Utils::split_uint16(msw, b1, b2);
		Utils::split_uint16(lsw, b3, b4);

		//convert the values into a float and return
		return Utils::make_float_little_endian(b1, b2, b3, b4);
	}

	uint32 Eeprom::readEeprom_uint32(uint16 location)
	{
		//try to read the first part of the float
		uint16 msw = readEeprom(location);

		//try to read the second part of the float
		uint16 lsw = readEeprom(location + 2);

		//make a uint32 and return
		return Utils::make_uint32(msw, lsw);
	}

	uint16 Eeprom::readEeprom_uint16(EepromLocation location)
	{
		return readEeprom(location.location());
	}

	float Eeprom::readEeprom_float(EepromLocation location)
	{
		return readEeprom_float(location.location());
	}

	uint32 Eeprom::readEeprom_uint32(EepromLocation location)
	{
		return readEeprom_uint32(location.location());
	}

	void Eeprom::writeEeprom_float(uint16 location, float value)
	{
		uint8 b1, b2, b3, b4;

		//split the float into its 4 bytes (in little endian)
		Utils::split_float_little_endian(value, b1, b2, b3, b4);

		//write the first eeprom location
		writeEeprom(location, Utils::make_uint16(b1, b2));

		//write the second eeprom location
		writeEeprom(location + 2, Utils::make_uint16(b3, b4)); //TODO: possibly throw a custom exception if this throws? We wrote the msw but not the lsw
	}

	void Eeprom::writeEeprom_uint16(EepromLocation location, uint16 value)
	{
		writeEeprom(location.location(), value);
	}

	void Eeprom::writeEeprom_float(EepromLocation location, float value)
	{
		writeEeprom_float(location.location(), value);
	}

	void Eeprom::writeEeprom_uint32(uint16 location, uint32 value)
	{
		uint16 msw = 0;
		uint16 lsw = 0;

		//split the uint32 into 2 parts
		Utils::split_uint32(value, msw, lsw);

		//try to write the msw
		writeEeprom(location, msw);

		//try to write the lsw
		writeEeprom(location + 2, lsw);	//TODO: possibly throw a custom exception if this throws? We wrote the msw but not the lsw
	}
}