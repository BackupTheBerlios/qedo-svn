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

class ServantEntry
{
public:
	PortableServer::ObjectId_var object_id_;
	Qedo::ServantBase* servant_;

	ServantEntry (const PortableServer::ObjectId&, Qedo::ServantBase*);
	ServantEntry();
	ServantEntry (const ServantEntry&);
	ServantEntry& operator= (const ServantEntry&);
	~ServantEntry();
};


class ServantFactoryEntry
{
public:
	PortableServer::ObjectId_var object_id_;
	Qedo::ServantFactory* servant_factory_;

	ServantFactoryEntry (const PortableServer::ObjectId&, Qedo::ServantFactory*);
	ServantFactoryEntry();
	ServantFactoryEntry (const ServantFactoryEntry&);
	ServantFactoryEntry& operator= (const ServantFactoryEntry&);
	~ServantFactoryEntry();
};


class CONTAINERDLL_API ServantRegistry : public RefCountBase
{
private:
	std::vector <ServantEntry> static_servants_;
	std::vector <ServantFactoryEntry> servant_factories_;

public:
	ServantRegistry();
	~ServantRegistry();

	void register_static_servant (const PortableServer::ObjectId&, Qedo::ServantBase*);
	void unregister_static_servant (const PortableServer::ObjectId&);
	void register_servant_factory (const PortableServer::ObjectId&, Qedo::ServantFactory*);
	void unregister_servant_factory (const PortableServer::ObjectId&);
	void set_variables_static_servant (const PortableServer::ObjectId&,
									   Components::ExecutorLocator_ptr,
									   CCMObjectExecutor*);

	Qedo::ServantBase* lookup_static_servant (const PortableServer::ObjectId&);
	Qedo::ServantBase* lookup_factory_created_servant (const PortableServer::ObjectId&);
};

} // namespace Qedo

#endif

