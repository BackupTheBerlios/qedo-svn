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

#include "ComponentRepository_impl.h"
#include "Anonymous.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ComponentRepository_impl::ComponentRepository_impl
( CORBA::ORB_ptr orb, PortableServer::POA_ptr poa )
: IRObject_impl ( this ),
  Container_impl ( this ),
  Repository_impl ( orb, poa )
{
	DEBUG_OUTLINE ( "ComponentRepository_impl::ComponentRepository_impl() called" );
}

ComponentRepository_impl::~ComponentRepository_impl
()
{
	DEBUG_OUTLINE ( "ComponentRepository_impl::~ComponentRepository_impl() called" );
}

void
ComponentRepository_impl::destroy_repository
()
{
	Repository_impl::destroy_repository();
}

} // namespace QEDO_ComponentRepository