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

static char rcsid[] = "$Id: CCMObjectExecutor.cpp,v 1.11 2003/05/27 10:59:59 boehme Exp $";

#include "CCMObjectExecutor.h"
#include "GlobalHelpers.h"
#include "HomeServantBase.h"
#include "Output.h"
#include "Valuetypes.h"
#ifdef WIN32
#include "objbase.h"
#else /* Linux */
#include "uuid/uuid.h"
#endif

namespace Qedo {


CCMObjectExecutor::CCMObjectExecutor (const PortableServer::ObjectId& component_object_id,
									  const CORBA::Object_ptr& component_primary_ref,
									  HomeServantBase* home_servant)
: component_object_id_ (new PortableServer::ObjectId (component_object_id)),
  component_primary_ref_ (CORBA::Object::_duplicate (component_primary_ref)),
  home_servant_ (home_servant)
{
	home_servant_->_add_ref();

	// create uuid
#ifdef _WIN32
	GUID guid;
	CoCreateGuid(&guid);
	LPOLESTR lpolestr;
	StringFromCLSID(guid, &lpolestr);
	int i = wcstombs(NULL, lpolestr, 0);
    char *buf = (char *)malloc(i);
    wcstombs(buf, lpolestr, i);
	// remove { and }
	buf[i - 1] = '\0';
	uuid_ = buf;
	uuid_.erase(0, 1);
	free(buf);
	CoTaskMemFree(lpolestr);
#else /* Linux */
	uuid_t uuid;
	char buf[38];
	uuid_generate(uuid);
	sprintf(buff,"%2.2X%2.2X%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X\n"
	                ,(u_int32_t)uuid[0]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*1]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*2]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*3]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*4]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*5]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*6]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*7]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*8]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*9]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*10]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*11]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*12]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*13]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*14]
	                ,(u_int8_t)uuid[sizeof(u_int8_t)*15]);
	uuid_ = buf;
#endif
}


CCMObjectExecutor::~CCMObjectExecutor()
{
	DEBUG_OUT ( "CCMObjectExecutor: Destructor called" );

	home_servant_->_remove_ref();
}


const CORBA::Object_ptr 
CCMObjectExecutor::get_component()
{
	return CORBA::Object::_duplicate (component_primary_ref_);
}


const Components::CCMHome_ptr 
CCMObjectExecutor::get_home()
{
	return home_servant_->ref();
}


const SubscribedConsumerVector& 
CCMObjectExecutor::get_consumers_for_publisher (const char* name)
{
	PublisherVector::const_iterator pub_iter;
	
	for (pub_iter = publishers_.begin(); pub_iter != publishers_.end(); pub_iter++)
	{
		if ((*pub_iter).port_name() == name)
		{
			break;
		}
	}

	if (pub_iter == publishers_.end())
	{
		NORMAL_ERR2 ("CCMObjectExecutor: Fatal internal error: Publisher port not found in internal list, port name is ", name);
		assert (0);
	}

	return (*pub_iter).consumers();
}


const Components::EventConsumerBase_ptr 
CCMObjectExecutor::get_consumer_for_emitter (const char* name)
{
	EmitterVector::const_iterator emit_iter;
	
	for (emit_iter = emitters_.begin(); emit_iter != emitters_.end(); emit_iter++)
	{
		if ((*emit_iter).port_name() == name)
		{
			break;
		}
	}

	if (emit_iter == emitters_.end())
	{
		NORMAL_ERR2 ("CCMObjectExecutor: Fatal internal error: Emitter port not found in internal list, port name is ", name);
		assert (0);
	}

	return (*emit_iter).consumer();
}


void
CCMObjectExecutor::add_facet (const char* name,
                              const char* type_id,
                              const CORBA::Object_ptr facet_ref)
{
	FacetPort new_facet_port (name, type_id, facet_ref);

	facets_.push_back (new_facet_port);

	DEBUG_OUT2 ("CCMObjectExecutor: New facet registered: ", name);
}


void
CCMObjectExecutor::add_receptacle (const char* name,
                                   const char* type_id,
                                   bool is_multiplex)
{
	ReceptaclePort new_receptacle_port (name, type_id, is_multiplex);

	receptacles_.push_back (new_receptacle_port);

	DEBUG_OUT2 ("CCMObjectExecutor: New receptacle port registered: ", name);
}


void 
CCMObjectExecutor::add_publisher (const char* name,
                                  const char* type_id)
{
	PublisherPort new_publisher_port (name, type_id);

	publishers_.push_back (new_publisher_port);

	DEBUG_OUT2 ("CCMObjectExecutor: New publisher port registered: ", name);
}


void 
CCMObjectExecutor::add_emitter (const char* name,
                                const char* type_id)
{
	EmitterPort new_emitter_port (name, type_id);

	emitters_.push_back (new_emitter_port);

	DEBUG_OUT2 ("CCMObjectExecutor: New emitter port registered: ", name);
}


