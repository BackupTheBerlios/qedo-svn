//
// generated by Qedo
//

#include "dinner_ObserverImpl.h"


// BEGIN USER INSERT SECTION file
#include "PhilosopherState.h"

#ifndef WIN32
static GUI gui;
#endif
// END USER INSERT SECTION file


namespace dinner {


// BEGIN USER INSERT SECTION ObserverSessionImpl
#ifdef OBSERVER_WITH_GUI
void
ObserverSessionImpl::run()
{
#ifdef WIN32
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	
	gui_ = new ObserverGUI ();
#endif

	running_ = true;

	MSG msg;
	BOOL bRet;

	while (running_ && ( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)) { 
		if (bRet == -1) {
			WITH_PID_ERR( "Error from GetMessage()" );
			break;
		}
		else {
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

#ifdef WIN32
	if(gui_) delete gui_;
#endif
}


void
ObserverSessionImpl::finish()
{
	JTCThreadHandle t = this;
	running_ = false;

#ifdef WIN32
	gui_ -> InvalidateRect(0);
#endif

	do {
		try {
			DEBUG_WITH_PID_OUT ( "try join" );
			t->join();
		}
		catch(const JTCInterruptedException&) {
		}
	} while( t->isAlive());
	DEBUG_WITH_PID_OUT ( "done" );
}

#endif
// END USER INSERT SECTION ObserverSessionImpl


ObserverSessionImpl::ObserverSessionImpl()
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::ObserverSessionImpl
    running_ = false;
#ifdef OBSERVER_WITH_GUI
	start ();
#endif
// END USER INSERT SECTION ObserverSessionImpl::ObserverSessionImpl
}


ObserverSessionImpl::~ObserverSessionImpl()
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::~ObserverSessionImpl
// END USER INSERT SECTION ObserverSessionImpl::~ObserverSessionImpl

}


void
ObserverSessionImpl::set_context(::DiningPhilosophers::CCM_Observer_Context_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::DiningPhilosophers::CCM_Observer_Context::_duplicate(context);
}


void
ObserverSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::configuration_complete
// END USER INSERT SECTION ObserverSessionImpl::configuration_complete
}


void
ObserverSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::remove
#ifdef OBSERVER_WITH_GUI
	finish ();
#endif
// END USER INSERT SECTION ObserverSessionImpl::remove
}


void
ObserverSessionImpl::push_event (Components::EventBase* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::push_event
    ::DiningPhilosophers::StatusInfo* e = ::DiningPhilosophers::StatusInfo::_downcast(ev);
    if(!e) {
        WITH_PID_ERR ( "ObserverSessionImpl: Cannot push event in push_event()" );
    }
    push_StatusInfo(e);
// END USER INSERT SECTION ObserverSessionImpl::push_event
}


void
ObserverSessionImpl::push_StatusInfo(::DiningPhilosophers::StatusInfo* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ObserverSessionImpl::push_StatusInfo
   std::stringstream message;
    message << ev->name();

	switch (ev->state())
	{
	case DiningPhilosophers::EATING:
		message << " is eating for " << ev->ticks_since_last_meal() << " ticks";
        message << "; left fork(" << ev->has_left_fork() << "), right fork(" << ev->has_right_fork() << ");";
		break;
	case DiningPhilosophers::THINKING:
		message << " is thinking for " << ev->ticks_since_last_meal() << " ticks";
        message << "; left fork(" << ev->has_left_fork() << "), right fork(" << ev->has_right_fork() << ");";
		break;
	case DiningPhilosophers::HUNGRY:
		message << " is hungry for " << (ev->ticks_since_last_meal() - 3) << " ticks";
        message << "; left fork(" << ev->has_left_fork() << "), right fork(" << ev->has_right_fork() << ");";
		break;
	case DiningPhilosophers::STARVING:
		message << " is starving for " << (ev->ticks_since_last_meal() - 10) << " ticks";
        message << "; left fork(" << ev->has_left_fork() << "), right fork(" << ev->has_right_fork() << ");";
		break;
	case DiningPhilosophers::DEAD:
		message << " is dead";
        message << "; left fork(" << ev->has_left_fork() << "), right fork(" << ev->has_right_fork() << ");";
		break;
	}

    string philoName = ev->name();
    vector < string > ::const_iterator iter;
    int index = 0;
	for (iter = philoNames_.begin(); iter != philoNames_.end(); iter++ )
	{
		if ((*iter) == philoName)
		{
			break;
		}
        index++;
	}
    if (index == philoNames_.size())
    {
        philoNames_.push_back(philoName);
    }

#ifdef WIN32
	gui_->m_list.DeleteString(index);
    gui_->m_list.InsertString(index, message.str().c_str());
	gui_->m_list.SetCurSel(index);
#endif

// END USER INSERT SECTION ObserverSessionImpl::push_StatusInfo
}


// BEGIN USER INSERT SECTION ObserverImpl
// END USER INSERT SECTION ObserverImpl


ObserverImpl::ObserverImpl()
:component_(new ObserverSessionImpl())
{
// BEGIN USER INSERT SECTION ObserverImpl::ObserverImpl
    component_executor_ = 0;
// END USER INSERT SECTION ObserverImpl::ObserverImpl
}


ObserverImpl::~ObserverImpl()
{
// BEGIN USER INSERT SECTION ObserverImpl::~ObserverImpl
// END USER INSERT SECTION ObserverImpl::~ObserverImpl

    component_->_remove_ref();
}


::CORBA::Object*
ObserverImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
ObserverImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
ObserverImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION ObserverImpl::configuration_complete
    ObserverSessionImpl* segment = dynamic_cast<ObserverSessionImpl*>(obtain_executor("component"));
	//segment -> configuration_complete ();
// END USER INSERT SECTION ObserverImpl::configuration_complete
}


void
ObserverImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::DiningPhilosophers::CCM_Observer_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::DiningPhilosophers::CCM_Observer_Context*>(context);
    
    if (tmp_context)
        context_ = ::DiningPhilosophers::CCM_Observer_Context::_duplicate(tmp_context);
    else
        context_ = ::DiningPhilosophers::CCM_Observer_Context::_nil();
        
    #else
    context_ = ::DiningPhilosophers::CCM_Observer_Context::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
ObserverImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ObserverImpl::ccm_activate
// END USER INSERT SECTION ObserverImpl::ccm_activate
}


void
ObserverImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ObserverImpl::ccm_passivate
// END USER INSERT SECTION ObserverImpl::ccm_passivate
}


void
ObserverImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION ObserverImpl::ccm_remove
// END USER INSERT SECTION ObserverImpl::ccm_remove
}


// BEGIN USER INSERT SECTION ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl


ObserverHomeImpl::ObserverHomeImpl()
{
// BEGIN USER INSERT SECTION ObserverHomeImpl::ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl::ObserverHomeImpl
}


ObserverHomeImpl::~ObserverHomeImpl()
{
// BEGIN USER INSERT SECTION ObserverHomeImpl::~ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl::~ObserverHomeImpl

}


void
ObserverHomeImpl::set_context(Components::CCMContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::CCMContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
ObserverHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION ObserverHomeImpl::create
    return new ObserverImpl();
// END USER INSERT SECTION ObserverHomeImpl::create
    return new ObserverImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ObserverHomeE(void)
{
// BEGIN USER INSERT SECTION create_ObserverHome
// END USER INSERT SECTION create_ObserverHome

    return new ::dinner::ObserverHomeImpl();
}
