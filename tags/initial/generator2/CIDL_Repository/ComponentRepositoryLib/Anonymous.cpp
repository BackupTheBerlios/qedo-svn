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

#include "Anonymous.h"
#include "Repository_impl.h"
#include "Debug.h"

namespace QEDO_ComponentRepository {


//
// StringDef_impl
//
StringDef_impl::StringDef_impl
( Repository_impl *repository )
: IDLType_impl ( repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "StringDef_impl::StringDef_impl() called " );
	bound_ = 0;
}

StringDef_impl::~StringDef_impl
()
{
	DEBUG_OUTLINE ( "StringDef_impl::~StringDef_impl() called " );
}

void
StringDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StringDef_impl::destroy() called" );
	repository_ -> remove_anonymous ( this );
	IDLType_impl::destroy();
}

CORBA::ULong
StringDef_impl::bound
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StringDef_impl::bound() called " );

	if ( ! bound_ )
		throw CORBA::BAD_INV_ORDER();

	return bound_;
}

void
StringDef_impl::bound
( CORBA::ULong bound )
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "StringDef_impl::bound(...) called " );

	if ( ! ( bound > 0 ) )
		throw CORBA::BAD_PARAM();

	bound_ = bound;
}

CORBA::TypeCode_ptr
StringDef_impl::type()
    throw(CORBA::SystemException)
{
	return repository_ -> orb() -> create_string_tc ( bound_ );
}

//
// WstringDef impl
//
WstringDef_impl::WstringDef_impl
( Repository_impl *repository )
: IDLType_impl ( repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "WstringDef_impl::WstringDef_impl() called " );
	bound_ = 0;
}

WstringDef_impl::~WstringDef_impl
()
{
	DEBUG_OUTLINE ( "WstringDef_impl::~WstringDef_impl() called " );
}

void
WstringDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "WstringDef_impl::destroy() called" );
	repository_ -> remove_anonymous ( this );
	IDLType_impl::destroy();
}

CORBA::ULong
WstringDef_impl::bound
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "WstringDef_impl::bound() called " );

	if ( ! bound_ )
		throw CORBA::BAD_INV_ORDER();

	return bound_;
}

void
WstringDef_impl::bound
( CORBA::ULong bound )
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "WstringDef_impl::bound(...) called " );

	if ( ! ( bound > 0 ) )
		throw CORBA::BAD_PARAM();

	bound_ = bound;
}

CORBA::TypeCode_ptr
WstringDef_impl::type()
    throw(CORBA::SystemException)
{
	return repository_ -> orb() -> create_wstring_tc ( bound_ );
}

//
// SequenceDef_impl
//
SequenceDef_impl::SequenceDef_impl
( Repository_impl *repository )
: IDLType_impl ( repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "SequenceDef_impl::SequenceDef_impl() called " );
	bound_ = 0;
	element_type_ = NULL;
}

SequenceDef_impl::~SequenceDef_impl
()
{
	DEBUG_OUTLINE ( "SequenceDef_impl::~SequenceDef_impl() called " );
	if ( element_type_ )
		element_type_ -> _remove_ref();
}

void
SequenceDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SequenceDef_impl::destroy() called" );
	
	if ( element_type_ )
		element_type_ -> _remove_ref();

	repository_ -> remove_anonymous ( this );
	IDLType_impl::destroy();
}

CORBA::TypeCode_ptr
SequenceDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
	DEBUG_OUTLINE ( "SequenceDef_impl::build_recursive_type_code(...) called" );

     if(!element_type_)
         throw CORBA::BAD_INV_ORDER();

	 CORBA::TypeCode_var tc;

     Contained_impl* contained = dynamic_cast<Contained_impl*>(element_type_);
     if(contained)
     {
		 IR__::RepositoryId_var id = contained -> id();
         for(unsigned int i = 0 ; i < seq.size() ; i++)
         {
			 IR__::RepositoryId_var id2 = seq[i] -> id();
             if(strcmp(id, id2) == 0)
             {
                 //
                 // An alias can be recursive if it's an alias for a
                 // valuetype (this is from ORBacus)
                 //
				 CORBA__::DefinitionKind elem_def_kind = contained -> def_kind();
                 if(elem_def_kind != CORBA__::dk_Struct &&
					 elem_def_kind != CORBA__::dk_Exception &&
					 elem_def_kind != CORBA__::dk_Union &&
					 elem_def_kind != CORBA__::dk_Value &&
					 elem_def_kind != CORBA__::dk_Alias)
                 {
                     throw CORBA::INTF_REPOS ( 3, CORBA::COMPLETED_NO );
                 }

                 tc = repository_ -> orb() -> create_recursive_tc(id);
                 break;
             }
         }
     }

     if ( CORBA::is_nil(tc) )
         tc = element_type_ -> build_recursive_type_code(seq);

     return repository_ -> orb() -> create_sequence_tc(bound_, tc);
}

