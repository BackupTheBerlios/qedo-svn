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

#ifndef __CATALOG_DEF_IMPL_H__
#define __CATALOG_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "InterfaceDef_impl.h"
#include "ProvidesDef_impl.h"
#include <vector>

using namespace std;


namespace QEDO_ComponentRepository {

class CatalogDef_impl : public virtual POA_IR__::CatalogDef,
						public virtual InterfaceDef_impl
{
    
public:
	CatalogDef_impl ( Container_impl *container, Repository_impl *repository );

	~CatalogDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Catalog;
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
    // IDL:omg.org/IR__/CatalogDef/provides_interfaces:1.0
    //
    virtual IR__::ProvidesDefSeq* provides_interfaces()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/CatalogDef/create_provides:1.0
    //
    virtual IR__::ProvidesDef_ptr create_provides(const char* id,
                                                  const char* name,
                                                  const char* version,
                                                  IR__::InterfaceDef_ptr interface_type)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif
