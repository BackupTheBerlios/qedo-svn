/*****************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                    */
/*                                                                           */
/* Copyright (c) 2002 by the Qedo Team                                       */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */ 
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/

#include "ComponentDef_impl.h"
#include "ProvidesDef_impl.h"
#include "UsesDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ComponentDef_impl::ComponentDef_impl
( Container_impl *container,
  Repository_impl *repository,
  ComponentDef_impl *base_component_impl )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository ),
  InterfaceDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "ComponentDef_impl::ComponentDef_impl() called" );

	base_component_impl_ = base_component_impl;
	if ( base_component_impl_ )
		base_component_impl_ -> _add_ref();
}


ComponentDef_impl::~ComponentDef_impl
()
{
	DEBUG_OUTLINE ( "ComponentDef_impl::~ComponentDef_impl() called" );
}

void
ComponentDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::destroy() called" );

	unsigned int i;

	// Release base component impl
	if ( base_component_impl_ )
		base_component_impl_ -> _remove_ref();

	// Release all supported interface impls
    for ( i = 0 ; i < supported_interface_impls_.size() ; i++)
        supported_interface_impls_[i] -> _remove_ref();

	InterfaceDef_impl::destroy();
}

IR__::Contained::Description*
ComponentDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::describe() called" );

	IR__::ComponentDescription_var component_desc = new IR__::ComponentDescription();
	component_desc -> id = this -> id();
	component_desc -> name = this -> name();
	component_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		component_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		component_desc -> defined_in = CORBA::string_dup ( "" );

	// Base component
	if ( base_component_impl_ )
		component_desc -> base_component = base_component_impl_ -> id();
	else
		component_desc -> base_component = CORBA::string_dup ( "" );

	unsigned int i;

	// Supports interfaces
	component_desc -> supports_interfaces.length ( supported_interface_impls_.size() );
	for ( i = 0; i < supported_interface_impls_.size(); i++ )
		component_desc -> supports_interfaces[i] = supported_interface_impls_[i] -> id();

	// Attributes
	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		IR__::Contained::Description_var desc;

		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Attribute )
		{
			desc = (*contained_iter) -> describe();
			const IR__::AttributeDescription *attr_desc;

			// Extract attribute description from general description
			try
			{
				desc -> value >>= attr_desc;
			}
			catch ( ... )
			{
				// This cannot be, what to do???
				throw;
			}
			component_desc -> attributes.length ( component_desc -> attributes.length() + 1 );
			component_desc -> attributes[component_desc -> attributes.length() - 1] =
				*attr_desc;
		}
	}

	// Now do all the provides, uses interfaces and all the emits, publishes, consumes events
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		// Provides
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Provides )
		{
			ProvidesDef_impl *impl;
			impl = dynamic_cast < ProvidesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Provides' cannot be casted to ProvidesDef_impl" );
				continue;
			}
			component_desc -> provides_interfaces.length (
				component_desc -> provides_interfaces.length() + 1 );
			component_desc -> 
				provides_interfaces [ component_desc -> provides_interfaces.length() - 1 ] =
					impl -> _this();
		}
		// Uses
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Uses )
		{
			UsesDef_impl *impl;
			impl = dynamic_cast < UsesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Uses' cannot be casted to UsesDef_impl" );
				continue;
			}
			component_desc -> uses_interfaces.length (
				component_desc -> uses_interfaces.length() + 1 );
			component_desc -> 
				uses_interfaces [ component_desc -> uses_interfaces.length() - 1 ] =
					impl -> _this();
		}
		// Emits
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Emits )
		{
			EmitsDef_impl *impl;
			impl = dynamic_cast < EmitsDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Emits' cannot be casted to EmitsDef_impl" );
				continue;
			}
			component_desc -> emits_events.length (
				component_desc -> emits_events.length() + 1 );
			component_desc -> 
				emits_events [ component_desc -> emits_events.length() - 1 ] =
					impl -> _this();
		}
		// Publishes
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Publishes )
		{
			PublishesDef_impl *impl;
			impl = dynamic_cast < PublishesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Publishes' cannot be casted to PublishesDef_impl" );
				continue;
			}
			component_desc -> publishes_events.length (
				component_desc -> publishes_events.length() + 1 );
			component_desc -> 
				publishes_events [ component_desc -> publishes_events.length() - 1 ] =
					impl -> _this();
		}
		// Consumes
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Consumes )
		{
			ConsumesDef_impl *impl;
			impl = dynamic_cast < ConsumesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Consumes' cannot be casted to ConsumesDef_impl" );
				continue;
			}
			component_desc -> consumes_events.length (
				component_desc -> consumes_events.length() + 1 );
			component_desc -> 
				consumes_events [ component_desc -> consumes_events.length() - 1 ] =
					impl -> _this();
		}
	}

	component_desc -> is_basic = is_basic();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= component_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::InterfaceDefSeq*
