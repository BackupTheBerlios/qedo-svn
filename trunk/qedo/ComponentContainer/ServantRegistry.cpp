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

static char rcsid[] = "$Id: ServantRegistry.cpp,v 1.7 2003/04/03 09:08:08 tom Exp $";

#include "GlobalHelpers.h"
#include "ServantRegistry.h"
#include "Output.h"


namespace Qedo {


ServantEntry::ServantEntry (const PortableServer::ObjectId& object_id, Qedo::ServantBase* servant)
: object_id_ (new PortableServer::ObjectId (object_id)),
  servant_ (servant)
{
	servant_->_add_ref();
}


ServantEntry::ServantEntry()
{
}


ServantEntry::ServantEntry (const ServantEntry& servant_entry)
: object_id_ (new PortableServer::ObjectId (servant_entry.object_id_)),
  servant_ (servant_entry.servant_)
{
	servant_->_add_ref();
}


ServantEntry& 
ServantEntry::operator= (const ServantEntry& servant_entry)
{
	object_id_ = new PortableServer::ObjectId (servant_entry.object_id_);
	
	if (servant_)
		servant_->_remove_ref();

	servant_ = servant_entry.servant_;
	servant_->_add_ref();

	return *this;
}


ServantEntry::~ServantEntry()
{
	DEBUG_OUT ("ServantEntry: Destructor called");

	servant_->_remove_ref();
}


ServantFactoryEntry::ServantFactoryEntry (const PortableServer::ObjectId& object_id, 
										  Qedo::ServantFactory* servant_factory)
: object_id_ (new PortableServer::ObjectId (object_id)),
  servant_factory_ (servant_factory)
{
	servant_factory_->_add_ref();
}


ServantFactoryEntry::ServantFactoryEntry()
{
}


ServantFactoryEntry::ServantFactoryEntry (const ServantFactoryEntry& servant_factory_entry)
: object_id_ (new PortableServer::ObjectId (servant_factory_entry.object_id_)),
  servant_factory_ (servant_factory_entry.servant_factory_)
{
	servant_factory_->_add_ref();
}


ServantFactoryEntry& 
ServantFactoryEntry::operator= (const ServantFactoryEntry& servant_factory_entry)
{
	object_id_ = new PortableServer::ObjectId (servant_factory_entry.object_id_);
	
	if (servant_factory_)
		servant_factory_->_remove_ref();

	servant_factory_ = servant_factory_entry.servant_factory_;
	servant_factory_->_add_ref();

	return *this;
}


ServantFactoryEntry::~ServantFactoryEntry()
{
#ifndef TAO_ORB
	DEBUG_OUT2("ServantFactoryEntry: Destructor called for ", object_id_);
#else
	DEBUG_OUT("ServantFactoryEntry: Destructor called for ") 
#endif
	servant_factory_->_remove_ref();
}


ServantRegistry::ServantRegistry()
{
}


ServantRegistry::~ServantRegistry()
{
	DEBUG_OUT ("ServantRegistry: Destructor called");
}


void 
ServantRegistry::register_static_servant (const PortableServer::ObjectId& object_id, Qedo::ServantBase* servant)
{
	ServantEntry new_servant (object_id, servant);

	static_servants_.push_back (new_servant);
}


void 
ServantRegistry::register_servant_factory (const PortableServer::ObjectId& object_id, 
										   Qedo::ServantFactory* servant_factory)
{
	ServantFactoryEntry new_factory (object_id, servant_factory);

	servant_factories_.push_back (new_factory);
}


void 
ServantRegistry::unregister_static_servant (const PortableServer::ObjectId& object_id)
{
	std::vector <ServantEntry>::iterator servants_iter;

	for (servants_iter = static_servants_.begin(); servants_iter != static_servants_.end(); servants_iter++)
	{
		if (Qedo::compare_object_ids ((*servants_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (servants_iter == static_servants_.end())
	{
		return;
	}

	static_servants_.erase (servants_iter);
}


void 
ServantRegistry::unregister_servant_factory (const PortableServer::ObjectId& object_id)
{
	std::vector <ServantFactoryEntry>::iterator servant_factories_iter;

	for (servant_factories_iter = servant_factories_.begin(); 
		 servant_factories_iter != servant_factories_.end(); 
		 servant_factories_iter++)
	{
		if (Qedo::compare_object_ids ((*servant_factories_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (servant_factories_iter == servant_factories_.end())
	{
		return;
	}

	servant_factories_.erase (servant_factories_iter);
}


void 
ServantRegistry::set_variables_static_servant (const PortableServer::ObjectId& object_id,
											   Components::ExecutorLocator_ptr executor_locator,
											   CCMObjectExecutor* ccm_object_executor)
{
	std::vector <ServantEntry>::iterator servants_iter;

	for (servants_iter = static_servants_.begin(); servants_iter != static_servants_.end(); servants_iter++)
	{
		if (Qedo::compare_object_ids ((*servants_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (servants_iter == static_servants_.end())
	{
		return;
	}

	(*servants_iter).servant_->executor_locator (executor_locator);
	(*servants_iter).servant_->ccm_object_executor (ccm_object_executor);
}


Qedo::ServantBase* 
ServantRegistry::lookup_static_servant (const PortableServer::ObjectId& object_id)
{
	std::vector <ServantEntry>::const_iterator servants_iter;

	for (servants_iter = static_servants_.begin(); servants_iter != static_servants_.end(); servants_iter++)
	{
		if (Qedo::compare_object_ids ((*servants_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (servants_iter != static_servants_.end())
	{
		// Static servants have their CCM object executor and executor locator already set, so we
		// can simply return the found servant
		(*servants_iter).servant_->_add_ref();
		return (*servants_iter).servant_;
	}

	return 0;
}


Qedo::ServantBase* 
ServantRegistry::lookup_factory_created_servant (const PortableServer::ObjectId& object_id)
{
	std::vector <ServantFactoryEntry>::const_iterator servant_factories_iter;

	for (servant_factories_iter = servant_factories_.begin(); 
		 servant_factories_iter != servant_factories_.end(); 
		 servant_factories_iter++)
	{
		if (Qedo::compare_object_ids ((*servant_factories_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (servant_factories_iter != servant_factories_.end())
	{
		Qedo::ServantBase* servant = (*servant_factories_iter).servant_factory_->create_servant();
		return servant;
	}

	return 0;
}

} // namespace Qedo
