//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: PhilosopherState.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $
//

static char rcsid[] = "$Id: PhilosopherState.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $";


#include "PhilosopherState.h"


PhilosopherState_impl::PhilosopherState_impl () {
}


PhilosopherState_impl::PhilosopherState_impl (const char* p_name,
                                              DiningPhilosophers::PhilosopherState p_stat,
                                              CORBA::ULong p_ticks_since_last_meal,
                                              CORBA::Boolean p_has_left_fork,
                                              CORBA::Boolean p_has_right_fork)
{
	name (CORBA::string_dup (p_name));
	state (p_stat);
	ticks_since_last_meal (p_ticks_since_last_meal);
    has_left_fork (p_has_left_fork);
    has_right_fork (p_has_right_fork);
}


void 
PhilosopherState_impl::operator=(const PhilosopherState_impl& val)
{
	name (val.name ());
	state (val.state ());
    ticks_since_last_meal(val.ticks_since_last_meal());
	has_left_fork (val.has_left_fork());
    has_right_fork (val.has_right_fork());
}


CORBA::ValueBase* 
PhilosopherState_impl::_copy_value () {

	PhilosopherState_impl* val = new PhilosopherState_impl ();
	val->name (name ());
	val->state (state ());
	val->ticks_since_last_meal (ticks_since_last_meal ());
    val->has_left_fork (has_left_fork());
    val->has_right_fork (has_right_fork());
	return val;
}


CORBA::ValueBase* 
PhilosopherStateFactory_impl::create_for_unmarshal() {
	
	return new PhilosopherState_impl ();
}


DiningPhilosophers::StatusInfo* 
PhilosopherStateFactory_impl::create (const char* p_name,
                                      DiningPhilosophers::PhilosopherState p_stat,
                                      CORBA::ULong p_ticks_since_last_meal,
                                      CORBA::Boolean p_has_left_fork,
                                      CORBA::Boolean p_has_right_fork)
{
	return new PhilosopherState_impl (p_name, p_stat, p_ticks_since_last_meal, p_has_left_fork, p_has_right_fork);
}