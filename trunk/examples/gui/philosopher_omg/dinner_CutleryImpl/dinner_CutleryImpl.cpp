//
// generated by Qedo
//

#include "dinner_CutleryImpl.h"


// BEGIN USER INSERT SECTION file

#include "used.xpm"
#include "unused.xpm"


void
CutleryGUI::init()
{
	// add button and empty fork
//	button = new Fl_Button(10,10,120,120,"Bitmap");
//	button ->image(new Fl_Bitmap(sorceress_bits,sorceress_width,sorceress_height));
	box = new Fl_Box(0,0,this->w(),this->h()); 
	used_img = new Fl_Pixmap(used_xpm);
	unused_img = new Fl_Pixmap(unused_xpm);
	box->image(unused_img);
	box->redraw();
	
};

void
CutleryGUI::unused()
{
	// draw unused
//	button ->image(new Fl_Bitmap(sorceress_bits,sorceress_width,sorceress_height));
	box->image(unused_img);
	box->redraw();
	

};

void
CutleryGUI::used()
{
	// draw used
//	button ->image(new Fl_Bitmap(sorceress_bits1,sorceress_width,sorceress_height));
	box->image(used_img);
	box->redraw();
	
};

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
// END USER INSERT SECTION CutlerySessionImpl::~CutlerySessionImpl

}


void
CutlerySessionImpl::set_context(::DiningPhilosophers::CCM_ForkManager_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::DiningPhilosophers::CCM_ForkManager_ContextImpl::_duplicate(context);
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


// BEGIN USER INSERT SECTION Seg

void*
Seg::start_gui(void *p)
{
	Seg* impl;
	impl = static_cast<Seg*>(p);

	impl->gui_stopped_ = false;

	impl->gui = //new Fl_Double_Window(300,180, "Radar1");
		new CutleryGUI(150, 200,impl);

	impl->gui->init();
	impl->gui->end();
	impl->gui->show();

	while (Fl::check()) 
	{
		if ( impl->gui_stopped_) 
		{
			break;
		}
// TODO		sleep(1);

	};


	return 0;
}

void
Seg::stop_gui()
{
	gui_stopped_ = true;
	delete gui;
//	gui_thread->join();

}

// END USER INSERT SECTION Seg


Seg::Seg()
{
// BEGIN USER INSERT SECTION Seg::Seg
// END USER INSERT SECTION Seg::Seg
}


Seg::~Seg()
{
// BEGIN USER INSERT SECTION Seg::~Seg
// END USER INSERT SECTION Seg::~Seg

}


void
Seg::set_context(::DiningPhilosophers::CCM_ForkManager_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::DiningPhilosophers::CCM_ForkManager_ContextImpl::_duplicate(context);
}


void
Seg::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION Seg::configuration_complete
		gui_thread_ = context_->start_thread(start_gui,this);
		owner = false;

// END USER INSERT SECTION Seg::configuration_complete
}


void
Seg::get()
	throw(CORBA::SystemException, ::DiningPhilosophers::InUse)
{
// BEGIN USER INSERT SECTION Seg::get
	if(owner) 
    {
		throw DiningPhilosophers::InUse();
	}

/* update gui */
	// ToDo
	std::cout << "get() called " << std::endl;
	gui -> used();
	owner = true;

// END USER INSERT SECTION Seg::get
}


void
Seg::release()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION Seg::release

// update GUI
	// ToDo
    owner = false;
	std::cout << "release() called " << std::endl;
	gui -> unused();
// END USER INSERT SECTION Seg::release
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
    ::DiningPhilosophers::CCM_ForkManager_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::DiningPhilosophers::CCM_ForkManager_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::DiningPhilosophers::CCM_ForkManager_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::DiningPhilosophers::CCM_ForkManager_ContextImpl::_nil();
        
    #else
    context_ = ::DiningPhilosophers::CCM_ForkManager_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
    Seg_->set_context(context_);
}


void
CutleryImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CutleryImpl::ccm_activate
// END USER INSERT SECTION CutleryImpl::ccm_activate
}


void
CutleryImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CutleryImpl::ccm_passivate
// END USER INSERT SECTION CutleryImpl::ccm_passivate
}


void
CutleryImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CutleryImpl::ccm_remove
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
// END USER INSERT SECTION CutleryHomeImpl::~CutleryHomeImpl

}


void
CutleryHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
CutleryHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION CutleryHomeImpl::create
// END USER INSERT SECTION CutleryHomeImpl::create
    return new CutleryImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ForkHomeE(void)
{
// BEGIN USER INSERT SECTION create_ForkHome
// END USER INSERT SECTION create_ForkHome

    return new ::dinner::CutleryHomeImpl();
}
