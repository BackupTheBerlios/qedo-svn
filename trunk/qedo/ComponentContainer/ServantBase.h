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

#ifndef __SERVANT_BASE_H__
#define __SERVANT_BASE_H__

#include <CORBA.h>
#include "Components_skel.h"
#include "CCMObjectExecutor.h"
#include "ComponentInstance.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class ComponentInstance;


/**
 * base class for all servants
 */
class CONTAINERDLL_API ServantBase : public virtual PortableServer::RefCountServantBase,
									 public virtual CreateDestructCORBAObjectCounter
{
	/** needs access to executor_locator and ccm_object_executor */
	friend class ServantLocator;
	/** to set the instance */
	friend class HomeServantBase;

protected:
	/** the executor locator of the component instance */
	Components::ExecutorLocator_var		executor_locator_;
	/** the generic ccm object executor for the component instance */
	CCMObjectExecutor*					ccm_object_executor_;
#ifndef _QEDO_NO_STREAMS
        /** the generic stream ccm object executor for the component instance */
        StreamCCMObjectExecutor*                        stream_ccm_object_executor_;
#endif
	/** the current executor*/
	CORBA::Object_ptr					current_executor_;

#ifndef _QEDO_NO_QOS
	Components::Extension::ServantInterceptorRegistration_var servant_interceptor_registry_ ;
#endif

public:
	/**
	 * constructor
	 */
	ServantBase();

	/**
	 * copy constructor
	 */
	ServantBase (const ServantBase&);

	/**
	 * assignment operator
	 */
	ServantBase& operator= (const ServantBase&);

	/**
	 * destructor
	 */
	~ServantBase();

	/**
	 * set the current executor
	 * \param cur_exec The executor.
	 */
	void current_executor (CORBA::Object_ptr cur_exec);

	/**
	 * set the component instance
	 * \param instance The component instance.
	 */
	void set_instance (Qedo::ComponentInstance& instance);

#ifndef _QEDO_NO_QOS
	void
	set_servant_dispatcher_registry(Components::Extension::ServantInterceptorRegistration_ptr reg);

#endif
};


/**
 * base class for all servants of the primary component interface (CCMObject)
 *
 * This class provides the implementation of generic operations.
 */
