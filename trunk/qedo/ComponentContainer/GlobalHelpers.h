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

#ifndef __GLOBAL_HELPERS_H__
#define __GLOBAL_HELPERS_H__

#include <CORBA.h>
#include "CORBADepends.h"
#include "Key.h"
#include "config.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * creates an object id
 */
CONTAINERDLL_API PortableServer::ObjectId* create_object_id (const CORBA::OctetSeq*, const char*);


/**
 *
 */
CONTAINERDLL_API bool compare_OctetSeqs (const CORBA::OctetSeq&, const CORBA::OctetSeq&);


/**
 *
 */
CONTAINERDLL_API bool compare_object_ids (const PortableServer::ObjectId&, const PortableServer::ObjectId&);


/**
 *
 */
CONTAINERDLL_API char* ObjectId_to_string (const PortableServer::ObjectId&);

#ifndef _QEDO_NO_DB
CONTAINERDLL_API std::string convertPidToString( const CosPersistentState::Pid& rPid );
CONTAINERDLL_API std::string convertPidToString( const CosPersistentState::Pid* rPid );

CONTAINERDLL_API std::string convertSpidToString( const CosPersistentState::ShortPid& rSpid );
CONTAINERDLL_API std::string convertSpidToString( const CosPersistentState::ShortPid* rSpid );

CONTAINERDLL_API void convertStringToPid( const char* szPid, CosPersistentState::Pid& rPid );
CONTAINERDLL_API void convertStringToSpid( const char* szSpid, CosPersistentState::ShortPid& rSpid );

CONTAINERDLL_API bool comparePid(const CosPersistentState::Pid& rSrc, const CosPersistentState::Pid& rDest);
CONTAINERDLL_API bool compareShortPid(const CosPersistentState::ShortPid& rSrc, const CosPersistentState::ShortPid& rDest);
#endif
CONTAINERDLL_API std::string convertBool2String(bool bc);
CONTAINERDLL_API std::string convert2Lowercase(std::string strIn);

/** @} */

} // namespace Qedo

#endif

