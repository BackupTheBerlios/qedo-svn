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

#ifndef __EXCEPTION_DEF_IMPL_H__
#define __EXCEPTION_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Container_impl.h"
#include "Contained_impl.h"
#include "Repository_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

	class ExceptionDef_impl : public virtual POA_IR__::ExceptionDef,
								public virtual Contained_impl,
								public virtual Container_impl
{
	IR__::StructMemberSeq members_;
    vector < IDLType_impl* > members_impls_;
public:
	ExceptionDef_impl ( Container_impl *container, Repository_impl *repository );

	~ExceptionDef_impl();

	CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq );

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Exception;
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
    // IDL:omg.org/IR__/ExceptionDef/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ExceptionDef/members:1.0
    //
    virtual IR__::StructMemberSeq* members()
        throw(CORBA::SystemException);
    virtual void members(const IR__::StructMemberSeq&)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif
