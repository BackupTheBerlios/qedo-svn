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

#include "ExecutorDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {
	
ExecutorDef_impl::ExecutorDef_impl
( Container_impl *container,
  Repository_impl *repository )
: IRObject_impl ( repository ),
  Container_impl ( repository ),
  Contained_impl ( container, repository )
{
	DEBUG_OUTLINE ( "ExecutorDef_impl::ExecutorDef_impl() called" );
}

ExecutorDef_impl::~ExecutorDef_impl
()
{
}

void
ExecutorDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExecutorDef_impl::~ExecutorDef_impl() called" );

	Container_impl::destroy();
	Contained_impl::destroy();
}

IR__::Contained::Description*
ExecutorDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExecutorDef_impl::describe() called" );

	CIDL::ExecutorDescription_var executor_desc = new CIDL::ExecutorDescription;
	executor_desc -> id = this -> id();
	executor_desc -> name = this -> name();
	executor_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		executor_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		executor_desc -> defined_in = CORBA::string_dup ( "" );

	// Segments
	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Segment )
		{
			SegmentDef_impl *impl;
			impl = 0;
			impl = dynamic_cast < SegmentDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Segment' cannot be casted to SegmentDef_impl" );
				continue;
			}
			executor_desc -> segments.length ( executor_desc -> segments.length() + 1 );
			executor_desc -> segments [ executor_desc -> segments.length() - 1 ] =
				impl -> _this();
		}
	}

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= executor_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

CIDL::SegmentDefSeq*
ExecutorDef_impl::segments
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExecutorDef_impl::segments() called" );

	CIDL::SegmentDefSeq_var segments_seq = new CIDL::SegmentDefSeq;

	list < Contained_impl* >::const_iterator contained_iter;
	for ( contained_iter = contained_.begin();
			contained_iter != contained_.end();
			contained_iter++ )
	{
		if ( (*contained_iter) -> def_kind() == CORBA__::dk_Segment )
		{
			SegmentDef_impl *impl;
			impl = 0;
			impl = dynamic_cast < SegmentDef_impl* > ( *contained_iter );
			if ( !impl )
			{
				// This cannot be, what to do?
				DEBUG_ERRLINE ( "Fatal error: Contained with kind 'dk_Segment' cannot be casted to SegmentDef_impl" );
				continue;
			}
			segments_seq -> length ( segments_seq -> length() + 1 );
			segments_seq [ segments_seq -> length() - 1 ] = impl -> _this();
		}
	}

	return segments_seq._retn();
}

CIDL::SegmentDef_ptr
ExecutorDef_impl::create_segment
(const char* id,
 const char* name,
 const char* version,
 const IR__::ProvidesDefSeq& provided_facets)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ExecutorDef_impl::create_segment() called" );

	if ( repository_ -> check_for_id ( id ) )
		throw CORBA::BAD_PARAM ( 2, CORBA::COMPLETED_NO );
	if ( check_for_name ( name ) )
		throw CORBA::BAD_PARAM ( 3, CORBA::COMPLETED_NO );

	SegmentDef_impl *new_segment = new SegmentDef_impl ( this, repository_, provided_facets );
	new_segment -> id ( id );
	new_segment -> name ( name );
	new_segment -> version ( version );

	repository_ -> _add_ref();
	this -> _add_ref();

	return new_segment -> _this();
}

} // namespace QEDO_ComponentRepository
