/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org/                                                    */
/*                                                                         */
/* Copyright (C) 2002-2004 by the Qedo Team                                */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/


#ifndef __SERVANT_INTERCEPTOR_DISPATCHER_H__
#define __SERVANT_INTERCEPTOR_DISPATCHER_H__

#ifndef _QEDO_NO_QOS
#include <vector>
#include "Components.h"
#include "Synchronisation.h"
#include "Util.h"
#include "ComponentServerImpl.h"

namespace Qedo {

	class ServantInterceptorEntry {
	public:
		Components::ContainerPortableInterceptor::ServantContainerInterceptor_var interceptor;
		std::string id;
	};

	typedef std::vector < ServantInterceptorEntry > ServantInterceptorVector;

	class CONTAINERDLL_API ServantInterceptorDispatcher :
		public virtual Qedo_Components::ServantInterceptorDispatcher,
//		public virtual Components::ContainerPortableInterceptor::ServantInterceptorRegistration,
		public virtual CORBA::LocalObject
	{
	private:

		/** vector of interceptors registered for all */
		ServantInterceptorVector all_servant_interceptors_;
		/** Mutex for all_server_interceptors_ */
		QedoMutex all_servant_interceptors_mutex_;

		/** vector of interceptors registered for component_id */
		ServantInterceptorVector for_component_id_servant_interceptors_;
		/** Mutex for all_servant_interceptors_ */
		QedoMutex for_component_id_servant_interceptors_mutex_;

		/** reference to the component server */
		Qedo::ComponentServerImpl* component_server_;

		/** reference to the orb */
		CORBA::ORB_var orb_;
		

	public:
		ServantInterceptorDispatcher();

		~ServantInterceptorDispatcher();

		void
		set_component_server(Qedo::ComponentServerImpl* component_server);

		// helper functions
		virtual char*
		get_target_id();

		virtual char*
		get_origin_id();

		// Server Registration interface
		virtual Components::Cookie* 
		register_server_interceptor( Components::ContainerPortableInterceptor::ServerContainerInterceptor_ptr si );

		virtual Components::ContainerPortableInterceptor::ServerContainerInterceptor_ptr 
		unregister_server_interceptor( Components::Cookie* ck );

		virtual Components::Cookie* 
		register_servant_interceptor( Components::ContainerPortableInterceptor::ServantContainerInterceptor_ptr si ) ;

		virtual Components::ContainerPortableInterceptor::ServantContainerInterceptor_ptr 
		unregister_servant_interceptor( Components::Cookie* ck ) ;

		virtual void
		register_interceptor_for_all(Components::ContainerPortableInterceptor::ServantContainerInterceptor_ptr interceptor);

		virtual void
		unregister_interceptor_for_all(Components::ContainerPortableInterceptor::ServantContainerInterceptor_ptr interceptor);


		virtual char*
		name();

	    virtual void 
		destroy();
		
		virtual void 
		set_slot_id( ::PortableInterceptor::SlotId slot_id );

	    virtual void 
		servant_receive_request ( Components::ContainerPortableInterceptor::ContainerServantRequestInfo_ptr info, CORBA::Boolean_out con ) ;

		virtual void 
		servant_send_reply ( Components::ContainerPortableInterceptor::ContainerServantRequestInfo_ptr info, CORBA::Boolean_out con ) ;

	    virtual void 
		call( const char* comp_id, const char* origin, const char* operation, CORBA::Boolean_out con ) ;

		virtual CORBA::Boolean 
		call( const char* oper ) ;
//CCMObject
		virtual Components::Cookie* connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con ) ;
	    virtual CORBA::Object_ptr provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con );

#ifndef _QEDO_NO_STREAMS

// StreamCCMObject
		virtual Components::Cookie* 
		bind(const char* comp_id, char*& name,
                           StreamComponents::SinkStreamPort_ptr& the_sink,
						   char*& transport_profile,
						   CORBA::Boolean_out con);

		virtual StreamComponents::SinkStreamPort_ptr 
		unbind(const char* comp_id, char*& name,
                           Components::Cookie*& ck,
						   CORBA::Boolean_out con);

		virtual CORBA::Object_ptr 
		provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) ;

#endif //_QEDO_NO_STREAMS

	};
};

#endif // _QEDO_NO_QOS
#endif // __SERVANT_INTERCEPTOR_DISPATCHER_H__
