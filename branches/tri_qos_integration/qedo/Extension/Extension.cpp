#include "ContainerInterceptor.h"
#include "Extension.h"

namespace Qedo {
	ExtensionBase::ExtensionBase()
	{

	}

	ExtensionBase::~ExtensionBase()
	{

	}

	void 
	ExtensionBase::register_container_interceptors(Components::ExtensionContext_ptr context) 
	{
		interceptor_ = new Qedo::ContainerInterceptor;
		Components::Extension::ServerInterceptorRegistration_ptr server_registration;
		server_registration = context-> get_server_interceptor_dispatcher_registration();
		server_registration -> register_server_interceptor(interceptor_);
	}

} // Qedo