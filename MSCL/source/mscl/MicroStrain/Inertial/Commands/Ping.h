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

#include "GenericInertialCommand.h"

namespace mscl
{

#ifndef SWIG

	//Class: Ping
	//	Contains the logic for the Inertial Ping command.
	class Ping
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID			- CMD_PING	- The <InertialTypes::Command> for this command
		static const InertialTypes::Command CMD_ID = InertialTypes::CMD_PING;

	private:
		Ping();				//default constructor disabled

	public:
		//Function: buildCommand
		//	Builds the command packet
		//
		//Returns:
		//	A <ByteStream> containing the Inertial Ping command packet
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the Ping command.
		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const override { return CMD_ID; }

		public:
			//Constructor: Response
			//	Creates a Ping Response object
			//
			//Parameters:
			//	collector - The <ResponseCollector> used to register and unregister the response
			Response(std::weak_ptr<ResponseCollector> collector);
		};
	};

#endif

}