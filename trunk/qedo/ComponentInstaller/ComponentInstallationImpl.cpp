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

#include "ComponentInstallationImpl.h"
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#else
#include <unistd.h>
#endif


static char rcsid[] UNUSED = "$Id: ComponentInstallationImpl.cpp,v 1.19 2003/10/05 18:48:38 tom Exp $";


namespace Qedo {


std::string	ComponentInstallationImpl::inst_file_;


ComponentInstallationImpl::ComponentInstallationImpl (CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
	if (inst_file_.empty())
	{
		inst_file_ = g_qedo_dir + "/deployment/installedComponentImplementations.xml";
	}
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

	// get NameService
    if ( !initNameService(orb_))
    {
        throw CannotInitialize();
    }

	// bind in NameService
	CORBA::Object_var my_ref = this->_this();
    std::string name = "Qedo/ComponentInstallation/";
    char hostname[256];
	if (gethostname (hostname, 256))
	{
		std::cerr << "ComponentInstallationImpl: Cannot determine my hostname" << std::endl;
		throw CannotInitialize();
	}
    name.append(hostname);
    if ( !registerName(name, my_ref, true))
    {
        throw CannotInitialize();
    }

	std::cout << "..... bound under " << name << std::endl;

	//
	// deployment directory
	//
	if (makeDir(g_qedo_dir + "/deployment"))
	{
		std::cerr << "deployment directory can not be created" << std::endl;
		throw CannotInitialize();
	}

	//
	// directory to put the component packages
	//
	packageDirectory_ = g_qedo_dir + "/deployment/packages";
	if (makeDir(packageDirectory_))
	{
		std::cerr << "componentPackages directory can not be created" << std::endl;
		throw CannotInitialize();
	}

	//
	// directory to put the component implementations
	//
	installationDirectory_ = g_qedo_dir + "/deployment/components";
	if (makeDir(installationDirectory_))
	{
		std::cerr << "componentImplementations directory can not be created" << std::endl;
		throw CannotInitialize();
	}

	//
	// read information about deployed components
	//
	ComponentImplementationDataVector data;
	try
	{
		reader_.read( inst_file_, &data );
		ComponentImplementationDataVector::const_iterator iter;
		for(iter = data.begin();
			iter != data.end();
			iter++)
		{
			ComponentImplementation impl( *iter, nameService_ );
			installed_components_.push_back( impl );
		}
	}
	catch(InstallationReadException)
	{
		throw CannotInitialize();
	}

	std::cout << "..... number of already installed components: " << installed_components_.size() << std::endl;
	std::cout << std::endl;
}


void 
ComponentInstallationImpl::install (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
	//
	// The description may have 2 forms:
	//
	// 1) servant_module:servant_entry_point:executor_module:executor_entry_point
	// 2) PACKAGE=<packagename>
	//

	std::cout << "..... installing Component type with UUID: " << implUUID << std::endl;

	//
	// test if already installed
	//
	std::vector < ComponentImplementation >::const_iterator inst_iter;
	for (inst_iter = installed_components_.begin();
		inst_iter != installed_components_.end();
		inst_iter++)
	{
		if ((*inst_iter).data_.uuid == implUUID)
		{
			std::cout << ".......... already installed !" << std::endl;
			return;
		}
	}

	//
	// component_loc contains PACKAGE location
	//
	std::string::size_type pos;
	std::string desc = component_loc;
	if( !desc.compare(0, 8, "PACKAGE="))
	{
		//
		// check whether the package exists
		//
		std::string comp_loc = packageDirectory_ + "/" + desc.substr(8);
		if (!checkExistence(comp_loc, IS_FILE))
		{
			std::cerr << ".......... package for " << implUUID << " has to be uploaded" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}

		//
		// create new implementation
		//
		ComponentImplementationData data;
		data.uuid = implUUID;
		ComponentImplementation newComponentImplementation(data, installationDirectory_, comp_loc, nameService_);

		try
		{
			newComponentImplementation.install();
			data = newComponentImplementation.getData();
		}
		catch( Components::CreateFailure )
		{
			std::cerr << "!!!!! installation error" << std::endl;
			throw Components::Deployment::InstallationFailure();
		}
		
		// register component
		installed_components_.push_back(newComponentImplementation);
		reader_.add( inst_file_, &data );
	}
	//
	// component_loc contains local code location
	//
	else
	{
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			std::cerr << "ComponentInstallationImpl: Cannot extract servant module name" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}
		std::string servant_module = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			std::cerr << "ComponentInstallationImpl: Cannot extract servant entry point" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}
		std::string servant_entry_point = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			std::cerr << "ComponentInstallationImpl: Cannot extract executor module name" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}
		std::string executor_module = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		std::string executor_entry_point = desc;

		//
		// create new implementation
		//
		ComponentImplementationData data;
		data.uuid = implUUID;
		data.servant_module = servant_module;
		data.servant_entry_point = servant_entry_point;
		data.executor_module = executor_module;
		data.executor_entry_point = executor_entry_point;
		ComponentImplementation newComponentImplementation( data, nameService_ );
		installed_components_.push_back ( newComponentImplementation );
		reader_.add( inst_file_, &data );
	}

	std::cout << "..... done (" << implUUID << ")" << std::endl;
}


