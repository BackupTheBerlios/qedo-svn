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

#include "Util.h"
#include "Output.h"

#ifndef _WIN32
#include <dlfcn.h>
#endif


static char rcsid[] UNUSED = "$Id: Util.cpp,v 1.6 2004/05/13 13:01:57 hao Exp $";


namespace Qedo {


#ifdef _WIN32

HINSTANCE 
load_shared_library (const char* name, const char* dir)
{
	HINSTANCE handle_lib;

	handle_lib = LoadLibraryEx (name, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

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
	const char *local_name=0;

	if (!b || !strcmp (b, ""))
	{
		DEBUG_OUT("load_shared_library got no dir");
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
		DEBUG_OUT2("load_shared_library go from", cwd);
		DEBUG_OUT2("load_shared_library go to", b);
		if(chdir(b)== -1)
		{
			DEBUG_OUT("load_shared_library error while chdir");
			perror("chdir");
		}
		
		DEBUG_OUT2("load_shared_library original name was ", name);
		local_name = strrchr(name,'/');
		if(local_name) local_name++;
	}
	else
	{
		local_name = name;
	}

	DEBUG_OUT2("load_shared_library name is ", local_name);

	
	handle_lib = dlopen( local_name ,RTLD_GLOBAL|RTLD_LAZY);

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
			NORMAL_ERR2("load_shared_library can't change back to working directory ", cwd);
		}
	}

	delete [] b1;

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

