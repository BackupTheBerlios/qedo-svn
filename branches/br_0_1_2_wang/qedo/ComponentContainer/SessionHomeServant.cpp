/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
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

static char rcsid[] = "$Id: SessionHomeServant.cpp,v 1.4 2003/04/01 07:50:10 neubauer Exp $";

#include "SessionHomeServant.h"
#include "Output.h"


namespace Qedo {


SessionHomeServant::SessionHomeServant()
{
}


SessionHomeServant::SessionHomeServant (const SessionHomeServant& session_home)
: HomeServantBase (session_home),
  CCMHomeServant (session_home)
{
}


SessionHomeServant& SessionHomeServant::operator= (const SessionHomeServant& session_home)
{
	return *this;
}


SessionHomeServant::~SessionHomeServant()
{
	DEBUG_OUT ("SessionHomeServant: Destructor called");
}


void 
SessionHomeServant::before_remove_component (Components::ExecutorLocator_ptr executor_locator)
{
	Components::SessionComponent_ptr session_component = 
		dynamic_cast <Components::SessionComponent_ptr> (executor_locator);

	// Should never happen
	assert (! CORBA::is_nil (session_component));

	session_component->ccm_remove();
}


void 
SessionHomeServant::do_finalize_component_incarnation (Components::ExecutorLocator_ptr exec_loc)
{
	Components::SessionComponent_ptr session_component = 
		dynamic_cast <Components::SessionComponent_ptr> (exec_loc);

	// Should never happen
	assert (! CORBA::is_nil (session_component));

	session_component->ccm_activate();
}

} // namespace Qedo
