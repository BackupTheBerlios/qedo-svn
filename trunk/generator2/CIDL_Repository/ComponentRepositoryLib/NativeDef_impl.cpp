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

#include "NativeDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

NativeDef_impl::NativeDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Contained_impl ( container, repository ),
  TypedefDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "NativeDef_impl::NativeDef_impl() called" );
}

NativeDef_impl::~NativeDef_impl
()
{
	DEBUG_OUTLINE ( "NativeDef_impl::~NativeDef_impl() called" );
}

void
NativeDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "NativeDef_impl::destroy() called" );

	TypedefDef_impl::destroy();
}

CORBA::TypeCode_ptr
NativeDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "NativeDef_impl::type() called" );

    return repository_ -> orb() -> create_native_tc ( id_, name_ );
}

} // namespace QEDO_ComponentRepository