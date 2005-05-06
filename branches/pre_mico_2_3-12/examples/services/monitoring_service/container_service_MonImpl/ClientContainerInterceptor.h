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

	class ClientContainerInterceptor: public virtual Components::ContainerPortableInterceptor::ClientContainerInterceptor
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

	    virtual char* 
		name() ;
		
		virtual void 
		destroy();
		
		virtual void 
		set_slot_id(PortableInterceptor::SlotId slot_id);
		
		virtual void 
		send_request (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci) ;
		
		virtual void 
		send_poll (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci) ;

		virtual void 
		receive_reply (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci) ;
		
		virtual void 
		receive_exception (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci) ;
		
		virtual void 
		receive_other (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci) ;

		
/*
		virtual Components::Cookie* connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) ;
		virtual CORBA::Object_ptr provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con ) ;
		virtual Components::Cookie* bind( const char* comp_id, char*& name, ::StreamComponents::SinkStreamPort_ptr& the_sink, char*& transport_profile, CORBA::Boolean_out con ) ;
		virtual ::StreamComponents::SinkStreamPort_ptr unbind( const char* comp_id, char*& name, Components::Cookie*& ck, CORBA::Boolean_out con ) ;
		virtual CORBA::Object_ptr provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) ;
*/
	};
}; // namespace Qedo

#endif