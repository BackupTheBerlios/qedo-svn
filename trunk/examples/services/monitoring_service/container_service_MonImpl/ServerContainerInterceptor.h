#ifndef __MONITORING_SERVERCOPI_H__
#define __MONITORING_SERVERCOPI_H__

#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"
#include "container_service_MonImpl_LOCAL.h"

namespace Qedo {
	class ServerContainerInterceptor;
};
#include "container_service_MonImpl.h"

namespace Qedo {

	class ServerContainerInterceptor: public virtual Components::Extension::ServerContainerInterceptor
	{
	private:
	container_service::CCM_monitor_Context* context_;
	std::string hostname_;
	std::string process_id_;
	PortableInterceptor::SlotId slot_id_;
	container_service::MonExec* executor_;

	public:
		ServerContainerInterceptor(container_service::CCM_monitor_Context* context, container_service::MonExec* executor);

		~ServerContainerInterceptor();

		virtual void set_slot_id(PortableInterceptor::SlotId slot_id);
		virtual void receive_request (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_reply (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_system_exception (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_user_exception (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void rec_request_from_servant_locator(const char* operation);

	};
}; // namespace Qedo

#endif