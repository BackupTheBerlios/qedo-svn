#ifndef __RESERVATION_SERVERCOPI_H__
#define __RESERVATION_SERVERCOPI_H__

#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"
#include "QedoQoS_ReservationQoSProvider_LOCAL.h"

namespace QedoQoS_Reservation {
	class ServerContainerInterceptor;
};

#include "QedoQoS_ReservationQoSProvider.h"
#include <time.h>


namespace QedoQoS_Reservation {

	class ServerContainerInterceptor: public virtual Components::ContainerPortableInterceptor::ServantContainerInterceptor
	{
	private:
		QedoQoS::CCM_Reservation_ContextImpl* context_;

		PortableInterceptor::SlotId slot_id_;
		std::string		m_uid;
		QedoQoS::ReservationQoSproviderImpl* executor_;

		Components::Cookie_var contract_cookie;
		// this is an short cut for the reservation 
		CORBA::ULong number_of_calls;
		__time64_t time_stamp;

		// store information for contract negotiation
		// using better data structure later
		std::string comp_origin_id;
		std::string operation_id;
		Components::ConfigValues* data;

		std::string server_origin;
		std::string server_operation;
		Components::ConfigValues* server_data;

		CORBA::ULong number_of_calls_;
		CORBA::ULong intervall_;

	public:
		ServerContainerInterceptor(QedoQoS::CCM_Reservation_ContextImpl* context, QedoQoS::ReservationQoSproviderImpl* executor);

		~ServerContainerInterceptor();


		virtual void register_requirement(char * component_id, char * receptacle_name, Components::ConfigValues* req);

		virtual void add_contract(const char *component_id, Components::ConfigValues);

		virtual char* name();
		virtual void destroy();
		virtual void set_slot_id(PortableInterceptor::SlotId slot_id);

		virtual void receive_request_service_contexts (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr info) ;
		virtual void servant_receive_request (Components::ContainerPortableInterceptor::ContainerServantRequestInfo_ptr info, CORBA::Boolean_out con) ;
		virtual void servant_send_reply (Components::ContainerPortableInterceptor::ContainerServantRequestInfo_ptr info, CORBA::Boolean_out con) ;
		virtual void servant_send_exception (Components::ContainerPortableInterceptor::ContainerServantRequestInfo_ptr info, CORBA::Boolean_out con) ;
		virtual void servant_send_other (Components::ContainerPortableInterceptor::ContainerServantRequestInfo_ptr info) ;

	    virtual void call( const char* comp_id, const char* origin, const char* operation, CORBA::Boolean_out con ) ;

		virtual void rec_request_from_servant_locator(const char* operation);

		virtual Components::Cookie* connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) ;
	    virtual CORBA::Object_ptr provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con );

		virtual Components::Cookie* bind( const char* comp_id, char*& name, ::StreamComponents::SinkStreamPort_ptr& the_sink, char*& transport_profile, CORBA::Boolean_out con ) ;
		virtual ::StreamComponents::SinkStreamPort_ptr unbind( const char* comp_id, char*& name, Components::Cookie*& ck, CORBA::Boolean_out con ) ;
		virtual CORBA::Object_ptr provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) ;

	};
}; // namespace QedoQoS

#endif