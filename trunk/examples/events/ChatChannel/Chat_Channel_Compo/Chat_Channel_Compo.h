//
// generated by Qedo
//

#ifndef _Chat_Channel_Compo_H_
#define _Chat_Channel_Compo_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "Chat_Channel_Compo_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
// END USER INSERT SECTION file_post


namespace Chat
{
    
    //
    // executor
    //
    class ChatChannelSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::Chat::CCM_ChatChannelSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ChatChannelSessionImpl
// END USER INSERT SECTION INHERITANCE_ChatChannelSessionImpl
    {
    
    private:
    
        ::Chat::CCM_ChatChannel_Context_var context_;
        
    public:
    
        ChatChannelSessionImpl();
        virtual ~ChatChannelSessionImpl();
        
        void set_context(::Chat::CCM_ChatChannel_Context_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:Components/EventConsumerBase/push_event:1.0
        //
        virtual void push_event (Components::EventBase* ev)
            throw (CORBA::SystemException);
        
        
        //
        // IDL:Chat/ChatChannel/from_writer:1.0
        //
        void push_ChatMessage(::Chat::ChatMessage* ev)
            throw (CORBA::SystemException);
        
    
// BEGIN USER INSERT SECTION ChatChannelSessionImpl
// END USER INSERT SECTION ChatChannelSessionImpl

    };
    
    
    //
    // executor locator
    //
    class Channel_Compo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_Channel_Compo
// END USER INSERT SECTION INHERITANCE_Channel_Compo
    {
    
    private:
    
        ::Chat::CCM_ChatChannel_Context_var context_;
        
        ChatChannelSessionImpl* component_;
        
    public:
    
        Channel_Compo();
        virtual ~Channel_Compo();
        
        
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
    
// BEGIN USER INSERT SECTION Channel_Compo
// END USER INSERT SECTION Channel_Compo

    };
    
    
    //
    // home executor
    //
    class ChatChannelHomeSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::Chat::CCM_ChatChannelHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ChatChannelHomeSessionImpl
// END USER INSERT SECTION INHERITANCE_ChatChannelHomeSessionImpl
    {
    
    private:
    
        Components::CCMContext_var context_;
        
    public:
        ChatChannelHomeSessionImpl();
        virtual ~ChatChannelHomeSessionImpl();
        
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
    
// BEGIN USER INSERT SECTION ChatChannelHomeSessionImpl
// END USER INSERT SECTION ChatChannelHomeSessionImpl

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
::Components::HomeExecutorBase_ptr create_ChatChannelHomeE(void);
}

#endif
