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


#include <CORBA.h>
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include "Components.h"
#include "Valuetypes.h"
#include "NameServiceBase.h"
#include <iostream>
#include <fstream>
#include <string>


namespace Qedo {


/**
 * @addtogroup Deployment Component Deployment Support
 * This is the Qedo deployment support for CORBA components.
 * The subdirectory Runtime/Deployment of the Qedo installation directory
 * contains all deployment related stuff. The XML file DeployedComponents.xml
 * contains information about all installed component implementations and is used
 * to keep those information persistent. The subdirectory ComponentPackages
 * contains the softpackages for component implementations and assemblies.
 * During component installation each component softpackage is unpacked into a temporary directory named by the
 * UUID of the installed component implementation. These directories are created
 * in the Runtime/ComponentImplementations subdirectory. If no servant code is enclosed 
 * it will be subsequently generated and also put into the Runtime/ComponentImplementations directory.
 * The makefiles in this directory are used therefore.
 *
 * In order to deploy an assembly, a zip file has to be created by the assembly
 * developer, containing an assembly descriptor, zip files for each component 
 * and probably property file descriptors for component instances. The component
 * zip files in turn contain a software package descriptor, the dynamic library
 * for the components business logic and the idl file for the servant code
 * generation.
 * @{
 */


/**
 * @defgroup DeploymentClient Generic Client for Deployment
 * The deployment client is used to deploy an assembly package to the qedo platform.
 * @{
 */


/**
 * deploys an assembly package
 */
class DeploymentClient : public virtual NameServiceBase
{
private:
	/** the orb */
	CORBA::ORB_var									orb_;
	/** the root poa */
	PortableServer::POA_var							root_poa_;
	/** the root poa manager */
	PortableServer::POAManager_var					root_poa_manager_;
	/** the assembly factory to be used */
	Components::Deployment::AssemblyFactory_var		assemblyFactory_;

public:
	/**
	 * constructor
	 */
	DeploymentClient (CORBA::ORB_ptr);

	/**
	 * destructor
	 */
	~DeploymentClient();

	/**
	 * exception to indicate the initialization was not sucessful
	 */
	class CannotInitialize{};

	/**
	 * initialize the client
	 */
	void initialize() 
		throw (CannotInitialize);

	/**
	 * create an assembly
	 * \param packageName The name of the assembly package.
	 */
	void create(std::string uri);
};

/** @} */

/** @} */

}

