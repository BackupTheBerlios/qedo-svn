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

#include "AbsStorageHomeDef_impl.h"
#include "FactoryDef_impl.h"
#include "PSSKeyDef_impl.h"
#include "PSSPrimaryKeyDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

AbstractStorageHomeDef_impl::AbstractStorageHomeDef_impl ( Container_impl *container,
					    Repository_impl *repository,
						AbstractStorageTypeDef_impl *managed_abstract_storage_type_impl )
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository ),
  InterfaceDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::AbstractStorageHomeDef_impl() called" );

	// Abstract storage homes must always manage a abstract storage type
	managed_abstract_storage_type_impl_ = managed_abstract_storage_type_impl;
	managed_abstract_storage_type_impl_ -> _add_ref();
}

AbstractStorageHomeDef_impl::~AbstractStorageHomeDef_impl
()
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::~AbstractStorageHomeDef_impl() called" );
}

void
AbstractStorageHomeDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::destroy() called" );

	managed_abstract_storage_type_impl_ -> _remove_ref();

	// Release all inherited interface impls
	unsigned int i;
    for ( i = 0 ; i < base_abstract_storage_home_impls_.size() ; i++)
        base_abstract_storage_home_impls_[i] -> _remove_ref();

	InterfaceDef_impl::destroy();
}

IR__::Contained::Description*
AbstractStorageHomeDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::describe() called" );

	IR__::AbstractStorageHomeDescription_var storage_home_desc = new IR__::AbstractStorageHomeDescription();
	storage_home_desc -> id = this -> id();
	storage_home_desc -> name = this -> name();
	storage_home_desc -> version = this -> version();

	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		storage_home_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		storage_home_desc -> defined_in = CORBA::string_dup ( "" );

	// Managed abstract storage type
	storage_home_desc -> managed_abstract_storage_type = managed_abstract_storage_type_impl_ -> id();

	unsigned int i;

	// Inherited interfaces
	storage_home_desc -> base_abstract_storage_homes.length ( base_abstract_storage_home_impls_.size() );
	for ( i = 0; i < base_abstract_storage_home_impls_.size(); i++ )
		storage_home_desc -> base_abstract_storage_homes[i] = base_abstract_storage_home_impls_[i] -> id();

	// Factories
	IR__::FactoryDefSeq_var factories = this -> factories();
	storage_home_desc -> factories.length (  factories -> length() );
	for ( i = 0; i < factories -> length(); i++ )
		storage_home_desc -> factories[i] = factories.inout()[i];

	// Keys
	IR__::PSSKeyDefSeq_var keys = this -> keys();
	storage_home_desc -> keys.length (  keys -> length() );
	for ( i = 0; i < keys -> length(); i++ )
		storage_home_desc -> keys[i] = keys.inout()[i];

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
			storage_home_desc -> attributes.length ( storage_home_desc -> attributes.length() + 1 );
			storage_home_desc -> attributes[storage_home_desc -> attributes.length() - 1] =	*attr_desc;
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
			storage_home_desc -> operations.length ( storage_home_desc -> operations.length() + 1 );
			storage_home_desc -> operations[storage_home_desc -> operations.length() - 1] = *operation_desc;
		}
	}

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= storage_home_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::AbstractStorageTypeDef_ptr 
AbstractStorageHomeDef_impl::managed_abstract_storage_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::managed_abstract_storage_type() called" );

	if ( managed_abstract_storage_type_impl_ )
		return managed_abstract_storage_type_impl_ -> _this();
	else
		return IR__::AbstractStorageTypeDef::_nil();
}

IR__::AbsStorageHomeDefSeq* 
AbstractStorageHomeDef_impl::base_abstract_storage_homes
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::base_abstract_storage_homes() called" );

	IR__::AbsStorageHomeDefSeq_var inherited_seq = new IR__::AbsStorageHomeDefSeq;

	inherited_seq -> length ( base_abstract_storage_home_impls_.size() );

	for ( unsigned int i = 0; i < inherited_seq -> length(); i++ )
		inherited_seq.inout()[i] = base_abstract_storage_home_impls_[i] -> _this();

	return inherited_seq._retn();
}
 
void 
AbstractStorageHomeDef_impl::base_abstract_storage_homes
(const IR__::AbsStorageHomeDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::base_abstract_storage_homes() called" );

    unsigned int i;

	// Check: Derived storage homes may not directly support an interface
	//if ( base_storage_home_impl_ && seq.length() > 0 )
	//{
	//	throw CORBA::BAD_PARAM();
	//}

	// Check for name clash for each inherited interface
	for ( i = 0; i < seq.length(); i++ )
	{
		IR__::ContainedSeq_var contained = seq[i] -> contents ( CORBA__::dk_all, false );
		
		// test each inherited interface contained object
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

    vector < AbstractStorageHomeDef_impl* > impl_seq;
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
            impl_seq[i] = dynamic_cast<AbstractStorageHomeDef_impl*>(servant.in());
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

    for ( i = 0; i < base_abstract_storage_home_impls_.size(); i++)
        base_abstract_storage_home_impls_[i] -> _remove_ref();

    base_abstract_storage_home_impls_ = impl_seq;
}

IR__::FactoryDefSeq* 
AbstractStorageHomeDef_impl::factories
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::factories() called" );

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

IR__::PSSKeyDefSeq* 
AbstractStorageHomeDef_impl::keys
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::keys() called" );

	IR__::PSSKeyDefSeq_var key_seq = new IR__::PSSKeyDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_PSSKey )
		{
			PSSKeyDef_impl *impl;
			impl = dynamic_cast < PSSKeyDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_PSSKey' cannot be casted to PSSKeyDef_impl" );
				continue;
			}
			key_seq -> length ( key_seq -> length() + 1 );
			key_seq [ key_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return key_seq._retn();
}

IR__::FactoryDef_ptr 
AbstractStorageHomeDef_impl::create_factory
(const char* id,
 const char* name,
 const char* version,
 const IR__::ParDescriptionSeq& params,
 const IR__::ExceptionDefSeq& exceptions)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::create_factory() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	FactoryDef_impl *new_factory = 
		new FactoryDef_impl ( this, repository_, managed_abstract_storage_type_impl_ );
	new_factory -> id ( id );
	new_factory -> name ( name );
	new_factory -> version ( version );
	new_factory -> params ( params );
	new_factory -> exceptions ( exceptions );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_factory -> _this();
}

IR__::PSSKeyDef_ptr 
AbstractStorageHomeDef_impl::create_key
(const char* id,
 const char* name,
 const char* version,
 const IR__::ParDescriptionSeq& params)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "AbstractStorageHomeDef_impl::create_key() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	PSSKeyDef_impl *new_key = 
		new PSSKeyDef_impl ( this, repository_, managed_abstract_storage_type_impl_ );
	new_key -> id ( id );
	new_key -> name ( name );
	new_key -> version ( version );
	new_key -> params ( params );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_key -> _this();	
}

} // namespace QEDO_ComponentRepository
