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

	class ServerContainerInterceptor: public virtual Components::ContainerPortableInterceptor::ServerContainerInterceptor
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

		virtual char* 
		name() ;
		
		virtual void 
		destroy();
		
		virtual void 
		set_slot_id(PortableInterceptor::SlotId slot_id);
		
		virtual void 
		receive_request_service_contexts (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;

		virtual void 
		receive_request (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
		
		virtual void 
		send_reply (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
		
		virtual void 
		send_exception (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
		
		virtual void 
		send_other (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;


/*
		virtual void call( const char* comp_id, const char* origin, const char* operation, CORBA::Boolean_out con ) ;

		virtual Components::Cookie* connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) ;
	    virtual CORBA::Object_ptr provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con );

		virtual Components::Cookie* bind( const char* comp_id, char*& name, ::StreamComponents::SinkStreamPort_ptr& the_sink, char*& transport_profile, CORBA::Boolean_out con ) ;
		virtual ::StreamComponents::SinkStreamPort_ptr unbind( const char* comp_id, char*& name, Components::Cookie*& ck, CORBA::Boolean_out con ) ;
		virtual CORBA::Object_ptr provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) ;
*/
	};
}; // namespace Qedo

#endif