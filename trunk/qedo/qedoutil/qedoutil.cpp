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


static char rcsid[] UNUSED = "$Id: qedoutil.cpp,v 1.2 2003/09/29 14:50:11 boehme Exp $";


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


#ifdef _WIN32

HINSTANCE 
load_shared_library (const char* name, const char* dir)
{
	HINSTANCE handle_lib;

	handle_lib = LoadLibrary (name);

	if (handle_lib < (HINSTANCE)HINSTANCE_ERROR)
	{
		// Unable to load DLL
		LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf, 0, NULL);
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot load dynamic library: ", (LPCTSTR)lpMsgBuf);
		
		// Free the buffer.
		LocalFree( lpMsgBuf );
		handle_lib = 0;
	}

	return handle_lib;
}

void
unload_shared_library (HINSTANCE handle)
{
	if (! FreeLibrary (handle))
	{
		LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf, 0, NULL);
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot unload dynamic library: ", (LPCTSTR)lpMsgBuf);	
	}
}

#else

void* 
load_shared_library (const char* name, const char* dir)
{

	void * handle_lib;
	bool changed_cwd = true;
	char cwd[1024];
	const char *b=dir;
	char *b1=0;

	if (!b)
	{
		b = strrchr(name,'/');
		if(!b) changed_cwd=false;
		else
		{
			b1 = new char[b-name+1];
			strncpy(b1,name,b-name);
			b1[b-name]='\0';
			b = b1;
		}
	}

	if(!getcwd(cwd,1023)) 
	{
		perror("getcwd");
		changed_cwd=false;
	}

	if (changed_cwd) 
	{
		if(chdir(b)== -1)
		{
			perror("chdir");
		}
	}

	
	handle_lib = dlopen( name ,RTLD_LAZY);

	if (!handle_lib)
	{
		// Unable to load shared object
		NORMAL_ERR2 ( "ContainerBase: Cannot load dynamic library ", name );
		NORMAL_ERR2 ( "ContainerBase: Error was: ", dlerror() );

	}

	if (changed_cwd)
	{
		if (chdir(cwd) == -1)
		{
			perror("chdir");
			std::cerr << "Can't change back to working directory" << std::endl;
		}
	}

	delete b1;

	return handle_lib;
}

void
unload_shared_library (void* handle)
{
	if (dlclose (handle))
	{
		NORMAL_ERR ( "ContainerBase: Cannot unload dynamic library");
		NORMAL_ERR2 ( "ContainerBase: Error was: ", dlerror() );
	}
}

#endif

}

