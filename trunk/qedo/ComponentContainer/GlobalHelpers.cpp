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

static char rcsid[] = "$Id: GlobalHelpers.cpp,v 1.6 2003/04/01 07:50:10 neubauer Exp $";

#include "GlobalHelpers.h"
#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif


namespace Qedo {


PortableServer::ObjectId*
create_object_id (const CORBA::OctetSeq* octet_key, const char* variable_info)
{
	unsigned int i;
	unsigned int cur_len = octet_key->length();

	PortableServer::ObjectId_var object_id = new PortableServer::ObjectId();

	object_id->length (cur_len);

	for (i = 0; i < cur_len; i++)
	{
		object_id.inout()[i] = (*octet_key)[i];
	}

	// Append the process id
	CORBA::ULong process_id = (CORBA::ULong)getpid();

	object_id->length (cur_len + 4 /*ULong*/);

	for (i = 0; i < 4; i++, cur_len++)
	{
		object_id.inout()[cur_len] = ((CORBA::Octet*)&process_id)[i];
	}

	unsigned int variable_info_len = strlen (variable_info);

	object_id->length (cur_len + variable_info_len);

	for (i = 0; i < variable_info_len; i++, cur_len++)
	{
		object_id.inout()[cur_len] = variable_info[i];
	}

	return object_id._retn();
}


bool 
compare_OctetSeqs (const CORBA::OctetSeq& seq1, const CORBA::OctetSeq& seq2)
{
	if (seq1.length() != seq2.length())
	{
		return false;
	}

	for (unsigned int i = 0; i < seq1.length(); i++)
	{
		if (seq1[i] != seq2[i])
		{
			return false;
		}
	}

	return true;
}


bool 
compare_object_ids (const PortableServer::ObjectId& id1, const PortableServer::ObjectId& id2)
{
	if (id1.length() != id2.length())
	{
		return false;
	}

	for (unsigned int i = 0; i < id1.length(); i++)
	{
		if (id1[i] != id2[i])
		{
			return false;
		}
	}

	return true;
}


char* 
ObjectId_to_string (const PortableServer::ObjectId& object_id)
{
	CORBA::ULong object_id_len = object_id.length();
	CORBA::String_var string_buffer = CORBA::string_alloc (object_id_len * 2 + 2 + 1);

	string_buffer.inout()[0] = '0';
	string_buffer.inout()[1] = 'x';
	string_buffer[object_id_len * 2 + 2] = 0;

	for (unsigned int i = 0; i < object_id_len; i++)
	{
		unsigned int val1 = (unsigned int)(object_id[i] & 0xf0) >> 4;
		unsigned int val2 = (unsigned int)object_id[i] & 0x0f;

		if (val1 >= 0 && val1 <= 9)
			string_buffer.inout()[2*i+2] = val1 + 48;
		else
			string_buffer.inout()[2*i+2] = val1 + 87;       // a..f

		if (val2 >= 0 && val2 <= 9)
			string_buffer.inout()[2*i+2+1] = val2 + 48;
		else
			string_buffer.inout()[2*i+2+1] = val2 + 87;
	}

	return string_buffer._retn();
}

} // namespace Qedo
