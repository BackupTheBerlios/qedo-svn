/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

#include <OB/CORBA.h>

#include "Key.h"

namespace Qedo {

PortableServer::ObjectId* create_object_id (const CORBA::OctetSeq*, const char*);
bool compare_OctetSeqs (const CORBA::OctetSeq&, const CORBA::OctetSeq&);
bool compare_object_ids (const PortableServer::ObjectId&, const PortableServer::ObjectId&);
char* ObjectId_to_string (const PortableServer::ObjectId&);

} // namespace Qedo

#endif

