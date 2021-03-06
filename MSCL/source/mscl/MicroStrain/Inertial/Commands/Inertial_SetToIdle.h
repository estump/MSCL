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

	//Class: Inertial_SetToIdle
	//	Contains the logic for the Inertial "Set to Idle" command.
	class Inertial_SetToIdle
	{
	public:
		//Constants: Packet Bytes
		//	CMD_ID		- CMD_SET_IDLE	- The <InertialTypes::Command> for this command
		static const InertialTypes::Command CMD_ID = InertialTypes::CMD_SET_IDLE;

	private:
		Inertial_SetToIdle();										//default constructor disabled
		Inertial_SetToIdle(const Inertial_SetToIdle&);				//copy constructor disabled
		Inertial_SetToIdle& operator=(const Inertial_SetToIdle&);	//assignment operator disabled

	public:
		//Function: buildCommand
		//	Builds the command packet.
		//
		//Returns:
		//	A <ByteStream> containing the Inertial_SetToIdle command packet.
		static ByteStream buildCommand();

		//Class: Response
		//	Handles the response to the Inertial_SetToIdle command.
		class Response : public GenericInertialCommand::Response
		{
		protected:
			virtual InertialTypes::Command commandId() const override { return CMD_ID; }

		public:
			//Constructor: Response
			//	Creates the Inertial_SetToIdle::Response object.
			//	
			//Parameters:
			//	collector - The ResponseCollector to register the response with.
			Response(std::weak_ptr<ResponseCollector> collector);
		};
	};

#endif

}