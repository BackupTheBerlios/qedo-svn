//
// generated by Qedo
//

#include "dinner_CutleryImpl.h"


// BEGIN USER INSERT SECTION file
#include <iostream>
#include "Valuetypes.h"

using namespace std;
// END USER INSERT SECTION file


namespace dinner {


// BEGIN USER INSERT SECTION CutlerySessionImpl
// END USER INSERT SECTION CutlerySessionImpl


CutlerySessionImpl::CutlerySessionImpl()
{
// BEGIN USER INSERT SECTION CutlerySessionImpl::CutlerySessionImpl
// END USER INSERT SECTION CutlerySessionImpl::CutlerySessionImpl
}


CutlerySessionImpl::~CutlerySessionImpl()
{
// BEGIN USER INSERT SECTION CutlerySessionImpl::~CutlerySessionImpl
	cout << "CutlerySessionImpl: Destructor called" << endl;
// END USER INSERT SECTION CutlerySessionImpl::~CutlerySessionImpl

}


void
CutlerySessionImpl::set_context(::dinner::CCM_Cutlery_Context_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::dinner::CCM_Cutlery_Context::_duplicate(context);
}


void
CutlerySessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION CutlerySessionImpl::configuration_complete
// END USER INSERT SECTION CutlerySessionImpl::configuration_complete
}


void
CutlerySessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CutlerySessionImpl::remove
// END USER INSERT SECTION CutlerySessionImpl::remove
}


void
CutlerySessionImpl::name(const char* param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CutlerySessionImpl::_name
	id_ = param;
// END USER INSERT SECTION CutlerySessionImpl::_name
}


char*
CutlerySessionImpl::name()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CutlerySessionImpl::name
	return CORBA::string_dup (id_.c_str());
// END USER INSERT SECTION CutlerySessionImpl::name
}


// BEGIN USER INSERT SECTION Seg
// END USER INSERT SECTION Seg


Seg::Seg()
{
// BEGIN USER INSERT SECTION Seg::Seg
	in_use_ = false;
// END USER INSERT SECTION Seg::Seg
}


Seg::~Seg()
{
// BEGIN USER INSERT SECTION Seg::~Seg
	cout << "Seg: Destructor called" << endl;
// END USER INSERT SECTION Seg::~Seg

}


void
Seg::set_context(::dinner::CCM_Cutlery_Context_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::dinner::CCM_Cutlery_Context::_duplicate(context);
}


void
Seg::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION Seg::configuration_complete
// END USER INSERT SECTION Seg::configuration_complete
}


Components::Cookie*
Seg::obtain_fork()
	throw(CORBA::SystemException, ::dinner::ForkNotAvailable)
{
// BEGIN USER INSERT SECTION Seg::obtain_fork
	cout << ".....obtain_fork called" << endl;

	if (in_use_)
	{
		cout << ".....fork already used" << endl;
		throw dinner::ForkNotAvailable();
	}

	cout << ".....fork now used" << endl;
	in_use_ = true;
	
	// Normally we should store a cookie somewhere to check later, whether the caller
	// is allowed to relase the fork
	return new Cookie_impl();
// END USER INSERT SECTION Seg::obtain_fork
}


void
Seg::release_fork(Components::Cookie* ck)
	throw(CORBA::SystemException, ::dinner::NotTheEater)
{
// BEGIN USER INSERT SECTION Seg::release_fork
	// We should first check the cookie ;-)
	in_use_ = false;
// END USER INSERT SECTION Seg::release_fork
}


// BEGIN USER INSERT SECTION CutleryImpl
// END USER INSERT SECTION CutleryImpl


CutleryImpl::CutleryImpl()
:component_(new CutlerySessionImpl())
, Seg_(new Seg())
{
// BEGIN USER INSERT SECTION CutleryImpl::CutleryImpl
// END USER INSERT SECTION CutleryImpl::CutleryImpl
}


CutleryImpl::~CutleryImpl()
{
// BEGIN USER INSERT SECTION CutleryImpl::~CutleryImpl
	cout << "CutleryImpl: Destructor called" << endl;
// END USER INSERT SECTION CutleryImpl::~CutleryImpl

    component_->_remove_ref();
    Seg_->_remove_ref();
}


::CORBA::Object*
CutleryImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "the_fork")) {
        return Components::EnterpriseComponent::_duplicate (Seg_);
    }
    
    else if (! strcmp (name, "the_name")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
CutleryImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
CutleryImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();
    Seg_->configuration_complete();

// BEGIN USER INSERT SECTION CutleryImpl::configuration_complete
// END USER INSERT SECTION CutleryImpl::configuration_complete
}


void
CutleryImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::dinner::CCM_Cutlery_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::dinner::CCM_Cutlery_Context*>(context);
    
    if (tmp_context)
        context_ = ::dinner::CCM_Cutlery_Context::_duplicate(tmp_context);
    else
        context_ = ::dinner::CCM_Cutlery_Context::_nil();
        
    #else
    context_ = ::dinner::CCM_Cutlery_Context::_narrow(context);
    
    #endif
    component_->set_context(context_);
    Seg_->set_context(context_);
}


void
CutleryImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CutleryImpl::ccm_activate
	cout << "CutleryImpl: ccm_activate() called" << endl;
// END USER INSERT SECTION CutleryImpl::ccm_activate
}


void
CutleryImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CutleryImpl::ccm_passivate
	cout << "CutleryImpl: ccm_passivate() called" << endl;
// END USER INSERT SECTION CutleryImpl::ccm_passivate
}


void
CutleryImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CutleryImpl::ccm_remove
	cout << "CutleryImpl: ccm_remove() called" << endl;
// END USER INSERT SECTION CutleryImpl::ccm_remove
}


// BEGIN USER INSERT SECTION CutleryHomeImpl
// END USER INSERT SECTION CutleryHomeImpl


CutleryHomeImpl::CutleryHomeImpl()
{
// BEGIN USER INSERT SECTION CutleryHomeImpl::CutleryHomeImpl
// END USER INSERT SECTION CutleryHomeImpl::CutleryHomeImpl
}


CutleryHomeImpl::~CutleryHomeImpl()
{
// BEGIN USER INSERT SECTION CutleryHomeImpl::~CutleryHomeImpl
	cout << "CutleryHomeImpl: Destructor called" << endl;

	int dummy = 0;
	CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);

    orb->unregister_value_factory ("IDL:omg.org/Components/Cookie:1.0");
// END USER INSERT SECTION CutleryHomeImpl::~CutleryHomeImpl

}


void
CutleryHomeImpl::set_context(Components::CCMContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::CCMContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
CutleryHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION CutleryHomeImpl::create
	cout << "CutleryHomeImpl: create() called" << endl;
// END USER INSERT SECTION CutleryHomeImpl::create
    return new CutleryImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_CutleryHomeE(void)
{
// BEGIN USER INSERT SECTION create_CutleryHome
// END USER INSERT SECTION create_CutleryHome

    return new ::dinner::CutleryHomeImpl();
}

