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

#ifndef __SESSION_CONTEXT_H__
#define __SESSION_CONTEXT_H__

#include <CORBA.h>
#include <Components.h>
#include "CCMContext.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * the session context
 */
class CONTAINERDLL_API SessionContext : public virtual Components::SessionContext,
										public virtual ExecutorContext
{
public:
	/**
	 * constructor
	 */
	SessionContext();

	/**
	 * destructor
	 */
	~SessionContext();

    /**
	 * implements IDL:omg.org/Components/SessionContext/get_CCM_object:1.0
	 * provide the reference to the CCMObject of the component
	 * delegated to the object executor
	 * \return The object reference of the component.
	 */
    CORBA::Object_ptr get_CCM_object();

    /**
	 * implements IDL:omg.org/Components/CCMContext/get_caller_principal:1.0
	 * not implemented
	 */
	Components::Principal get_caller_principal();

    /**
	 * implements IDL:omg.org/Components/CCMContext/get_CCM_home:1.0
	 * provide the home of the component
	 * \return The object reference of the component home.
	 */
	Components::CCMHome_ptr get_CCM_home();

    /**
	 * implements IDL:omg.org/Components/CCMContext/get_rollback_only:1.0
	 * not implemented
	 */
    CORBA::Boolean get_rollback_only()
		throw (Components::IllegalState);

    /**
	 * implements IDL:omg.org/Components/CCMContext/get_user_transaction:1.0
	 * not implemented
	 */
    Components::Transaction::UserTransaction_ptr get_user_transaction()
		throw (Components::IllegalState);

    /**
	 * implements IDL:omg.org/Components/CCMContext/is_caller_in_role:1.0
	 * not implemented
	 */
    CORBA::Boolean is_caller_in_role(const char* role);

    /**
	 * implements IDL:omg.org/Components/CCMContext/set_rollback_only:1.0
	 * not implemented
	 */
    void set_rollback_only()
		throw (Components::IllegalState);
};

/** @} */

} // namespace Qedo

#endif

