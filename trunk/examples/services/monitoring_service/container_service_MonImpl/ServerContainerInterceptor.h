#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"

namespace Qedo {

	class ServerContainerInterceptor: public virtual Components::Extension::ServerContainerInterceptor,
		public virtual Qedo::RefCountLocalObject
	{
	private:

	public:
		ServerContainerInterceptor();

		~ServerContainerInterceptor();

		virtual void receive_request (::PortableInterceptor::ServerRequestInfo_ptr info, const char * id) ;
		virtual void send_reply (::PortableInterceptor::ServerRequestInfo_ptr info) ;
		virtual void send_system_exception (::PortableInterceptor::ServerRequestInfo_ptr info) ;
		virtual void send_user_exception (::PortableInterceptor::ServerRequestInfo_ptr info) ;
		virtual void rec_request_from_servant_locator(const char* operation);

	};
}; // namespace Qedo
