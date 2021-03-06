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

static char rcsid[] UNUSED = "$Id: ServerInterceptorDispatcher.cpp,v 1.2 2003/08/01 12:25:30 boehme Exp $";

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
			ServerInterceptorDispatcher::receive_request_service_contexts(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {

		}

	    void
			ServerInterceptorDispatcher::receive_request(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {

			}


		void
			ServerInterceptorDispatcher::send_reply(PortableInterceptor::ServerRequestInfo_ptr)
			throw(CORBA::SystemException){
				std::cout << "!!!!!!!!!!!!!!TEST!!!!!!!!!!!!!" << std::endl;

				
			}

		void
			ServerInterceptorDispatcher::send_exception(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {
			
			}

		void
			ServerInterceptorDispatcher::send_other(PortableInterceptor::ServerRequestInfo_ptr)
			throw(PortableInterceptor::ForwardRequest, CORBA::SystemException) {

			}



}  //namespace Qedo
