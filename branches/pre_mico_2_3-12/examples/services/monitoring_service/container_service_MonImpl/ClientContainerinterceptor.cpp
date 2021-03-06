#include "ClientContainerInterceptor.h"
#include <sys/timeb.h>


namespace Qedo {

char*
ClientContainerInterceptor::name()
{
	return "anon";
};

void 
ClientContainerInterceptor::destroy() {
};

void 
ClientContainerInterceptor::set_slot_id(PortableInterceptor::SlotId slot_id) {
	slot_id_ = slot_id;
};


ClientContainerInterceptor::ClientContainerInterceptor (container_service::CCM_monitor_Context* context,container_service::MonExec* executor)
{
	executor_ = executor;
	context_ = context;

	char hostname[256];
	gethostname(hostname, 256);
	hostname_ = hostname;

	DWORD pid = GetCurrentProcessId();

	char s[11];

	sprintf (s, "%d", pid);

	process_id_ = s;
	
	m_uid = s;	

}

ClientContainerInterceptor::~ClientContainerInterceptor ()
{
}

void
ClientContainerInterceptor::send_request (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci)
{

	std::cout << "COPI: send_request: " << cci->request_info()->operation() << std::endl;
		if ( 0 == strcmp (cci->request_info()->operation(), "receiveEvent") )
	{
		/*
		 * Suppress interception of handling for events to Trace server
		 */

		return;
	}

		org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

		// set time_stamp
		struct _timeb current_time;
		_ftime(&current_time);
		CORBA::LongLong tm = current_time.time;
		tm = tm * 1000 + current_time.millitm;
		event->time_stamp = tm;

		// set ineraction point
		event->interaction_point = org::coach::tracing::api::STUB_OUT;


		event->trail_label= CORBA::string_dup ("");

		unsigned long event_number = executor_ -> get_new_event_number();

		char cnt[11];
		sprintf (cnt, "__%08x", event_number);
		std::string messageid = process_id_ + cnt;

		std::cout << "@@ message_id client" << messageid.c_str() << std::endl;
		event->message_id = CORBA::string_dup (messageid.c_str());

		event->thread_id = CORBA::string_dup ("thread");

		std::string trail_id;
		trail_id = process_id_ + cnt;

		event->trail_id	= CORBA::string_dup (messageid.c_str());
		
		event->event_counter  = event_number;
		event->op_name = CORBA::string_dup (CORBA::string_dup(cci->request_info()->operation()));

		event->identity.object_instance_id		= CORBA::string_dup (cci->name());
		event->identity.object_repository_id	= CORBA::string_dup ("UNKNOWN");

		event->identity.cmp_name				= CORBA::string_dup (cci->component_id());
		event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
		event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
		event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
		event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
		event->identity.node_ip					= CORBA::string_dup (" e");
		event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

		event->parameters.length(0);

		org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
		trace->length(1);
		(*trace)[0] = event;
		context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());


		CORBA::Any any;
		any <<= messageid.c_str();
		CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(any);

		IOP::ServiceContext sc;

		sc.context_id = 101;

		sc.context_data.length(data->length());

		memcpy(sc.context_data.get_buffer(), data->get_buffer(), data->length());

		cci->request_info()->add_request_service_context(sc, true);
		
}

void
ClientContainerInterceptor::send_poll (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci)
{

}

void
ClientContainerInterceptor::receive_reply (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci)
{
	
	std::cout << "COPI: receive_reply: " << cci->request_info()->operation() << "for id: " << std::endl;
	if ( 0 == strcmp (cci->request_info()->operation(), "receiveEvent") )
	{
		/*
		 * Suppress PI handling for events to Trace server
		 */

		return;
	}

	char mess_cnt[11];
	unsigned long event_number = executor_ -> get_new_event_number();
	sprintf (mess_cnt, "__%08x", event_number);	

	IOP::ServiceContext* sc = 0;
	char *message_data;
	CORBA::Any_var any = new CORBA::Any;
	try {
		sc = cci->request_info()->get_reply_service_context(101);	
		
		CORBA::OctetSeq data;

		data.length(sc->context_data.length());
		memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
		any = executor_-> get_cdr_codec_ptr() -> decode_value(data, CORBA::_tc_string);


		any >>= message_data;
		
	} catch (CORBA::BAD_PARAM&)
	{
		//no service context for tracing
		message_data = new char[11];
		strcpy(message_data,mess_cnt);		
	} catch (...)
	{
		return;
	}
	std::cout << "@@@@@COPI after catch" << std::endl;
	org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

	// set time_stamp
	struct _timeb current_time;
	_ftime(&current_time);
	CORBA::LongLong tm = current_time.time;
	tm = tm * 1000 + current_time.millitm;
	event->time_stamp = tm;

	// set ineraction point
	event->interaction_point = org::coach::tracing::api::STUB_IN;


	event->trail_label= CORBA::string_dup ("");
	event->message_id = CORBA::string_dup (message_data);
	event->thread_id = CORBA::string_dup ("");
	event->trail_id	= CORBA::string_dup (message_data);
	event->event_counter  = event_number;
	event->op_name = CORBA::string_dup (CORBA::string_dup(cci->request_info()->operation()));
	event->identity.object_instance_id		= CORBA::string_dup (cci->name());
	event->identity.object_repository_id	= CORBA::string_dup ("UNKNOWN");
	event->identity.cmp_name				= CORBA::string_dup (cci->component_id());
	event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
	event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
	event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
	event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
	event->identity.node_ip					= CORBA::string_dup (" e");
	event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

	event->parameters.length(0);

	org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
	trace->length(1);
	(*trace)[0] = event;
	context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());

}

