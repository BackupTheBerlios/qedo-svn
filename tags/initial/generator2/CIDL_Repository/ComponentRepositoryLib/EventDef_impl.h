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

#ifndef __EVENT_DEF_IMPL_H__
#define __EVENT_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "Repository_impl.h"
#include "ValueDef_impl.h"

namespace QEDO_ComponentRepository {

class EventDef_impl : public virtual POA_IR__::EventDef,
						public virtual Contained_impl
{
	ValueDef_impl *event_type_impl_;
public:
	EventDef_impl ( Container_impl *container,
		            Repository_impl *repository,
					ValueDef_impl *event_type_impl );

	virtual ~EventDef_impl();

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
    // IDL:omg.org/IR__/EventDef/is_a:1.0
    //
    virtual CORBA::Boolean is_a(const char* event_id)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/EventDef/event:1.0
    //
    virtual IR__::ValueDef_ptr event()
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif