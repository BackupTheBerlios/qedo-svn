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

#ifndef __COMPONENT_INSTANCE_H__
#define __COMPONENT_INSTANCE_H__

#include <CORBA.h>
#include "Components.h"
#include "CCMContext.h"
#include "HomeServantBase.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class ExecutorContext;


/**
 * a component instance
 */
class CONTAINERDLL_API ComponentInstance
{
public:
	/** object id of the component */
	PortableServer::ObjectId_var		object_id_;
	/** object reference of the component */
	CORBA::Object_var					component_ref_;
	/** executor locator of the component */
	Components::ExecutorLocator_var		executor_locator_;
	/** generic executor */
	Qedo::CCMObjectExecutor*			ccm_object_executor_;

	/**
	 * constructor
	 * \param object_id
	 * \param component_ref
	 * \param executor_locator
	 * \param executor_context
	 * \param home_servant
	 */
	ComponentInstance (const PortableServer::ObjectId& object_id, 
					   CORBA::Object_ptr component_ref, 
					   Components::ExecutorLocator_ptr executor_locator,
					   ExecutorContext* executor_context,
					   HomeServantBase* home_servant);

	/**
	 * constructor
	 */
	ComponentInstance();

	/**
	 * copy constructor
	 */
	ComponentInstance (const ComponentInstance&);

	/**
	 * assignment operator
	 */
	ComponentInstance& operator= (const ComponentInstance&);

	/**
	 * destructor
	 */
	~ComponentInstance();

	/**
	 * provides the object reference of the component
	 * \return The object reference of the component.
	 */
	CORBA::Object_ptr component_ref();
};

/** @} */

} // namespace Qedo

#endif

