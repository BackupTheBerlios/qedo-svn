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

#ifndef __ALIAS_DEF_IMPL_H__
#define __ALIAS_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "TypedefDef_impl.h"
#include "Repository_impl.h"

namespace QEDO_ComponentRepository {

class AliasDef_impl : public virtual POA_IR__::AliasDef,
						public virtual TypedefDef_impl
{
	IDLType_impl *original_idl_type_impl_;
public:
	AliasDef_impl ( Container_impl *container, Repository_impl *repository );

	~AliasDef_impl();

	// Helper function for building recursive type code
	virtual CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq );

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Alias;
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ConstantDef/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AliasDef/original_type_def:1.0
    //
    virtual IR__::IDLType_ptr original_type_def()
        throw(CORBA::SystemException);
    virtual void original_type_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif