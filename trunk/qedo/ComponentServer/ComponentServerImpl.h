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

#ifndef __COMPONENT_SERVER_IMPL_H__
#define __COMPONENT_SERVER_IMPL_H__

#include <CORBA.h>
#include "QedoComponents_skel.h"
#include "ContainerInterfaceImpl.h"
#include "Util.h"
#include <vector>


namespace Qedo {


/**
 * @addtogroup Deployment Component Deployment Support
 * @{
 */


/**
 * @defgroup ComponentServer Component Server
 * The component server is created by the component server activator and used to create containers.
 * @{
 */


class ValuetypeEntry
{
public:
	long						count;
	std::string					repid;
	std::string					code;
	/** handle of the dynamic library */
#ifdef _WIN32
	HINSTANCE					dll;
#else
	void*						dll;
#endif
};


class ContainerEntry
{
public:
	ContainerInterfaceImpl* container_;

	ContainerEntry (ContainerInterfaceImpl*);

	ContainerEntry();
	
	ContainerEntry (const ContainerEntry&);

	ContainerEntry& operator= (const ContainerEntry&);

	~ContainerEntry();
};


typedef std::vector < ContainerEntry > ContainerVector;


/**
 * the server for containers
 */
class ComponentServerImpl : public virtual POA_Qedo_Components::Deployment::ComponentServer,
							public virtual PortableServer::RefCountServantBase,
							public virtual CreateDestructCORBAObjectCounter
{
private:
	/** the stringified object reference of the server activator */
	CORBA::String_var										csa_string_ref_;
	/** the object reference of the server activator */
	Qedo_Components::Deployment::ServerActivator_var		csa_ref_;
	/** the process id */
	CORBA::ULong											process_id_;
	/** the object reference of the component installer */
	Components::Deployment::ComponentInstallation_var		component_installer_;

	/** the orb */
	CORBA::ORB_var											orb_;
	/** the root poa */
	PortableServer::POA_var									root_poa_;
	/** the root poa manager */
	PortableServer::POAManager_var							root_poa_manager_;
	/** the list of created containers */
	ContainerVector											containers_;
	/** the slot id where our interceptor stores information to be used by container services */
	PortableInterceptor::SlotId								slot_id_;
	/** the list of valuetype implementations */
	std::vector < ValuetypeEntry >							valuetypes_;
	/** the mutex for the container list */
	QedoMutex												container_mutex_;
	/** the mutex for the valuetype implementation list */
	QedoMutex												value_mutex_;

public:
	/**
	 * constructor
	 */
	ComponentServerImpl (CORBA::ORB_ptr, const char*, PortableInterceptor::SlotId);

	/**
	 * destructor
	 */
	~ComponentServerImpl();

	/**
	 * initialize the server
	 */
	void initialize();

	/**
     * implements IDL:omg.org/Components/Deployment/ComponentServer/configuration:1.0
     */
    Components::ConfigValues* configuration()
	 	throw (CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentServer/get_server_activator:1.0
     */
    Components::Deployment::ServerActivator_ptr get_server_activator()
	 	throw (CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentServer/create_container:1.0
     */
    Components::Deployment::Container_ptr create_container(const ::Components::ConfigValues& config)
		throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentServer/remove_container:1.0
     */
    void remove_container(Components::Deployment::Container_ptr cref)
		throw (Components::RemoveFailure, CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentServer/get_containers:1.0
     */
    Components::Deployment::Containers* get_containers()
	 	throw (CORBA::SystemException);

    /**
     * implements IDL:omg.org/Components/Deployment/ComponentServer/remove:1.0
     */
    void remove()
		throw (Components::RemoveFailure, CORBA::SystemException);

	/**
	 * implements IDL:Qedo_Components/Deployment/ComponentServer/loadValuetypeFactory:1.0
	 * load the required valuetype factory if not already done
	 */
	void loadValuetypeFactory(const char* repid, const char* loc)
		throw (CORBA::SystemException);

	//
	// Exceptions
	//

	class CannotInitialize {};
};

/** @} */

/** @} */

} // namespace Qedo

#endif
