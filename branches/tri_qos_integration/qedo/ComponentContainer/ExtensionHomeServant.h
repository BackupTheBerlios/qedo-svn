/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2003 by the Qedo Team                                */
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

#ifndef __EXTENSION_HOME_SERVANT_H__
#define __EXTENSION_HOME_SERVANT_H__

#include "CCMHomeServant.h"
#include "Util.h"
#include "ServerInterceptorDispatcher.h"
#include "ClientInterceptorDispatcher.h"

namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * the servant for extension homes
 */
class CONTAINERDLL_API ExtensionHomeServant : public CCMHomeServant
{
protected:
	/** reference to server interceptor dispatcher interface */
	Components::Extension::ServerInterceptorRegistration_var  server_dispatcher_;

	/** reference to server interceptor dispatcher interface */
	Components::Extension::ClientInterceptorRegistration_var client_dispatcher_;
	
private:
	/**
	 * indicate removal
	 * \param executor_locator The executor locator of the component instance to be removed.
	 */
	void before_remove_component (Components::ExecutorLocator_ptr executor_locator);

	/**
	 * finalize the component incarnation
	 * \param exec_loc The executor locator of the component instance to be incarnated.
	 */
	void do_finalize_component_incarnation (Components::ExecutorLocator_ptr exec_loc);

public:
	/**
	 * constructor
	 */
	ExtensionHomeServant ();

	/**
	 * copy constructor
	 */
	ExtensionHomeServant (const ExtensionHomeServant&);

	/**
	 * assignment operator
	 */
	ExtensionHomeServant& operator= (const ExtensionHomeServant&);

	/**
	 * destructor
	 */
	~ExtensionHomeServant();

	/**
	 * set the server interceptor dispatcher interface at the home
	 */
	void set_server_interceptor_dispatcher(Components::Extension::ServerInterceptorRegistration_ptr server_dispatcher);

	/**
	 * set the client interceptor dispatcher interface at the home
	 */
	void set_client_interceptor_dispatcher(Components::Extension::ClientInterceptorRegistration_ptr client_dispatcher);

};

/** @} */

} // namespace Qedo

#endif

