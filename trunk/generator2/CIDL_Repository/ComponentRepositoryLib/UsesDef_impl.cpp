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

#include "UsesDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

UsesDef_impl::UsesDef_impl
( Container_impl *container,
  Repository_impl *repository,
  IDLType_impl* interface_type_impl,
  CORBA::Boolean is_multiple )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "UsesDef_impl::UsesDef_impl() called" );

	interface_type_impl_ = interface_type_impl;
	interface_type_impl_ -> _add_ref();

	is_multiple_ = is_multiple;
}

UsesDef_impl::~UsesDef_impl
()
{
	DEBUG_OUTLINE ( "UsesDef_impl::~UsesDef_impl() called" );
}

void
UsesDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesDef_impl::destroy() called" );

	interface_type_impl_ -> _remove_ref();

	Contained_impl::destroy();
}

IR__::Contained::Description*
UsesDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesDef_impl::describe() called" );

	IR__::UsesDescription_var uses_desc = new IR__::UsesDescription;
	uses_desc -> id = this -> id();
	uses_desc -> name = this -> name();
	uses_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		uses_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		uses_desc -> defined_in = CORBA::string_dup ( "" );
	uses_desc -> interface_type = interface_type_impl_ -> _this();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= uses_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::IDLType_ptr
UsesDef_impl::interface_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesDef_impl::interface_type() called" );

	return interface_type_impl_ -> _this();
}

CORBA::Boolean
UsesDef_impl::is_multiple
()
throw(CORBA::SystemException)
{
	return is_multiple_;
}

} // namespace QEDO_ComponentRepository