void
CCMObjectExecutor::add_consumer (const char* name,
                                 const char* type_id,
                                 Components::EventConsumerBase_ptr consumer)
{
	ConsumerPort new_consumer_port (name, type_id, consumer);

	consumers_.push_back (new_consumer_port);

	DEBUG_OUT2 ("CCMObjectExecutor: New consumes port registered: ", name);
}


//
// from Navigation
//

CORBA::Object_ptr
CCMObjectExecutor::provide_facet (const char* name)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: provide_facet() called");

	FacetVector::const_iterator facet_iter;

	for (facet_iter = facets_.begin(); facet_iter != facets_.end(); facet_iter++)
	{
		if ((*facet_iter).port_name() == name)
		{
			return (*facet_iter).facet_ref();
		}
	}

	DEBUG_OUT2 ( "CCMObjectExecutor: No facet registered with name ", name );

    throw Components::InvalidName();
}


Components::FacetDescriptions*
CCMObjectExecutor::get_all_facets()
throw (CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_all_facets() called");
	
	Components::FacetDescriptions_var facets = new Components::FacetDescriptions();
	facets->length (facets_.size());

	for (unsigned int i = 0; i < facets_.size(); i++)
	{
        facets.inout()[i] = facets_[i].facet_description();
	}

	return facets._retn();
}


Components::FacetDescriptions*
CCMObjectExecutor::get_named_facets (const Components::NameList& names)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_named_facets() called");

	Components::FacetDescriptions_var facets = new Components::FacetDescriptions();

	for (unsigned int i = 0; i < names.length(); i++)
	{
		const char * name = static_cast<const char*>(names[i]);

		for (unsigned int j = 0; j < facets_.size(); j++)
		{	
			if (facets_[j].port_name() == name)
			{
                facets->length (facets->length() + 1);
				(*facets)[facets->length() - 1] = facets_[j].facet_description();
				break;
			}
		}

		throw Components::InvalidName();
	}
	
	return facets._retn();
}


CORBA::Boolean
CCMObjectExecutor::same_component (CORBA::Object_ptr ref)
throw (CORBA::SystemException)
{
/*	PortableServer::ObjectId_var object_id;

	object_id = my_poa_ -> reference_to_id ( ref );

	string stringified_object_id = PortableServer::ObjectId_to_string ( object_id );

	string::size_type position_of_colon = stringified_object_id.find ( ":" );

	if ( position_of_colon == string::npos )
	{
		return false;
	}

	string hu_key = stringified_object_id.substr ( position_of_colon + 1 );

	CORBA::String_var my_key = key_ -> to_string();

	return hu_key == (char*)my_key;*/
    return true;
}


//
// from Receptacles
//

Components::Cookie*
CCMObjectExecutor::connect (const char* name, CORBA::Object_ptr connection)
throw (Components::InvalidName, 
	   Components::InvalidConnection,
	   Components::AlreadyConnected,
	   Components::ExceededConnectionLimit,
	   CORBA::SystemException)
{
	ReceptacleVector::iterator rec_iter;

	for (rec_iter = receptacles_.begin(); 
         rec_iter != receptacles_.end(); 
         rec_iter++)
	{
		if ((*rec_iter).port_name() == name)
		{
			return (*rec_iter).add_connection (connection);
		}
	}

	throw Components::InvalidName();
}


void 
CCMObjectExecutor::disconnect (const char* name, Components::Cookie* ck)
throw (Components::InvalidName,
	   Components::InvalidConnection,
	   Components::CookieRequired, 
	   Components::NoConnection,
	   CORBA::SystemException )
{
	ReceptacleVector::iterator rec_iter;

	for (rec_iter = receptacles_.begin(); 
         rec_iter != receptacles_.end(); 
         rec_iter++ )
	{
		if ((*rec_iter).port_name() == name)
		{
            (*rec_iter).remove_connection (ck);
        }
	}

	throw Components::InvalidName();
}


Components::ConnectedDescriptions* 
CCMObjectExecutor::get_connections (const char* name)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT2 ("CCMObjectExecutor: get_connections() called for ", name);

	ReceptacleVector::const_iterator rec_iter;
	
	for (rec_iter = receptacles_.begin(); rec_iter != receptacles_.end(); rec_iter++)
	{
		if ((*rec_iter).port_name() == name)
			break;
	}

	if (rec_iter == receptacles_.end())
	{
		throw Components::InvalidName();
	}

	Components::ConnectedDescriptions_var con_descs = (*rec_iter).connected_descriptions();

	return con_descs._retn();
}


