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
#ifndef __STORAGEHOME_DEF_IMPL_H__
#define __STORAGEHOME_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Repository_impl.h"
#include "InterfaceDef_impl.h"
#include "IDLType_impl.h"
#include "StorageTypeDef_impl.h"
#include "FactoryDef_impl.h"
#include "KeyDef_impl.h"
#include "PSSPrimaryKeyDef_impl.h"
#include "Debug.h"


namespace QEDO_ComponentRepository {

class StorageHomeDef_impl : public virtual POA_IR__::StorageHomeDef,
							public virtual InterfaceDef_impl
{
	StorageTypeDef_impl *managed_storagetype_impl_;	
	StorageHomeDef_impl *base_storagehome_impl_;
	vector < InterfaceDef_impl* > supported_interface_impls_;
	IDLType_impl *primary_key_impl_;

public:
	StorageHomeDef_impl ( Container_impl *container,
							Repository_impl *repository,
							StorageTypeDef_impl *managed_storagetype_impl,
							StorageHomeDef_impl *base_storagehome_impl,
							IDLType_impl *primary_key );

	~StorageHomeDef_impl();

	//
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_StorageHome;
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
    // IDL:omg.org/IR__/StorageHomeDef/base_storagehome:1.0
    //
    virtual IR__::StorageHomeDef_ptr base_storagehome()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/managed_storagetype:1.0
    //
    virtual IR__::StorageTypeDef_ptr managed_storagetype()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/supported_interfaces:1.0
    //
    virtual IR__::InterfaceDefSeq* supported_interfaces()
		throw(CORBA::SystemException);
    virtual void supported_interfaces(const IR__::InterfaceDefSeq&)
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/primary_key:1.0
    //
    virtual IR__::PSSPrimaryKeyDef_ptr primary_key()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/factories:1.0
    //
    virtual IR__::FactoryDefSeq* factories()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/keys:1.0
    //
    virtual IR__::KeyDefSeq* keys()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/create_primary_key:1.0
    //
    virtual IR__::PSSPrimaryKeyDef_ptr create_primary_key(const char* id,
                                                       const char* name,
                                                       const char* version,
                                                       IR__::IDLType_ptr primary_key)
	   throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/create_factory:1.0
    //
    virtual IR__::FactoryDef_ptr create_factory(const char* id,
                                                const char* name,
                                                const char* version,
                                                const IR__::ParDescriptionSeq& params,
                                                const IR__::ExceptionDefSeq& exceptions)
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StorageHomeDef/create_key:1.0
    //
    virtual IR__::KeyDef_ptr create_key(const char* id,
                                        const char* name,
                                        const char* version,
                                        const IR__::ParDescriptionSeq& params)
		throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