ComponentDef_impl::supported_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::supported_interfaces() called" );

	
	IR__::InterfaceDefSeq_var supported_seq = new IR__::InterfaceDefSeq;

	supported_seq -> length ( supported_interface_impls_.size() );

	for ( unsigned int i = 0; i < supported_seq -> length(); i++ )
		supported_seq.inout()[i] = supported_interface_impls_[i] -> _this();

	return supported_seq._retn();
}

void
ComponentDef_impl::supported_interfaces
(const IR__::InterfaceDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::supported_interfaces(...) called" );

    unsigned int i;

	// Check: Derived components may not directly support an interface
	if ( base_component_impl_ && seq.length() > 0 )
	{
		throw CORBA::BAD_PARAM();
	}

	// Check for name clash
	// For each supported interface
	for ( i = 0; i < seq.length(); i++ )
	{
		IR__::ContainedSeq_var contained = seq[i] -> contents ( CORBA__::dk_all, false );
		
		// test each supported interface contained object
		for ( unsigned int j = 0; j < contained -> length(); j++ )
		{
			list < Contained_impl* >::const_iterator contained_iter;

			// against each of my own contained object
			for ( contained_iter = contained_.begin();
					contained_iter != contained_.end();
					contained_iter++ )
			{
				// for name clash
				// Note: Each interface includes in its containers contained list
				// also all inherited objects, so name clash appears when names
				// are equal and ids are different
				if ( strcmp ( contained.inout()[j] -> name(), (*contained_iter) -> name() ) == 0 &&
					 strcmp ( contained.inout()[j] -> id(), (*contained_iter) -> id() ) != 0 )
					throw CORBA::BAD_PARAM ( 5, CORBA::COMPLETED_NO );
			}
		}
	}

    vector < InterfaceDef_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );

    for ( i = 0; i < seq.length(); i++ )
    {
        if ( CORBA::is_nil ( seq[i] ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?
        impl_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(seq[i]);
            impl_seq[i] = dynamic_cast<InterfaceDef_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if(!impl_seq[i])
        {
            // Must be same repository
            throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
        }
    }

    for ( i = 0; i < impl_seq.size(); i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0; i < supported_interface_impls_.size(); i++)
        supported_interface_impls_[i] -> _remove_ref();

    supported_interface_impls_ = impl_seq;
}

IR__::ComponentDef_ptr
ComponentDef_impl::base_component
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::base_component() called" );

	if ( base_component_impl_ )
		return base_component_impl_ -> _this();
	else
		return IR__::ComponentDef::_nil();
}

IR__::ProvidesDefSeq*
ComponentDef_impl::provides_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::provides_interfaces() called" );

	IR__::ProvidesDefSeq_var provides_seq = new IR__::ProvidesDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Provides )
		{
			ProvidesDef_impl *impl;
			impl = dynamic_cast < ProvidesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Provides' cannot be casted to ProvidesDef_impl" );
				continue;
			}
			provides_seq -> length ( provides_seq -> length() + 1 );
			provides_seq [ provides_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return provides_seq._retn();
}

IR__::UsesDefSeq*
ComponentDef_impl::uses_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::uses_interfaces() called" );

	IR__::UsesDefSeq_var uses_seq = new IR__::UsesDefSeq;;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Uses )
		{
			UsesDef_impl *impl;
			impl = dynamic_cast < UsesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Uses' cannot be casted to UsesDef_impl" );
				continue;
			}
			uses_seq -> length ( uses_seq -> length() + 1 );
			uses_seq [ uses_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return uses_seq._retn();
}

