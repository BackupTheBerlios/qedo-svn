//
// generated by Qedo
//

#include "component_valuetypes.h"
#include "Output.h"
#include "RefCountBase.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace dinner {
    void
    PhilosopherStateImpl::operator= (const PhilosopherStateImpl& v)
    {
        status( v.status() );
        name( v.name() );
        phil_ref( v.phil_ref() );
// BEGIN USER INSERT SECTION PhilosopherStateImpl::operator=
// END USER INSERT SECTION PhilosopherStateImpl::operator=
    }
    
    
    PhilosopherStateImpl::PhilosopherStateImpl(const PhilosopherStateImpl& v)
    {
        status( v.status() );
        name( v.name() );
        phil_ref( v.phil_ref() );
// BEGIN USER INSERT SECTION PhilosopherStateImpl::PhilosopherStateImpl1
// END USER INSERT SECTION PhilosopherStateImpl::PhilosopherStateImpl1
    }
    
    
    PhilosopherStateImpl::PhilosopherStateImpl(dinner::PhilosopherStatus status, const char* name, dinner::Philosopher_ptr phil_ref)
    : ::OBV_dinner::PhilosopherState(status, name, phil_ref)
    {
// BEGIN USER INSERT SECTION PhilosopherStateImpl::PhilosopherStateImpl2
// END USER INSERT SECTION PhilosopherStateImpl::PhilosopherStateImpl2
    }
    
    
    PhilosopherStateImpl::PhilosopherStateImpl()
    {
// BEGIN USER INSERT SECTION PhilosopherStateImpl::PhilosopherStateImpl3
// END USER INSERT SECTION PhilosopherStateImpl::PhilosopherStateImpl3
    }
    
    
    PhilosopherStateImpl::~PhilosopherStateImpl()
    {
// BEGIN USER INSERT SECTION PhilosopherStateImpl::~PhilosopherStateImpl
// END USER INSERT SECTION PhilosopherStateImpl::~PhilosopherStateImpl
    }
    
    
    CORBA::ValueBase*
    PhilosopherStateImpl::_copy_value()
    {
        PhilosopherStateImpl *val = new PhilosopherStateImpl(* this);
// BEGIN USER INSERT SECTION PhilosopherStateImpl::_copy_value
// END USER INSERT SECTION PhilosopherStateImpl::_copy_value
        return val;
    }
    
    
    CORBA::ValueBase *
    PhilosopherStateFactoryImpl::create_for_unmarshal ()
    {
        return new ::dinner::PhilosopherStateImpl();
    }
    
    
    static Qedo::ValueFactoryCleaner PhilosopherStateFactory_cleaner( new PhilosopherStateFactoryImpl(), "IDL:dinner/PhilosopherState:1.0" );
};
