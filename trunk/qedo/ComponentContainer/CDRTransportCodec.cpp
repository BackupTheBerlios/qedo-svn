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


static char rcsid[] UNUSED = "$Id: CDRTransportCodec.cpp,v 1.1 2004/01/15 10:45:00 stoinski Exp $";

namespace Qedo {


bool 
CDRTransportCoDec::determine_endianess()
{
	// This function returns true for little-endian systems and false otherwise
	CORBA::UShort test_val = 0xFF00;
	CORBA::Octet* first_byte = reinterpret_cast <CORBA::Octet*> (&test_val);
	
	return !*first_byte;
}


CORBA::ULong
CDRTransportCoDec::calculate_align (const char* data, const char* data_start, CORBA::ULong align_val)
{
	CORBA::ULong modulo = static_cast <CORBA::ULong> (data - data_start) % align_val;
	if (modulo)
		return align_val - modulo;
	else
		return 0;
}

void 
CDRTransportCoDec::do_align (char*& data, const char* data_start, CORBA::ULong align_val)
{
	data += calculate_align (data, data_start, align_val);
}


//
// Marshal functions
//
void 
CDRTransportCoDec::marshal_char (char*& data, const char* data_start, const CORBA::Char val)
{
	*data++ = (char) val;
}

void 
CDRTransportCoDec::marshal_wchar (char*& data, const char* data_start, const CORBA::WChar)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_octet (char*& data, const char* data_start, const CORBA::Octet val)
{
	*data++ = (char) val;
}

void 
CDRTransportCoDec::marshal_short (char*& data, const char* data_start, const CORBA::Short val)
{
	do_align (data, data_start, 2);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		data[0] = tmp_data[1];
		data[1] = tmp_data[0];
	}
	else
	{
		// Big endian
		memcpy (data, &val, 2);
	}

	data += 2;
}

void 
CDRTransportCoDec::marshal_ushort (char*& data, const char* data_start, const CORBA::UShort val)
{
	do_align (data, data_start, 2);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		data[0] = tmp_data[1];
		data[1] = tmp_data[0];
	}
	else
	{
		// Big endian
		memcpy (data, &val, 2);
	}

	data += 2;
}

void 
CDRTransportCoDec::marshal_long (char*& data, const char* data_start, const CORBA::Long val)
{
	do_align (data, data_start, 4);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		data[0] = tmp_data[3];
		data[1] = tmp_data[2];
		data[2] = tmp_data[1];
		data[3] = tmp_data[0];
	}
	else
	{
		// Big endian
		memcpy (data, &val, 4);
	}

	data += 4;
}

void 
CDRTransportCoDec::marshal_ulong (char*& data, const char* data_start, const CORBA::ULong val)
{
	do_align (data, data_start, 4);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		data[0] = tmp_data[3];
		data[1] = tmp_data[2];
		data[2] = tmp_data[1];
		data[3] = tmp_data[0];
	}
	else
	{
		// Big endian
		memcpy (data, &val, 4);
	}

	data += 4;
}

void 
CDRTransportCoDec::marshal_longlong (char*& data, const char* data_start, const CORBA::LongLong val)
{
	do_align (data, data_start, 8);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		data[0] = tmp_data[7];
		data[1] = tmp_data[6];
		data[2] = tmp_data[5];
		data[3] = tmp_data[4];
		data[4] = tmp_data[3];
		data[5] = tmp_data[2];
		data[6] = tmp_data[1];
		data[7] = tmp_data[0];
	}
	else
	{
		// Big endian
		memcpy (data, &val, 8);
	}

	data += 8;
}

void 
CDRTransportCoDec::marshal_ulonglong (char*& data, const char* data_start, const CORBA::ULongLong val)
{
	do_align (data, data_start, 8);

	if (determine_endianess())
	{
		// Little-endian
		const char* tmp_data = reinterpret_cast <const char*> (&val);
		data[0] = tmp_data[7];
		data[1] = tmp_data[6];
		data[2] = tmp_data[5];
		data[3] = tmp_data[4];
		data[4] = tmp_data[3];
		data[5] = tmp_data[2];
		data[6] = tmp_data[1];
		data[7] = tmp_data[0];
	}
	else
	{
		// Big endian
		memcpy (data, &val, 8);
	}

	data += 8;
}

void 
CDRTransportCoDec::marshal_float (char*& data, const char* data_start, const CORBA::Float)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_double (char*& data, const char* data_start, const CORBA::Double)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_longdouble (char*& data, const char* data_start, const CORBA::LongDouble)
{
	assert (0);
}

