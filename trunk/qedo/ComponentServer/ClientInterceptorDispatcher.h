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


#ifndef __CLIENT_INTERCEPTOR_DISPATCHER_H__
#define __CLIENT_INTERCEPTOR_DISPATCHER_H__

#ifndef _QEDO_NO_QOS


#include <CORBA.h>
#ifdef MICO_ORB
#include <mico/pi.h>
#else
#include <PortableInterceptor.h>
#endif
#include "QedoComponents_skel.h"
#include "ComponentServerImpl.h"


namespace Qedo {

	class ClientInterceptorEntry {
	public:
		Components::Extension::ClientContainerInterceptor_var interceptor;
		std::string id;
	};

	typedef std::vector < ClientInterceptorEntry > ClientInterceptorVector;

	class ClientInterceptorDispatcher :
		public virtual Components::Extension::ClientInterceptorRegistration,
		public virtual CORBA::LocalObject
	{
	private:
		/** vector of interceptors registered for all */
		ClientInterceptorVector all_client_interceptors_;
		/** Mutex for all_server_interceptors_ */
		QedoReadWriteMutex all_client_interceptors_mutex_;

		/** vector of interceptors registered for all */
		ClientInterceptorVector for_component_id_client_interceptors_;
		/** Mutex for all_server_interceptors_ */
		QedoMutex for_component_id_client_interceptors_mutex_;

		/** reference to the component server */
		Qedo::ComponentServerImpl* component_server_;

		/** reference to the CDR codec to code the service context data */
		IOP::Codec_var m_cdrCodec;

	public:
		ClientInterceptorDispatcher();

		~ClientInterceptorDispatcher();


		// PI name
		virtual char* name ();

		virtual void
		destroy();

		virtual void
		send_request( PortableInterceptor::ClientRequestInfo_ptr info );

		virtual void
		send_poll( PortableInterceptor::ClientRequestInfo_ptr info );

		virtual void
		receive_reply( PortableInterceptor::ClientRequestInfo_ptr info ) ;

		virtual void
		receive_exception( PortableInterceptor::ClientRequestInfo_ptr info );

		virtual void
		receive_other( PortableInterceptor::ClientRequestInfo_ptr info );

		virtual void
		register_interceptor_for_all(Components::Extension::ClientContainerInterceptor_ptr interceptor);

		virtual void
		unregister_interceptor_for_all(Components::Extension::ClientContainerInterceptor_ptr interceptor);

		void
		set_component_server(Qedo::ComponentServerImpl* component_server);

		void
		init_cdr();

	};
}

#endif

#endif
