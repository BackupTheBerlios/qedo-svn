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

#ifndef __ENTITY_CONTEXT_H__
#define __ENTITY_CONTEXT_H__

#include <CORBA.h>
#include <Components.h>
#include "CCMContext.h"
#include "Util.h"
#include "StorageObject.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * the entity context
 */
class CONTAINERDLL_API EntityContext : public virtual Components::EntityContext,
										public virtual CCMContext
{
public:
	/**
	 * constructor
	 */
	EntityContext();

	/**
	 * destructor
	 */
	~EntityContext();

    /**
	 * implements IDL:omg.org/Components/EntityContext/get_CCM_object:1.0
	 * provide the reference to the CCMObject of the component
	 * delegated to the object executor
	 * \return The object reference of the component.
	 */
    CORBA::Object_ptr get_CCM_object();

	//
    // IDL:omg.org/Components/EntityContext/get_primary_key:1.0
    //
    Components::PrimaryKeyBase* get_primary_key();

	::CosPersistentState::StorageObjectBase get_storage_object();

private:

	CosPersistentState::StorageObjectBase object_;
};

/** @} */

} // namespace Qedo

#endif

