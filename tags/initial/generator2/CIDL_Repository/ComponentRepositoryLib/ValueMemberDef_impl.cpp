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

#include "ValueMemberDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ValueMemberDef_impl::ValueMemberDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::ValueMemberDef_impl() called" );

	type_impl_ = NULL;
}

ValueMemberDef_impl::~ValueMemberDef_impl
()
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::~ValueMemberDef_impl() called" );
}

CORBA::TypeCode_ptr
ValueMemberDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
    if ( !type_impl_ )
        throw CORBA::BAD_INV_ORDER();

	CORBA::TypeCode_var tc;

    Contained_impl* contained = dynamic_cast<Contained_impl*>(type_impl_);
    if ( contained )
    {
		IR__::RepositoryId_var id = contained -> id();
        for ( unsigned int i = 0 ; i < seq.size() ; i++ )
        {
			IR__::RepositoryId_var id2 = seq[i] -> id();
            if ( strcmp ( id, id2 ) == 0 )
                tc = repository_ -> orb() -> create_recursive_tc ( id );
        }
    }

    if ( CORBA::is_nil ( tc ) )
        tc = type_impl_ -> build_recursive_type_code ( seq );

    return tc._retn();
}

void
ValueMemberDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::destroy() called" );

    if ( type_impl_ )
        type_impl_ -> _remove_ref();

    Contained_impl::destroy();
}

IR__::Contained::Description*
ValueMemberDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::describe() called" );

	IR__::ValueMember_var value_member_desc = new IR__::ValueMember;

    value_member_desc -> name = this -> name();
    value_member_desc -> id = this -> id();
    value_member_desc -> version = this -> version();

    Contained_impl* contained = dynamic_cast<Contained_impl*>(defined_in_);
    if(contained)
        value_member_desc -> defined_in = contained -> id();
    else
        value_member_desc -> defined_in = CORBA::string_dup("");

    value_member_desc -> type = this -> type();
    value_member_desc -> type_def = this -> type_def();
    value_member_desc -> access = this -> access();

    IR__::Contained::Description_var desc = new IR__::Contained::Description;
    desc -> kind = def_kind();
    desc -> value <<= desc._retn();

    return desc._retn();
}

CORBA::TypeCode_ptr
ValueMemberDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::type() called" );

    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var tc = build_recursive_type_code ( helper_seq );
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    
	return tc._retn();
}

IR__::IDLType_ptr
ValueMemberDef_impl::type_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::type_def() called" );

    if ( !type_impl_ )
        throw CORBA::BAD_INV_ORDER();

    return type_impl_ -> _this();
}

void
ValueMemberDef_impl::type_def
(IR__::IDLType_ptr idl_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::type_def(...) called" );

    if ( CORBA::is_nil ( idl_type ) )
        throw CORBA::BAD_PARAM(); // Is this exception correct?

    IDLType_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant(idl_type);
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
    }

    impl -> _add_ref();

    if(type_impl_)
        type_impl_ -> _remove_ref();

    type_impl_ = impl;
}

CORBA__::Visibility
ValueMemberDef_impl::access
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::access() called" );

	return access_;
}

void
ValueMemberDef_impl::access
(CORBA__::Visibility access)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueMemberDef_impl::access(...) called" );

	access_ = access;
}

} // namespace QEDO_ComponentRepository