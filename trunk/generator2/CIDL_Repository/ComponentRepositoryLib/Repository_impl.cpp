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

#include "Repository_impl.h"
#include "Anonymous.h"
#include "ComponentDef_impl.h"
#include "HomeDef_impl.h"
#include "PrimaryKeyDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

Repository_impl::Repository_impl
( CORBA::ORB_ptr orb, PortableServer::POA_ptr poa )
: orb_ ( CORBA::ORB::_duplicate ( orb ) ),
  poa_ ( PortableServer::POA::_duplicate ( poa ) ),
  IRObject_impl ( this ),
  Container_impl ( this )
{
	DEBUG_OUTLINE ( "Repository_impl::Repository_impl() called" );

	pd_void_ = new PrimitiveDef_impl ( IR__::pk_void, this );
	pd_short_ = new PrimitiveDef_impl ( IR__::pk_short, this );
	pd_long_ = new PrimitiveDef_impl ( IR__::pk_long, this );
	pd_ushort_ = new PrimitiveDef_impl ( IR__::pk_ushort, this );
	pd_ulong_ = new PrimitiveDef_impl ( IR__::pk_ulong, this );
	pd_float_ = new PrimitiveDef_impl ( IR__::pk_float, this );
	pd_double_ = new PrimitiveDef_impl ( IR__::pk_double, this );
	pd_boolean_ = new PrimitiveDef_impl ( IR__::pk_boolean, this );
	pd_char_ = new PrimitiveDef_impl ( IR__::pk_char, this );
	pd_octet_ = new PrimitiveDef_impl ( IR__::pk_octet, this );
	pd_any_ = new PrimitiveDef_impl ( IR__::pk_any, this );
	pd_TypeCode_ = new PrimitiveDef_impl ( IR__::pk_TypeCode, this );
	pd_Principal_ = new PrimitiveDef_impl ( IR__::pk_Principal, this );
	pd_string_ = new PrimitiveDef_impl ( IR__::pk_string, this );
	pd_objref_ = new PrimitiveDef_impl ( IR__::pk_objref, this );
	pd_longlong_ = new PrimitiveDef_impl ( IR__::pk_longlong, this );
	pd_ulonglong_ = new PrimitiveDef_impl ( IR__::pk_ulonglong, this );
	pd_longdouble_ = new PrimitiveDef_impl ( IR__::pk_longdouble, this );
	pd_wchar_ = new PrimitiveDef_impl ( IR__::pk_wchar, this );
	pd_wstring_ = new PrimitiveDef_impl ( IR__::pk_wstring, this );
	pd_value_base_ = new PrimitiveDef_impl ( IR__::pk_value_base, this );
}

Repository_impl::~Repository_impl
()
{
	DEBUG_OUTLINE ( "Repository_impl::~Repository_impl() called" );

	if ( ir_anonymous_objects_.size() != 0 )
	{
		DEBUG_ERRLINE ( "Not all anonymous IR objects destroyed" );
	}
	else
	{
		DEBUG_OUTLINE ( "All anonymous IR objects destroyed" );
	}

	if ( IRObject_impl::number_ir_objects() != 1 )
	{
		DEBUG_OUTLINE ( "Warning: Not all IR objects destroyed on destruction of Repository" );
		DEBUG_OUT ( "Object count is " ); DEBUG_OUTLINE ( IRObject_impl::number_ir_objects() );
	}
	else
	{
		DEBUG_OUTLINE ( "All IR objects destroyed" );

	}
}

