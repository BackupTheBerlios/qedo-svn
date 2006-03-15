//
// generated by Qedo
//

#include "QedoQoS_ReservationQoSProvider.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace QedoQoS {


// BEGIN USER INSERT SECTION ReservationQoSproviderImpl
void
ReservationQoSproviderImpl::register_copis()
{
	std::cout << "ReservationQoSProvider: register_copis" << std::endl;

	client_interceptor_ = new QedoQoS_Reservation::ClientContainerInterceptor(context_, this);
	server_interceptor_ = new QedoQoS_Reservation::ServerContainerInterceptor(context_, this);

	//server
	Components::ContainerPortableInterceptor::ServerContainerInterceptorRegistration_ptr server_reg =
		context_->get_server_interceptor_dispatcher_registration();
	server_reg->register_server_interceptor(server_interceptor_);

	//Client
	Components::ContainerPortableInterceptor::ClientContainerInterceptorRegistration_ptr client_reg =
		context_->get_client_interceptor_dispatcher_registration();
	client_reg->register_client_interceptor(client_interceptor_);

	//Servant
	Components::ContainerPortableInterceptor::ServantContainerInterceptorRegistration_ptr servant_reg =
		context_->get_servant_interceptor_dispatcher_registration();
	servant_reg->register_servant_interceptor(server_interceptor_);

	//Stub
	Components::ContainerPortableInterceptor::StubContainerInterceptorRegistration_ptr stub_reg =
		context_ -> get_stub_interceptor_dispatcher_registration();
	stub_reg -> register_stub_interceptor(client_interceptor_);
}

void
ReservationQoSproviderImpl::unregister_copis()
{
	std::cout << "ReservationQoSProvider: unregister_copis" << std::endl;

	//server
	Components::ContainerPortableInterceptor::ServerInterceptorRegistration_ptr server_reg =
		context_->get_server_interceptor_dispatcher_registration();
	server_reg->unregister_interceptor_for_all(server_interceptor_);

	//Client
	Components::ContainerPortableInterceptor::ClientInterceptorRegistration_ptr client_reg =
		context_->get_client_interceptor_dispatcher_registration();
	client_reg->register_interceptor_for_all(client_interceptor_);

	//Servant
	Components::ContainerPortableInterceptor::ServantInterceptorRegistration_ptr servant_reg =
		context_->get_servant_interceptor_dispatcher_registration();
	servant_reg->register_interceptor_for_all(server_interceptor_);

	//Stub
	Components::ContainerPortableInterceptor::StubInterceptorRegistration_ptr stub_reg =
		context_ -> get_stub_interceptor_dispatcher_registration();
	stub_reg -> unregister_interceptor_for_all(client_interceptor_);
}

void
ReservationQoSproviderImpl::init_copis(Components::ConfigValues* config) 
{
	CORBA::Any test_any;

	std::cout << "length of config values: " << config->length() << std::endl;
	char* req_component_id;
	char* req_operation_name;
	Components::ConfigValues* data;
	// search for extensionspecification
	CORBA::ULong len;
	for (len = 0; len < config->length(); len++)
	{
		if (!strcmp((*config)[len]->name(),"extensionspecification"))
		{
			Components::ConfigValues *extension_content;
			Components::ConfigValue *extension_content_test;
			CORBA::Any test_any;
			test_any = ((*config)[len]-> value()) ;
			// ((*config)[len]-> value()) >>= test_any;
			test_any >>= extension_content;
			CORBA::ULong ext_len;
			for (ext_len = 0; ext_len < extension_content->length(); ext_len++)
			{
				// search for binding
				if ( !strcmp((*extension_content)[ext_len]->name(), "binding"))
				{
					Components::ConfigValues *binding_content;
					((*extension_content)[ext_len]-> value()) >>= binding_content ;
					CORBA::ULong binding_len;
					for (binding_len = 0; binding_len < binding_content->length(); binding_len++)
					{
						// search for component_id
						if (!strcmp((*binding_content)[binding_len]->name(), "componentid"))
						{
							((*binding_content)[binding_len]-> value()) >>= req_component_id;
						} // end of component_id

						// search for restriction
						if (!strcmp((*binding_content)[binding_len]->name(), "restriction"))
						{
							((*binding_content)[binding_len]-> value()) >>= req_operation_name;
						} // end of restriction
					} // end of binding search
				} // end serach for binding

				//search for constraint
				if ( !strcmp((*extension_content)[ext_len]->name(), "constraint"))
				{
					Components::ConfigValues *constraint_content;
					Components::ConfigValue *test;
					((*extension_content)[ext_len]-> value()) >>= constraint_content ;
					CORBA::ULong constraint_len;
					for (constraint_len = 0; constraint_len < constraint_content->length(); constraint_len++)
					{
						// search for charakteristic
						if ( !strcmp((*constraint_content)[constraint_len]->name(), "characteristic"))
						{
							// only search for reservation
							// first element of content needs to be a name=Reservation
							Components::ConfigValues *characteristic_content;

							//((*constraint_content)[constraint_len]-> value()) >>= characteristic_content ;
							CORBA::Any *test2_any = new CORBA::Any((*constraint_content)[constraint_len] -> value()) ;
							*test2_any >>= data;//constraint_content;

							char* char_name;
								if ( !strcmp((*data)[0]->name(), "name"))
								{
									((*data)[0]-> value()) >>= char_name;
									if (!strcmp(char_name,"Reservation"))
									{
									//	((*constraint_content)[constraint_len]-> value()) >>= data;
										//data = characteristic_content;
										
									} // end if Reservation
		
								} // end name
						} // end of if characteristic
					}
				}
			} // end of for extension_content
				server_interceptor_ -> register_requirement(req_component_id, req_operation_name, data);
		} // end of if extensionspecification
	} // end of extensionspecification search
}

