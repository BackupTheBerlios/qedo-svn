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

#include "Container_impl.h"
#include "Repository_impl.h"
#include "ModuleDef_impl.h"
#include "ConstantDef_impl.h"
#include "StructDef_impl.h"
#include "UnionDef_impl.h"
#include "EnumDef_impl.h"
#include "AliasDef_impl.h"
#include "NativeDef_impl.h"
#include "ExceptionDef_impl.h"
#include "InterfaceDef_impl.h"
#include "ValueDef_impl.h"
#include "StreamTypeDef_impl.h"
#include "ComponentDef_impl.h"
#include "HomeDef_impl.h"
#include "Debug.h"

#include <string>

using namespace std;

namespace QEDO_ComponentRepository {

Container_impl::Container_impl
( Repository_impl *repository )
: IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "Container_impl::Container_impl() called" );
}

Container_impl::~Container_impl
()
{
	DEBUG_OUTLINE ( "Container_impl::~Container_impl() called" );
}

void
Container_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUT ( "Container_impl::destroy() called for container " );

	Contained_impl *contained = dynamic_cast<Contained_impl*>(this);
	if ( contained )
		DEBUG_OUTLINE ( contained -> name() )
	else
		DEBUG_OUTLINE ( "Repository" );

	IR__::ContainedSeq_var contents = this -> contents ( CORBA__::dk_all, true );
	
	for ( CORBA::ULong index = 0; index < contents -> length(); index++ )
	{
		contents.inout()[index] -> destroy();
	}

	IRObject_impl::destroy();
}

bool
Container_impl::check_for_name
( const char *name )
{
	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( !strcmp ( (*contained_iter) -> name(), name ) )
			return true;
	}

	return false;
}

bool
Container_impl::add_name
( const char *name, Contained_impl *contained )
{
	if ( check_for_name ( name ) )
		return false;

	contained_.push_back ( contained );
	contained -> _add_ref();

	return true;
}

bool
Container_impl::remove_name
( const char *name )
{
	if ( !check_for_name ( name ) )
		return false;

	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( !strcmp ( (*contained_iter) -> name(), name ) )
		{
			Contained_impl* contained = *contained_iter;
			contained_.remove ( contained );
			contained -> _remove_ref();
			return true;
		}
	}

	return false;
}

Contained_impl*
Container_impl::resolve_name
( const char *name )
{
	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( !strcmp ( (*contained_iter) -> name(), name ) )
			return ( *contained_iter );
	}

	return NULL;
}


void
Container_impl::contained_sequence_cat
( IR__::ContainedSeq& return_seq,
  IR__::ContainedSeq& cat_seq )
{
	CORBA::ULong current_index = return_seq.length();
	int length_of_original_sequence = current_index;
	return_seq.length ( length_of_original_sequence + cat_seq.length() );

	for ( ; current_index < return_seq.length(); current_index++ )
	{
		return_seq[current_index] = cat_seq[current_index - length_of_original_sequence];
	}
}

void
Container_impl::check_recursion
( const char* id, CORBA::TypeCode_ptr tc )
{
	return; // TODO - sometimes infinite recursion

	// Get original type code
	CORBA::TypeCode_var orig_tc = CORBA::TypeCode::_duplicate ( tc );
    while ( tc -> kind() == CORBA::tk_alias )
        orig_tc = tc -> content_type();

    if ( orig_tc -> kind() == CORBA::tk_struct || orig_tc -> kind() == CORBA::tk_union ||
		orig_tc -> kind() == CORBA::tk_except )
    {
		CORBA::String_var tc_id = orig_tc -> id();
        if ( strcmp ( id, tc_id ) == 0 )
            throw CORBA::INTF_REPOS ( 3, CORBA::COMPLETED_NO );

        for ( unsigned int i = 0 ; i < orig_tc -> member_count() ; i++ )
        {
			CORBA::TypeCode_var member_type = orig_tc -> member_type(i);
            check_recursion ( id, member_type );
        }
    }
    else if(orig_tc -> kind() == CORBA::tk_array)
    {
		CORBA::TypeCode_var content_type = orig_tc -> content_type();
        check_recursion ( id, content_type );
    }
}

