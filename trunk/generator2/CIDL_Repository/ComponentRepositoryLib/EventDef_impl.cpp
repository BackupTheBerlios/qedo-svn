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
#include "AttributeDef_impl.h"
#include "OperationDef_impl.h"
#include "Debug.h"
#include "EventDef_impl.h"

namespace QEDO_ComponentRepository {

EventDef_impl::EventDef_impl
( Container_impl *container, Repository_impl *repository )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "EventDef_impl::EventDef_impl() called" );

	base_value_impl_ = NULL;
	is_abstract_ = false;
	is_custom_ = false;
	is_truncatable_ = false;

}

EventDef_impl::~EventDef_impl
()
{
	DEBUG_OUTLINE ( "EventDef_impl::~EventDef_impl() called" );
}

CORBA::TypeCode_ptr
EventDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
    unsigned int i;

    for ( i = 0 ; i < seq.size() ; i++ )
    {
		IR__::RepositoryId_var id2 = seq[i] -> id();
        if ( strcmp ( id_, id2 ) == 0 )
            return repository_ -> orb() -> create_recursive_tc ( id_ );
    }

    seq.resize ( seq.size() + 1, NULL );
    seq[seq.size() - 1] = this;

	CORBA::TypeCode_var concrete_base;
	CORBA::ValueModifier type_modifier = CORBA::VM_NONE;
	IR__::ValueMemberSeq members;

    if ( this -> is_abstract() )
        type_modifier = CORBA::VM_ABSTRACT;
    else if ( this -> is_custom() )
        type_modifier = CORBA::VM_CUSTOM;
    else if ( this -> is_truncatable() )
        type_modifier = CORBA::VM_TRUNCATABLE;

    if ( base_value_impl_ )
        if ( !base_value_impl_ -> is_abstract() )
            concrete_base = base_value_impl_ -> build_recursive_type_code ( seq );

    list < Contained_impl* >::const_iterator contained_iter;
    for ( contained_iter = contained_.begin();
        contained_iter != contained_.end();
        contained_iter++)
    {
        Contained_impl* contained = *contained_iter;

        if ( contained -> def_kind() == CORBA__::dk_ValueMember)
        {
			ValueMemberDef_impl* member =
                dynamic_cast<ValueMemberDef_impl*>(contained);
            if ( !member )
			{
				DEBUG_ERRLINE ( "Fatal error: Value member cannot by casted to ValueMember_impl" );
				CORBA::TypeCode::_nil();
			}
			IR__::ValueMember value_member;
            value_member.name = member -> name();
            value_member.id = member -> id();
            value_member.version = member -> version();
            value_member.access = member -> access();
            value_member.type = member -> build_recursive_type_code ( seq );
            members.length ( members.length() + 1 );
            members[members.length() - 1] = value_member;
        }
    }

	// TODO: this is a hack because create_value_tc needs a sequence
	// from the CORBA module and we know that the both types are
	// exactly the same
	CORBA::ValueMemberSeq* members_new = (CORBA::ValueMemberSeq*)&members;

	CORBA::TypeCode_var tc = 
		repository_ -> orb() -> create_value_tc ( id_, name_, type_modifier,
                                              concrete_base, *members_new );

    seq.resize ( seq.size() - 1, NULL );
    
	return tc._retn();
}

void
EventDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::destroy() called" );

    unsigned int i;

    for ( i = 0 ; i < supported_interface_impls_.size() ; i++)
        supported_interface_impls_[i] -> _remove_ref();

    for ( i = 0 ; i < initializers_member_impls_.size() ; i++)
        for ( unsigned int j = 0 ; j < initializers_member_impls_[i].size() ; j++ )
            initializers_member_impls_[i][j] -> _remove_ref();

    if ( base_value_impl_ )
        base_value_impl_ -> _remove_ref();

    for ( i = 0 ; i < abstract_base_value_impls_.size() ; i++ )
        abstract_base_value_impls_[i] -> _remove_ref();

	Container_impl::destroy();
    Contained_impl::destroy();
}

