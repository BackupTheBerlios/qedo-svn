/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2003 by the Qedo Team                                */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#include "ExtensionContext.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: ExtensionContext.cpp,v 1.3 2003/11/03 15:34:26 tom Exp $";


namespace Qedo {


ExtensionContext::ExtensionContext()
{
}


ExtensionContext::~ExtensionContext()
{
	DEBUG_OUT ( "SessionContext: Destructor called" );
}

void
ExtensionContext::set_server_interceptor_dispatcher_registration(Components::Extension::ServerInterceptorRegistration_ptr registration)
{

	server_registration_ = registration;
};

void
ExtensionContext::set_client_interceptor_dispatcher_registration(Components::Extension::ClientInterceptorRegistration_ptr registration)
{
	client_registration_ = registration;
}

Components::Extension::ServerInterceptorRegistration_ptr
ExtensionContext::get_server_interceptor_dispatcher_registration()
{
	return Components::Extension::ServerInterceptorRegistration::_duplicate(server_registration_);

}

Components::Extension::ClientInterceptorRegistration_ptr
ExtensionContext::get_client_interceptor_dispatcher_registration()
{
	return Components::Extension::ClientInterceptorRegistration::_duplicate(client_registration_);

}

} // namepscae Qedo