class CONTAINERDLL_API PrimaryServant : public virtual POA_Components::CCMObject,
										public ServantBase
{
public:
	/**
	 * constructor
	 */
	PrimaryServant();

	/**
	 * copy constructor
	 */
	PrimaryServant(const PrimaryServant&);

	/**
	 * assignment operator
	 */
	PrimaryServant& operator= (const PrimaryServant&);

	/**
	 * destructor
	 */
	~PrimaryServant();

private:
    //
    // from Navigation
    //

	/**
	 * implements IDL:omg.org/Components/Navigation/provide_facet:1.0
	 * provide the facet for the given name
	 * delegated to the object executor
	 * \param name The name of the facet.
	 * \return The reference of the facet.
	 */
    CORBA::Object_ptr provide_facet (const char* name)
      throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Navigation/get_all_facets:1.0
	 * provide the list of descriptions for all facets
	 * delegated to the object executor
	 * \return The list of descrtiption for all facets.
	 */
    Components::FacetDescriptions* get_all_facets()
      throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Navigation/get_named_facets:1.0
	 * provide the list of descriptions for those facets specified in the name list
	 * delegated to the object executor
	 * \param names The list of names for the facets.
	 * \return The list of descriptions of the facets.
	 */
    Components::FacetDescriptions*
    get_named_facets (const Components::NameList& names)
      throw (CORBA::SystemException, Components::InvalidName);

	/**
	 * implements IDL:omg.org/Components/Navigation/same_component:1.0
	 * decides whether the given reference belongs to this component
	 * delegated to the object executor
	 * \param ref The reference of a facet.
	 * \return True if the facet reference belongs to the component instance.
	 */
    CORBA::Boolean same_component (CORBA::Object_ptr ref)
      throw (CORBA::SystemException);

    //
    // from Receptacles
    //

	/**
	 * implements IDL:omg.org/Components/Receptacles/connect:1.0
	 * establish a connection on the named receptacle
	 * delegated to the object executor
	 * \param name The name of the receptacle port, the connection is made with.
	 * \param connection The reference to be connected with the receptacle.
	 * \return The cookie for identification of the connection.
	 */
    Components::Cookie* connect (const char* name, CORBA::Object_ptr connection)
		throw (Components::InvalidName, 
			   Components::InvalidConnection,
			   Components::AlreadyConnected,
			   Components::ExceededConnectionLimit,
			   CORBA::SystemException );

	/**
	 * implements IDL:omg.org/Components/Receptacles/disconnect:1.0
	 * disconnect a reference from a receptacle
	 * delegated to the object executor
	 * \param name The name of the receptacle port.
	 * \param ck The cookie of the connection to be disconnected.
	 */
    void disconnect (const char* name, Components::Cookie* ck)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   Components::CookieRequired,
			   Components::NoConnection,
			   CORBA::SystemException );

	/**
	 * implements IDL:omg.org/Components/Receptacles/get_connections:1.0
	 * provide the list of descriptions of all connections
	 * delegated to the object executor
	 * \param name The name of the receptacle port.
	 * \return The list of descriptions of the connections.
	 */
    Components::ConnectedDescriptions* get_connections (const char* name)
      throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Receptacles/get_all_receptacles:1.0
	 * provide the list of descriptions of all receptacles
	 * delegated to the object executor
	 * \return The list of descriptions of all receptacles.
	 */
    Components::ReceptacleDescriptions* get_all_receptacles()
      throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Receptacles/get_named_receptacles:1.0
	 * provide the list of descriptions for a list of receptacles
	 * delegated to the object executor
	 * \param names The list of names of the receptacles.
	 * \return The list of descriptions of the named receptacles.
	 */
    Components::ReceptacleDescriptions*
    get_named_receptacles (const ::Components::NameList& names)
      throw (Components::InvalidName );

    //
    // from Events
    //

	/**
	 * implements IDL:omg.org/Components/Events/get_consumer:1.0
	 * provide the reference of the given consumer port.
	 * delegated to the object executor
	 * \param sink_name The name of the consumer port.
	 * \return The reference of the consumer.
	 */
    Components::EventConsumerBase_ptr get_consumer (const char* sink_name)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/subscribe:1.0
	 * subscribe a consumer to a publisher
	 * delegated to the object executor
	 * \param publisher_name The name of the publisher.
	 * \param subscriber The consumer to be subscribed.
	 * \return The cookie of the consumer.
	 */
    Components::Cookie* subscribe (const char* publisher_name,
								   Components::EventConsumerBase_ptr subscriber)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/unsubscribe:1.0
	 * unsubscribe a consumer from a publisher
	 * delegated to the object executor
	 * \param publisher_name The name of the publisher.
	 * \param ck The cookie of the subscription.
	 */
    void unsubscribe (const char* publisher_name, Components::Cookie* ck)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/connect_consumer:1.0
	 * connect a consumer with an emitter
	 * delegated to the object executor
	 * \param emitter_name The name of the emitter.
	 * \param consumer The consumer to be connected.
	 */
    void connect_consumer (const char* emitter_name,
						   Components::EventConsumerBase_ptr consumer)
		throw (Components::InvalidName,
			   Components::AlreadyConnected,
			   CORBA::SystemException );

	/**
	 * implements IDL:omg.org/Components/Events/disconnect_consumer:1.0
	 * disconnect a consumer from an emitter
	 * delegated to the object executor
	 * \param source_name The name of the emitter.
	 * \return The formerly connected consumer.
	 */
    Components::EventConsumerBase_ptr disconnect_consumer (const char* source_name)
		throw (Components::InvalidName,
			   Components::NoConnection,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_all_consumers:1.0
	 * provide the list of descriptions of all consumers
	 * delegated to the object executor
	 * \return The list of descriptions of all consumers.
	 */
    Components::ConsumerDescriptions* get_all_consumers()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_named_consumers:1.0
	 * provide the list of descriptions of consumer ports.
	 * delegated to the object executor
	 * \param names The list of names of consumer ports.
	 * \return The list of descriptions of consumer ports.
	 */
    Components::ConsumerDescriptions* get_named_consumers (const ::Components::NameList& names)
		throw (Components::InvalidName);

	/**
	 * implements IDL:omg.org/Components/Events/get_all_emitters:1.0
	 * provide the list of descriptions of all emitters
	 * delegated to the object executor
	 * \return The list of descriptions of all emitters.
	 */
    Components::EmitterDescriptions* get_all_emitters()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_named_emitters:1.0
	 * provide the list of descriptions of a named list of emitters
	 * delegated to the object executor
	 * \param names The list of names of emitters.
	 * \return The list of descriptions of the emitters.
	 */
    Components::EmitterDescriptions* get_named_emitters (const ::Components::NameList& names)
		throw (Components::InvalidName);

	/**
	 * implements IDL:omg.org/Components/Events/get_all_publishers:1.0
	 * provide the list of descriptions of all publishers
	 * delegated to the object executor
	 * \return The list of descriptions of all publishers.
	 */
    Components::SubscriberDescriptions* get_all_publishers()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_named_publishers:1.0
	 * provide the list of descriptions of publishers
	 * delegated to the object executor
	 * \param names The list of names of publisher ports.
	 * \return The list of descriptions of the publisher ports.
	 */
    Components::SubscriberDescriptions* get_named_publishers (const ::Components::NameList& names)
		throw (Components::InvalidName);

    //
    // from CCMObject
    //

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_component_def:1.0
	 * provide the component definition in an interface repository
	 * delegated to the object executor
	 * \return The reference to the repository object for the component.
	 */
    CORBA::IRObject_ptr get_component_def()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_ccm_home:1.0
	 * provide the home definition in an interface repository
	 * delegated to the object executor
	 * \return The reference to the repository object for the home.
	 */
    Components::CCMHome_ptr get_ccm_home()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_primary_key:1.0
	 * provide the primary key
	 * delegated to the object executor
	 * \return The primary key.
	 */
    Components::PrimaryKeyBase* get_primary_key()
		throw (Components::NoKeyAvailable, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/configuration_complete:1.0
	 * announce the completion of configuration
	 * delegated to the executor locator
	 */
    void configuration_complete()
		throw (Components::InvalidConfiguration, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/remove:1.0
	 * remove the component instance
	 * delegated to the object executor
	 */
    void remove()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_all_ports:1.0
	 * provide the list of descriptions of all ports
	 * delegated to the object executor
	 * \return The list of description of all ports.
	 */
    Components::ComponentPortDescription* get_all_ports()
		throw (CORBA::SystemException);

#ifndef _QEDO_NO_QOS
	char *
	get_component_id();

#endif

};


/**
 * base class for servant factories
 */
class ServantFactory : public RefCountBase
{
public:
	/**
	 * create a new servant
	 */
	virtual Qedo::ServantBase* create_servant() = 0;
};


/**
 * helper class for servant factories during unloading a shared library
 */
class CONTAINERDLL_API ServantFactoryCleaner
{
public:
	class ServantFactory* factory_;
	ServantFactoryCleaner (class ServantFactory* factory);
	~ServantFactoryCleaner();
};


/** @} */

} // namespace Qedo

#endif

