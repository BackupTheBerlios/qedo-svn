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

#include "InterfaceDef_impl.h"
#include "AttributeDef_impl.h"
#include "OperationDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

InterfaceDef_impl::InterfaceDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::InterfaceDef_impl() called" );

	is_abstract_ = false;
	is_local_ = false;
        prefix_ = 0;
}

InterfaceDef_impl::~InterfaceDef_impl
()
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::~InterfaceDef_impl() called" );

        if ( prefix_ ) CORBA::string_free ( prefix_ );
}

void
InterfaceDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::destroy() called" );

    for ( unsigned int i = 0; i < base_interfaces_.size(); i++ )
        base_interfaces_[i] -> _remove_ref();

	Container_impl::destroy();
    Contained_impl::destroy();
}

IR__::Contained::Description*
InterfaceDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::describe() called" );

	IR__::InterfaceDescription_var interface_desc = new IR__::InterfaceDescription();
	interface_desc -> id = this -> id();
	interface_desc -> name = this -> name();
	interface_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		interface_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		interface_desc -> defined_in = CORBA::string_dup ( "" );

	interface_desc -> type = type();

	// Operations and Attributes
	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		IR__::Contained::Description_var desc;

		// Do Attributes
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Attribute )
		{
			desc = (*contained_iter) -> describe();
			const IR__::AttributeDescription *attr_desc;

			// Extract attribute description from general description
			try
			{
				desc -> value >>= attr_desc;
			}
			catch ( ... )
			{
				// This cannot be, what to do???
				throw;
			}
			interface_desc -> attributes.length ( interface_desc -> attributes.length() + 1 );
			interface_desc -> attributes[interface_desc -> attributes.length() - 1] =
				*attr_desc;
		}
		// Do Operations
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Operation )
		{
			desc = (*contained_iter) -> describe();
			const IR__::OperationDescription *operation_desc;

			// Extract attribute description from general description
			try
			{
				desc -> value >>= operation_desc;
			}
			catch ( ... )
			{
				// This cannot be, what to do???
				throw;
			}
			interface_desc -> operations.length ( interface_desc -> operations.length() + 1 );
			interface_desc -> operations[interface_desc -> operations.length() - 1] =
				*operation_desc;
		}
	}
	
	// Base interfaces
	interface_desc -> base_interfaces.length ( base_interfaces_.size() );
	for ( unsigned int i = 0; i < base_interfaces_.size(); i++ )
	{
		interface_desc -> base_interfaces[i] = base_interfaces_[i] -> id();
	}

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= interface_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::ContainedSeq*
InterfaceDef_impl::contents
(
 CORBA__::DefinitionKind limit_type,
 CORBA::Boolean exclude_inherited
)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::contents() called" );

	IR__::ContainedSeq_var return_seq = 
		Container_impl::contents ( limit_type, exclude_inherited );

	// We only have to care for inherited operations and attributes
	// if we are asked for them and if we should obey inherited constructs
	if ( ( limit_type != CORBA__::dk_all && limit_type != CORBA__::dk_Attribute &&
		limit_type != CORBA__::dk_Operation ) || exclude_inherited )
	{
		return return_seq._retn();
	}

	if ( !exclude_inherited )
	{
		list < Contained_impl* >::const_iterator contained_iter;

		for ( contained_iter = contained_.begin();
				contained_iter != contained_.end();
				contained_iter++ )
		{
			Container_impl *container =
				dynamic_cast<Container_impl*>(*contained_iter );
			if ( !container )
				continue;

			// For dk_attributes include the inherited attributes
			if ( limit_type == CORBA__::dk_all || limit_type == CORBA__::dk_Attribute )
			{
				IR__::ContainedSeq_var attribute_seq =
					container -> contents ( limit_type, exclude_inherited );

				contained_sequence_cat ( return_seq, attribute_seq );
			}
			// For dk_operation include the inherited operations
			if ( limit_type == CORBA__::dk_all || limit_type == CORBA__::dk_Operation )
			{
				IR__::ContainedSeq_var operation_seq =
					container -> contents ( limit_type, exclude_inherited );

				contained_sequence_cat ( return_seq, operation_seq );
			}
		}
	}

    return return_seq._retn();
}

CORBA::TypeCode_ptr
InterfaceDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::type() called" );

    return repository_ -> orb() -> create_interface_tc ( id_, name_ );
}

IR__::InterfaceDefSeq*
InterfaceDef_impl::base_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::base_interfaces() called" );

	IR__::InterfaceDefSeq_var interface_seq = new IR__::InterfaceDefSeq;
    interface_seq -> length ( base_interfaces_.size() );
    for ( unsigned int i = 0; i < interface_seq -> length(); i++ )
        interface_seq.inout()[i] = base_interfaces_[i] -> _this();
    return interface_seq._retn();
}

