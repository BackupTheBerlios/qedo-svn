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

#include "CIDLRepository_impl.h"
#include "Debug.h"
#include "HomeDef_impl.h"
#include "CompositionDef_impl.h"

namespace QEDO_ComponentRepository {

CIDLRepository_impl::CIDLRepository_impl
( CORBA::ORB_ptr orb, PortableServer::POA_ptr poa )
: IRObject_impl ( this ),
  Container_impl ( this ),
  Repository_impl ( orb, poa ),
  ComponentRepository_impl ( orb, poa )
{
	DEBUG_OUTLINE ( "CIDLRepository_impl::CIDLRepository_impl() called" );
}

CIDLRepository_impl::~CIDLRepository_impl
()
{
	DEBUG_OUTLINE ( "CIDLRepository_impl::~CIDLRepository_impl() called" );
}

void
CIDLRepository_impl::destroy_repository
()
{
	DEBUG_OUTLINE ( "CIDLRepository_impl::destroy() called" );

//	ComponentRepository_impl::destroy_repository();
}

CIDL::CompositionDef_ptr
CIDLRepository_impl::create_composition
(const char* id,
 const char* name,
 const char* version,
 CIDL::LifecycleCategory lifecycle,
 IR__::HomeDef_ptr home)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CIDLRepository_impl::create_composition() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

    HomeDef_impl* impl = 0;

	// Test the home
	if ( CORBA::is_nil ( home ) )
		throw CORBA::BAD_PARAM();

	try
	{
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( home );
		impl = dynamic_cast<HomeDef_impl*>(servant.in());
	}
	catch(...)
	{
	}
	if(!impl)
	{
		// Must be same repository
		throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
	}

	CompositionDef_impl *new_composition =
		new CompositionDef_impl ( this, repository_, lifecycle, impl );

	new_composition -> id ( id );
	new_composition -> name ( name );
	new_composition -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_composition -> _this();
}

} // namespace QEDO_ComponentRepository

