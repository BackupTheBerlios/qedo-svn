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

static char rcsid[] = "$Id: ClientValuetypes.cpp,v 1.2 2003/04/27 21:25:22 tom Exp $";


#include "ClientValuetypes.h"


CORBA::LongLong Cookie_impl::cookie_key_ = 0;

//
// Cookie
//
Cookie_impl::Cookie_impl()
{
	CORBA::OctetSeq_var octet_key = new CORBA::OctetSeq();

	octet_key->length (8);

	for (unsigned int i = 0; i < 8; i++)
	{
		octet_key.inout()[i] = ((char*)(&cookie_key_))[i];
	}

	cookieValue (octet_key.in());

    ++cookie_key_;
}


Cookie_impl::~Cookie_impl
()
{
}


CORBA::Boolean 
Cookie_impl::equal (Components::Cookie* cook)
{
	Cookie_impl* foreign_cook = dynamic_cast<Cookie_impl*>(cook);

	if (! foreign_cook)
		return false;

	CORBA::OctetSeq x = cookieValue();
	CORBA::OctetSeq y = foreign_cook->cookieValue();

	for (unsigned int i = 0; i < x.length(); i++)
	{
		if (x[i] != y[i])
			return false;
    }
    
	return true;
}


CORBA::ValueBase*
CookieFactory_impl::create_for_unmarshal()
{
	return new Cookie_impl();
}


//
// PortDescription
//
PortDescription_impl::PortDescription_impl (const char* name, const char* type_id)
#ifndef VC6
: PortDescription (name, type_id)
#endif
{
}


PortDescription_impl::PortDescription_impl()
{
}


PortDescription_impl::~PortDescription_impl()
{
}


CORBA::ValueBase* 
PortDescriptionFactory_impl::create_for_unmarshal
()
{	
	return new PortDescription_impl();
}


//
// FacetDescription
//
FacetDescription_impl::FacetDescription_impl (const char* name, 
											  const char* type_id, 
											  CORBA::Object_ptr ref)
#ifndef VC6
: FacetDescription (name, type_id, ref)
#endif
{
}


FacetDescription_impl::FacetDescription_impl()
{
}


FacetDescription_impl::~FacetDescription_impl()
{
}


CORBA::ValueBase* 
FacetDescriptionFactory_impl::create_for_unmarshal()
{	
	return new FacetDescription_impl();
}


//
// ConnectionDescription
//
ConnectionDescription_impl::ConnectionDescription_impl (Components::Cookie* ck, CORBA::Object_ptr objref)
#ifndef VC6
: ConnectionDescription (ck, objref)
#endif
{
}


ConnectionDescription_impl::ConnectionDescription_impl()
{
}


ConnectionDescription_impl::~ConnectionDescription_impl
()
{
}


CORBA::ValueBase* 
ConnectionDescriptionFactory_impl::create_for_unmarshal
()
{	
	return new ConnectionDescription_impl();
}


//
// ReceptacleDescription
//
ReceptacleDescription_impl::ReceptacleDescription_impl (const char* name, 
														const char* type_id, 
														CORBA::Boolean is_multiple, 
														const Components::ConnectedDescriptions& connections)
#ifndef VC6
: ReceptacleDescription (name, type_id, is_multiple, connections)
#endif
{
}


ReceptacleDescription_impl::ReceptacleDescription_impl()
{
}


ReceptacleDescription_impl::~ReceptacleDescription_impl()
{
}


CORBA::ValueBase* 
ReceptacleDescriptionFactory_impl::create_for_unmarshal()
{	
	return new ReceptacleDescription_impl();
}


//
// ConsumerDescription
//
ConsumerDescription_impl::ConsumerDescription_impl (const char* name, 
													const char* type_id, 
													Components::EventConsumerBase_ptr consumer)
#ifndef VC6
: ConsumerDescription (name, type_id, consumer)
#endif
{
}


ConsumerDescription_impl::ConsumerDescription_impl()
{
}


ConsumerDescription_impl::~ConsumerDescription_impl()
{
}


CORBA::ValueBase* 
ConsumerDescriptionFactory_impl::create_for_unmarshal()
{	
	return new ConsumerDescription_impl();
}


//
// EmitterDescription
//
EmitterDescription_impl::EmitterDescription_impl (const char* name, 
												  const char* type_id, 
												  Components::EventConsumerBase_ptr consumer)
#ifndef VC6
: EmitterDescription (name, type_id, consumer)
#endif
{
}


EmitterDescription_impl::EmitterDescription_impl()
{
}


EmitterDescription_impl::EmitterDescription_impl (const EmitterDescription_impl& emitter_desc)
{
}


EmitterDescription_impl::~EmitterDescription_impl()
{
}


CORBA::ValueBase* 
EmitterDescriptionFactory_impl::create_for_unmarshal()
{	
	return new EmitterDescription_impl();
}


//
// SubscriberDescription
//
SubscriberDescription_impl::SubscriberDescription_impl (const char* name, 
						   const char* type_id, 
						   Components::Cookie* ck, 
						   Components::EventConsumerBase_ptr consumer)
#ifndef VC6
: SubscriberDescription (name, type_id, ck, consumer)
#endif
{
}


SubscriberDescription_impl::SubscriberDescription_impl()
{
}


SubscriberDescription_impl::~SubscriberDescription_impl()
{
}


CORBA::ValueBase* 
SubscriberDescriptionFactory_impl::create_for_unmarshal()
{	
	return new SubscriberDescription_impl();
}


//
// ComponentPortDescription
//
ComponentPortDescription_impl::ComponentPortDescription_impl (const Components::FacetDescriptions& facets,
															  const Components::ReceptacleDescriptions& receptacles,
															  const Components::ConsumerDescriptions& consumers,
															  const Components::EmitterDescriptions& emitters,
															  const Components::SubscriberDescriptions& publishers)
#ifndef VC6
: ComponentPortDescription (facets, receptacles, consumers, emitters, publishers)
#endif
{
}


ComponentPortDescription_impl::ComponentPortDescription_impl()
{
}


ComponentPortDescription_impl::~ComponentPortDescription_impl()
{
}


CORBA::ValueBase* 
ComponentPortDescriptionFactory_impl::create_for_unmarshal()
{	
	return new ComponentPortDescription_impl();
}


//
// ConfigValue
//
#if _MSC_VER < 1300
ConfigValue_impl::ConfigValue_impl (const char* name, CORBA::Any& value)
{
	this->name(name);
	this->value(value);
}
#else
ConfigValue_impl::ConfigValue_impl (const char* name, CORBA::Any& value)
: ConfigValue (name, value)
{
}
#endif

ConfigValue_impl::ConfigValue_impl()
{
}


ConfigValue_impl::~ConfigValue_impl
()
{
}


CORBA::ValueBase* 
ConfigValueFactory_impl::create_for_unmarshal
()
{	
	return new ConfigValue_impl();
}
