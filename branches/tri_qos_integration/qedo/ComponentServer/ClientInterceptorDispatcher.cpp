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

#include "ClientInterceptorDispatcher.h"
#include "Util.h"
#include "fstream"

static char rcsid[] UNUSED = "$Id: ClientInterceptorDispatcher.cpp,v 1.2.6.1 2003/09/08 10:37:55 tom Exp $";

namespace Qedo {

	ClientInterceptorDispatcher::ClientInterceptorDispatcher()
	{
	}

	ClientInterceptorDispatcher::~ClientInterceptorDispatcher() {

	}

	char* 
		ClientInterceptorDispatcher::name () {
			return CORBA::string_dup("ClientIntereptorDispatcher");

		}

	void
		ClientInterceptorDispatcher::destroy() {
			
		}

	void 
	ClientInterceptorDispatcher::send_request(PortableInterceptor::ClientRequestInfo_ptr ri)
	{
			
	}

	void 
	ClientInterceptorDispatcher::send_poll(PortableInterceptor::ClientRequestInfo_ptr ri) 
	{
	}

	void 
	ClientInterceptorDispatcher::receive_reply(PortableInterceptor::ClientRequestInfo_ptr ri)
	{
	}

	void 
	ClientInterceptorDispatcher::receive_exception(PortableInterceptor::ClientRequestInfo_ptr ri) 
	{
	}

	void 
	ClientInterceptorDispatcher::receive_other(PortableInterceptor::ClientRequestInfo_ptr ri)
	{
	}

	void 
	ClientInterceptorDispatcher::register_client_interceptor(Components::Extension::ContainerInterceptor_ptr interceptor)
	{
		
	}

}  //namespace Qedo
