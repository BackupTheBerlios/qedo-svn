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

#ifndef __EXECUTOR_DEF_IMPL_H__
#define __EXECUTOR_DEF_IMPL_H__

#include <CORBA.h>
#include "CIDL_Extension_skel.h"
#include "Contained_impl.h"
#include "Repository_impl.h"
#include "SegmentDef_impl.h"

namespace QEDO_ComponentRepository {

class ExecutorDef_impl : public virtual POA_CIDL::ExecutorDef,
							 public virtual Contained_impl,
							 public virtual Container_impl
{
public:
	ExecutorDef_impl ( Container_impl *container,
		            Repository_impl *repository );

	~ExecutorDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Executor;
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
    // IDL:omg.org/CIDL/ExecutorDef/segments:1.0
    //
    virtual CIDL::SegmentDefSeq* segments()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/ExecutorDef/create_segment:1.0
    //
    virtual CIDL::SegmentDef_ptr create_segment(const char* id,
                                                const char* name,
                                                const char* version,
                                                const IR__::ProvidesDefSeq& provided_facets)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

