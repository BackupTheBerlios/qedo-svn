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

#ifndef __HOME_FINDER_ENTRY_H__
#define __HOME_FINDER_ENTRY_H__

#include <CORBA.h>
#include <Components.h>
#include <string>
#include <vector>
#include "Valuetypes.h"


namespace Qedo {


/**
 * @addtogroup Runtime
 * bla.
 * @{
 */


/**
 * @defgroup HomeFinder Home Finder
 * When starting the homefinder executable the HomeFinder implementations starts and registers in the NameService
 * under Qedo/HomeFinder. Thus the ORBInitializer of the ComponentServer implementation can resolve the object
 * and register it with register_initial_reference under "ComponentHomeFinder" as required by the CCM standard.
 * @{
 */


/**
 * helper class for registration
 */
class HomeFinderEntry
{

public:
	/** interface repository id for the home */
	std::string					home_repid_;

	/** interface repository id for the component */
	std::string					comp_repid_;

	/** name under what the home was registered */
	std::string					name_;

	/** the home IOR */
	Components::CCMHome_var		home_;

	/** the cookie to identify this registration entry */
	Qedo::Cookie_impl*			cookie_;

	/**
	 * constructor
	 * \param home_repid The interface repository id of the home.
	 * \param comp_repid The interface repository id of the component.
	 * \param name The name of the home.
	 * \param home The home.
	 */
    HomeFinderEntry(const char* home_repid, const char* comp_repid, const char* name, Components::CCMHome_ptr home);

	/**
	 * destructor
	 */
    ~HomeFinderEntry();

	/**
	 * comparison
	 */
	bool operator < (const HomeFinderEntry&) const {return true;}

	/**
	 * comparison
	 */
	bool operator == (const HomeFinderEntry&) const {return true;}
};

/** @} */

/** @} */

} // namespace


#endif