IR__::Contained_ptr
Container_impl::lookup
(const char* search_name)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::lookup() called" );
	
	// First look, whether it is a global name
	if ( strlen ( search_name ) > 1 )
	{
		if ( search_name[0] == ':' && search_name[1] == ':' )
		{
			return repository_ -> lookup ( &(search_name[2]) );
		}
	
		else
		{
			// Find first '::'
			string::size_type position_of_colons;
			string current_name_part = search_name;
			position_of_colons = current_name_part.find ( "::" );
			if ( position_of_colons != string::npos )
				current_name_part = current_name_part.substr ( 0, position_of_colons );

			if ( !check_for_name ( current_name_part.c_str() ) )
				return IR__::Contained::_nil();
		
			Contained_impl* contained = resolve_name ( current_name_part.c_str() );

			// If there is no other "::", return this one
			if ( position_of_colons == string::npos )
				return contained -> _this();

			current_name_part = search_name;
			current_name_part = current_name_part.substr ( position_of_colons + 2 );

			// We can only lookup if the found comtained is a container
			Container_impl *container = dynamic_cast<Container_impl*>(contained);
			if ( container )
				return container -> lookup ( current_name_part.c_str() );
		}
	}
	return IR__::Contained::_nil();
}

IR__::ContainedSeq*
Container_impl::contents
(CORBA__::DefinitionKind limit_type,
 CORBA::Boolean exclude_inherited)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::contents() called" );
	IR__::ContainedSeq_var return_seq = new IR__::ContainedSeq;
	return_seq -> length(0);
	int current_index = 0;

	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( limit_type == CORBA__::dk_all ||
				(*contained_iter) -> def_kind() == limit_type )
		{
			return_seq -> length ( current_index + 1 );
			return_seq.inout()[current_index] = (*contained_iter) -> _this();
			current_index++;
		}
	}

	return return_seq._retn();
}

IR__::ContainedSeq*
Container_impl::lookup_name
(const char* search_name,
 CORBA::Long levels_to_search,
 CORBA__::DefinitionKind limit_type,
 CORBA::Boolean exclude_inherited)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::lookup_name() called" );

	if ( levels_to_search > 1 )
		levels_to_search--;

	IR__::ContainedSeq_var return_seq = new IR__::ContainedSeq;
	return_seq -> length ( 0 );
	int current_index = 0;

	// In any case look in the current scope, after that we can
	// go through the contained objects to find the name
	if ( resolve_name ( search_name ) )
	{
		return_seq -> length ( current_index + 1 );
		return_seq.inout()[current_index] = resolve_name ( search_name ) -> _this();
		current_index++;
	}
	if ( levels_to_search == -1 || levels_to_search > 1 )
	{
		// Now go through each of the contained objects, test whether it is
		// a container and get the result from lookup_name
		list < Contained_impl* >::const_iterator contained_iter;
		for ( contained_iter = contained_.begin();
				contained_iter != contained_.end();
				contained_iter++ )
		{
			IR__::ContainedSeq_var recursive_return_seq = new IR__::ContainedSeq;
			recursive_return_seq -> length ( 0 );

			Container_impl *container =
				dynamic_cast<Container_impl*>(*contained_iter );
			if ( !container )
				continue;
			else
			{
				recursive_return_seq = container -> lookup_name (
					search_name,
					levels_to_search,
					limit_type,
					exclude_inherited );

				contained_sequence_cat ( return_seq, recursive_return_seq );
			}
		}
	}
	return return_seq._retn();
}

IR__::Container::DescriptionSeq*
Container_impl::describe_contents
(CORBA__::DefinitionKind limit_type,
 CORBA::Boolean exclude_inherited,
 CORBA::Long max_returned_objs)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::describe_contents() called" );
	IR__::ContainedSeq_var contained_objects =
		this -> contents ( limit_type, exclude_inherited );

	IR__::Container::DescriptionSeq_var descriptions =
		new IR__::Container::DescriptionSeq;
	descriptions -> length ( 0 );

	for ( CORBA::ULong current_index = 0;
			current_index < contained_objects -> length();
			current_index++ )
	{
		// For limitation of maximal number of returned objects
		if ( !max_returned_objs )
			return descriptions;

		descriptions -> length ( current_index + 1 );
		IR__::Contained::Description_var desc =
			contained_objects.inout()[current_index] -> describe();
		IR__::Container::Description_var container_desc =
			new IR__::Container::Description;
		container_desc -> contained_object = (IR__::Contained*)(contained_objects.inout()[current_index]);
		container_desc -> kind =	desc -> kind;
		container_desc -> value = desc -> value;
		
		descriptions.inout()[current_index] = container_desc;
		current_index++;
		max_returned_objs--;
	}

	return descriptions._retn();
}

