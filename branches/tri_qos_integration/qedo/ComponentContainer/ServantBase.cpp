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

#include "ServantBase.h"
#include "HomeServantBase.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: ServantBase.cpp,v 1.8 2003/08/01 14:57:26 stoinski Exp $";

namespace Qedo {


ServantBase::ServantBase()
: current_executor_ (CORBA::Object::_nil()),
  executor_locator_ (Components::ExecutorLocator::_nil()),
  ccm_object_executor_ (0)
{
}


ServantBase::ServantBase (const ServantBase& base)
{
	current_executor_ = base.current_executor_;
	executor_locator_ = base.executor_locator_;
	ccm_object_executor_ = base.ccm_object_executor_;
}


ServantBase&
ServantBase::operator= (const ServantBase&)
{
	return *this;
}


ServantBase::~ServantBase()
{
	DEBUG_OUT ("ServantBase: Destructor called");

	// If current executor is not nil, we have to release it
	// A current executor of nil means, that the last operation call was handled
	// by the CCM object executor
	if (! CORBA::is_nil (current_executor_))
	{
		executor_locator_->release_executor (current_executor_);
	}

	ccm_object_executor_->_remove_ref();
}


void
ServantBase::current_executor (CORBA::Object_ptr cur_exec)
{
	current_executor_ = CORBA::Object::_duplicate (cur_exec);
}


void 
ServantBase::set_instance (const Qedo::ComponentInstance& instance)
{
	executor_locator_ = Components::ExecutorLocator::_duplicate (instance.executor_locator_);
	ccm_object_executor_ = instance.ccm_object_executor_;
	ccm_object_executor_->_add_ref();
}


//
// primary servant
//

PrimaryServant::PrimaryServant()
{
}


PrimaryServant::PrimaryServant (const PrimaryServant& base)
{
}


PrimaryServant&
PrimaryServant::operator= (const PrimaryServant&)
{
	return *this;
}


PrimaryServant::~PrimaryServant()
{
}


//
// from Navigation
//

CORBA::Object_ptr
PrimaryServant::provide_facet (const char* name)
throw (Components::InvalidName, CORBA::SystemException)
{
    return ccm_object_executor_->provide_facet (name);
}


Components::FacetDescriptions*
PrimaryServant::get_all_facets()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_all_facets();
}


Components::FacetDescriptions*
PrimaryServant::get_named_facets (const Components::NameList& names)
throw (CORBA::SystemException, Components::InvalidName)
{
    return ccm_object_executor_->get_named_facets (names);
}


CORBA::Boolean
PrimaryServant::same_component (CORBA::Object_ptr ref)
throw (CORBA::SystemException)
{
    return ccm_object_executor_->same_component (ref);
}


Components::Cookie*
PrimaryServant::connect (const char* name, CORBA::Object_ptr connection)
throw( Components::InvalidName, 
	   Components::InvalidConnection,
	   Components::AlreadyConnected,
	   Components::ExceededConnectionLimit,
	   CORBA::SystemException)
{
    return ccm_object_executor_->connect (name,connection);
}


void
PrimaryServant::disconnect (const char* name, Components::Cookie* ck)
throw (Components::InvalidName,
	   Components::InvalidConnection,
	   Components::CookieRequired,
	   Components::NoConnection,
	   CORBA::SystemException)
{
    ccm_object_executor_->disconnect (name,ck);
}


Components::ConnectedDescriptions*
PrimaryServant::get_connections (const char* name)
throw (Components::InvalidName, CORBA::SystemException)
{
    return ccm_object_executor_->get_connections (name);
}


Components::ReceptacleDescriptions*
PrimaryServant::get_all_receptacles()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_all_receptacles();
}


Components::ReceptacleDescriptions*
PrimaryServant::get_named_receptacles (const Components::NameList& names)
throw (Components::InvalidName)
{
    return ccm_object_executor_->get_named_receptacles (names);
}

//
// from Events
//

Components::EventConsumerBase_ptr
PrimaryServant::get_consumer (const char* sink_name)
throw(Components::InvalidName, CORBA::SystemException)
{
    return ccm_object_executor_->get_consumer (sink_name);
}


