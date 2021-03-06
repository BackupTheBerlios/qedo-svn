/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

static char rcsid[] = "$Id: ContainerInterfaceImpl.cpp,v 1.2 2002/11/08 10:35:08 neubauer Exp $";

#include "ContainerInterfaceImpl.h"
#include "EntityHomeServant.h"
#include "SessionHomeServant.h"
#include "Output.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <sys/types.h>
#endif

namespace Qedo {

HomeEntry::HomeEntry (Qedo::HomeServantBase* home_servant)
: home_servant_ (home_servant)
{
	home_servant_->_add_ref();
}


HomeEntry::HomeEntry()
{
}


HomeEntry::HomeEntry (const HomeEntry& home_entry)
: home_servant_ (home_entry.home_servant_)
{
	home_servant_->_add_ref();
}


HomeEntry& 
HomeEntry::operator= (const HomeEntry& home_entry)
{
	if (home_servant_)
		home_servant_->_remove_ref();

	home_servant_ = home_entry.home_servant_;
	home_servant_->_add_ref();

	return *this;
}


HomeEntry::~HomeEntry()
{
	DEBUG_OUT ("HomeEntry: Destructor called");
	home_servant_->_remove_ref();
}


ContainerInterfaceImpl::ContainerInterfaceImpl (CORBA::ORB_ptr orb, 
												PortableServer::POA_ptr root_poa, 
												ContainerType container_type,
												Components::Deployment::ComponentInstallation_ptr component_installer)
: orb_ (CORBA::ORB::_duplicate (orb)),
  root_poa_ (PortableServer::POA::_duplicate (root_poa)),
  container_type_ (container_type),
  component_installer_ (Components::Deployment::ComponentInstallation::_duplicate (component_installer))
{
}


ContainerInterfaceImpl::~ContainerInterfaceImpl()
{
}


#ifdef _WIN32
HINSTANCE 
ContainerInterfaceImpl::load_shared_library (const char* name)
{
	HINSTANCE handle_lib;

	handle_lib = LoadLibrary (name);

	if (handle_lib < (HINSTANCE)HINSTANCE_ERROR)
	{
		// Unable to load DLL
		LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf, 0, NULL);
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot load dynamic library: ", (LPCTSTR)lpMsgBuf);
		
		// Free the buffer.
		LocalFree( lpMsgBuf );
		handle_lib = 0;
	}

	return handle_lib;
}
#else
void* 
ContainerInterfaceImpl::load_shared_library (const char* name)
{

	void * handle_lib;

	handle_lib = dlopen( name ,RTLD_LAZY);

	if (!handle_lib)
	{
		// Unable to load shared object
		NORMAL_ERR2 ( "ContainerBase: Cannot load dynamic library ", name );
		NORMAL_ERR2 ( "ContainerBase: Error was: ", dlerror() );

	}

	return handle_lib;
}
#endif

Components::ConfigValues*
ContainerInterfaceImpl::configuration()
throw (CORBA::SystemException)
{
	return 0;
}


Components::Deployment::ComponentServer_ptr 
ContainerInterfaceImpl::get_component_server()
throw (CORBA::SystemException)
{
	return 0;
}


Components::CCMHome_ptr
ContainerInterfaceImpl::install_home (const char* id,
									  const char* entrypt,
									  const Components::ConfigValues& config)