void 
CDRTransportCoDec::marshal_boolean (char*& data, const char* data_start, const CORBA::Boolean val)
{
	if (val > 0)
		*data++ = (char) 1;
	else
		*data++ = (char) 0;
}


//
// Unmarshal functions
//
void 
CDRTransportCoDec::unmarshal_char (char*& data, const char* data_start, CORBA::Char& val)
{
	val = (char) *data++;
}

void 
CDRTransportCoDec::unmarshal_wchar (char*& data, const char* data_start, CORBA::WChar& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_octet (char*& data, const char* data_start, CORBA::Octet& val)
{
	val = (char) *data++;
}

void 
CDRTransportCoDec::unmarshal_short (char*& data, const char* data_start, CORBA::Short& val)
{
	do_align (data, data_start, 2);

	if (determine_endianess())
	{
		// Little-endian
		char* tmp_data = reinterpret_cast <char*> (&val);
		tmp_data[0] = data[1];
		tmp_data[1] = data[0];
	}
	else
	{
		// Big endian
		memcpy (&val, data, 2);
	}

	data += 2;
}

void 
CDRTransportCoDec::unmarshal_ushort (char*& data, const char* data_start, CORBA::UShort& val)
{
	do_align (data, data_start, 2);

	if (determine_endianess())
	{
		// Little-endian
		char* tmp_data = reinterpret_cast <char*> (&val);
		tmp_data[0] = data[1];
		tmp_data[1] = data[0];
	}
	else
	{
		// Big endian
		memcpy (&val, data, 2);
	}

	data += 2;
}

void 
CDRTransportCoDec::unmarshal_long (char*& data, const char* data_start, CORBA::Long& val)
{
	do_align (data, data_start, 4);

	if (determine_endianess())
	{
		// Little-endian
		char* tmp_data = reinterpret_cast <char*> (&val);
		tmp_data[0] = data[3];
		tmp_data[1] = data[2];
		tmp_data[2] = data[1];
		tmp_data[3] = data[0];
	}
	else
	{
		// Big endian
		memcpy (&val, data, 4);
	}

	data += 4;
}

void 
CDRTransportCoDec::unmarshal_ulong (char*& data, const char* data_start, CORBA::ULong& val)
{
	do_align (data, data_start, 4);

	if (determine_endianess())
	{
		// Little-endian
		char* tmp_data = reinterpret_cast <char*> (&val);
		tmp_data[0] = data[3];
		tmp_data[1] = data[2];
		tmp_data[2] = data[1];
		tmp_data[3] = data[0];
	}
	else
	{
		// Big endian
		memcpy (&val, data, 4);
	}

	data += 4;
}

void 
CDRTransportCoDec::unmarshal_longlong (char*& data, const char* data_start, CORBA::LongLong& val)
{
	do_align (data, data_start, 8);

	if (determine_endianess())
	{
		// Little-endian
		char* tmp_data = reinterpret_cast <char*> (&val);
		tmp_data[0] = data[7];
		tmp_data[1] = data[6];
		tmp_data[2] = data[5];
		tmp_data[3] = data[4];
		tmp_data[4] = data[3];
		tmp_data[5] = data[2];
		tmp_data[6] = data[1];
		tmp_data[7] = data[0];
	}
	else
	{
		// Big endian
		memcpy (&val, data, 8);
	}

	data += 8;
}

void 
CDRTransportCoDec::unmarshal_ulonglong (char*& data, const char* data_start, CORBA::ULongLong& val)
{
	do_align (data, data_start, 8);

	if (determine_endianess())
	{
		// Little-endian
		char* tmp_data = reinterpret_cast <char*> (&val);
		tmp_data[0] = data[7];
		tmp_data[1] = data[6];
		tmp_data[2] = data[5];
		tmp_data[3] = data[4];
		tmp_data[4] = data[3];
		tmp_data[5] = data[2];
		tmp_data[6] = data[1];
		tmp_data[7] = data[0];
	}
	else
	{
		// Big endian
		memcpy (&val, data, 8);
	}

	data += 8;
}

void 
CDRTransportCoDec::unmarshal_float (char*& data, const char* data_start, CORBA::Float& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_double (char*& data, const char* data_start, CORBA::Double& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_longdouble (char*& data, const char* data_start, CORBA::LongDouble& val)
{
	assert (0);
}

void 
CDRTransportCoDec::unmarshal_boolean (char*& data, const char* data_start, CORBA::Boolean& val)
{
	if (*data++ > 0)
		val = (char) 1;
	else
		val = (char) 0;
}


} // namespace Qedo


#endif