/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

#ifndef __HOME_FINDER_IMPL_H__
#define __HOME_FINDER_IMPL_H__


#include <OB/CORBA.h>
#include "QedoComponents_skel.h"
#include "NameServiceBase.h"
#include "Util.h"
#include <string>
#include <vector>
#include "HomeFinderEntry.h"


namespace Qedo {


typedef std::vector < HomeFinderEntry > HomeFinderEntryVector;

/**
 * implementation of the home finder
 *
 * This is the implementation of the Qedo_Components::HomeFinder interface which is a specialisation of 
 * Components::HomeFinder.
 */
class HomeFinderImpl : public POA_Qedo_Components::HomeFinder,
					   public NameServiceBase,
					   public PortableServer::RefCountServantBase
{

private:
	/** the orb */
	CORBA::ORB_var							orb_;

	/** the root_poa */
	PortableServer::POA_var					root_poa_;

	/** the root_poa manager */
	PortableServer::POAManager_var			root_poa_manager_;

	/** the vector for storing the home entries */
	HomeFinderEntryVector					entries_;

public:
	HomeFinderImpl(CORBA::ORB_ptr);
	~HomeFinderImpl();

	void initialize();

	//
    // IDL:Qedo_Components/HomeFinder/register_home:1.0
    //
    virtual Components::Cookie* register_home(Components::CCMHome_ptr ahome,
                                              const char* comp_repid,
                                              const char* home_repid,
											  const char* home_name)
        throw(CORBA::SystemException);

    //
    // IDL:Qedo_Components/HomeFinder/unregister_home:1.0
    //
    virtual void unregister_home(Components::Cookie* c)
        throw(CORBA::SystemException);

	//
    // IDL:omg.org/Components/HomeFinder/find_home_by_component_type:1.0
    //
    virtual Components::CCMHome_ptr find_home_by_component_type(const char* comp_repid)
        throw(Components::HomeNotFound,
              CORBA::SystemException);

    //
    // IDL:omg.org/Components/HomeFinder/find_home_by_home_type:1.0
    //
    virtual Components::CCMHome_ptr find_home_by_home_type(const char* home_repid)
        throw(Components::HomeNotFound,
              CORBA::SystemException);

    //
    // IDL:omg.org/Components/HomeFinder/find_home_by_name:1.0
    //
    virtual Components::CCMHome_ptr find_home_by_name(const char* home_name)
        throw(Components::HomeNotFound,
              CORBA::SystemException);

	//
	// Exceptions
	//
	class CannotInitialize {};
};


} // namespace Qedo


#endif
