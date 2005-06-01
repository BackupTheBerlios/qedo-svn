//
// generated by Qedo
//

#ifndef _EventFrequency_EFQoSProviderComposition_H_
#define _EventFrequency_EFQoSProviderComposition_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "EventFrequency_EFQoSProviderComposition_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include "ServerContainerInterceptor.h"
// END USER INSERT SECTION file_post


namespace EventFrequency
{
    
    //
    // executor
    //
    class EFQoSProviderExec
        : public virtual CORBA::LocalObject
        , public virtual ::EventFrequency::CCM_EFQoSProviderExec
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_EFQoSProviderExec
// END USER INSERT SECTION INHERITANCE_EFQoSProviderExec
    {
    
    private:
    
        ::EventFrequency::CCM_EFQoSProvider_ContextImpl_var context_;
        
    public:
    
        EFQoSProviderExec();
        virtual ~EFQoSProviderExec();
        
        void set_context(::EventFrequency::CCM_EFQoSProvider_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:EventFrequency/FreqUsage/set_frequency:1.0
        //
        virtual void set_frequency(CORBA::Long freq)
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION EFQoSProviderExec
public:
	Qedo::EFServerContainerInterceptor* server_interceptor_;
// END USER INSERT SECTION EFQoSProviderExec

    };
    
    
    //
    // executor locator
    //
    class EFQoSProviderComposition
        : public virtual CORBA::LocalObject
        , public virtual Components::ExtensionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_EFQoSProviderComposition
// END USER INSERT SECTION INHERITANCE_EFQoSProviderComposition
    {
    
    private:
    
        ::EventFrequency::CCM_EFQoSProvider_ContextImpl_var context_;
        
        EFQoSProviderExec* component_;
        
    public:
    
        EFQoSProviderComposition();
        virtual ~EFQoSProviderComposition();
        
        
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
        // IDL:Components/ExtensionComponent/set_extension_context:1.0
        //
        virtual void set_extension_context(Components::ExtensionContext_ptr ctx)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, ::Components::CCMException);
    
// BEGIN USER INSERT SECTION EFQoSProviderComposition
// END USER INSERT SECTION EFQoSProviderComposition

    };
    
    
    //
    // home executor
    //
    class EFQoSProviderHomeExec
        : public virtual CORBA::LocalObject
        , public virtual ::EventFrequency::CCM_EFQoSProviderHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_EFQoSProviderHomeExec
// END USER INSERT SECTION INHERITANCE_EFQoSProviderHomeExec
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        EFQoSProviderHomeExec();
        virtual ~EFQoSProviderHomeExec();
        
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
    
// BEGIN USER INSERT SECTION EFQoSProviderHomeExec
// END USER INSERT SECTION EFQoSProviderHomeExec

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
::Components::HomeExecutorBase_ptr create_EFQoSProviderHomeE(void);
}

#endif
