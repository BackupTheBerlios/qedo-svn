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

#ifndef __ABS_STORAGEHOME_DEF_IMPL_H__
#define __ABS_STORAGEHOME_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Repository_impl.h"
#include "InterfaceDef_impl.h"
#include "AbsStorageTypeDef_impl.h"

namespace QEDO_ComponentRepository {

class AbstractStorageHomeDef_impl : public virtual POA_IR__::AbstractStorageHomeDef,
							public virtual InterfaceDef_impl
{
	AbstractStorageTypeDef_impl *managed_abstract_storage_type_impl_;
	vector < AbstractStorageHomeDef_impl* > base_abstract_storage_home_impls_;

public:
	AbstractStorageHomeDef_impl ( Container_impl *container,
							Repository_impl *repository,
							AbstractStorageTypeDef_impl *managed_abstract_storage_type_impl);

	~AbstractStorageHomeDef_impl();

	//
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_AbstractStorageHome;
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
    // IDL:omg.org/IR__/AbstractStorageHomeDef/managed_abstract_storage_type:1.0
    //
    virtual IR__::AbstractStorageTypeDef_ptr managed_abstract_storage_type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AbstractStorageHomeDef/base_abstract_storage_homes:1.0
    //
    virtual IR__::AbsStorageHomeDefSeq* base_abstract_storage_homes()
        throw(CORBA::SystemException);
    virtual void base_abstract_storage_homes(const IR__::AbsStorageHomeDefSeq& seq)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AbstractStorageHomeDef/factories:1.0
    //
    virtual IR__::FactoryDefSeq* factories()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AbstractStorageHomeDef/finders:1.0
    //
    virtual IR__::PSSFinderDefSeq* finders()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AbstractStorageHomeDef/create_factory:1.0
    //
    virtual IR__::FactoryDef_ptr create_factory(const char* id,
                                                   const char* name,
                                                   const char* version,
                                                   const IR__::ParDescriptionSeq& params,
                                                   const IR__::ExceptionDefSeq& exceptions)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/AbstractStorageHomeDef/create_finder:1.0
    //
    virtual IR__::PSSFinderDef_ptr create_finder(const char* id,
                                                 const char* name,
                                                 const char* version,
                                                 const IR__::ParDescriptionSeq& params,
                                                 const IR__::ExceptionDefSeq& exceptions)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

