//
// generated by Qedo
//

#ifndef _HelloWorld_CalleeImpl_H_
#define _HelloWorld_CalleeImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "HelloWorld_CalleeImpl_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
// END USER INSERT SECTION file_post


namespace HelloWorld
{
    
    //
    // executor
    //
    class CalleeSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::HelloWorld::CCM_CalleeSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CalleeSessionImpl
// END USER INSERT SECTION INHERITANCE_CalleeSessionImpl
    {
    
    private:
    
        ::HelloWorld::CCM_Callee_Context_var context_;
        
    public:
    
        CalleeSessionImpl();
        virtual ~CalleeSessionImpl();
        
        void set_context(::HelloWorld::CCM_Callee_Context_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:HelloWorld/Hello/say:1.0
        //
        virtual void say()
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION CalleeSessionImpl
// END USER INSERT SECTION CalleeSessionImpl

    };
    
    
    //
    // executor locator
    //
    class CalleeImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CalleeImpl
// END USER INSERT SECTION INHERITANCE_CalleeImpl
    {
    
    private:
    
        ::HelloWorld::CCM_Callee_Context_var context_;
        
        CalleeSessionImpl* component_;
        
    public:
    
        CalleeImpl();
        virtual ~CalleeImpl();
        
        
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
        	throw(CORBA::SystemException, ::Components::InvalidConfiguration);
        
        //
        // IDL:Components/SessionComponent/set_session_context:1.0
        //
        virtual void set_session_context(Components::SessionContext_ptr ctx)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, ::Components::CCMException);
    
// BEGIN USER INSERT SECTION CalleeImpl
// END USER INSERT SECTION CalleeImpl

    };
    
    
    //
    // home executor
    //
    class CalleeHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::HelloWorld::CCM_CalleeHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CalleeHomeImpl
// END USER INSERT SECTION INHERITANCE_CalleeHomeImpl
    {
    
    private:
    
        Components::CCMContext_var context_;
        
    public:
        CalleeHomeImpl();
        virtual ~CalleeHomeImpl();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::CCMContext_ptr ctx)
            throw (CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::EnterpriseComponent_ptr create()
            throw (CORBA::SystemException, Components::CreateFailure);
    
// BEGIN USER INSERT SECTION CalleeHomeImpl
// END USER INSERT SECTION CalleeHomeImpl

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
::Components::HomeExecutorBase_ptr create_CalleeHomeE(void);
}

#endif
