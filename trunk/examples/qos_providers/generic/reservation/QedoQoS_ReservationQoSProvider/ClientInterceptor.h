#ifndef __RESERVATION_CLIENTCOPI_H__
#define __RESERVATION_CLIENTCOPI_H__

#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"
#include "QedoQoS_ReservationQoSProvider_LOCAL.h"

namespace QedoQoS_Reservation {
	class ClientContainerInterceptor;
};

#include "QedoQoS_ReservationQoSProvider.h"


namespace QedoQoS_Reservation {

	class ClientContainerInterceptor: public virtual Components::Extension::ClientContainerInterceptor
	{
	private:
		QedoQoS::CCM_Reservation_ContextImpl* context_;

		PortableInterceptor::SlotId slot_id_;
		std::string		m_uid;
		QedoQoS::ReservationQoSproviderImpl* executor_;
	public:
		ClientContainerInterceptor(QedoQoS::CCM_Reservation_ContextImpl* context, QedoQoS::ReservationQoSproviderImpl* executor);

		~ClientContainerInterceptor();

		virtual void set_slot_id(PortableInterceptor::SlotId slot_id);
		virtual void send_request (Components::Extension::ContainerClientRequestInfo_ptr info) ;
		virtual void receive_reply (Components::Extension::ContainerClientRequestInfo_ptr info) ;
		virtual void receive_system_exception (Components::Extension::ContainerClientRequestInfo_ptr info) ;
		virtual void receive_user_exception (Components::Extension::ContainerClientRequestInfo_ptr info) ;
//		virtual void rec_request_from_servant_locator(const char* operation);

		virtual Components::Cookie* connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) ;
		virtual CORBA::Object_ptr provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con ) ;
		virtual Components::Cookie* bind( const char* comp_id, char*& name, ::StreamComponents::SinkStreamPort_ptr& the_sink, char*& transport_profile, CORBA::Boolean_out con ) ;
		virtual ::StreamComponents::SinkStreamPort_ptr unbind( const char* comp_id, char*& name, Components::Cookie*& ck, CORBA::Boolean_out con ) ;
		virtual CORBA::Object_ptr provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) ;

	};
}; // namespace Qedo

#endif