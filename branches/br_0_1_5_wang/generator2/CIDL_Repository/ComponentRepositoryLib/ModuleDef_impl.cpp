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

#include "ModuleDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ModuleDef_impl::ModuleDef_impl
( Container_impl *container,
  Repository_impl *repository
)
: Contained_impl ( container, repository ),
  Container_impl ( repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "ModuleDef_impl::ModuleDef_impl() called" );
}

ModuleDef_impl::~ModuleDef_impl
()
{
	DEBUG_OUTLINE ( "ModuleDef_impl::~ModuleDef_impl() called" );
}

void
ModuleDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ModuleDef_impl::destroy() called" );

	Container_impl::destroy();
	Contained_impl::destroy();
}

IR__::Contained::Description*
ModuleDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ModuleDef_impl::describe() called" );
	
	IR__::ModuleDescription_var module_desc = new IR__::ModuleDescription;
	module_desc -> id = this -> id();
	module_desc -> name = this -> name();
	module_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		module_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		module_desc -> defined_in = CORBA::string_dup ( "" );

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= module_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

} // namespace QEDO_ComponentRepository
