/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#ifndef __EXECUTOR_VALUETYPES_H__
#define __EXECUTOR_VALUETYPES_H__

#include <CORBA.h>
#include "dinner_EQUIVALENT.h"

namespace dinner {

class Cookie_impl : public virtual OBV_Components::Cookie,
					public virtual CORBA::DefaultValueRefCountBase
{
private:
    static CORBA::LongLong cookie_key_;

	void operator=(const Cookie_impl&);
	Cookie_impl (const Cookie_impl&);

public:
	Cookie_impl();
	~Cookie_impl();

	// Extension
	CORBA::Boolean equal (Components::Cookie*);
};


class CookieFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


class PhilosopherState_impl : public virtual OBV_dinner::PhilosopherState,
							  public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator= (const PhilosopherState_impl& val);
	PhilosopherState_impl (const PhilosopherState_impl&);

public:
	PhilosopherState_impl (dinner::PhilosopherStatus, const char*, dinner::Philosopher_ptr);
	PhilosopherState_impl();
	~PhilosopherState_impl();
};


class PhilosopherStateFactory_impl : public virtual dinner::PhilosopherState_init 
{
private:	
	virtual CORBA::ValueBase* create_for_unmarshal();

public:
	dinner::PhilosopherState* create (dinner::PhilosopherStatus, const char*, dinner::Philosopher_ptr);
};

} // namespace dinner

#endif