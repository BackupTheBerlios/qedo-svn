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

#include "CompositionDef_impl.h"
#include "Debug.h"
#include "HomeExecutorDef_impl.h"
#include "ExecutorDef_impl.h"

namespace QEDO_ComponentRepository {

CompositionDef_impl::CompositionDef_impl
( Container_impl *container,
  Repository_impl *repository,
  CIDL::LifecycleCategory lifecycle,
  HomeDef_impl *home_impl)
: IRObject_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "CompositionDef_impl::CompositionDef_impl() called" );

	home_impl_ = home_impl;
	home_impl_ -> _add_ref();
	
	lifecycle_ = lifecycle;
	home_executor_impl_ = NULL;
	executor_impl_ = NULL;
}

CompositionDef_impl::~CompositionDef_impl
()
{
	DEBUG_OUTLINE ( "CompositionDef_impl::~CompositionDef_impl() called" );
}

void
CompositionDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::destroy() called" );

	home_impl_ -> _remove_ref();

	Container_impl::destroy();
	Contained_impl::destroy();
}

IR__::Contained::Description*
CompositionDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::describe() called" );

	CIDL::CompositionDescription_var composition_desc = new CIDL::CompositionDescription;
	composition_desc -> id = this -> id();
	composition_desc -> name = this -> name();
	composition_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		composition_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		composition_desc -> defined_in = CORBA::string_dup ( "" );

	composition_desc -> lifecycle = this -> lifecycle();
	composition_desc -> home_executor = this -> home_executor();
	composition_desc -> executor_def = this -> executor_def();

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= composition_desc._retn();
	desc -> value = any;

	return desc._retn();
}

IR__::HomeDef_ptr
CompositionDef_impl::ccm_home
()
throw(CORBA::SystemException)
{
	return IR__::HomeDef::_duplicate ( home_impl_ -> _this() );
}

IR__::ComponentDef_ptr 
CompositionDef_impl::ccm_component
()
throw(CORBA::SystemException)
{
	return IR__::ComponentDef::_duplicate ( home_impl_ -> managed_component() );
}

CIDL::LifecycleCategory
CompositionDef_impl::lifecycle
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::lifecycle() called" );

	return lifecycle_;
}

CIDL::HomeExecutorDef_ptr
CompositionDef_impl::home_executor
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::home_executor() called" );

    if ( home_executor_impl_ )
        return home_executor_impl_ -> _this();
    else
        return CIDL::HomeExecutorDef::_nil();
}

CIDL::ExecutorDef_ptr
CompositionDef_impl::executor_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::executor() called" );

    if ( executor_impl_ )
        return executor_impl_ -> _this();
    else
        return CIDL::ExecutorDef::_nil();
}

CIDL::HomeExecutorDef_ptr 
CompositionDef_impl::create_home_executor
( const char* id,
  const char* name,
  const char* version,
  IR__::StorageHomeDef_ptr storagehome)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::create_home_executor() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	HomeExecutorDef_impl *new_home_executor =
		new HomeExecutorDef_impl ( this, repository_, storagehome );
	new_home_executor -> id ( id );
	new_home_executor -> name ( name );
	new_home_executor -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	home_executor_impl_ = new_home_executor;

	return new_home_executor -> _this();
}

CIDL::ExecutorDef_ptr
CompositionDef_impl::create_executor
( const char* id,
  const char* name,
  const char* version )
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "CompositionDef_impl::create_executor() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	ExecutorDef_impl *new_executor =
		new ExecutorDef_impl ( this, repository_ );
	new_executor -> id ( id );
	new_executor -> name ( name );
	new_executor -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	executor_impl_ = new_executor;

	return new_executor -> _this();
}

} // namespace QEDO_ComponentRepository
