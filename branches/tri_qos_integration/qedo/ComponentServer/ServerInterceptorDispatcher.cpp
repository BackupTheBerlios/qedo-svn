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

#include "ServerInterceptorDispatcher.h"
#include "Util.h"
#include "fstream"
#include "string"

static char rcsid[] UNUSED = "$Id: ServerInterceptorDispatcher.cpp,v 1.2.6.2 2003/09/10 06:13:33 tom Exp $";

namespace Qedo {

	ServerInterceptorDispatcher::ServerInterceptorDispatcher() {
	
	}

	ServerInterceptorDispatcher::~ServerInterceptorDispatcher() {

	}

		char* 
			ServerInterceptorDispatcher::name () {
				return CORBA::string_dup("ServerIntereptorDispatcher");

			}

		void
			ServerInterceptorDispatcher::destroy() {
				
			}

		void
			ServerInterceptorDispatcher::receive_request_service_contexts(PortableInterceptor::ServerRequestInfo_ptr info)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {
				try
				{
					if ( !CORBA::is_nil(interceptor_))
					{
						std::string mes;
						mes.append("rec_service_context : ");
						mes.append(info -> operation());
						interceptor_ -> get_message(mes.c_str());
					}
				} catch ( ... )
				{
				}
		}

	    void
			ServerInterceptorDispatcher::receive_request(PortableInterceptor::ServerRequestInfo_ptr info)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {
				try
				{
					if ( !CORBA::is_nil(interceptor_))
					{
						std::string mes;
						mes.append("rec_req : ");
						mes.append(info -> operation());
						interceptor_ -> get_message(mes.c_str());
					}
				}  catch ( ... )
				{
				}
			}


		void
			ServerInterceptorDispatcher::send_reply(PortableInterceptor::ServerRequestInfo_ptr info)
			throw(CORBA::SystemException){
				try
				{
					if ( !CORBA::is_nil(interceptor_))
					{
						std::string mes;
						mes.append("send_reply : ");
						mes.append(info -> operation());
						interceptor_ -> get_message(mes.c_str());
					}
				}  catch ( ... )
				{
				}				
			}

		void
			ServerInterceptorDispatcher::send_exception(PortableInterceptor::ServerRequestInfo_ptr info)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {
				try
				{
					if ( !CORBA::is_nil(interceptor_))
					{
						std::string mes;
						mes.append("send_exception : ");
						mes.append(info -> operation());
						interceptor_ -> get_message(mes.c_str());
					}
				} catch ( ... )
				{
				}
			}

		void
			ServerInterceptorDispatcher::send_other(PortableInterceptor::ServerRequestInfo_ptr info)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {
				try
				{
					if ( !CORBA::is_nil(interceptor_))
					{
						std::string mes;
						mes.append("send_other : ");
						mes.append(info -> operation());
						interceptor_ -> get_message(mes.c_str());
					}
				} catch ( ... )
				{
				}
			}


		void 
		ServerInterceptorDispatcher::register_server_interceptor(Components::Extension::ContainerInterceptor_ptr interceptor)
		{
			interceptor_ = interceptor;
			
			
		}


}  //namespace Qedo