IR__::ModuleDef_ptr
Container_impl::create_module
(const char* id,
 const char* name,
 const char* version)
throw(CORBA::SystemException)
{
	DEBUG_OUT ( "Container_impl::create_module() called " );
	DEBUG_OUT ( "--> id=" ); DEBUG_OUT ( id ); DEBUG_OUT ( ", name=" );
	DEBUG_OUT ( name ); DEBUG_OUT ( ", version=" );
	DEBUG_OUTLINE ( version );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	ModuleDef_impl *new_module = new ModuleDef_impl ( this, repository_ );
	new_module -> id ( id );
	new_module -> name ( name );
	new_module -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_module -> _this();
}

IR__::ConstantDef_ptr
Container_impl::create_constant
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr type,
 const CORBA::Any& value)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_constant() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	ConstantDef_impl *new_constant = new ConstantDef_impl ( this, repository_ );
	new_constant -> id ( id );
	new_constant -> name ( name );
	new_constant -> version ( version );
	new_constant -> type_def ( type );
	new_constant -> value ( value );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_constant -> _this();
}

//
// IDL:omg.org/IR__/Container/create_struct:1.0
//
IR__::StructDef_ptr
Container_impl::create_struct
(const char* id,
 const char* name,
 const char* version,
 const IR__::StructMemberSeq& members)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_struct() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	StructDef_impl *new_struct = new StructDef_impl ( this, repository_ );
	new_struct -> id ( id );
	new_struct -> name ( name );
	new_struct -> version ( version );
	new_struct -> members ( members );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_struct -> _this();
}

IR__::UnionDef_ptr
Container_impl::create_union
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr discriminator_type,
 const IR__::UnionMemberSeq& members)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_union() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	UnionDef_impl *new_union = new UnionDef_impl ( this, repository_ );
	new_union -> id ( id );
	new_union -> name ( name );
	new_union -> version ( version );
    new_union -> discriminator_type_def ( discriminator_type );
    new_union -> members ( members );
	
	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_union -> _this();
}

//
// IDL:omg.org/IR__/Container/create_enum:1.0
//
IR__::EnumDef_ptr
Container_impl::create_enum
(const char* id,
 const char* name,
 const char* version,
 const IR__::EnumMemberSeq& members)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_enum() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	EnumDef_impl *new_enum = new EnumDef_impl ( this, repository_ );
	new_enum -> id ( id );
	new_enum -> name ( name );
	new_enum -> version ( version );
	new_enum -> members ( members );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_enum -> _this();
}

IR__::AliasDef_ptr
Container_impl::create_alias
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr original_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_alias() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	AliasDef_impl *new_alias = new AliasDef_impl ( this, repository_ );
	new_alias -> id ( id );
	new_alias -> name ( name );
	new_alias -> version ( version );
	new_alias -> original_type_def ( original_type );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_alias -> _this();
}

IR__::InterfaceDef_ptr
Container_impl::create_interface
(const char* id,
 const char* name,
 const char* version,
 const IR__::InterfaceDefSeq& base_interfaces,
 CORBA::Boolean is_abstract)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_interface() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	InterfaceDef_impl *new_interface = new InterfaceDef_impl ( this, repository_ );
	new_interface -> id ( id );
	new_interface -> name ( name );
	new_interface -> version ( version );
	new_interface -> base_interfaces ( base_interfaces );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_interface -> _this();
}

IR__::ValueDef_ptr
Container_impl::create_value
(const char* id,
 const char* name,
 const char* version,
 CORBA::Boolean is_custom,
 CORBA::Boolean is_abstract,
 IR__::ValueDef_ptr base_value,
 CORBA::Boolean is_truncatable,
 const IR__::ValueDefSeq& abstract_base_values,
 const IR__::InterfaceDefSeq& supported_interfaces,
 const IR__::InitializerSeq& initializers)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_value() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	ValueDef_impl *new_value = new ValueDef_impl ( this, repository_ );
	new_value -> id ( id );
	new_value -> name ( name );
	new_value -> version ( version );
	new_value -> is_custom ( is_custom );
	new_value -> is_abstract ( is_abstract );
	new_value -> base_value ( base_value );
	new_value -> is_truncatable ( is_truncatable );
	new_value -> abstract_base_values ( abstract_base_values );
	new_value -> supported_interfaces ( supported_interfaces );
	new_value -> initializers ( initializers );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_value -> _this();
}

