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

#ifndef __FINDER_DEF_IMPL_H__
#define __FINDER_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Repository_impl.h"
#include "OperationDef_impl.h"
#include "ComponentDef_impl.h"

namespace QEDO_ComponentRepository {

class FinderDef_impl : public virtual POA_IR__::FinderDef,
						public virtual OperationDef_impl
{
public:
	FinderDef_impl ( Container_impl *container,
						Repository_impl *repository,
						ComponentDef_impl *component );

	~FinderDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Finder;
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/result:1.0
    //
    virtual CORBA::TypeCode_ptr result()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/result_def:1.0
    //
    virtual void result_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/params:1.0
    //
    virtual void params(const IR__::ParDescriptionSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/mode:1.0
    //
    virtual void mode(IR__::OperationMode)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/OperationDef/contexts:1.0
    //
    virtual void contexts(const IR__::ContextIdSeq&)
        throw(CORBA::SystemException);

};

} // namespace QEDO_ComponentRepository

#endif

