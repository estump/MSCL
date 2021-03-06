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
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

	//Class: Erase
	//	Contains logic for the Erase Node command
	class Erase
	{
	private:
		Erase();						//default constructor disabled
		Erase(const Erase&);			//copy constructor disabled
		Erase& operator=(const Erase&);	//assignment operator disabled

	public:
		//Function: buildCommand
		//	Builds the Erase command packet.
		//
		//Parameters:
		//	nodeAddress - The address of the Node to build the command for.
		//
		//Returns:
		//	A <ByteStream> containing the command packet.
		static ByteStream buildCommand(NodeAddress nodeAddress);

		//Class: Response
		//	Handles the response to the Erase node command
		class Response : public ResponsePattern
		{
		public:
			//Constructor: Response
			//	Creates a Erase Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response
			explicit Response(std::weak_ptr<ResponseCollector> collector);

		public:
			//Function: match
			//	Checks if the bytes passed in match the response pattern from their current read position
			//
			//Parameters:
			//	data - The <DataBuffer> containing the bytes in which to try to find the pattern
			//
			//Returns:
			//	true if the response pattern was found, false otherwise
			virtual bool match(DataBuffer& data) override;
		};
	};

#endif
}