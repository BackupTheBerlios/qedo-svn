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

#include <OB/CORBA.h>
#include <Components.h>
#include <string>
#include <vector>
#include "Valuetypes.h"


namespace Qedo {


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

    HomeFinderEntry(const char*, const char*, const char*, Components::CCMHome_ptr);
    ~HomeFinderEntry();

	bool operator < (const HomeFinderEntry&) const {return true;}
	bool operator == (const HomeFinderEntry&) const {return true;}
};


} // namespace


#endif

