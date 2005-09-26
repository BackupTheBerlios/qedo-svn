#include "ServerPEPInterceptor.h"
#include <CCMRequestInfoHolder.h>
#include <sys/timeb.h>
#ifdef WIN32
#include "winsock2.h"
#endif

namespace Qedo {

char* 
ServerPEPInterceptor::name () 
{
	return "anon";
	
};

void 
ServerPEPInterceptor::destroy() {


};

void 
ServerPEPInterceptor::set_slot_id(PortableInterceptor::SlotId slot_id) {
	slot_id_ = slot_id;

};

  ServerPEPInterceptor::ServerPEPInterceptor (openpmf_ccm::CCM_pep_manager_Context* context,openpmf_ccm::CCM_PEP_ManagerExec* executor,OpenPMF::CORBA::Platform *pf, OpenPMF::RTTreeElement *rt_policy   )
{
  std::cout << "ServerPEPInterceptor::ServerPEPInterceptor\n";
  context_ = context;
  executor_ = executor;
  pf_ = pf;
  rt_policy_ = rt_policy;
  assert(pf_);
  assert(rt_policy_);
}

ServerPEPInterceptor::~ServerPEPInterceptor ()
{
	std::cout << "!!!!!!destructor of ServerPEPInterceptor!!!!!!!!" << std::endl;

}

void
ServerPEPInterceptor::receive_request_service_contexts (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{

}

void
ServerPEPInterceptor::receive_request (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
	std::cout << "ServerPEPInterceptor:::receive_request " << " "
		  << csi->request_info()->target_most_derived_interface() << " "
		  << csi->component_id() << " "
		  << csi->request_info()->operation() << " "
		  << std::endl;

	CORBA::ORB_var orb = CORBA::ORB_instance("mico-local-orb", FALSE);
	OpenPMF::CCM::RequestInfoHolder* riref
	  = new OpenPMF::CCM::RequestInfoHolder(orb,csi );
	std::cout << "Got CSI\n";
	if (rt_policy_->evaluate(riref) == 0) {
	  std::cerr << "ServerPEPInterceptor: un-successful evaluation => throw CORBA::NO_PERMISSION" << std::endl;
	  mico_throw(CORBA::NO_PERMISSION());
	}

}

void
ServerPEPInterceptor::send_reply (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
	std::cout << "COPI: send_reply: " << csi->request_info()->operation();
	std::cout << " for id:" << csi->component_id() << std::endl;


}

void
ServerPEPInterceptor::send_exception (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
	std::cout << "COPI: send_exception: " << csi->request_info()->operation();
	std::cout << " for id:" << csi->component_id() << std::endl;


}

void
ServerPEPInterceptor::send_other (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) {
	std::cout << "COPI: send_other: " << csi->request_info()->operation();
	std::cout << " for id:" << csi->component_id() << std::endl;

}


}; // namespace Qedo