void
InterfaceDef_impl::base_interfaces
(const IR__::InterfaceDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::base_interfaces(...) called" );

    unsigned int i;

	// Check for name clash
	// For each base interface
	for ( i = 0; i < seq.length(); i++ )
	{
		IR__::ContainedSeq_var contained = seq[i] -> contents ( CORBA__::dk_all, false );
		
		// test each base interface contained object
		for ( unsigned int j = 0; j < contained -> length(); j++ )
		{
			list < Contained_impl* >::const_iterator contained_iter;

			// against each of my own contained object
			for ( contained_iter = contained_.begin();
					contained_iter != contained_.end();
					contained_iter++ )
			{
				// for name clash
				// Note: Each interface includes in its containers contained list
				// also all inherited objects, so name clash appears when names
				// are equal and ids are different
				if ( strcmp ( contained.inout()[j] -> name(), (*contained_iter) -> name() ) == 0 &&
					 strcmp ( contained.inout()[j] -> id(), (*contained_iter) -> id() ) != 0 )
					throw CORBA::BAD_PARAM ( 5, CORBA::COMPLETED_NO );
			}
		}
	}

    vector < InterfaceDef_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );

    for ( i = 0; i < seq.length(); i++ )
    {
        if ( CORBA::is_nil ( seq[i].in() ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?
        impl_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(seq[i].in());
            impl_seq[i] = dynamic_cast<InterfaceDef_impl*>(servant.in());
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

    for ( i = 0; i < base_interfaces_.size(); i++)
        base_interfaces_[i] -> _remove_ref();

    base_interfaces_ = impl_seq;
}

CORBA::Boolean
InterfaceDef_impl::is_abstract
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::is_abstract() called" );

	return is_abstract_;
}

void
InterfaceDef_impl::is_abstract
(CORBA::Boolean is_abstract)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::is_abstract(...) called" );

	is_abstract_ = is_abstract;
}

CORBA::Boolean
InterfaceDef_impl::is_local
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::is_local() called" );

	return is_local_;
}

void
InterfaceDef_impl::is_local
(CORBA::Boolean is_local)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::is_local(...) called" );

	is_local_ = is_local;
}

CORBA::Boolean
InterfaceDef_impl::is_a
(const char* interface_id)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::is_a() called" );

	// Test against our own id
    if ( strcmp ( id_, interface_id ) == 0 )
        return true;

	// Test against basic object
    if ( strcmp ( interface_id, "IDL:omg.org/CORBA/Object:1.0" ) == 0 )
        return true;

	// Go through all the base interfaces and look for the repository id
	for ( unsigned int i = 0; i < base_interfaces_.size(); i++ )
	{
		if ( strcmp ( id_, base_interfaces_[i] -> id() ) == 0 )
			return true;
	}

	return false;
}

IR__::AttributeDef_ptr
InterfaceDef_impl::create_attribute
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr type,
 IR__::AttributeMode mode,
 const IR__::ExceptionDefSeq& get_exceptions,
 const IR__::ExceptionDefSeq& put_exceptions)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::create_attribute() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	AttributeDef_impl *new_attribute = new AttributeDef_impl ( this, repository_ );
	new_attribute -> id ( id );
	new_attribute -> name ( name );
	new_attribute -> version ( version );
	new_attribute -> type_def ( type );
	new_attribute -> mode ( mode );
	new_attribute -> get_exceptions ( get_exceptions );
	new_attribute -> put_exceptions ( put_exceptions );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_attribute -> _this();
}

IR__::OperationDef_ptr
InterfaceDef_impl::create_operation
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr result,
 IR__::OperationMode mode,
 const IR__::ParDescriptionSeq& params,
 const IR__::ExceptionDefSeq& exceptions,
 const IR__::ContextIdSeq& contexts)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "InterfaceDef_impl::create_operation() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	OperationDef_impl *new_operation = new OperationDef_impl ( this, repository_ );
	new_operation -> id ( id );
	new_operation -> name ( name );
	new_operation -> version ( version );
	new_operation -> result_def ( result );
	new_operation -> mode ( mode );
	new_operation -> params ( params );
	new_operation -> exceptions ( exceptions );
	new_operation -> contexts ( contexts );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_operation -> _this();
}

char*
InterfaceDef_impl::prefix
()
throw(CORBA::SystemException)
{
	if ( prefix_ ) {

		return CORBA::string_dup (prefix_);
	}

	return CORBA::string_dup ( "" );
}

void
InterfaceDef_impl::prefix
(const char* value)
throw(CORBA::SystemException)
{
	if ( prefix_ && !strcmp(value,prefix_) )
		return;

	if ( prefix_ ) {
		CORBA::string_free ( prefix_); 
	}

	prefix_ = CORBA::string_dup ( value );
}
} // namespace QEDO_ComponentRepository