void 
ComponentInstallationImpl::replace (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
	std::cout << "..... replace Component type with UUID: " << implUUID << std::endl;
	// todo

	throw Components::Deployment::InstallationFailure();
}


void 
ComponentInstallationImpl::remove (const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::RemoveFailure)
{
	std::cout << "..... remove Component type with UUID: " << implUUID << std::endl;
	ComponentImplementation* impl = 0;

	//
	// first test for UUID
	//
	std::vector < ComponentImplementation >::iterator iter;
	for (iter = installed_components_.begin();
		iter != installed_components_.end();
		iter++)
	{
		if ((*iter).data_.uuid == implUUID)
		{
			impl = &(*iter);
			break;
		}
	}
	if(! impl)
	{
		std::cout << ".......... " << implUUID << " not installed !" << std::endl;
		throw Components::Deployment::UnknownImplId();
	}

	//
	// uninstall
	//
	try
	{
		impl->uninstall();
	}
	catch( Components::RemoveFailure )
	{
        throw Components::RemoveFailure();
	}
}


Components::Deployment::Location
ComponentInstallationImpl::get_implementation(const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::Deployment::InstallationFailure)
{
    std::cout << "..... get_implementation for " << implUUID << std::endl;
	
	//
	// Scan through the installed components
	//
	std::vector < ComponentImplementation >::const_iterator iter;
	for(iter = installed_components_.begin();
		iter != installed_components_.end();
		iter++)
	{
		if ((*iter).data_.uuid == implUUID)
		{
			// component installation dir
			std::string description = (*iter).data_.installation_dir + ";";

			// component code
			description += (*iter).data_.servant_module + ";";
			description += (*iter).data_.servant_entry_point + ";";
			description += (*iter).data_.executor_module + ";";
			description += (*iter).data_.executor_entry_point + ";";

			// valuetypes
			std::vector < ValuetypeData > ::const_iterator val_iter;
			for(val_iter = (*iter).data_.valuetypes.begin();
				val_iter != (*iter).data_.valuetypes.end();
				val_iter++)
			{
				description += (*val_iter).repid + ";" + (*val_iter).location.file + ";";
			}

			return CORBA::string_dup (description.c_str());
		}
	}

	throw Components::Deployment::UnknownImplId();
}


char* 
ComponentInstallationImpl::upload (const char* implUUID, const ::CORBA::OctetSeq& package)
throw (Components::Deployment::InstallationFailure)
{
	std::cout << "..... uploading package for UUID " << implUUID << std::endl;

	std::string name(implUUID);
	std::string file = packageDirectory_ + "/" + name + ".zip";

	//
	// save to disk
	//
	std::ofstream ofs(file.c_str(), std::ios::binary|std::ios::out);
    if (!ofs)
    {
		std::cerr << "Package for " << name << " can not be locally saved !!!" << std::endl;
        throw Components::Deployment::InstallationFailure();
    }
    const CORBA::Octet* it = package.get_buffer();
    ofs.write((char*)it, package.length());
    ofs.close();

	//
	// ensure the file is stored
	//
#ifdef _WIN32
	Sleep(1000);
#else
  sleep(1);
#endif

	std::string loc = std::string("PACKAGE=") + name + ".zip";
    return CORBA::string_dup(loc.c_str());
}


} // namespace Qedo
