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

class HomeServantBase;

class CONTAINERDLL_API CCMObjectExecutor : public RefCountBase
{
private:
	FacetVector					facets_;
	ReceptacleVector			receptacles_;
	PublisherVector	        	publishers_;
    EmitterVector               emitters_;
	ConsumerVector  			consumers_;

	PortableServer::ObjectId_var component_object_id_;
	CORBA::Object_var component_primary_ref_;
	HomeServantBase* home_servant_;

	CCMObjectExecutor (const CCMObjectExecutor&);
	CCMObjectExecutor& operator= (const CCMObjectExecutor&);

public:
	CCMObjectExecutor (const PortableServer::ObjectId&,
					   const CORBA::Object_ptr&,
					   HomeServantBase*);
	~CCMObjectExecutor();

	// Helper functions for the contexts
	const CORBA::Object_ptr get_component();
	const SubscribedConsumerVector& get_consumers_for_publisher (const char* name);
	const Components::EventConsumerBase_ptr get_consumer_for_emitter (const char* name);
	
	// Functions to build up the component instance structure
	void add_facet (const char*, const char*, const CORBA::Object_ptr);

	void add_receptacle (const char*, const char*, bool);

	void add_publisher (const char*, const char*);

	void add_emitter (const char*, const char*);

	void add_consumer (const char*, const char*, const Components::EventConsumerBase_ptr);

	//
	// from Navigation
	//
	CORBA::Object_ptr provide_facet (const char*)
		throw (Components::InvalidName, CORBA::SystemException);

	Components::FacetDescriptions* get_all_facets()
		throw (CORBA::SystemException);

    Components::FacetDescriptions* get_named_facets (const ::Components::NameList&)
		throw (Components::InvalidName, CORBA::SystemException);

	CORBA::Boolean same_component (CORBA::Object_ptr)
		throw(CORBA::SystemException);

	//
	// from Receptacles
	//
	Components::Cookie* connect (const char*, CORBA::Object_ptr)
		throw (Components::InvalidName, 
			   Components::InvalidConnection,
			   Components::AlreadyConnected, 
			   Components::ExceededConnectionLimit,
			   CORBA::SystemException);

	void disconnect (const char*, Components::Cookie*)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   Components::CookieRequired,
			   Components::NoConnection,
			   CORBA::SystemException);

	Components::ConnectedDescriptions* get_connections (const char*)
		throw (Components::InvalidName, CORBA::SystemException);

	Components::ReceptacleDescriptions* get_all_receptacles()
        throw (CORBA::SystemException);

	Components::ReceptacleDescriptions* get_named_receptacles (const Components::NameList&)
        throw (Components::InvalidName, CORBA::SystemException);

	//
	// from Events
	//
	Components::EventConsumerBase_ptr get_consumer (const char*)
		throw (Components::InvalidName, CORBA::SystemException);

	Components::Cookie* subscribe ( 
		const char*,
		Components::EventConsumerBase_ptr)
		throw (Components::InvalidName, CORBA::SystemException);

	Components::EventConsumerBase_ptr unsubscribe (const char*, Components::Cookie*)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   CORBA::SystemException);

	void connect_consumer (const char*,
		                   Components::EventConsumerBase_ptr)
		throw (Components::InvalidName,
			   Components::AlreadyConnected,
			   CORBA::SystemException);

	Components::EventConsumerBase_ptr disconnect_consumer (const char*)
		throw (Components::InvalidName, 
			   Components::NoConnection,
			   CORBA::SystemException);

	Components::ConsumerDescriptions* get_all_consumers()
        throw (CORBA::SystemException);

    Components::ConsumerDescriptions* get_named_consumers (const Components::NameList&)
        throw (Components::InvalidName, CORBA::SystemException);

    Components::EmitterDescriptions* get_all_emitters()
        throw (CORBA::SystemException);

    Components::EmitterDescriptions* get_named_emitters (const Components::NameList&)
        throw (Components::InvalidName, CORBA::SystemException);

    Components::SubscriberDescriptions* get_all_publishers()
        throw (CORBA::SystemException);

    Components::SubscriberDescriptions* get_named_publishers (const Components::NameList&)
        throw (Components::InvalidName, CORBA::SystemException);

	//
	// from CCMObject
	//
	CORBA::IRObject_ptr get_component_def()
		throw (CORBA::SystemException);

	Components::CCMHome_ptr get_ccm_home()
		throw ( CORBA::SystemException );

	Components::PrimaryKeyBase* get_primary_key()
		throw (Components::NoKeyAvailable, CORBA::SystemException);

	void remove()
		throw (CORBA::SystemException);

	Components::ComponentPortDescription* get_all_ports();
};


} // namespace Qedo

#endif

