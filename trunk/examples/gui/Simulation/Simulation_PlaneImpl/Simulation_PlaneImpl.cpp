//
// generated by Qedo
//

#include "Simulation_PlaneImpl.h"


// BEGIN USER INSERT SECTION file

#ifdef _WIN32
#define sleep(X) Sleep(X*1000)
#endif
#include <math.h>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>

// END USER INSERT SECTION file


namespace Simulation {


// BEGIN USER INSERT SECTION PlaneSessionImpl
void
PlaneSessionImpl::fly()
{
	flight_stopped = false;

	while (! flight_stopped) 
	{

		// fly

		//compute new position
		longitude_= longitude_ + ((sin(course_) * speed_));
		latitude_ = latitude_ + ((cos(course_) * speed_));
		altitude_++;

		// send position to Simulation Server
		Position cur_pos;
		cur_pos.longitude = longitude_;
		cur_pos.latitude = latitude_;
		cur_pos.altitude = altitude_;

		try {
			context_->get_connection_sim_server()->set_position(id_.c_str(), cur_pos);
		} catch( ... ) {}; 
		// debug
		std::cout << "fly " << longitude_ << " " << latitude_ << " " <<	altitude_ << std::endl;

		sleep(1);
	}
}

void*
PlaneSessionImpl::run(void *p)
{

	PlaneSessionImpl* impl;
	impl = static_cast<PlaneSessionImpl*>(p);

	impl->fly();

	return 0;
}

void
PlaneSessionImpl::stop()
{
	flight_stopped = true;
	flight_thread->join();

}

void*
PlaneSessionImpl::start_gui(void *p)
{
	PlaneSessionImpl* impl;
	impl = static_cast<PlaneSessionImpl*>(p);

	impl->gui_stopped = false;

	impl->window = new Fl_Window(300,180, impl->identifier());

	Fl_Input *course = new Fl_Input(100,10, 100, 20, "Course:");
	Fl_Input *speed = new Fl_Input(100,40, 100, 20, "Speed:");

	Fl_Button *change = new Fl_Button(100, 70, 100, 20, "Change");

	std::cout << "id: " << impl->identifier() << std::endl;
	  impl->window->end();
	  impl->window->show();

	while (Fl::wait()) 
	{
		if ( impl->gui_stopped) 
		{
			break;
		}

	};


	return 0;
}

void
PlaneSessionImpl::stop_gui()
{
	gui_stopped = true;
	Fl::awake();
	delete window;
//	gui_thread->join();

}

// END USER INSERT SECTION PlaneSessionImpl


PlaneSessionImpl::PlaneSessionImpl()
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::PlaneSessionImpl
	flight_stopped = true;
	gui_stopped = true;
// END USER INSERT SECTION PlaneSessionImpl::PlaneSessionImpl
}


PlaneSessionImpl::~PlaneSessionImpl()
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::~PlaneSessionImpl
// END USER INSERT SECTION PlaneSessionImpl::~PlaneSessionImpl

}


void
PlaneSessionImpl::set_context(::Simulation::CCM_Plane_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::Simulation::CCM_Plane_ContextImpl::_duplicate(context);
}


void
PlaneSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::configuration_complete
	flight_thread = context_->start_thread(run,this);
	gui_thread = context_->start_thread(start_gui,this);

// END USER INSERT SECTION PlaneSessionImpl::configuration_complete
}


void
PlaneSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::remove
// END USER INSERT SECTION PlaneSessionImpl::remove
}


void
PlaneSessionImpl::identifier(const char* param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::_identifier
	id_=param;
// END USER INSERT SECTION PlaneSessionImpl::_identifier
}


char*
PlaneSessionImpl::identifier()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::identifier
	return strdup(id_.c_str());  
// END USER INSERT SECTION PlaneSessionImpl::identifier
}


void
PlaneSessionImpl::initial_longitude(CORBA::Double param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::_initial_longitude
	longitude_ = param;
// END USER INSERT SECTION PlaneSessionImpl::_initial_longitude
}


CORBA::Double
PlaneSessionImpl::initial_longitude()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::initial_longitude
	return longitude_;
