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

#include <OB/CORBA.h>
#include "Components.h"

#include "CCMContext.h"
#include "HomeServantBase.h"
#include "Util.h"

namespace Qedo {

class CONTAINERDLL_API ComponentInstance
{
public:
	PortableServer::ObjectId_var object_id_;
	CORBA::Object_var component_ref_;
	Components::ExecutorLocator_var executor_locator_;
	Qedo::CCMObjectExecutor* ccm_object_executor_;

	ComponentInstance (const PortableServer::ObjectId&, 
					   CORBA::Object_ptr, 
					   Components::ExecutorLocator_ptr,
					   ExecutorContext*,
					   HomeServantBase*);
	ComponentInstance();
	ComponentInstance (const ComponentInstance&);
	ComponentInstance& operator= (const ComponentInstance&);
	~ComponentInstance();

	CORBA::Object_ptr component_ref();
};

} // namespace Qedo

#endif

