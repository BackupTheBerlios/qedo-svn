/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

#ifndef __SERVANT_LOCATOR_H__
#define __SERVANT_LOCATOR_H__

#include <OB/CORBA.h>

#include "ServantBase.h"

namespace Qedo {

class HomeServantBase;

class ServantLocator : public PortableServer::ServantLocator,
					   public RefCountLocalObject
{
private:
	HomeServantBase* home_servant_;

public:
	ServantLocator (HomeServantBase*);
	~ServantLocator();

	PortableServer::Servant preinvoke ( 
		const PortableServer::ObjectId& oid,
		PortableServer::POA_ptr adapter,
		const char* operation,
		PortableServer::ServantLocator::Cookie& the_cookie )
        throw ( PortableServer::ForwardRequest, CORBA::SystemException );

	void postinvoke ( 
		const PortableServer::ObjectId& oid,
		PortableServer::POA_ptr adapter,
	    const char* operation,
	    PortableServer::ServantLocator::Cookie the_cookie,
		PortableServer::Servant the_servant )
        throw ( CORBA::SystemException );
};

} // namespace Qedo

#endif

