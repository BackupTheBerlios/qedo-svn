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

#ifndef __ATTRIBUTE_DEF_IMPL_H__
#define __ATTRIBUTE_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "Repository_impl.h"
#include "ExceptionDef_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

class AttributeDef_impl : public virtual POA_IR__::AttributeDef,
						public virtual Contained_impl
{
    IDLType_impl* idl_type_;
	IR__::AttributeMode mode_;
	vector < ExceptionDef_impl* > get_exceptions_;
	vector < ExceptionDef_impl* > put_exceptions_;
public:
	AttributeDef_impl ( Container_impl *container, Repository_impl *repository );

	~AttributeDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Attribute;
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
    // IDL:omg.org/IR__/AttributeDef/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AttributeDef/type_def:1.0
    //
    virtual IR__::IDLType_ptr type_def()
        throw(CORBA::SystemException);
    virtual void type_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AttributeDef/mode:1.0
    //
    virtual IR__::AttributeMode mode()
        throw(CORBA::SystemException);
    virtual void mode(IR__::AttributeMode)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AttributeDef/get_exceptions:1.0
    //
    virtual IR__::ExceptionDefSeq* get_exceptions()
        throw(CORBA::SystemException);
    virtual void get_exceptions(const IR__::ExceptionDefSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AttributeDef/put_exceptions:1.0
    //
    virtual IR__::ExceptionDefSeq* put_exceptions()
        throw(CORBA::SystemException);
    virtual void put_exceptions(const IR__::ExceptionDefSeq&)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

