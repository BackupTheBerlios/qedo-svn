/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

static char rcsid[] = "$Id: ComponentInstallationImpl.cpp,v 1.1 2002/10/07 07:17:02 tom Exp $";

#include "ComponentInstallationImpl.h"
#include <OB/CosNaming.h>

#include <iostream>
#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

namespace Qedo {

ComponentInstallationImpl::ComponentInstallationImpl (CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
}


ComponentInstallationImpl::~ComponentInstallationImpl()
{
}


void
ComponentInstallationImpl::initialize()
{
	try
	{
		CORBA::Object_var root_poa_obj = orb_->resolve_initial_references ("RootPOA");
		root_poa_ = PortableServer::POA::_narrow (root_poa_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		std::cerr << "ComponentInstallationImpl: Fatal error - no root POA available." << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ComponentInstallationImpl: Fatal error - cannot narrow root POA." << std::endl;
		throw CannotInitialize();
	}

	root_poa_manager_ = root_poa_->the_POAManager();

	root_poa_manager_->activate();

	CosNaming::NamingContext_var ns;

	// Now try to bind with the Name Service
	try
	{
		CORBA::Object_var ns_obj = orb_->resolve_initial_references ("NameService");
		ns = CosNaming::NamingContext::_narrow (ns_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		std::cerr << "ComponentInstallationImpl: Name Service not found" << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ComponentInstallationImpl: Cannot narrow object reference of Name Service" << std::endl;
		throw CannotInitialize();
	}

	if (CORBA::is_nil (ns))
	{
		std::cerr << "ComponentInstallationImpl: Name Service is nil" << std::endl;
		throw CannotInitialize();
	}

	// Create the Qedo and Installers naming context
	CosNaming::Name current_name;
	current_name.length (1);
	current_name[0].id = CORBA::string_dup ("Qedo");
	current_name[0].kind = CORBA::string_dup ("");
	try
	{
		ns->bind_new_context (current_name);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		// Ignore this exception
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ComponentInstallationImpl: CORBA system exception during binding context 'Qedo'" << std::endl;
		throw CannotInitialize();
	}

	current_name.length(2);
	current_name[1].id = CORBA::string_dup ("Installers");
	current_name[1].kind = CORBA::string_dup ("");

	try
	{
		ns->bind_new_context (current_name);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		// Ignore this exception
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ComponentInstallationImpl: CORBA system exception during binding context 'Installers'" << std::endl;
		throw CannotInitialize();
	}

	// Now bind this Component Server Activator with the Name Service, use the name Qedo/Activators/<hostname>
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		std::cerr << "ComponentInstallationImpl: Cannot determine my hostname" << std::endl;
		throw CannotInitialize();
	}

	std::cout << "ComponentInstallationImpl: Binding Component Installer under Qedo/Installers/" << hostname << std::endl;

	current_name.length (3);
	current_name[2].id = CORBA::string_dup (hostname);
	current_name[2].kind = CORBA::string_dup ("");

	CORBA::Object_var my_ref = this->_this();

	try
	{
		ns->bind (current_name, my_ref);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		try
		{
			ns->rebind (current_name, my_ref);
		}
		catch (CosNaming::NamingContext::InvalidName&)
		{
			std::cerr << "ComponentInstallationImpl: Name Service complains about an invalid name" << std::endl;
			throw CannotInitialize();
		}
		catch (CORBA::SystemException&)
		{
			std::cerr << "ComponentInstallationImpl: CORBA system exception in rebind()" << std::endl;
			throw CannotInitialize();
		}
	}
	catch (CosNaming::NamingContext::InvalidName&)
	{
		std::cerr << "ComponentInstallationImpl: Name Service complains about an invalid name" << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ComponentInstallationImpl: CORBA system exception during bind()" << std::endl;
		throw CannotInitialize();
	}
}


void 
ComponentInstallationImpl::install (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
	// The description has the form: servant_module:servant_entry_point:executor_module:executor_entry_point
	// First test for duplicate UUIDs
	std::vector <InstalledComponent>::const_iterator inst_iter;

	for (inst_iter = installed_components_.begin(); inst_iter != installed_components_.end(); inst_iter++)
	{
		if ((*inst_iter).uuid_ == implUUID)
		{
			std::cerr << "ComponentInstallationImpl: Component type already installed with UUID " << implUUID << std::endl;
			return;
		}
	}

	std::string::size_type pos;
	std::string desc = component_loc;

	pos = desc.find (":");
	if (pos == std::string::npos)
	{
		std::cerr << "ComponentInstallationImpl: Cannot extract servant module name" << std::endl;
		throw Components::Deployment::InvalidLocation();
	}
	std::string servant_module = desc.substr (0, pos);

	desc = desc.substr (pos + 1);

	pos = desc.find (":");
	if (pos == std::string::npos)
	{
		std::cerr << "ComponentInstallationImpl: Cannot extract servant entry point" << std::endl;
		throw Components::Deployment::InvalidLocation();
	}
	std::string servant_entry_point = desc.substr (0, pos);

	desc = desc.substr (pos + 1);

	pos = desc.find (":");
	if (pos == std::string::npos)
	{
		std::cerr << "ComponentInstallationImpl: Cannot extract executor module name" << std::endl;
		throw Components::Deployment::InvalidLocation();
	}
	std::string executor_module = desc.substr (0, pos);

	desc = desc.substr (pos + 1);

	std::string executor_entry_point = desc;

	// Register this installation
	InstalledComponent new_component (implUUID, servant_module, servant_entry_point, executor_module, executor_entry_point);

	installed_components_.push_back (new_component);

	std::cout << "ComponentInstallationImpl: New component installed with UUID " << implUUID << std::endl;
}


void 
ComponentInstallationImpl::replace (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
}


void 
ComponentInstallationImpl::remove (const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::RemoveFailure)
{
}


Components::Deployment::Location 
ComponentInstallationImpl::get_implementation( const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::Deployment::InstallationFailure)
{
	// Scan through the installed components
	std::vector <InstalledComponent>::const_iterator inst_iter;

	for (inst_iter = installed_components_.begin(); inst_iter != installed_components_.end(); inst_iter++)
	{
		if ((*inst_iter).uuid_ == implUUID)
		{
			// Component found
			std::string description = (*inst_iter).servant_module_; description += ":";
			description += (*inst_iter).servant_entry_point_; description += ":";
			description += (*inst_iter).executor_module_; description += ":";
			description += (*inst_iter).executor_entry_point_;

			return CORBA::string_dup (description.c_str());
		}
	}

	throw Components::Deployment::UnknownImplId();
}


char* 
ComponentInstallationImpl::upload (const char* implUUID, const ::CORBA::OctetSeq& package)
throw (Components::Deployment::InstallationFailure)
{
	return 0;
}

} // namespace Qedo

