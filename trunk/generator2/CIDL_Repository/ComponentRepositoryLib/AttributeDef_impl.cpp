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

#include "AttributeDef_impl.h"
#include "Debug.h"


namespace QEDO_ComponentRepository {

AttributeDef_impl::AttributeDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "AttributeDef_impl::AttributeDef_impl() called" );

	idl_type_ = NULL;
}

AttributeDef_impl::~AttributeDef_impl
()
{
	DEBUG_OUTLINE ( "AttributeDef_impl::~AttributeDef_impl() called" );
}

void
AttributeDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AtrributeDef_impl::destroy() called" );

    if ( idl_type_ )
    {
        idl_type_ -> _remove_ref();
    }

    Contained_impl::destroy();
}

IR__::Contained::Description*
AttributeDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AttrributeDef_impl::describe() called" );

	IR__::AttributeDescription_var attribute_desc = new IR__::AttributeDescription;
	attribute_desc -> id = this -> id();
	attribute_desc -> name = this -> name();
	attribute_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		attribute_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		attribute_desc -> defined_in = CORBA::string_dup ( "" );
	attribute_desc -> mode = mode_;
	attribute_desc -> type = type();

	// get exceptions
	unsigned int i;
	IR__::ExcDescriptionSeq_var exception_seq = new IR__::ExcDescriptionSeq;
	exception_seq -> length ( get_exceptions_.size() );
	for ( i = 0; i < exception_seq -> length(); i++ )
	{
		IR__::Contained::Description_var desc = get_exceptions_[i] -> describe();

		// Extract Exception description
		const IR__::ExceptionDescription *exception_desc;
		try
		{
			desc -> value >>= exception_desc;
		}
		catch (...)
		{
			// This cannot be, what to do???
			throw;
		}

		exception_seq.inout()[i] = *exception_desc;
	}

	attribute_desc -> get_exceptions = exception_seq;

	// put exceptions
	exception_seq -> length ( put_exceptions_.size() );
	for ( i = 0; i < exception_seq -> length(); i++ )
	{
		IR__::Contained::Description_var desc = put_exceptions_[i] -> describe();

		// Extract Exception description
		const IR__::ExceptionDescription *exception_desc;
		try
		{
			desc -> value >>= exception_desc;
		}
		catch (...)
		{
			// This cannot be, what to do???
			throw;
		}

		exception_seq.inout()[i] = *exception_desc;
	}

	attribute_desc -> put_exceptions = exception_seq;

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	desc -> value <<= attribute_desc._retn();;

	return desc._retn();
}

CORBA::TypeCode_ptr
AttributeDef_impl::type
()
throw(CORBA::SystemException)
{
   if ( !idl_type_ )
       throw CORBA::BAD_INV_ORDER();

   return idl_type_ -> type();
}

IR__::IDLType_ptr
AttributeDef_impl::type_def
()
throw(CORBA::SystemException)
{
   if ( !idl_type_ )
       throw CORBA::BAD_INV_ORDER();

   return idl_type_ -> _this();
}

void
AttributeDef_impl::type_def
(IR__::IDLType_ptr type )
throw(CORBA::SystemException)
{
    if ( CORBA::is_nil ( type ) )
        throw CORBA::BAD_PARAM(); // Is this exception correct?

    IDLType_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant = repository_ -> poa() -> reference_to_servant(type);
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
    if ( idl_type_ )
        idl_type_ -> _remove_ref();
    idl_type_ = impl;
}

IR__::AttributeMode
AttributeDef_impl::mode
()
throw(CORBA::SystemException)
{
	return mode_;
}

void
AttributeDef_impl::mode
(IR__::AttributeMode mode)
throw(CORBA::SystemException)
{
	mode_ = mode;
}

IR__::ExceptionDefSeq*
AttributeDef_impl::get_exceptions
()
throw(CORBA::SystemException)
{
	IR__::ExceptionDefSeq_var exception_seq = new IR__::ExceptionDefSeq;
    exception_seq -> length ( get_exceptions_.size() );
    for ( unsigned int i = 0; i < exception_seq -> length(); i++ )
        exception_seq.inout()[i] = get_exceptions_[i] -> _this();
    return exception_seq._retn();
}

void
AttributeDef_impl::get_exceptions
(const IR__::ExceptionDefSeq& seq)
throw(CORBA::SystemException)
{
    vector < ExceptionDef_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );

	unsigned int i;

    for ( i = 0; i < seq.length(); i++ )
    {
        if ( CORBA::is_nil ( seq[i].in() ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?
        impl_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(seq[i].in());
            impl_seq[i] = dynamic_cast<ExceptionDef_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if(!impl_seq[i])
        {
            // Must be same repository
            throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
        }
    }

    for ( i = 0; i < impl_seq.size(); i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0; i < get_exceptions_.size(); i++)
        get_exceptions_[i] -> _remove_ref();

    get_exceptions_ = impl_seq;
}

IR__::ExceptionDefSeq*
AttributeDef_impl::put_exceptions
()
throw(CORBA::SystemException)
{
	IR__::ExceptionDefSeq_var exception_seq = new IR__::ExceptionDefSeq;
    exception_seq -> length ( put_exceptions_.size() );
    for ( unsigned int i = 0; i < exception_seq -> length(); i++ )
        exception_seq.inout()[i] = put_exceptions_[i] -> _this();
    return exception_seq._retn();
}

void
AttributeDef_impl::put_exceptions
(const IR__::ExceptionDefSeq& seq)
throw(CORBA::SystemException)
{
    vector < ExceptionDef_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );

	unsigned int i;

    for ( i = 0; i < seq.length(); i++ )
    {
        if ( CORBA::is_nil ( seq[i].in() ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?
        impl_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(seq[i].in());
            impl_seq[i] = dynamic_cast<ExceptionDef_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if(!impl_seq[i])
        {
            // Must be same repository
            throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
        }
    }

    for ( i = 0; i < impl_seq.size(); i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0; i < put_exceptions_.size(); i++)
        put_exceptions_[i] -> _remove_ref();

    put_exceptions_ = impl_seq;
}

} // namespace QEDO_ComponentRepository

