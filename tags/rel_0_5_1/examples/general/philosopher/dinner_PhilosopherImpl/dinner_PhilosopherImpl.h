//
// generated by Qedo
//

#ifndef _dinner_PhilosopherImpl_H_
#define _dinner_PhilosopherImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "dinner_PhilosopherImpl_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
using namespace std;

namespace dinner {

#ifdef ORBACUS_ORB
class JTCThreadWithTimer : public virtual JTCThread, public virtual JTCMonitor
{
protected:
	void timer_sleep (long millis);

public:
	JTCThreadWithTimer();
	~JTCThreadWithTimer();
	void wake_up ();
};

class PhilosopherSessionImpl;

class PhilosopherThread : public virtual JTCThreadWithTimer
{
	friend class PhilosopherSessionImpl;

private:
	PhilosopherSessionImpl* phil_;

public:
	PhilosopherThread (PhilosopherSessionImpl*);
	~PhilosopherThread();

	void run();
	void stop();
};

#endif

}
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
    
        ::dinner::CCM_Philosopher_ContextImpl_var context_;
        
    public:
    
        PhilosopherSessionImpl();
        virtual ~PhilosopherSessionImpl();
        
        void set_context(::dinner::CCM_Philosopher_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:dinner/Philosopher/thinking_seconds:1.0
        //
        void thinking_seconds(CORBA::ULong param)
        	throw(CORBA::SystemException);
        CORBA::ULong thinking_seconds()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/Philosopher/eating_seconds:1.0
        //
        void eating_seconds(CORBA::ULong param)
        	throw(CORBA::SystemException);
        CORBA::ULong eating_seconds()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/Philosopher/sleeping_seconds:1.0
        //
        void sleeping_seconds(CORBA::ULong param)
        	throw(CORBA::SystemException);
        CORBA::ULong sleeping_seconds()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/Named/name:1.0
        //
        void name(const char* param)
        	throw(CORBA::SystemException);
        char* name()
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION PhilosopherSessionImpl
#ifdef ORBACUS_ORB
		friend class PhilosopherThread;
#endif

	private:
		string id_;
		long tsec_, esec_, ssec_;
		bool stopped_;

#ifdef ORBACUS_ORB
		PhilosopherThread* phil_thread_;
#else
		Components::Thread_var phil_thread_;
#endif

	public:
		// This is the run function that the PhilosopherThread will enter
#ifdef ORBACUS_ORB
		void run();
#else
		static void* run(void*);
#endif
		void stop();
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
    
        ::dinner::CCM_Philosopher_ContextImpl_var context_;
        
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
        , public virtual ::dinner::CCM_PhilosopherHome
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
