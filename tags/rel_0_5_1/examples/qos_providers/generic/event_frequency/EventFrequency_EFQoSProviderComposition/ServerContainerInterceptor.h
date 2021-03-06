#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"

namespace Qedo {

	class EFServerContainerInterceptor: public virtual Components::Extension::ServerContainerInterceptor
	{
	private:
		unsigned long count;
		long frequency_;
		time_t stamp;
	public:
		EFServerContainerInterceptor();
		EFServerContainerInterceptor(long freq);

		~EFServerContainerInterceptor();

		virtual void receive_request (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id) ;
		virtual void send_reply (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id) ;
		virtual void send_system_exception (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id) ;
		virtual void send_user_exception (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id) ;
		virtual void rec_request_from_servant_locator(const char* operation);

	};
}; // namespace Qedo
