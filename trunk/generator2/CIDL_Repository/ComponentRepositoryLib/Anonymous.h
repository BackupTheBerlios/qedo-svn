/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
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

#ifndef __ANONYMOUS_H__
#define __ANONYMOUS_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "IDLType_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

//
// StringDef_impl
//
class StringDef_impl : public virtual POA_IR__::StringDef,
						public virtual IDLType_impl
{
	CORBA::ULong bound_;
public:
	StringDef_impl ( Repository_impl *repository );

	~StringDef_impl();

    CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq )
        throw (CORBA::SystemException)
    {
		DEBUG_OUTLINE ( "StringDef_impl::build_recursive_type_code(...) called" );
        return type();
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
	{
		return CORBA__::dk_String;
	}

    //
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/StringDef/bound:1.0
    //
    virtual CORBA::ULong bound()
        throw(CORBA::SystemException);
    virtual void bound(CORBA::ULong)
        throw(CORBA::SystemException);
};

//
// WstringDef_impl
//
class WstringDef_impl : public virtual POA_IR__::WstringDef,
						public virtual IDLType_impl
{
	CORBA::ULong bound_;
public:
	WstringDef_impl ( Repository_impl *repository );

	~WstringDef_impl();

    CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq )
        throw (CORBA::SystemException)
    {
		DEBUG_OUTLINE ( "WstringDef_impl::build_recursive_type_code(...) called" );
        return type();
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
	{
		return CORBA__::dk_Wstring;
	}

    //
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/WstringDef/bound:1.0
    //
    virtual CORBA::ULong bound()
        throw(CORBA::SystemException);
    virtual void bound(CORBA::ULong)
        throw(CORBA::SystemException);
};

//
// SequenceDef_impl
//
class SequenceDef_impl : public virtual POA_IR__::SequenceDef,
						public virtual IDLType_impl
{
	CORBA::ULong bound_;
	IDLType_impl *element_type_;
public:
	SequenceDef_impl ( Repository_impl *repository );

	~SequenceDef_impl();

	CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq );

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
	{
		return CORBA__::dk_Sequence;
	}

    //
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/SequenceDef/bound:1.0
    //
    virtual CORBA::ULong bound()
        throw(CORBA::SystemException);
    virtual void bound(CORBA::ULong)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/SequenceDef/element_type:1.0
    //
    virtual CORBA::TypeCode_ptr element_type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/SequenceDef/element_type_def:1.0
    //
    virtual IR__::IDLType_ptr element_type_def()
        throw(CORBA::SystemException);
    virtual void element_type_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);
};

//
// ArrayDef_impl
//
class ArrayDef_impl : public virtual POA_IR__::ArrayDef,
						public virtual IDLType_impl
{
	CORBA::ULong length_;
	IDLType_impl *element_type_;
public:
	ArrayDef_impl ( Repository_impl *repository );

	~ArrayDef_impl();

	CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq );

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
	{
		return CORBA__::dk_Array;
	}

    //
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ArrayDef/length:1.0
    //
    virtual CORBA::ULong length()
        throw(CORBA::SystemException);
    virtual void length(CORBA::ULong)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ArrayDef/element_type:1.0
    //
    virtual CORBA::TypeCode_ptr element_type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ArrayDef/element_type_def:1.0
    //
    virtual IR__::IDLType_ptr element_type_def()
        throw(CORBA::SystemException);
    void element_type_def(IR__::IDLType_ptr)
        throw(CORBA::SystemException);
};

//
// FixedDef_impl
//
class FixedDef_impl : public virtual POA_IR__::FixedDef,
						public virtual IDLType_impl
{
	CORBA::UShort digits_;
	CORBA::Short scale_;
public:
	FixedDef_impl ( Repository_impl *repository );

	~FixedDef_impl();

    CORBA::TypeCode_ptr build_recursive_type_code ( vector < Contained_impl* >& seq )
        throw (CORBA::SystemException)
    {
		DEBUG_OUTLINE ( "FixedDef_impl::build_recursive_type_code(...) called" );
        return type();
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
	{
		return CORBA__::dk_Fixed;
	}

    //
    // IDL:omg.org/IR__/IDLType/type:1.0
    //
    virtual CORBA::TypeCode_ptr type()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/FixedDef/digits:1.0
    //
    virtual CORBA::UShort digits()
        throw(CORBA::SystemException);
    virtual void digits(CORBA::UShort)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/FixedDef/scale:1.0
    //
    virtual CORBA::Short scale()
        throw(CORBA::SystemException);
    virtual void scale(CORBA::Short)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