void
Repository_impl::destroy_repository
()
{
	// Copy the list, because we want to call IRObject::destroy(), which
	// writes to the list
	list < IRObject_impl* > ir_anonymous_objects_copy = ir_anonymous_objects_;
	list < IRObject_impl* >::const_iterator ir_anonymous_objects_iter;

	for ( ir_anonymous_objects_iter = ir_anonymous_objects_copy.begin();
			ir_anonymous_objects_iter != ir_anonymous_objects_copy.end();
			ir_anonymous_objects_iter++ )
	{
		this -> remove_anonymous ( *ir_anonymous_objects_iter );
		(*ir_anonymous_objects_iter) -> destroy();
	}

	pd_void_ -> destroy_from_repository();
	pd_short_ -> destroy_from_repository();
	pd_long_ -> destroy_from_repository();
	pd_ushort_ -> destroy_from_repository();
	pd_ulong_ -> destroy_from_repository();
	pd_float_ -> destroy_from_repository();
	pd_double_ -> destroy_from_repository();
	pd_boolean_ -> destroy_from_repository();
	pd_char_ -> destroy_from_repository();
	pd_octet_ -> destroy_from_repository();
	pd_any_ -> destroy_from_repository();
	pd_TypeCode_ -> destroy_from_repository();
	pd_Principal_ -> destroy_from_repository();
	pd_string_ -> destroy_from_repository();
	pd_objref_ -> destroy_from_repository();
	pd_longlong_ -> destroy_from_repository();
	pd_ulonglong_ -> destroy_from_repository();
	pd_longdouble_ -> destroy_from_repository();
	pd_wchar_ -> destroy_from_repository();
	pd_wstring_ -> destroy_from_repository();
	pd_value_base_ -> destroy_from_repository();

	Container_impl::destroy();

	this -> _remove_ref();
}

bool
Repository_impl::check_for_id
( const char *id )
{
	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = ir_named_objects_.begin();
			contained_iter != ir_named_objects_.end();
			contained_iter++ )
	{
		const char *current_id = (*contained_iter) -> id();
		if ( !strcmp ( (*contained_iter) -> id(), id ) )
			return true;
	}

	return false;
}


bool
Repository_impl::add_id
( const char *id, Contained_impl *contained )
{
	if ( check_for_id ( id ) )
		return false;

	ir_named_objects_.push_back ( contained );
	contained -> _add_ref();

	return true;
}

bool
Repository_impl::remove_id
( const char *id )
{
	if ( !check_for_id ( id ) )
		return false;

	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = ir_named_objects_.begin();
			contained_iter != ir_named_objects_.end();
			contained_iter++ )
	{
		const char* the_id = (*contained_iter) -> id();
		if ( !strcmp ( the_id, id ) )
		{
			Contained_impl *contained = *contained_iter;
			ir_named_objects_.remove ( contained );
			contained -> _remove_ref();
			return true;
		}
	} 

	return false;
}

bool
Repository_impl::remove_anonymous
( IRObject_impl* anonymous )
{
	list < IRObject_impl* >::const_iterator anonymous_iter;

	for ( anonymous_iter = ir_anonymous_objects_.begin();
			anonymous_iter != ir_anonymous_objects_.end();
			anonymous_iter++ )
	{
		if ( (*anonymous_iter) == anonymous )
		{
			DEBUG_OUTLINE ( "Repository_impl::remove_anonymous(...): object found" );
			ir_anonymous_objects_.remove ( *anonymous_iter );
			anonymous -> _remove_ref();
			return true;
		}
	}

	DEBUG_OUTLINE ( "Repository_impl::remove_anonymous(...): object not found" );

	return false;
}

Contained_impl*
Repository_impl::resolve_id
( const char *id )
{
	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = ir_named_objects_.begin();
			contained_iter != ir_named_objects_.end();
			contained_iter++ )
	{
		if ( !strcmp ( (*contained_iter) -> id(), id ) )
			return ( *contained_iter );
	}

	return NULL;
}


void
Repository_impl::destroy
()
throw(CORBA::SystemException)
{
	// Not allowed
	DEBUG_ERRLINE ( "*** destroy() on Repository called" );
	throw CORBA::BAD_INV_ORDER ( 2, CORBA::COMPLETED_NO );
}

IR__::Contained_ptr
Repository_impl::lookup_id
(const char* search_id)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::lookup_id() called" );
	
	if ( !check_for_id ( search_id ) )
		return IR__::Contained::_nil();
	
	Contained_impl *contained = resolve_id ( search_id );
	return contained -> _this();
}

CORBA::TypeCode_ptr
Repository_impl::get_canonical_typecode
(CORBA::TypeCode_ptr tc)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::get_canonical_typecode() called" );
	// TODO
	throw CORBA::NO_IMPLEMENT();
}

