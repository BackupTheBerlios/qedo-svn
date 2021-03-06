#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"
#include "fstream"

namespace Qedo {

	class ContainerInterceptor : public virtual Components::Extension::ContainerInterceptor,
                                 public virtual RefCountLocalObject
	{
	private:
		std::ofstream log_file;
	public:
		ContainerInterceptor();

		~ContainerInterceptor();

		virtual void get_message(const char* mess);

	};

} // Qedo