throw (Components::Deployment::UnknownImplId,
       Components::Deployment::ImplEntryPointNotFound,
       Components::Deployment::InstallationFailure,
       Components::Deployment::InvalidConfiguration,
       CORBA::SystemException)
{
	DEBUG_OUT ("ContainerInterfaceImpl: install_home() called");

	//
	// Retrieve implementation description from the Component Installer
	//
	CORBA::String_var description;

	try
	{
		description = component_installer_->get_implementation (id);
	}
	catch (Components::Deployment::UnknownImplId&)
	{
		NORMAL_ERR2 ( "ContainerInterfaceImpl: Unknown Implementation Id ", id );
		throw;
	}

	//
	// Now extract relevant information out of the description
	//
	std::string::size_type pos;
	std::string desc = (const char*)description;

	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract servant module name" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string servant_module = desc.substr (0, pos);

	desc = desc.substr (pos + 1);

	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract servant entry point" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string servant_entry_point = desc.substr (0, pos);

	desc = desc.substr (pos + 1);

	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract executor module name" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string executor_module = desc.substr (0, pos);

	desc = desc.substr (pos + 1);

	std::string executor_entry_point = desc;

	// Now we have all relevant information and can go to load the dynamic code modules
#ifdef _WIN32
	HINSTANCE handle_lib;
#else
	void* handle_lib;
#endif

	handle_lib = load_shared_library (servant_module.c_str());

	if (! handle_lib)
	{
		NORMAL_ERR2 ("ContainerInterfaceImpl: Failed to load servant module ", servant_module);
		throw Components::Deployment::InstallationFailure();
	}

	// Find the entry point function
	Qedo::HomeServantBase* (*servant_entry_proc)();

#ifdef _WIN32
	(FARPROC&)servant_entry_proc = GetProcAddress (handle_lib, servant_entry_point.c_str());
#else
	servant_entry_proc = (Qedo::HomeServantBase* (*)()) 
				dlsym (handle_lib, servant_entry_point.c_str());
#endif

	if (servant_entry_proc == NULL)
	{
		// Unable to locate entry point
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot find entry point function for servant module: ",
			servant_entry_point.c_str());
		throw Components::Deployment::ImplEntryPointNotFound();
	}
	
	Qedo::HomeServantBase* qedo_home_servant;

	qedo_home_servant = (*servant_entry_proc)();

	if (! qedo_home_servant)
	{
		NORMAL_ERR ("ContainerInterfaceImpl: Entry point function returned a nil home servant");
		throw Components::Deployment::InstallationFailure();
	}

	// Validate the created home servant
	// Service or session container only accept Qedo::SessionHomeServants and process and entity containers
	// only accept Qedo::EntityHomeServants
	switch (container_type_)
	{
	case CT_SERVICE:
	case CT_SESSION:
		Qedo::SessionHomeServant* session_home;

		session_home = dynamic_cast <Qedo::SessionHomeServant*> (qedo_home_servant);

		if (! session_home)
		{
			NORMAL_ERR ("ContainerInterfaceImpl: Container type is service or session, but loaded home servant is not a Qedo::SessionHomeServant");
			throw Components::Deployment::InstallationFailure();
		}
		break;
	case CT_PROCESS:
	case CT_ENTITY:
		Qedo::EntityHomeServant* entity_home;

		entity_home = dynamic_cast <Qedo::EntityHomeServant*> (qedo_home_servant);

		if (! entity_home)
		{
			NORMAL_ERR ("ContainerInterfaceImpl: Container type is process or entity, but loaded home servant is not a Qedo::EntityHomeServant");
			throw Components::Deployment::InstallationFailure();
		}
		break;
	}
	
	//
	// Load the executor module
	//
	handle_lib = load_shared_library (executor_module.c_str());

	if (! handle_lib)
	{
		NORMAL_ERR2 ("ContainerInterfaceImpl: Failed to load executor module ", executor_module);
		throw Components::Deployment::InstallationFailure();
	}

	//
	// Find the entry point function
	//
	Components::HomeExecutorBase_ptr (*executor_entry_proc)();

#ifdef _WIN32
	(FARPROC&)executor_entry_proc = GetProcAddress (handle_lib, executor_entry_point.c_str());
#else
	executor_entry_proc = (::Components::HomeExecutorBase_ptr (*)())
				dlsym ( handle_lib, executor_entry_point.c_str() );
#endif

	if (executor_entry_proc == NULL)
	{
		// Unable to locate entry point
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot find entry point function for executor module: ",
			executor_entry_point.c_str());
		throw Components::Deployment::ImplEntryPointNotFound();
	}
	
	Components::HomeExecutorBase_ptr home_executor;
		
	home_executor = (*executor_entry_proc)();

	if (! home_executor)
	{
		NORMAL_ERR ("ContainerInterfaceImpl: Entry point function returned a nil home executor");
		throw Components::Deployment::InstallationFailure();
	}

	// Initialize home servant
	qedo_home_servant->initialize (root_poa_, home_executor);

	HomeEntry new_entry (qedo_home_servant);

	installed_homes_.push_back (new_entry);

	Components::CCMHome_var home_ref = qedo_home_servant->ref();

	// Okay, our home servant is stored in the home entry and the executor is stored in the
	// home servant, so we do not need any additional reference here
	qedo_home_servant->_remove_ref();
	home_executor->_remove_ref();

	return home_ref._retn();
}


void 
ContainerInterfaceImpl::remove_home (Components::CCMHome_ptr href)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	// Find the home in our list of installed homes
	std::vector <HomeEntry>::iterator homes_iter;

	for (homes_iter = installed_homes_.begin(); homes_iter != installed_homes_.end(); homes_iter++)
	{
		Components::CCMHome_var home_ref = (*homes_iter).home_servant_->ref();

		if (home_ref->_is_equivalent (href))
		{
			DEBUG_OUT ("ContainerInterfaceImpl: remove_home(): Home servant found");
			break;
		}
	}

	if (homes_iter == installed_homes_.end())
	{
		throw Components::RemoveFailure();
	}

	Qedo::HomeServantBase* home_servant = (*homes_iter).home_servant_;

	home_servant->prepare_remove();

	installed_homes_.erase (homes_iter);
}


Components::CCMHomes* 
ContainerInterfaceImpl::get_homes()
throw (CORBA::SystemException)
{
	Components::CCMHomes_var homes = new Components::CCMHomes();
	homes->length (installed_homes_.size());

	for (unsigned int i = 0; i < installed_homes_.size(); i++)
	{
        homes[i] = installed_homes_[i].home_servant_->ref();
	}

	return homes._retn();
}


void 
ContainerInterfaceImpl::remove()
throw (Components::RemoveFailure, CORBA::SystemException)
{
	throw Components::RemoveFailure();
}

} // namespace Qedo

