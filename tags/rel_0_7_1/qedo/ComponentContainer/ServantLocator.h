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

#ifndef __SERVANT_LOCATOR_H__
#define __SERVANT_LOCATOR_H__

#include <CORBA.h>
#include "ServantBase.h"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class HomeServantBase;


/**
 * servant locator
 */
class ServantLocator : public PortableServer::ServantLocator
					 , public RefCountLocalObject
{
private:
	/** the home servant */
	HomeServantBase* home_servant_;
#ifndef _QEDO_NO_QOS
	Components::Extension::ServerContainerInterceptor_var server_interceptor_;
	PortableServer::ObjectId_var oid_;
#endif

public:
	/**
	 * constructor
	 * \param home_servant The servant for the home.
	 */
	ServantLocator (HomeServantBase* home_servant);

	/**
	 * destructor
	 */
	~ServantLocator();

	/**
	 * implements PortableServer/ServantLocator/preinvoke
	 * provide the servant for a new request
	 * calls an operation on the home servant
	 * \param oid The object id of the target.
	 * \param adapter The used poa.
	 * \param operation The operation name.
	 * \param the_cookie The cookie.
	 * \return The servant to handle the request.
	*/
	PortableServer::Servant preinvoke (
		const PortableServer::ObjectId& oid,
		PortableServer::POA_ptr adapter,
		const char* operation,
		PortableServer::ServantLocator::Cookie& the_cookie )
        throw ( PortableServer::ForwardRequest, CORBA::SystemException );

	/**
	 * implements PortableServer/ServantLocator/postinvoke
	 * called after request processing
	 * \param oid The object id of the target.
	 * \param adapter The used poa.
	 * \param operation The operation name.
	 * \param the_cookie The cookie.
	 * \param the_servant The servant which processed the request.
	 */
	void postinvoke (
		const PortableServer::ObjectId& oid,
		PortableServer::POA_ptr adapter,
	    const char* operation,
	    PortableServer::ServantLocator::Cookie the_cookie,
		PortableServer::Servant the_servant )
        throw ( CORBA::SystemException );
#ifndef _QEDO_NO_QOS

	void register_interceptor(Components::Extension::ServerContainerInterceptor_ptr interceptor);

	void register_interceptor_with_oid(Components::Extension::ServerContainerInterceptor_ptr interceptor, PortableServer::ObjectId* oid);

#endif
};

/** @} */

} // namespace Qedo

#endif
