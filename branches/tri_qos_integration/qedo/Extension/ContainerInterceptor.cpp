#include "ContainerInterceptor.h"

namespace Qedo {

	ContainerInterceptor::ContainerInterceptor()
	{
		log_file.open("log_file.txt");		
	}

	ContainerInterceptor::~ContainerInterceptor()
	{
	}

	void ContainerInterceptor::get_message(const char* mess) 
	{
		log_file << "!!!! got message !!!" << mess << std::endl;

	}
} // Qedo