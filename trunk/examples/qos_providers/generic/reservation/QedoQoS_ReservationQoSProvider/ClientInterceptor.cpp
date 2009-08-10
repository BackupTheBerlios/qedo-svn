#include "ClientInterceptor.h"
#include "valuetypes.h"
#include "output.h"
#include "qedoutil.h"
#include "Util.h"
#include "GlobalHelpers.h"


namespace QedoQoS_Reservation {

char*
ClientContainerInterceptor::name()
{
	return "Reservation";
};

void
ClientContainerInterceptor::destroy()
{
};

void 
ClientContainerInterceptor::set_slot_id(PortableInterceptor::SlotId slot_id) {
	slot_id_ = slot_id;
};


ClientContainerInterceptor::ClientContainerInterceptor (QedoQoS::CCM_Reservation_ContextImpl* context, QedoQoS::ReservationQoSproviderImpl* executor)
{
	executor_ = executor;
	context_ = context;


}

ClientContainerInterceptor::~ClientContainerInterceptor ()
{
}


void
ClientContainerInterceptor::stub_send_request (Components::ContainerPortableInterceptor::ContainerStubRequestInfo_ptr info, CORBA::Boolean_out con)
{
	std::cout << "ClientCOPI: send_request: " << info->operation();
	CORBA::OctetSeq* temp_seq;
	temp_seq = info->origin_id();
	CORBA::String_var temp_string;
	//temp_string = Qedo::OctetSeq_to_string(*temp_seq); 
	//std::cout << Qedo::OctetSeq_to_string(*temp_seq) << std::endl;
	DEBUG_OUT2 ("for id: ", Qedo::OctetSeq_to_string(*temp_seq));
	CORBA::Any any;
	// This needs to be re´placed by own id
	// get it from the current slot
	any <<= "id";

/*
	CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(any);

	IOP::ServiceContext sc;

	sc.context_id = 100;

	sc.context_data.length(data->length());

	memcpy(sc.context_data.get_buffer(), data->get_buffer(), data->length());

	info->request_info()->add_request_service_context(sc, true);
*/	
}

void
ClientContainerInterceptor::send_poll (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr info)
{
	//std::cout << "ClientCOPI: send_request: " << info->request_info()->operation() << std::endl;

	CORBA::Any any;
	// This needs to be re´placed by own id
	// get it from the current slot
	any <<= "id";
}

void
ClientContainerInterceptor::stub_receive_reply (Components::ContainerPortableInterceptor::ContainerStubRequestInfo_ptr info,CORBA::Boolean_out con)
{
	
//	std::cout << "ClientCOPI: receive_reply: " << info->request_info()->operation() << std::endl;
/*
	IOP::ServiceContext* sc = 0;
	char *message_data;
	CORBA::Any_var any = new CORBA::Any;
	try {
		sc = info->request_info()->get_reply_service_context(100);	
		
		CORBA::OctetSeq data;

		data.length(sc->context_data.length());
		memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
		any = executor_-> get_cdr_codec_ptr() -> decode_value(data, CORBA::_tc_string);


		any >>= message_data;
		
	} catch (CORBA::BAD_PARAM&)
	{
		//no service context 
	} catch (...)
	{
		return;
	}
*/
}

void
ClientContainerInterceptor::stub_receive_exception (Components::ContainerPortableInterceptor::ContainerStubRequestInfo_ptr info, CORBA::Boolean_out con)
{
//	std::cout << "ClientCOPI: receive_system_exception: " << info->request_info()->operation() << std::endl;


}

void
ClientContainerInterceptor::stub_receive_other (Components::ContainerPortableInterceptor::ContainerStubRequestInfo_ptr info) {
//	std::cout << "ClientCOPI: receive_user_exception: " << info->request_info()->operation() << std::endl;

}

Components::Cookie* 
ClientContainerInterceptor::connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Client: connect called" << std::endl;
	con = true;
	return 0;	
}

CORBA::Object_ptr 
ClientContainerInterceptor::provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Client: provide_facet called" << std::endl;
	return CORBA::Object::_nil();
}

Components::Cookie* 
ClientContainerInterceptor::bind( const char* comp_id, char*& name, ::StreamComponents::SinkStreamPort_ptr& the_sink, char*& transport_profile, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Client: bind called" << std::endl;
	return 0;
}

::StreamComponents::SinkStreamPort_ptr 
ClientContainerInterceptor::unbind( const char* comp_id, char*& name, Components::Cookie*& ck, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Client: unbind called" << std::endl;
	return 0;
}

CORBA::Object_ptr 
ClientContainerInterceptor::provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Client: provide_sink_stream_port" << std::endl;
	return 0;
}

}; // QedoQoS_Reservation 
