//
// generated by Qedo
//

#ifndef _Simulation_SimulationServerImpl_H_
#define _Simulation_SimulationServerImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "Simulation_SimulationServerImpl_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include <map>
// END USER INSERT SECTION file_post


namespace Simulation
{
    
    //
    // executor
    //
    class SimulationServerSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::Simulation::CCM_SimulationServerSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SimulationServerSessionImpl
// END USER INSERT SECTION INHERITANCE_SimulationServerSessionImpl
    {
    
    private:
    
        ::Simulation::CCM_SimulationServer_ContextImpl_var context_;
        
    public:
    
        SimulationServerSessionImpl();
        virtual ~SimulationServerSessionImpl();
        
        void set_context(::Simulation::CCM_SimulationServer_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:Simulation/PlaneInput/set_position:1.0
        //
        virtual void set_position(const char* identifier, const Simulation::Position& current_position)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Simulation/RetrieveRadarData/get_data:1.0
        //
        virtual Simulation::RadarData* get_data(const Simulation::Position& radar_position, CORBA::Double radius)
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION SimulationServerSessionImpl
		Components::Mutex_ptr list_mutex_;

		// map element
		// at this time only position
		//map
		typedef std::map<std::string, Simulation::Position> position_map;
		position_map plane_position_map_;
// END USER INSERT SECTION SimulationServerSessionImpl

    };
    
    
    //
    // executor locator
    //
    class SimulationServerImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SimulationServerImpl
// END USER INSERT SECTION INHERITANCE_SimulationServerImpl
    {
    
    private:
    
        ::Simulation::CCM_SimulationServer_ContextImpl_var context_;
        
        SimulationServerSessionImpl* component_;
        
    public:
    
        SimulationServerImpl();
        virtual ~SimulationServerImpl();
        
        
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
    
// BEGIN USER INSERT SECTION SimulationServerImpl
// END USER INSERT SECTION SimulationServerImpl

    };
    
    
    //
    // home executor
    //
    class SimulationServerHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::Simulation::CCM_SimulationServerHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_SimulationServerHomeImpl
// END USER INSERT SECTION INHERITANCE_SimulationServerHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        SimulationServerHomeImpl();
        virtual ~SimulationServerHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION SimulationServerHomeImpl
// END USER INSERT SECTION SimulationServerHomeImpl

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
::Components::HomeExecutorBase_ptr create_SimulationServerHomeE(void);
}

#endif
