#include "ServerPEPInterceptor.h"
#include <CCMRequestInfoHolder.h>
#include <sys/timeb.h>
#ifdef WIN32
#include "winsock2.h"
#endif

//#define DEBUG 1
#undef DEBUG

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

  ServerPEPInterceptor::ServerPEPInterceptor (openpmf_ccm::CCM_pep_manager_Context* context,openpmf_ccm::CCM_PEP_ManagerExec* executor, PMFIMPL::PolicyEnforcementPoint_impl* pep)
{
#ifdef DEBUG
  std::cout << "ServerPEPInterceptor::ServerPEPInterceptor\n";
#endif // DEBUG
  context_ = context;
  executor_ = executor;
  pep_ = pep;
  pmf_slot_set_ = false;
}

ServerPEPInterceptor::~ServerPEPInterceptor ()
{

}

void
ServerPEPInterceptor::receive_request_service_contexts (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{

}

void
ServerPEPInterceptor::receive_request (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
#ifdef DEBUG
    PortableInterceptor::ServerRequestInfo_var rinfo = csi->request_info();
    CORBA::String_var tmdi = rinfo->target_most_derived_interface();
    CORBA::String_var compid = csi->component_id();
    CORBA::String_var oper = rinfo->operation();
    std::cout << "ServerPEPInterceptor:::receive_request " << " "
              << tmdi.in() << " "
              << compid.in() << " "
              << oper.in() << " "
              << std::endl;
    std::cerr << ">>>>>>>>>>>>>>PMF slot ID: " << this->pmf_slot_id_ << std::endl;
#endif // DEBUG
	CORBA::ORB_var orb = CORBA::ORB_instance("mico-local-orb", FALSE);
        CORBA::Object_var obj = orb -> resolve_initial_references ("PICurrent");
        assert(!CORBA::is_nil(obj));
        CORBA::Long evaluate_policy = 0;
        if (this->pmf_slot_set_) {
            PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);
            CORBA::Any_var v = piCurrent->get_slot(this->pmf_slot_id_);
            v >>= evaluate_policy;
#ifdef DEBUG
            std::cout << "SPEPI: received in slot: " << evaluate_policy << std::endl;
        }
        else {
            std::cerr << "ERROR!!! SPEPI: pmf_slot_id_ NOT set!" << std::endl;
#endif // DEBUG
        }
	OpenPMF::CCM::RequestInfoHolderRef riref
	  = new OpenPMF::CCM::RequestInfoHolder(orb,csi );
#ifdef DEBUG
	std::cout << "Got CSI\n";
#endif // DEBUG
        if (evaluate_policy == 0) {
#ifdef DEBUG
            std::cerr << "SPEPI: going to evaluate policy..." << std::endl;
#endif // DEBUG
            pep_->evaluate(riref);
        }
#ifdef DEBUG
        else {
            std::cerr << "SPEPI: evaluator NOT CALLED" << std::endl;
        }
#endif // DEBUG
}

void
ServerPEPInterceptor::send_reply (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
#ifdef DEBUG
    PortableInterceptor::RequestInfo_var rinfo = csi->request_info();
    CORBA::String_var compid = csi->component_id();
    CORBA::String_var oper = rinfo->operation();
    std::cout << "COPI: send_reply: " << oper.in();
    std::cout << " for id:" << compid.in()<< std::endl;
#endif // DEBUG
}

void
ServerPEPInterceptor::send_exception (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
#ifdef DEBUG
    PortableInterceptor::RequestInfo_var rinfo = csi->request_info();
    CORBA::String_var compid = csi->component_id();
    CORBA::String_var oper = rinfo->operation();
    std::cout << "COPI: send_exception: " << oper.in();
    std::cout << " for id:" << compid.in()<< std::endl;
#endif // DEBUG
}

void
ServerPEPInterceptor::send_other (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi)
{
#ifdef DEBUG
    PortableInterceptor::RequestInfo_var rinfo = csi->request_info();
    CORBA::String_var compid = csi->component_id();
    CORBA::String_var oper = rinfo->operation();
    std::cout << "COPI: send_other: " << oper.in();
    std::cout << " for id:" << compid.in()<< std::endl;
#endif // DEBUG
}

void
ServerPEPInterceptor::set_pmf_slot_id(PortableInterceptor::SlotId id)
{
    pmf_slot_id_ = id;
    pmf_slot_set_ = true;
}
}; // namespace Qedo

