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

#ifndef __COMPONENT_INSTALLATION_IMPL_H__
#define __COMPONENT_INSTALLATION_IMPL_H__

#include <CORBA.h>
#include "QedoComponents_skel.h"
#include "Synchronisation.h"
#include "ComponentImplementation.h"
#include "NameServiceBase.h"
#include "PlatformBase.h"
#include "InstallationReader.h"
#include <vector>


namespace Qedo {


/**
 * @addtogroup ComponentInstaller
 * @{
 */


extern std::string g_qedo_dir;


/**
 * implementation of Components::Deployment::ComponentInstallation
 */
class ComponentInstallationImpl : public POA_Qedo_Components::Deployment::ComponentInstallation,
								  public PortableServer::RefCountServantBase,
								  public virtual NameServiceBase,
								  public virtual PlatformBase
{
private:

	/** the orb */
	CORBA::ORB_var							orb_;
	/** the root poa */
	PortableServer::POA_var					root_poa_;
	/** the root poa manager */
	PortableServer::POAManager_var			root_poa_manager_;
	/** the package directory */
	std::string								packageDirectory_;
	/** the installation directory */
	std::string								installationDirectory_;
	/** the deployment directory */
	std::string								deployment_dir_;
	/** the installation xml file */
	static std::string						inst_file_;
	/** */
	InstallationReader						reader_;
	/** list of installed components */
	std::vector < ComponentImplementation > installed_components_;
	/** mutex for installed_components_ */
	QedoMutex								installed_components_mutex_;

public:
	/**
	 * constructor
	 */
	ComponentInstallationImpl (CORBA::ORB_ptr);

	/**
	 * destructor
	 */
	~ComponentInstallationImpl();

	/**
	 * initialize the server
	 */
	void initialize();

	/**
     * implements IDL:omg.org/Components/Deployment/ComponentInstallation/install:1.0
	 * \param implUUID The uuid of the implementation.
	 * \param component_loc The Location of the component implementation.
	 * There are two formats for component_loc: 
	 * 1) "PACKAGE=<packagename>" determining the package id for an uploaded zip package
	 * 2) "<servant_module>;<servant_entry_point>;<executor_module>;<executor_entry_point>"
	 *    where servant_module denotes the servant library, servant_entry_point denotes
	 *    the entry point of the servant library, executor_module denotes the executor library,
	 *    executor_entry_point denotes the entry point for the executor library
     */
    void install (const char* implUUID, const char* component_loc)
        throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentInstallation/replace:1.0
     */
    void replace (const char* implUUID, const char* component_loc)
        throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentInstallation/remove:1.0
     */
    void remove (const char* implUUID)
        throw (Components::Deployment::UnknownImplId, Components::RemoveFailure);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentInstallation/get_implementation:1.0
     */
	Components::Deployment::Location get_implementation (const char* implUUID)
        throw (Components::Deployment::UnknownImplId, Components::Deployment::InstallationFailure);

    /**
     * implements IDL:Qedo_Components/Deployment/ComponentInstallation/upload:1.0
     */
    char* upload (const char* implUUID, const ::CORBA::OctetSeq& package)
        throw (Components::Deployment::InstallationFailure);

	//
	// Exceptions
	//

	class CannotInitialize {};
};

/** @} */

} // namespace Qedo

#endif

