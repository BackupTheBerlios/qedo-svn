//
// generated by Qedo
//

#include "HelloWorld_CalleeImpl.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace HelloWorld {


// BEGIN USER INSERT SECTION CalleeSessionImpl
// END USER INSERT SECTION CalleeSessionImpl


CalleeSessionImpl::CalleeSessionImpl()
{
// BEGIN USER INSERT SECTION CalleeSessionImpl::CalleeSessionImpl
// END USER INSERT SECTION CalleeSessionImpl::CalleeSessionImpl
}


CalleeSessionImpl::~CalleeSessionImpl()
{
// BEGIN USER INSERT SECTION CalleeSessionImpl::~CalleeSessionImpl
// END USER INSERT SECTION CalleeSessionImpl::~CalleeSessionImpl

}


void
CalleeSessionImpl::set_context(::HelloWorld::CCM_Callee_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::HelloWorld::CCM_Callee_ContextImpl::_duplicate(context);
}


void
CalleeSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION CalleeSessionImpl::configuration_complete
// END USER INSERT SECTION CalleeSessionImpl::configuration_complete
}


void
CalleeSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CalleeSessionImpl::remove
// END USER INSERT SECTION CalleeSessionImpl::remove
}


void
CalleeSessionImpl::say()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CalleeSessionImpl::say
	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	std::cout << "!!! Hello World !!!!!!!!!!!!!!!!!!!\n";
	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
// END USER INSERT SECTION CalleeSessionImpl::say
}


// BEGIN USER INSERT SECTION CalleeImpl
// END USER INSERT SECTION CalleeImpl


CalleeImpl::CalleeImpl()
:component_(new CalleeSessionImpl())
{
// BEGIN USER INSERT SECTION CalleeImpl::CalleeImpl
// END USER INSERT SECTION CalleeImpl::CalleeImpl
}


CalleeImpl::~CalleeImpl()
{
// BEGIN USER INSERT SECTION CalleeImpl::~CalleeImpl
// END USER INSERT SECTION CalleeImpl::~CalleeImpl

    component_->_remove_ref();
}


::CORBA::Object*
CalleeImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "the_hello")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
CalleeImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
CalleeImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION CalleeImpl::configuration_complete
// END USER INSERT SECTION CalleeImpl::configuration_complete
}


void
CalleeImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::HelloWorld::CCM_Callee_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::HelloWorld::CCM_Callee_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::HelloWorld::CCM_Callee_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::HelloWorld::CCM_Callee_ContextImpl::_nil();
        
    #else
    context_ = ::HelloWorld::CCM_Callee_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
CalleeImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CalleeImpl::ccm_activate
// END USER INSERT SECTION CalleeImpl::ccm_activate
}


void
CalleeImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CalleeImpl::ccm_passivate
// END USER INSERT SECTION CalleeImpl::ccm_passivate
}


void
CalleeImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CalleeImpl::ccm_remove
// END USER INSERT SECTION CalleeImpl::ccm_remove
}


// BEGIN USER INSERT SECTION CalleeHomeImpl
// END USER INSERT SECTION CalleeHomeImpl


CalleeHomeImpl::CalleeHomeImpl()
{
// BEGIN USER INSERT SECTION CalleeHomeImpl::CalleeHomeImpl
// END USER INSERT SECTION CalleeHomeImpl::CalleeHomeImpl
}


CalleeHomeImpl::~CalleeHomeImpl()
{
// BEGIN USER INSERT SECTION CalleeHomeImpl::~CalleeHomeImpl
// END USER INSERT SECTION CalleeHomeImpl::~CalleeHomeImpl

}


void
CalleeHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
CalleeHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION CalleeHomeImpl::create
// END USER INSERT SECTION CalleeHomeImpl::create
    return new CalleeImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_CalleeHomeE(void)
{
// BEGIN USER INSERT SECTION create_CalleeHome
// END USER INSERT SECTION create_CalleeHome

    return new ::HelloWorld::CalleeHomeImpl();
}

