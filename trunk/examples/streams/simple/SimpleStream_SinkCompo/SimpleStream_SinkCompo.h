//
// generated by Qedo
//

#ifndef _SimpleStream_SinkCompo_H_
#define _SimpleStream_SinkCompo_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "SimpleStream_SinkCompo_BUSINESS.h"
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
    class SinkImpl
        : public virtual CORBA::LocalObject
        , public virtual ::SimpleStream::CCM_SinkImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SinkImpl
// END USER INSERT SECTION INHERITANCE_SinkImpl
    {
    
    private:
    
        ::SimpleStream::CCM_StreamSink_ContextImpl_var context_;
        
    public:
    
        SinkImpl();
        virtual ~SinkImpl();
        
        void set_context(::SimpleStream::CCM_StreamSink_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        //
        // IDL:SimpleStream/StreamSink/input:1.0
        //
        void begin_stream_input (const char*, const ::Components::ConfigValues&);
        void end_stream_input();
        void failed_stream_input();
        void receive_stream_input (StreamComponents::StreamingBuffer_ptr);
        
    
// BEGIN USER INSERT SECTION SinkImpl

// END USER INSERT SECTION SinkImpl

    };
    
    
    //
    // executor locator
    //
    class SinkCompo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SinkCompo
// END USER INSERT SECTION INHERITANCE_SinkCompo
    {
    
    private:
    
        ::SimpleStream::CCM_StreamSink_ContextImpl_var context_;
        
        SinkImpl* component_;
        
    public:
    
        SinkCompo();
        virtual ~SinkCompo();
        
        
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
    
// BEGIN USER INSERT SECTION SinkCompo
// END USER INSERT SECTION SinkCompo

    };
    
    
    //
    // home executor
    //
    class SinkHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::SimpleStream::CCM_StreamSinkHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SinkHomeImpl
// END USER INSERT SECTION INHERITANCE_SinkHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        SinkHomeImpl();
        virtual ~SinkHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION SinkHomeImpl
// END USER INSERT SECTION SinkHomeImpl

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
::Components::HomeExecutorBase_ptr create_StreamSinkHomeE(void);
}

#endif
