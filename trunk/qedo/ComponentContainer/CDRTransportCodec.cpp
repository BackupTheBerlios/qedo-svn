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


#ifndef _QEDO_NO_STREAMS


#include "CDRTransportCoDec.h"
#include "Output.h"

#include <cstring>


static char rcsid[] UNUSED = "$Id: CDRTransportCodec.cpp,v 1.2 2004/01/19 13:07:55 stoinski Exp $";

namespace Qedo {


bool 
CDRTransportCoDec::determine_endianess()
{
	// This function returns true for little-endian systems and false otherwise
	CORBA::UShort test_val = 0xFF00;
	CORBA::Octet* first_byte = reinterpret_cast <CORBA::Octet*> (&test_val);
	
	return !*first_byte;
}


//
// Marshal functions
//
void 
CDRTransportCoDec::marshal_char (MarshalBuffer* buf, const CORBA::Char val)
{
	buf->marshal_data ((char*)&val, 1);
}

void 
CDRTransportCoDec::marshal_wchar (MarshalBuffer* buf, const CORBA::WChar)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_octet (MarshalBuffer* buf, const CORBA::Octet val)
{
	buf->marshal_data ((char*)&val, 1);
}

void 
CDRTransportCoDec::marshal_short (MarshalBuffer* buf, const CORBA::Short val)
{
	buf->do_align (2);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		char new_val[2];
		new_val[0] = tmp_data[1];
		new_val[1] = tmp_data[0];
		buf->marshal_data ((char*)&new_val, 2);
	}
	else
	{
		// Big endian
		buf->marshal_data ((char*)&val, 2);
	}
}

void 
CDRTransportCoDec::marshal_ushort (MarshalBuffer* buf, const CORBA::UShort val)
{
	buf->do_align (2);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		char new_val[2];
		new_val[0] = tmp_data[1];
		new_val[1] = tmp_data[0];
		buf->marshal_data ((char*)&new_val, 2);
	}
	else
	{
		// Big endian
		buf->marshal_data ((char*)&val, 2);
	}
}

void 
CDRTransportCoDec::marshal_long (MarshalBuffer* buf, const CORBA::Long val)
{
	buf->do_align (4);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		char new_val[4];
		new_val[0] = tmp_data[3];
		new_val[1] = tmp_data[2];
		new_val[2] = tmp_data[1];
		new_val[3] = tmp_data[0];
		buf->marshal_data ((char*)&new_val, 4);
	}
	else
	{
		// Big endian
		buf->marshal_data ((char*)&val, 4);
	}
}

void 
CDRTransportCoDec::marshal_ulong (MarshalBuffer* buf, const CORBA::ULong val)
{
	buf->do_align (4);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		char new_val[4];
		new_val[0] = tmp_data[3];
		new_val[1] = tmp_data[2];
		new_val[2] = tmp_data[1];
		new_val[3] = tmp_data[0];
		buf->marshal_data ((char*)&new_val, 4);
	}
	else
	{
		// Big endian
		buf->marshal_data ((char*)&val, 4);
	}
}

void 
CDRTransportCoDec::marshal_longlong (MarshalBuffer* buf, const CORBA::LongLong val)
{
	buf->do_align (8);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		char new_val[8];
		new_val[0] = tmp_data[7];
		new_val[1] = tmp_data[6];
		new_val[2] = tmp_data[5];
		new_val[3] = tmp_data[4];
		new_val[4] = tmp_data[3];
		new_val[5] = tmp_data[2];
		new_val[6] = tmp_data[1];
		new_val[7] = tmp_data[0];
		buf->marshal_data ((char*)&new_val, 8);
	}
	else
	{
		// Big endian
		buf->marshal_data ((char*)&val, 8);
	}
}

void 
CDRTransportCoDec::marshal_ulonglong (MarshalBuffer* buf, const CORBA::ULongLong val)
{
	buf->do_align (8);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		char new_val[8];
		new_val[0] = tmp_data[7];
		new_val[1] = tmp_data[6];
		new_val[2] = tmp_data[5];
		new_val[3] = tmp_data[4];
		new_val[4] = tmp_data[3];
		new_val[5] = tmp_data[2];
		new_val[6] = tmp_data[1];
		new_val[7] = tmp_data[0];
		buf->marshal_data ((char*)&new_val, 8);
	}
	else
	{
		// Big endian
		buf->marshal_data ((char*)&val, 8);
	}
}

void 
CDRTransportCoDec::marshal_float (MarshalBuffer* buf, const CORBA::Float)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_double (MarshalBuffer* buf, const CORBA::Double)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_longdouble (MarshalBuffer* buf, const CORBA::LongDouble)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_boolean (MarshalBuffer* buf, const CORBA::Boolean val)
{
	bool new_val = val;

	if (new_val)
	{
		new_val = 1;
	}

	buf->marshal_data ((char*)&val, 1);
}


