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

#include "PSSPrimaryKeyDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

PSSPrimaryKeyDef_impl::PSSPrimaryKeyDef_impl
( Container_impl *container,
  Repository_impl *repository,
  IDLType_impl *key_idltype_impl )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "PSSPrimaryKeyDef_impl::PSSPrimaryKeyDef_impl() called" );

	key_idltype_impl_ = key_idltype_impl;
	key_idltype_impl_ -> _add_ref();
}

PSSPrimaryKeyDef_impl::~PSSPrimaryKeyDef_impl
()
{
	DEBUG_OUTLINE ( "PSSPrimaryKeyDef_impl::~PSSPrimaryKeyDef_impl() called" );
}

void
PSSPrimaryKeyDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSPrimaryKeyDef_impl::destroy() called" );

	key_idltype_impl_ -> _add_ref();

	Contained_impl::destroy();
}

IR__::Contained::Description*
PSSPrimaryKeyDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSPrimaryKeyDef_impl::describe() called" );

	IR__::PSSPrimaryKeyDescription_var key_desc = new IR__::PSSPrimaryKeyDescription;
	key_desc -> id = this -> id();;
	key_desc -> name = this -> name();
	key_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		key_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		key_desc -> defined_in = CORBA::string_dup ( "" );

	key_desc -> primary_key = key_idltype_impl_ -> _this();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= key_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

CORBA::Boolean
PSSPrimaryKeyDef_impl::is_a
(const char* primary_key_id)
throw(CORBA::SystemException)
{
	IR__::Contained_var primary_key_impl;

	primary_key_impl = repository_ -> lookup_id ( primary_key_id );

	if ( CORBA::is_nil ( primary_key_impl ) )
		throw CORBA::BAD_PARAM();	// Is this exception correct ?

	return this -> is_a ( primary_key_impl -> id() );
}

IR__::IDLType_ptr
PSSPrimaryKeyDef_impl::primary_key
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSPrimaryKeyDef_impl::primary_key() called" );

	return key_idltype_impl_ -> _this();
}

} // namespace QEDO_ComponentRepository

