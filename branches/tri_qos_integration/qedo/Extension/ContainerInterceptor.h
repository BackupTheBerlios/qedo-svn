#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"

namespace Qedo {

	class ContainerInterceptor : public virtual Components::Extension::ContainerInterceptor,
                                 public virtual RefCountLocalObject
	{
	public:
		ContainerInterceptor();

		~ContainerInterceptor();

		virtual void get_message(const char* mess);

	};

} // Qedo