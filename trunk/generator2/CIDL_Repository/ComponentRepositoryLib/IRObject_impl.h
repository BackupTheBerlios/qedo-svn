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

#ifndef __IROBJECT_IMPL_H__
#define __IROBJECT_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"

#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

namespace QEDO_ComponentRepository {

class Repository_impl;

class IRObject_impl : public virtual POA_CORBA__::IRObject,
						public virtual PortableServer::RefCountServantBase
{
protected:
	Repository_impl *repository_;
	static int ir_object_count_;
public:
	IRObject_impl ( Repository_impl* );

	virtual ~IRObject_impl ();

	static unsigned long number_ir_objects () { return ir_object_count_; }

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
    virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException) = 0;

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

