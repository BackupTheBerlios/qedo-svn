#include "ServerContainerInterceptor.h"

namespace Qedo {

EFServerContainerInterceptor::EFServerContainerInterceptor ()
{
count = 0;
}

EFServerContainerInterceptor::EFServerContainerInterceptor (long freq)
{
count = 1;
frequency_ = freq;
time(&stamp);
}

EFServerContainerInterceptor::~EFServerContainerInterceptor ()
{
}

void
EFServerContainerInterceptor::receive_request (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
	if(!strcmp(info->operation(), "push_event"))
	{
		time_t temp_stamp;
		time (&temp_stamp);
		if ((temp_stamp-stamp) < frequency_)
		{
	//		std::cout << "!!!EVENT BLOCKED!!!" << count << " " << frequency_ << std::endl;
			throw CORBA::UNKNOWN();

		} else
		{
	//		std::cout << "!!!Event delivered!!!" << std::endl;
			time(&stamp);
		}
	}
}

void
EFServerContainerInterceptor::send_reply (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
//	std::cout << "COPI: send_reply: " << info->operation() << "for id: " << std::endl;

}

void
EFServerContainerInterceptor::send_system_exception (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id)
{
//	std::cout << "COPI: send_system_exception: " << info->operation() << "for id: " << std::endl;

}

void
EFServerContainerInterceptor::send_user_exception (::PortableInterceptor::ServerRequestInfo_ptr info, const char* id) {
//	std::cout << "COPI: send_user_exception: " << info->operation() << "for id:" << std::endl;

}

void
EFServerContainerInterceptor::rec_request_from_servant_locator(const char * operation)
{
//	std::cout << "operation: " << operation << " from servant locator" << std::endl;
}

}; // namespace Qedo
