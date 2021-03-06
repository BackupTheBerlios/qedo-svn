//
// generated by Qedo
//

#ifndef _Computation_ServerCompo_H_
#define _Computation_ServerCompo_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "Computation_ServerCompo_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
// END USER INSERT SECTION file_post


namespace Computation
{
    
    //
    // executor
    //
    class ServerExec
        : public virtual CORBA::LocalObject
        , public virtual ::Computation::CCM_ServerExec
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ServerExec
// END USER INSERT SECTION INHERITANCE_ServerExec
    {
    
    private:
    
        ::Computation::CCM_Server_ContextImpl_var context_;
        
    public:
    
        ServerExec();
        virtual ~ServerExec();
        
        void set_context(::Computation::CCM_Server_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:Computation/Computing_Service/compute:1.0
        //
        virtual CORBA::Long compute(CORBA::Long argument_of_function)
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION ServerExec
// END USER INSERT SECTION ServerExec

    };
    
    
    //
    // executor locator
    //
    class ServerCompo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ServerCompo
// END USER INSERT SECTION INHERITANCE_ServerCompo
    {
    
    private:
    
        ::Computation::CCM_Server_ContextImpl_var context_;
        
        ServerExec* component_;
        
    public:
    
        ServerCompo();
        virtual ~ServerCompo();
        
        
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
    
// BEGIN USER INSERT SECTION ServerCompo
// END USER INSERT SECTION ServerCompo

    };
    
    
    //
    // home executor
    //
    class ServerHomeExec
        : public virtual CORBA::LocalObject
        , public virtual ::Computation::CCM_ServerHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ServerHomeExec
// END USER INSERT SECTION INHERITANCE_ServerHomeExec
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        ServerHomeExec();
        virtual ~ServerHomeExec();
        
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
    
// BEGIN USER INSERT SECTION ServerHomeExec
// END USER INSERT SECTION ServerHomeExec

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
::Components::HomeExecutorBase_ptr create_ServerHomeE(void);
}

#endif
