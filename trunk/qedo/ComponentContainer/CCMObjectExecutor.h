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

#ifndef __CCM_OBJECT_EXECUTOR_H__
#define __CCM_OBJECT_EXECUTOR_H__

#include <CORBA.h>
#include "Components.h"
#include "ConsumerPort.h"
#include "EmitterPort.h"
#include "FacetPort.h"
#include "PublisherPort.h"
#include "ReceptaclePort.h"
#include "Key.h"
#include "RefCountBase.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class HomeServantBase;


/**
 * generic executor for components
 */
class CONTAINERDLL_API CCMObjectExecutor : public RefCountBase
{
	/** need access to home_servant_ */
	friend class PrimaryServant;
	/** need access */
	friend class ServantLocator;
	/** needs access to home_servant_ */
	friend class InternalConfiguration;

#ifndef _QEDO_NO_QOS

	friend class ServerInterceptorDispatcher;
#endif

private:
	/** list of facets */
	FacetVector						facets_;
	/** list of receptacles */
	ReceptacleVector				receptacles_;
	/** list of publishers */
	PublisherVector	        		publishers_;
	/** list of emitters */
    EmitterVector					emitters_;
	/** list of consumers */
	ConsumerVector  				consumers_;

	/** object id of the component */
	PortableServer::ObjectId_var	component_object_id_;
	/** object reference of the component interface */
	CORBA::Object_var				component_primary_ref_;
	/** home servant */
	HomeServantBase*				home_servant_;

	/**
	 * copy constructor shall not be called
	 */
	CCMObjectExecutor (const CCMObjectExecutor&);

	/**
	 * assignment operator shall not be called
	 */
	CCMObjectExecutor& operator= (const CCMObjectExecutor&);

public:
	/**
	 * constructor
	 * \param component_object_id The object id of the component instance.
	 * \param component_primary_ref The object reference of the component interface.
	 * \param home_servant The home servant.
	 */
	CCMObjectExecutor (const PortableServer::ObjectId& component_object_id,
					   const CORBA::Object_ptr& component_primary_ref,
					   HomeServantBase* home_servant);

	/**
	 * destructor
	 */
	~CCMObjectExecutor();

	//
	// Helper functions for the contexts
	//

	/**
	 * provides the object reference for the component CCMObject interface
	 */
	const CORBA::Object_ptr get_component();

	/**
	 * provides the object reference for the home interface
	 */
	const Components::CCMHome_ptr get_home();

	/**
	 * provides a list of consumers for the given publisher name
	 * \param name The name of the publisher.
	 */
	const SubscribedConsumerVector& get_consumers_for_publisher (const char* name);

	/**
	 * provides a list of consumers for the given emitter name
	 * \param name The name of the emitter.
	 */
	const Components::EventConsumerBase_ptr get_consumer_for_emitter (const char* name);
	
	//
	// Functions to build up the component instance structure
	//

	/**
	 * add a facet entry to the internal structure
	 * \param name The name of the facet.
	 * \param type_id The interface repository id of the interface.
	 * \param facet_ref The object reference of the facet.
	 */
	void add_facet (const char* name, const char* type_id, const CORBA::Object_ptr facet_ref);
	
	/**
	 * add a receptacle entry to the internal structure
	 * \param name The name of the receptacle.
	 * \param type_id The interface repository id of the interface.
	 * \param is_multiplex True if the receptacle is multiplex.
	 */
	void add_receptacle (const char* name, const char* type_id, bool is_multiplex);
	
	/**
	 * add a publisher entry to the internal structure
	 * \param name The name of the publisher.
	 * \param type_id The interface repository id of the interface.
	 */
	void add_publisher (const char* name, const char* type_id);
	
	/**
	 * add an emitter entry to the internal structure
	 * \param name The name of the emitter.
	 * \param type_id The interface repository id of the interface.
	 */
	void add_emitter (const char* name, const char* type_id);
	
	/**
	 * add a consumer entry to the internal structure
	 * \param name The name of the consumer.
	 * \param type_id The interface repository id of the interface.
	 * \param consumer The consumer object reference.
	 */
	void add_consumer (const char* name, const char* type_id, const Components::EventConsumerBase_ptr consumer);

	//
	// operations from navigation
	//

	/**
	 * implements IDL:omg.org/Components/Navigation/provide_facet:1.0
	 * provides the facet object reference
	 * \param name The name of the facet.
	 */
	CORBA::Object_ptr provide_facet (const char* name)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Navigation/get_all_facets:1.0
	 * provides the list of all facets
	 */
	Components::FacetDescriptions* get_all_facets()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Navigation/get_named_facets:1.0
	 * provides the list of the facets specified by the list of names
	 * \param names The list of the names of the facets.
	 */
    Components::FacetDescriptions* get_named_facets (const ::Components::NameList& names)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Navigation/same_component:1.0
	 * (not implemented yet)
	 */
	CORBA::Boolean same_component (CORBA::Object_ptr)
		throw(CORBA::SystemException);

	//
	// operations from receptacles
	//