Components::ReceptacleDescriptions*
CCMObjectExecutor::get_all_receptacles()
throw (CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_all_receptacles() called");

	Components::ReceptacleDescriptions_var receptacles = 
        new Components::ReceptacleDescriptions();
	receptacles->length (receptacles_.size());

	Components::ConnectedDescriptions_var con_descs;

	for (unsigned int i = 0; i < receptacles_.size(); i++)
	{
		(*receptacles)[i] = receptacles_[i].receptacle_description();
	}

	return receptacles._retn();
}


Components::ReceptacleDescriptions*
CCMObjectExecutor::get_named_receptacles (const Components::NameList& names)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_named_receptacles() called");

	Components::ReceptacleDescriptions_var receptacles = 
        new Components::ReceptacleDescriptions();

	for (unsigned int i = 0; i < names.length(); i++)
	{
		const char * name = static_cast<const char*>(names[i]);

		for (unsigned int j = 0; j < receptacles_.size(); j++)
		{
			if (receptacles_[j].port_name() == name)
			{
                receptacles->length (receptacles->length() + 1);

				(*receptacles)[receptacles->length() - 1] = 
                    receptacles_[j].receptacle_description();
			}
		}

		throw Components::InvalidName();
	}

	return receptacles._retn();
}


//
// from Events
//

Components::EventConsumerBase_ptr 
CCMObjectExecutor::get_consumer (const char* sink_name)
throw (Components::InvalidName, CORBA::SystemException)
{
	ConsumerVector::const_iterator con_iter;
	
	for (con_iter = consumers_.begin(); con_iter != consumers_.end(); con_iter++)
	{
		if ((*con_iter).port_name() == sink_name)
			break;
	}

	if (con_iter == consumers_.end())
	{
		throw Components::InvalidName();
	}

	Components::EventConsumerBase_var event_consumer = (*con_iter).consumer();
		
	return event_consumer._retn();
}


Components::Cookie* 
CCMObjectExecutor::subscribe (const char* name, 
                              Components::EventConsumerBase_ptr subscriber)
throw (Components::InvalidName, CORBA::SystemException)
{
	PublisherVector::iterator pub_iter;

	for (pub_iter = publishers_.begin(); pub_iter != publishers_.end(); pub_iter++)
	{
		if ((*pub_iter).port_name() == name)
		{
			return (*pub_iter).add_consumer (subscriber);
		}
	}

	throw Components::InvalidName();
}


Components::EventConsumerBase_ptr 
CCMObjectExecutor::unsubscribe (const char* name, Components::Cookie* ck)
throw (Components::InvalidName, Components::InvalidConnection, CORBA::SystemException)
{
	PublisherVector::iterator pub_iter;

	for (pub_iter = publishers_.begin(); pub_iter != publishers_.end(); pub_iter++)
	{
		if ((*pub_iter).port_name() == name)
		{
            return (*pub_iter).remove_consumer (ck);
        }
	}

	throw Components::InvalidName();
}


void 
CCMObjectExecutor::connect_consumer (const char* emitter_name, Components::EventConsumerBase_ptr consumer)
throw (Components::InvalidName, Components::AlreadyConnected, CORBA::SystemException)
{
	EmitterVector::iterator emi_iter;

	for (emi_iter = emitters_.begin(); emi_iter != emitters_.end(); emi_iter++)
	{
		if ((*emi_iter).port_name() == emitter_name)
		{
            (*emi_iter).set_consumer (consumer);

			return;
		}
	}

	throw Components::InvalidName();
}


Components::EventConsumerBase_ptr 
CCMObjectExecutor::disconnect_consumer (const char* name)
throw (Components::InvalidName, Components::NoConnection, CORBA::SystemException)
{
	EmitterVector::iterator emi_iter;

	for (emi_iter = emitters_.begin(); emi_iter != emitters_.end(); emi_iter++)
	{
		if ((*emi_iter).port_name() == name)
		{
            return (*emi_iter).unset_consumer();
		}
	}

	throw Components::InvalidName();
}


Components::ConsumerDescriptions* 
CCMObjectExecutor::get_all_consumers()
throw (CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_all_consumers() called");

	Components::ConsumerDescriptions_var consumers = new Components::ConsumerDescriptions();
	consumers->length (consumers_.size());

	for (unsigned int i = 0; i < consumers_.size(); i++)
	{
		(*consumers)[i] = consumers_[i].consumer_description();
	}

	return consumers._retn();
}


Components::ConsumerDescriptions* 
CCMObjectExecutor::get_named_consumers (const Components::NameList& names)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_named_consumers() called");

	Components::ConsumerDescriptions_var consumers = new Components::ConsumerDescriptions();
	consumers -> length ( names.length() );

	for (unsigned int i = 0; i < consumers_.size(); i++)
	{
		for (unsigned int j = 0; j < names.length(); j++)
		{
			const char * name = static_cast<const char*>(names[j]);

			if (consumers_[i].port_name() == name)
			{
       			consumers->length (consumers->length () + 1);

				(*consumers)[consumers->length() - 1] = consumers_[i].consumer_description();
			}
		}

   		if (consumers->length() == 0)
			throw Components::InvalidName();
	}

	return consumers._retn();
}


