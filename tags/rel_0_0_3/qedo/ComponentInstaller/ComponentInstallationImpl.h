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

#ifndef __COMPONENT_INSTALLATION_IMPL_H__
#define __COMPONENT_INSTALLATION_IMPL_H__

#include <OB/CORBA.h>
#include "QedoComponents_skel.h"
#include "ComponentImplementation.h"
#include "NameServiceBase.h"
#include "PlatformBase.h"
#include "DOMXMLParser.h"
#include <vector>


#define DEPLOYMENT_PERSISTENCE_FILE		"DeployedComponents.xml"


namespace Qedo {

class ComponentInstallationImpl : public POA_Qedo_Components::Deployment::ComponentInstallation,
								  public PortableServer::RefCountServantBase,
								  public virtual NameServiceBase,
								  public virtual PlatformBase
{
private:
	std::vector < ComponentImplementation > installed_components_;

	CORBA::ORB_var					orb_;
	PortableServer::POA_var			root_poa_;
	PortableServer::POAManager_var	root_poa_manager_;
	std::string						packageDirectory_;
	std::string						installationDirectory_;

	bool readInstalledComponents (const char* inst_file);
	bool addInstalledComponent (ComponentImplementation* aComponentImplementation);

public:
	ComponentInstallationImpl (CORBA::ORB_ptr);
	~ComponentInstallationImpl();

	void initialize();

	//
    // IDL:omg.org/Components/Deployment/ComponentInstallation/install:1.0
    //
    void install (const char* implUUID, const char* component_loc)
        throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure);

    //
    // IDL:omg.org/Components/Deployment/ComponentInstallation/replace:1.0
    //
    void replace (const char* implUUID, const char* component_loc)
        throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure);

    //
    // IDL:omg.org/Components/Deployment/ComponentInstallation/remove:1.0
    //
    void remove (const char* implUUID)
        throw (Components::Deployment::UnknownImplId, Components::RemoveFailure);

    //
    // IDL:omg.org/Components/Deployment/ComponentInstallation/get_implementation:1.0
    //
	Components::Deployment::Location get_implementation (const char* implUUID)
        throw (Components::Deployment::UnknownImplId, Components::Deployment::InstallationFailure);

    //
    // IDL:omg.org/Components/Deployment/ComponentInstallation/upload:1.0
    //
    char* upload (const char* implUUID, const ::CORBA::OctetSeq& package)
        throw (Components::Deployment::InstallationFailure);

	// Exceptions
	class CannotInitialize {};
};

} // namespace Qedo

#endif

