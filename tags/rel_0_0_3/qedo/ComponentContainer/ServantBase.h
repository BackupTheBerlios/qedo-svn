/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

#ifndef __SERVANT_BASE_H__
#define __SERVANT_BASE_H__

#include <OB/CORBA.h>
#include "Components_skel.h"

#include "CCMObjectExecutor.h"
#include "Util.h"

namespace Qedo {

class CONTAINERDLL_API ServantBase : public virtual PortableServer::RefCountServantBase
{
protected:
	Components::ExecutorLocator_var executor_locator_;
	CCMObjectExecutor* ccm_object_executor_;
	CORBA::Object_ptr current_executor_;

public:
	ServantBase();
	ServantBase (const ServantBase&);
	ServantBase& operator= (const ServantBase&);
	~ServantBase();

	void current_executor (CORBA::Object_ptr);
	void executor_locator (Components::ExecutorLocator_ptr);
	void ccm_object_executor (CCMObjectExecutor*);
};


class CONTAINERDLL_API PrimaryServant : public virtual POA_Components::CCMObject,
										public ServantBase
{
    //
    // from Navigation
    //
    CORBA::Object_ptr provide_facet (const char* name)
      throw (Components::InvalidName, CORBA::SystemException);

    Components::FacetDescriptions* get_all_facets()
      throw (CORBA::SystemException);

    Components::FacetDescriptions*
    get_named_facets (const Components::NameList& names)
      throw (CORBA::SystemException, Components::InvalidName);

    CORBA::Boolean same_component (CORBA::Object_ptr ref)
      throw (CORBA::SystemException);

    //
    // from Receptacles
    //
    Components::Cookie* connect (const char* name, CORBA::Object_ptr connection)
		throw (Components::InvalidName, 
			   Components::InvalidConnection,
			   Components::AlreadyConnected,
			   Components::ExceededConnectionLimit,
			   CORBA::SystemException );

    void disconnect (const char* name, Components::Cookie* ck)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   Components::CookieRequired,
			   Components::NoConnection,
			   CORBA::SystemException );

    Components::ConnectedDescriptions* get_connections (const char* name)
      throw (Components::InvalidName, CORBA::SystemException);

    Components::ReceptacleDescriptions* get_all_receptacles()
      throw (CORBA::SystemException);

    Components::ReceptacleDescriptions*
    get_named_receptacles (const ::Components::NameList& names)
      throw (Components::InvalidName );

    //
    // from Events
    //
    Components::EventConsumerBase_ptr get_consumer (const char* sink_name)
		throw (Components::InvalidName, CORBA::SystemException);

    Components::Cookie* subscribe (const char* publisher_name,
								   Components::EventConsumerBase_ptr subscriber)
		throw (Components::InvalidName, CORBA::SystemException);

    void unsubscribe (const char* publisher_name, Components::Cookie* ck)
		throw (Components::InvalidName,
			   Components::InvalidConnection,
			   CORBA::SystemException);

    void connect_consumer (const char* emitter_name,
						   Components::EventConsumerBase_ptr consumer)
		throw (Components::InvalidName,
			   Components::AlreadyConnected,
			   CORBA::SystemException );

    Components::EventConsumerBase_ptr disconnect_consumer (const char* source_name)
		throw (Components::InvalidName,
			   Components::NoConnection,
			   CORBA::SystemException);

    Components::ConsumerDescriptions* get_all_consumers()
		throw (CORBA::SystemException);

    Components::ConsumerDescriptions* get_named_consumers (const ::Components::NameList& names)
		throw (Components::InvalidName);

    Components::EmitterDescriptions* get_all_emitters()
		throw (CORBA::SystemException);

    Components::EmitterDescriptions* get_named_emitters (const ::Components::NameList& names)
		throw (Components::InvalidName);

    Components::SubscriberDescriptions* get_all_publishers()
		throw (CORBA::SystemException);

    Components::SubscriberDescriptions* get_named_publishers (const ::Components::NameList& names)
		throw (Components::InvalidName);

    //
    // from CCMObject
    //
    CORBA::IRObject_ptr get_component_def()
		throw (CORBA::SystemException);

    Components::CCMHome_ptr get_ccm_home()
		throw (CORBA::SystemException);

    Components::PrimaryKeyBase* get_primary_key()
		throw (Components::NoKeyAvailable, CORBA::SystemException);

    void configuration_complete()
		throw (Components::InvalidConfiguration, CORBA::SystemException);

    void remove()
		throw (CORBA::SystemException);

    Components::ComponentPortDescription* get_all_ports()
		throw (CORBA::SystemException);
};


class ServantFactory : public RefCountBase
{
public:
	virtual Qedo::ServantBase* create_servant() = 0;
};

} // namespace Qedo

#endif

