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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _QEDO_NO_QOS

#include "ExtensionHomeServant.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: ExtensionHomeServant.cpp,v 1.5 2004/06/24 13:11:03 tom Exp $";


namespace Qedo {

ExtensionHomeServant::ExtensionHomeServant ()
{

}


ExtensionHomeServant::ExtensionHomeServant (const ExtensionHomeServant& extension_home)
: HomeServantBase (extension_home),
  CCMHomeServant (extension_home)
{
}


ExtensionHomeServant& ExtensionHomeServant::operator= (const ExtensionHomeServant& extension_home)
{
	return *this;
}


ExtensionHomeServant::~ExtensionHomeServant()
{
	DEBUG_OUT ("ExtensionHomeServant: Destructor called");
}


void
ExtensionHomeServant::before_remove_component (Components::ExecutorLocator_ptr executor_locator)
{
	Components::ExtensionComponent_ptr extension_component =
		dynamic_cast <Components::ExtensionComponent_ptr> (executor_locator);

	// Should never happen
	assert (! CORBA::is_nil (extension_component));

	extension_component -> ccm_passivate();
	extension_component -> ccm_remove();
}


void
ExtensionHomeServant::do_finalize_component_incarnation (Components::ExecutorLocator_ptr exec_loc)
{
	Components::ExtensionComponent_ptr extension_component =
		dynamic_cast <Components::ExtensionComponent_ptr> (exec_loc);

	// Should never happen
	assert (! CORBA::is_nil (extension_component));

	extension_component->ccm_activate();
}


void
ExtensionHomeServant::set_server_interceptor_dispatcher(Components::Extension::ServerInterceptorRegistration_ptr server_dispatcher)
{
	server_dispatcher_ = server_dispatcher;
}

void
ExtensionHomeServant::set_client_interceptor_dispatcher(Components::Extension::ClientInterceptorRegistration_ptr client_dispatcher)
{
	client_dispatcher_ = client_dispatcher;
}

} // namespace Qedo

#endif //_QEDO_NO_QOS
