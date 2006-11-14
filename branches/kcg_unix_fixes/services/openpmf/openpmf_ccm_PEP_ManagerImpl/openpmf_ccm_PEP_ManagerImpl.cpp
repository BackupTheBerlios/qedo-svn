//
// generated by Qedo
//

#include "openpmf_ccm_PEP_ManagerImpl.h"


// BEGIN USER INSERT SECTION file
#include "ServerPEPInterceptor.h"
#include <SL3_Transformer.h>
#include <CCM_Transformer.h>
#include <pep_impl.h>
#ifdef _WIN32
#include <winsock.h>
#endif // _WIN32

#ifndef _WIN32
extern PortableInterceptor::SlotId global_pmf_slot_id;
#else // _WIN32
extern PortableInterceptor::SlotId
get_global_pmf_slot_id();
#endif // _WIN32


using namespace PMFIMPL;
using namespace OpenPMF;
using namespace PortableServer;
using namespace CORBA;


#undef DEBUG
// END USER INSERT SECTION file


namespace openpmf_ccm {


// BEGIN USER INSERT SECTION PEP_ManagerExec
// END USER INSERT SECTION PEP_ManagerExec


PEP_ManagerExec::PEP_ManagerExec()
{
// BEGIN USER INSERT SECTION PEP_ManagerExec::PEP_ManagerExec
#ifdef DEBUG
  std::cout << "PEP_ManagerExec::PEP_ManagerExec()\n";
#endif // DEBUG
// END USER INSERT SECTION PEP_ManagerExec::PEP_ManagerExec
}


PEP_ManagerExec::~PEP_ManagerExec()
{
// BEGIN USER INSERT SECTION PEP_ManagerExec::~PEP_ManagerExec
    Components::ContainerPortableInterceptor::ServerContainerInterceptorRegistration_ptr server_reg =
        context_->get_server_interceptor_dispatcher_registration();
    server_reg->unregister_server_interceptor(server_cookie_);
// END USER INSERT SECTION PEP_ManagerExec::~PEP_ManagerExec

}


void
PEP_ManagerExec::set_context(::openpmf_ccm::CCM_pep_manager_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::openpmf_ccm::CCM_pep_manager_ContextImpl::_duplicate(context);
}


void
PEP_ManagerExec::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION PEP_ManagerExec::configuration_complete
#ifdef DEBUG
  std::cout << "PEP_ManagerExec::configuration_complete " 
	    << policy_name_ 
	    << std::endl;
#endif // DEBUG

  PMFCORBA::PlatformRef pf = new PMFCORBA::Platform;

  pf->add_transformer("client.name", new PMFCORBA_SL3::TLSIdentityTransformer
                             (NULL, new PMFCORBA_SL3::ClientTransformer));
  pf->add_transformer("initiator.name", new PMFCORBA_SL3::InitiatorTransformer);
  pf->add_transformer("target.name", new OpenPMF::CCM::TargetTransformer(NULL, NULL));
  pf->add_transformer("operation.name", new OpenPMF::CCM::OperationTransformer(NULL, NULL));
  pf->add_transformer("target.type", new OpenPMF::CCM::TypeTransformer(NULL, NULL));

#ifdef DEBUG
  std::cout << "Transformer OK"
    	    << policy_name_ 
	    << std::endl;
#endif // DEBUG
  
  ORB_var orb = ORB_instance("mico-local-orb", FALSE);
  CORBA::PolicyList pl(0);
  char hostname[200];
  int ret = gethostname(hostname, 200);
  assert(ret == 0);
  std::string host = CORBA::string_dup(hostname);
  AbstractPolicyEnforcementPoint* pep = PEPFactory::create_PEP
      (orb, pl, pf, "<unspecified>", "CCM",
       host, this->policy_name_);

  //  server_interceptor_ = new Qedo::ServerPEPInterceptor(pf_, rt_policy_);

  //  server_reg->register_interceptor_for_all(server_interceptor_);
#ifdef DEBUG
  std::cout << "PEP_ManagerExec::configuration_complete COPI init OK\n";
#endif // DEBUG



