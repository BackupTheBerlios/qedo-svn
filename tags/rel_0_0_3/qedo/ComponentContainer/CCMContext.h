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

#ifndef __CCM_CONTEXT_H__
#define __CCM_CONTEXT_H__

#include <OB/CORBA.h>
#include <Components.h>

#include "CCMObjectExecutor.h"
#include "RefCountBase.h"
#include "Util.h"

namespace Qedo {

class CONTAINERDLL_API CCMContext : public virtual Components::CCMContext,
									public virtual Qedo::RefCountLocalObject
{
public:
	CCMContext();
	~CCMContext();

	//
    // IDL:omg.org/Components/CCMContext/get_caller_principal:1.0
    //
	Components::Principal get_caller_principal();

	//
    // IDL:omg.org/Components/CCMContext/get_CCM_home:1.0
    //
	Components::CCMHome_ptr get_CCM_home();

    //
    // IDL:omg.org/Components/CCMContext/get_rollback_only:1.0
    //
    CORBA::Boolean get_rollback_only()
		throw (Components::IllegalState);

    //
    // IDL:omg.org/Components/CCMContext/get_user_transaction:1.0
    //
    Components::Transaction::UserTransaction_ptr get_user_transaction()
		throw (Components::IllegalState);

    //
    // IDL:omg.org/Components/CCMContext/is_caller_in_role:1.0
    //
    CORBA::Boolean is_caller_in_role (const char* role);

    //
    // IDL:omg.org/Components/CCMContext/set_rollback_only:1.0
    //
    void set_rollback_only()
		throw (Components::IllegalState);
};


class CONTAINERDLL_API ExecutorContext : public virtual CCMContext
{
protected:
	CCMObjectExecutor* ccm_object_executor_;

public:
	ExecutorContext();
	~ExecutorContext();

	void ccm_object_executor (CCMObjectExecutor*);
};

} // namespace Qedo

#endif

