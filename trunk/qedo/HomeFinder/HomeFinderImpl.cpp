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

static char rcsid[] = "$Id: HomeFinderImpl.cpp,v 1.1 2003/02/07 11:24:35 neubauer Exp $";

#include "HomeFinderImpl.h"
#include "Valuetypes.h"
#include "Output.h"


namespace Qedo {


/**
 * constructor
 */
HomeFinderImpl::HomeFinderImpl(CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
}


/**
 * destructor
 */
HomeFinderImpl::~HomeFinderImpl()
{
}


/**
 * initialize
 */
void
HomeFinderImpl::initialize()
{
	try
	{
		CORBA::Object_var root_poa_obj = orb_->resolve_initial_references ("RootPOA");
		root_poa_ = PortableServer::POA::_narrow (root_poa_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		NORMAL_ERR ("ComponentServerImpl: Fatal error - no root POA available.");
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Fatal error - cannot narrow root POA.");
		throw CannotInitialize();
	}

	root_poa_manager_ = root_poa_->the_POAManager();
	root_poa_manager_->activate();

	// get NameService
    if (! initNameService(orb_))
    {
        throw CannotInitialize();
    }

    // bind HomeFinder
	CORBA::Object_var homeFinder_ref = this->_this();
    std::string name = "Qedo/HomeFinder";
    //char hostname[256];
	//gethostname(hostname, 256);
    //name.append(hostname);

    if ( ! registerName(name, homeFinder_ref, true))
    {
        throw CannotInitialize();
    }

	std::cout << "..... bound under " << name << std::endl << std::endl;
}


/**
 * implementation of IDL:Qedo_Components/HomeFinder/register_home:1.0
 */
Components::Cookie* 
HomeFinderImpl::register_home(Components::CCMHome_ptr ahome, const char* comp_repid, const char* home_repid, const char* home_name)
throw(CORBA::SystemException)
{
	HomeFinderEntry entry = HomeFinderEntry(home_repid, comp_repid, home_name, ahome);
	entries_.push_back(entry);
	std::cout << "home registered" << std::endl;
	std::cout << "..... home id: " << home_repid << std::endl;
	std::cout << "..... component id: " << comp_repid << std::endl;
	std::cout << "..... name: " << home_name << std::endl << std::endl;

	return entry.cookie_;
}


/**
 * implementation of IDL:Qedo_Components/HomeFinder/unregister_home:1.0
 */
void 
HomeFinderImpl::unregister_home(Components::Cookie* c)
throw(CORBA::SystemException)
{
	HomeFinderEntryVector::iterator iter;
	
	for (iter = entries_.begin(); iter != entries_.end(); iter++)
	{
		if ((*iter).cookie_->equal(c))
		{
			std::cout << "home unregistered" << std::endl;
			std::cout << "..... home id: " << (*iter).home_repid_ << std::endl;
			std::cout << "..... component id: " << (*iter).comp_repid_ << std::endl;
			std::cout << "..... name: " << (*iter).name_ << std::endl << std::endl;
			entries_.erase(iter);
			return;
		}
	}
}


/**
 * implementation of IDL:omg.org/Components/HomeFinder/find_home_by_component_type:1.0
 */
Components::CCMHome_ptr 
HomeFinderImpl::find_home_by_component_type(const char* comp_repid)
throw(Components::HomeNotFound, CORBA::SystemException)
{
	HomeFinderEntryVector::iterator iter;
	
	for (iter = entries_.begin(); iter != entries_.end(); iter++)
	{
		if (!(*iter).comp_repid_.compare(comp_repid))
		{
			// existency check ???
			Components::CCMHome_var home = Components::CCMHome::_duplicate((*iter).home_);
			return home._retn();
		}
	}

	throw Components::HomeNotFound();
}


/**
 * implementation of IDL:omg.org/Components/HomeFinder/find_home_by_home_type:1.0
 */
Components::CCMHome_ptr 
HomeFinderImpl::find_home_by_home_type(const char* home_repid)
throw(Components::HomeNotFound, CORBA::SystemException)
{
	HomeFinderEntryVector::const_iterator iter;
	
	for (iter = entries_.begin(); iter != entries_.end(); iter++)
	{
		if (!(*iter).home_repid_.compare(home_repid))
		{
			// existency check ???
			Components::CCMHome_var home = Components::CCMHome::_duplicate((*iter).home_);
			return home._retn();
		}
	}

	throw Components::HomeNotFound();
}


/**
 * implementation of IDL:omg.org/Components/HomeFinder/find_home_by_name:1.0
 */
Components::CCMHome_ptr 
HomeFinderImpl::find_home_by_name(const char* home_name)
throw(Components::HomeNotFound, CORBA::SystemException)
{
	HomeFinderEntryVector::const_iterator iter;
	
	for (iter = entries_.begin(); iter != entries_.end(); iter++)
	{
		if (!(*iter).name_.compare(home_name))
		{
			// existency check ???
			Components::CCMHome_var home = Components::CCMHome::_duplicate((*iter).home_);
			return home._retn();
		}
	}

	throw Components::HomeNotFound();
}


} // namespace