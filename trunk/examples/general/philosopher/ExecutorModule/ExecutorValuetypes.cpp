//
// TETRA
// Example 1 for Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: ExecutorValuetypes.cpp,v 1.1 2002/10/13 12:08:44 tom Exp $
//

static char rcsid[] = "$Id: ExecutorValuetypes.cpp,v 1.1 2002/10/13 12:08:44 tom Exp $";

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
: PhilosopherState (stat, name, phil)
{
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