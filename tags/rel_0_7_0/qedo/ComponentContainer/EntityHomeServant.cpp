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

#include "EntityHomeServant.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: EntityHomeServant.cpp,v 1.6 2004/05/13 13:01:57 hao Exp $";


namespace Qedo {


EntityHomeServant::EntityHomeServant()
{
}


EntityHomeServant::EntityHomeServant (const EntityHomeServant& entity_home)
: HomeServantBase (entity_home),
  CCMHomeServant (entity_home)
{
}


EntityHomeServant& EntityHomeServant::operator= (const EntityHomeServant& entity_home)
{
	return *this;
}


EntityHomeServant::~EntityHomeServant()
{
	DEBUG_OUT ("EntityHomeServant: Destructor called");
}


void 
EntityHomeServant::before_remove_component (Components::ExecutorLocator_ptr exec_loc)
{
	Components::EntityComponent_ptr entity_component = 
		dynamic_cast <Components::EntityComponent_ptr> (exec_loc);

	// Should never happen
	assert (! CORBA::is_nil (entity_component));

	entity_component->ccm_store();
	entity_component->ccm_passivate();
	entity_component->ccm_remove();
}


void 
EntityHomeServant::do_finalize_component_incarnation (Components::ExecutorLocator_ptr exec_loc)
{
	Components::EntityComponent_ptr entity_component = 
		dynamic_cast <Components::EntityComponent_ptr> (exec_loc);

	// Should never happen
	assert (! CORBA::is_nil (entity_component));

	entity_component->ccm_activate();
}

} // namespace Qedo
