/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
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

#ifndef __SEGMENT_DEF_IMPL_H__
#define __SEGMENT_DEF_IMPL_H__

#include <CORBA.h>
#include "CIDL_Extension_skel.h"
#include "Contained_impl.h"
#include "Repository_impl.h"
#include "ProvidesDef_impl.h"

#include <vector>

//using namespace std;

namespace QEDO_ComponentRepository {

class SegmentDef_impl : public virtual POA_CIDL::SegmentDef,
						public virtual Contained_impl
{
	vector < ProvidesDef_impl* > provided_facet_impls_;
public:
	SegmentDef_impl ( Container_impl *container,
		            Repository_impl *repository,
					IR__::ProvidesDefSeq provided_facets );

	~SegmentDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Segment;
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/describe:1.0
    //
	virtual IR__::Contained::Description* describe()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/SegmentDef/provided_facets:1.0
    //
    virtual IR__::ProvidesDefSeq* provided_facets()
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

