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

#include "FactoryDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

FactoryDef_impl::FactoryDef_impl
( Container_impl *container,
  Repository_impl *repository,
  ComponentDef_impl *component )
: IRObject_impl ( repository ),
  Contained_impl ( container, repository ),
  OperationDef_impl ( container, repository )
{
	DEBUG_OUTLINE ( "FactoryDef_impl::FactoryDef_impl() called" );

	OperationDef_impl::result_def ( component -> _this() );
	OperationDef_impl::mode ( IR__::OP_NORMAL );
}

FactoryDef_impl::~FactoryDef_impl
()
{
	DEBUG_OUTLINE ( "FactoryDef_impl::~FactoryDef_impl() called" );
}

void
FactoryDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FactoryDef_impl::destroy() called" );
}

CORBA::TypeCode_ptr
FactoryDef_impl::result
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FactoryDef_impl::result() called" );

	// How to implement???
	throw CORBA::NO_IMPLEMENT();
}

void
FactoryDef_impl::result_def
(IR__::IDLType_ptr idl_type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FactoryDef_impl::result_def(...) called" );

	// Setting the result_def has no effect in FactoryDef
	// result_def is automatically set by the home during
	// creation of the FactoryDef
}

void
FactoryDef_impl::params
(const IR__::ParDescriptionSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FactoryDef_impl::params(...) called" );

    // For FactoryDef all parameters must be 'in' parameters
    for ( unsigned int i = 0 ; i < seq.length() ; i++ )
		if ( seq[i].mode != IR__::PARAM_IN )
			throw CORBA::BAD_PARAM ();	// Is this exception correct?

	OperationDef_impl::params ( seq );
}

void
FactoryDef_impl::mode
(IR__::OperationMode mode)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FactoryDef_impl::mode(...) called" );

	// mode must not be changed for FactoryDef
	throw CORBA::BAD_INV_ORDER();	// Is this exception correct
}

void
FactoryDef_impl::contexts
(const IR__::ContextIdSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FactoryDef_impl::contexts(...) called" );

	// FactoryDef has never contexts associated with it
	if ( seq.length() > 0 )
		throw CORBA::BAD_PARAM();	// Is this exception correct?

	OperationDef_impl::contexts ( seq );
}

} // namespace QEDO_ComponentRepository