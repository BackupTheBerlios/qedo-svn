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

#ifndef __COMPONENT_SERVER_ACTIVATOR_IMPL_H__
#define __COMPONENT_SERVER_ACTIVATOR_IMPL_H__


#include <CORBA.h>
#include <vector>
#include "QedoComponents_skel.h"
#include "Synchronisation.h"


namespace Qedo {


/**
 * @addtogroup Deployment Component Deployment Support
 * @{
 */


/**
 * @defgroup ServerActivator Component Server Activator
 * When starting the server activator executable the ServerActivator implementations starts and registers in the NameService
 * under Qedo/<host name>/ServerActivator.
 * @{
 */


typedef std::vector < Components::Deployment::ComponentServer_var > ComponentServerVector;


/**
 * the implementation of the ServerActivator interface
 */
class ServerActivatorImpl : public POA_Qedo_Components::Deployment::ServerActivator,
							public PortableServer::RefCountServantBase
{
private:
	/** debug mode */
	bool debug_mode_;

	/** qos-enabled mode */
	bool enable_qos_;

	/** for syncronization */
	qedo_cond component_server_activation;

	/** the orb */
	CORBA::ORB_var									orb_;
	/** the root poa */
	PortableServer::POA_var							root_poa_;
	/** the root poa manager */
	PortableServer::POAManager_var					root_poa_manager_;
	/** the last created component server */
	Components::Deployment::ComponentServer_var		last_created_component_server_;
	/** the list of all created component servers */
	ComponentServerVector							component_servers_;

public:
	/**
	 * constructor
	 */
	ServerActivatorImpl (CORBA::ORB_ptr, bool, bool);

	/**
	 * destructor
	 */
	~ServerActivatorImpl();

	/**
	 * initialize the server
	 */
	void initialize();

	/**
     * implements IDL:omg.org/Components/Deployment/ServerActivator/create_component_server:1.0
     */
    Components::Deployment::ComponentServer_ptr create_component_server (const ::Components::ConfigValues& config)
		throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ServerActivator/remove_component_server:1.0
     */
    void remove_component_server (::Components::Deployment::ComponentServer_ptr server)
		throw (Components::RemoveFailure, CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ServerActivator/get_component_servers:1.0
     */
    Components::Deployment::ComponentServers* get_component_servers()
		throw (CORBA::SystemException);

	/**
     * implements IDL:omg.org/HU_Components/Deployment/ServerActivator/notify_component_server:1.0
     */
    virtual void notify_component_server (Components::Deployment::ComponentServer_ptr server)
        throw(CORBA::SystemException);

	/**
	 * exception to indicate the initialization was not sucessful
	 */
	class CannotInitialize{};
};

/** @} */

/** @} */

} // namespace Qedo

#endif

