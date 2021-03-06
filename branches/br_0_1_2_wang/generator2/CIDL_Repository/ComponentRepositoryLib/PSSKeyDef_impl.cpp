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

#include "PSSKeyDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

PSSKeyDef_impl::PSSKeyDef_impl
( Container_impl *container,
  Repository_impl *repository,
  AbstractStorageTypeDef_impl *abs_storage_type)

: IRObject_impl ( repository ),
  Contained_impl ( container, repository ),
  OperationDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::PSSKeyDef_impl() called" );

	OperationDef_impl::result_def ( abs_storage_type -> _this() );
	OperationDef_impl::mode ( IR__::OP_NORMAL );
}

PSSKeyDef_impl::PSSKeyDef_impl
( Container_impl *container,
  Repository_impl *repository,
  StorageTypeDef_impl *storage_type)

: IRObject_impl ( repository ),
  Contained_impl ( container, repository ),
  OperationDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::PSSKeyDef_impl() called" );

	OperationDef_impl::result_def ( storage_type -> _this() );
	OperationDef_impl::mode ( IR__::OP_NORMAL );
}

PSSKeyDef_impl::~PSSKeyDef_impl
()
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::~PSSKeyDef_impl() called" );
}

void
PSSKeyDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::destroy() called" );
}

CORBA::TypeCode_ptr
PSSKeyDef_impl::result
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::result() called" );

	// How to implement???
	throw CORBA::NO_IMPLEMENT();
}

void
PSSKeyDef_impl::result_def
(IR__::IDLType_ptr idl_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::result_def(...) called" );

	// Setting the result_def has no effect in PSSFactoryDef
	// result_def is automatically set by the home during
	// creation of the PSSFactoryDef
}

void
PSSKeyDef_impl::params
(const IR__::ParDescriptionSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::params(...) called" );

    // For PSSFactoryDef all parameters must be 'in' parameters
    for ( unsigned int i = 0 ; i < seq.length() ; i++ )
		if ( seq[i].mode != IR__::PARAM_IN )
			throw CORBA::BAD_PARAM ();	// Is this exception correct?

	OperationDef_impl::params ( seq );
}

void
PSSKeyDef_impl::mode
(IR__::OperationMode mode)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::mode(...) called" );

	// mode must not be changed for PSSFactoryDef
	throw CORBA::BAD_INV_ORDER();	// Is this exception correct
}

void
PSSKeyDef_impl::contexts
(const IR__::ContextIdSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "PSSKeyDef_impl::contexts(...) called" );

	// PSSFactoryDef has never contexts associated with it
	if ( seq.length() > 0 )
		throw CORBA::BAD_PARAM();	// Is this exception correct?

	OperationDef_impl::contexts ( seq );
}

} // namespace QEDO_ComponentRepository