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

#include "ConstantDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ConstantDef_impl::ConstantDef_impl
( Container_impl *container,
  Repository_impl *repository )
: Contained_impl ( container, repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "ConstantDef_impl::ConstantDef_impl() called" );

	idl_type_ = NULL;
}

ConstantDef_impl::~ConstantDef_impl
()
{
	DEBUG_OUTLINE ( "ConstantDef_impl::~ConstantDef_impl() called" );
}

void
ConstantDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ConstantDef_impl::destroy() called" );
	if ( idl_type_ )
		idl_type_ -> _remove_ref();

	Contained_impl::destroy();
}

IR__::Contained::Description*
ConstantDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ConstantDef_impl::describe() called" );

	IR__::ConstantDescription_var constant_desc = new IR__::ConstantDescription;
	constant_desc -> id = this -> id();
	constant_desc -> name = this -> name();
	constant_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		constant_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		constant_desc -> defined_in = CORBA::string_dup ( "" );
	constant_desc -> type = type();
    constant_desc -> value = value_;

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= constant_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

CORBA::TypeCode_ptr
ConstantDef_impl::type
()
{
     if(!idl_type_)
         throw CORBA::BAD_INV_ORDER();

     return idl_type_ -> type();
}

IR__::IDLType_ptr
ConstantDef_impl::type_def
()
{
    if(!idl_type_)
        throw CORBA::BAD_INV_ORDER();

    return idl_type_ -> _this();
}

void
ConstantDef_impl::type_def
(IR__::IDLType_ptr idl_type)
{
    if(CORBA::is_nil(idl_type))
        throw CORBA::BAD_PARAM();

    IDLType_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant = repository_ -> poa() -> reference_to_servant(idl_type);
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // The idl type object must be in the same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

    impl -> _add_ref();
    if(idl_type_)
        idl_type_ -> _remove_ref();
    idl_type_ = impl;
}

CORBA::Any*
ConstantDef_impl::value
()
{
    return new CORBA::Any ( value_ );
}

void
ConstantDef_impl::value
(const CORBA::Any& value)
{
    value_ = value;
}

} // namespace QEDO_ComponentRepository