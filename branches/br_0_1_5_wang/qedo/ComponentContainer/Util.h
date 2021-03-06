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

#ifndef __UTIL_H__
#define __UTIL_H__


#include <CORBA.h>

#ifdef _WIN32
#include <Windows.h>
#endif


#ifdef _WIN32
#ifdef CONTAINERDLL_EXPORTS
#define CONTAINERDLL_API __declspec(dllexport)
#define CONTAINERDLL_EXTERN
#else
#define CONTAINERDLL_API __declspec(dllimport)
#define CONTAINERDLL_EXTERN extern
#endif

// VC++ warnings 
#pragma warning (disable : 4251) // class OB::ObjVar<*> needs to have dll-interface to be used by clients of class ...
#pragma warning (disable : 4275) // non dll-interface class ... used as base class for dll-interface class ...
#pragma warning (disable : 4290) // exception specification ignored

#else // WIN32
#define CONTAINERDLL_API 
#define CONTAINERDLL_EXTERN
#endif

#if !defined(UNUSED) 
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif


namespace Qedo
{

	/**
	 * loads a shared library
	 * \param name The path of the shared library.
	 * \param dir The directory of the shared library.
	 */
#ifdef _WIN32
	CONTAINERDLL_API HINSTANCE load_shared_library (const char* name,const char* dir);
#else
	void* load_shared_library (const char* name,const char* dir);
#endif

	/**
	 * unload a shared library
	 * \param handle The handle of the shared library.
	 */
#ifdef _WIN32
	CONTAINERDLL_API void unload_shared_library (HINSTANCE handle);
#else
	void unload_shared_library (void* handle);
#endif

};

#endif

