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

#include "qedoutil.h"
#include "Output.h"

#ifndef _WIN32
#include <sys/fcntl.h>
#include <dlfcn.h>
#endif


static char rcsid[] UNUSED = "$Id: qedoutil.cpp,v 1.3 2003/09/29 17:00:07 neubauer Exp $";


namespace Qedo {

std::string
getEnvironment(std::string name)
{
	std::string val;
#ifdef _WIN32
	TCHAR tchBuffer[256];
	LPTSTR lpszSystemInfo = tchBuffer;
	DWORD dwResult = ExpandEnvironmentStrings( (std::string("%") + name + "%").c_str(), lpszSystemInfo, 256 );
	val.append(lpszSystemInfo);
#else
	char *e = getenv( name.c_str() );
	if(e)
	{
	    val.append(e);
	}
#endif
	return val;
}


std::string 
getCurrentDirectory() 
{
    char path[1024];
#ifdef _WIN32
    GetCurrentDirectory(1024, path);
#else
    if(!getcwd(path,1023))
    {
        perror("css");
        assert(0);
    }
#endif
    return std::string(path);
}


int 
copyFile(std::string src, std::string dst)
{
#ifdef _WIN32
	return CopyFile(src.c_str(), dst.c_str(), false);
#else
	int buf[1024];
	size_t bytes_read,bytes_write,delta;
	int source, dest;

	source = open(src.c_str(), O_RDONLY, 0);
	if(source == -1) 
	{
		perror("open");
		return 0;
	}
	dest = creat(dst.c_str(), 0700);   /* stat first to prevent overwriting existing */
	if(dest == -1) 
	{
		perror("creat");
		close(source);
		return 0;
	}

	while((bytes_read= read(source, buf, 1024)) > 0) 
	{
		if(bytes_read==-1)
		{
			perror("read");
			close(source);
			close(dest);
			unlink(dst.c_str());
			return 0;
		}
		bytes_write = 0;
		while(bytes_read>bytes_write)
		{
			delta = write(dest, buf+bytes_write, bytes_read-bytes_write);
			if(delta==-1)
			{
				perror("write");
				close(source);
				close(dest);
				unlink(dst.c_str());
				return 0;
			}
			bytes_write += delta;
		}
	}

	close(dest);
	close(source);
	return 1;
#endif
}


int 
moveFile(std::string source, std::string dest)
{
	return rename( source.c_str(), dest.c_str() );
}


std::string 
getFileName(std::string source)
{
	std::string::size_type pos = source.find_last_of("/\\:");
	if(pos != std::string::npos)
	{
		return source.substr(pos + 1, std::string::npos);
	}
	else
	{
		return source;
	}
}


std::string
getPath(std::string source)
{
    std::string path = source;

    //
	// insert delimiter
	//
#ifdef _WIN32
	if (path[path.length() - 1] != '\\')
	{
		return path.append("\\");
	}
#else
	if (path[path.length() - 1] != '/')
	{
		return path.append("/");
	}
#endif

	return path;
}

}

