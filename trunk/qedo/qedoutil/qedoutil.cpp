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
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#else
#include "config.h"
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <fcntl.h>
#endif

#ifdef HAVE_LIBUUID
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include "uuid/uuid.h"
#endif

static char rcsid[] UNUSED = "$Id: qedoutil.cpp,v 1.9 2003/10/30 16:34:09 boehme Exp $";


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
	if( CopyFile(src.c_str(), dst.c_str(), false) )
	{
		return 1;
	}

	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf, 0, NULL);
	NORMAL_ERR3( "copyFile ", src, " failed: " );
	NORMAL_ERR2( "..... ", (LPCTSTR)lpMsgBuf );
		
	// Free the buffer.
	LocalFree( lpMsgBuf );
	return 0;
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


int
makeDir(std::string dir)
{
	if( isFile(dir) ) 
	{ 
        return 1;
	}

	if( isDir(dir) ) 
	{ 
        return 0;
	}

	//
	// check base directory
	//
	int err;
	std::string::size_type pos = dir.find_last_of("/\\");
	if(pos != std::string::npos)
	{
		err = makeDir( dir.substr(0, pos) );
		if(err)
		{
			return err;
		}
	}

	//
	// create directory
	//
#ifdef _WIN32
	DWORD dw;
	if( !CreateDirectory(dir.c_str(), NULL) )
	{
		dw = GetLastError();
		return 2;
	}
#else
	err = mkdir( dir.c_str(), 0755 );
	if(err)
	{
		return 2;
	}
#endif

	return 0;
}


bool
isFile(std::string name)
{
#ifdef _WIN32
	std::string::size_type pos = name.find_first_of("/");
	while (pos != std::string::npos)
    {
        name.replace(pos, 1, "\\");
        pos = name.find_first_of("/");
    }
	// if the last symbol is a delimiter, remove it
	char* object_name = strdup(name.c_str());
	if ((strlen(object_name)) && (object_name[strlen(object_name) - 1] == '\\'))
#else
	// if the last symbol is a delimiter, remove it
	char* object_name = strdup(name.c_str());
	if ((strlen(object_name)) && (object_name[strlen(object_name) - 1] == '/' ))
#endif
	{
		object_name[strlen(object_name) - 1] = '\0';
	}

	struct stat statbuff;
	int rt = stat(object_name, &statbuff);
	free(object_name);

	if  (rt < 0)
	{
		return false;
	}

	if( (statbuff.st_mode & S_IFMT) == S_IFREG )
	{
		return true;
	}

	return false;
}


int
removeFile(std::string name)
{
    if( isFile(name) )
	{
#ifdef _WIN32
        char dummy[256];
        strcpy(dummy, name.c_str());
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
		std::string command = std::string("\\rm -f ") + name;
		system(command.c_str());
#endif
		return 0;
	}

    return 1;
}


bool
isDir(std::string name)
{
#ifdef _WIN32
	std::string::size_type pos = name.find_first_of("/");
	while (pos != std::string::npos)
    {
        name.replace(pos, 1, "\\");
        pos = name.find_first_of("/");
    }
	// if the last symbol is a delimiter, remove it
	char* object_name = strdup(name.c_str());
	if ((strlen(object_name)) && (object_name[strlen(object_name) - 1] == '\\'))
#else
	// if the last symbol is a delimiter, remove it
	char* object_name = strdup(name.c_str());
	if ((strlen(object_name)) && (object_name[strlen(object_name) - 1] == '/' ))
#endif
	{
		object_name[strlen(object_name) - 1] = '\0';
	}

	struct stat statbuff;
	int rt = stat(object_name, &statbuff);
	free(object_name);

	if  (rt < 0)
	{
		return false;
	}
		
	if( (statbuff.st_mode & S_IFMT) == S_IFDIR )
	{
		return true; 
	}
    
	return false;
}


int 
removeDir(std::string name) 
{
	// if the last symbol is a delimiter, remove it
	std::string object_name = name;
#ifdef _WIN32
	if (object_name[object_name.size() - 1] == '\\')
#else
	if (object_name[object_name.size() - 1] == '/')
#endif
	{
		object_name.erase(object_name.size() - 1, 1);
	}
    
    if( isDir(object_name) ) 
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

    return 1;
}


std::string
createUUID()
{
	std::string id;

#ifdef _WIN32
	GUID guid;
	CoCreateGuid(&guid);
	LPOLESTR lpolestr;
	StringFromCLSID(guid, &lpolestr);
	int i = wcstombs(NULL, lpolestr, 0);
   char *buf = new char[i];
    wcstombs(buf, lpolestr, i);
	// remove { and }
	buf[i - 1] = '\0';
	id = buf;
	id.erase(0, 1);
	delete [] buf;
	CoTaskMemFree(lpolestr);
#else /* Linux */
	uuid_t uuid;
	char buf[38];
	uuid_generate(uuid);
	sprintf(buf,"%2.2X%2.2X%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X\n"
	                ,(uint32_t)uuid[0]
	                ,(uint8_t)uuid[sizeof(uint8_t)*1]
	                ,(uint8_t)uuid[sizeof(uint8_t)*2]
	                ,(uint8_t)uuid[sizeof(uint8_t)*3]
	                ,(uint8_t)uuid[sizeof(uint8_t)*4]
	                ,(uint8_t)uuid[sizeof(uint8_t)*5]
	                ,(uint8_t)uuid[sizeof(uint8_t)*6]
	                ,(uint8_t)uuid[sizeof(uint8_t)*7]
	                ,(uint8_t)uuid[sizeof(uint8_t)*8]
	                ,(uint8_t)uuid[sizeof(uint8_t)*9]
	                ,(uint8_t)uuid[sizeof(uint8_t)*10]
	                ,(uint8_t)uuid[sizeof(uint8_t)*11]
	                ,(uint8_t)uuid[sizeof(uint8_t)*12]
	                ,(uint8_t)uuid[sizeof(uint8_t)*13]
	                ,(uint8_t)uuid[sizeof(uint8_t)*14]
	                ,(uint8_t)uuid[sizeof(uint8_t)*15]);
	id = buf;
#endif

	return id;
}


}

