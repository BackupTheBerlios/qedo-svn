/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2003 by the Qedo Team                                */
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


#ifndef __SERVER_INTERCEPTOR_DISPATCHER_H__
#define __SERVER_INTERCEPTOR_DISPATCHER_H__

#ifndef _QEDO_NO_QOS


#include <CORBA.h>
#ifdef MICO_ORB
#include <mico/pi.h>
#else
#include <PortableInterceptor.h>
#endif
#include "QedoComponents_skel.h"
#include "Synchronisation.h"
#include "ComponentServerImpl.h"
#include <vector>

namespace Qedo {


	class ServerInterceptorEntry {
	public:
		Components::Extension::ServerContainerInterceptor_var interceptor;
		std::string id;
	};

	typedef std::vector < ServerInterceptorEntry > ServerInterceptorVector;


	class ServerInterceptorDispatcher :
		public virtual Components::Extension::ServerInterceptorRegistration,
		public virtual CORBA::LocalObject
	{
	private:

		/** vector of interceptors registered for all */
		ServerInterceptorVector all_server_interceptors_;
		/** Mutex for all_server_interceptors_ */
		QedoMutex all_server_interceptors_mutex_;

		/** vector of interceptors registered for all */
		ServerInterceptorVector for_component_id_server_interceptors_;
		/** Mutex for all_server_interceptors_ */
		QedoMutex for_component_id_server_interceptors_mutex_;

		/** reference to the component server */
		Qedo::ComponentServerImpl* component_server_;

	public:
		ServerInterceptorDispatcher();

		~ServerInterceptorDispatcher();


		// PI name
		virtual char* name ();

		virtual void
		destroy();

		virtual void
		receive_request_service_contexts(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

		virtual void
		receive_request(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

		virtual void
		send_reply(PortableInterceptor::ServerRequestInfo_ptr)
			throw(CORBA::SystemException);

		virtual void
		send_exception(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

		virtual void
		send_other(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException);

		virtual void
		register_interceptor_for_all(Components::Extension::ServerContainerInterceptor_ptr interceptor);

		virtual void
		register_interceptor_for_component(Components::Extension::ServerContainerInterceptor_ptr interceptor, const char * id);

		virtual void
		unregister_interceptor_for_all(Components::Extension::ServerContainerInterceptor_ptr interceptor);

		virtual void
		unregister_interceptor_for_component(Components::Extension::ServerContainerInterceptor_ptr interceptor, const char * id);

		void
		set_component_server(Qedo::ComponentServerImpl* component_server);

	};
}

#endif

#endif
