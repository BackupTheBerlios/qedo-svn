#include "ServerContainerInterceptor.h"

namespace Qedo {

ServerContainerInterceptor::ServerContainerInterceptor ()
{

}

ServerContainerInterceptor::~ServerContainerInterceptor ()
{
}

void
ServerContainerInterceptor::receive_request (::PortableInterceptor::ServerRequestInfo_ptr info)
{
	std::cout << "COPI: recieve_request" << std::endl;
	// write something ino the current slot

}

void
ServerContainerInterceptor::send_reply (::PortableInterceptor::ServerRequestInfo_ptr info)
{
	std::cout << "COPI: send_reply" << std::endl;

}

void
ServerContainerInterceptor::send_system_exception (::PortableInterceptor::ServerRequestInfo_ptr info)
{
	std::cout << "COPI: send_system_exception" << std::endl;

}

void
ServerContainerInterceptor::send_user_exception (::PortableInterceptor::ServerRequestInfo_ptr info) {
	std::cout << "COPI: send_user_exception" << std::endl;

}

void
ServerContainerInterceptor::rec_request_from_servant_locator()
{
	std::cout << "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" << std::endl;
}

}; // namespace Qedo
