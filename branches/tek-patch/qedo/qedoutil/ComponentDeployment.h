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


#ifndef __COMPONENT_DEPLOYMENT_H__
#define __COMPONENT_DEPLOYMENT_H__


#include "qedoutil.h"
#include <CORBA.h>
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
 * deploys an assembly package
 */
class QEDOUTIL_API ComponentDeployment : public virtual NameServiceBase
{
public:

	/**
	 * exception to indicate the deployment was not sucessful
	 */
	class DeploymentFailure{};

private:

	/** the assembly package */
	std::string										uri_;
	/** the naming service */
	CosNaming::NamingContext_var					ns_;
	/** the assembly factory to be used */
	Components::Deployment::AssemblyFactory_var		assemblyFactory_;
	/** the assembly */
	Components::Deployment::Assembly_var			assembly_;
	/** the cookie */
	Components::Cookie*								cookie_;

	/**
	 * initialise
	 */
	void init() 
		throw (DeploymentFailure);

public:
	/**
	 * constructor
	 * \param uri The uri of the assembly package.
	 */
	ComponentDeployment(std::string uri);

	/**
	 * destructor
	 */
	~ComponentDeployment();

	/**
	 * deploy the assembly
	 */
	void deploy() 
		throw (DeploymentFailure);

	/**
	 * undeploy the assembly
	 */
	void undeploy() 
		throw (DeploymentFailure);
};

/** @} */

}

#endif


