/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

#ifndef __PLATFORM_BASE_H__
#define __PLATFORM_BASE_H__


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <string>


#ifndef _WIN32
# include <unistd.h>
# include <utime.h>
#else
# include <direct.h>
# include <io.h>
# include <wtypes.h>
#include <windows.h>
#endif

#define DIRECTORY_OR_FILE 0
#define DIRECTORY         1
#define IS_FILE           2


namespace Qedo {


/**
 *
 */
class PlatformBase
{
protected:
	PlatformBase();

	// Returns the string corresponding to the current directory.
	std::string getCurrentDirectory (); 
	
	// Makes the directory whose pathname is specified by the string parameter.
	// The return value is 1 if the object already exists, 2 if there is a problem creating it and 0 else.
	int makeDir (std::string); 
	
	// checks whether file or directory exists
	bool checkExistence (std::string, int);

	// This function removes the object whose pathname is specified by the string parameter.
	// The returned value is 0 if the object to destroy exists, 1 else.
	int removeFileOrDirectory (std::string); 

    // appends the right path delimiter
	std::string getPath (std::string);

public:
    virtual ~PlatformBase();

};


}

#endif
