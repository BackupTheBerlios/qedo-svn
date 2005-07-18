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

#include "HomeDef_impl.h"
#include "FactoryDef_impl.h"
#include "FinderDef_impl.h"
#include "PrimaryKeyDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

HomeDef_impl::HomeDef_impl ( Container_impl *container,
					    Repository_impl *repository,
						HomeDef_impl *base_home_impl,
						ComponentDef_impl *managed_component_impl,
						ValueDef_impl *primary_key_impl )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository ),
  InterfaceDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "HomeDef_impl::HomeDef_impl() called" );
	// If there is no base home, base_home_impl will be NULL
	base_home_impl_ = base_home_impl;
	if ( base_home_impl_ )
		base_home_impl_ -> _add_ref();

	// Homes must always manage a component
	managed_component_impl_ = managed_component_impl;
	managed_component_impl_ -> _add_ref();

	// If there is no primary key, primary_key_impl will be NULL
	primary_key_impl_ = primary_key_impl;
	if ( primary_key_impl_ )
		primary_key_impl_ -> _add_ref();

	primary_key_ = NULL;
}

HomeDef_impl::~HomeDef_impl
()
{
	DEBUG_OUTLINE ( "HomeDef_impl::~HomeDef_impl() called" );
	
	delete primary_key_;
	primary_key_ = NULL;
}

void
HomeDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::destroy() called" );

	if ( base_home_impl_ )
		base_home_impl_ -> _remove_ref();

	managed_component_impl_ -> _remove_ref();

	// Release all supported interface impls
	unsigned int i;
    for ( i = 0 ; i < supported_interface_impls_.size() ; i++)
        supported_interface_impls_[i] -> _remove_ref();

	if ( primary_key_impl_ )
		primary_key_impl_ -> _remove_ref();

	InterfaceDef_impl::destroy();
}

IR__::Contained::Description*
HomeDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::describe() called" );

	IR__::HomeDescription_var home_desc = new IR__::HomeDescription();
	home_desc -> id = this -> id();
	home_desc -> name = this -> name();
	home_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		home_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		home_desc -> defined_in = CORBA::string_dup ( "" );

	// Base home
	if ( base_home_impl_ )
		home_desc -> base_home = base_home_impl_ -> id();
	else
		home_desc -> base_home = CORBA::string_dup ( "" );

	// Managed component
	home_desc -> managed_component = managed_component_impl_ -> id();

	unsigned int i;

	// Supports interfaces
	home_desc -> supports_interfaces.length ( supported_interface_impls_.size() );
	for ( i = 0; i < supported_interface_impls_.size(); i++ )
		home_desc -> supports_interfaces[i] = supported_interface_impls_[i] -> id();

	// Primary Key
	// TODO: What should be inserted here? -> primary key during
	// creation is a ValueDef, so should a PrimaryKeyDef created
	// automatically???
	home_desc -> primary_key_def = IR__::PrimaryKeyDef::_nil();


	// Factories
	IR__::FactoryDefSeq_var factories = this -> factories();
	home_desc -> factories.length (  factories -> length() );
	for ( i = 0; i < factories -> length(); i++ )
		home_desc -> factories[i] = factories.inout()[i];

	// Finders
	IR__::FinderDefSeq_var finders = this -> finders();
	home_desc -> finders.length (  finders -> length() );
	for ( i = 0; i < finders -> length(); i++ )
		home_desc -> finders[i] = finders.inout()[i];

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
			home_desc -> attributes.length ( home_desc -> attributes.length() + 1 );
			home_desc -> attributes[home_desc -> attributes.length() - 1] =
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
			home_desc -> operations.length ( home_desc -> operations.length() + 1 );
			home_desc -> operations[home_desc -> operations.length() - 1] =
				*operation_desc;
		}
	}

	home_desc -> is_basic = this -> is_basic();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= home_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::HomeDef_ptr
HomeDef_impl::base_home
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::base_home() called" );

	if ( base_home_impl_ )
		return base_home_impl_ -> _this();
	else
		return IR__::HomeDef::_nil();
}

IR__::ComponentDef_ptr
HomeDef_impl::managed_component
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::managed_component() called" );

	if ( managed_component_impl_ )
		return managed_component_impl_ -> _this();
	else
		return IR__::ComponentDef::_nil();
}

IR__::InterfaceDefSeq*
HomeDef_impl::supported_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::supported_interfaces() called" );

	
	IR__::InterfaceDefSeq_var supported_seq = new IR__::InterfaceDefSeq;

	supported_seq -> length ( supported_interface_impls_.size() );

	for ( unsigned int i = 0; i < supported_seq -> length(); i++ )
		supported_seq.inout()[i] = supported_interface_impls_[i] -> _this();

	return supported_seq._retn();
}

