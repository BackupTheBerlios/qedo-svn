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

#include "ComponentInstallationImpl.h"
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include <iostream>

static char rcsid[] UNUSED = "$Id: qci.cpp,v 1.13 2003/07/24 13:14:54 boehme Exp $";


/**
 * @addtogroup ComponentInstaller
 * @{
 */


/**
 * the Qedo directory
 */
namespace Qedo {
std::string g_qedo_dir;
};


/**
 * starts the server for the component installer object
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Component Installer" << std::endl;

#ifdef _WIN32
	TCHAR tchBuffer[256];
	LPTSTR lpszSystemInfo = tchBuffer;
	DWORD dwResult = ExpandEnvironmentStrings("%QEDO%", lpszSystemInfo, 256);
	Qedo::g_qedo_dir.append(lpszSystemInfo);
#else
	char *e = getenv("QEDO");
	if(e) {
	    Qedo::g_qedo_dir.append(e);
	} else {
	    std::cout << "Missing Environment Variable QEDO" << std::endl;
	    std::cout << "Assuming curretn dir as local deployment dir" << std::endl; 
	    Qedo::g_qedo_dir.append("./");
	};
	
#endif

	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	Qedo::ComponentInstallationImpl* component_installation = new Qedo::ComponentInstallationImpl (orb);

	try
	{
		component_installation->initialize();
	}
	catch (Qedo::ComponentInstallationImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Component Installer... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}

	orb->run();
	return 0;
}

/** @} */