  Components::ContainerPortableInterceptor::ServerContainerInterceptorRegistration_ptr server_reg =
    context_->get_server_interceptor_dispatcher_registration();
  server_pep_interceptor_ = new Qedo::ServerPEPInterceptor(context_,this, pep);
#ifndef _WIN32
  server_pep_interceptor_->set_pmf_slot_id(global_pmf_slot_id);
#else // _WIN32
  server_pep_interceptor_->set_pmf_slot_id(get_global_pmf_slot_id());
#endif // _WIN32
  server_cookie_ = server_reg->register_server_interceptor(server_pep_interceptor_);
  




// END USER INSERT SECTION PEP_ManagerExec::configuration_complete
}


void
PEP_ManagerExec::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PEP_ManagerExec::remove
// END USER INSERT SECTION PEP_ManagerExec::remove
}


void
PEP_ManagerExec::policy_name(const char* param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PEP_ManagerExec::_policy_name
#ifdef DEBUG
  std::cout << "PEP_ManagerExec::policy_name= " << param << std::endl;
#endif // DEBUG
  policy_name_ = param;
// END USER INSERT SECTION PEP_ManagerExec::_policy_name
}


char*
PEP_ManagerExec::policy_name()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PEP_ManagerExec::policy_name
    return CORBA::string_dup(this->policy_name_.c_str());
// END USER INSERT SECTION PEP_ManagerExec::policy_name
}


// BEGIN USER INSERT SECTION PEP_ManagerImpl
// END USER INSERT SECTION PEP_ManagerImpl


PEP_ManagerImpl::PEP_ManagerImpl()
:component_(new PEP_ManagerExec())
{
// BEGIN USER INSERT SECTION PEP_ManagerImpl::PEP_ManagerImpl
#ifdef DEBUG
  std::cout << "PEP_ManagerImpl::PEP_ManagerImpl\n";
#endif // DEBUG

// END USER INSERT SECTION PEP_ManagerImpl::PEP_ManagerImpl
}


PEP_ManagerImpl::~PEP_ManagerImpl()
{
// BEGIN USER INSERT SECTION PEP_ManagerImpl::~PEP_ManagerImpl
// END USER INSERT SECTION PEP_ManagerImpl::~PEP_ManagerImpl

    component_->_remove_ref();
}


::CORBA::Object*
PEP_ManagerImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
PEP_ManagerImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
PEP_ManagerImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION PEP_ManagerImpl::configuration_complete
#ifdef DEBUG
    std::cout << "PEP_ManagerImpl::configuration_complete "
      //	      << policy_name 
	      << std::cout;
#endif // DEBUG
// END USER INSERT SECTION PEP_ManagerImpl::configuration_complete
}


void
PEP_ManagerImpl::set_extension_context(::Components::ExtensionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::openpmf_ccm::CCM_pep_manager_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::openpmf_ccm::CCM_pep_manager_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::openpmf_ccm::CCM_pep_manager_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::openpmf_ccm::CCM_pep_manager_ContextImpl::_nil();
        
    #else
    context_ = ::openpmf_ccm::CCM_pep_manager_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
PEP_ManagerImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PEP_ManagerImpl::ccm_activate
// END USER INSERT SECTION PEP_ManagerImpl::ccm_activate
}


void
PEP_ManagerImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PEP_ManagerImpl::ccm_passivate
// END USER INSERT SECTION PEP_ManagerImpl::ccm_passivate
}


void
PEP_ManagerImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PEP_ManagerImpl::ccm_remove
// END USER INSERT SECTION PEP_ManagerImpl::ccm_remove
}


// BEGIN USER INSERT SECTION HomePEP_ManagerExec
// END USER INSERT SECTION HomePEP_ManagerExec


HomePEP_ManagerExec::HomePEP_ManagerExec()
{
// BEGIN USER INSERT SECTION HomePEP_ManagerExec::HomePEP_ManagerExec
// END USER INSERT SECTION HomePEP_ManagerExec::HomePEP_ManagerExec
}


HomePEP_ManagerExec::~HomePEP_ManagerExec()
{
// BEGIN USER INSERT SECTION HomePEP_ManagerExec::~HomePEP_ManagerExec
// END USER INSERT SECTION HomePEP_ManagerExec::~HomePEP_ManagerExec

}


void
HomePEP_ManagerExec::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
HomePEP_ManagerExec::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION HomePEP_ManagerExec::create
// END USER INSERT SECTION HomePEP_ManagerExec::create
    return new PEP_ManagerImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_pep_manager_homeE(void)
{
// BEGIN USER INSERT SECTION create_pep_manager_home
// END USER INSERT SECTION create_pep_manager_home

    return new ::openpmf_ccm::HomePEP_ManagerExec();
}

