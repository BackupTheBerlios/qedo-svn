#include "ServerContainerInterceptor.h"

namespace Qedo {

ServerContainerInterceptor::ServerContainerInterceptor ()
{

}

ServerContainerInterceptor::~ServerContainerInterceptor ()
{
}

void
ServerContainerInterceptor::receive_request (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
	std::cout << "COPI: recieve_request: " << info->operation() << " for id: " << id << std::endl;
	// write something ino the current slot
		if (!strcmp(info->operation(), "say"))
		{
			std::cout << "it is not allowed to call say()" << std::endl;
			throw CORBA::UNKNOWN();
		}

}

void
ServerContainerInterceptor::send_reply (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
	std::cout << "COPI: send_reply: " << info->operation() << "for id: " << std::endl;

}

void
ServerContainerInterceptor::send_system_exception (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
	std::cout << "COPI: send_system_exception: " << info->operation() << "for id: " << std::endl;

}

void
ServerContainerInterceptor::send_user_exception (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id) {
	std::cout << "COPI: send_user_exception: " << info->operation() << "for id:" << std::endl;

}

void
ServerContainerInterceptor::rec_request_from_servant_locator(const char * operation)
{
	std::cout << "operation: " << operation << " from servant locator" << std::endl;
}

}; // namespace Qedo
