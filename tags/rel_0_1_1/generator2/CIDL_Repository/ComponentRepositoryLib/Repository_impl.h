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

#ifndef __REPOSITORY_IMPL_H__
#define __REPOSITORY_IMPL_H__

#ifdef _WIN32
#pragma warning( disable : 4290 )
#endif
#include <CORBA.h>

#include "IFR_skel.h"
#include "Contained_impl.h"
#include "Container_impl.h"
#include "PrimitiveDef_impl.h"

#include <list>

using namespace std;

namespace QEDO_ComponentRepository {

class Repository_impl : public virtual POA_IR__::Repository,
								public virtual Container_impl
{
	CORBA::ORB_var orb_;

	PortableServer::POA_var poa_;

	list < Contained_impl* > ir_named_objects_;
	list < IRObject_impl* > ir_anonymous_objects_;

	// The PrimitiveDef objects
	PrimitiveDef_impl *pd_void_;
	PrimitiveDef_impl *pd_short_;
	PrimitiveDef_impl *pd_long_;
	PrimitiveDef_impl *pd_ushort_;
	PrimitiveDef_impl *pd_ulong_;
	PrimitiveDef_impl *pd_float_;
	PrimitiveDef_impl *pd_double_;
	PrimitiveDef_impl *pd_boolean_;
	PrimitiveDef_impl *pd_char_;
	PrimitiveDef_impl *pd_octet_;
	PrimitiveDef_impl *pd_any_;
	PrimitiveDef_impl *pd_TypeCode_;
	PrimitiveDef_impl *pd_Principal_;
	PrimitiveDef_impl *pd_string_;
	PrimitiveDef_impl *pd_objref_;
	PrimitiveDef_impl *pd_longlong_;
	PrimitiveDef_impl *pd_ulonglong_;
	PrimitiveDef_impl *pd_longdouble_;
	PrimitiveDef_impl *pd_wchar_;
	PrimitiveDef_impl *pd_wstring_;
	PrimitiveDef_impl *pd_value_base_;
public:
	Repository_impl ( CORBA::ORB_ptr orb, PortableServer::POA_ptr poa );
	
	~Repository_impl ();

	virtual void destroy_repository();

	// Get ORB
	CORBA::ORB_ptr orb() { return CORBA::ORB::_duplicate ( orb_ ); }

	// Get POA
	PortableServer::POA_ptr poa() { return PortableServer::POA::_duplicate ( poa_ ); }

	// Check for an id in the global ir object map
	bool check_for_id ( const char *id );

	// Add a global id to ir object map
	bool add_id ( const char *id, Contained_impl *contained );
	
	// Remove a global id from ir object map
	bool remove_id ( const char *id );

	// Return an ir object from the global object map for a given id
	Contained_impl* resolve_id ( const char *id );

	// Remove an anonymous objects from the anonymous object map
	bool remove_anonymous ( IRObject_impl* anonymous );

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
		return CORBA__::dk_Repository;
	}

    //
    // IDL:omg.org/IR__/Repository/lookup_id:1.0
    //
    virtual IR__::Contained_ptr lookup_id(const char* search_id)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/get_canonical_typecode:1.0
    //
    virtual CORBA::TypeCode_ptr get_canonical_typecode(CORBA::TypeCode_ptr tc)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/get_primitive:1.0
    //
    virtual IR__::PrimitiveDef_ptr get_primitive(IR__::PrimitiveKind kind)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/create_string:1.0
    //
    virtual IR__::StringDef_ptr create_string(CORBA::ULong bound)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/create_wstring:1.0
    //
    virtual IR__::WstringDef_ptr create_wstring(CORBA::ULong bound)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/create_sequence:1.0
    //
    virtual IR__::SequenceDef_ptr create_sequence(CORBA::ULong bound,
                                                  IR__::IDLType_ptr element_type)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/create_array:1.0
    //
    virtual IR__::ArrayDef_ptr create_array(CORBA::ULong length,
                                            IR__::IDLType_ptr element_type)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Repository/create_fixed:1.0
    //
    virtual IR__::FixedDef_ptr create_fixed(CORBA::UShort digits,
                                            CORBA::Short scale)
        throw(CORBA::SystemException);
};

} // namespace QEDO_ComponentRepository

#endif

