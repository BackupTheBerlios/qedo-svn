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
		PortableInterceptor::SlotId slot_id_;
	public:
		EFServerContainerInterceptor();
		EFServerContainerInterceptor(long freq);

		~EFServerContainerInterceptor();

		virtual void set_slot_id(PortableInterceptor::SlotId id);
		virtual void receive_request (::Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_reply (::Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_system_exception (::Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_user_exception (::Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void rec_request_from_servant_locator(const char* operation);

	};
}; // namespace Qedo
