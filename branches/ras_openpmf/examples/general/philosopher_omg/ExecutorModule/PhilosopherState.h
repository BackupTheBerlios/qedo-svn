//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: PhilosopherState.h,v 1.3 2003/01/10 13:23:28 neubauer Exp $
//

#ifndef __PHILOSOPHERSTATE_H__
#define __PHILOSOPHERSTATE_H__

#ifndef WIN32
#include "HU_Container.h"
#include CORBA_H
#include CORBA_STUB_HEADER(dinner_implied)
#else
#include <OB/CORBA.h>
#include "dinner_EQUIVALENT.h"
#endif


/*
class PhilosopherState_impl :
public virtual OBV_DiningPhilosophers::StatusInfo,
public virtual CORBA::DefaultValueRefCountBase {

	void operator=(const PhilosopherState_impl& val);

public:

	PhilosopherState_impl ();
	PhilosopherState_impl (DiningPhilosophers::StatusInfo stat,
						   const char* nam,
						   dinner::Philosopher_ptr re);

	virtual CORBA::ValueBase* _copy_value ();
};


class PhilosopherStateFactory_impl : 
public virtual dinner::PhilosopherState_init {
	
	virtual CORBA::ValueBase* create_for_unmarshal();

public:

	dinner::PhilosopherState* create (dinner::PhilosopherStatus status,
									  const char* name,
									  dinner::Philosopher_ptr ref);
};
*/



class PhilosopherState_impl :
public virtual OBV_DiningPhilosophers::StatusInfo,
public virtual CORBA::DefaultValueRefCountBase {

	void operator=(const PhilosopherState_impl& val);

public:

	PhilosopherState_impl ();
	PhilosopherState_impl (const char* p_name,
                           DiningPhilosophers::PhilosopherState p_stat,
                           CORBA::ULong p_ticks_since_last_meal,
                           CORBA::Boolean p_has_left_fork,
                           CORBA::Boolean p_has_right_fork);

	virtual CORBA::ValueBase* _copy_value ();
};


class PhilosopherStateFactory_impl : 
public virtual DiningPhilosophers::StatusInfo_init {
	
	virtual CORBA::ValueBase* create_for_unmarshal();

public:

	DiningPhilosophers::StatusInfo* create (const char* p_name,
                                      DiningPhilosophers::PhilosopherState p_stat,
                                      CORBA::ULong p_ticks_since_last_meal,
                                      CORBA::Boolean p_has_left_fork,
                                      CORBA::Boolean p_has_right_fork);
};


#endif

