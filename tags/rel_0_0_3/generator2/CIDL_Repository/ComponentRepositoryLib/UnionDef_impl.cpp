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

#include "UnionDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

UnionDef_impl::UnionDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  Container_impl ( repository ),
  IDLType_impl ( repository ),
  Contained_impl ( container, repository ),
  TypedefDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "UnionDef_impl::UnionDef_impl() called" );

	discriminator_type_impl_ = NULL;
}

UnionDef_impl::~UnionDef_impl
()
{
	DEBUG_OUTLINE ( "UnionDef_impl::~UnionDef_impl() called" );
}

CORBA::TypeCode_ptr
UnionDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
	//
    // A union can be recursive even without a sequence, so check
    // for recursion first. For example:
    //
    // struct S
    // {
    //     union U switch(boolean)
    //     {
    //         case TRUE: sequence<S> seq;
    //     };
    // };
    // This is from ORBacus
    unsigned int i;
    for ( i = 0 ; i < seq.size() ; i++ )
    {
		IR__::RepositoryId_var id2 = seq[i] -> id();
        if ( strcmp(id_, id2 ) == 0 )
            return repository_ -> orb() -> create_recursive_tc ( id_ );
    }

    seq.resize ( seq.size() + 1 );
    seq[seq.size() - 1] = this;

    //
    // Recalculate TypeCodes every time, as ids may have changed, and
    // also in order to calculate recursive TypeCodes correctly.
    // This is from ORBacus
    for ( i = 0 ; i < member_impls_.size() ; i++ )
        members_[i].type = member_impls_[i] -> build_recursive_type_code ( seq );

    seq.resize ( seq.size() - 1, NULL );
	CORBA::TypeCode_var discriminator_type_code =
		CORBA::TypeCode::_duplicate ( discriminator_type() );

	// TODO: this is a hack because create_union_tc needs a sequence
	// from the CORBA module and we know that the both types are
	// exactly the same
	CORBA::UnionMemberSeq* members_new = (CORBA::UnionMemberSeq*)&members_;

    return repository_ -> orb() -> create_union_tc ( 
		id_, name_, discriminator_type_code, *members_new );
}

void
UnionDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::destroy() called" );

    if ( discriminator_type_impl_ )
    {
        discriminator_type_impl_ -> _remove_ref();
    }

    for ( unsigned int i = 0 ; i < member_impls_.size() ; i++ )
        member_impls_[i] -> _remove_ref();

	Container_impl::destroy();
    Contained_impl::destroy();
}

CORBA::TypeCode_ptr
UnionDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::type() called" );

    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var tc = build_recursive_type_code(helper_seq);
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    return tc._retn();
}

CORBA::TypeCode_ptr
UnionDef_impl::discriminator_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::discriminator_type() called" );

    if ( !discriminator_type_impl_ )
        throw CORBA::BAD_INV_ORDER();

    return discriminator_type_impl_ -> type();
}

IR__::IDLType_ptr
UnionDef_impl::discriminator_type_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::discriminator_type_def() called" );

    if ( !discriminator_type_impl_ )
        throw CORBA::BAD_INV_ORDER();

    return discriminator_type_impl_ -> _this();
}

void
UnionDef_impl::discriminator_type_def
(IR__::IDLType_ptr discriminator_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::discriminator_type_def(...) called" );

    if ( CORBA::is_nil ( discriminator_type ) )
        throw CORBA::BAD_PARAM(); // Is this exception correct?

    IDLType_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant = 
			repository_ -> poa() -> reference_to_servant ( discriminator_type );
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if ( !impl )
    {
        // Must be same repository
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
    }

    impl -> _add_ref();

    if ( discriminator_type_impl_ )
        discriminator_type_impl_ -> _remove_ref();
    
	discriminator_type_impl_ = impl;
}

IR__::UnionMemberSeq*
UnionDef_impl::members
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::members() called" );

    //
    // Recalculate TypeCodes every time, as ids may have changed, and
    // also in order to calculate recursive TypeCodes correctly.
    // This is from ORBacus
    for ( unsigned int i = 0 ; i < member_impls_.size() ; i++ )
    {
        vector < Contained_impl* > helper_seq;
        members_[i].type = member_impls_[i] -> build_recursive_type_code ( helper_seq );
		if ( helper_seq.size() != 0 )
			throw CORBA::BAD_INV_ORDER();	// Is this correct?
    }

    return new IR__::UnionMemberSeq ( members_ );
}

void
UnionDef_impl::members
(const IR__::UnionMemberSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "UnionDef_impl::members(...) called" );

    unsigned int i;

    //
    // No test for duplicate declarator names, because there may be
    // several members which have the same declarator but different
    // labels. For example:
    //
    // union U switch(long)
    // {
    // case 0:
    // case 1: char c;
    // };
    // This is from ORBacus

    vector < IDLType_impl* > impl_seq;
    impl_seq.resize ( seq.length() );

    for ( i = 0 ; i < seq.length() ; i++ )
    {
        if ( strlen ( seq[i].name ) == 0 )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        // No check for name collision in the comtainer scope
		// TODO !!!

        // Check for name redefinition in an immediate scope
        if ( strcmp ( seq[i].name, name_ ) == 0 )
            throw CORBA::BAD_PARAM ( 7,	CORBA::COMPLETED_NO);

        if ( CORBA::is_nil ( seq[i].type_def ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        impl_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
                repository_ -> poa() -> reference_to_servant ( seq[i].type_def );
            impl_seq[i] = dynamic_cast<IDLType_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if(!impl_seq[i])
        {
            // Must be same repository
            throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
        }
    }

    // Check for illegal recursion
    for ( i = 0 ; i < seq.length() ; i++ )
        check_recursion ( id_, seq[i].type );

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0 ; i < member_impls_.size() ; i++ )
        member_impls_[i] -> _remove_ref();

    member_impls_ = impl_seq;
    members_ = seq;
}

} // namespace QEDO_ComponentRepository