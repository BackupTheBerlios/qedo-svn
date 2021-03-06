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

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "Synchronisation.h"
#include <Util.h>

#ifdef _WIN32
#include <process.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif
#include <iostream>

namespace Qedo {
	extern CONTAINERDLL_API QedoMutex* container_mutex;
}

#define SYNC_WITH_CONTAINER  \
Qedo::QedoLock output (Qedo::container_mutex);

#define NORMAL_OUT(x) \
{ \
	SYNC_WITH_CONTAINER \
	std::cout << x << std::endl; \
}


#define NORMAL_OUT2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	std::cout << x << y << std::endl; \
}


#define NORMAL_OUT3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	std::cout << x << y << z << std::endl; \
}


#define NORMAL_ERR(x) \
{ \
	SYNC_WITH_CONTAINER \
	std::cerr << "???" << x << std::endl; \
}


#define NORMAL_ERR2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	std::cerr << "???" << x << y << std::endl; \
}


#define NORMAL_ERR3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	std::cerr << "???" << x << y << z << std::endl; \
}


#ifdef _DEBUG
// Debug stuff
#define DEBUG_OUT(x) \
{ \
	SYNC_WITH_CONTAINER \
	std::cout << x << std::endl; \
}


#define DEBUG_OUT2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	std::cout << x << y << std::endl; \
}


#define DEBUG_OUT3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	std::cout << x << y << z << std::endl; \
}
#else

// no Debug output
#define DEBUG_OUT(x) \
{ \
}


#define DEBUG_OUT2(x,y) \
{ \
}


#define DEBUG_OUT3(x,y,z) \
{ \
}
#endif
//} // namespace Qedo
 
#endif