Components::Cookie*
PrimaryServant::subscribe (const char* publisher_name, Components::EventConsumerBase_ptr subscriber)
throw(Components::InvalidName, CORBA::SystemException)
{
    return ccm_object_executor_->subscribe (publisher_name, subscriber);
}


void
PrimaryServant::unsubscribe (const char* publisher_name, Components::Cookie* ck)
throw (Components::InvalidName, Components::InvalidConnection, CORBA::SystemException)
{
    ccm_object_executor_->unsubscribe(publisher_name, ck);
}


void
PrimaryServant::connect_consumer (const char* emitter_name, Components::EventConsumerBase_ptr consumer)
throw (Components::InvalidName, Components::AlreadyConnected, CORBA::SystemException)
{
    ccm_object_executor_->connect_consumer (emitter_name, consumer);
}


Components::EventConsumerBase_ptr
PrimaryServant::disconnect_consumer (const char* source_name)
throw (Components::InvalidName, Components::NoConnection, CORBA::SystemException)
{
    return ccm_object_executor_->disconnect_consumer (source_name);
}


Components::ConsumerDescriptions*
PrimaryServant::get_all_consumers()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_all_consumers();
}


Components::ConsumerDescriptions*
PrimaryServant::get_named_consumers (const ::Components::NameList& names)
throw (Components::InvalidName)
{
    return ccm_object_executor_->get_named_consumers (names);
}


Components::EmitterDescriptions*
PrimaryServant::get_all_emitters()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_all_emitters();
}


Components::EmitterDescriptions*
PrimaryServant::get_named_emitters (const ::Components::NameList& names)
throw (Components::InvalidName)
{
    return ccm_object_executor_->get_named_emitters (names);
}


Components::SubscriberDescriptions*
PrimaryServant::get_all_publishers()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_all_publishers();
}


Components::SubscriberDescriptions*
PrimaryServant::get_named_publishers (const ::Components::NameList& names)
throw (Components::InvalidName)
{
    return ccm_object_executor_->get_named_publishers (names);
}

//
// from CCMObject
//

CORBA::IRObject_ptr
PrimaryServant::get_component_def()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_component_def();
}


Components::CCMHome_ptr
PrimaryServant::get_ccm_home()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_ccm_home();
}


Components::PrimaryKeyBase*
PrimaryServant::get_primary_key()
throw(Components::NoKeyAvailable, CORBA::SystemException)
{
    return ccm_object_executor_->get_primary_key();
}


void
PrimaryServant::configuration_complete()
throw (Components::InvalidConfiguration, CORBA::SystemException)
{
    executor_locator_->configuration_complete();

	//
	// check whether the components home is for container services
	//
	if(ccm_object_executor_->home_servant_->service_name_ != "")
	{
		std::string name = ccm_object_executor_->home_servant_->service_name_;
		Components::CCMService* service = dynamic_cast< Components::CCMService_ptr >(executor_locator_.in());
		if (!service)
		{
			NORMAL_ERR("ERROR: a component shall implement a service but is no");
		}

		ContainerInterfaceImpl* container = ccm_object_executor_->home_servant_->container_;
		
		//
		// register service reference
		//
		try
		{
			container->install_service_reference(name.c_str(), 
				ccm_object_executor_->component_primary_ref_);
		}
		catch(Components::CCMException)
		{
			NORMAL_ERR("ERROR: a component shall implement a service which is already implemented in the container");
		}

		//
		// register the service to be called in call chain
		//
//		container->services_preinvoke_.push_back(instance_);
//		container->services_postinvoke_.push_back(instance_);
	}
}


void
PrimaryServant::remove()
throw (CORBA::SystemException)
{
	ccm_object_executor_->remove();
}


Components::ComponentPortDescription*
PrimaryServant:: get_all_ports()
throw (CORBA::SystemException)
{
    return ccm_object_executor_->get_all_ports();
}


//
// The cleaner object for a ServantFactory
// 
ServantFactoryCleaner::ServantFactoryCleaner (class ServantFactory* factory)
: factory_ (factory)
{
}

ServantFactoryCleaner::~ServantFactoryCleaner()
{
	DEBUG_OUT ("ServantFactoryCleaner: Destructor called");
	factory_->_remove_ref();
}


} // namespace Qedo
