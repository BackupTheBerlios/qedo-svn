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

#include "Sink_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

SinkDef_impl::SinkDef_impl
( Container_impl *container,
  Repository_impl *repository,
  StreamTypeDef_impl *stream_type_impl )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository ),
  StreamPortDef_impl ( container, repository, stream_type_impl )
{
	DEBUG_OUTLINE ( "ConsumesDef_impl::ConsumesDef_impl() called" );
}

SinkDef_impl::~SinkDef_impl
()
{
	DEBUG_OUTLINE ( "ConsumesDef_impl::~ConsumesDef_impl() called" );
}

void
SinkDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ConsumesDef_impl::destroy() called" );

	StreamPortDef_impl::destroy();
}

} // namespace QEDO_ComponentRepository
