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

static char rcsid[] = "$Id: qassf.cpp,v 1.8 2003/07/25 12:29:28 tom Exp $";

#include "AssemblyFactory.h"
#include "Output.h"


/**
 * @addtogroup Assembly
 * @{
 */


/**
 * the Qedo directory
 */
namespace Qedo {
std::string g_qedo_dir;
};


/**
 * start the server for the assembly factory object
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Assembly Factory" << std::endl;

	// get the qedo dir
#ifdef _WIN32
	TCHAR tchBuffer[256];
	LPTSTR lpszSystemInfo = tchBuffer;
	DWORD dwResult = ExpandEnvironmentStrings("%QEDO%", lpszSystemInfo, 256); 
	Qedo::g_qedo_dir.append(lpszSystemInfo);
#else
	char *e = getenv("QEDO");
	if(e) Qedo::g_qedo_dir.append(e);
#endif

	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	//
	// register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/Cookie:1.0", factory);
	factory = new Qedo::ConfigValueFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/ConfigValue:1.0", factory);

	Qedo::AssemblyFactoryImpl* assembly_factory = new Qedo::AssemblyFactoryImpl(orb);

	try
	{
		assembly_factory->initialize();
	}
	catch (Qedo::AssemblyFactoryImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Assembly Factory... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}
	std::cout << "Qedo Assembly Factory Server is up and running ...\n";
	orb->run();
	return 0;
}

/** @} */
