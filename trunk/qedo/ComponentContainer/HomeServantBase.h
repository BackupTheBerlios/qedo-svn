/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#ifndef __HOME_SERVANT_BASE_H__
#define __HOME_SERVANT_BASE_H__

#include <CORBA.h>
#include "Components.h"
#include "CCMContext.h"
#include "ComponentInstance.h"
#include "ServantBase.h"
#include "ServantLocator.h"
#include "ServantRegistry.h"
#include "Util.h"
#include <vector>


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class ComponentInstance;
class CCMContext;
class ContainerInterfaceImpl;
class ServantRegistry;


/**
 * base for all home servants
 */
class CONTAINERDLL_API HomeServantBase : public PortableServer::RefCountServantBase
{
	/** makes use of this */
	friend class ContainerInterfaceImpl;
	friend class PrimaryServant;
	/** access container */
	friend class ServantLocator;
	/** needs access to install_dir_ */
	friend class InternalConfiguration;

#ifndef _QEDO_NO_QOS
	/** to access the servant_locator */
	friend class ExtensionContext;
	friend class CCMContext;

	friend class ServerInterceptorDispatcher;
#endif

private:
	/** poa manager */
	PortableServer::POAManager_var	home_poa_manager_;
	/** home servant */
	PortableServer::Servant			my_home_servant_;
	/** object id */
	PortableServer::ObjectId_var	my_object_id_;

	/** home reference */
	Components::CCMHome_var			my_home_ref_;
	/** repository id of the home */
	CORBA::String_var				repository_id_;
	/** repository id of the component */
	CORBA::String_var				comp_repository_id_;

	/** the container interface where the home is installed in */
	ContainerInterfaceImpl*			container_;
	/** the installation directory */
	std::string						install_dir_;

	/** the name of the service if the homes components implement a container service */
	std::string						service_name_;

	/** the servant locator for the homes components */
	ServantLocator*					servant_locator_;

	/** This counter will be part of any object reference created by this home */
	CORBA::ULong instance_counter_;

	/**
	 * create an object reference for the component
	 * creates an object reference for the primary interface and for home interfaces.
	 * Facets and event consumers must use create_object_reference()
	 * \param rep_id The repository id of the component.
	 */
	CORBA::Object_ptr create_primary_object_reference (const char* rep_id);

	//
	// These are the virtual functions that should be implemented by each container type
	//

	/**
	 * called before the component instance is removed from a home via CCMHome::remove_component or destruction of the home
	 */
	virtual void before_remove_component (Components::ExecutorLocator_ptr) = 0;

	/**
	 * This function is called in the final stage of finalize_component_incarnation
	 */
	virtual void do_finalize_component_incarnation (Components::ExecutorLocator_ptr) = 0;

	/**
	 * set the name of the service the components implement (only if installed as service home)
	 * \param name The name of the service.
	 */
	void service(const char* name);


protected:
	/** poa */
	PortableServer::POA_var						home_poa_;
	/** home executor */
	Components::HomeExecutorBase_var			home_executor_;
	/** servant registry */
	Qedo::ServantRegistry*						servant_registry_;

	/** list of component instances */
	std::vector <Qedo::ComponentInstance>		component_instances_;
	/** the mutex for component_instances_ */
	QedoMutex									component_instances_mutex_;

	/**
	 * create an object reference
	 * This function creates an object reference and is used by create_primary_object_reference()
	 * \param qedo_key The qedo internal key.
	 * \param rep_id The repository id.
	 */
	CORBA::Object_ptr HomeServantBase::create_object_reference (const CORBA::OctetSeq* qedo_key, const char* rep_id);

	/**
	 * start component incarnation
	 * \param executor_locator The executor locator of the component instance.
	 * \param ccm_context The context of the component instance
	 * \return The component instance.
	 */
	ComponentInstance& incarnate_component (Components::ExecutorLocator_ptr executor_locator, 
											CCMContext* ccm_context);

	/**
	 * start component incarnation
	 * \param executor_locator The executor locator of the component instance.
	 * \param ccm_context The context of the component instance
	 * \param cfg The configuration values.
	 * \return The component instance.
	 */
	ComponentInstance& incarnate_component (Components::ExecutorLocator_ptr executor_locator, 
											CCMContext* ccm_context,
											const Components::ConfigValues& config);
	
	/**
	 * finalize the component incarnation
	 * \param object_id The object id.
	 */
	void finalize_component_incarnation (const PortableServer::ObjectId& object_id);

public:
	/**
	 * constructor
	 * \param repository_id The repository id of the home.
	 * \param comp_repid The repository id of the component.
	 */
	HomeServantBase (const char* repository_id, const char* comp_repid);

	/**
	 * constructor
	 */
	HomeServantBase();

	/**
	 * copy constructor
	 */
	HomeServantBase (const HomeServantBase&);

	/**
	 * assignment operator
	 */
	HomeServantBase& operator= (const HomeServantBase&);

	/**
	 * destructor
	 */
	~HomeServantBase();

	/**
	 * initialize
	 * \param root_poa The root poa.
	 * \param home_executor The home executor of this home.
	 * \param container The container the home is installed in.
	 */
	void initialize (PortableServer::POA_ptr root_poa,
		             Components::HomeExecutorBase_ptr home_executor,
					 ContainerInterfaceImpl* container,
					 std::string install_dir)
		throw (Components::Deployment::InstallationFailure);

	/**
	 * provide the home
	 * provides the object reference of the home
	 * \return The object reference of the CCMHome.
	 */
	Components::CCMHome_ptr ref();

	// This is a helper function to implement our get_component()
	Components::CCMObject_ptr HomeServantBase::lookup_component (const PortableServer::ObjectId&);

	/**
	 * extract the object id from the given object reference
	 * \param obj The object reference.
	 * \return The object id.
	 */
	PortableServer::ObjectId* reference_to_oid (const CORBA::Object_ptr obj);

	/**
	 * remove object with certain object id
	 * removes the component insatnce with the given obejct id
	 * \param object_id The object id of the component instance to be removed.
	 */
	void remove_component_with_oid (const PortableServer::ObjectId& object_id);

	/**
	 * lookup servant for the given object id
	 * \param object_id The object id of the component instance.
	 * \return The servant for the component instance.
	 */
	PortableServer::Servant lookup_servant (const PortableServer::ObjectId& object_id);

	/**
	 * bla
	 */

	void prepare_remove();

	/**
	 * provides the repository id of the home
	 * \return The repository id of the home.
	 */
	const char* get_home_repid();

	/**
	 * provides the repository id of the component
	 * \return The repository id of the component.
	 */
	const char* get_component_repid();
};

/** @} */

} // namespace Qedo

#endif
