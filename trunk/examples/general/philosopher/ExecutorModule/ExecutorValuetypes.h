//
// TETRA
// Example 1 for Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: ExecutorValuetypes.h,v 1.1 2002/10/13 12:08:44 tom Exp $
//

#ifndef __EXECUTOR_VALUETYPES_H__
#define __EXECUTOR_VALUETYPES_H__

#include <OB/CORBA.h>
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