IR__::Contained::Description*
EventDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::describe() called" );

    unsigned int i;

	IR__::ValueDescription_var value_desc = new IR__::ValueDescription;

    value_desc -> id = this -> id();
    value_desc -> name = this -> name();
    value_desc -> version = this -> version();

    Contained_impl* contained = dynamic_cast<Contained_impl*>(defined_in_);
    if(contained)
        value_desc -> defined_in = contained -> id();
    else
        value_desc -> defined_in = CORBA::string_dup("");

    value_desc -> is_abstract = this -> is_abstract();
    value_desc -> is_custom = this -> is_custom();

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
			value_desc -> attributes.length ( value_desc -> attributes.length() + 1 );
			value_desc -> attributes[value_desc -> attributes.length() - 1] =
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
			value_desc -> operations.length ( value_desc -> operations.length() + 1 );
			value_desc -> operations[value_desc -> operations.length() - 1] =
				*operation_desc;
		}
	}

	// Value members
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_ValueMember )
		{
			ValueMemberDef_impl *impl;
			impl = dynamic_cast < ValueMemberDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_ValueMember' cannot be casted to ValueMemberDef_impl" );
				continue;
			}
			value_desc -> members.length ( value_desc -> members.length() + 1 );
			value_desc -> members[value_desc->members.length() - 1].name =
				impl -> name();
			value_desc -> members[value_desc->members.length() - 1].id =
				impl -> id();
			value_desc -> members[value_desc->members.length() - 1].defined_in =
				this -> id();
			value_desc -> members[value_desc->members.length() - 1].version =
				impl -> version();
			value_desc -> members[value_desc->members.length() - 1].type =
				impl -> type();
			value_desc -> members[value_desc->members.length() - 1].type_def =
				impl -> type_def();
			value_desc -> members[value_desc->members.length() - 1].access =
				impl -> access();
		}
	}

	// Initializers
	IR__::InitializerSeq_var initializers = this -> initializers();
	value_desc -> initializers.length (  initializers -> length() );
	for ( i = 0; i < initializers -> length(); i++ )
		value_desc -> initializers[i] = initializers.inout()[i];

	// Supported interfaces
    value_desc -> supported_interfaces.length ( supported_interface_impls_.size());
    for ( i = 0 ; i < supported_interface_impls_.size() ; i++ )
        value_desc -> supported_interfaces[i] = supported_interface_impls_[i] -> id();

	// Abstract base values
    value_desc -> abstract_base_values.length ( abstract_base_value_impls_.size());
    for ( i = 0 ; i < abstract_base_value_impls_.size() ; i++ )
        value_desc -> abstract_base_values[i] = abstract_base_value_impls_[i] -> id();

    value_desc -> is_truncatable = this -> is_truncatable();

    if ( base_value_impl_ )
        value_desc -> base_value = base_value_impl_ -> id();
    else
        value_desc -> base_value = CORBA::string_dup("");

	value_desc -> type = this -> type();

    IR__::Contained::Description_var desc = new IR__::Contained::Description;

    desc -> kind = def_kind();
    desc -> value <<= value_desc._retn();

    return desc._retn();
}

CORBA::TypeCode_ptr
EventDef_impl::type
()
throw(CORBA::SystemException)
{
    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var type_code = build_recursive_type_code ( helper_seq );
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    return type_code._retn();
}

IR__::InterfaceDefSeq*
EventDef_impl::supported_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::supported_interfaces() called" );

	IR__::InterfaceDefSeq_var supported_interfaces = new IR__::InterfaceDefSeq;
    supported_interfaces -> length ( supported_interface_impls_.size() );
    for ( unsigned int i = 0 ; i < supported_interfaces -> length() ; i++ )
        supported_interfaces.inout()[i] = supported_interface_impls_[i] -> _this();
    return supported_interfaces._retn();
}

