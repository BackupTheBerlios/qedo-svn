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

#include "OperationDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

OperationDef_impl::OperationDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "OperationDef_impl::OperationDef_impl() called" );

	result_impl_ = NULL;
}

OperationDef_impl::~OperationDef_impl
()
{
	DEBUG_OUTLINE ( "OperationDef_impl::~OperationDef_impl() called" );
}

void
OperationDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::destroy() called" );

	unsigned int i;

	if ( result_impl_ )
		result_impl_ -> _remove_ref();

	for ( i = 0 ; i < param_impls_.size() ; i++ )
		param_impls_[i] -> _remove_ref();

	for ( i = 0 ; i < exception_impls_.size() ; i++ )
		exception_impls_[i] -> _remove_ref();

    Contained_impl::destroy();
}

IR__::Contained::Description*
OperationDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::describe() called" );

	IR__::OperationDescription_var operation_desc = new IR__::OperationDescription;
    operation_desc -> id = this -> id();
    operation_desc -> name = this -> name();
    operation_desc -> version = this -> version();

    Contained_impl* contained = dynamic_cast<Contained_impl*>(defined_in_);
    if(contained)
        operation_desc -> defined_in = contained -> id();
    else
        operation_desc -> defined_in = CORBA::string_dup("");

    operation_desc -> result = this -> result();
    operation_desc -> mode = this -> mode();
    operation_desc -> contexts = this -> contexts_;

    //
    // Recalculate TypeCodes every time, as ids may have changed, and
    // also in order to calculate recursive TypeCodes correctly.
    // This is from ORBacus
    unsigned int i;

    for(i = 0 ; i < param_impls_.size() ; i++)
    {
        vector < Contained_impl* > helper_seq;
        params_[i].type = param_impls_[i] -> build_recursive_type_code ( helper_seq );
		if ( helper_seq.size() != 0 )
			throw CORBA::BAD_INV_ORDER();	// Is this correct?
    }

    operation_desc -> parameters = params_;

    operation_desc -> exceptions.length ( exception_impls_.size() );
    for ( i = 0 ; i < exception_impls_.size() ; i++ )
    {
        IR__::Contained::Description_var contained_exception_desc = exception_impls_[i] -> describe();
        const IR__::ExceptionDescription* exception_desc;
        try
		{
			contained_exception_desc -> value >>= exception_desc;
		}
		catch ( ... )
		{
			// This cannot be, what to do???
			throw;
		}
        operation_desc -> exceptions[i] = *exception_desc;
    }

    IR__::Contained::Description_var desc =
        new IR__::Contained::Description;
    desc -> kind = def_kind();
    desc -> value <<= operation_desc._retn();

    return desc._retn();
}

CORBA::TypeCode_ptr
OperationDef_impl::result
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::result() called" );

	if ( !result_impl_ )
		throw CORBA::BAD_INV_ORDER ();

	return result_impl_ -> type();
}

IR__::IDLType_ptr
OperationDef_impl::result_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::result_def() called" );

    if ( !result_impl_ )
        throw CORBA::BAD_INV_ORDER();

    return result_impl_ -> _this();
}

void
OperationDef_impl::result_def
(IR__::IDLType_ptr result)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::result_def(...) called" );

    if ( CORBA::is_nil ( result ) )
        throw CORBA::BAD_PARAM(); // Is this exception correct?

    IDLType_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant = repository_ -> poa() ->
			reference_to_servant(result);
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if ( !impl )
    {
        // Must be same repository
        throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
    }

    impl -> _add_ref();
    
	if ( result_impl_ )
        result_impl_ -> _remove_ref();

    result_impl_ = impl;
}

IR__::ParDescriptionSeq*
OperationDef_impl::params
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::paramas() called" );

	//
	// Recalculate TypeCodes every time, as ids may have changed, and
	// also in order to calculate recursive TypeCodes correctly.
	// This is from ORBacus
	for ( unsigned int i = 0 ; i < param_impls_.size() ; i++ )
	{
		vector < Contained_impl* > helper_seq;
		params_[i].type = param_impls_[i] -> build_recursive_type_code ( helper_seq );
		if ( helper_seq.size() != 0 )
			throw CORBA::BAD_INV_ORDER();	// Is this correct?
	}

	return new IR__::ParDescriptionSeq(params_);
}

void
OperationDef_impl::params
(const IR__::ParDescriptionSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::params(...) called" );

	unsigned int i;

    // Check for duplicate attribute names
    for ( i = 0 ; i < seq.length() ; i++ )
        for ( unsigned int j = i + 1 ; j < seq.length() ; j++ )
            if ( strcmp ( seq[i].name, seq[j].name ) == 0 )
                throw CORBA::BAD_PARAM  ( 1, CORBA::COMPLETED_NO );

    vector < IDLType_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );
    for ( i = 0 ; i < seq.length() ; i++ )
    {
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
        if ( !impl_seq[i] )
        {
            // Must be same repository
            throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
        }
    }

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0 ; i < param_impls_.size() ; i++ )
        param_impls_[i] -> _remove_ref();

    param_impls_ = impl_seq;
    params_ = seq;
}

IR__::OperationMode
OperationDef_impl::mode
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::mode() called" );

	return mode_;
}

void
OperationDef_impl::mode
(IR__::OperationMode mode)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::mode(...) called" );

	// TODO: Check when mode is OP_ONEWAY that result is TC_void and all
	// parameters are in parameters
	mode_ = mode;
}

IR__::ContextIdSeq*
OperationDef_impl::contexts
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::contexts() called" );

	return new IR__::ContextIdSeq ( contexts_ );
}

void
OperationDef_impl::contexts
(const IR__::ContextIdSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::contexts(...) called" );

	contexts_ = seq;
}

IR__::ExceptionDefSeq*
OperationDef_impl::exceptions
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::exceptions() called" );

	IR__::ExceptionDefSeq_var exception_seq = new IR__::ExceptionDefSeq;
    exception_seq -> length ( exception_impls_.size() );
    for ( unsigned int i = 0 ; i < exception_seq -> length() ; i++ )
        exception_seq.inout()[i] = exception_impls_[i] -> _this();
    return exception_seq._retn();
}

void
OperationDef_impl::exceptions
(const IR__::ExceptionDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "OperationDef_impl::exceptions(...) called" );

    unsigned int i;

    vector < ExceptionDef_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );

    for ( i = 0 ; i < seq.length() ; i++ )
    {
        if ( CORBA::is_nil ( seq[i] ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?
       
		impl_seq[i] = 0;

        try
        {
			PortableServer::ServantBase_var servant = 
				repository_ -> poa() -> reference_to_servant(seq[i]);
            impl_seq[i] = dynamic_cast<ExceptionDef_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if ( !impl_seq[i] )
        {
            // Must be same repository
            throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
        }
    }

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0 ; i < exception_impls_.size() ; i++ )
        exception_impls_[i] -> _remove_ref();

    exception_impls_ = impl_seq;
}

} // namespace QEDO_ComponentRepository