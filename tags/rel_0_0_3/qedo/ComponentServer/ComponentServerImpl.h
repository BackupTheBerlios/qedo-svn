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

#ifndef __COMPONENT_SERVER_IMPL_H__
#define __COMPONENT_SERVER_IMPL_H__

#include <OB/CORBA.h>
#include "QedoComponents_skel.h"
#include "Util.h"
#include <vector>

namespace Qedo {

typedef std::vector < Components::Deployment::Container_var > ContainerVector;

class ComponentServerImpl : public POA_Components::Deployment::ComponentServer,
							public PortableServer::RefCountServantBase
{
private:
	CORBA::String_var										csa_string_ref_;
	CORBA::ULong											process_id_;
	Qedo_Components::Deployment::ServerActivator_var		csa_ref_;
	Components::Deployment::ComponentInstallation_var		component_installer_;

	CORBA::ORB_var											orb_;
	PortableServer::POA_var									root_poa_;
	PortableServer::POAManager_var							root_poa_manager_;
	ContainerVector											containers_;

public:
	ComponentServerImpl (CORBA::ORB_ptr, const char*);
	~ComponentServerImpl();

	void initialize();

	//
    // IDL:omg.org/Components/Deployment/ComponentServer/configuration:1.0
    //
    Components::ConfigValues* configuration()
	 	throw (CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ComponentServer/get_server_activator:1.0
    //
    Components::Deployment::ServerActivator_ptr get_server_activator()
	 	throw (CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ComponentServer/create_container:1.0
    //
    Components::Deployment::Container_ptr create_container(const ::Components::ConfigValues& config)
		throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ComponentServer/remove_container:1.0
    //
    void remove_container(Components::Deployment::Container_ptr cref)
		throw (Components::RemoveFailure, CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ComponentServer/get_containers:1.0
    //
    Components::Deployment::Containers* get_containers()
	 	throw (CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ComponentServer/remove:1.0
    //
    void remove()
		throw (Components::RemoveFailure, CORBA::SystemException);

	// Exceptions
	class CannotInitialize {};
};

} // namespace Qedo

#endif
