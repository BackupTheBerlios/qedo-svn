#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"

namespace Qedo {

	class ExtensionBase 
	{
	protected:
		Qedo::ContainerInterceptor* interceptor_;
	public:
		ExtensionBase();

		~ExtensionBase();

		virtual void
		register_container_interceptors(Components::ExtensionContext_ptr context);

	};

} // Qedo