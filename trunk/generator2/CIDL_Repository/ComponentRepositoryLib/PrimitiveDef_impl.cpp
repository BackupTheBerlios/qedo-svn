/*****************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                    */
/*                                                                           */
/* Copyright (c) 2002 by the Qedo Team                                       */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */ 
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/

#include "PrimitiveDef_impl.h"
#include "Repository_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {

PrimitiveDef_impl::PrimitiveDef_impl
( IR__::PrimitiveKind kind, Repository_impl *repository )
: IDLType_impl ( repository ),
	IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "PrimitiveDef_impl::PrimitiveDef_impl() called " );
	kind_ = kind;
}

PrimitiveDef_impl::~PrimitiveDef_impl
()
{
	DEBUG_OUTLINE ( "PrimitiveDef_impl::~PrimitiveDef_impl() called " );
}

void
PrimitiveDef_impl::destroy_from_repository
()
{
	DEBUG_OUTLINE ( "PrimitiveDef_impl::destroy() called" );
	IDLType_impl::destroy();
	this -> _remove_ref();
}

void
PrimitiveDef_impl::destroy
()
throw(CORBA::SystemException)
{
	throw CORBA::BAD_INV_ORDER ( 2, CORBA::COMPLETED_NO );
}

IR__::PrimitiveKind PrimitiveDef_impl::kind
()
throw(CORBA::SystemException)
{
	return kind_;
}

CORBA::TypeCode_ptr
PrimitiveDef_impl::type
()
throw(CORBA::SystemException)
{
    switch ( kind_ )
    {
    case IR__::pk_void:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_void);
		break;
    case IR__::pk_short:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_short);
		break;
    case IR__::pk_long:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_long);
		break;
    case IR__::pk_ushort:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_ushort);
		break;
    case IR__::pk_ulong:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_ulong);
		break;
    case IR__::pk_float:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_float);
		break;
    case IR__::pk_double:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_double);
		break;
    case IR__::pk_boolean:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_boolean);
		break;
    case IR__::pk_char:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_char);
		break;
    case IR__::pk_octet:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_octet);
		break;
    case IR__::pk_any:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_any);
		break;
    case IR__::pk_TypeCode:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_TypeCode);
		break;
    case IR__::pk_Principal:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_Principal);
		break;
    case IR__::pk_string:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_string);
		break;
    case IR__::pk_objref:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_Object);
		break;
    case IR__::pk_longlong:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_longlong);
		break;
    case IR__::pk_ulonglong:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_ulonglong);
		break;
    case IR__::pk_longdouble:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_longdouble);
		break;
    case IR__::pk_wchar:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_wchar);
		break;
    case IR__::pk_wstring:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_wstring);
		break;
    case IR__::pk_value_base:
	{
		IR__::ValueMemberSeq members;
		// This is a hack, because ORBacus needs a ValueMemberSeq from the CORBA module
		CORBA::ValueMemberSeq *members_new;
		members_new = (CORBA::ValueMemberSeq *)&members;
        return repository_ -> orb() -> create_value_tc("IDL:omg.org/CORBA/ValueBase:1.0",
                                       "ValueBase", CORBA::VM_ABSTRACT,
                                       CORBA::TypeCode::_nil(), *members_new);
		break;
	}
	default:
        return CORBA::TypeCode::_duplicate(CORBA::_tc_null);
		break;
	}
}

} // namespace QEDO_ComponentRepository
