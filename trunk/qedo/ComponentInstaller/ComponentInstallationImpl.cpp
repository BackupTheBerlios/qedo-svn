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
#include "Output.h"
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#else
#include <unistd.h>
#endif


static char rcsid[] UNUSED = "$Id: ComponentInstallationImpl.cpp,v 1.20 2003/10/23 09:50:36 neubauer Exp $";


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
		NORMAL_ERR( "ComponentInstallationImpl: no root POA available" );
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR( "ComponentInstallationImpl: cannot narrow root POA" );
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
		NORMAL_ERR( "ComponentInstallationImpl: Cannot determine my hostname" );
		throw CannotInitialize();
	}
    name.append(hostname);
    if ( !registerName(name, my_ref, true))
    {
        throw CannotInitialize();
    }

	DEBUG_OUT2( "ComponentInstallationImpl: bound under ", name );

	//
	// deployment directory
	//
	if (makeDir(g_qedo_dir + "/deployment"))
	{
		NORMAL_ERR( "ComponentInstallationImpl: deployment directory can not be created" );
		throw CannotInitialize();
	}

	//
	// directory to put the component packages
	//
	packageDirectory_ = g_qedo_dir + "/deployment/packages";
	if (makeDir(packageDirectory_))
	{
		NORMAL_ERR( "ComponentInstallationImpl: componentPackages directory can not be created" );
		throw CannotInitialize();
	}

	//
	// directory to put the component implementations
	//
	installationDirectory_ = g_qedo_dir + "/deployment/components";
	if (makeDir(installationDirectory_))
	{
		NORMAL_ERR( "ComponentInstallationImpl: componentImplementations directory can not be created" );
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
			ComponentImplementation impl( *iter, "", nameService_ );
			impl.installation_count_ = 1;
			installed_components_.push_back( impl );
		}
	}
	catch(InstallationReadException)
	{
		throw CannotInitialize();
	}

	DEBUG_OUT2( "ComponentInstallationImpl: number of already installed components: ", installed_components_.size() );
}


void 
ComponentInstallationImpl::install
(const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
	DEBUG_OUT2( "ComponentInstallationImpl: installing ", implUUID );

	//
	// exclusive operation
	//
	QedoLock lock(&mutex_);

	//
	// already installed ?
	//
	ComponentImplementation *impl = 0;
	std::vector < ComponentImplementation >::iterator iter;
	for(iter = installed_components_.begin();
		iter != installed_components_.end();
		iter++)
	{
		if ((*iter).data_.uuid == implUUID)
		{
			impl = &(*iter);
			break;
		}
	}

	//
	// component_loc contains PACKAGE location ?
	//
	std::string::size_type pos;
	std::string desc = component_loc;
	if( !impl && !desc.compare(0, 8, "PACKAGE=") )
	{
		//
		// check whether the package exists
		//
		std::string comp_loc = packageDirectory_ + "/" + desc.substr(8);
		if (!checkExistence(comp_loc, IS_FILE))
		{
			DEBUG_OUT3( "ComponentInstallationImpl: package for ", implUUID, " has to be uploaded" );
			throw Components::Deployment::InvalidLocation();
		}

		//
		// create new implementation
		//
		ComponentImplementationData data;
		data.uuid = implUUID;
		data.installation_dir = getPath(installationDirectory_) + implUUID;
		impl = new ComponentImplementation(data, comp_loc, nameService_);
	}

	//
	// component_loc contains local code location
	//
	if( !impl )
	{
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			NORMAL_ERR( "ComponentInstallationImpl: cannot extract servant module name" );
			throw Components::Deployment::InvalidLocation();
		}
		std::string servant_module = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			NORMAL_ERR( "ComponentInstallationImpl: cannot extract servant entry point" );
			throw Components::Deployment::InvalidLocation();
		}
		std::string servant_entry_point = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			NORMAL_ERR( "ComponentInstallationImpl: cannot extract executor module name" );
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
		data.installation_dir = getPath(installationDirectory_) + implUUID;
		data.servant_module = servant_module;
		data.servant_entry_point = servant_entry_point;
		data.executor_module = executor_module;
		data.executor_entry_point = executor_entry_point;
		impl = new ComponentImplementation( data, "", nameService_ );

		//
		// create directory for the component implementation
		//
		makeDir( data.installation_dir );
		copyFile( servant_module, getPath(data.installation_dir) + servant_module );
		copyFile( executor_module, getPath(data.installation_dir) + executor_module );
	}

	if( !impl )
	{
		throw Components::Deployment::InstallationFailure();
	}

	//
	// install
	//
	try
	{
		impl->install();
	}
	catch( Components::CreateFailure )
	{
		NORMAL_ERR( "ComponentInstallationImpl: installation error" );
		throw Components::Deployment::InstallationFailure();
	}

	//
	// register
	//
	if( impl->installation_count_ == 1 )
	{
		installed_components_.push_back( *impl );
		reader_.add( inst_file_, &(impl->getData()) );
		delete impl;
	}

	DEBUG_OUT3( "ComponentInstallationImpl: ", implUUID, "installed" );
}


void 
ComponentInstallationImpl::replace (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
	DEBUG_OUT2( "ComponentInstallationImpl: replace ", implUUID );
	
	//
	// exclusive operation
	//
	QedoLock lock(&mutex_);

	throw Components::Deployment::InstallationFailure();
}


void 
ComponentInstallationImpl::remove (const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::RemoveFailure)
{
	DEBUG_OUT2( "ComponentInstallationImpl: remove ", implUUID );

	//
	// exclusive operation
	//
	QedoLock lock(&mutex_);

	std::vector < ComponentImplementation >::iterator iter;
	for(iter = installed_components_.begin();
		iter != installed_components_.end();
		iter++)
	{
		if ((*iter).data_.uuid == implUUID)
		{
			//
			// uninstall
			//
			try 
			{ 
				(*iter).uninstall();
				
				if( (*iter).installation_count_ == 0 )
				{
					installed_components_.erase( iter );
					reader_.remove( inst_file_, implUUID );
				}
			}
			catch( Components::RemoveFailure ) 
			{ 
				NORMAL_ERR2( "ComponentInstallationImpl: remove failure for ", implUUID );
				throw Components::RemoveFailure(); 
			}

			return;
		}
	}

	NORMAL_ERR3( "ComponentInstallationImpl: ", implUUID, " not installed" );
	throw Components::Deployment::UnknownImplId();
}


Components::Deployment::Location
ComponentInstallationImpl::get_implementation(const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::Deployment::InstallationFailure)
{
	DEBUG_OUT2( "ComponentInstallationImpl: get_implementation for ", implUUID );
	
	//
	// exclusive operation
	//
	QedoLock lock(&mutex_);

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
	DEBUG_OUT2( "ComponentInstallationImpl: uploading package for ", implUUID );

	//
	// exclusive operation
	//
	QedoLock lock(&mutex_);

	std::string name(implUUID);
	std::string file = packageDirectory_ + "/" + name + ".zip";

	//
	// save to disk
	//
	std::ofstream ofs(file.c_str(), std::ios::binary|std::ios::out);
    if (!ofs)
    {
		NORMAL_ERR3( "ComponentInstallationImpl: package for ", name, " can not be locally saved" );
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
