//
// generated by Qedo
//

#ifndef _VALUETYPES_H_
#define _VALUETYPES_H_


#include <CORBA.h>
#include "dinner_EQUIVALENT.h"


// BEGIN USER INSERT SECTION file
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

};
// END USER INSERT SECTION file


namespace dinner {
    
    
    //
    // IDL:dinner/PhilosopherState:1.0
    //
    class PhilosopherStateImpl
    : virtual public ::OBV_dinner::PhilosopherState
    , virtual public CORBA::DefaultValueRefCountBase
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherState
// END USER INSERT SECTION INHERITANCE_PhilosopherState
    {
    private:
    
        void operator= (const PhilosopherStateImpl& v);
        PhilosopherStateImpl (const PhilosopherStateImpl& v);
        
    public:
    
        PhilosopherStateImpl(dinner::PhilosopherStatus status, const char* name, dinner::Philosopher_ptr ref);
        PhilosopherStateImpl();
        ~PhilosopherStateImpl();
        
        CORBA::ValueBase* _copy_value();
        
// BEGIN USER INSERT SECTION PhilosopherState
// END USER INSERT SECTION PhilosopherState
    };
    
    
    class PhilosopherStateFactoryImpl
    : virtual public CORBA::ValueFactoryBase
    {
    private:
    
        virtual CORBA::ValueBase * create_for_unmarshal();
        
    public:
    
        PhilosopherStateFactoryImpl();
        
// BEGIN USER INSERT SECTION PhilosopherState_factory
// END USER INSERT SECTION PhilosopherState_factory
    };
    
    
};
#endif
