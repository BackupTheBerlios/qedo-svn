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

#ifndef __HOME_EXECUTOR_DEF_IMPL_H__
#define __HOME_EXECUTOR_DEF_IMPL_H__

#include <CORBA.h>
#include "CIDL_Extension_skel.h"
#include "Contained_impl.h"
#include "Repository_impl.h"
#include "AbsStorageHomeDef_impl.h"

namespace QEDO_ComponentRepository {

class HomeExecutorDef_impl : public virtual POA_CIDL::HomeExecutorDef,
							 public virtual Contained_impl
{
	IR__::StorageHomeDef_ptr binds_to_;
	CIDL::DelegationSeq delegations_;
	CIDL::StorageHomeDelegationSeq storagehome_delegations_;

public:
	HomeExecutorDef_impl ( Container_impl *container,
							Repository_impl *repository,
							IR__::StorageHomeDef_ptr binds_to);

	~HomeExecutorDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_HomeExecutor;
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
    // IDL:omg.org/CIDL/HomeExecutorDef/delegations:1.0
    //
    virtual CIDL::DelegationSeq* delegations()
        throw(CORBA::SystemException);
    virtual void delegations(const CIDL::DelegationSeq&)
        throw(CORBA::SystemException);

	//
    // IDL:omg.org/CIDL/HomeExecutorDef/storagehome_delegations:1.0
    //
    virtual CIDL::StorageHomeDelegationSeq* storagehome_delegations()
		throw(CORBA::SystemException);
    virtual void storagehome_delegations(const CIDL::StorageHomeDelegationSeq&)
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/CIDL/HomeExecutorDef/binds_to:1.0
    //
    virtual IR__::StorageHomeDef_ptr binds_to()
        throw(CORBA::SystemException);
    virtual void binds_to(IR__::StorageHomeDef_ptr)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif
