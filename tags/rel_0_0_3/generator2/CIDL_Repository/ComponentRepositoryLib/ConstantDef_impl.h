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

#ifndef __CONSTANT_DEF_IMPL_H__
#define __CONSTANT_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "Repository_impl.h"

namespace QEDO_ComponentRepository {

class ConstantDef_impl : public virtual POA_IR__::ConstantDef,
						public virtual Contained_impl
{
	IDLType_impl *idl_type_;
	CORBA::Any value_;
public:
	ConstantDef_impl ( Container_impl *container, Repository_impl *repository );

	~ConstantDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Constant;
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
    // IDL:omg.org/IR__/ConstantDef/type:1.0
    //
    virtual CORBA::TypeCode_ptr type();

    //
    // IDL:omg.org/IR__/ConstantDef/type_def:1.0
    //
    virtual IR__::IDLType_ptr type_def();
    virtual void type_def(IR__::IDLType_ptr);

    //
    // IDL:omg.org/IR__/ConstantDef/value:1.0
    //
    virtual CORBA::Any* value();
    virtual void value(const CORBA::Any&);
};

} // namespace QEDO_ComponentRepository

#endif