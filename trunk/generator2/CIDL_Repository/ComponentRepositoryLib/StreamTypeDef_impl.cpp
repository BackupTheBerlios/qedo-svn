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

#include "StreamTypeDef_impl.h"
#include "Repository_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

StreamTypeDef_impl::StreamTypeDef_impl
( Container_impl *container, Repository_impl *repository )
: IDLType_impl ( repository ),
	IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "PrimitiveDef_impl::PrimitiveDef_impl() called " );
}

StreamTypeDef_impl::~StreamTypeDef_impl
()
{
	DEBUG_OUTLINE ( "PrimitiveDef_impl::~PrimitiveDef_impl() called " );
}

void
StreamTypeDef_impl::destroy_from_repository
()
{
	DEBUG_OUTLINE ( "PrimitiveDef_impl::destroy() called" );
	IDLType_impl::destroy();
	this -> _remove_ref();
}

void
StreamTypeDef_impl::destroy
()
throw(CORBA::SystemException)
{
	throw CORBA::BAD_INV_ORDER ( 2, CORBA::COMPLETED_NO );
}


IR__::Contained::Description*
StreamTypeDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StreamTypeDef_impl::describe() called" );


	IR__::StreamTypeDescription_var stream_type_desc = new IR__::StreamTypeDescription;

    stream_type_desc -> id = this -> id();
    stream_type_desc -> name = this -> name();
    stream_type_desc -> version = this -> version();

    Contained_impl* contained = dynamic_cast<Contained_impl*>(defined_in_);
    if(contained)
        stream_type_desc -> defined_in = contained -> id();
    else
        stream_type_desc -> defined_in = CORBA::string_dup("");

//	stream_type_desc -> type = this -> type();

    IR__::Contained::Description_var desc = new IR__::Contained::Description;

    desc -> kind = def_kind();
    desc -> value <<= stream_type_desc._retn();

    return desc._retn();
}
CORBA::TypeCode_ptr
StreamTypeDef_impl::type
()
throw(CORBA::SystemException)
{
        return CORBA::TypeCode::_duplicate(CORBA::_tc_null);
}

IR__::IDLType_ptr 
StreamTypeDef_impl::transported_type
()
throw(CORBA::SystemException)
{
	return IR__::IDLType::_duplicate (transported_type_);
}

void 
StreamTypeDef_impl::transported_type
(IR__::IDLType_ptr transported_type)
throw(CORBA::SystemException)
{
	transported_type_ = IR__::IDLType::_duplicate (transported_type);
}


IR__::StreamTypeDefSeq* 
StreamTypeDef_impl::grouped_types()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StreamTypeDef_impl::grouped_types() called" );

	IR__::StreamTypeDefSeq_var type_seq = new IR__::StreamTypeDefSeq;
    type_seq -> length ( grouped_types_.size() );
    for ( unsigned int i = 0; i < type_seq -> length(); i++ )
        type_seq.inout()[i] = grouped_types_[i] -> _this();
    return type_seq._retn();
}


void 
StreamTypeDef_impl::grouped_types (const IR__::StreamTypeDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StreamTypeDef_impl::grouped_types(...) called" );

    vector < StreamTypeDef_impl* > type_seq;
    type_seq.resize ( seq.length(), NULL );

    unsigned i;

    for ( i = 0; i < seq.length(); i++ )
    {
        if ( CORBA::is_nil ( seq[i].in() ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?
        type_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(seq[i].in());
            type_seq[i] = dynamic_cast<StreamTypeDef_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if(!type_seq[i])
        {
            // Must be same repository
            throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
        }
    }

    for ( i = 0; i < type_seq.size(); i++ )
        type_seq[i] -> _add_ref();

    for ( i = 0; i < grouped_types_.size(); i++)
        grouped_types_[i] -> _remove_ref();

    grouped_types_ = type_seq;
}


} // namespace QEDO_ComponentRepository
