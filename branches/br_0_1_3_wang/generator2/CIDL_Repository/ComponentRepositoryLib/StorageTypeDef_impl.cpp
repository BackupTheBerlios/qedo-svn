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

#include "StorageTypeDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

StorageTypeDef_impl::StorageTypeDef_impl
( Container_impl *container,
  Repository_impl *repository,
  StorageTypeDef_impl *base_storage_type_impl )
  
: IRObject_impl ( repository ),
  IDLType_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository ),
  InterfaceDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::StorageTypeDef_impl() called" );

	base_storage_type_impl_ = base_storage_type_impl;
	if ( base_storage_type_impl_ )
		base_storage_type_impl_ -> _add_ref();
}

StorageTypeDef_impl::~StorageTypeDef_impl
()
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::~StorageTypeDef_impl() called" );
}

void
StorageTypeDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::destroy() called" );

	unsigned int i;

	// Release base storage type impl
	if ( base_storage_type_impl_ )
		base_storage_type_impl_ -> _remove_ref();

	// Release all supported interface impls
    for ( i = 0 ; i < supported_interface_impls_.size() ; i++)
        supported_interface_impls_[i] -> _remove_ref();

	InterfaceDef_impl::destroy();
}

IR__::Contained::Description*
StorageTypeDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::describe() called" );

	IR__::StorageTypeDescription_var storage_type_desc = new IR__::StorageTypeDescription();
	storage_type_desc -> id = this -> id();
	storage_type_desc -> name = this -> name();
	storage_type_desc -> version = this -> version();

	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		storage_type_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		storage_type_desc -> defined_in = CORBA::string_dup ( "" );

	// Base storage type
	if ( base_storage_type_impl_ )
		storage_type_desc -> base_storage_type = base_storage_type_impl_ -> id();
	else
		storage_type_desc -> base_storage_type = CORBA::string_dup ( "" );

	unsigned int i;

	// Supports interfaces
	storage_type_desc -> supports_interfaces.length ( supported_interface_impls_.size() );
	for ( i = 0; i < supported_interface_impls_.size(); i++ )
		storage_type_desc -> supports_interfaces[i] = supported_interface_impls_[i] -> id();

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
			storage_type_desc -> attributes.length ( storage_type_desc -> attributes.length() + 1 );
			storage_type_desc -> attributes[storage_type_desc -> attributes.length() - 1] =
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
			storage_type_desc -> operations.length ( storage_type_desc -> operations.length() + 1 );
			storage_type_desc -> operations[storage_type_desc -> operations.length() - 1] = *operation_desc;
		}
	}

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= storage_type_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::InterfaceDefSeq*
StorageTypeDef_impl::supported_interfaces
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::supported_interfaces() called" );
	
	IR__::InterfaceDefSeq_var supported_seq = new IR__::InterfaceDefSeq;

	supported_seq -> length ( supported_interface_impls_.size() );

	for ( unsigned int i = 0; i < supported_seq -> length(); i++ )
		supported_seq.inout()[i] = supported_interface_impls_[i] -> _this();

	return supported_seq._retn();
}

void
StorageTypeDef_impl::supported_interfaces
(const IR__::InterfaceDefSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::supported_interfaces(...) called" );

    unsigned int i;

	// Check: Derived storage types may not directly support an interface
	if ( base_storage_type_impl_ && seq.length() > 0 )
	{
		throw CORBA::BAD_PARAM();
	}

	// Check for name clash for each supported interface
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

IR__::StorageTypeDef_ptr
StorageTypeDef_impl::base_storage_type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StorageTypeDef_impl::base_storage_type() called" );

	if ( base_storage_type_impl_ )
		return base_storage_type_impl_ -> _this();
	else
		return IR__::StorageTypeDef::_nil();
}

void
StorageTypeDef_impl::get_StateMembers
(IR__::AttributeDefSeq& state_members)
throw(CORBA::SystemException)
{
	IR__::ContainedSeq_var contained_seq = this->contents(CORBA__::dk_Attribute, false);
	CORBA::ULong len = contained_seq->length();
	CORBA::ULong ulPre = state_members.length();
	state_members.length(ulPre+len);
	for(CORBA::ULong i=0; i<len; i++)
	{
		IR__::AttributeDef_var a_attribute = IR__::AttributeDef::_narrow(((*contained_seq)[i]));
		state_members[i+ulPre] = (a_attribute);
	}

	IR__::StorageTypeDef_ptr storagetype = base_storage_type();
	if(!CORBA::is_nil(storagetype))
		storagetype->get_StateMembers(state_members);
}

} // namespace QEDO_ComponentRepository