void
EventDef_impl::supported_interfaces
(const IR__::InterfaceDefSeq& seq)
throw(CORBA::SystemException)
{
    unsigned int i;

    vector < InterfaceDef_impl* > impl_seq;
    impl_seq.resize ( seq.length() );

    for ( i = 0 ; i < seq.length() ; i++ )
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
		if ( !impl_seq[i] )
        {
            // Must be same repository
            throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
        }
    }

    // Now we have to check for name collisions in the give supported interfaces,
	// the concrete base value and the abstract base values
	// TODO

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0 ; i < supported_interface_impls_.size() ; i++ )
        supported_interface_impls_[i] -> _remove_ref();

    supported_interface_impls_ = impl_seq;
}

IR__::InitializerSeq*
EventDef_impl::initializers
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::initializers() called" );

    //
    // Recalculate TypeCodes every time, as ids may have changed, and
    // also in order to calculate recursive TypeCodes correctly.
    // This is from ORBacus
    for ( unsigned int i = 0 ; i < initializers_.length() ; i++ )
        for ( unsigned int j = 0 ; j < initializers_[i].members.length() ; j++ )
        {
            vector < Contained_impl* > helper_seq;
            initializers_[i].members[j].type =
                initializers_member_impls_[i][j] -> build_recursive_type_code ( helper_seq );
			if ( helper_seq.size() != 0 )
				throw CORBA::BAD_INV_ORDER();	// Is this correct?
        }

	return new IR__::InitializerSeq ( initializers_ );
}

void
EventDef_impl::initializers
(const IR__::InitializerSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::initializers(...) called" );

    unsigned int i;

    // Abstract valuetypes do not have initializers
    if ( this -> is_abstract() && seq.length() > 0)
        throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );

    // Now check for duplicate names
    for ( i = 0 ; i < seq.length() ; i++ )
    {
        unsigned int j;

		// Check for duplicate names in the members list of each factory
        for ( j = 0 ; j < seq[i].members.length() ; j++ )
        {
            for ( unsigned int k = j + 1 ; k < seq[i].members.length() ; k++ )
            {
                if ( strcmp ( seq[i].members[j].name,
                                    seq[i].members[k].name ) == 0 )
				{
					throw CORBA::BAD_PARAM ( 1, CORBA::COMPLETED_NO );
				}
            }
        }

		// Check for duplicate factory names
        for ( j = i + 1 ; j < seq.length() ; j++ )
        {
            if ( strcmp ( seq[i].name, seq[j].name ) == 0 )
                throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );
        }

		// Check whether a factory name collides with a another identifier
		// TODO!!! do not evaluate inherited names, since factory names
		// can be redefined in derived valuetypes
		// check_name ( seq[i], ... );
    }

    vector < vector < IDLType_impl* > > impl_seq;
    impl_seq.resize ( seq.length(), vector < IDLType_impl* > (0) );

    for ( i = 0 ; i < seq.length() ; i++ )
    {
        impl_seq[i].resize ( seq[i].members.length(), NULL );
        for ( unsigned int j = 0 ; j < seq[i].members.length() ; j++ )
        {
            if ( CORBA::is_nil ( seq[i].members[j].type_def.in() ) )
                throw CORBA::BAD_PARAM(); // Is this exception correct?
            impl_seq[i][j] = 0;
            try
            {
				PortableServer::ServantBase_var servant =
                    repository_ -> poa() -> reference_to_servant(seq[i].members[j].type_def.in());
                impl_seq[i][j] = dynamic_cast<IDLType_impl*>(servant.in());
            }
            catch(...)
            {
            }
            if(!impl_seq[i][j])
            {
                // Must be same repository
                throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
            }
        }
    }

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        for ( unsigned int j = 0 ; j < impl_seq[i].size() ; j++ )
            impl_seq[i][j] -> _add_ref();

    for ( i = 0 ; i < initializers_member_impls_.size() ; i++ )
        for ( unsigned int j = 0 ; j < initializers_member_impls_[i].size() ; j++ )
            initializers_member_impls_[i][j] -> _remove_ref();

    initializers_member_impls_ = impl_seq;
    
	initializers_ = seq;
}

