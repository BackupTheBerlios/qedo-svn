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

#ifndef __OPERATION_DEF_IMPL_H__
#define __OPERATION_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "Repository_impl.h"
#include "ExceptionDef_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

class OperationDef_impl : public virtual POA_IR__::OperationDef,
						public virtual Contained_impl
{
	IDLType_impl* result_impl_;
	IR__::OperationMode mode_;
	IR__::ParDescriptionSeq params_;
	IR__::ContextIdSeq contexts_;
	vector < IDLType_impl* > param_impls_;
	vector < ExceptionDef_impl* > exception_impls_;
public:
	OperationDef_impl ( Container_impl *container, Repository_impl *repository );

	~OperationDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Operation;
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
    // IDL:omg.org/IR__/OperationDef/result:1.0
    //
    virtual CORBA::TypeCode_ptr result()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/result_def:1.0
    //
    virtual IR__::IDLType_ptr result_def()
        throw(CORBA::SystemException);
    virtual void result_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/params:1.0
    //
    virtual IR__::ParDescriptionSeq* params()
        throw(CORBA::SystemException);
    virtual void params(const IR__::ParDescriptionSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/mode:1.0
    //
    virtual IR__::OperationMode mode()
        throw(CORBA::SystemException);
    virtual void mode(IR__::OperationMode)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/contexts:1.0
    //
    virtual IR__::ContextIdSeq* contexts()
        throw(CORBA::SystemException);
    virtual void contexts(const IR__::ContextIdSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/exceptions:1.0
    //
    virtual IR__::ExceptionDefSeq* exceptions()
        throw(CORBA::SystemException);
    virtual void exceptions(const IR__::ExceptionDefSeq&)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif
