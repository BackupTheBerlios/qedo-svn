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

#include "EventPortDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

EventPortDef_impl::EventPortDef_impl
( Container_impl *container,
  Repository_impl *repository,
  EventDef_impl *event_type_impl )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "EventDef_impl::EventDef_impl() called" );

	event_type_impl_ = event_type_impl;
	event_type_impl_ -> _add_ref();
}

EventPortDef_impl::~EventPortDef_impl
()
{
	DEBUG_OUTLINE ( "EventDef_impl::~EventDef_impl() called" );
}
    
void
EventPortDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::destroy() called" );

	event_type_impl_ -> _remove_ref();

	Contained_impl::destroy();
}

IR__::Contained::Description*
EventPortDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::describe() called" );

	IR__::EventDescription_var event_desc = new IR__::EventDescription;
	event_desc -> id = this -> id();
	event_desc -> name = this -> name();
	event_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		event_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		event_desc -> defined_in = CORBA::string_dup ( "" );
	event_desc -> value = event_type_impl_ -> _this();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= event_desc._retn();;
	desc -> value = any;

	return desc._retn();

}

CORBA::Boolean
EventPortDef_impl::is_a
(const char* id)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::is_a() called" );

	return event_type_impl_ -> is_a ( id );
}

IR__::EventDef_ptr
EventPortDef_impl::event
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::event() called" );

	return 	event_type_impl_ -> _this();
}

} // namespace QEDO_ComponentRepository