IR__::ValueDef_ptr
EventDef_impl::base_value
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::base_value() called" );

    if ( base_value_impl_ )
        return base_value_impl_ -> _this();
    else
        return IR__::ValueDef::_nil();
}

void
EventDef_impl::base_value
(IR__::ValueDef_ptr base_value)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::base_value(...) called" );

    if ( !CORBA::is_nil ( base_value ) )
    {
        // Abstract valuetype do not have base values
        if ( this -> is_abstract() )
            throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO );

        // Abstract base valuetypes are not allowed here
        if ( base_value -> is_abstract() )
            throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO);

        // Non-custom valuetype must inherit from a non-custom valuetype
        if ( !this -> is_custom() && base_value -> is_custom() )
            throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO);

        // A truncatable valuetype needs a truncatable base valuetype if
		// the base valuetype is not abstract
        if ( this -> is_truncatable() )
        {
			IR__::ValueDef_var base = base_value -> base_value();
            if ( !CORBA::is_nil ( base ) && !base_value -> is_truncatable() )
                throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO );
        }

        ValueDef_impl* impl = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant ( base_value );
            impl = dynamic_cast<ValueDef_impl*>(servant.in());
        }
        catch(...)
        {
        }
        if(!impl)
        {
            // Must be same repository
            throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
        }

        // Now we have to check for duplicate names in our scope,
		// in the abstract base value scopes and in the supported interfaces
		// scope
		// TODO!!!!

        impl -> _add_ref();
 
		if ( base_value_impl_ )
            base_value_impl_ -> _remove_ref();
 
		base_value_impl_ = impl;
    }
    else
    {
        if ( base_value_impl_ )
            base_value_impl_ -> _remove_ref();

        base_value_impl_ = 0;
    }
}

IR__::ValueDefSeq*
EventDef_impl::abstract_base_values
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::abstract_base_values() called" );

	IR__::ValueDefSeq_var value_def_seq = new IR__::ValueDefSeq;
    value_def_seq -> length ( abstract_base_value_impls_.size() );
    for ( unsigned int i = 0 ; i < value_def_seq -> length() ; i++ )
        value_def_seq.inout()[i] = abstract_base_value_impls_[i] -> _this();
    return value_def_seq._retn();
}

void
EventDef_impl::abstract_base_values
(const IR__::ValueDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::abstract_base_values(...) called" );

    unsigned int i;

    // Check for duplicates and whether all valuetypes are abstract
    for ( i = 0 ; i < seq.length() ; i++ )
    {
        if ( CORBA::is_nil(seq[i].in()) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        if ( !seq[i] -> is_abstract() )
            throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO );

		CORBA::String_var id1 = seq[i] -> id();
        for ( unsigned int j = i + 1 ; j < seq.length() ; j++ )
        {
			CORBA::String_var id2 = seq[j] -> id();
            if ( strcmp ( id1, id2 ) == 0 )
                throw CORBA::BAD_PARAM ( 5, CORBA::COMPLETED_NO );
        }
    }

    vector < ValueDef_impl* > impl_seq;
    impl_seq.resize ( seq.length(), NULL );

    for ( i = 0 ; i < seq.length() ; i++ )
    {
        impl_seq[i] = 0;
        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(seq[i].in());
            impl_seq[i] = dynamic_cast<ValueDef_impl*>(servant.in());
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

    // Now check for duplicate names in my own scope, in base value and
	// in supported interfaces
	// TODO

    for ( i = 0 ; i < impl_seq.size() ; i++ )
        impl_seq[i] -> _add_ref();

    for ( i = 0 ; i < abstract_base_value_impls_.size() ; i++ )
        abstract_base_value_impls_[i] -> _remove_ref();

    abstract_base_value_impls_ = impl_seq;
}

CORBA::Boolean
EventDef_impl::is_abstract
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::is_abstract() called" );

	return is_abstract_;
}

