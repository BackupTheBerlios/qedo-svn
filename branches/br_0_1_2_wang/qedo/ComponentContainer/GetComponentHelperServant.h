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

#ifndef __GET_COMPONENT_HELPER_SERVANT_H__
#define __GET_COMPONENT_HELPER_SERVANT_H__

#include <CORBA.h>

#include "QedoComponents_skel.h"
#include "Util.h"

namespace Qedo
{

class GetComponentHelperServant : public virtual POA_Qedo_Components::GetComponentHelper,
								  public virtual PortableServer::RefCountServantBase
{
private:
	Components::CCMObject_var ccm_object_;

public:
	GetComponentHelperServant (Components::CCMObject_ptr);
	~GetComponentHelperServant();

    //
    // IDL:Qedo_Components/GetComponentHelper/get_component:1.0
    //
    Components::CCMObject_ptr get_component()
		throw(CORBA::SystemException);
};


} // namespace Qedo


#endif