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

#include "UsesCatalogDef_impl.h"
#include "Debug.h"


namespace QEDO_ComponentRepository {

UsesCatalogDef_impl::UsesCatalogDef_impl
( Container_impl *container,
  Repository_impl *repository )
: Contained_impl ( container, repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::UsesCatalogDef_impl() called" );
}

UsesCatalogDef_impl::~UsesCatalogDef_impl
()
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::~UsesCatalogDef_impl() called" );
}

void
UsesCatalogDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::destroy() called" );

	Contained_impl::destroy();
}

IR__::Contained::Description*
UsesCatalogDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::describe() called" );

	CIDL::UsesCatalogDefDescription_var uses_catalog_def_desc = new CIDL::UsesCatalogDefDescription;
	uses_catalog_def_desc -> id = this -> id();
	uses_catalog_def_desc -> name = this -> name();
	uses_catalog_def_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		uses_catalog_def_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		uses_catalog_def_desc -> defined_in = CORBA::string_dup ( "" );

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= uses_catalog_def_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::CatalogDef_ptr
UsesCatalogDef_impl::catalog_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::catalog_type() called" );
	return IR__::CatalogDef::_duplicate(catalog_def_);
}

void
UsesCatalogDef_impl::catalog_type
(IR__::CatalogDef_ptr catalog_def)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::catalog_type(...) called" );
	catalog_def_ = catalog_def;
}

IR__::Identifier
UsesCatalogDef_impl::catalog_label
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::catalog_label() called" );
	throw CORBA::BAD_PARAM();
}

void 
UsesCatalogDef_impl::catalog_label
(const char* str_label)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UsesCatalogDef_impl::catalog_label(...) called" );
	str_label_ = CORBA::string_dup ( str_label );
}

} // namespace QEDO_ComponentRepository