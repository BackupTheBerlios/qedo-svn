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

#include "CatalogDef_impl.h"
#include "ProvidesDef_impl.h"
#include "Debug.h"


namespace QEDO_ComponentRepository {

CatalogDef_impl::CatalogDef_impl
( Container_impl *container, Repository_impl *repository )

: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository ),
  InterfaceDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "CatalogDef_impl::CatalogDef_impl() called" );
}

CatalogDef_impl::~CatalogDef_impl
()
{
	DEBUG_OUTLINE ( "CatalogDef_impl::~CatalogDef_impl() called" );
}

void
CatalogDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CatalogDef_impl::destroy() called" );

    Contained_impl::destroy();
}

IR__::Contained::Description*
CatalogDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CatalogDef_impl::describe() called" );

	IR__::CatalogDescription_var catalog_desc = new IR__::CatalogDescription;
	catalog_desc -> id = this -> id();
	catalog_desc -> name = this -> name();
	catalog_desc -> version = this -> version();

	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		catalog_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		catalog_desc -> defined_in = CORBA::string_dup ( "" );	

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		// Provides
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Provides )
		{
			ProvidesDef_impl *impl;
			impl = dynamic_cast < ProvidesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Provides' cannot be casted to ProvidesDef_impl" );
				continue;
			}
			catalog_desc -> provides_interfaces.length (
				catalog_desc -> provides_interfaces.length() + 1 );
			catalog_desc -> 
				provides_interfaces [ catalog_desc -> provides_interfaces.length() - 1 ] =
					impl -> _this();
		}
	}

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	desc -> value <<= catalog_desc._retn();

	return desc._retn();
}

IR__::ProvidesDef_ptr
CatalogDef_impl::create_provides
(const char* id,
 const char* name,
 const char* version,
 IR__::InterfaceDef_ptr interface_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CatalogDef_impl::create_provides() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( interface_type ) )
		throw CORBA::BAD_PARAM();		// Is this correct?

    InterfaceDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( interface_type );
        impl = dynamic_cast<InterfaceDef_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

	ProvidesDef_impl *new_provides = new ProvidesDef_impl ( this, repository_, impl );
	new_provides -> id ( id );
	new_provides -> name ( name );
	new_provides -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_provides -> _this();
}

IR__::ProvidesDefSeq*
CatalogDef_impl::provides_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CatalogDef_impl::provides_interfaces() called" );

	IR__::ProvidesDefSeq_var provides_seq = new IR__::ProvidesDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;

	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Provides )
		{
			ProvidesDef_impl *impl;
			impl = dynamic_cast < ProvidesDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Provides' cannot be casted to ProvidesDef_impl" );
				continue;
			}
			provides_seq -> length ( provides_seq -> length() + 1 );
			provides_seq [ provides_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return provides_seq._retn();
}

} // namespace QEDO_ComponentRepository
