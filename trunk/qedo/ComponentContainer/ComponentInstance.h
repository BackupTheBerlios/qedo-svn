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
#include "RefCountBase.h"
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
class CONTAINERDLL_API ComponentInstance : public RefCountBase
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


/**
 * a component instance var type
 */
class ComponentInstance_var
{
	/** the component instance */
	ComponentInstance* ptr_;

public:

    ComponentInstance_var() : ptr_(0) { }
    ComponentInstance_var(ComponentInstance* p) : ptr_(p) { assert(p != 0); }
    ComponentInstance_var(const ComponentInstance& r) : ptr_(new ComponentInstance(r)) { }
    ComponentInstance_var(const ComponentInstance_var& r) : ptr_(r.ptr_ ? new ComponentInstance(*r.ptr_) : 0) { }
    ~ComponentInstance_var() { ptr_->_remove_ref(); }

    ComponentInstance_var& operator=(ComponentInstance* p)
	{
		ptr_ ? ptr_->_remove_ref() : 0;
        ptr_ = p;
        return *this;
    }
    ComponentInstance_var& operator=(const ComponentInstance&);
    ComponentInstance_var& operator=(const ComponentInstance_var& r)
	{
        if(r.ptr_ != ptr_)
        {
            ptr_ ? ptr_->_remove_ref() : 0;
            ptr_ = r.ptr_;
            ptr_->_add_ref();
        }
        return *this;
    }

    ComponentInstance* operator->() { assert(ptr_ != 0); return ptr_; }
    const ComponentInstance* operator->() const { assert(ptr_ != 0); return ptr_; }

	operator const ComponentInstance&() const { assert(ptr_ != 0); return *ptr_; }
    operator ComponentInstance&() { assert(ptr_ != 0); return *ptr_; }

	operator ComponentInstance*() const { assert(ptr_ != 0); return ptr_; }
};

/** @} */

} // namespace Qedo

#endif

