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

#include "TypedefDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

TypedefDef_impl::TypedefDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Contained_impl ( container, repository ) 
{
	DEBUG_OUTLINE ( "TypedefDef_impl::TypedefDef_impl() called" );
}

TypedefDef_impl::~TypedefDef_impl
()
{
	DEBUG_OUTLINE ( "TypedefDef_impl::~TypedefDef_impl() called" );
}

void
TypedefDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "TypedefDef_impl::destroy() called" );

	IDLType_impl::destroy();

}

IR__::Contained::Description*
TypedefDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "TypedefDef_impl::describe() called" );

	IR__::TypeDescription_var typedef_desc = new IR__::TypeDescription;
	typedef_desc -> id = this -> id();
	typedef_desc -> name = this -> name();
	typedef_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		typedef_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		typedef_desc -> defined_in = CORBA::string_dup ( "" );
	typedef_desc -> type = this -> type();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= typedef_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

} // namespace QEDO_ComponentRepository