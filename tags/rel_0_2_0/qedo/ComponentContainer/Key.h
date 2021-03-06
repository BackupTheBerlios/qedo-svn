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

#ifndef __KEY_H__
#define __KEY_H__

#include <CORBA.h>
#include <Components.h>

#include "RefCountBase.h"
#include "Util.h"
#include "Synchronisation.h"
#include <string>


#define QEDO_KEY_MAGIC_BYTE_1 0xab
#define QEDO_KEY_MAGIC_BYTE_2 0xad
#define QEDO_KEY_MAGIC_BYTE_3 0xfa
#define QEDO_KEY_MAGIC_BYTE_4 0xce


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * internal key
 */
class CONTAINERDLL_API Key : public RefCountBase
{
private:
	/** the key value */
	CORBA::OctetSeq_var key_value_;

	/** the key id */
    static CORBA::ULongLong key_id_;

	/** mutex for synchronization */
	static qedo_mutex* m_mutex;

public:
	/**
	 * constructor
	 */
	Key();

	/**
	 * destructor
	 */
	~Key();

	/**
	 * provide the key value
	 * \return The key value.
	 */
	CORBA::OctetSeq* key_value() const
	{
		return new CORBA::OctetSeq (key_value_.in());
	}

	/**
	 * provides the stringified key
	 * \return The string of the key.
	 */
	const char* to_string();

	/**
	 * provides the key value of a given object id
	 * \param object_id The object id to get the key value from.
	 * \return The key value.
	 */
	static CORBA::OctetSeq* key_value_from_object_id (const PortableServer::ObjectId& object_id);
};

/** @} */

} // namespace Qedo

#endif