// END USER INSERT SECTION ReservationQoSproviderImpl


ReservationQoSproviderImpl::ReservationQoSproviderImpl()
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::ReservationQoSproviderImpl
// END USER INSERT SECTION ReservationQoSproviderImpl::ReservationQoSproviderImpl
}


ReservationQoSproviderImpl::~ReservationQoSproviderImpl()
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::~ReservationQoSproviderImpl
// END USER INSERT SECTION ReservationQoSproviderImpl::~ReservationQoSproviderImpl

}


void
ReservationQoSproviderImpl::set_context(::QedoQoS::CCM_Reservation_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::QedoQoS::CCM_Reservation_ContextImpl::_duplicate(context);
}


void
ReservationQoSproviderImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::configuration_complete
	// create interceptors

	//register interceptors
	
// END USER INSERT SECTION ReservationQoSproviderImpl::configuration_complete
}


void
ReservationQoSproviderImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::remove
// END USER INSERT SECTION ReservationQoSproviderImpl::remove
}


void
ReservationQoSproviderImpl::trigger_negotiation()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::trigger_negotiation
// END USER INSERT SECTION ReservationQoSproviderImpl::trigger_negotiation
}


Components::Extension::ContractDescription*
ReservationQoSproviderImpl::req_offer(const Components::Extension::ContractDescription& requirements, const char* client_id)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::req_offer
	std::cout << "@@@@@@@@ got req_contract" << std::endl;
	// check for availability

	// create offer

	// store offer information and reserver resources for the offer

	// return offer
	return new Components::Extension::ContractDescription(requirements); 
// END USER INSERT SECTION ReservationQoSproviderImpl::req_offer
}


CORBA::Boolean
ReservationQoSproviderImpl::accept(const Components::Extension::ContractDescription& requirements, const char* client_id)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl::accept
	std::cout << "@@@@@@@@ got accept" << std::endl;

	// check for offer reservation

	// use ressources

	// store contract info
	server_interceptor_ -> add_contract(client_id, requirements.dimensions);

	// return an identfier
	// true meanwhile
	return true;
// END USER INSERT SECTION ReservationQoSproviderImpl::accept
}


// BEGIN USER INSERT SECTION ReservationQoSProvider
// END USER INSERT SECTION ReservationQoSProvider


ReservationQoSProvider::ReservationQoSProvider()
:component_(new ReservationQoSproviderImpl())
{
// BEGIN USER INSERT SECTION ReservationQoSProvider::ReservationQoSProvider
// END USER INSERT SECTION ReservationQoSProvider::ReservationQoSProvider
}


ReservationQoSProvider::~ReservationQoSProvider()
{
// BEGIN USER INSERT SECTION ReservationQoSProvider::~ReservationQoSProvider
// END USER INSERT SECTION ReservationQoSProvider::~ReservationQoSProvider

    component_->_remove_ref();
}


::CORBA::Object*
ReservationQoSProvider::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "nego_external")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
ReservationQoSProvider::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
ReservationQoSProvider::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION ReservationQoSProvider::configuration_complete
// END USER INSERT SECTION ReservationQoSProvider::configuration_complete
}


void
ReservationQoSProvider::set_extension_context(::Components::ExtensionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::QedoQoS::CCM_Reservation_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::QedoQoS::CCM_Reservation_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::QedoQoS::CCM_Reservation_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::QedoQoS::CCM_Reservation_ContextImpl::_nil();
        
    #else
    context_ = ::QedoQoS::CCM_Reservation_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
ReservationQoSProvider::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ReservationQoSProvider::ccm_activate

	component_ -> register_copis();
	component_ -> init_copis(context_ -> get_contract_data());

// END USER INSERT SECTION ReservationQoSProvider::ccm_activate
}


void
ReservationQoSProvider::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ReservationQoSProvider::ccm_passivate
	component_ -> unregister_copis();
// END USER INSERT SECTION ReservationQoSProvider::ccm_passivate
}


void
ReservationQoSProvider::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ReservationQoSProvider::ccm_remove
// END USER INSERT SECTION ReservationQoSProvider::ccm_remove
}


// BEGIN USER INSERT SECTION ReservationQoSProviderHomeImpl
// END USER INSERT SECTION ReservationQoSProviderHomeImpl


ReservationQoSProviderHomeImpl::ReservationQoSProviderHomeImpl()
{
// BEGIN USER INSERT SECTION ReservationQoSProviderHomeImpl::ReservationQoSProviderHomeImpl
// END USER INSERT SECTION ReservationQoSProviderHomeImpl::ReservationQoSProviderHomeImpl
}


ReservationQoSProviderHomeImpl::~ReservationQoSProviderHomeImpl()
{
// BEGIN USER INSERT SECTION ReservationQoSProviderHomeImpl::~ReservationQoSProviderHomeImpl
// END USER INSERT SECTION ReservationQoSProviderHomeImpl::~ReservationQoSProviderHomeImpl

}


void
ReservationQoSProviderHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
ReservationQoSProviderHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION ReservationQoSProviderHomeImpl::create
// END USER INSERT SECTION ReservationQoSProviderHomeImpl::create
    return new ReservationQoSProvider();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ReservationHomeE(void)
{
// BEGIN USER INSERT SECTION create_ReservationHome
// END USER INSERT SECTION create_ReservationHome

    return new ::QedoQoS::ReservationQoSProviderHomeImpl();
}

