//
// generated by Qedo
//

#ifndef _dinner_PhilosopherImpl_H_
#define _dinner_PhilosopherImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "dinner_PhilosopherImpl_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

namespace dinner {
class PhilosopherSessionImpl;
};

class PhilosopherGUI : public Fl_Window  {
	//void draw();
	dinner::PhilosopherSessionImpl* impl_;

public:
	
	PhilosopherGUI(int W,int H, dinner::PhilosopherSessionImpl* impl
,const char *l=0) : Fl_Window(W,H,l), impl_(impl) {}
};

// END USER INSERT SECTION file_post


namespace dinner
{
    
    //
    // executor
    //
    class PhilosopherSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::dinner::CCM_PhilosopherSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherSessionImpl
// END USER INSERT SECTION INHERITANCE_PhilosopherSessionImpl
    {
    
    private:
    
        ::DiningPhilosophers::CCM_Philosopher_ContextImpl_var context_;
        
    public:
    
        PhilosopherSessionImpl();
        virtual ~PhilosopherSessionImpl();
        
        void set_context(::DiningPhilosophers::CCM_Philosopher_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:DiningPhilosophers/Philosopher/name:1.0
        //
        void name(const char* param)
        	throw(CORBA::SystemException);
        char* name()
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION PhilosopherSessionImpl
	private :
		bool right_hander_;
		std::string id_;
		bool stopped_;
		int tickTime_;
		
		DiningPhilosophers::PhilosopherState status;

        Components::Thread_var data_thread_;
        Components::Thread_var gui_thread_;

		bool gui_stopped;
		PhilosopherGUI *gui_;
		static void* run(void*);
		void stop();
		static void* start_gui(void*);
		void stop_gui();
		void run_philo();


// END USER INSERT SECTION PhilosopherSessionImpl

    };
    
    
    //
    // executor locator
    //
    class PhilosopherImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherImpl
// END USER INSERT SECTION INHERITANCE_PhilosopherImpl
    {
    
    private:
    
        ::DiningPhilosophers::CCM_Philosopher_ContextImpl_var context_;
        
        PhilosopherSessionImpl* component_;
        
    public:
    
        PhilosopherImpl();
        virtual ~PhilosopherImpl();
        
        
        //
        // IDL:Components/ExecutorLocator/obtain_executor:1.0
        //
        virtual CORBA::Object_ptr obtain_executor(const char* name)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/ExecutorLocator/release_executor:1.0
        //
        virtual void release_executor(CORBA::Object_ptr exc)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/ExecutorLocator/configuration_complete:1.0
        //
        virtual void configuration_complete()
        	throw(CORBA::SystemException, ::Components::InvalidConfiguration);
        
        //
        // IDL:Components/SessionComponent/set_session_context:1.0
        //
        virtual void set_session_context(Components::SessionContext_ptr ctx)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, ::Components::CCMException);
    
// BEGIN USER INSERT SECTION PhilosopherImpl
// END USER INSERT SECTION PhilosopherImpl

    };
    
    
    //
    // home executor
    //
    class PhilosopherHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::DiningPhilosophers::CCM_PhilosopherHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherHomeImpl
// END USER INSERT SECTION INHERITANCE_PhilosopherHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        PhilosopherHomeImpl();
        virtual ~PhilosopherHomeImpl();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::HomeContext_ptr ctx)
            throw (CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::EnterpriseComponent_ptr create()
            throw (CORBA::SystemException, Components::CreateFailure);
        
        //
        // IDL:DiningPhilosophers/PhilosopherHome/new:1.0
        //
        virtual ::Components::EnterpriseComponent_ptr _cxx_new(const char* name)
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION PhilosopherHomeImpl
// END USER INSERT SECTION PhilosopherHomeImpl

    };
    
};

//
// entry point
//
extern "C" {
#ifdef _WIN32
__declspec(dllexport)
#else
#endif
::Components::HomeExecutorBase_ptr create_PhilosopherHomeE(void);
}

#endif
