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

#ifndef __CONTAINED_IMPL_H__
#define __CONTAINED_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "IRObject_impl.h"

namespace QEDO_ComponentRepository {

class Container_impl;
class Contained_impl : public virtual POA_IR__::Contained,
						public virtual IRObject_impl
{
protected:
	Container_impl *defined_in_;
	IR__::RepositoryId_var id_;
    IR__::Identifier_var name_;
    IR__::VersionSpec_var version_;
public:
	Contained_impl ( Container_impl*, Repository_impl* );

	virtual ~Contained_impl ();

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
	virtual void destroy()
		throw(CORBA::SystemException);
 
    //
    // IDL:omg.org/IR__/Contained/id:1.0
    //
    virtual IR__::RepositoryId id()
        throw(CORBA::SystemException);
    virtual void id(const char*)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/name:1.0
    //
    virtual IR__::Identifier name()
        throw(CORBA::SystemException);
    virtual void name(const char*)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/version:1.0
    //
    virtual IR__::VersionSpec version()
        throw(CORBA::SystemException);
    virtual void version(const char*)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/defined_in:1.0
    //
    virtual IR__::Container_ptr defined_in()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/absolute_name:1.0
    //
    virtual IR__::ScopedName absolute_name()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/containing_repository:1.0
    //
    virtual IR__::Repository_ptr containing_repository()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/describe:1.0
    //
    virtual IR__::Contained::Description* describe()
        throw(CORBA::SystemException) = 0;

    //
    // IDL:omg.org/IR__/Contained/move:1.0
    //
    virtual void move(IR__::Container_ptr new_container,
                      const char* new_name,
                      const char* new_version)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif