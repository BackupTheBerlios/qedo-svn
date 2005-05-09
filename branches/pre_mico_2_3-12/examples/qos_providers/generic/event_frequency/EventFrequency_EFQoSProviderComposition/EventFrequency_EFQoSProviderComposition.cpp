//
// generated by Qedo
//

#include "EventFrequency_EFQoSProviderComposition.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace EventFrequency {


// BEGIN USER INSERT SECTION EFQoSProviderExec
// END USER INSERT SECTION EFQoSProviderExec


EFQoSProviderExec::EFQoSProviderExec()
{
// BEGIN USER INSERT SECTION EFQoSProviderExec::EFQoSProviderExec
// END USER INSERT SECTION EFQoSProviderExec::EFQoSProviderExec
}


EFQoSProviderExec::~EFQoSProviderExec()
{
// BEGIN USER INSERT SECTION EFQoSProviderExec::~EFQoSProviderExec
// END USER INSERT SECTION EFQoSProviderExec::~EFQoSProviderExec

}


void
EFQoSProviderExec::set_context(::EventFrequency::CCM_EFQoSProvider_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::EventFrequency::CCM_EFQoSProvider_ContextImpl::_duplicate(context);
}


void
EFQoSProviderExec::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION EFQoSProviderExec::configuration_complete

// get interceptor_registration
Components::Extension::ServerInterceptorRegistration_var server_reg =
	context_ -> get_server_interceptor_dispatcher_registration();

// check for contract assignments
Components::ConfigValues_var contract_info =
	context_ -> get_contract_data();

//for (CORBA::ULong counter = 0; counter < contract_info -> length(), counter++ )
//{
CORBA::Any an_any;
	an_any = contract_info.in()[2]->value();
	CORBA::Long freq;
	an_any >>= freq;
//}
//create Server interceptor interface
server_interceptor_ = new Qedo::EFServerContainerInterceptor(freq);

//register it with interceptor dispatcher
std::string component_id = "reader";
server_reg -> register_interceptor_for_component(server_interceptor_, component_id.c_str());

// register interceptor for all
//server_reg -> register_interceptor_for_all(server_interceptor_);


// register QoS Usage interface
FreqUsageImpl* usage = new FreqUsageImpl(server_interceptor_);
context_ -> install_service_reference("Freq", usage);

// END USER INSERT SECTION EFQoSProviderExec::configuration_complete
}


void
EFQoSProviderExec::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION EFQoSProviderExec::remove
// END USER INSERT SECTION EFQoSProviderExec::remove
}


void
EFQoSProviderExec::set_frequency(CORBA::Long freq)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION EFQoSProviderExec::set_frequency
// END USER INSERT SECTION EFQoSProviderExec::set_frequency
}


// BEGIN USER INSERT SECTION EFQoSProviderComposition
// END USER INSERT SECTION EFQoSProviderComposition


EFQoSProviderComposition::EFQoSProviderComposition()
:component_(new EFQoSProviderExec())
{
// BEGIN USER INSERT SECTION EFQoSProviderComposition::EFQoSProviderComposition
// END USER INSERT SECTION EFQoSProviderComposition::EFQoSProviderComposition
}


EFQoSProviderComposition::~EFQoSProviderComposition()
{
// BEGIN USER INSERT SECTION EFQoSProviderComposition::~EFQoSProviderComposition
// END USER INSERT SECTION EFQoSProviderComposition::~EFQoSProviderComposition

    component_->_remove_ref();
}


::CORBA::Object*
EFQoSProviderComposition::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "qos_usage")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
EFQoSProviderComposition::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
EFQoSProviderComposition::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION EFQoSProviderComposition::configuration_complete
// END USER INSERT SECTION EFQoSProviderComposition::configuration_complete
}


void
EFQoSProviderComposition::set_extension_context(::Components::ExtensionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::EventFrequency::CCM_EFQoSProvider_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::EventFrequency::CCM_EFQoSProvider_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::EventFrequency::CCM_EFQoSProvider_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::EventFrequency::CCM_EFQoSProvider_ContextImpl::_nil();
        
    #else
    context_ = ::EventFrequency::CCM_EFQoSProvider_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
EFQoSProviderComposition::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION EFQoSProviderComposition::ccm_activate
// END USER INSERT SECTION EFQoSProviderComposition::ccm_activate
}


void
EFQoSProviderComposition::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION EFQoSProviderComposition::ccm_passivate
// END USER INSERT SECTION EFQoSProviderComposition::ccm_passivate
}


void
EFQoSProviderComposition::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION EFQoSProviderComposition::ccm_remove
// END USER INSERT SECTION EFQoSProviderComposition::ccm_remove
}


// BEGIN USER INSERT SECTION EFQoSProviderHomeExec
// END USER INSERT SECTION EFQoSProviderHomeExec


EFQoSProviderHomeExec::EFQoSProviderHomeExec()
{
// BEGIN USER INSERT SECTION EFQoSProviderHomeExec::EFQoSProviderHomeExec
// END USER INSERT SECTION EFQoSProviderHomeExec::EFQoSProviderHomeExec
}


EFQoSProviderHomeExec::~EFQoSProviderHomeExec()
{
// BEGIN USER INSERT SECTION EFQoSProviderHomeExec::~EFQoSProviderHomeExec
// END USER INSERT SECTION EFQoSProviderHomeExec::~EFQoSProviderHomeExec

}


void
EFQoSProviderHomeExec::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
EFQoSProviderHomeExec::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION EFQoSProviderHomeExec::create
// END USER INSERT SECTION EFQoSProviderHomeExec::create
    return new EFQoSProviderComposition();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_EFQoSProviderHomeE(void)
{
// BEGIN USER INSERT SECTION create_EFQoSProviderHome
// END USER INSERT SECTION create_EFQoSProviderHome

    return new ::EventFrequency::EFQoSProviderHomeExec();
}