IR__::PrimitiveDef_ptr
Repository_impl::get_primitive
(IR__::PrimitiveKind kind)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::get_primitive() called" );
	switch ( kind )
	{
	case IR__::pk_void : return pd_void_ -> _this(); break;
	case IR__::pk_short : return pd_short_ -> _this(); break;
	case IR__::pk_long : return pd_long_ -> _this(); break;
	case IR__::pk_ushort : return pd_ushort_ -> _this(); break;
	case IR__::pk_ulong : return pd_ulong_ -> _this(); break;
	case IR__::pk_float : return pd_float_ -> _this(); break;
	case IR__::pk_double : return pd_double_ -> _this(); break;
	case IR__::pk_boolean : return pd_boolean_ -> _this(); break;
	case IR__::pk_char : return pd_char_ -> _this(); break;
	case IR__::pk_octet : return pd_octet_ -> _this(); break;
	case IR__::pk_any : return pd_any_ -> _this(); break;
	case IR__::pk_TypeCode : return pd_TypeCode_ -> _this(); break;
	case IR__::pk_Principal : return pd_Principal_ -> _this(); break;
	case IR__::pk_string : return pd_string_ -> _this(); break;
	case IR__::pk_objref : return pd_objref_ -> _this(); break;
	case IR__::pk_longlong : return pd_longlong_ -> _this(); break;
	case IR__::pk_ulonglong : return pd_ulonglong_ -> _this(); break;
	case IR__::pk_longdouble : return pd_longdouble_ -> _this(); break;
	case IR__::pk_wchar : return pd_wchar_ -> _this(); break;
	case IR__::pk_wstring : return pd_wstring_ -> _this(); break;
	case IR__::pk_value_base : return pd_value_base_ -> _this(); break;
	}
	throw CORBA::BAD_PARAM();
}

IR__::StringDef_ptr
Repository_impl::create_string
(CORBA::ULong bound)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::create_string() called" );
	StringDef_impl *new_string = new StringDef_impl ( this );

	new_string -> bound ( bound );
	ir_anonymous_objects_.push_back ( new_string );
	new_string -> _add_ref();
	return new_string -> _this();
}

IR__::WstringDef_ptr
Repository_impl::create_wstring
(CORBA::ULong bound)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::create_wstring() called" );
	WstringDef_impl *new_wstring = new WstringDef_impl ( this );

	new_wstring -> bound ( bound );
	ir_anonymous_objects_.push_back ( new_wstring );
	new_wstring -> _add_ref();
	return new_wstring -> _this();
}

IR__::SequenceDef_ptr
Repository_impl::create_sequence
(CORBA::ULong bound,
 IR__::IDLType_ptr element_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::create_sequence() called" );
	SequenceDef_impl *new_sequence = new SequenceDef_impl ( this );

	new_sequence -> bound ( bound );
	new_sequence -> element_type_def ( element_type );
	ir_anonymous_objects_.push_back ( new_sequence );
	new_sequence -> _add_ref();
	return new_sequence -> _this();
}

IR__::ArrayDef_ptr
Repository_impl::create_array
(CORBA::ULong length,
 IR__::IDLType_ptr element_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::create_array() called" );
	ArrayDef_impl *new_array = new ArrayDef_impl ( this );

	new_array -> length ( length );
	new_array -> element_type_def ( element_type );
	ir_anonymous_objects_.push_back ( new_array );
	new_array -> _add_ref();
	return new_array -> _this();
}

IR__::FixedDef_ptr
Repository_impl::create_fixed
(CORBA::UShort digits,
 CORBA::Short scale)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Repository_impl::create_fixed() called" );
	FixedDef_impl *new_fixed = new FixedDef_impl ( this );

	new_fixed -> digits ( digits );
	new_fixed -> scale ( scale );
	ir_anonymous_objects_.push_back ( new_fixed );
	new_fixed -> _add_ref();
	return new_fixed -> _this();
}

} // namespace QEDO_ComponentRepository

