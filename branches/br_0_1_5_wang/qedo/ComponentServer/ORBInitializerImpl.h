/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

#ifndef __ORB_INITIALIZER_IMPL_H__
#define __ORB_INITIALIZER_IMPL_H__

#include <CORBA.h>
#ifdef MICO_ORB
#include <mico/pi.h>
#else
#include <PortableInterceptor.h>
#endif
#include "QedoComponents_skel.h"

#include "ComponentServerImpl.h"
#include "NameServiceBase.h"
#include "Util.h"


namespace Qedo {


/**
 * \addtogroup ComponentServer
 * @{
 */


/**
 * the orb initializer to register interceptors and HomeFinder
 */
class ORBInitializerImpl : public virtual PortableInterceptor::ORBInitializer,
						   public virtual NameServiceBase,
						   public virtual CORBA::LocalObject
{
private:
	ComponentServerImpl* comp_server_;
	PortableInterceptor::SlotId slot_id_;
	bool m_enable_qos;
#ifndef _QEDO_NO_QOS
	/** interceptor dispatcher on server side */
	PortableInterceptor::ServerRequestInterceptor_var server_dispatcher_;
	/** interceptor dispatcher on client side */
	PortableInterceptor::ClientRequestInterceptor_var client_dispatcher_;
#endif
public:
	/**
	 * constructor
	 */
	ORBInitializerImpl();

	ORBInitializerImpl(bool enable_qos);

	/**
	 * destructor
	 */
	~ORBInitializerImpl();

	/**
	 * pre_init
	 */
	void pre_init (PortableInterceptor::ORBInitInfo_ptr info);

	/**
	 * post_init
	 */
	void post_init (PortableInterceptor::ORBInitInfo_ptr info);

	/**
	 * slot_id
	 */
	PortableInterceptor::SlotId slot_id();
#ifndef _QEDO_NO_QOS
	/**
	 * set_server_dispatcher
	 */
	void
	set_server_dispatcher (PortableInterceptor::ServerRequestInterceptor_ptr server_dispatcher);

	/**
	 * set_server_dispatcher
	 */
	void
	set_client_dispatcher (PortableInterceptor::ClientRequestInterceptor_ptr client_dispatcher);
#endif
};

/** @} */

} // namespace


#endif
