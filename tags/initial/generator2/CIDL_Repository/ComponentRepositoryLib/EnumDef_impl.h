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

#ifndef __ENUM_DEF_IMPL_H__
#define __ENUM_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "TypedefDef_impl.h"
#include "Contained_impl.h"
#include "Repository_impl.h"

namespace QEDO_ComponentRepository {

class EnumDef_impl : public virtual POA_IR__::EnumDef,
						public virtual TypedefDef_impl
{
	IR__::EnumMemberSeq members_;
public:
	EnumDef_impl ( Container_impl *container, Repository_impl *repository );

	virtual ~EnumDef_impl();

	// Helper function for building recursive type code
	virtual CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq )
	{
		return type();
	}

    virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Enum;
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
    // IDL:omg.org/IR__/EnumDef/members:1.0
    //
    virtual IR__::EnumMemberSeq* members()
        throw(CORBA::SystemException);
    virtual void members(const IR__::EnumMemberSeq&)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif
