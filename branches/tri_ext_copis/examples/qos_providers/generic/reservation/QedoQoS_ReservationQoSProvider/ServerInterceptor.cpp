#include "ServerInterceptor.h"
#include <sys/timeb.h>
#include "valuetypes.h"


namespace QedoQoS_Reservation {

void 
ServerContainerInterceptor::set_slot_id(PortableInterceptor::SlotId slot_id) {
	slot_id_ = slot_id;

};

ServerContainerInterceptor::ServerContainerInterceptor (QedoQoS::CCM_Reservation_ContextImpl* context, QedoQoS::ReservationQoSproviderImpl* executor)
{
	executor_ = executor;
	context_ = context;
	number_of_calls = 0;
	_time64( &time_stamp);

}

ServerContainerInterceptor::~ServerContainerInterceptor ()
{
//	std::cout << "!!!!!!destructor of ServerContainerInterceptor!!!!!!!!" << std::endl;

}

void
ServerContainerInterceptor::register_requirement(char * req_component_id, char * req_operation_name, Components::ConfigValues* req)
{
	std::cout << "WWWWWWWWW" << std::endl;
	// store information
	comp_origin_id = strdup(req_component_id);
	operation_id = strdup(req_operation_name);
	data = req;

}

void 
ServerContainerInterceptor::add_contract(const char *component_id, Components::ConfigValues val)
{
	std::cout << "RRRR" << std::endl;
	// store information
	server_origin= strdup(component_id);
	server_operation = "compute";
	server_data = &val;
	// extract values;
	CORBA::ULong server_data_len = server_data ->length();
	for (server_data_len = 0; server_data_len < server_data->length(); server_data_len++)
	{
		// search for dimension
		if ( !strcmp((*server_data)[server_data_len]->name(), "dimension"))
		{
			Components::ConfigValues *dim_content;
			CORBA::Any dim_any;
			dim_any=((*server_data)[server_data_len]-> value());
			dim_any >>= dim_content ;
//			CORBA::ULong dim_len;
//			for (dim_len = 0; dim_len < dim_content->length(); dim_len++)
//			{
	//				std::cout << "XXXX: " << ((*dim_content)[dim_len] -> name()) << std::endl;
	//			if (!strcmp((*dim_content)[dim_len] -> name(),"name")
	//			{
			char* dim_name;
			CORBA::Any dim_name_any;
			dim_name_any = ((*dim_content)[0] -> value());
			dim_name_any >>= dim_name;
			std::cout << "found dim: " << dim_name << std::endl;
			if (!strcmp(dim_name,"calls"))
			{
				// take val
				char* dim_val;
				CORBA::Any dim_val_any;
				dim_val_any = ((*dim_content)[4] -> value());
				dim_val_any >>= dim_val;
				std::cout << "found dim val: " << dim_val << std::endl;
				// transform to long
				number_of_calls_ = atol( dim_val); 
			}
			if (!strcmp(dim_name,"interval"))
			{
				// take val
				char* dim_val;
				CORBA::Any dim_val_any;
				dim_val_any = ((*dim_content)[4] -> value());
				dim_val_any >>= dim_val;
				std::cout << "found dim val: " << dim_val << std::endl;
				// transform to long
				intervall_ = atol( dim_val);
			}

//			} // end dimension fo
			
		} // end if dimension

	// calls
	}
	//data -> _add_ref();
	
}


void
ServerContainerInterceptor::receive_request (Components::Extension::ContainerServerRequestInfo_ptr info)
{
//	std::cout << "ServerCOPI: receive_request: " << info->request_info()->operation() << "for id: " << info -> component_id() << std::endl;


		/* 
		 * Get encoded context information
		 */
	
/*	 
		IOP::ServiceContext_var sc = 0;
		char *message_data;
		CORBA::Any_var any = new CORBA::Any;

		try {
			sc = info->request_info()->get_request_service_context(100);	
			
		    CORBA::OctetSeq data;

			data.length(sc->context_data.length());
			memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
			any = executor_-> get_cdr_codec_ptr() -> decode_value(data, CORBA::_tc_string);


			any >>= message_data;
			
		} catch (CORBA::BAD_PARAM&)
		{
			//no service context for tracing
		} catch (...)
		{
			return;
		}
*/		
}

void
ServerContainerInterceptor::send_reply (Components::Extension::ContainerServerRequestInfo_ptr info)
{
//	std::cout << "ServerCOPI: send_reply: " << info->request_info()->operation() << "for id: " << info -> component_id() << std::endl;

/*
	CORBA::Any out_any;
	out_any <<= messageid.c_str();
	CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(out_any);

	IOP::ServiceContext out_sc;

	out_sc.context_id = 100;

	out_sc.context_data.length(data->length());

	memcpy(out_sc.context_data.get_buffer(), data->get_buffer(), data->length());

	info->request_info()->add_reply_service_context(out_sc, true);
*/

}

void
ServerContainerInterceptor::send_system_exception (Components::Extension::ContainerServerRequestInfo_ptr info)
{
//	std::cout << "ServerCOPI: send_system_exception: " << info->request_info()->operation() << "for id: " << std::endl;


	/*
	CORBA::Any out_any;
	out_any <<= messageid.c_str();k
	CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(out_any);

	IOP::ServiceContext out_sc;

	out_sc.context_id = 100;

	out_sc.context_data.length(data->length());

	memcpy(out_sc.context_data.get_buffer(), data->get_buffer(), data->length());

	info->request_info()->add_reply_service_context(out_sc, true);
*/

}

void
ServerContainerInterceptor::send_user_exception (Components::Extension::ContainerServerRequestInfo_ptr info) {

}

void 
ServerContainerInterceptor::call( const char* comp_id, const char* origin, const char* operation, CORBA::Boolean_out con ) 
{
	// test implementaiton
	// set time_stamp
	con = true;
//	if (!strcmp(operation,"compute"/*server_operation.c_str()*/))
	if (!server_operation.compare(operation))
	{

		__time64_t current_time;
		_time64( &current_time);
		if ((current_time - time_stamp) > intervall_)
		{
			// reset time-stamp
			_time64( &time_stamp);

			// reset counter
			number_of_calls = 0;
		}

		con = true;
		if (number_of_calls < number_of_calls_)
		{
			//client has not used all of its reservations
			//if (strcmp(origin,"client"))
			if(server_origin.compare(origin))
			{
				con = false;
				return;
			} else
			{
				number_of_calls++;
				con = true;
			}
		}
	}
}

void
ServerContainerInterceptor::rec_request_from_servant_locator(const char * operation)
{
//	std::cout << "operation: " << operation << " from servant locator" << std::endl;
}

Components::Cookie* 
ServerContainerInterceptor::connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) 
{
	std::cout << "QQQQQQQQQQ COPI Server: connect called" << std::endl;

		con = true;
	// get the id from the contract data
	if (!strcmp(comp_id, comp_origin_id.c_str()))
	{
		CORBA::Object_var temp_obj = connection -> _get_component();
		Components::CCMObject_var temp_comp = Components::CCMObject::_narrow(temp_obj);
		CORBA::Object_var nego_obj = temp_comp -> provide_facet("_qos_negotiation_external");
		Components::Extension::Negotiation_var nego = Components::Extension::Negotiation::_narrow(nego_obj);
		
		std::cout << "req_offer" << std::endl;
		
		//create a ContractDescription from contract Data

		CORBA::Any an_any;
		CORBA::ULong freq = 5;
		an_any <<= freq;

		Components::Extension::ContractDescription requirements;
		requirements.dimensions.length(2);

		requirements.contract_type = CORBA::string_dup("Reservation");

		// start with 1 because the first one is the already checked name= Reservation

		Components::ConfigValues dims;
		CORBA::Any content_any;
		//(data->value()) >>= content_any;
		//content_any = (data->value());
		//content_any >>= dims;
		requirements.dimensions[0] = 
			(*data)[1];
		requirements.dimensions[1] = (*data)[2];

		Components::Extension::ContractDescription *offer = nego -> req_offer(requirements, comp_id);
		std::cout << "got answer" << std::endl;
		// check offer

		// does it fit the needs

		// accept
		if (nego -> accept(*offer, comp_id))
		{
			// store information
			
//			std::cout << "contract established" << std::endl;
		}
	}	

		return 0;
}


CORBA::Object_ptr 
ServerContainerInterceptor::provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con )
{
//	std::cout << "COPI Server: provide_facet" << std::endl;
	if (!strcmp(name, "_qos_negotiation_external"))
	{
		//provide the negotiation interface
		//Components::Negotiation_ptr nego = executor_ -> get_nego_interface();
		con = false;
		Components::CCMObject_var aComponent = Components::CCMObject::_narrow( context_ -> get_CCM_object());
		return aComponent -> provide_facet( "nego_external" );
		
	} else
	{
		con = true;
		return CORBA::Object::_nil();
	}
}



Components::Cookie* 
ServerContainerInterceptor::bind( const char* comp_id, char*& name, ::StreamComponents::SinkStreamPort_ptr& the_sink, char*& transport_profile, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Server: bind called" << std::endl;
	return 0;
}

::StreamComponents::SinkStreamPort_ptr 
ServerContainerInterceptor::unbind( const char* comp_id, char*& name, Components::Cookie*& ck, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Server: unbind called" << std::endl;
	return 0;
}

CORBA::Object_ptr 
ServerContainerInterceptor::provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) 
{
//	std::cout << "COPI Server: provided_sink_stream_port called" << std::endl;
	return 0;
}


/*

Components::Cookie_ptr
ServerContainerInterceptor::bind(const char* comp_id, const char* name, CORBA::Object_ptr the_sink,
						   const char* transport_profile, CORBA::Boolean_out con)
{
	con = false;
	std::cout << "@@@got bind" << comp_id << std::endl;
//	StreamComponents::SinkStreamPort_var port = StreamComponents::SinkStreamPort::_narrow(the_sink);
	CORBA::Object_var anObject = the_sink->_get_component();
	StreamComponents::StreamCCMObject_var anComponent = StreamComponents::StreamCCMObject::_narrow(anObject);
	CORBA::Object_var anotherObject = anComponent->provide_facet ("_qos_negotiation_external");

	
	Components::Extension::Negotiation_var nego = Components::Extension::Negotiation::_narrow(anotherObject);

	//extracted from contract_data
	Components::Extension::ContractDescription req;
	std::cout << "@@@@ " << nego->req_offer(req) << std::endl;

//	Components::Cookie_ptr temp_ck = filter -> bind(name, StreamComponents::SinkStreamPort::_narrow(the_sink), transport_profile);
//	return temp_ck;

	return 0;
}

CORBA::Object_ptr 
ServerContainerInterceptor::provide_sink_stream_port( const char* comp_id, const char* name, CORBA::Boolean_out con )
{
	std::cout << "@@@got provide_stream_sink_port" << comp_id << std::endl;

	CORBA::Object_var anObject;
	con = true;
	return anObject;
}
*/
}; // namespace Qedo