void
HomeDef_impl::supported_interfaces
(const IR__::InterfaceDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ComponentDef_impl::supported_interfaces(...) called" );

    unsigned int i;

	// Check: Derived components may not directly support an interface
	if ( base_home_impl_ && seq.length() > 0 )
	{
		throw CORBA::BAD_PARAM();
	}

	// Check for name clash
	// For each supported interface
	for ( i = 0; i < seq.length(); i++ )
	{
		IR__::ContainedSeq_var contained = seq[i] -> contents ( CORBA__::dk_all, false );
		
		// test each supported interface contained object
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

    for ( i = 0; i < supported_interface_impls_.size(); i++)
        supported_interface_impls_[i] -> _remove_ref();

    supported_interface_impls_ = impl_seq;
}

IR__::PrimaryKeyDef_ptr
HomeDef_impl::primary_key
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::primary_key() called" );

	// TODO: What to return here, should a PrimaryKeyDef automatically
	// be constructed from the primary key value that was passed
	// during creation?

	return primary_key_;
}

IR__::FactoryDefSeq*
HomeDef_impl::factories
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::factories() called" );

	IR__::FactoryDefSeq_var factory_seq = new IR__::FactoryDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Factory )
		{
			FactoryDef_impl *impl;
			impl = dynamic_cast < FactoryDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Factory' cannot be casted to FactoryDef_impl" );
				continue;
			}
			factory_seq -> length ( factory_seq -> length() + 1 );
			factory_seq [ factory_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return factory_seq._retn();
}

IR__::FinderDefSeq*
HomeDef_impl::finders
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::finders() called" );

	IR__::FinderDefSeq_var finder_seq = new IR__::FinderDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Finder )
		{
			FinderDef_impl *impl;
			impl = dynamic_cast < FinderDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Finder' cannot be casted to FinderDef_impl" );
				continue;
			}
			finder_seq -> length ( finder_seq -> length() + 1 );
			finder_seq [ finder_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return finder_seq._retn();
}

CORBA::Boolean
HomeDef_impl::is_basic
()
throw(CORBA::SystemException)
{
	// Basic Homes do not have a base home, do only have factories and finder
	// Operations and manage a basic component

	// Test base home
	if ( base_home_impl_ )
		return false;

	// Test for finders and factories
	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() != CORBA__::dk_Factory &&
			 (*contained_iter) -> def_kind() != CORBA__::dk_Finder )
		{
			 return false;
		}
	}

	// Test base component
	return managed_component_impl_ -> is_basic();
}

IR__::PrimaryKeyDef_ptr
HomeDef_impl::create_primary_key
(const char* id,
 const char* name,
 const char* version,
 IR__::ValueDef_ptr primary_key)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::create_primary_key() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	if ( CORBA::is_nil ( primary_key ) )
		throw CORBA::BAD_PARAM();		// Is this exception correct?

	// TODO: Check: primary_key must be derived from PrimaryKeyBase

    ValueDef_impl* impl = 0;
    try
    {
		PortableServer::ServantBase_var servant =
			repository_ -> poa() -> reference_to_servant ( primary_key );
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

	PrimaryKeyDef_impl *new_primary_key = new PrimaryKeyDef_impl ( this, repository_, impl );
	new_primary_key -> id ( id );
	new_primary_key -> name ( name );
	new_primary_key -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	primary_key_ = new_primary_key -> _this();
	//return new_primary_key -> _this();
	return primary_key_;
}

IR__::FactoryDef_ptr
HomeDef_impl::create_factory
(const char* id,
 const char* name,
 const char* version,
 const IR__::ParDescriptionSeq& params,
 const IR__::ExceptionDefSeq& exceptions)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::create_factory() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	FactoryDef_impl *new_factory = 
		new FactoryDef_impl ( this, repository_, managed_component_impl_ );
	new_factory -> id ( id );
	new_factory -> name ( name );
	new_factory -> version ( version );
	new_factory -> params ( params );
	new_factory -> exceptions ( exceptions );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_factory -> _this();
}

IR__::FinderDef_ptr
HomeDef_impl::create_finder
(const char* id,
 const char* name,
 const char* version,
 const IR__::ParDescriptionSeq& params,
 const IR__::ExceptionDefSeq& exceptions)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeDef_impl::create_finder() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	FinderDef_impl *new_finder = 
		new FinderDef_impl ( this, repository_, managed_component_impl_ );
	new_finder -> id ( id );
	new_finder -> name ( name );
	new_finder -> version ( version );
	new_finder -> params ( params );
	new_finder -> exceptions ( exceptions );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_finder -> _this();
}

} // namespace QEDO_ComponentRepository
