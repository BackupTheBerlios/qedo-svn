#ifndef _EventFrequency_ServerContainerInterceptor_H_
#define _EventFrequency_ServerContainerInterceptor_H_

#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"

namespace Qedo {

	class EFServerContainerInterceptor: public virtual Components::ContainerPortableInterceptor::ServerContainerInterceptor
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

		void set_freq(long freq);

		virtual char* name ();
		virtual void destroy ();
		virtual void set_slot_id(PortableInterceptor::SlotId id);
		virtual void receive_request (::Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr info) ;
		virtual void send_reply (::Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr info) ;
		virtual void send_system_exception (::Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr info) ;
		virtual void send_user_exception (::Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr info) ;
//		virtual void rec_request_from_servant_locator(const char* operation);

	};
}; // namespace Qedo
#endif