CORBA::TypeCode_ptr
SequenceDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SequenceDef_impl::type() called" );

    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var tc = build_recursive_type_code(helper_seq);
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    return tc._retn();
}

CORBA::ULong
SequenceDef_impl::bound
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SequenceDef_impl::bound() called " );

	return bound_;
}

void
SequenceDef_impl::bound
(CORBA::ULong bound)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SequenceDef_impl::bound(...) called " );

	if ( ! ( bound >= 0 ) )
		throw CORBA::BAD_PARAM();

	bound_ = bound;
}

CORBA::TypeCode_ptr
SequenceDef_impl::element_type
()
throw(CORBA::SystemException)
{
    if(!element_type_)
        throw CORBA::BAD_INV_ORDER();

    return element_type_ -> type();
}

IR__::IDLType_ptr
SequenceDef_impl::element_type_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SequenceDef_impl::element_type_def() called " );

	if ( ! element_type_ )
		throw CORBA::BAD_INV_ORDER();

	return element_type_ -> _this();
}

void
SequenceDef_impl::element_type_def
(IR__::IDLType_ptr type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "SequenceDef_impl::element_type_def(...) called " );

	if ( CORBA::is_nil ( type ) )
	{
		DEBUG_ERRLINE ( "nil object reference passed to SequenceDef_impl::element_type_def()" );
		throw CORBA::BAD_PARAM();
	}

	IDLType_impl* impl = 0;

    try
    {
		PortableServer::ServantBase_var servant = 
			repository_ -> poa() -> reference_to_servant(type);
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be in the same repository
        throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
    }

	impl -> _add_ref();
	if(element_type_)
		element_type_ -> _remove_ref();
	element_type_ = impl;
}

//
// ArrayDef_impl
//
ArrayDef_impl::ArrayDef_impl
( Repository_impl *repository )
: IDLType_impl ( repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "ArrayDef_impl::ArrayDef_impl() called " );
	length_ = 0;
	element_type_ = NULL;
}

ArrayDef_impl::~ArrayDef_impl
()
{
	DEBUG_OUTLINE ( "ArrayDef_impl::~ArrayDef_impl() called " );
	if ( element_type_ )
		element_type_ -> _remove_ref();
}

void
ArrayDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ArrayDef_impl::destroy() called" );

	if ( element_type_ )
		element_type_ -> _remove_ref();

	repository_ -> remove_anonymous ( this );
	IDLType_impl::destroy();
}

CORBA::TypeCode_ptr
ArrayDef_impl::build_recursive_type_code
( vector < Contained_impl* >& seq )
{
	DEBUG_OUTLINE ( "ArrayDef_impl::build_recursive_type_code(...) called" );

     if(!element_type_)
         throw CORBA::BAD_INV_ORDER();

	 CORBA::TypeCode_var tc;

     Contained_impl* contained =
         dynamic_cast<Contained_impl*>(element_type_);
     if(contained)
     {
		 IR__::RepositoryId_var id = contained -> id();
         for(unsigned int i = 0 ; i < seq.size() ; i++)
         {
			 IR__::RepositoryId_var id2 = seq[i] -> id();
             if(strcmp(id, id2) == 0)
             {
                 //
                 // An array can only be recursive if its element type is
                 // a valuetype. Skip any aliases to determine the original
                 // element type ( this is from ORBacus )
                 //
				 CORBA__::DefinitionKind elem_def_kind = contained -> def_kind();
                 if(elem_def_kind == CORBA__::dk_Alias)
                 {/*  TODO
                     AliasDef_impl* aliasImpl =
                         dynamic_cast<AliasDef_impl*>(contained);
					 IR__::IDLType_var type = aliasImpl -> original_type_def();
                     elem_def_kind = type -> def_kind();
                     while(elem_def_kind == CORBA__::dk_Alias)
                     {
						 IR__::AliasDef_var alias = IR__::AliasDef::_narrow(type);
                         type = alias -> original_type_def();
                         elem_def_kind = type -> def_kind();
                     }*/
                 }
                 if(elem_def_kind != CORBA__::dk_Value)
                 {
                     throw CORBA::INTF_REPOS ( 3, CORBA::COMPLETED_NO );
                 }

                 tc = repository_ -> orb() -> create_recursive_tc(id);
                 break;
             }
         }
     }

     if(CORBA::is_nil(tc))
         tc = element_type_ -> build_recursive_type_code(seq);

     return repository_ -> orb() -> create_array_tc(length_, tc);
}