Components::EmitterDescriptions* 
CCMObjectExecutor::get_all_emitters()
throw (CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_all_emitters() called");

	Components::EmitterDescriptions_var emitters = new Components::EmitterDescriptions();

    emitters->length (emitters_.size());

	for (unsigned int i = 0; i < emitters_.size(); i++)
	{
		(*emitters)[i] = emitters_[i].emitter_description();
	}

	return emitters._retn();
}


Components::EmitterDescriptions* 
CCMObjectExecutor::get_named_emitters (const Components::NameList& names)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_named_emitters() called");

	Components::EmitterDescriptions_var emitters = new Components::EmitterDescriptions();

	for (unsigned int i = 0; i < emitters_.size(); i++)
	{
		for (unsigned int j = 0; j < names.length(); j++)
		{
			const char * name = static_cast<const char*>(names[j]);

			if (emitters_[i].port_name() == name)
			{
				emitters->length ( emitters->length() + 1);

                (*emitters)[emitters->length() - 1] = emitters_[i].emitter_description();
			}
		}

        if (emitters->length() == 0)
			throw Components::InvalidName();
	}

	return emitters._retn();
}


Components::SubscriberDescriptions* 
CCMObjectExecutor::get_all_publishers()
throw (CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_all_publishers() called");

	Components::SubscriberDescriptions_var publishers = 
        new Components::SubscriberDescriptions();

	for (unsigned int i = 0, ii = 0; i < publishers_.size(); i++)
	{
		// Get subscriber descriptions for current publisher
        Components::SubscriberDescriptions_var sub_helper;
        
        sub_helper = publishers_[i].subscriber_descriptions();

        // Append new sequence to existing sequence
        for (unsigned int j = 0; j < sub_helper->length(); j++, ii++)
        {
            publishers.inout()[ii] = sub_helper.in()[j];
        }
	}

	return publishers._retn();
}


Components::SubscriberDescriptions* 
CCMObjectExecutor::get_named_publishers (const Components::NameList& names)
throw (Components::InvalidName, CORBA::SystemException)
{
	DEBUG_OUT ("CCMObjectExecutor: get_named_publishers() called");

	Components::SubscriberDescriptions_var publishers = 
        new Components::SubscriberDescriptions();

	for (unsigned int i = 0, ii = 0; i < publishers_.size(); i++)
	{
		for (unsigned int j = 0; j < names.length(); j++)
		{
			const char * name = static_cast<const char*>(names[j]);

			if (publishers_[i].port_name() == name)
			{
		        // Get subscriber descriptions for current publisher
                Components::SubscriberDescriptions_var sub_helper;
        
                sub_helper = publishers_[i].subscriber_descriptions();

                // Append new sequence to existing sequence
                for (unsigned int k = 0; k < sub_helper->length(); k++, ii++)
                {
					publishers->length (publishers->length() + 1);

                    publishers.inout()[ii] = sub_helper.in()[k];
                }
			}
		}

        if (publishers->length() == 0)
			throw Components::InvalidName();
	}

	return publishers._retn();
}


//
// from CCMObject
//

CORBA::IRObject_ptr 
CCMObjectExecutor::get_component_def()
throw (CORBA::SystemException)
{
	return CORBA::IRObject::_nil();
}


Components::CCMHome_ptr 
CCMObjectExecutor::get_ccm_home()
throw (CORBA::SystemException)
{
    return Components::CCMHome::_nil();
}


Components::PrimaryKeyBase* 
CCMObjectExecutor::get_primary_key()
throw (Components::NoKeyAvailable, CORBA::SystemException)
{
	throw Components::NoKeyAvailable();
}


void 
CCMObjectExecutor::remove()
throw (CORBA::SystemException)
{
	home_servant_->remove_component_with_oid (component_object_id_);
}


Components::ComponentPortDescription* 
CCMObjectExecutor::get_all_ports()
{
	Components::ComponentPortDescription_var ports = new ComponentPortDescription_impl();
	Components::FacetDescriptions_var the_facets = get_all_facets();
	Components::ReceptacleDescriptions_var the_receptacles = get_all_receptacles();
	Components::ConsumerDescriptions_var the_consumers = get_all_consumers();
	Components::EmitterDescriptions_var the_emitters = get_all_emitters();
	Components::SubscriberDescriptions_var the_publishers = get_all_publishers();

    ports->facets (the_facets);
    ports->receptacles (the_receptacles);
	ports->consumers (the_consumers);
    ports->emitters (the_emitters);
    ports->publishers (the_publishers);

	return ports._retn(); 
}


} // namespace Qedo