void
EventDef_impl::is_abstract
(CORBA::Boolean is_abstract)
throw(CORBA::SystemException)
{
	if ( is_abstract )
	{
		// Abstract valuetypes do not have base values
		if ( base_value_impl_ )
			throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO );

		// Abstract valuetypes are not truncatable
		if ( this -> is_truncatable() )
			throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );

		// Abstract valuetypes are not custom
		if ( this -> is_custom() )
			throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	}

	is_abstract_ = is_abstract;
}

CORBA::Boolean
EventDef_impl::is_custom
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::is_custom() called" );

	return is_custom_;
}

void
EventDef_impl::is_custom
(CORBA::Boolean is_custom)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::is_custom(...) called" );

	if ( is_custom )
	{
		// Custom valuetypes are not truncatable
		if ( this -> is_truncatable() )
			throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );

		// Custom valuetypes can not be abstract
		if ( this -> is_abstract() )
			throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	}

	is_custom_ = is_custom;
}

CORBA::Boolean
EventDef_impl::is_truncatable
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::is_truncatable() called" );

	return is_truncatable_;
}

void
EventDef_impl::is_truncatable
(CORBA::Boolean is_truncatable)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::is_truncatable(...) called" );

	if ( is_truncatable )
	{
		// Truncatable valuetypes need a concrete base valuetype
		if ( ! base_value_impl_ )
			throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO );

		// Truncatable valuetypes need a truncatable base valuetype
		if ( base_value_impl_ -> is_truncatable() )
			throw CORBA::BAD_PARAM ( 12, CORBA::COMPLETED_NO );

		// Truncatable valuetypes can not be abstract
		if ( this -> is_abstract() )
			throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );

		// Truncatable valuetypes can not be custom
		if ( this -> is_custom() )
			throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	}

	is_truncatable_ = is_truncatable;
}

CORBA::Boolean
EventDef_impl::is_a
(const char* id)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::is_a() called" );

	// First check whether its our own id
    if ( strcmp ( id, id_ ) == 0 )
        return true;

    unsigned int i;

	// Now check all of the supported interfaces
    for ( i = 0 ; i < supported_interface_impls_.size() ; i++ )
        if ( supported_interface_impls_[i] -> is_a ( id ) )
            return true;

	// Now check our concrete base value
    if ( base_value_impl_ )
        if ( base_value_impl_ -> is_a ( id ) )
            return true;

	// Finally check all abstract base valuetype implementations 
    for ( i = 0 ; i < abstract_base_value_impls_.size() ; i++ )
        if ( abstract_base_value_impls_[i] -> is_a ( id ) )
            return true;

    return false;
}

IR__::ValueMemberDef_ptr
EventDef_impl::create_value_member
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr type,
 CORBA__::Visibility access)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::create_value_member() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	ValueMemberDef_impl *new_value_member = new ValueMemberDef_impl ( this, repository_ );
	new_value_member -> id ( id );
	new_value_member -> name ( name );
	new_value_member -> version ( version );
	new_value_member -> type_def ( type );
	new_value_member -> access ( access );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_value_member -> _this();
}

IR__::AttributeDef_ptr
EventDef_impl::create_attribute
(const char* id,
 const char* name,
 const char* version,
 IR__::IDLType_ptr type,
 IR__::AttributeMode mode,
 const IR__::ExceptionDefSeq& get_exceptions,
 const IR__::ExceptionDefSeq& put_exceptions)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ValueDef_impl::create_attribute() called" );

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
EventDef_impl::create_operation
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
	DEBUG_OUTLINE ( "ValueDef_impl::create_operation() called" );

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

} // namespace QEDO_ComponentRepository

