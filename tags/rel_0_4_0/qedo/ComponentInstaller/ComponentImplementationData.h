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

#ifndef __COMPONENT_IMPLEMENTATION_DATA_H__
#define __COMPONENT_IMPLEMENTATION_DATA_H__


#include <string>
#include <vector>


#if !defined(UNUSED) && defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif


namespace Qedo {


/**
 * @addtogroup ComponentInstaller
 * @{
 */


/**
 * file location
 */
struct LocationData
{
	/** the uri of the file */
	std::string								uri;
	/** the path of the file */
	std::string								file;
};


/**
 * the idl info
 */
enum IDLKind { LINK, FILEINARCHIVE, REPOSITORY };
struct IDLData
{
	/** kind if idl info */
	IDLKind									kind;
	/** location of idl file */
	LocationData							location;
};


/**
 * the valuetype info
 */
struct ValuetypeData
{
	/** the repository id of the valuetype */
	std::string									repid;
	/** the location of the implementation file */
	LocationData								location;
};


/**
 * the component implementation data
 */
struct ComponentImplementationData
{
	/** the uuid of the component implementation */
	std::string									uuid;
	/** the location of the idl spec */
	IDLData										idl;
	/** the RepId of the component */
	std::string									repid;
	/** the servant module */
	std::string									servant_module;
	/** the entry point for the servant module */
	std::string									servant_entry_point;
	/** the executor module */
	std::string									executor_module;
	/** the entry point for the executor module */
	std::string									executor_entry_point;
	/** the RepId of the home */
	std::string									home_repid;
	/** the name of the home */
	std::string									home_name;
	/** list of installed artifacts */
	std::vector < std::string >					artifacts;
	/** list of required valuetype factories */
	std::vector < ValuetypeData >				valuetypes;
};


/** @} */

}

#endif
