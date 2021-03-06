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
//precompiled header file

#ifdef _MSC_VER
#pragma warning( disable : 4100 )								//"unreferenced formal parameter"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include <boost/asio.hpp>										//for boost asio communication
#include <boost/circular_buffer.hpp>							//for boost circular buffer
#include <boost/date_time.hpp>									//for boost::posix_time::from_time_t
#include <boost/chrono/chrono.hpp>								//for boost::chrono
#include <boost/date_time/posix_time/posix_time_duration.hpp>	//for boost::posix_time::nanosec
#include <boost/date_time/posix_time/ptime.hpp>					//for boost ptime	
#include <boost/detail/endian.hpp>								//for endianess
#include <boost/numeric/conversion/cast.hpp>					//for boost::numeric_cast
#include <boost/optional.hpp>									//for boost::optional
#include <boost/utility/binary.hpp>								//for BOOST_BINARY

#include <algorithm>			//for std::min, std::replace
#include <chrono>				//for std::chrono::duration
#include <condition_variable>	//for std::condition_variable
#include <cstdint>				//for std::uint16_t and like fixed-width types
#include <exception>			//for std::exception
#include <functional>			//for std::function
#include <iomanip>				//for std::setprecision
#include <map>					//for std::map
#include <memory>				//for std::shared_ptr, std::unique_ptr
#include <mutex>				//for std::mutex
#include <regex>				//for std::regex
#include <set>					//for std::set
#include <sstream>				//for std::stringstream
#include <string>				//for std::string
#include <thread>				//for std::thread
#include <time.h>				//for gmtime_r and gmtime_s
#include <tuple>				//for std:tuple, std::get
#include <unordered_map>		//for std::unordered_map
#include <vector>				//for std::vector
#include <bitset>				//for std::bitset

//common MSCL files that will rarely change
#include "mscl/simple_any.h"
#include "mscl/Exceptions.h"
#include "mscl/TimedCondition.h"
#include "mscl/TimeSpan.h"
#include "mscl/Timestamp.h"
#include "mscl/Types.h"
#include "mscl/Version.h"
#include "mscl/Communication/BoostCommunication.h"
#include "mscl/Communication/Connection.h"
#include "mscl/Communication/OperatingSystemErrorCodes.h"