IR__::EmitsDefSeq*
ComponentDef_impl::emits_events
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::emits_events() called" );

	IR__::EmitsDefSeq_var emits_seq = new IR__::EmitsDefSeq;;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Emits )
		{
			EmitsDef_impl *impl;
			impl = dynamic_cast < EmitsDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Emits' cannot be casted to EmitsDef_impl" );
				continue;
			}
			emits_seq -> length ( emits_seq -> length() + 1 );
			emits_seq [ emits_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return emits_seq._retn();
}

IR__::PublishesDefSeq*
ComponentDef_impl::publishes_events
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::publishes_events() called" );

	IR__::PublishesDefSeq_var publishes_seq = new IR__::PublishesDefSeq;;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Publishes )
		{
			PublishesDef_impl *impl;
			impl = dynamic_cast < PublishesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Publishes' cannot be casted to PublishesDef_impl" );
				continue;
			}
			publishes_seq -> length ( publishes_seq -> length() + 1 );
			publishes_seq [ publishes_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return publishes_seq._retn();
}

IR__::ConsumesDefSeq*
ComponentDef_impl::consumes_events
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::consumes_events() called" );

	IR__::ConsumesDefSeq_var consumes_seq = new IR__::ConsumesDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Consumes )
		{
			ConsumesDef_impl *impl;
			impl = dynamic_cast < ConsumesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Consumes' cannot be casted to ConsumesDef_impl" );
				continue;
			}
			consumes_seq -> length ( consumes_seq -> length() + 1 );
			consumes_seq [ consumes_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return consumes_seq._retn();
}

IR__::SinkDefSeq*
ComponentDef_impl::sinks
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::sinks() called" );

	IR__::SinkDefSeq_var sink_seq = new IR__::SinkDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Sink )
		{
			SinkDef_impl *impl;
			impl = dynamic_cast < SinkDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Sink' cannot be casted to SinkDef_impl" );
				continue;
			}
			sink_seq -> length ( sink_seq -> length() + 1 );
			sink_seq [ sink_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return sink_seq._retn();
}

IR__::SourceDefSeq*
ComponentDef_impl::sources
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::sinks() called" );

	IR__::SourceDefSeq_var source_seq = new IR__::SourceDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Source )
		{
			SourceDef_impl *impl;
			impl = dynamic_cast < SourceDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Source' cannot be casted to SourceDef_impl" );
				continue;
			}
			source_seq -> length ( source_seq -> length() + 1 );
			source_seq [ source_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return source_seq._retn();
}

IR__::SiSoDefSeq*
ComponentDef_impl::sisos
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::sinks() called" );

	IR__::SiSoDefSeq_var siso_seq = new IR__::SiSoDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_SiSo )
		{
			SiSoDef_impl *impl;
			impl = dynamic_cast < SiSoDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_SiSo' cannot be casted to SiSoDef_impl" );
				continue;
			}
			siso_seq -> length ( siso_seq -> length() + 1 );
			siso_seq [ siso_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return siso_seq._retn();
}

CORBA::Boolean
ComponentDef_impl::is_basic
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::is_basic() called" );

	// Basic components do not have a base component, do not
	// provide, use interfaces, do not consume, emit or publish events
	if ( base_component_impl_ )
		return false;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		CORBA__::DefinitionKind def_kind;
		def_kind = (*contained_iter) -> def_kind();
		if ( def_kind == CORBA__::dk_Provides ||
			 def_kind == CORBA__::dk_Uses ||
			 def_kind == CORBA__::dk_Emits ||
			 def_kind == CORBA__::dk_Publishes ||
			 def_kind == CORBA__::dk_Consumes  )
			 return false;
	}

	return true;
}

