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

#ifndef __INTERFACE_DEF_IMPL_H__
#define __INTERFACE_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "Repository_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

class InterfaceDef_impl : public virtual POA_IR__::InterfaceDef,
							public virtual Container_impl,
							public virtual Contained_impl,
							public virtual IDLType_impl
{
	vector < InterfaceDef_impl* > base_interfaces_;
	CORBA::Boolean is_abstract_;
	CORBA::Boolean is_local_;
public:
	InterfaceDef_impl ( Container_impl *container, Repository_impl *repository );

	virtual ~InterfaceDef_impl();

	CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq )
	{
		return this -> type();
	}

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Interface;
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
    // IDL:omg.org/IR__/Container/contents:1.0
    //
    virtual IR__::ContainedSeq* contents(CORBA__::DefinitionKind limit_type,
                                         CORBA::Boolean exclude_inherited)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ExceptionDef/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/InterfaceDef/base_interfaces:1.0
    //
    virtual IR__::InterfaceDefSeq* base_interfaces()
        throw(CORBA::SystemException) ;
    virtual void base_interfaces(const IR__::InterfaceDefSeq&)
        throw(CORBA::SystemException) ;

    //
    // IDL:omg.org/IR__/InterfaceDef/is_abstract:1.0
    //
    virtual CORBA::Boolean is_abstract()
       throw(CORBA::SystemException);
    virtual void is_abstract(CORBA::Boolean)
       throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/InterfaceDef/is_local:1.0
    //
    virtual CORBA::Boolean is_local()
        throw(CORBA::SystemException);
    virtual void is_local(CORBA::Boolean)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/InterfaceDef/is_a:1.0
    //
    virtual CORBA::Boolean is_a(const char* interface_id)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/InterfaceDef/create_attribute:1.0
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
    // IDL:omg.org/IR__/InterfaceDef/create_operation:1.0
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

