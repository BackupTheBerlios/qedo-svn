//
// generated by Qedo
//

#include "Chat_Writer_Compo.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace Chat {


// BEGIN USER INSERT SECTION ChatWriterSessionImpl
// END USER INSERT SECTION ChatWriterSessionImpl


ChatWriterSessionImpl::ChatWriterSessionImpl()
{
// BEGIN USER INSERT SECTION ChatWriterSessionImpl::ChatWriterSessionImpl
// END USER INSERT SECTION ChatWriterSessionImpl::ChatWriterSessionImpl
}


ChatWriterSessionImpl::~ChatWriterSessionImpl()
{
// BEGIN USER INSERT SECTION ChatWriterSessionImpl::~ChatWriterSessionImpl
// END USER INSERT SECTION ChatWriterSessionImpl::~ChatWriterSessionImpl

}


void
ChatWriterSessionImpl::set_context(::Chat::CCM_ChatWriter_Context_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::Chat::CCM_ChatWriter_Context::_duplicate(context);
}


void
ChatWriterSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION ChatWriterSessionImpl::configuration_complete
// END USER INSERT SECTION ChatWriterSessionImpl::configuration_complete
}


void
ChatWriterSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatWriterSessionImpl::remove
// END USER INSERT SECTION ChatWriterSessionImpl::remove
}


void
ChatWriterSessionImpl::request_and_push_message()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatWriterSessionImpl::request_and_push_message
	Chat::ChatMessageImpl* message = new Chat::ChatMessageImpl();
	message->message(CORBA::string_dup("test"));
	context_->push_to_channel(message);
// END USER INSERT SECTION ChatWriterSessionImpl::request_and_push_message
}


// BEGIN USER INSERT SECTION Writer_Compo
// END USER INSERT SECTION Writer_Compo


Writer_Compo::Writer_Compo()
:component_(new ChatWriterSessionImpl())
{
// BEGIN USER INSERT SECTION Writer_Compo::Writer_Compo
// END USER INSERT SECTION Writer_Compo::Writer_Compo
}


Writer_Compo::~Writer_Compo()
{
// BEGIN USER INSERT SECTION Writer_Compo::~Writer_Compo
// END USER INSERT SECTION Writer_Compo::~Writer_Compo

    component_->_remove_ref();
}


::CORBA::Object*
Writer_Compo::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "control")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
Writer_Compo::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
Writer_Compo::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION Writer_Compo::configuration_complete
// END USER INSERT SECTION Writer_Compo::configuration_complete
}


void
Writer_Compo::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::Chat::CCM_ChatWriter_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::Chat::CCM_ChatWriter_Context*>(context);
    
    if (tmp_context)
        context_ = ::Chat::CCM_ChatWriter_Context::_duplicate(tmp_context);
    else
        context_ = ::Chat::CCM_ChatWriter_Context::_nil();
        
    #else
    context_ = ::Chat::CCM_ChatWriter_Context::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
Writer_Compo::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Writer_Compo::ccm_activate
// END USER INSERT SECTION Writer_Compo::ccm_activate
}


void
Writer_Compo::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Writer_Compo::ccm_passivate
// END USER INSERT SECTION Writer_Compo::ccm_passivate
}


void
Writer_Compo::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Writer_Compo::ccm_remove
// END USER INSERT SECTION Writer_Compo::ccm_remove
}


// BEGIN USER INSERT SECTION WriterHomeSessionImpl
// END USER INSERT SECTION WriterHomeSessionImpl


WriterHomeSessionImpl::WriterHomeSessionImpl()
{
// BEGIN USER INSERT SECTION WriterHomeSessionImpl::WriterHomeSessionImpl
// END USER INSERT SECTION WriterHomeSessionImpl::WriterHomeSessionImpl
}


WriterHomeSessionImpl::~WriterHomeSessionImpl()
{
// BEGIN USER INSERT SECTION WriterHomeSessionImpl::~WriterHomeSessionImpl
// END USER INSERT SECTION WriterHomeSessionImpl::~WriterHomeSessionImpl

}


void
WriterHomeSessionImpl::set_context(Components::CCMContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::CCMContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
WriterHomeSessionImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION WriterHomeSessionImpl::create
// END USER INSERT SECTION WriterHomeSessionImpl::create
    return new Writer_Compo();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ChatWriterHomeE(void)
{
// BEGIN USER INSERT SECTION create_ChatWriterHome
// END USER INSERT SECTION create_ChatWriterHome

    return new ::Chat::WriterHomeSessionImpl();
}
