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

#ifndef _QEDO_NO_QOS
#include "GlobalHelpers.h"
#endif

static char rcsid[] UNUSED = "$Id: ServantBase.cpp,v 1.16 2004/07/16 12:50:51 tom Exp $";

namespace Qedo {


ServantBase::ServantBase()
: executor_locator_ (Components::ExecutorLocator::_nil()),
  ccm_object_executor_ (0),
#ifndef _QEDO_NO_STREAMS
  stream_ccm_object_executor_ (0),
#endif
  current_executor_ (CORBA::Object::_nil())
{
}


ServantBase::ServantBase (const ServantBase& base)
: executor_locator_ (Components::ExecutorLocator::_duplicate (base.executor_locator_.in())),
  ccm_object_executor_ (base.ccm_object_executor_),
#ifndef _QEDO_NO_STREAMS
  stream_ccm_object_executor_ (base.stream_ccm_object_executor_),
#endif
  current_executor_ (base.current_executor_)
{
        ccm_object_executor_->_add_ref();
#ifndef _QEDO_NO_STREAMS
        stream_ccm_object_executor_->_add_ref();
#endif
}


ServantBase&
ServantBase::operator= (const ServantBase& base)
{
       current_executor_ = base.current_executor_;
       executor_locator_ = Components::ExecutorLocator::_duplicate (base.executor_locator_.in());
                                                                                                  
        if (ccm_object_executor_)
                ccm_object_executor_->_remove_ref();
                                                                                                  
        ccm_object_executor_ = base.ccm_object_executor_;
        ccm_object_executor_->_add_ref();
                                                                                                  
#ifndef _QEDO_NO_STREAMS
        if (stream_ccm_object_executor_)
                stream_ccm_object_executor_->_remove_ref();
                                                                                                  
        stream_ccm_object_executor_ = base.stream_ccm_object_executor_;
        stream_ccm_object_executor_->_add_ref();
#endif
                                                                                                  
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

#ifndef _QEDO_NO_STREAMS
        stream_ccm_object_executor_->_remove_ref();
#endif
}


void
ServantBase::current_executor (CORBA::Object_ptr cur_exec)
{
	current_executor_ = CORBA::Object::_duplicate (cur_exec);
}


void 
ServantBase::set_instance (Qedo::ComponentInstance& instance)
{
	executor_locator_ = Components::ExecutorLocator::_duplicate (instance.executor_locator_);
	ccm_object_executor_ = instance.ccm_object_executor_;
	ccm_object_executor_->_add_ref();

#ifndef _QEDO_NO_STREAMS
        stream_ccm_object_executor_ = instance.stream_ccm_object_executor_;
        stream_ccm_object_executor_->_add_ref();
#endif
}

#ifndef _QEDO_NO_QOS
void
ServantBase::set_servant_dispatcher_registry(Components::Extension::ServantInterceptorRegistration_ptr reg) 
{
	servant_interceptor_registry_ = Components::Extension::ServantInterceptorRegistration::_duplicate(reg);
}


#endif


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
#ifndef _QEDO_NO_QOS
	const char * comp_id = this-> get_component_id();
	CORBA::Boolean con = true;
	CORBA::Object_ptr anObject= servant_interceptor_registry_ -> provide_facet (comp_id, name, con);
	if (con)
	{
#endif

    return ccm_object_executor_->provide_facet (name);

#ifndef _QEDO_NO_QOS
	}
	return anObject;
#endif 
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
#ifndef _QEDO_NO_QOS
	const char * comp_id = this-> get_component_id();
	CORBA::Boolean con;
	Components::Cookie* temp_ck = servant_interceptor_registry_ -> connect (comp_id, name, connection, con);
	if (con)
	{
#endif
    return ccm_object_executor_->connect (name,connection);
#ifndef _QEDO_NO_QOS
	}
	return temp_ck;
#endif 
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
	std::cout << "PrimaryServant::get_primary_key()\n";
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
	if(ccm_object_executor_->home_servant_->service_name_.length())
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

#ifndef _QEDO_NO_QOS
const char *
PrimaryServant::get_component_id(){
	const char* comp_id = 0;
	unsigned int i;
	for (i=0; i < ccm_object_executor_ -> home_servant_ -> component_instances_.size(); i++)
	{
		if (Qedo::compare_OctetSeqs(this -> ccm_object_executor_ -> component_object_id_,
			(this -> ccm_object_executor_ -> home_servant_ -> component_instances_[i].object_id_)))
		{
			Components::ConfigValues* temp_config=0;
			temp_config = this -> ccm_object_executor_ -> home_servant_ -> component_instances_[i].config_;

			if (temp_config != 0)
			{

				Components::ConfigValue* value;
				for (CORBA::ULong k = 0; k < temp_config->length(); k++)
				{
					value = (*temp_config)[k];

					if (! strcmp ((*temp_config)[k]->name(), "id"))
					{
						(*temp_config)[k]->value() >>= comp_id;
						break;
					}
				}
			}
		}
	}
	if (!comp_id)
	{
		comp_id="__QEDO__NOT_COMPONENT_ID__";
	}
	return comp_id;
}

#endif

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
