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

#ifndef __COMPONENT_SERVER_ACTIVATOR_IMPL_H__
#define __COMPONENT_SERVER_ACTIVATOR_IMPL_H__

#include <vector>

#ifndef _WIN32
#include "HU_Container.h"
#endif
#include <OB/CORBA.h>
#include "QedoComponents_skel.h"
#ifdef HAVE_JTC
#include <JTC/JTC.h>
#endif

namespace Qedo {

typedef std::vector < Components::Deployment::ComponentServer_var > ComponentServerVector;

class ServerActivatorImpl : public POA_Qedo_Components::Deployment::ServerActivator,
							public PortableServer::RefCountServantBase
{
private:
	bool debug_mode_;
#ifdef HAVE_JTC
	JTCMonitor monitor;
#else
#ifdef _WIN32
	HANDLE event_handle_;
#else
#error Have no semaphore
#endif
#endif

	CORBA::ORB_var									orb_;
	PortableServer::POA_var							root_poa_;
	PortableServer::POAManager_var					root_poa_manager_;
	Components::Deployment::ComponentServer_var		last_created_component_server_;
	ComponentServerVector							component_servers_;

public:
	ServerActivatorImpl (CORBA::ORB_ptr, bool);
	~ServerActivatorImpl();

	void initialize();

	//
    // IDL:omg.org/Components/Deployment/ServerActivator/create_component_server:1.0
    //
    Components::Deployment::ComponentServer_ptr create_component_server (const ::Components::ConfigValues& config)
		throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ServerActivator/remove_component_server:1.0
    //
    void remove_component_server (::Components::Deployment::ComponentServer_ptr server)
		throw (Components::RemoveFailure, CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/ServerActivator/get_component_servers:1.0
    //
    Components::Deployment::ComponentServers* get_component_servers()
		throw (CORBA::SystemException);

	//
    // IDL:omg.org/HU_Components/Deployment/ServerActivator/notify_component_server:1.0
    //
    virtual void notify_component_server (Components::Deployment::ComponentServer_ptr server)
        throw(CORBA::SystemException);

	// Exceptions
	class CannotInitialize{};
};

} // namespace Qedo

#endif