CORBA::TypeCode_ptr 
ArrayDef_impl::type
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ArrayDef_impl::type() called" );

    vector < Contained_impl* > helper_seq;
	CORBA::TypeCode_var tc = build_recursive_type_code ( helper_seq );
	if ( helper_seq.size() != 0 )
		throw CORBA::BAD_INV_ORDER();	// Is this correct?
    return tc._retn();
}

CORBA::ULong 
ArrayDef_impl::length
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ArrayDef_impl::length() called " );

	if ( ! length_ )
		throw CORBA::BAD_INV_ORDER();

	return length_;
}

void
ArrayDef_impl::length
(CORBA::ULong length)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ArrayDef_impl::length(...) called " );

	if ( ! ( length > 0 ) )
		throw CORBA::BAD_PARAM();

	length_ = length;
}

CORBA::TypeCode_ptr
ArrayDef_impl::element_type
()
throw(CORBA::SystemException)
{
    if(!element_type_)
        throw CORBA::BAD_INV_ORDER();

    return element_type_ -> type();
}

IR__::IDLType_ptr
ArrayDef_impl::element_type_def
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ArrayDef_impl::element_type_def() called " );

	if ( ! element_type_ )
		throw CORBA::BAD_INV_ORDER();

	return element_type_ -> _this();

}

void
ArrayDef_impl::element_type_def
(IR__::IDLType_ptr type)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "ArrayDef_impl::element_type_def(...) called " );

	if ( CORBA::is_nil ( type ) )
	{
		DEBUG_ERRLINE ( "nil object reference passed to ArrayDef_impl::element_type_def()" );
		throw CORBA::BAD_PARAM();
	}

	IDLType_impl* impl = 0;

    try
    {
		PortableServer::ServantBase_var servant = 
			repository_ -> poa() -> reference_to_servant(type);
        impl = dynamic_cast<IDLType_impl*>(servant.in());
    }
    catch(...)
    {
    }
    if(!impl)
    {
        // Must be in the same repository
        throw CORBA::BAD_PARAM(4, CORBA::COMPLETED_NO);
    }

	impl -> _add_ref();
	if(element_type_)
		element_type_ -> _remove_ref();
	element_type_ = impl;
}

//
// FixedDef_impl
//
FixedDef_impl::FixedDef_impl
( Repository_impl *repository )
: IDLType_impl ( repository ),
  IRObject_impl ( repository )
{
	DEBUG_OUTLINE ( "FixedDef_impl::FixedDef_impl() called " );
	digits_ = 0;
	scale_ = 0;
}

FixedDef_impl::~FixedDef_impl
()
{
	DEBUG_OUTLINE ( "FixedDef_impl::~FixedDef_impl() called " );
}

void
FixedDef_impl::destroy
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FixedDef_impl::destroy() called" );
	repository_ -> remove_anonymous ( this );
	IDLType_impl::destroy();
}

CORBA::TypeCode_ptr
FixedDef_impl::type
()
throw(CORBA::SystemException)
{
    return repository_ -> orb() -> create_fixed_tc ( digits_, scale_ );
}

CORBA::UShort
FixedDef_impl::digits
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FixedDef_impl::digits() called" );
	return digits_;
}

void
FixedDef_impl::digits
(CORBA::UShort digits)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FixedDef_impl::digits(...) called" );
	digits_ = digits;
}

CORBA::Short
FixedDef_impl::scale
()
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FixedDef_impl::scale() called" );
	return scale_;
}

void
FixedDef_impl::scale
(CORBA::Short scale)
throw(CORBA::SystemException)
{
	DEBUG_OUTLINE ( "FixedDef_impl::scale(...) called" );
	scale_ = scale;
}

} // namespace QEDO_ComponentRepository
