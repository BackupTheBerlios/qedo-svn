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

#ifndef __CDR_TRANSPORT_CODEC_H__
#define __CDR_TRANSPORT_CODEC_H__

#ifndef _QEDO_NO_STREAMS


#include "CORBA.h"
#include "StreamComponents.h"
#include "Util.h"


namespace Qedo {


class CDRTransportCoDec
{
private:
	static CORBA::ULong calculate_align (const char*, const char*, CORBA::ULong);
	static void do_align (char*&, const char*, CORBA::ULong);
	static bool determine_endianess();

public:
	CDRTransportCoDec();
	~CDRTransportCoDec();

	static CONTAINERDLL_API void marshal_char (char*&, const char*, CORBA::Char);
	static CONTAINERDLL_API void marshal_wchar (char*&, const char*, CORBA::WChar);
	static CONTAINERDLL_API void marshal_octet (char*&, const char*, const CORBA::Octet);
	static CONTAINERDLL_API void marshal_short (char*&, const char*, const CORBA::Short);
	static CONTAINERDLL_API void marshal_ushort (char*&, const char*, const CORBA::UShort);
	static CONTAINERDLL_API void marshal_long (char*&, const char*, const CORBA::Long);
	static CONTAINERDLL_API void marshal_ulong (char*&, const char*, const CORBA::ULong);
	static CONTAINERDLL_API void marshal_longlong (char*&, const char*, const CORBA::LongLong);
	static CONTAINERDLL_API void marshal_ulonglong (char*&, const char*, const CORBA::ULongLong);
	static CONTAINERDLL_API void marshal_float (char*&, const char*, const CORBA::Float);
	static CONTAINERDLL_API void marshal_double (char*&, const char*, const CORBA::Double);
	static CONTAINERDLL_API void marshal_longdouble (char*&, const char*, const CORBA::LongDouble);
	static CONTAINERDLL_API void marshal_boolean (char*&, const char*, const CORBA::Boolean);

	static CONTAINERDLL_API void unmarshal_char (char*&, const char*, CORBA::Char&);
	static CONTAINERDLL_API void unmarshal_wchar (char*&, const char*, CORBA::WChar&);
	static CONTAINERDLL_API void unmarshal_octet (char*&, const char*, CORBA::Octet&);
	static CONTAINERDLL_API void unmarshal_short (char*&, const char*, CORBA::Short&);
	static CONTAINERDLL_API void unmarshal_ushort (char*&, const char*, CORBA::UShort&);
	static CONTAINERDLL_API void unmarshal_long (char*&, const char*, CORBA::Long&);
	static CONTAINERDLL_API void unmarshal_ulong (char*&, const char*, CORBA::ULong&);
	static CONTAINERDLL_API void unmarshal_longlong (char*&, const char*, CORBA::LongLong&);
	static CONTAINERDLL_API void unmarshal_ulonglong (char*&, const char*, CORBA::ULongLong&);
	static CONTAINERDLL_API void unmarshal_float (char*&, const char*, CORBA::Float&);
	static CONTAINERDLL_API void unmarshal_double (char*&, const char*, CORBA::Double&);
	static CONTAINERDLL_API void unmarshal_longdouble (char*&, const char*, CORBA::LongDouble&);
	static CONTAINERDLL_API void unmarshal_boolean (char*&, const char*, CORBA::Boolean&);
};


} // namespace Qedo

#endif

#endif

