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

#include "EnumDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

EnumDef_impl::EnumDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Contained_impl ( container, repository ),
  TypedefDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "EnumDef_impl::EnumDef_impl() called" );
}

EnumDef_impl::~EnumDef_impl
()
{
	DEBUG_OUTLINE ( "EnumDef_impl::~EnumDef_impl() called" );
}

void
EnumDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EnumDef_impl::destroy() called" );

	TypedefDef_impl::destroy();
}

CORBA::TypeCode_ptr
EnumDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EnumDef_impl::type() called" );

	// TODO: this is a hack because create_enum_tc needs a sequence
	// from the CORBA module and we know that the both types are
	// exactly the same
	CORBA::EnumMemberSeq* members_new = (CORBA::EnumMemberSeq*)&members_;

    return repository_ -> orb() -> create_enum_tc ( id_, name_, *members_new );
}

IR__::EnumMemberSeq*
EnumDef_impl::members
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EnumDef_impl::members() called" );

    return new IR__::EnumMemberSeq(members_);
}

void
EnumDef_impl::members
(const IR__::EnumMemberSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "EnumDef_impl::members(...) called" );

    unsigned int i;

    // Check for name collision
    for ( i = 0 ; i < seq.length() ; i++ )
        for ( unsigned int j = i + 1 ; j < seq.length() ; j++ )
            if ( strcmp ( seq[i], seq[j] ) == 0 )
                throw CORBA::BAD_PARAM ( 1, CORBA::COMPLETED_NO );

    for ( i = 0 ; i < seq.length() ; i++ )
    {
        if ( strlen(seq[i]) == 0 )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        // TODO: Check for duplicate names in inherited scope
		// defined_in_ -> check_name...
    }

    members_ = seq;
}

} // namespace QEDO_ComponentRepository