IR__::StreamTypeDef_ptr
Container_impl::create_stream_type
(const char* id,
 const char* name,
 const char* version)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_stream_type() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	StreamTypeDef_impl *new_stream_type = new StreamTypeDef_impl ( this, repository_ );
	new_stream_type -> id ( id );
	new_stream_type -> name ( name );
	new_stream_type -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_stream_type -> _this();
}

IR__::ValueBoxDef_ptr
Container_impl::create_value_box
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr original_type_def)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_value_box() called" );
	return (IR__::ValueBoxDef_ptr)0;
}

IR__::ExceptionDef_ptr
Container_impl::create_exception
(const char* id,
 const char* name,
 const char* version,
 const IR__::StructMemberSeq& members)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_exception() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	ExceptionDef_impl *new_exception = new ExceptionDef_impl ( this, repository_ );
	new_exception -> id ( id );
	new_exception -> name ( name );
	new_exception -> version ( version );
	new_exception -> members ( members );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_exception -> _this();
}

IR__::NativeDef_ptr
Container_impl::create_native
(const char* id,
 const char* name,
 const char* version)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_native() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	NativeDef_impl *new_native = new NativeDef_impl ( this, repository_ );
	new_native -> id ( id );
	new_native -> name ( name );
	new_native -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();
	
	return new_native -> _this();
}

IR__::ComponentDef_ptr
Container_impl::create_component
(const char* id,
 const char* name,
 const char* version,
 IR__::ComponentDef_ptr base_component,
 const IR__::InterfaceDefSeq& supports_interfaces)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_component() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

    ComponentDef_impl* impl = 0;

	// Test the base component if there is one
	if ( !CORBA::is_nil ( base_component ) )
	{
		try
		{
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant ( base_component );
			impl = dynamic_cast<ComponentDef_impl*>(servant.in());
		}
		catch(...)
		{
		}
		if(!impl)
		{
			// Must be same repository
			throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
		}
	}

	ComponentDef_impl *new_component = new ComponentDef_impl ( this, repository_, impl );

	new_component -> id ( id );
	new_component -> name ( name );
	new_component -> version ( version );
	new_component -> supported_interfaces ( supports_interfaces );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_component -> _this();
}

IR__::HomeDef_ptr
Container_impl::create_home
(const char* id,
 const char* name,
 const char* version,
 IR__::HomeDef_ptr base_home,
 IR__::ComponentDef_ptr managed_component,
 const IR__::InterfaceDefSeq& supports_interfaces,
 IR__::ValueDef_ptr primary_key)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Container_impl::create_home() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

    HomeDef_impl* base_home_impl = 0;
    ComponentDef_impl* managed_component_impl = 0;
    ValueDef_impl* primary_key_impl = 0;

	// Test the base home if there is one
	if ( !CORBA::is_nil ( base_home ) )
	{
		try
		{
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant ( base_home );
			base_home_impl = dynamic_cast<HomeDef_impl*>(servant.in());
		}
		catch(...)
		{
		}
		if(!base_home_impl)
		{
			// Must be same repository
			throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
		}
	}

	// Test the managed component
	if ( CORBA::is_nil ( managed_component ) )
		throw CORBA::BAD_PARAM();	// Is this exception corect?

	try
	{
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( managed_component );
		managed_component_impl = dynamic_cast<ComponentDef_impl*>(servant.in());
	}
	catch(...)
	{
	}
	if(!managed_component_impl)
	{
		// Must be same repository
		throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
	}

	// Test the primary key if there is one
	if ( !CORBA::is_nil ( primary_key ) )
	{
		try
		{
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant ( primary_key );
			primary_key_impl = dynamic_cast<ValueDef_impl*>(servant.in());
		}
		catch(...)
		{
		}
		if(!primary_key_impl)
		{
			// Must be same repository
			throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
		}
	}

	HomeDef_impl *new_home = 
		new HomeDef_impl ( this, repository_, 
			base_home_impl, managed_component_impl, primary_key_impl );

	new_home -> id ( id );
	new_home -> name ( name );
	new_home -> version ( version );
	new_home -> supported_interfaces ( supports_interfaces );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_home -> _this();
}

} // namespace QEDO_ComponentRepository
