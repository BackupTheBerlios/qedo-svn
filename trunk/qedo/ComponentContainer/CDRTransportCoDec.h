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
#include "Components.h"

#include "MarshalBuffer.h"
#include "Util.h"


namespace Qedo {


class CDRTransportCoDec
{
private:
	static bool determine_endianess();

public:
	CDRTransportCoDec();
	~CDRTransportCoDec();

	static CONTAINERDLL_API void marshal_char (MarshalBuffer*, const CORBA::Char);
	static CONTAINERDLL_API void marshal_wchar (MarshalBuffer*, const CORBA::WChar);
	static CONTAINERDLL_API void marshal_octet (MarshalBuffer*, const CORBA::Octet);
	static CONTAINERDLL_API void marshal_short (MarshalBuffer*, const CORBA::Short);
	static CONTAINERDLL_API void marshal_ushort (MarshalBuffer*, const CORBA::UShort);
	static CONTAINERDLL_API void marshal_long (MarshalBuffer*, const CORBA::Long);
	static CONTAINERDLL_API void marshal_ulong (MarshalBuffer*, const CORBA::ULong);
	static CONTAINERDLL_API void marshal_longlong (MarshalBuffer*, const CORBA::LongLong);
	static CONTAINERDLL_API void marshal_ulonglong (MarshalBuffer*, const CORBA::ULongLong);
	static CONTAINERDLL_API void marshal_float (MarshalBuffer*, const CORBA::Float);
	static CONTAINERDLL_API void marshal_double (MarshalBuffer*, const CORBA::Double);
	static CONTAINERDLL_API void marshal_longdouble (MarshalBuffer*, const CORBA::LongDouble);
	static CONTAINERDLL_API void marshal_boolean (MarshalBuffer*, const CORBA::Boolean);
	static CONTAINERDLL_API void marshal_string (MarshalBuffer*, const char*);

	static CONTAINERDLL_API void unmarshal_char (UnmarshalBuffer*, CORBA::Char&);
	static CONTAINERDLL_API void unmarshal_wchar (UnmarshalBuffer*, CORBA::WChar&);
	static CONTAINERDLL_API void unmarshal_octet (UnmarshalBuffer*, CORBA::Octet&);
	static CONTAINERDLL_API void unmarshal_short (UnmarshalBuffer*, CORBA::Short&);
	static CONTAINERDLL_API void unmarshal_ushort (UnmarshalBuffer*, CORBA::UShort&);
	static CONTAINERDLL_API void unmarshal_long (UnmarshalBuffer*, CORBA::Long&);
	static CONTAINERDLL_API void unmarshal_ulong (UnmarshalBuffer*, CORBA::ULong&);
	static CONTAINERDLL_API void unmarshal_longlong (UnmarshalBuffer*, CORBA::LongLong&);
	static CONTAINERDLL_API void unmarshal_ulonglong (UnmarshalBuffer*, CORBA::ULongLong&);
	static CONTAINERDLL_API void unmarshal_float (UnmarshalBuffer*, CORBA::Float&);
	static CONTAINERDLL_API void unmarshal_double (UnmarshalBuffer*, CORBA::Double&);
	static CONTAINERDLL_API void unmarshal_longdouble (UnmarshalBuffer*, CORBA::LongDouble&);
	static CONTAINERDLL_API void unmarshal_boolean (UnmarshalBuffer*, CORBA::Boolean&);
	static CONTAINERDLL_API void unmarshal_string (UnmarshalBuffer*, char*&);
};


} // namespace Qedo

#endif

#endif