IR__::ProvidesDef_ptr
ComponentDef_impl::create_provides
(const char* id,
 const char* name,
 const char* version,
 IR__::InterfaceDef_ptr interface_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_provides() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( interface_type ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

    InterfaceDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( interface_type );
        impl = dynamic_cast<InterfaceDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	ProvidesDef_impl *new_provides = new ProvidesDef_impl ( this, repository_, impl );
	new_provides -> id ( id );
	new_provides -> name ( name );
	new_provides -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_provides -> _this();
}

IR__::UsesDef_ptr
ComponentDef_impl::create_uses
(const char* id,
 const char* name,
 const char* version,
 IR__::InterfaceDef_ptr interface_type,
 CORBA::Boolean is_multiple)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_uses() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( interface_type ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

    InterfaceDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( interface_type );
        impl = dynamic_cast<InterfaceDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	UsesDef_impl *new_uses = new UsesDef_impl ( this, repository_, impl, is_multiple );
	new_uses -> id ( id );
	new_uses -> name ( name );
	new_uses -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_uses -> _this();
}

IR__::EmitsDef_ptr
ComponentDef_impl::create_emits
(const char* id,
 const char* name,
 const char* version,
 IR__::EventDef_ptr event_value )
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_emits() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( event_value ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

	// TODO: Check: event_value must be derived from EventBase

    EventDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( event_value );
        impl = dynamic_cast<EventDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	EmitsDef_impl *new_emits = new EmitsDef_impl ( this, repository_, impl );
	new_emits -> id ( id );
	new_emits -> name ( name );
	new_emits -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_emits -> _this();
}

IR__::PublishesDef_ptr
ComponentDef_impl::create_publishes
(const char* id,
 const char* name,
 const char* version,
 IR__::EventDef_ptr event_value)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_publishes() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( event_value ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

	// TODO: Check: event_value must be derived from EventBase

    EventDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( event_value );
        impl = dynamic_cast<EventDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	PublishesDef_impl *new_publishes = new PublishesDef_impl ( this, repository_, impl );
	new_publishes -> id ( id );
	new_publishes -> name ( name );
	new_publishes -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_publishes -> _this();
}

IR__::ConsumesDef_ptr
ComponentDef_impl::create_consumes
(const char* id,
 const char* name,
 const char* version,
 IR__::EventDef_ptr event_value)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_consumes() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( event_value ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

	// TODO: Check: event_value must be derived from EventBase

    EventDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( event_value );
        impl = dynamic_cast<EventDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	ConsumesDef_impl *new_consumes = new ConsumesDef_impl ( this, repository_, impl );
	new_consumes -> id ( id );
	new_consumes -> name ( name );
	new_consumes -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_consumes -> _this();
}

IR__::SinkDef_ptr
ComponentDef_impl::create_sink
(const char* id,
 const char* name,
 const char* version,
 IR__::StreamTypeDef_ptr stream_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_sink() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( stream_type ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

	// TODO: Check: event_value must be derived from EventBase

    StreamTypeDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( stream_type );
        impl = dynamic_cast<StreamTypeDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	SinkDef_impl *new_sink = new SinkDef_impl ( this, repository_, impl );
	new_sink -> id ( id );
	new_sink -> name ( name );
	new_sink -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_sink -> _this();
}

IR__::SourceDef_ptr
ComponentDef_impl::create_source
(const char* id,
 const char* name,
 const char* version,
 IR__::StreamTypeDef_ptr stream_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_sink() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( stream_type ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

	// TODO: Check: event_value must be derived from EventBase

    StreamTypeDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( stream_type );
        impl = dynamic_cast<StreamTypeDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	SourceDef_impl *new_source = new SourceDef_impl ( this, repository_, impl );
	new_source -> id ( id );
	new_source -> name ( name );
	new_source -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_source -> _this();
}

IR__::SiSoDef_ptr
ComponentDef_impl::create_siso
(const char* id,
 const char* name,
 const char* version,
 IR__::StreamTypeDef_ptr stream_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::create_sink() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( stream_type ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

	// TODO: Check: event_value must be derived from EventBase

    StreamTypeDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( stream_type );
        impl = dynamic_cast<StreamTypeDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	SiSoDef_impl *new_siso = new SiSoDef_impl ( this, repository_, impl );
	new_siso -> id ( id );
	new_siso -> name ( name );
	new_siso -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_siso -> _this();
}

} // namespace QEDO_ComponentRepository

