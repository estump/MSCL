cmake_minimum_required(VERSION 3.1.3)
project(mscl)

find_package(catkin REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem chrono date_time)

include_directories(
  MSCL/source
  MSCL/source/mscl
  ${Boost_INCLUDE_DIRS}
  )

if (APPLE)
  set(CMAKE_CXX_FLAGS "-ftemplate-depth=900 ${CMAKE_CXX_FLAGS}")
endif (APPLE)

# Set this project to use C++11
set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
if (APPLE)
  set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif (APPLE)

# Grab all sources
file(GLOB msclSrcs
  MSCL/source/mscl/*.cpp
  MSCL/source/mscl/Communication/*.cpp
  MSCL/source/mscl/MicroStrain/*.cpp
  MSCL/source/mscl/MicroStrain/Inertial/*.cpp
  MSCL/source/mscl/MicroStrain/Inertial/Commands/*.cpp
  MSCL/source/mscl/MicroStrain/Inertial/Packets/*.cpp
  # Wireless API disabled
  # MSCL/source/mscl/MicroStrain/Wireless/Commands/*.cpp
  # MSCL/source/mscl/MicroStrain/Wireless/Configuration/*.cpp
  # MSCL/source/mscl/MicroStrain/Wireless/Features/*.cpp
  # MSCL/source/mscl/MicroStrain/Wireless/Packets/*.cpp
  )

catkin_package(
  INCLUDE_DIRS MSCL/source
  LIBRARIES mscl
  )

add_definitions(-DUNIX_SOCKETS)
add_library(mscl ${msclSrcs})
target_link_libraries(mscl ${Boost_LIBRARIES})

INSTALL(TARGETS mscl
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  )

INSTALL(DIRECTORY MSCL/source/mscl/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN Wrapper EXCLUDE
  # Wireless API disabled
  PATTERN Wireless EXCLUDE
  )
