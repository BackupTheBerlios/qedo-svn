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

#include "EntityContext.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: EntityContext.cpp,v 1.2 2004/05/13 13:01:57 hao Exp $";


namespace Qedo {
	

EntityContext::EntityContext()
{
}


EntityContext::~EntityContext()
{
	DEBUG_OUT ( "EntityContext: Destructor called" );
}


CORBA::Object_ptr 
EntityContext::get_CCM_object()
{
	return ccm_object_executor_->get_component();
}

Components::PrimaryKeyBase* 
EntityContext::get_primary_key()
{
	std::cout << "EntityContext::get_primary_key()\n";
	return ccm_object_executor_->get_primary_key();
    //Components::PrimaryKeyBase* pkb_ = 0;
    //return pkb_;
}


} // namepscae Qedo
