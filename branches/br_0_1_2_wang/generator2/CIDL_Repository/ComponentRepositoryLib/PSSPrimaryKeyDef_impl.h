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

#ifndef __PSSPRIMARY_KEY_DEF_IMPL_H__
#define __PSSPRIMARY_KEY_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Repository_impl.h"
#include "IDLType_impl.h"

namespace QEDO_ComponentRepository {

class PSSPrimaryKeyDef_impl : public virtual POA_IR__::PSSPrimaryKeyDef,
							public virtual Contained_impl
{
	IDLType_impl *key_idltype_impl_;
public:
	PSSPrimaryKeyDef_impl ( Container_impl *container,
						 Repository_impl *repository,
						 IDLType_impl *key_idltype_impl );

	~PSSPrimaryKeyDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_PSSPrimaryKey;
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
    // IDL:omg.org/IR__/PSSPrimaryKeyDef/is_a:1.0
    //
    virtual CORBA::Boolean is_a(const char* primary_key_id)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/PSSPrimaryKeyDef/primary_key:1.0
    //
    virtual IR__::IDLType_ptr primary_key()
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif
