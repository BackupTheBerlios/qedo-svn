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

static char rcsid[] = "$Id: Key.cpp,v 1.1 2002/10/07 07:17:02 tom Exp $";

#include "Key.h"
#include "Output.h"

namespace Qedo {

Key::Key
()
{
	// Keys can be generated from concurrent threads, so accessing the static
	// key id must be synchronized
	JTCSynchronized synchronized (*this);

	key_value_ = new CORBA::OctetSeq();
	key_value_->length (12);

	key_value_[0] = QEDO_KEY_MAGIC_BYTE_1;
	key_value_[1] = QEDO_KEY_MAGIC_BYTE_2;
	key_value_[2] = QEDO_KEY_MAGIC_BYTE_3;
	key_value_[3] = QEDO_KEY_MAGIC_BYTE_4;

	key_id_++;
	memcpy(key_value_->get_buffer()+4,&key_id_,sizeof(key_id_));
#if 0
	key_value_[4] = (CORBA::Octet)(++key_id_ & 0xff00000000000000UL) >> 56;
	key_value_[5] = (CORBA::Octet)(key_id_ & 0x00ff000000000000) >> 48;
	key_value_[6] = (CORBA::Octet)(key_id_ & 0x0000ff0000000000) >> 40;
	key_value_[7] = (CORBA::Octet)(key_id_ & 0x000000ff00000000) >> 32;
	key_value_[8] = (CORBA::Octet)(key_id_ & 0x00000000ff000000) >> 24;
	key_value_[9] = (CORBA::Octet)(key_id_ & 0x0000000000ff0000) >> 16;
	key_value_[10] = (CORBA::Octet)(key_id_ & 0x000000000000ff00) >> 8;
	key_value_[11] = (CORBA::Octet)key_id_ & 0x00000000000000ff;
#endif
}


Key::~Key
()
{
	DEBUG_OUT ("Key: Destructor called");
}


const char*
Key::to_string
()
{
	CORBA::String_var key_id_buffer = CORBA::string_alloc(27);		// 2 + 2*12 + 1
	key_id_buffer[0] = '0';
	key_id_buffer[1] = 'x';
	key_id_buffer[26] = 0;

	for (unsigned int i = 0; i < 12; i++)
	{
		unsigned int val1 = (unsigned int)(key_value_[i] & 0xf0) >> 4;
		unsigned int val2 = (unsigned int)key_value_[i] & 0x0f;

		if (val1 >= 0 && val1 <= 9)
			key_id_buffer[2*i+2] = val1 + 48;
		else
			key_id_buffer[2*i+2] = val1 + 87;       // a..f

		if (val2 >= 0 && val2 <= 9)
			key_id_buffer[2*i+2+1] = val2 + 48;
		else
			key_id_buffer[2*i+2+1] = val2 + 87;
	}

	return key_id_buffer._retn();
}


CORBA::OctetSeq* 
Key::key_value_from_object_id (const PortableServer::ObjectId& object_id)
{
	if (object_id.length() < 12)
	{
		return new CORBA::OctetSeq();
	}

	CORBA::OctetSeq* key_seq = new CORBA::OctetSeq();
	key_seq->length (12);

	memcpy (key_seq->get_buffer(), object_id.get_buffer(), 12);

	if ((*key_seq)[0] != QEDO_KEY_MAGIC_BYTE_1
		|| (*key_seq)[1] != QEDO_KEY_MAGIC_BYTE_2
		|| (*key_seq)[2] != QEDO_KEY_MAGIC_BYTE_3
		|| (*key_seq)[3] != QEDO_KEY_MAGIC_BYTE_4)
	{
		NORMAL_ERR ("Key: Fatal internal error in key_value_from_object_id(): Supplied object id was not created by the Qedo framework");
		// TODO - what to do???
	}

	return key_seq;
}


CORBA::ULongLong Key::key_id_ = 0;

} // namespace Qedo

