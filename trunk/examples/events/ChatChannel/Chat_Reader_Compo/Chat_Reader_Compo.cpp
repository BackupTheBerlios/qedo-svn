//
// generated by Qedo
//

#include "Chat_Reader_Compo.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace Chat {


// BEGIN USER INSERT SECTION ChatReaderSessionImpl
// END USER INSERT SECTION ChatReaderSessionImpl


ChatReaderSessionImpl::ChatReaderSessionImpl()
{
// BEGIN USER INSERT SECTION ChatReaderSessionImpl::ChatReaderSessionImpl
mess_count = 0;
// END USER INSERT SECTION ChatReaderSessionImpl::ChatReaderSessionImpl
}


ChatReaderSessionImpl::~ChatReaderSessionImpl()
{
// BEGIN USER INSERT SECTION ChatReaderSessionImpl::~ChatReaderSessionImpl
// END USER INSERT SECTION ChatReaderSessionImpl::~ChatReaderSessionImpl

}


void
ChatReaderSessionImpl::set_context(::Chat::CCM_ChatReader_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::Chat::CCM_ChatReader_ContextImpl::_duplicate(context);
}


void
ChatReaderSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION ChatReaderSessionImpl::configuration_complete
// END USER INSERT SECTION ChatReaderSessionImpl::configuration_complete
}


void
ChatReaderSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatReaderSessionImpl::remove
// END USER INSERT SECTION ChatReaderSessionImpl::remove
}


void
ChatReaderSessionImpl::push_event (Components::EventBase* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatReaderSessionImpl::push_event
// END USER INSERT SECTION ChatReaderSessionImpl::push_event
}


void
ChatReaderSessionImpl::push_ChatMessage(::Chat::ChatMessage* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatReaderSessionImpl::push_ChatMessage
	std::cout << "ChannelReader: got message.\n";
	std::cout << ev->message() << std::endl;
	std::cout << mess_count++ << std::endl;
// END USER INSERT SECTION ChatReaderSessionImpl::push_ChatMessage
}


// BEGIN USER INSERT SECTION Reader_Compo
// END USER INSERT SECTION Reader_Compo


Reader_Compo::Reader_Compo()
:component_(new ChatReaderSessionImpl())
{
// BEGIN USER INSERT SECTION Reader_Compo::Reader_Compo
// END USER INSERT SECTION Reader_Compo::Reader_Compo
}


Reader_Compo::~Reader_Compo()
{
// BEGIN USER INSERT SECTION Reader_Compo::~Reader_Compo
// END USER INSERT SECTION Reader_Compo::~Reader_Compo

    component_->_remove_ref();
}


::CORBA::Object*
Reader_Compo::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }

    return Components::EnterpriseComponent::_nil();
}


void
Reader_Compo::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
Reader_Compo::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION Reader_Compo::configuration_complete
// END USER INSERT SECTION Reader_Compo::configuration_complete
}


void
Reader_Compo::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::Chat::CCM_ChatReader_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::Chat::CCM_ChatReader_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::Chat::CCM_ChatReader_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::Chat::CCM_ChatReader_ContextImpl::_nil();
        
    #else
    context_ = ::Chat::CCM_ChatReader_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
Reader_Compo::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Reader_Compo::ccm_activate
// END USER INSERT SECTION Reader_Compo::ccm_activate
}


void
Reader_Compo::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Reader_Compo::ccm_passivate
// END USER INSERT SECTION Reader_Compo::ccm_passivate
}


void
Reader_Compo::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Reader_Compo::ccm_remove
// END USER INSERT SECTION Reader_Compo::ccm_remove
}


// BEGIN USER INSERT SECTION ChatReaderHomeSessionImpl
// END USER INSERT SECTION ChatReaderHomeSessionImpl


ChatReaderHomeSessionImpl::ChatReaderHomeSessionImpl()
{
// BEGIN USER INSERT SECTION ChatReaderHomeSessionImpl::ChatReaderHomeSessionImpl
// END USER INSERT SECTION ChatReaderHomeSessionImpl::ChatReaderHomeSessionImpl
}


ChatReaderHomeSessionImpl::~ChatReaderHomeSessionImpl()
{
// BEGIN USER INSERT SECTION ChatReaderHomeSessionImpl::~ChatReaderHomeSessionImpl
// END USER INSERT SECTION ChatReaderHomeSessionImpl::~ChatReaderHomeSessionImpl

}


void
ChatReaderHomeSessionImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
ChatReaderHomeSessionImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION ChatReaderHomeSessionImpl::create
// END USER INSERT SECTION ChatReaderHomeSessionImpl::create
    return new Reader_Compo();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ChatReaderHomeE(void)
{
// BEGIN USER INSERT SECTION create_ChatReaderHome
// END USER INSERT SECTION create_ChatReaderHome

    return new ::Chat::ChatReaderHomeSessionImpl();
}

