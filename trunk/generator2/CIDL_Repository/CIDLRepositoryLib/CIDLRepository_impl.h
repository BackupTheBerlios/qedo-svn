/*****************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                    */
/*                                                                           */
/* Copyright (c) 2002 by the Qedo Team                                       */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */ 
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/

#ifndef __CIDL_REPOSITORY_IMPL_H__
#define __CIDL_REPOSITORY_IMPL_H__

#include <CORBA.h>
#include "CIDL_Extension_skel.h"
#include "ComponentRepository_impl.h"

namespace QEDO_ComponentRepository {

class CIDLRepository_impl : public virtual POA_CIDL::CIDLRepository,
								public virtual ComponentRepository_impl
{
public:
	CIDLRepository_impl ( CORBA::ORB_ptr orb, PortableServer::POA_ptr poa );
	
	~CIDLRepository_impl ();

	virtual void destroy_repository();

    //
    // IDL:omg.org/CIDL/CIDLRepository/create_composition:1.0
    //
    virtual CIDL::CompositionDef_ptr create_composition(const char* id,
                                                        const char* name,
                                                        const char* version,
                                                        CIDL::LifecycleCategory lifecycle,
                                                        IR__::HomeDef_ptr home)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