void 
CDRTransportCoDec::marshal_string (MarshalBuffer* buf, const char* str)
{
	CORBA::ULong str_len = std::strlen (str) + 1;

	CDRTransportCoDec::marshal_ulong (buf, str_len);

	buf->marshal_data (str, str_len);
}


//
// Unmarshal functions
//
void 
CDRTransportCoDec::unmarshal_char (MarshalBuffer* buf, CORBA::Char& val)
{
	buf->unmarshal_data ((char*)&val, 1);
}

void 
CDRTransportCoDec::unmarshal_wchar (MarshalBuffer* buf, CORBA::WChar& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_octet (MarshalBuffer* buf, CORBA::Octet& val)
{
	buf->unmarshal_data ((char*)&val, 1);
}

void 
CDRTransportCoDec::unmarshal_short (MarshalBuffer* buf, CORBA::Short& val)
{
	buf->do_align (2);

	buf->unmarshal_data ((char*)&val, 2);

	if (determine_endianess())
	{
		// Little-endian
		char* data = reinterpret_cast <char*> (&val);
		char new_val[2];
		new_val[0] = data[1];
		new_val[1] = data[0];
		memcpy (&val, &new_val, 2);
	}
}

void 
CDRTransportCoDec::unmarshal_ushort (MarshalBuffer* buf, CORBA::UShort& val)
{
	buf->do_align (2);

	buf->unmarshal_data ((char*)&val, 2);

	if (determine_endianess())
	{
		// Little-endian
		char* data = reinterpret_cast <char*> (&val);
		char new_val[2];
		new_val[0] = data[1];
		new_val[1] = data[0];
		memcpy (&val, &new_val, 2);
	}
}

void 
CDRTransportCoDec::unmarshal_long (MarshalBuffer* buf, CORBA::Long& val)
{
	buf->do_align (4);

	buf->unmarshal_data ((char*)&val, 4);

	if (determine_endianess())
	{
		// Little-endian
		char* data = reinterpret_cast <char*> (&val);
		char new_val[4];
		new_val[0] = data[3];
		new_val[1] = data[2];
		new_val[2] = data[1];
		new_val[3] = data[0];
		memcpy (&val, &new_val, 4);
	}
}

void 
CDRTransportCoDec::unmarshal_ulong (MarshalBuffer* buf, CORBA::ULong& val)
{
	buf->do_align (4);

	buf->unmarshal_data ((char*)&val, 4);

	if (determine_endianess())
	{
		// Little-endian
		char* data = reinterpret_cast <char*> (&val);
		char new_val[4];
		new_val[0] = data[3];
		new_val[1] = data[2];
		new_val[2] = data[1];
		new_val[3] = data[0];
		memcpy (&val, &new_val, 4);
	}
}

void 
CDRTransportCoDec::unmarshal_longlong (MarshalBuffer* buf, CORBA::LongLong& val)
{
	buf->do_align (8);

	buf->unmarshal_data ((char*)&val, 8);

	if (determine_endianess())
	{
		// Little-endian
		char* data = reinterpret_cast <char*> (&val);
		char new_val[8];
		new_val[0] = data[7];
		new_val[1] = data[6];
		new_val[2] = data[5];
		new_val[3] = data[4];
		new_val[4] = data[3];
		new_val[5] = data[2];
		new_val[6] = data[1];
		new_val[7] = data[0];
		memcpy (&val, &new_val, 8);
	}
}

void 
CDRTransportCoDec::unmarshal_ulonglong (MarshalBuffer* buf, CORBA::ULongLong& val)
{
	buf->do_align (8);

	buf->unmarshal_data ((char*)&val, 8);

	if (determine_endianess())
	{
		// Little-endian
		char* data = reinterpret_cast <char*> (&val);
		char new_val[8];
		new_val[0] = data[7];
		new_val[1] = data[6];
		new_val[2] = data[5];
		new_val[3] = data[4];
		new_val[4] = data[3];
		new_val[5] = data[2];
		new_val[6] = data[1];
		new_val[7] = data[0];
		memcpy (&val, &new_val, 8);
	}
}

void 
CDRTransportCoDec::unmarshal_float (MarshalBuffer* buf, CORBA::Float& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_double (MarshalBuffer* buf, CORBA::Double& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_longdouble (MarshalBuffer* buf, CORBA::LongDouble& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_boolean (MarshalBuffer* buf, CORBA::Boolean& val)
{
	buf->unmarshal_data ((char*)&val, 1);

	if (val)
		val = 1;
}


void 
CDRTransportCoDec::unmarshal_string (MarshalBuffer* buf, char*& str)
{
	CORBA::ULong str_len;

	CDRTransportCoDec::unmarshal_ulong (buf, str_len);

	str = CORBA::string_alloc (str_len);

	if (!str)
	{
		NORMAL_ERR3 ("CDRTransportCoDec: Cannot allocate ", str_len, " bytes for string");
		return;
	}

	buf->unmarshal_data (str, str_len);
}

} // namespace Qedo


#endif