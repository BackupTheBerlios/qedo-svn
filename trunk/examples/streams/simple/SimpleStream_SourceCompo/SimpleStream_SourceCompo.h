//
// generated by Qedo
//

#ifndef _SimpleStream_SourceCompo_H_
#define _SimpleStream_SourceCompo_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "SimpleStream_SourceCompo_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
// END USER INSERT SECTION file_post


namespace SimpleStream
{
    
    //
    // executor
    //
    class SourceImpl
        : public virtual CORBA::LocalObject
        , public virtual ::SimpleStream::CCM_SourceImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SourceImpl
// END USER INSERT SECTION INHERITANCE_SourceImpl
    {
    
    private:
    
        ::SimpleStream::CCM_StreamSource_ContextImpl_var context_;
        
    public:
    
        SourceImpl();
        virtual ~SourceImpl();
        
        void set_context(::SimpleStream::CCM_StreamSource_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
    
// BEGIN USER INSERT SECTION SourceImpl
		bool						stopped_;
		Components::Thread_var		thread_;

		static void* sender_thread_initiator (void*);
		void sender_thread();

// END USER INSERT SECTION SourceImpl

    };
    
    
    //
    // executor locator
    //
    class SourceCompo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SourceCompo
// END USER INSERT SECTION INHERITANCE_SourceCompo
    {
    
    private:
    
        ::SimpleStream::CCM_StreamSource_ContextImpl_var context_;
        
        SourceImpl* component_;
        
    public:
    
        SourceCompo();
        virtual ~SourceCompo();
        
        
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
    
// BEGIN USER INSERT SECTION SourceCompo
// END USER INSERT SECTION SourceCompo

    };
    
    
    //
    // home executor
    //
    class SourceHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::SimpleStream::CCM_StreamSourceHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SourceHomeImpl
// END USER INSERT SECTION INHERITANCE_SourceHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        SourceHomeImpl();
        virtual ~SourceHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION SourceHomeImpl
// END USER INSERT SECTION SourceHomeImpl

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
::Components::HomeExecutorBase_ptr create_StreamSourceHomeE(void);
}

#endif
