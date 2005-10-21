#ifndef __SERVERPEPCOPI_H__
#define __SERVERPEPCOPI_H__

#include "CORBA.h"
#include "Components_skel.h"
#include "RefCountBase.h"
#include "openpmf_ccm_PEP_ManagerImpl_LOCAL.h"
#include <Attribute.h>
#include <Transformer.h>
#include <RTTreeElement.h>
#define MICO_CONF_INTERCEPT
#include <PMFRepository.h>
#include <Platform.h>



namespace Qedo {
	class ServerPEPInterceptor;
}
#include "openpmf_ccm_PEP_ManagerImpl.h"


namespace Qedo {

  class ServerPEPInterceptor: public virtual Components::ContainerPortableInterceptor::ServerContainerInterceptor	{
  private:

    openpmf_ccm::CCM_pep_manager_Context *context_;
    std::string hostname_;
    std::string process_id_;
    PortableInterceptor::SlotId slot_id_;
    openpmf_ccm::CCM_PEP_ManagerExec* executor_;

    std::string name_;
    std::string policy_name_;
    OpenPMF::RTTreeElementRef rt_policy_;
    OpenPMF::CORBA::PlatformRef pf_;

    PortableInterceptor::SlotId pmf_slot_id_;
    bool pmf_slot_set_;
  public:
    ServerPEPInterceptor(openpmf_ccm::CCM_pep_manager_Context *context,openpmf_ccm::CCM_PEP_ManagerExec *executor,OpenPMF::CORBA::Platform *pf, OpenPMF::RTTreeElement *rt_policy  );
    
    ~ServerPEPInterceptor();
    
    virtual char* 
      name() ;
    
    virtual void 
      destroy();
    
    virtual void 
      set_slot_id(PortableInterceptor::SlotId slot_id);
    
    virtual void 
      receive_request_service_contexts (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
    
    virtual void 
      receive_request (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
    
    virtual void 
      send_reply (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
    
    virtual void 
      send_exception (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
    
    virtual void 
      send_other (Components::ContainerPortableInterceptor::ContainerServerRequestInfo_ptr csi) ;
    
    virtual void
    set_pmf_slot_id(PortableInterceptor::SlotId id);
	};
}; // namespace Qedo

#endif
