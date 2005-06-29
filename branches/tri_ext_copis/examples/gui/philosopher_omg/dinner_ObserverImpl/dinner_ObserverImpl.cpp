//
// generated by Qedo
//

#include "dinner_ObserverImpl.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace dinner {


// BEGIN USER INSERT SECTION ObserverSessionImpl
// END USER INSERT SECTION ObserverSessionImpl


ObserverSessionImpl::ObserverSessionImpl()
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::ObserverSessionImpl
// END USER INSERT SECTION ObserverSessionImpl::ObserverSessionImpl
}


ObserverSessionImpl::~ObserverSessionImpl()
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::~ObserverSessionImpl
// END USER INSERT SECTION ObserverSessionImpl::~ObserverSessionImpl

}


void
ObserverSessionImpl::set_context(::DiningPhilosophers::CCM_Observer_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::DiningPhilosophers::CCM_Observer_ContextImpl::_duplicate(context);
}


void
ObserverSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::configuration_complete
// END USER INSERT SECTION ObserverSessionImpl::configuration_complete
}


void
ObserverSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::remove
// END USER INSERT SECTION ObserverSessionImpl::remove
}


void
ObserverSessionImpl::push_event (Components::EventBase* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::push_event
// END USER INSERT SECTION ObserverSessionImpl::push_event
}


void
ObserverSessionImpl::push_StatusInfo(::DiningPhilosophers::StatusInfo* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::push_StatusInfo
	std::cout << "got event" << std::endl;

// END USER INSERT SECTION ObserverSessionImpl::push_StatusInfo
}


// BEGIN USER INSERT SECTION ObserverImpl
// END USER INSERT SECTION ObserverImpl


ObserverImpl::ObserverImpl()
:component_(new ObserverSessionImpl())
{
// BEGIN USER INSERT SECTION ObserverImpl::ObserverImpl
// END USER INSERT SECTION ObserverImpl::ObserverImpl
}


ObserverImpl::~ObserverImpl()
{
// BEGIN USER INSERT SECTION ObserverImpl::~ObserverImpl
// END USER INSERT SECTION ObserverImpl::~ObserverImpl

    component_->_remove_ref();
}


::CORBA::Object*
ObserverImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
ObserverImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
ObserverImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION ObserverImpl::configuration_complete
// END USER INSERT SECTION ObserverImpl::configuration_complete
}


void
ObserverImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::DiningPhilosophers::CCM_Observer_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::DiningPhilosophers::CCM_Observer_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::DiningPhilosophers::CCM_Observer_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::DiningPhilosophers::CCM_Observer_ContextImpl::_nil();
        
    #else
    context_ = ::DiningPhilosophers::CCM_Observer_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
ObserverImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ObserverImpl::ccm_activate
// END USER INSERT SECTION ObserverImpl::ccm_activate
}


void
ObserverImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ObserverImpl::ccm_passivate
// END USER INSERT SECTION ObserverImpl::ccm_passivate
}


void
ObserverImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ObserverImpl::ccm_remove
// END USER INSERT SECTION ObserverImpl::ccm_remove
}


// BEGIN USER INSERT SECTION ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl


ObserverHomeImpl::ObserverHomeImpl()
{
// BEGIN USER INSERT SECTION ObserverHomeImpl::ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl::ObserverHomeImpl
}


ObserverHomeImpl::~ObserverHomeImpl()
{
// BEGIN USER INSERT SECTION ObserverHomeImpl::~ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl::~ObserverHomeImpl

}


void
ObserverHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
ObserverHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION ObserverHomeImpl::create
// END USER INSERT SECTION ObserverHomeImpl::create
    return new ObserverImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ObserverHomeE(void)
{
// BEGIN USER INSERT SECTION create_ObserverHome
// END USER INSERT SECTION create_ObserverHome

    return new ::dinner::ObserverHomeImpl();
}

