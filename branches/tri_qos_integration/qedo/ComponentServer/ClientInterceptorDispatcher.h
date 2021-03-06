/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
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

#include <CORBA.h>
#ifdef MICO_ORB
#include <mico/pi.h>
#else
#include <PortableInterceptor.h>
#endif
#include "QedoComponents_skel.h"
#include "RefCountBase.h"


namespace Qedo {


	class ClientInterceptorDispatcher : 
//		public virtual PortableInterceptor::ClientRequestInterceptor,
		public Components::Extension::ClientInterceptorRegistration,
		public virtual Qedo::RefCountLocalObject
	{

	public:
		ClientInterceptorDispatcher();

		~ClientInterceptorDispatcher();


		// PI name
		virtual char* name ();

		virtual void
		destroy();

		virtual void 
		send_request(PortableInterceptor::ClientRequestInfo_ptr ri);

	    virtual void 
		send_poll(PortableInterceptor::ClientRequestInfo_ptr ri) ;

	    virtual void 
		receive_reply(PortableInterceptor::ClientRequestInfo_ptr ri);

	    virtual void 
		receive_exception(PortableInterceptor::ClientRequestInfo_ptr ri);

	    virtual void 
		receive_other(PortableInterceptor::ClientRequestInfo_ptr ri);
	
		/**
		* to register a Container interceptor
		*/
		virtual void 
		register_client_interceptor(Components::Extension::ContainerInterceptor_ptr interceptor);


	};
}

#endif
