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

#include "Contained_impl.h"
#include "Repository_impl.h"
#include "Debug.h"

#include <string>

using namespace std;

namespace QEDO_ComponentRepository {

Contained_impl::Contained_impl
( Container_impl *container,
  Repository_impl *repository )
: IRObject_impl ( repository )
{
	DEBUG_OUT ( "Contained_impl::Contained_impl() called " );

	DEBUG_OUT ( "--> Container=" );

	if ( container == repository )
		DEBUG_OUTLINE ( "Repository" )
	else
	{
		// The container must also be a contained object
		Contained_impl * contained = dynamic_cast<Contained_impl*>(container);
		if ( container )
			DEBUG_OUTLINE ( contained -> name() )
		else
			DEBUG_OUTLINE ( "???" );
	}

	defined_in_ = container;
}

Contained_impl::~Contained_impl
()
{
	DEBUG_OUT ( "Contained_impl::~Contained_impl() called " );
	DEBUG_OUT ( "--> name=" ); DEBUG_OUTLINE ( name() );
}

void
Contained_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Contained_impl::destroy() called" );

	repository_ -> remove_id ( id_ );
	repository_ -> _remove_ref();
	defined_in_ -> remove_name ( name_ );
	defined_in_ -> _remove_ref();

	IRObject_impl::destroy();

	this -> _remove_ref();
}

IR__::RepositoryId
Contained_impl::id
()
throw(CORBA::SystemException)
{
	if ( !id_.in() )
	{
		DEBUG_ERRLINE ( "*** No id set" );
		throw CORBA::BAD_INV_ORDER();
	}
	return CORBA::string_dup ( id_ );
}

void
Contained_impl:: id
(const char* id)
throw(CORBA::SystemException)
{
	if ( id_ && !strcmp ( id, id_ ) )
		return;

	if ( repository_ -> check_for_id ( id ) )
	{
		DEBUG_ERRLINE ( "*** Id already in repository" );
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	}

	if ( id_ )
	{
		repository_ -> remove_id ( id_ );
	}

	id_ = CORBA::string_dup ( id );
	repository_ -> add_id ( id_, this );
}

IR__::Identifier
Contained_impl::name
()
throw(CORBA::SystemException)
{
	if ( !name_.in() )
	{
		DEBUG_ERRLINE ( "*** No Name set" );
		throw CORBA::BAD_INV_ORDER();
	}
	return CORBA::string_dup ( name_ );
}

void
Contained_impl::name
(const char* name)
throw(CORBA::SystemException)
{
	if ( name_ && !strcmp ( name, name_ ) )
		return;

	if ( defined_in_ -> check_for_name ( name ) )
	{
		DEBUG_ERRLINE ( "*** Name already in Container" );
		throw CORBA::BAD_PARAM ( 1 , CORBA::COMPLETED_NO );
	}

	if ( name_ )
	{
		defined_in_ -> remove_name ( name_ );
	}

	name_ = CORBA::string_dup ( name );
	defined_in_ -> add_name ( name_, this );
}

IR__::VersionSpec
Contained_impl::version
()
throw(CORBA::SystemException)
{
	if ( !version_.in() )
	{
		DEBUG_ERRLINE ( "*** No version set" );
		throw CORBA::BAD_INV_ORDER();
	}
	return CORBA::string_dup ( version_ );
}

void
Contained_impl::version
(const char* version)
throw(CORBA::SystemException)
{
	version_ = CORBA::string_dup ( version );
}

IR__::Container_ptr
Contained_impl::defined_in
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Contained_impl::defined_in() called" );
	return defined_in_->_this();
}

IR__::ScopedName
Contained_impl::absolute_name
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Contained_impl::absolute_name() called" );
	Contained_impl* contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
	{
		string scope_name = contained->absolute_name();
		string my_name = this -> name();
		string abs_name = scope_name + "::" + my_name;
		return CORBA::string_dup ( abs_name.c_str() );
	}
	else	// We are defined directly in the Component Repository root
	{
		string abs_name = this -> name();
		abs_name = "::" + abs_name;
		return CORBA::string_dup ( abs_name.c_str() );
	}
}

IR__::Repository_ptr
Contained_impl::containing_repository
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Contained_impl::containing_repository() called" );
	return repository_ -> _this();
}

void
Contained_impl::move
(IR__::Container_ptr new_container,
 const char* new_name,
 const char* new_version)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "Contained_impl::move() called" );

	PortableServer::POA_var poa = repository_ -> poa();
    Container_impl* try_new_container = 0;
    Contained_impl* try_new_contained = 0;
    try
    {
		PortableServer::ServantBase_var servant = poa -> reference_to_servant(new_container);
        try_new_container = dynamic_cast<Container_impl*>(servant.in());
		try_new_contained = dynamic_cast<Contained_impl*>(servant.in());
    }
	catch ( ... )
	{
	}
	if ( !try_new_container )
	{
		DEBUG_ERRLINE ( "*** New container is not a container within this repository" );
		throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
	}

	// Test whether we are already in the new container
	if ( defined_in_ == try_new_container )
	{
		DEBUG_OUTLINE ( "Already in the new container" );
		return;
	}

	// Test whether the new container is me
	if ( try_new_contained == this )
	{
		DEBUG_ERRLINE ( "*** Cannot move into myself" );
		throw CORBA::BAD_PARAM ( 4, CORBA::COMPLETED_NO );
	}

	// We now have to check, whether it is allowed to copy into
	// the new container (for instance attributes cannot go to a
	// module
	// TODO

	// Furthermore we must check for recursions, so moving a container
	// into one of its childs causes recursion
	Contained_impl* contained =	dynamic_cast<Contained_impl*>(try_new_container);
	
	while ( contained )
	{
		IR__::Container_var container = contained -> defined_in();
		PortableServer::ServantBase_var servant = 
			poa -> reference_to_servant(container);

		if ( servant.in() == this )
		{
			DEBUG_ERRLINE ( "*** Cannot move into child container" );
			// No minor code in the standard for this situation, so use 5
			throw CORBA::BAD_PARAM ( 5, CORBA::COMPLETED_NO );
		}

		contained = dynamic_cast<Contained_impl*>(servant.in());
	}

	if ( try_new_container -> check_for_name ( new_name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	defined_in_ -> remove_name ( name_ );
	defined_in_ -> _remove_ref();
	version ( new_version ); 
	defined_in_ = try_new_container;
	name ( new_name );
	defined_in_ -> add_name ( name_, this );
	defined_in_ -> _add_ref();
}

} // namespace QEDO_ComponentRepository