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

#include "SessionContext.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: SessionContext.cpp,v 1.7.6.1 2003/09/26 14:32:03 stoinski Exp $";


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


} // namepscae Qedo
