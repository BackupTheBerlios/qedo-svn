//
// generated by Qedo
//

#ifndef _dinner_ObserverImpl_H_
#define _dinner_ObserverImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <OB/CORBA.h>
#include "dinner_BUSINESS.h"
#include "RefCountLocalObject.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
// END USER INSERT SECTION file_post


namespace dinner
{
    
    //
    // executor
    //
    class ObserverSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual dinner::CCM_ObserverSessionImpl
// BEGIN USER INSERT SECTION INHERITANCE_ObserverSessionImpl
		, public RefCountLocalObject
// END USER INSERT SECTION INHERITANCE_ObserverSessionImpl
    {
    
    private:
    
        ::dinner::CCM_Observer_Context_var context_;
        
    public:
    
        ObserverSessionImpl();
        ~ObserverSessionImpl();
        
        void set_context(::dinner::CCM_Observer_Context_ptr context);
        void configuration_complete();
        void stop();
        void remove();
        
        //
        // IDL:Components/EventConsumerBase/push_event:1.0
        //
        virtual void push_event (Components::EventBase* ev);
        
        //
        // IDL:dinner/Observer/philosopher_state:1.0
        //
        void push_PhilosopherState(dinner::PhilosopherState* ev);
    
// BEGIN USER INSERT SECTION ObserverSessionImpl
// END USER INSERT SECTION ObserverSessionImpl

    };
    
    
    //
    // executor locator
    //
    class ObserverImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
// BEGIN USER INSERT SECTION INHERITANCE_ObserverImpl
		, public RefCountLocalObject
// END USER INSERT SECTION INHERITANCE_ObserverImpl
    {
    
    private:
    
        ::dinner::CCM_Observer_Context_var context_;
        
        ObserverSessionImpl* component_;
        
    public:
    
        ObserverImpl();
        ~ObserverImpl();
        
        //
        // IDL:Components/ExecutorLocator/obtain_executor:1.0
        //
        virtual CORBA::Object_ptr obtain_executor(const char* name)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/ExecutorLocator/release_executor:1.0
        //
        virtual void release_executor(CORBA::Object_ptr exc)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/ExecutorLocator/configuration_complete:1.0
        //
        virtual void configuration_complete()
        	throw(CORBA::SystemException, Components::InvalidConfiguration);
        
        //
        // IDL:Components/SessionComponent/set_session_context:1.0
        //
        virtual void set_session_context(Components::SessionContext_ptr ctx)
        	throw(CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, Components::CCMException);
    
// BEGIN USER INSERT SECTION ObserverImpl
// END USER INSERT SECTION ObserverImpl

    };
    
    
    //
    // home executor
    //
    class ObserverHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::dinner::CCM_ObserverHome
// BEGIN USER INSERT SECTION INHERITANCE_ObserverHomeImpl
		, public RefCountLocalObject
// END USER INSERT SECTION INHERITANCE_ObserverHomeImpl
    {
    
    private:
    
        Components::CCMContext_ptr context_;
        
    public:
        ObserverHomeImpl();
        ~ObserverHomeImpl();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::CCMContext_ptr ctx);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::ExecutorLocator_ptr create();
        
        //
        // IDL:dinner/ObserverHome/my_name:1.0
        //
        dinner::PhilosopherState* my_name()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/ObserverHome/muell:1.0
        //
        virtual void muell(CORBA::Long l)
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/ObserverHome/do_it:1.0
        //
        virtual dinner::Observer_ptr do_it(const char* name, dinner::PhilosopherState* state)
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/ObserverHome/find_it:1.0
        //
        virtual dinner::Observer_ptr find_it(const char* name)
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl

    };
    
};

//
// entry point
//
extern "C" {
#ifdef _WIN32
__declspec(dllexport)
#else
#endif
::Components::HomeExecutorBase_ptr create_ObserverHomeE(void);
}

#endif