	/**
	 * implements IDL:omg.org/Components/Receptacles/connect:1.0
	 * establishes a connection between a receptacle and an object
	 * \param name The name of the receptacle.
	 * \param connection The object reference of the object.
	 * \return A Cookie for identification of the connection.
	 */
	Components::Cookie* connect (const char* name, CORBA::Object_ptr connection)
		throw (Components::InvalidName, 
			   Components::InvalidConnection,
			   Components::AlreadyConnected, 
			   Components::ExceededConnectionLimit,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Receptacles/disconnect:1.0
	 * disconnects an obejct from a receptacle
	 * \param name The name of the receptacle.
	 * \param ck The Cookie for the connection.
	 */
	void disconnect (const char* name, Components::Cookie* ck)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   Components::CookieRequired,
			   Components::NoConnection,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Receptacles/get_connections:1.0
	 * provides the list of descriptions for all connections of a given receptacle
	 * \param name The name of the receptacle.
	 * \return The list of the connection descriptions.
	 */
	Components::ConnectedDescriptions* get_connections (const char* name)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Receptacles/get_all_receptacles:1.0
	 * provides a list of descriptions for all receptacles
	 */
	Components::ReceptacleDescriptions* get_all_receptacles()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Receptacles/get_named_receptacles:1.0
	 * provides a list of receptacle descriptions for a given list of receptacle names
	 * \param names The list of the receptacle names.
	 * \return The list of the receptacle descriptions.
	 */
	Components::ReceptacleDescriptions* get_named_receptacles (const Components::NameList& names)
        throw (Components::InvalidName, CORBA::SystemException);

	//
	// operations from events
	//

	/**
	 * implements IDL:omg.org/Components/Events/get_consumer:1.0
	 * provides the consumer interface for the given consumer name
	 * \param sink_name The name of the consumer.
	 * \return The object reference of the event consumer interface.
	 */
	Components::EventConsumerBase_ptr get_consumer (const char* sink_name)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/subscribe:1.0
	 * subscribes an event consumer on a publisher
	 * \param name The name of the publisher.
	 * \param subscriber The subscriber.
	 * \return A Cookie for identification of the subscription.
	 */
	Components::Cookie* subscribe (const char* name, Components::EventConsumerBase_ptr subscriber)
		throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/unsubscribe:1.0
	 * unsubscribes an event consumer from a publisher
	 * \param name The name of the publisher.
	 * \param ck The Cookie for identification of the subscription.
	 * \return The object reference of the unsubscribed event consumer.
	 */
	Components::EventConsumerBase_ptr unsubscribe (const char* name, Components::Cookie* ck)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/connect_consumer:1.0
	 * connects an event consumer with an emitter
	 * \param emitter_name The name of the emitter.
	 * \param consumer The object reference of the event consumer.
	 */
	void connect_consumer (const char* emitter_name, Components::EventConsumerBase_ptr consumer)
		throw (Components::InvalidName,
			   Components::AlreadyConnected,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/disconnect_consumer:1.0
	 * disconnects an event consumer from an emitter
	 * \param name The name of the emitter.
	 * \return The object reference of the event consumer.
	 */
	Components::EventConsumerBase_ptr disconnect_consumer (const char* name)
		throw (Components::InvalidName, 
			   Components::NoConnection,
			   CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_all_consumers:1.0
	 * provides a list of descriptions for all consumers
	 * \return The list of all consumer descriptions.
	 */
	Components::ConsumerDescriptions* get_all_consumers()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_named_consumers:1.0
	 * provides descriptions for a list of consumers
	 * \param names The list of the consumers.
	 * \return The list of consumer descriptions.
	 */
    Components::ConsumerDescriptions* get_named_consumers (const Components::NameList& names)
        throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_all_emitters:1.0
	 * provides a list of all emitter descriptions
	 * \return The list of emitter descriptions.
	 */
    Components::EmitterDescriptions* get_all_emitters()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_named_emitters:1.0
	 * provides a list of emitter descriptions
	 * \param names The list of names of the emitters.
	 * \return The list of emitter descriptions.
	 */
    Components::EmitterDescriptions* get_named_emitters (const Components::NameList& names)
        throw (Components::InvalidName, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_all_publishers:1.0
	 * provides all publisher descriptions
	 * \return The list of publisher descriptions.
	 */
    Components::SubscriberDescriptions* get_all_publishers()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Events/get_named_publishers:1.0
	 * provides a list of publisher descriptions
	 * \param names The list of names of the publishers.
	 * \return The list of publisher descriptions.
	 */
    Components::SubscriberDescriptions* get_named_publishers (const Components::NameList& names)
        throw (Components::InvalidName, CORBA::SystemException);

	//
	// operations from CCMObject
	//

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_component_def:1.0
	 * provides the interface repository object for the component definition (not yet implemented)
	 * \return The interface repository object reference for the component definition.
	 */
	CORBA::IRObject_ptr get_component_def()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_ccm_home:1.0
	 * provides the interface repository object for the home definition (not yet implemented)
	 * \return The interface repository object reference for the home definition.
	 */
	Components::CCMHome_ptr get_ccm_home()
		throw ( CORBA::SystemException );

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_primary_key:1.0
	 * (not yet implemented)
	 */
	Components::PrimaryKeyBase* get_primary_key()
		throw (Components::NoKeyAvailable, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/remove:1.0
	 * removes the component
	 */
	void remove()
		throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMObject/get_all_ports:1.0
	 * provides a list of descriptions for all ports
	 * \return The list of all port descriptions.
	 */
	Components::ComponentPortDescription* get_all_ports();
};

/** @} */

} // namespace Qedo

#endif

