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

#ifndef __COMPOSITION_DEF_IMPL_H__
#define __COMPOSITION_DEF_IMPL_H__

#include <CORBA.h>
#include "CIDL_Extension_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "Repository_impl.h"
#include "HomeExecutorDef_impl.h"
#include "ExecutorDef_impl.h"
#include "HomeDef_impl.h"

namespace QEDO_ComponentRepository {

class CompositionDef_impl : public virtual POA_CIDL::CompositionDef,
							public virtual Contained_impl,
							public virtual Container_impl
{
	CIDL::LifecycleCategory lifecycle_;
	HomeDef_impl *home_impl_;
	HomeExecutorDef_impl *home_executor_impl_;
	ExecutorDef_impl *executor_impl_;
public:
	CompositionDef_impl ( Container_impl *container,
		            Repository_impl *repository,
					CIDL::LifecycleCategory lifecycle,
					HomeDef_impl *home_impl );

	~CompositionDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Composition;
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
    // IDL:omg.org/CIDL/CompositionDef/ccm_home:1.0
    //
    virtual IR__::HomeDef_ptr ccm_home()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/CompositionDef/component:1.0
    //
    virtual IR__::ComponentDef_ptr ccm_component()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/CompositionDef/lifecycle:1.0
    //
    virtual CIDL::LifecycleCategory lifecycle()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/CompositionDef/home_executor:1.0
    //
    virtual CIDL::HomeExecutorDef_ptr home_executor()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/CompositionDef/executor_def:1.0
    //
    virtual CIDL::ExecutorDef_ptr executor_def()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/CompositionDef/create_home_executor:1.0
    //
    virtual CIDL::HomeExecutorDef_ptr create_home_executor(	const char* id,
															const char* name,
															const char* version	)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/CompositionDef/create_executor:1.0
    //
    virtual CIDL::ExecutorDef_ptr create_executor(	const char* id,
													const char* name,
													const char* version	)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

