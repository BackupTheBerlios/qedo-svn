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


#ifndef __INTERCEPTORDISPATCHER_H__
#define __INTERCEPTORDISPATCHER_H__

#include <CORBA.h>
#ifdef MICO_ORB
#include <mico/pi.h>
#else
#include <PortableInterceptor.h>
#endif
#include "QedoComponents_skel.h"


namespace Qedo {


	class ServerInterceptorDispatcher : 
		public PortableInterceptor::ServerRequestInterceptor,
		public CORBA::LocalObject
	{

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


	};
}

#endif