// END USER INSERT SECTION PlaneSessionImpl::initial_longitude
}


void
PlaneSessionImpl::initial_latitude(CORBA::Double param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::_initial_latitude
	latitude_ = param;

// END USER INSERT SECTION PlaneSessionImpl::_initial_latitude
}


CORBA::Double
PlaneSessionImpl::initial_latitude()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::initial_latitude
	return latitude_;
// END USER INSERT SECTION PlaneSessionImpl::initial_latitude
}


void
PlaneSessionImpl::initial_altitude(CORBA::Double param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::_initial_altitude
	altitude_ = param;
// END USER INSERT SECTION PlaneSessionImpl::_initial_altitude
}


CORBA::Double
PlaneSessionImpl::initial_altitude()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::initial_altitude
	return altitude_;
// END USER INSERT SECTION PlaneSessionImpl::initial_altitude
}


void
PlaneSessionImpl::initial_course(CORBA::Double param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::_initial_course
	course_ = (param * 3.14159) /  180;
// END USER INSERT SECTION PlaneSessionImpl::_initial_course
}


CORBA::Double
PlaneSessionImpl::initial_course()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::initial_course
	return course_;
// END USER INSERT SECTION PlaneSessionImpl::initial_course
}


void
PlaneSessionImpl::speed(CORBA::Double param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::_speed
	speed_ = param;
// END USER INSERT SECTION PlaneSessionImpl::_speed
}


CORBA::Double
PlaneSessionImpl::speed()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PlaneSessionImpl::speed
	return speed_;
// END USER INSERT SECTION PlaneSessionImpl::speed
}


// BEGIN USER INSERT SECTION PlaneImpl
// END USER INSERT SECTION PlaneImpl


PlaneImpl::PlaneImpl()
:component_(new PlaneSessionImpl())
{
// BEGIN USER INSERT SECTION PlaneImpl::PlaneImpl
// END USER INSERT SECTION PlaneImpl::PlaneImpl
}


PlaneImpl::~PlaneImpl()
{
// BEGIN USER INSERT SECTION PlaneImpl::~PlaneImpl
// END USER INSERT SECTION PlaneImpl::~PlaneImpl

    component_->_remove_ref();
}


::CORBA::Object*
PlaneImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
PlaneImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
PlaneImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION PlaneImpl::configuration_complete
// END USER INSERT SECTION PlaneImpl::configuration_complete
}


void
PlaneImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::Simulation::CCM_Plane_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::Simulation::CCM_Plane_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::Simulation::CCM_Plane_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::Simulation::CCM_Plane_ContextImpl::_nil();
        
    #else
    context_ = ::Simulation::CCM_Plane_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
PlaneImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PlaneImpl::ccm_activate
// END USER INSERT SECTION PlaneImpl::ccm_activate
}


void
PlaneImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PlaneImpl::ccm_passivate
// END USER INSERT SECTION PlaneImpl::ccm_passivate
}


void
PlaneImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PlaneImpl::ccm_remove
		component_->stop();
		component_->stop_gui();

// END USER INSERT SECTION PlaneImpl::ccm_remove
}


// BEGIN USER INSERT SECTION PlaneHomeImpl
// END USER INSERT SECTION PlaneHomeImpl


PlaneHomeImpl::PlaneHomeImpl()
{
// BEGIN USER INSERT SECTION PlaneHomeImpl::PlaneHomeImpl
// END USER INSERT SECTION PlaneHomeImpl::PlaneHomeImpl
}


PlaneHomeImpl::~PlaneHomeImpl()
{
// BEGIN USER INSERT SECTION PlaneHomeImpl::~PlaneHomeImpl
// END USER INSERT SECTION PlaneHomeImpl::~PlaneHomeImpl

}


void
PlaneHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
PlaneHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION PlaneHomeImpl::create
// END USER INSERT SECTION PlaneHomeImpl::create
    return new PlaneImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_PlaneHomeE(void)
{
// BEGIN USER INSERT SECTION create_PlaneHome
// END USER INSERT SECTION create_PlaneHome

    return new ::Simulation::PlaneHomeImpl();
}

