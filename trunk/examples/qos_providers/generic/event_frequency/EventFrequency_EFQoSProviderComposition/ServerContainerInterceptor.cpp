#include "ServerContainerInterceptor.h"

namespace Qedo {

ServerContainerInterceptor::ServerContainerInterceptor ()
{
count = 0;
}

ServerContainerInterceptor::~ServerContainerInterceptor ()
{
}

void
ServerContainerInterceptor::receive_request (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
	throw CORBA::UNKNOWN();
	if (count++ < 10)
	{
		std::cout << "!!!EVENT BLOCKED!!!" << std::endl;

	} else
	{
		std::cout << "!!!Event delivered!!!" << std::endl;
		count = 0;
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
