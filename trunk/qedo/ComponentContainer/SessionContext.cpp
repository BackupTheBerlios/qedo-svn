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

static char rcsid[] = "$Id: SessionContext.cpp,v 1.4 2002/12/03 07:57:46 stoinski Exp $";

#include "SessionContext.h"
#include "Output.h"

namespace Qedo {
	
SessionContext::SessionContext()
{
}


SessionContext::~SessionContext()
{
	DEBUG_OUT ( "SessionContext: Destructor called" );
}


CORBA::Object_ptr 
SessionContext::get_CCM_object()
{
	return ccm_object_executor_->get_component();
}


Components::Principal 
SessionContext::get_caller_principal()
{
	return 0;
}

 
Components::CCMHome_ptr 
SessionContext::get_CCM_home()
{
	DEBUG_OUT ("SessionContext: get_CCM_Home() called");
	return Components::CCMHome::_nil();
}


CORBA::Boolean 
SessionContext::get_rollback_only()
throw (Components::IllegalState)
{
	return 0;
}


Components::Transaction::UserTransaction_ptr 
SessionContext::get_user_transaction()
throw (Components::IllegalState)
{
	return 0;
}


CORBA::Boolean 
SessionContext::is_caller_in_role (const char* role)
{
	return 0;
}

 
void 
SessionContext::set_rollback_only()
throw (Components::IllegalState)
{
}

} // namepscae Qedo

