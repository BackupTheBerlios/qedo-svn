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

#include "ProvidesDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ProvidesDef_impl::ProvidesDef_impl
( Container_impl *container,
  Repository_impl *repository,
  IDLType_impl* interface_type_impl )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "ProvidesDef_impl::ProvidesDef_impl() called" );

	interface_type_impl_ = interface_type_impl;
	interface_type_impl_ -> _add_ref();
}

ProvidesDef_impl::~ProvidesDef_impl
()
{
	DEBUG_OUTLINE ( "ProvidesDef_impl::~ProvidesDef_impl() called" );
}

void
ProvidesDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ProvidesDef_impl::destroy() called" );

	interface_type_impl_ -> _remove_ref();

	Contained_impl::destroy();
}

IR__::Contained::Description*
ProvidesDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ProvidesDef_impl::describe() called" );

	IR__::ProvidesDescription_var provides_desc = new IR__::ProvidesDescription;
	provides_desc -> id = this -> id();
	provides_desc -> name = this -> name();
	provides_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		provides_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		provides_desc -> defined_in = CORBA::string_dup ( "" );
	provides_desc -> interface_type = interface_type_impl_ -> _this();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= provides_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::IDLType_ptr
ProvidesDef_impl::interface_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ProvidesDef_impl::interface_type() called" );

	return interface_type_impl_ -> _this();
}

} // namespace QEDO_ComponentRepository