void
ClientContainerInterceptor::receive_exception (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci)
{
	std::cout << "COPI: receive_system_exception: " << cci->request_info()->operation() << "for id: " << std::endl;
	if ( 0 == strcmp (cci->request_info()->operation(), "receiveEvent") )
	{
		/*
		 * Suppress PI handling for events to Trace server
		 */

		return;
	}

	char mess_cnt[11];
	unsigned long event_number = executor_ -> get_new_event_number();
	sprintf (mess_cnt, "__%08x", event_number);	

	IOP::ServiceContext* sc = 0;
	char *message_data;
	CORBA::Any_var any = new CORBA::Any;
	try {
		sc = cci->request_info()->get_reply_service_context(100);	
		
		CORBA::OctetSeq data;

		data.length(sc->context_data.length());
		memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
		any = executor_-> get_cdr_codec_ptr() -> decode_value(data, CORBA::_tc_string);


		any >>= message_data;
		
	} catch (CORBA::BAD_PARAM&)
	{
		//no service context for tracing
		message_data = new char[11];
		strcpy(message_data,mess_cnt);		
	} catch (...)
	{
		return;
	}
	std::cout << "@@@@@COPI after catch" << std::endl;
	org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

	// set time_stamp
	struct _timeb current_time;
	_ftime(&current_time);
	CORBA::LongLong tm = current_time.time;
	tm = tm * 1000 + current_time.millitm;
	event->time_stamp = tm;

	// set ineraction point
	event->interaction_point = org::coach::tracing::api::STUB_IN_EXCEPTION;


	event->trail_label= CORBA::string_dup ("");
	event->message_id = CORBA::string_dup (message_data);
	event->thread_id = CORBA::string_dup ("");
	event->trail_id	= CORBA::string_dup (message_data);
	event->event_counter  = event_number;
	event->op_name = CORBA::string_dup (CORBA::string_dup(cci->request_info()->operation()));
	event->identity.object_instance_id		= CORBA::string_dup (cci->name());
	event->identity.object_repository_id	= CORBA::string_dup ("UNKNOWN");
	event->identity.cmp_name				= CORBA::string_dup (cci->component_id());
	event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
	event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
	event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
	event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
	event->identity.node_ip					= CORBA::string_dup (" e");
	event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

	event->parameters.length(0);

	org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
	trace->length(1);
	(*trace)[0] = event;
	context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());

}

void
ClientContainerInterceptor::receive_other (Components::ContainerPortableInterceptor::ContainerClientRequestInfo_ptr cci) {
	std::cout << "COPI: receive_user_exception: " << cci->request_info()->operation() << "for id:" << std::endl;
	if ( 0 == strcmp (cci->request_info()->operation(), "receiveEvent") )
	{
		/*
		 * Suppress PI handling for events to Trace server
		 */

		return;
	}

	char mess_cnt[11];
	unsigned long event_number = executor_ -> get_new_event_number();
	sprintf (mess_cnt, "__%08x", event_number);	

	IOP::ServiceContext* sc = 0;
	char *message_data;
	CORBA::Any_var any = new CORBA::Any;
	try {
		sc = cci->request_info()->get_reply_service_context(100);	
		
		CORBA::OctetSeq data;

		data.length(sc->context_data.length());
		memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
		any = executor_-> get_cdr_codec_ptr() -> decode_value(data, CORBA::_tc_string);


		any >>= message_data;
		
	} catch (CORBA::BAD_PARAM&)
	{
		//no service context for tracing
		message_data = new char[11];
		strcpy(message_data,mess_cnt);		
	} catch (...)
	{
		return;
	}
	std::cout << "@@@@@COPI after catch" << std::endl;
	org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

	// set time_stamp
	struct _timeb current_time;
	_ftime(&current_time);
	CORBA::LongLong tm = current_time.time;
	tm = tm * 1000 + current_time.millitm;
	event->time_stamp = tm;

	// set ineraction point
	event->interaction_point = org::coach::tracing::api::STUB_IN_EXCEPTION;


	event->trail_label= CORBA::string_dup ("");
	event->message_id = CORBA::string_dup (message_data);
	event->thread_id = CORBA::string_dup ("");
	event->trail_id	= CORBA::string_dup (message_data);
	event->event_counter  = event_number;
	event->op_name = CORBA::string_dup (CORBA::string_dup(cci->request_info()->operation()));
	event->identity.object_instance_id		= CORBA::string_dup (cci->name());
	event->identity.object_repository_id	= CORBA::string_dup ("UNKNOWN");
	event->identity.cmp_name				= CORBA::string_dup (cci->component_id());
	event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
	event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
	event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
	event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
	event->identity.node_ip					= CORBA::string_dup (" e");
	event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

	event->parameters.length(0);

	org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
	trace->length(1);
	(*trace)[0] = event;
	context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());

}

/*

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
*/

}; // namespace Qedo
