//
// generated by Qedo
//

#ifndef _Computation_ClientCompo_H_
#define _Computation_ClientCompo_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "Computation_ClientCompo_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include <time.h>

// END USER INSERT SECTION file_post


namespace Computation
{
    
    //
    // executor
    //
    class ClientExec
        : public virtual CORBA::LocalObject
        , public virtual ::Computation::CCM_ClientExec
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ClientExec
// END USER INSERT SECTION INHERITANCE_ClientExec
    {
    
    private:
    
        ::Computation::CCM_Client_ContextImpl_var context_;
        
    public:
    
        ClientExec();
        virtual ~ClientExec();
        
        void set_context(::Computation::CCM_Client_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
    
// BEGIN USER INSERT SECTION ClientExec
		__time64_t ltime_start;
		__time64_t ltime_end;

		bool						stopped_;
		Components::Thread_var		thread_;

		static void* client_thread_initiator (void*);
		void client_thread();

// END USER INSERT SECTION ClientExec

    };
    
    
    //
    // executor locator
    //
    class ClientCompo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ClientCompo
// END USER INSERT SECTION INHERITANCE_ClientCompo
    {
    
    private:
    
        ::Computation::CCM_Client_ContextImpl_var context_;
        
        ClientExec* component_;
        
    public:
    
        ClientCompo();
        virtual ~ClientCompo();
        
        
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
    
// BEGIN USER INSERT SECTION ClientCompo
// END USER INSERT SECTION ClientCompo

    };
    
    
    //
    // home executor
    //
    class ClientHomeExec
        : public virtual CORBA::LocalObject
        , public virtual ::Computation::CCM_ClientHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ClientHomeExec
// END USER INSERT SECTION INHERITANCE_ClientHomeExec
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        ClientHomeExec();
        virtual ~ClientHomeExec();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::HomeContext_ptr ctx)
            throw (CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::EnterpriseComponent_ptr create()
            throw (CORBA::SystemException, Components::CreateFailure);
    
// BEGIN USER INSERT SECTION ClientHomeExec
// END USER INSERT SECTION ClientHomeExec

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
::Components::HomeExecutorBase_ptr create_ClientHomeE(void);
}

#endif
