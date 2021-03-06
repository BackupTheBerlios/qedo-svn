//
// generated by Qedo
//

#ifndef _QedoQoS_ReservationQoSProvider_H_
#define _QedoQoS_ReservationQoSProvider_H_


// BEGIN USER INSERT SECTION file_pre
namespace QedoQoS {
	class ReservationQoSproviderImpl;
};
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "QedoQoS_ReservationQoSProvider_BUSINESS.h"
#include "component_valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include "ClientInterceptor.h"
#include "ServerInterceptor.h"
#include "valuetypes.h"
// END USER INSERT SECTION file_post


namespace QedoQoS
{
    
    //
    // executor
    //
    class ReservationQoSproviderImpl
        : public virtual CORBA::LocalObject
        , public virtual ::QedoQoS::CCM_ReservationQoSproviderImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ReservationQoSproviderImpl
// END USER INSERT SECTION INHERITANCE_ReservationQoSproviderImpl
    {
    
    private:
    
        ::QedoQoS::CCM_Reservation_ContextImpl_var context_;
        
    public:
    
        ReservationQoSproviderImpl();
        virtual ~ReservationQoSproviderImpl();
        
        void set_context(::QedoQoS::CCM_Reservation_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:Components/QoS/Negotiation/require_qos:1.0
        //
        virtual Components::Cookie* require_qos(const Components::QoS::QoSConstraint& requirements, const char* client_id)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/QoS/Negotiation/release_qos:1.0
        //
        virtual void release_qos(Components::Cookie* ck)
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION ReservationQoSproviderImpl
	private:
		QedoQoS_Reservation::ClientContainerInterceptor* client_interceptor_;
		QedoQoS_Reservation::ServerContainerInterceptor* server_interceptor_;
		Components::Cookie_var client_ck;
		Components::Cookie_var server_ck;
	public:
		void
		register_copis();

		void
		unregister_copis();

		void 
		init_copis (Components::ConfigValues*);
// END USER INSERT SECTION ReservationQoSproviderImpl

    };
    
    
    //
    // executor locator
    //
    class ReservationQoSProvider
        : public virtual CORBA::LocalObject
        , public virtual Components::ExtensionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ReservationQoSProvider
// END USER INSERT SECTION INHERITANCE_ReservationQoSProvider
    {
    
    private:
    
        ::QedoQoS::CCM_Reservation_ContextImpl_var context_;
        
        ReservationQoSproviderImpl* component_;
        
    public:
    
        ReservationQoSProvider();
        virtual ~ReservationQoSProvider();
        
        
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
        // IDL:Components/ExtensionComponent/set_extension_context:1.0
        //
        virtual void set_extension_context(Components::ExtensionContext_ptr ctx)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, ::Components::CCMException);
    
// BEGIN USER INSERT SECTION ReservationQoSProvider
// END USER INSERT SECTION ReservationQoSProvider

    };
    
    
    //
    // home executor
    //
    class ReservationQoSProviderHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::QedoQoS::CCM_ReservationHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_ReservationQoSProviderHomeImpl
// END USER INSERT SECTION INHERITANCE_ReservationQoSProviderHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        ReservationQoSProviderHomeImpl();
        virtual ~ReservationQoSProviderHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION ReservationQoSProviderHomeImpl
// END USER INSERT SECTION ReservationQoSProviderHomeImpl

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
::Components::HomeExecutorBase_ptr create_ReservationHomeE(void);
}

#endif
