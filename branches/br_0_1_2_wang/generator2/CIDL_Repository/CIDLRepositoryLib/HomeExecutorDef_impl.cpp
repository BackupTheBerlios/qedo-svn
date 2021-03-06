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

#include "HomeExecutorDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

HomeExecutorDef_impl::HomeExecutorDef_impl
( Container_impl *container,
  Repository_impl *repository,
  IR__::AbstractStorageHomeDef_ptr binds_to)
: Contained_impl ( container, repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::HomeExecutorDef_impl() called" );
	binds_to_ = binds_to;
}

HomeExecutorDef_impl::~HomeExecutorDef_impl
()
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::~HomeExecutorDef_impl() called" );
}

void
HomeExecutorDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::destroy() called" );

	Contained_impl::destroy();
}

IR__::Contained::Description*
HomeExecutorDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::describe() called" );

	CIDL::HomeExecutorDescription_var home_executor_desc = new CIDL::HomeExecutorDescription;
	home_executor_desc -> id = this -> id();
	home_executor_desc -> name = this -> name();
	home_executor_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		home_executor_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		home_executor_desc -> defined_in = CORBA::string_dup ( "" );

	home_executor_desc -> binds_to = this -> binds_to();
	home_executor_desc -> delegations = *(this->delegations());
	home_executor_desc -> abs_storage_home_delegations = *(this->abs_storage_home_delegations());

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= home_executor_desc._retn();
	desc -> value = any;

	return desc._retn();
}

CIDL::DelegationSeq*
HomeExecutorDef_impl::delegations
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::delegations() called" );

	return new CIDL::DelegationSeq ( delegations_ );
}

void
HomeExecutorDef_impl::delegations
(const CIDL::DelegationSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::delegations(...) called" );

	delegations_ = seq;
}

CIDL::AbsStorageHomeDelegationSeq*
HomeExecutorDef_impl::abs_storage_home_delegations
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::abs_storage_home_delegations() called" );

	return new CIDL::AbsStorageHomeDelegationSeq ( abs_storage_home_delegations_ );
}

void
HomeExecutorDef_impl::abs_storage_home_delegations
(const CIDL::AbsStorageHomeDelegationSeq& seq)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::abs_storage_home_delegations(...) called" );

	abs_storage_home_delegations_ = seq;
}

IR__::AbstractStorageHomeDef_ptr
HomeExecutorDef_impl::binds_to
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::binds_to() called" );
	return binds_to_;
}

void 
HomeExecutorDef_impl::binds_to
(IR__::AbstractStorageHomeDef_ptr binds_to)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "HomeExecutorDef_impl::binds_to(...) called" );
	binds_to_ = binds_to;
}

} // namespace QEDO_ComponentRepository