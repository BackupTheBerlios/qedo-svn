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

static char rcsid[] = "$Id: Valuetypes.cpp,v 1.9 2003/04/01 07:50:10 neubauer Exp $";


#include "Valuetypes.h"


namespace Qedo {


CORBA::LongLong Cookie_impl::cookie_key_ = 0;


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


PortDescription_impl::PortDescription_impl (const char* name, const char* type_id)
#if _MSC_VER < 1300 
: PortDescription()
#else
: PortDescription (name, type_id)
#endif
{
#if _MSC_VER < 1300
	this -> name ( name );
	this -> type_id ( type_id );
#endif
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


FacetDescription_impl::FacetDescription_impl (const char* name, 
											  const char* type_id, 
											  CORBA::Object_ptr ref)
: FacetDescription()
{
	this -> name ( name );
	this -> type_id ( type_id );
	this -> ref ( ref );
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


ConnectionDescription_impl::ConnectionDescription_impl (Components::Cookie* ck, CORBA::Object_ptr objref)
#if _MSC_VER < 1300 
: ConnectionDescription()
#else
: ConnectionDescription (ck, objref)
#endif
{
#if _MSC_VER < 1300
	this -> ck( ck );
	this -> objref( objref );
#endif

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


ReceptacleDescription_impl::ReceptacleDescription_impl (const char* name, 
														const char* type_id, 
														CORBA::Boolean is_multiplex, 
														const Components::ConnectedDescriptions& connections)
: ReceptacleDescription ()
{
	this -> name( name );
	this -> type_id( type_id );
	this -> is_multiplex( is_multiplex );
	this -> connections( connections );
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


ConsumerDescription_impl::ConsumerDescription_impl (const char* name, 
													const char* type_id, 
													Components::EventConsumerBase_ptr consumer)
: ConsumerDescription ()
{
	this -> name ( name );
	this -> type_id ( type_id );
	this -> consumer ( consumer );
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


EmitterDescription_impl::EmitterDescription_impl (const char* name, 
												  const char* type_id, 
												  Components::EventConsumerBase_ptr consumer)
: EmitterDescription ( )
{
	this -> name ( name );
	this -> type_id ( type_id );
	this -> consumer ( consumer );
}


EmitterDescription_impl::EmitterDescription_impl()
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


SubscriberDescription_impl::SubscriberDescription_impl (const char* name, 
						   const char* type_id, 
						   Components::Cookie* ck, 
						   Components::EventConsumerBase_ptr consumer)
: SubscriberDescription ( )
{
	this -> name ( name );
	this -> type_id (type_id );
	this -> ck ( ck );
	this -> consumer ( consumer );
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


ComponentPortDescription_impl::ComponentPortDescription_impl (const Components::FacetDescriptions& facets,
															  const Components::ReceptacleDescriptions& receptacles,
															  const Components::ConsumerDescriptions& consumers,
															  const Components::EmitterDescriptions& emitters,
															  const Components::SubscriberDescriptions& publishers)
#if _MSC_VER < 1300 
: ComponentPortDescription ( )
#else
: ComponentPortDescription (facets, receptacles, consumers, emitters, publishers)
#endif
{
#if _MSC_VER < 1300
	this -> facets ( facets );
	this -> receptacles ( receptacles );
	this -> consumers ( consumers );
	this -> emitters ( emitters );
	this -> publishers ( publishers );
#endif
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


ConfigValue_impl::ConfigValue_impl (const char* name,  CORBA::Any& value)
#if _MSC_VER < 1300 
: ConfigValue ()
#else
: ConfigValue (name, value)
#endif
{
#if _MSC_VER < 1300
	this->name(name);
	this->value(value);
#endif
}


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


} // namespace Qedo
