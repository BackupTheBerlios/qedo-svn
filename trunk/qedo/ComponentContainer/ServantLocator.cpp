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

static char rcsid[] = "$Id: ServantLocator.cpp,v 1.4 2003/04/01 07:50:10 neubauer Exp $";

#include "HomeServantBase.h"
#include "ServantLocator.h"
#include "Output.h"


namespace Qedo {


ServantLocator::ServantLocator (HomeServantBase* home_servant)
: home_servant_ (home_servant)
{
}


ServantLocator::~ServantLocator()
{
	DEBUG_OUT ("ServantLocator: Destructor called");
}


PortableServer::Servant 
ServantLocator::preinvoke (const PortableServer::ObjectId& oid,
						   PortableServer::POA_ptr adapter,
						   const char* operation,
						   PortableServer::ServantLocator::Cookie& the_cookie )
throw (PortableServer::ForwardRequest, CORBA::SystemException)
{
	return home_servant_->lookup_servant (oid);
}


void 
ServantLocator::postinvoke (const PortableServer::ObjectId& oid,
							PortableServer::POA_ptr adapter,
							const char* operation,
							PortableServer::ServantLocator::Cookie the_cookie,
							PortableServer::Servant the_servant )
throw (CORBA::SystemException)
{
	the_servant->_remove_ref();
}

} // namespace Qedo
