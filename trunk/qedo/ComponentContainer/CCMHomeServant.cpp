/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

static char rcsid[] = "$Id: CCMHomeServant.cpp,v 1.4 2002/12/03 07:48:58 stoinski Exp $";

#include "CCMHomeServant.h"
#include "Output.h"

namespace Qedo {

CCMHomeServant::CCMHomeServant()
{
}


CCMHomeServant::CCMHomeServant (const CCMHomeServant& ccm_home)
: HomeServantBase (ccm_home)
{
}


CCMHomeServant& CCMHomeServant::operator= (const CCMHomeServant& ccm_home)
{
	return *this;
}


CCMHomeServant::~CCMHomeServant()
{
	DEBUG_OUT ("CCMHomeServant: Destructor called");
}


CORBA::IRObject_ptr 
CCMHomeServant::get_component_def()
throw (CORBA::SystemException)
{
	return 0;
}


CORBA::IRObject_ptr 
CCMHomeServant::get_home_def()
throw (CORBA::SystemException)
{
	return 0;
}


void 
CCMHomeServant::remove_component (Components::CCMObject_ptr obj)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	DEBUG_OUT ("CCMHomeServant:: remove_component() called");

	// Kick this component out of the home
	PortableServer::ObjectId_var object_id = this->reference_to_oid (obj);

	this->remove_component_with_oid (object_id);
}


Components::CCMObjects* 
CCMHomeServant::get_instances()
{
	DEBUG_OUT ("CCMHomeServant:: get_instances() called");

	Components::CCMObjects_var instances = new Components::CCMObjects();
	instances->length (this->component_instances_.size());

	for (unsigned int i = 0; i < this->component_instances_.size(); i++)
	{
		instances[i] = Components::CCMObject::_narrow(this->component_instances_[i].component_ref_);
	}

	return instances._retn();
}

} // namespace Qedo

