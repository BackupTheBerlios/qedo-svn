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

#ifndef __HOME_DEF_IMPL_H__
#define __HOME_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Repository_impl.h"
#include "InterfaceDef_impl.h"
#include "ComponentDef_impl.h"

namespace QEDO_ComponentRepository {

class HomeDef_impl : public virtual POA_IR__::HomeDef,
					 public virtual InterfaceDef_impl
{
	HomeDef_impl *base_home_impl_;
	ComponentDef_impl *managed_component_impl_;
	vector < InterfaceDef_impl* > supported_interface_impls_;
	ValueDef_impl *primary_key_impl_;
	IR__::PrimaryKeyDef_ptr primary_key_;
public:
	HomeDef_impl ( Container_impl *container,
					    Repository_impl *repository,
						HomeDef_impl *base_home_impl,
						ComponentDef_impl *managed_component_impl,
						ValueDef_impl *primary_key );

	~HomeDef_impl();

	//
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Home;
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
    // IDL:omg.org/IR__/HomeDef/base_home:1.0
    //
    virtual IR__::HomeDef_ptr base_home()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/managed_component:1.0
    //
    virtual IR__::ComponentDef_ptr managed_component()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/supported_interfaces:1.0
    //

    virtual IR__::InterfaceDefSeq* supported_interfaces()
        throw(CORBA::SystemException);

    virtual void supported_interfaces(const IR__::InterfaceDefSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/primary_key:1.0
    //
    virtual IR__::PrimaryKeyDef_ptr primary_key()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/factories:1.0
    //
    virtual IR__::FactoryDefSeq* factories()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/finders:1.0
    //
    virtual IR__::FinderDefSeq* finders()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/is_basic:1.0
    //
    virtual CORBA::Boolean is_basic()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/create_primary_key:1.0
    //
    virtual IR__::PrimaryKeyDef_ptr create_primary_key(const char* id,
                                                       const char* name,
                                                       const char* version,
                                                       IR__::ValueDef_ptr primary_key)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/create_factory:1.0
    //
    virtual IR__::FactoryDef_ptr create_factory(const char* id,
                                                const char* name,
                                                const char* version,
                                                const IR__::ParDescriptionSeq& params,
                                                const IR__::ExceptionDefSeq& exceptions)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/HomeDef/create_finder:1.0
    //
    virtual IR__::FinderDef_ptr create_finder(const char* id,
                                              const char* name,
                                              const char* version,
                                              const IR__::ParDescriptionSeq& params,
                                              const IR__::ExceptionDefSeq& exceptions)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

