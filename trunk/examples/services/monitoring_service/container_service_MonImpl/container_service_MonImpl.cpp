//
// generated by Qedo
//

#include "container_service_MonImpl.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace container_service {


// BEGIN USER INSERT SECTION MonExec
// END USER INSERT SECTION MonExec


MonExec::MonExec()
{
// BEGIN USER INSERT SECTION MonExec::MonExec
// END USER INSERT SECTION MonExec::MonExec
}


MonExec::~MonExec()
{
// BEGIN USER INSERT SECTION MonExec::~MonExec
		server_interceptor_ ->_remove_ref();
// END USER INSERT SECTION MonExec::~MonExec

}


void
MonExec::set_context(::container_service::CCM_monitor_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::container_service::CCM_monitor_ContextImpl::_duplicate(context);
}


void
MonExec::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION MonExec::configuration_complete
	Components::Extension::ServerInterceptorRegistration_ptr server_reg =
		context_->get_server_interceptor_dispatcher_registration();

	server_interceptor_ = new Qedo::ServerContainerInterceptor();

	server_reg->register_server_interceptor(server_interceptor_);


// END USER INSERT SECTION MonExec::configuration_complete
}


void
MonExec::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION MonExec::remove
// END USER INSERT SECTION MonExec::remove
}


// BEGIN USER INSERT SECTION MonImpl
// END USER INSERT SECTION MonImpl


MonImpl::MonImpl()
:component_(new MonExec())
{
// BEGIN USER INSERT SECTION MonImpl::MonImpl
// END USER INSERT SECTION MonImpl::MonImpl
}


MonImpl::~MonImpl()
{
// BEGIN USER INSERT SECTION MonImpl::~MonImpl
// END USER INSERT SECTION MonImpl::~MonImpl

    component_->_remove_ref();
}


::CORBA::Object*
MonImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }

    return Components::EnterpriseComponent::_nil();
}


void
MonImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
MonImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION MonImpl::configuration_complete
//	register_container_interceptors(context_);
// END USER INSERT SECTION MonImpl::configuration_complete
}


void
MonImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::container_service::CCM_monitor_Context_ptr tmp_context;

    tmp_context = dynamic_cast<::container_service::CCM_monitor_ContextImpl*>(context);

    if (tmp_context)
        context_ = ::container_service::CCM_monitor_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::container_service::CCM_monitor_ContextImpl::_nil();

    #else
    context_ = ::container_service::CCM_monitor_ContextImpl::_narrow(context);

    #endif
    component_->set_context(context_);
}


void
MonImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION MonImpl::ccm_activate
// END USER INSERT SECTION MonImpl::ccm_activate
}


void
MonImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION MonImpl::ccm_passivate
// END USER INSERT SECTION MonImpl::ccm_passivate
}


void
MonImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION MonImpl::ccm_remove
// END USER INSERT SECTION MonImpl::ccm_remove
}


// BEGIN USER INSERT SECTION HomeMonExec
// END USER INSERT SECTION HomeMonExec


HomeMonExec::HomeMonExec()
{
// BEGIN USER INSERT SECTION HomeMonExec::HomeMonExec
// END USER INSERT SECTION HomeMonExec::HomeMonExec
}


HomeMonExec::~HomeMonExec()
{
// BEGIN USER INSERT SECTION HomeMonExec::~HomeMonExec
// END USER INSERT SECTION HomeMonExec::~HomeMonExec

}


void
HomeMonExec::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
HomeMonExec::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION HomeMonExec::create
// END USER INSERT SECTION HomeMonExec::create
    return new MonImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_monitor_homeE(void)
{
// BEGIN USER INSERT SECTION create_monitor_home
// END USER INSERT SECTION create_monitor_home

    return new ::container_service::HomeMonExec();
}

