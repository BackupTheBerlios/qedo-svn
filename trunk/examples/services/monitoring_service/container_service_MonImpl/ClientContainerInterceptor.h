#ifndef __MONITORING_CLIENTCOPI_H__
#define __MONITORING_CLIENTCOPI_H__

#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"
#include "container_service_MonImpl_LOCAL.h"
namespace Qedo {
	class ClientContainerInterceptor;
};

#include "container_service_MonImpl.h"

namespace Qedo {

	class ClientContainerInterceptor: public virtual Components::Extension::ClientContainerInterceptor
	{
	private:
	container_service::CCM_monitor_Context* context_;
	std::string  hostname_;
	std::string process_id_;
	PortableInterceptor::SlotId slot_id_;
	std::string		m_uid;
	container_service::MonExec* executor_;
	public:
		ClientContainerInterceptor(container_service::CCM_monitor_Context* context, container_service::MonExec* executor);

		~ClientContainerInterceptor();

		virtual void set_slot_id(PortableInterceptor::SlotId slot_id);
		virtual void send_request (Components::Extension::ContainerClientRequestInfo_ptr info) ;
		virtual void receive_reply (Components::Extension::ContainerClientRequestInfo_ptr info) ;
		virtual void receive_system_exception (Components::Extension::ContainerClientRequestInfo_ptr info) ;
		virtual void receive_user_exception (Components::Extension::ContainerClientRequestInfo_ptr info) ;
//		virtual void rec_request_from_servant_locator(const char* operation);

	};
}; // namespace Qedo

#endif