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

#include "SegmentDef_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

SegmentDef_impl::SegmentDef_impl
( Container_impl *container,
  Repository_impl *repository,
  IR__::ProvidesDefSeq provided_facets )
: Contained_impl ( container, repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "SegmentDef_impl::SegmentDef_impl() called" );

    unsigned int i;

    vector < ProvidesDef_impl* > impl_seq;
    impl_seq.resize ( provided_facets.length(), NULL );

    for ( i = 0; i < provided_facets.length(); i++ )
    {
        if ( CORBA::is_nil ( provided_facets[i] ) )
            throw CORBA::BAD_PARAM(); // Is this exception correct?

        impl_seq[i] = 0;

        try
        {
			PortableServer::ServantBase_var servant =
				repository_ -> poa() -> reference_to_servant(provided_facets[i]);
            impl_seq[i] = dynamic_cast<ProvidesDef_impl*>(servant.in());
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

    for ( i = 0; i < provided_facet_impls_.size(); i++)
        provided_facet_impls_[i] -> _remove_ref();

    provided_facet_impls_ = impl_seq;
}

SegmentDef_impl::~SegmentDef_impl
()
{
	DEBUG_OUTLINE ( "SegmentDef_impl::~SegmentDef_impl() called" );
}

void
SegmentDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SegmentDef_impl::destroy() called" );

    for ( unsigned int i = 0; i < provided_facet_impls_.size(); i++ )
        provided_facet_impls_[i] -> _remove_ref();

    Contained_impl::destroy();
}

IR__::Contained::Description*
SegmentDef_impl::describe
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SegmentDef_impl::describe() called" );

	CIDL::SegmentDescription_var segment_desc = new CIDL::SegmentDescription;
	segment_desc -> id = this -> id();
	segment_desc -> name = this -> name();
	segment_desc -> version = this -> version();
	Contained_impl *contained = dynamic_cast<Contained_impl*>(defined_in_);
	if ( contained )
		segment_desc -> defined_in = CORBA::string_dup ( contained -> id() );
	else
		segment_desc -> defined_in = CORBA::string_dup ( "" );

	segment_desc -> provided_facets.length ( provided_facet_impls_.size() );
	for ( unsigned int i = 0; i < provided_facet_impls_.size(); i++ )
	{
		segment_desc -> provided_facets[i] = provided_facet_impls_[i] -> _this();
	}

	IR__::Contained::Description_var desc = new IR__::Contained::Description();
	desc -> kind = def_kind();
	CORBA::Any any;
	any <<= segment_desc._retn();;
	desc -> value = any;

	return desc._retn();
}

IR__::ProvidesDefSeq*
SegmentDef_impl::provided_facets
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SegmentDef_impl::provided_facets() called" );

	IR__::ProvidesDefSeq_var provided_facet_seq = new IR__::ProvidesDefSeq;

	provided_facet_seq -> length ( provided_facet_impls_.size() );
	for ( unsigned int i = 0; i < provided_facet_impls_.size(); i++ )
	{
		provided_facet_seq.inout()[i] = provided_facet_impls_[i] -> _this();
	}

	return provided_facet_seq._retn();
}

} // namespace QEDO_ComponentRepository 
