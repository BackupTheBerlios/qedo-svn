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

#ifndef __UNION_DEF_IMPL_H__
#define __UNION_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Container_impl.h"
#include "TypedefDef_impl.h"
#include "Repository_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

class UnionDef_impl : public virtual POA_IR__::UnionDef,
						public virtual TypedefDef_impl,
						public virtual Container_impl
{
	IDLType_impl *discriminator_type_impl_;
	IR__::UnionMemberSeq members_;
	vector < IDLType_impl* > member_impls_; 
public:
	UnionDef_impl ( Container_impl *container, Repository_impl *repository );

	~UnionDef_impl();

	virtual CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq );

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Union;
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/UnionDef/discriminator_type:1.0
    //
    virtual CORBA::TypeCode_ptr discriminator_type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/UnionDef/discriminator_type_def:1.0
    //
    virtual IR__::IDLType_ptr discriminator_type_def()
        throw(CORBA::SystemException);
    virtual void discriminator_type_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/UnionDef/members:1.0
    //
    virtual IR__::UnionMemberSeq* members()
        throw(CORBA::SystemException);
    virtual void members(const IR__::UnionMemberSeq&)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif