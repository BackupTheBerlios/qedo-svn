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

#ifndef __QEDO_UTIL_H__
#define __QEDO_UTIL_H__


#include <CORBA.h>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif


#include <xercesc/util/XMLString.hpp>

#ifdef _WIN32
#ifdef QEDOUTIL_EXPORTS
#define QEDOUTIL_API __declspec(dllexport)
#define QEDOUTIL_EXTERN
#else
#define QEDOUTIL_API __declspec(dllimport)
#define QEDOUTIL_EXTERN extern
#endif

// VC++ warnings 
#pragma warning (disable : 4251) // class OB::ObjVar<*> needs to have dll-interface to be used by clients of class ...
#pragma warning (disable : 4275) // non dll-interface class ... used as base class for dll-interface class ...
#pragma warning (disable : 4290) // exception specification ignored

#else // _WIN32
#define QEDOUTIL_API 
#define QEDOUTIL_EXTERN
#endif


#if !defined(UNUSED) 
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif


/**
 * @defgroup Utilities
 * collection of functions for plattform independen file and directory handling
 * @{
 */


namespace Qedo {

/**
 * get the value of the environment variable
 * \param name The environment variable.
 */
QEDOUTIL_API
std::string
getEnvironment(std::string name);


/**
 * get the current directory
 */
QEDOUTIL_API
std::string 
getCurrentDirectory();


/**
 * copy file
 */
QEDOUTIL_API
int 
copyFile(std::string src, std::string dst);


/**
 * move file
 */
QEDOUTIL_API
int
moveFile(std::string source, std::string dest);


/**
 * get the name of the file without path
 */
QEDOUTIL_API
std::string 
getFileName(std::string source);


/**
 * appends the right path delimiter
 */
QEDOUTIL_API
std::string 
getPath(std::string source);


/**
 * checks whether the file exists
 * \param name The name of the file.
 * \return True if name denotes a file
 */
QEDOUTIL_API
bool 
isFile(std::string name);


/**
 * remove file
 * \param name The name of the file to be removed.
 * \return 0 if removed
 */
QEDOUTIL_API
int 
removeFile(std::string name);


/**
 * checks whether the directory exists
 * \param name The name of the directory.
 * \return True if name denotes a directory
 */
QEDOUTIL_API
bool 
isDir(std::string name);


/**
 * create directory
 * \param name The name of the directory.
 * \return 0 if directory was created or already exists
 */
QEDOUTIL_API
int 
makeDir(std::string name);


/**
 * remove directory
 * \param name The name of the directory to be removed.
 * \return 0 if removed
 */
QEDOUTIL_API
int 
removeDir(std::string name);


/**
 * create UUID
 * \return The created UUID.
 */
QEDOUTIL_API
std::string
createUUID();

/**
 * own transcode adapter for memory handling
 * \return the transcoded string from Xerces as std::string
 */
QEDOUTIL_API
std::string
transcode(const XMLCh * const);

}

/** @} */


#endif

