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

#include "AliasDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

AliasDef_impl::AliasDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Contained_impl ( container, repository ),
  TypedefDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "AliasDef_impl::AliasDef_impl() called" );

	original_idl_type_impl_ = NULL;
}

AliasDef_impl::~AliasDef_impl
()
{
	DEBUG_OUTLINE ( "AliasDef_impl::~AliasDef_impl() called" );
}

CORBA::TypeCode_ptr
AliasDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
    if ( !original_idl_type_impl_ )
        throw CORBA::BAD_INV_ORDER();

    Contained_impl* contained = dynamic_cast<Contained_impl*>(original_idl_type_impl_);
    if ( contained )
    {
		IR__::RepositoryId_var id = contained -> id();
        for ( unsigned int i = 0 ; i < seq.size() ; i++ )
        {
			IR__::RepositoryId_var id2 = seq[i] -> id();
            if ( strcmp ( id, id2 ) == 0 )
            {
				CORBA__::DefinitionKind element_def_kind = contained -> def_kind();
                if(element_def_kind != CORBA__::dk_Struct &&
                   element_def_kind != CORBA__::dk_Exception &&
                   element_def_kind != CORBA__::dk_Union &&
                   element_def_kind != CORBA__::dk_Value &&
                   element_def_kind != CORBA__::dk_Alias)
                {
                    throw CORBA::INTF_REPOS ( 3, CORBA::COMPLETED_NO );
                }
            }
        }
    }

	CORBA::TypeCode_var tc = original_idl_type_impl_ -> build_recursive_type_code ( seq );

    return repository_ -> orb() -> create_alias_tc ( id_, name_, tc );
}

void
AliasDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AliasDef_impl::destroy() called" );

	if ( original_idl_type_impl_ )
		original_idl_type_impl_ -> _remove_ref();

	TypedefDef_impl::destroy();
}

CORBA::TypeCode_ptr
AliasDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AliasDef_impl::type() called" );

    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var tc = build_recursive_type_code(helper_seq);
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    return tc._retn();
}

IR__::IDLType_ptr
AliasDef_impl::original_type_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AliasDef_impl::original_type_def() called" );

    if ( !original_idl_type_impl_ )
        throw CORBA::BAD_INV_ORDER();

    return original_idl_type_impl_ -> _this();
}

void
AliasDef_impl::original_type_def
(IR__::IDLType_ptr original_idl_type )
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AliasDef_impl::original_type_def(...) called" );

    if ( CORBA::is_nil ( original_idl_type ) )
        throw CORBA::BAD_PARAM(); // Is this exception correct?

    IDLType_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant = 
			repository_ -> poa() -> reference_to_servant ( original_idl_type );
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

    impl -> _add_ref();
    
	if ( original_idl_type_impl_ )
        original_idl_type_impl_ -> _remove_ref();

    original_idl_type_impl_ = impl;
}

} // namespace QEDO_ComponentRepository

