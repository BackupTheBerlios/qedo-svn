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

#include "StreamPortDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

StreamPortDef_impl::StreamPortDef_impl
( Container_impl *container,
  Repository_impl *repository,
  StreamTypeDef_impl *stream_type_impl )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "EventDef_impl::EventDef_impl() called" );

	stream_type_impl_ = stream_type_impl;
	stream_type_impl_ -> _add_ref();
}

StreamPortDef_impl::~StreamPortDef_impl
()
{
	DEBUG_OUTLINE ( "EventDef_impl::~EventDef_impl() called" );
}
    
void
StreamPortDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::destroy() called" );

	stream_type_impl_ -> _remove_ref();

	Contained_impl::destroy();
}

IR__::Contained::Description*
StreamPortDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::describe() called" );

	IR__::StreamPortDescription_var stream_port_desc = new IR__::StreamPortDescription;
	stream_port_desc -> id = this -> id();
	stream_port_desc -> name = this -> name();
	stream_port_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		stream_port_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		stream_port_desc -> defined_in = CORBA::string_dup ( "" );
	stream_port_desc -> stream_type = stream_type_impl_ -> _this();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= stream_port_desc._retn();;
	desc -> value = any;

	return desc._retn();

}

CORBA::Boolean
StreamPortDef_impl::is_a
(const char* id)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StreamPortDef_impl::is_a() called" );

//	return stream_type_impl_ -> is_a ( id );
	return false;
}

IR__::StreamTypeDef_ptr
StreamPortDef_impl::stream_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EventDef_impl::event() called" );

	return 	stream_type_impl_ -> _this();
}

} // namespace QEDO_ComponentRepository
