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

#include "ExceptionDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

ExceptionDef_impl::ExceptionDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "ExceptionDef_impl::ExceptionDef_impl() called" );
}


ExceptionDef_impl::~ExceptionDef_impl
()
{
	DEBUG_OUTLINE ( "ExceptionDef_impl::~ExceptionDef_impl() called" );
}

CORBA::TypeCode_ptr
ExceptionDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
	seq.resize(seq.size() + 1, NULL);
	seq[seq.size() - 1] = this;

	//
	// Recalculate TypeCodes every time, as ids may have changed, and
	// also in order to calculate recursive TypeCodes correctly.
	// This is from ORBacus
	for ( unsigned int i = 0 ; i < members_impls_.size() ; i++ )
		members_[i].type = members_impls_[i] -> build_recursive_type_code ( seq );

	// TODO: this is a hack because create_exception_tc needs a sequence
	// from the CORBA module and we know that the both types are
	// exactly the same
	CORBA::StructMemberSeq* members_new = (CORBA::StructMemberSeq*)&members_;

	seq.resize(seq.size() - 1, NULL);
	return repository_ -> orb() -> create_exception_tc ( id_, name_, *members_new );
}

void
ExceptionDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExceptionDef_impl::destroy() called" );

    for ( unsigned int i = 0 ; i < members_impls_.size() ; i++ )
        members_impls_[i] -> _remove_ref();

	Container_impl::destroy();
	Contained_impl::destroy();
}


IR__::Contained::Description*
ExceptionDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExceptionDef_impl::describe() called" );

	IR__::ExceptionDescription_var exception_desc = new IR__::ExceptionDescription;
	exception_desc -> id = this -> id();
	exception_desc -> name = this -> name();
	exception_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		exception_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		exception_desc -> defined_in = CORBA::string_dup ( "" );
	exception_desc -> type = type();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= exception_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

CORBA::TypeCode_ptr
ExceptionDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExceptionDef_impl::type() called" );

    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var tc = build_recursive_type_code(helper_seq);
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    return tc._retn();
}

IR__::StructMemberSeq*
ExceptionDef_impl::members
()
throw(CORBA::SystemException)
{
    //
    // Recalculate TypeCodes every time, as ids may have changed, and
    // also in order to calculate recursive TypeCodes correctly.
    // This is from ORBacus
    for ( unsigned int i = 0 ; i < members_impls_.size() ; i++ )
    {
        vector < Contained_impl* > helper_seq;
        members_[i].type = members_impls_[i] -> build_recursive_type_code ( helper_seq );
		if ( helper_seq.size() != 0 )
			throw CORBA::BAD_INV_ORDER();	// Is this correct?
    }

    return new IR__::StructMemberSeq(members_);
}

void
ExceptionDef_impl::members
(const IR__::StructMemberSeq& seq)
throw(CORBA::SystemException)
{
    unsigned int i;

    //
    // Ensure we don't have duplicate declarator names
    // This is from ORBacus
    for ( i = 0 ; i < seq.length() ; i++ )
        for ( unsigned int j = i + 1 ; j < seq.length() ; j++ )
            if ( strcmp ( seq[i].name, seq[j].name ) == 0 )
                throw CORBA::BAD_PARAM ( 1, CORBA::COMPLETED_NO );

    vector < IDLType_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );
    for ( i = 0 ; i < seq.length(); i++ )
    {
        if ( strlen ( seq[i].name ) == 0 )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        //
        // Find out whether name already exists. Note:
        // Container_impl::validateName() must be used, so that the
        // current member names are not take into account.
        // This is from ORBacus
        if ( check_for_name ( seq[i].name ) )
			throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

        //
        // Check for name redefinition in an immediate scope
        //
        if ( strcmp ( seq[i].name, name_ ) == 0 )
            throw CORBA::BAD_PARAM (7 /* is this ORBacus or standard ??? */, CORBA::COMPLETED_NO);

        if ( CORBA::is_nil ( seq[i].type_def.in() ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        impl_seq[i] = 0;

        try
        {
			PortableServer::ServantBase_var servant =
                repository_ -> poa() -> reference_to_servant ( seq[i].type_def.in() );
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

    //
    // Check for illegal recursion
    //
    for ( i = 0 ; i < seq.length() ; i++ )
        check_recursion ( id_, seq[i].type.in() );

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0 ; i < members_impls_.size() ; i++ )
        members_impls_[i] -> _remove_ref();

    members_impls_ = impl_seq;
    members_ = seq;
}

} // namespace QEDO_ComponentRepository
