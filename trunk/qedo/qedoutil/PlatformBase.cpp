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

static char rcsid[] = "$Id: PlatformBase.cpp,v 1.3 2002/12/03 07:57:46 stoinski Exp $";


#include "PlatformBase.h"

#ifndef _WIN32
#include <time.h>
#include <Shellapi.h>
#else 
//#include <process.h>
#endif


namespace Qedo {


/**
 *
 */
PlatformBase::PlatformBase ()
{
}


/**
 *
 */
PlatformBase::~PlatformBase ()
{
}


/**
 *
 */
std::string 
PlatformBase::getCurrentDirectory () 
{
    char path[1024];
#ifdef _WIN32
    ::GetCurrentDirectory(1024, path);
#else
    if(!getcwd(path,1023))
    {
        perror("css");
        assert(0);
    }
#endif
    return std::string(path);
}


/**
 *
 */
int
PlatformBase::makeDir (std::string dir)
{
	if (checkExistence(dir, IS_FILE)) 
	{ 
        return 1;
	}

	if (checkExistence(dir, DIRECTORY)) 
	{ 
        return 0;
	}

	std::string::size_type pos = dir.find_last_of("/\\");
	int err = makeDir(dir.substr(0, pos));
	if(err)
	{
		return err;
	}

#ifdef _WIN32
	DWORD dw;
	if( !CreateDirectory(dir.c_str(), NULL))
	{
		dw = GetLastError();
		std::cerr << "Problem creating the directory " << dir << std::endl;
		return 2;
	}
#else
	int err = mkdir(dir.c_str(), 0755);
	if(err)
	{
		std::cerr << "Problem creating the directory " << dir << std::endl;
		return 2;
	}
#endif

	return 0;
}


/**
 *
 */
int 
PlatformBase::removeFileOrDirectory(std::string object) 
{
	// if the last symbol is a delimiter, remove it
	std::string object_name = object;
#ifdef _WINDOWS
	if (object_name[object_name.size() - 1] == '\\')
#else
	if (object_name[object_name.size() - 1] == '/')
#endif
	{
		object_name.erase(object_name.size() - 1, 1);
	}
    
    //
    // check whether the object exists
    //
    if (checkExistence(object_name, DIRECTORY_OR_FILE)) 
	{
#ifdef _WIN32
        char dummy[256];
        strcpy(dummy, object_name.c_str());
        dummy[strlen(dummy) + 1] = '\0';

        SHFILEOPSTRUCT fileOp;
        fileOp.hwnd = NULL;
        fileOp.wFunc = FO_DELETE;
        fileOp.pFrom = dummy;
        fileOp.pTo = NULL;
        fileOp.fFlags = FOF_NOCONFIRMATION;
        int error =  SHFileOperation(&fileOp);
        if (error)
        {
            return 1;
        }
#else
		std::string command = std::string("\\rm -rf ") + object_name;
		system(command.c_str());
#endif
		return 0;
	}

    // no such object
    return 1;
}


/**
 *
 */
bool 
PlatformBase::checkExistence(std::string object, int type)
{
#ifdef _WIN32
	std::string::size_type pos = object.find_first_of("/");
	while (pos != std::string::npos)
    {
        object.replace(pos, 1, "\\");
        pos = object.find_first_of("/");
    }
	// if the last symbol is a delimiter, remove it
	char* object_name = strdup(object.c_str());
	if ((strlen(object_name)) && (object_name[strlen(object_name) - 1] == '\\'))
#else
	// if the last symbol is a delimiter, remove it
	char* object_name = strdup(object.c_str());
	if ((strlen(object_name)) && (object_name[strlen(object_name) - 1] == '/' ))
#endif
	{
		object_name[strlen(object_name) - 1] = '\0';
	}
	
	struct stat statbuff;
	int rt = stat(object_name, &statbuff);
	free(object_name);

	// No object with this pathname exists.
	if  (rt < 0)
	{
		return false; 
	}
	
	if (type == DIRECTORY_OR_FILE)
	{
		return true;
	}
	
	if ((type == DIRECTORY) && ((statbuff.st_mode & S_IFMT) == S_IFDIR))
	{
		return true;
	}
		
	if ((type == IS_FILE) && ((statbuff.st_mode & S_IFMT) == S_IFREG))
	{
		return true; 
	}
    
	return false;
}


/**
 *
 */
std::string
PlatformBase::getPath(std::string path)
{
    std::string new_path = path;

    // insert delimiter
#ifdef _WIN32
	if (new_path[new_path.length() - 1] != '\\')
	{
		return new_path.append("\\");
	}
#else
	if (new_path[new_path.length() - 1] != '/')
	{
		return new_path.append("/");
	}
#endif
	return path;
}

}