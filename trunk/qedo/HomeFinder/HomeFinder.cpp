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

static char rcsid[] = "$Id: HomeFinder.cpp,v 1.2 2003/02/13 13:41:17 tom Exp $";

#include "HomeFinderImpl.h"
#include "Output.h"
#include <cstring>
#include <string>


/** 
 * \mainpage Home Finder Documentation
 *
 * \section installation
 * The implementation for home finder is installed within the Qedo installation process.
 *
 * \section usage
 * When starting the homefinder executable the HomeFinder implementations starts and registers in the NameService
 * under Qedo/HomeFinder. Thus the ORBInitializer of the ComponentServer implementation can resolve the object
 * and register it with register_initial_reference under "ComponentHomeFinder" as required by the CCM standard.
 * 
 */

int
main (int argc, char** argv)
{
	std::cout << "Qedo Home Finder" << std::endl;

	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	//
	// register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/Cookie:1.0", factory);

	Qedo::HomeFinderImpl* home_finder = new Qedo::HomeFinderImpl(orb);

	try
	{
		home_finder->initialize();
	}
	catch (Qedo::HomeFinderImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Home Finder... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}

	orb->run();
	return 0;
}