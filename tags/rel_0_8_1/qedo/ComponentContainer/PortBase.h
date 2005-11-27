/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#ifndef __PORT_BASE_H__
#define __PORT_BASE_H__

#include <CORBA.h>
#include <Components.h>
#include "Valuetypes.h"
#include "Util.h"
#include <string>
#include <vector>


#ifdef WIN32
#pragma warning (disable : 4231) // nonstandard extension used : 'extern' before template explicit instantiation
#endif


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * Base class for all port entries
 */
class PortBase
{
protected:
	/** the port name */
	std::string port_name_;

	/** the interface repository id of the ports interface */
	std::string type_id_;

	/**
	 * constructor
	 * \param port_name The name of the port.
	 * \param type_id The interface repository type id of the port.
	 */
    PortBase (const char* port_name, const char* type_id);

	/**
	 * constructor
	 */
	PortBase();

	/**
	 * copy constructor
	 */
	PortBase (const PortBase&);

	/**
	 * destructor
	 */
    ~PortBase();

public:
	/**
	 * provides the port name
	 * return value is string& for the convenient ==operator for const char* and char*
	 * \return The port name.
	 */
CONTAINERDLL_API	const std::string& port_name() const;
};

/** @} */

} // namespace Qedo

#endif

