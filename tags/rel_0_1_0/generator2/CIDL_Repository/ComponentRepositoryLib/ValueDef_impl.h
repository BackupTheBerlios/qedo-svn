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

#ifndef __VALUE_DEF_IMPL_H__
#define __VALUE_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "Repository_impl.h"
#include "InterfaceDef_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

class ValueDef_impl : public virtual POA_IR__::ValueDef,
						public virtual Container_impl,
						public virtual Contained_impl,
						public virtual IDLType_impl
{
	ValueDef_impl *base_value_impl_;
	IR__::InitializerSeq initializers_;
	vector < InterfaceDef_impl* > supported_interface_impls_;
	vector < vector < IDLType_impl* > > initializers_member_impls_;
	vector < ValueDef_impl* > abstract_base_value_impls_;
	CORBA::Boolean is_abstract_;
	CORBA::Boolean is_custom_;
	CORBA::Boolean is_truncatable_;
public:
	ValueDef_impl ( Container_impl *container, Repository_impl *repository );

	~ValueDef_impl();

	CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq );

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Value;
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
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/supported_interfaces:1.0
    //
    virtual IR__::InterfaceDefSeq* supported_interfaces()
        throw(CORBA::SystemException);
    virtual void supported_interfaces(const IR__::InterfaceDefSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/initializers:1.0
    //
    virtual IR__::InitializerSeq* initializers()
        throw(CORBA::SystemException);
    virtual void initializers(const IR__::InitializerSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/base_value:1.0
    //
    virtual IR__::ValueDef_ptr base_value()
        throw(CORBA::SystemException);
    virtual void base_value(IR__::ValueDef_ptr)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/abstract_base_values:1.0
    //
    virtual IR__::ValueDefSeq* abstract_base_values()
        throw(CORBA::SystemException);
    virtual void abstract_base_values(const IR__::ValueDefSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/is_abstract:1.0
    //
    virtual CORBA::Boolean is_abstract()
        throw(CORBA::SystemException);
    virtual void is_abstract(CORBA::Boolean)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/is_custom:1.0
    //
    virtual CORBA::Boolean is_custom()
        throw(CORBA::SystemException);
    virtual void is_custom(CORBA::Boolean)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/is_truncatable:1.0
    //
    virtual CORBA::Boolean is_truncatable()
        throw(CORBA::SystemException);
    virtual void is_truncatable(CORBA::Boolean)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/is_a:1.0
    //
    virtual CORBA::Boolean is_a(const char* id)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/create_value_member:1.0
    //
    virtual IR__::ValueMemberDef_ptr create_value_member(const char* id,
                                                 const char* name,
                                                 const char* version,
                                                 IR__::IDLType_ptr type,
                                                 CORBA__::Visibility access)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/create_attribute:1.0
    //
    virtual IR__::AttributeDef_ptr create_attribute(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::IDLType_ptr type,
                                            IR__::AttributeMode mode,
                                            const IR__::ExceptionDefSeq& get_exceptions,
                                            const IR__::ExceptionDefSeq& put_exceptions)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ValueDef/create_operation:1.0
    //
    virtual IR__::OperationDef_ptr create_operation(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::IDLType_ptr result,
                                            IR__::OperationMode mode,
                                            const IR__::ParDescriptionSeq& params,
                                            const IR__::ExceptionDefSeq& exceptions,
                                            const IR__::ContextIdSeq& contexts)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

