#include "ContainerInterceptor.h"

namespace Qedo {

	ContainerInterceptor::ContainerInterceptor()
	{

	}

	ContainerInterceptor::~ContainerInterceptor()
	{
	}

	void ContainerInterceptor::get_message(const char* mess) 
	{
		std::cout << "!!!! got message !!!" << mess << std::endl;

	}
} // Qedo