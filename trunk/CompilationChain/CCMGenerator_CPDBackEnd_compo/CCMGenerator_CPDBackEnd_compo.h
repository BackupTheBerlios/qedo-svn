//
// generated by Qedo
//

#ifndef _CCMGenerator_CPDBackEnd_compo_H_
#define _CCMGenerator_CPDBackEnd_compo_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "CCMGenerator_CPDBackEnd_compo_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include "RepositoryConnector.h"
// END USER INSERT SECTION file_post


namespace CCMGenerator
{
    
    //
    // executor
    //
    class CPDBackendSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::CCMGenerator::CCM_CPDBackendSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CPDBackendSessionImpl
// END USER INSERT SECTION INHERITANCE_CPDBackendSessionImpl
    {
    
    private:
    
        ::CCMGenerator::CCM_CPDBackend_ContextImpl_var context_;
        
    public:
    
        CPDBackendSessionImpl();
        virtual ~CPDBackendSessionImpl();
        
        void set_context(::CCMGenerator::CCM_CPDBackend_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:CCMGenerator/CPDBackend/rep_ref:1.0
        //
        void rep_ref(CORBA::Object_ptr param)
        	throw(CORBA::SystemException);
        CORBA::Object_ptr rep_ref()
        	throw(CORBA::SystemException);
        
        //
        // IDL:CCMGenerator/BackEndControl/generate:1.0
        //
        virtual void generate(const char* target, const char* output)
        	throw(CORBA::SystemException, ::CCMGenerator::OutputError);
    
// BEGIN USER INSERT SECTION CPDBackendSessionImpl
	private:

	CORBA::Object_var _root;
	CCMGenerator::CCMRepositoryConnector _repconnector;
	MDE::BaseIDL::BaseIDLPackage_var _base_idl_pkg_ref; 
	MDE::CIF::CIFPackage_var _cif_ref;
	MDE::ComponentIDL::ComponentIDLPackage_var _component_idl_ref;
	MDE::Deployment::DeploymentPackage_var _deployment_ref;

	void connect_the_whole_repository ();
	//generate methods
	void _generte_property_element
		( MDE::Deployment::Property_ptr, ostream& out, unsigned long & indent_level );

	public:
		void begin ( ostream& out );
// END USER INSERT SECTION CPDBackendSessionImpl

    };
    
    
    //
    // executor locator
    //
    class CPDBackEnd_compo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CPDBackEnd_compo
// END USER INSERT SECTION INHERITANCE_CPDBackEnd_compo
    {
    
    private:
    
        ::CCMGenerator::CCM_CPDBackend_ContextImpl_var context_;
        
        CPDBackendSessionImpl* component_;
        
    public:
    
        CPDBackEnd_compo();
        virtual ~CPDBackEnd_compo();
        
        
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
    
// BEGIN USER INSERT SECTION CPDBackEnd_compo
// END USER INSERT SECTION CPDBackEnd_compo

    };
    
    
    //
    // home executor
    //
    class CPDBackendHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::CCMGenerator::CCM_CPDBackendHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CPDBackendHomeImpl
// END USER INSERT SECTION INHERITANCE_CPDBackendHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        CPDBackendHomeImpl();
        virtual ~CPDBackendHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION CPDBackendHomeImpl
// END USER INSERT SECTION CPDBackendHomeImpl

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
::Components::HomeExecutorBase_ptr create_CPDBackendHomeE(void);
}

#endif