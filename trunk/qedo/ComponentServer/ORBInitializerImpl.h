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
#include "NameServiceBase.h"
#include "Util.h"


namespace Qedo {


class ORBInitializerImpl : public virtual PortableInterceptor::ORBInitializer,
						   public virtual NameServiceBase,
						   public virtual CORBA::LocalObject
{
public:
	ORBInitializerImpl();
	~ORBInitializerImpl();

	void pre_init (PortableInterceptor::ORBInitInfo_ptr info);
    void post_init (PortableInterceptor::ORBInitInfo_ptr info);
};


} // namespace


#endif
