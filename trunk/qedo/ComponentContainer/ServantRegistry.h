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

#ifndef __SERVANT_REGISTRY_H__
#define __SERVANT_REGISTRY_H__

#include <CORBA.h>
#include "RefCountBase.h"
#include "ServantBase.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * entry in a list of servants
 */
class ServantEntry
{
public:
	/** the object id of the servant */
	PortableServer::ObjectId_var object_id_;

	/** the servant */
	Qedo::ServantBase* servant_;

	/**
	 * constructor
	 * \param object_id The object id of the object.
	 * \param servant The servant for the object.
	 */
	ServantEntry (const PortableServer::ObjectId& object_id, Qedo::ServantBase* servant);

	/**
	 * constructor
	 */
	ServantEntry();

	/**
	 * copy constructor
	 */
	ServantEntry (const ServantEntry&);

	/**
	 * assignment operator
	 */
	ServantEntry& operator= (const ServantEntry&);

	/**
	 * destructor
	 */
	~ServantEntry();
};


/**
 * entry in a list of servant factories
 */
class ServantFactoryEntry
{
public:
	/** the object id of the servant factory */
	PortableServer::ObjectId_var object_id_;

	/** the servant factory */
	Qedo::ServantFactory* servant_factory_;

	/**
	 * constructor
	 * \param object_id The object id.
	 * \param servant_factory The servant factory.
	 */
	ServantFactoryEntry (const PortableServer::ObjectId& object_id, Qedo::ServantFactory* servant_factory);

	/**
	 * constructor
	 */
	ServantFactoryEntry();

	/**
	 * copy constructor
	 */
	ServantFactoryEntry (const ServantFactoryEntry&);

	/**
	 * assignment operator
	 */
	ServantFactoryEntry& operator= (const ServantFactoryEntry&);

	/**
	 * destructor
	 */
	~ServantFactoryEntry();
};


/**
 * the registry for servants and servant factories
 */
class CONTAINERDLL_API ServantRegistry : public RefCountBase
{
private:
	/** the list of servants */
	std::vector <ServantEntry> static_servants_;

	/** the list of servant factories */
	std::vector <ServantFactoryEntry> servant_factories_;

public:
	/**
	 * constructor
	 */
	ServantRegistry();

	/**
	 * destructor
	 */
	~ServantRegistry();

	/**
	 * register a servant
	 * \param object_id The object id.
	 * \param servant The servant.
	 */
	void register_static_servant (const PortableServer::ObjectId& object_id, Qedo::ServantBase* servant);

	/**
	 * unregister a servant
	 * \param object_id The object id for which the servant has to be unregistered.
	 */
	void unregister_static_servant (const PortableServer::ObjectId& object_id);

	/**
	 * register a servant factory
	 * \param object_id The object id.
	 * \param servant_factory The servant factory.
	 */
	void register_servant_factory (const PortableServer::ObjectId& object_id, Qedo::ServantFactory* servant_factory);

	/**
	 * unregister a servant factory
	 * \param object_id The object id of the servant factory object.
	 */
	void unregister_servant_factory (const PortableServer::ObjectId& object_id);

	/**
	 * bla
	 */
	void set_variables_static_servant (const PortableServer::ObjectId&,
									   Components::ExecutorLocator_ptr,
									   CCMObjectExecutor*);

	/**
	 * lookup a servant
	 * \param object_id The object id of an object.
	 * \return The servant for the given object.
	 */
	Qedo::ServantBase* lookup_static_servant (const PortableServer::ObjectId& object_id);

	/**
	 * create a servant
	 * \param object_id The object id of an object.
	 * \return The factory created servant.
	 */
	Qedo::ServantBase* lookup_factory_created_servant (const PortableServer::ObjectId& object_id);
};

/** @} */

} // namespace Qedo

#endif
