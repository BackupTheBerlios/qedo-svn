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

	class ServerContainerInterceptor: public virtual Components::Extension::ServerContainerInterceptor
	{
	private:
		QedoQoS::CCM_Reservation_ContextImpl* context_;

		PortableInterceptor::SlotId slot_id_;
		std::string		m_uid;
		QedoQoS::ReservationQoSproviderImpl* executor_;

		// this is an short cut for the reservation 
		CORBA::ULong number_of_calls;
		__time64_t time_stamp;

	public:
		ServerContainerInterceptor(QedoQoS::CCM_Reservation_ContextImpl* context, QedoQoS::ReservationQoSproviderImpl* executor);

		~ServerContainerInterceptor();

		virtual void set_slot_id(PortableInterceptor::SlotId slot_id);
		virtual void receive_request (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_reply (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_system_exception (Components::Extension::ContainerServerRequestInfo_ptr info) ;
		virtual void send_user_exception (Components::Extension::ContainerServerRequestInfo_ptr info) ;

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