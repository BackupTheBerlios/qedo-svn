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

static char rcsid[] = "$Id: ExecutorValuetypes.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $";

#include "ExecutorValuetypes.h"

namespace dinner {

CORBA::LongLong Cookie_impl::cookie_key_ = 0;

//
// Cookie
//
Cookie_impl::Cookie_impl()
{
	CORBA::OctetSeq_var octet_key = new CORBA::OctetSeq();

	octet_key->length (8);

	for (unsigned int i = 0; i < 8; i++)
	{
		(*octet_key)[i] = ((char*)(&cookie_key_))[i];
	}

	cookieValue (octet_key.in());

    ++cookie_key_;
}


Cookie_impl::~Cookie_impl
()
{
}


CORBA::Boolean 
Cookie_impl::equal (Components::Cookie* cook)
{
	Cookie_impl* foreign_cook = dynamic_cast<Cookie_impl*>(cook);

	if (! foreign_cook)
		return false;

	CORBA::OctetSeq x = cookieValue();
	CORBA::OctetSeq y = foreign_cook->cookieValue();

	for (unsigned int i = 0; i < x.length(); i++)
	{
		if (x[i] != y[i])
			return false;
    }
    
	return true;
}


CORBA::ValueBase*
CookieFactory_impl::create_for_unmarshal()
{
	return new Cookie_impl();
}


PhilosopherState_impl::PhilosopherState_impl (dinner::PhilosopherStatus stat,
											  const char* name,
											  dinner::Philosopher_ptr phil) 
#ifndef VC6
: PhilosopherState (stat, name, phil)
#endif
{
#ifdef VC6
this->status(stat);
this->name(name);
this->ref(phil);
#endif
}


PhilosopherState_impl::PhilosopherState_impl()
{
}


PhilosopherState_impl::~PhilosopherState_impl()
{
}


CORBA::ValueBase* 
PhilosopherStateFactory_impl::create_for_unmarshal() 
{	
	return new PhilosopherState_impl ();
}


dinner::PhilosopherState* 
PhilosopherStateFactory_impl::create (dinner::PhilosopherStatus status,
									  const char* name,
									  dinner::Philosopher_ptr phil) 
{
	return new PhilosopherState_impl (status, name, phil);
}

} // namespace dinner