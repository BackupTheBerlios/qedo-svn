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
#ifndef __STORAGETYPE_DEF_IMPL_H__
#define __STORAGETYPE_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "InterfaceDef_impl.h"
#include "Debug.h"
#include <vector>

using namespace std;


namespace QEDO_ComponentRepository {

class StorageTypeDef_impl : public virtual POA_IR__::StorageTypeDef,
							public virtual InterfaceDef_impl
{
	StorageTypeDef_impl *base_storagetype_impl_;
	vector < InterfaceDef_impl* > supported_interface_impls_;

public:
	StorageTypeDef_impl ( Container_impl *container,
					      Repository_impl *repository,
						  StorageTypeDef_impl *base_storagetype_impl );

	~StorageTypeDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_StorageType;
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
    // IDL:omg.org/IR__/StorageTypeDef/supported_interfaces:1.0
    //
    virtual IR__::InterfaceDefSeq* supported_interfaces()
        throw(CORBA::SystemException);
    virtual void supported_interfaces(const IR__::InterfaceDefSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageTypeDef/base_storagetype:1.0
    //
    virtual IR__::StorageTypeDef_ptr base_storagetype()
        throw(CORBA::SystemException);

	//
    // IDL:omg.org/IR__/StorageTypeDef/get_state_members:1.0
    //
	virtual void get_state_members(IR__::AttributeDefSeq& state_members,
                                  CORBA__::CollectStyle style)
        throw(CORBA::SystemException);
    
};

} // namespace QEDO_ComponentRepository

#endif
