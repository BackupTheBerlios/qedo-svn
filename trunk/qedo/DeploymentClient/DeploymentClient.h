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


#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include "Components.h"
#include "Valuetypes.h"
#include "NameServiceBase.h"
#include <iostream>
#include <fstream>
#include <string>


namespace Qedo {

/**
 *
 */
class DeploymentClient : public virtual NameServiceBase
{
private:
	CORBA::ORB_var									orb_;
	PortableServer::POA_var							root_poa_;
	PortableServer::POAManager_var					root_poa_manager_;
	Components::Deployment::AssemblyFactory_var		assemblyFactory_;

public:
	DeploymentClient (CORBA::ORB_ptr);
	~DeploymentClient();

	// Exceptions
	class CannotInitialize{};

	void initialize() 
		throw (CannotInitialize);

	void create(std::string packageName);
};


}