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

#ifndef __CONTAINER_IMPL_H__
#define __CONTAINER_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "IRObject_impl.h"
#include "Contained_impl.h"

#include <list>

using namespace std;

namespace QEDO_ComponentRepository {

class Container_impl : public virtual POA_IR__::Container,
						public virtual IRObject_impl
{
protected:
	list < Contained_impl* > contained_;
public:
	Container_impl ( Repository_impl* );

	virtual ~Container_impl ();

	// Check for a name in the contained object list
	bool check_for_name ( const char* );

	// Add a name to contained object list
	bool add_name ( const char*, Contained_impl* );
	
	// Remove a name from contained object list
	bool remove_name ( const char* );

	// Resolve a name from the contained object list
	Contained_impl* resolve_name ( const char* );

	// Cat second sequence to the end of first sequence
	void contained_sequence_cat ( IR__::ContainedSeq& return_seq,
								IR__::ContainedSeq& cat_seq );
 
	// Check for illegal recusion
	void check_recursion ( const char* id, CORBA::TypeCode_ptr tc );

	//
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
	virtual void destroy()
		throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/lookup:1.0
    //
    virtual IR__::Contained_ptr lookup(const char* search_name)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/contents:1.0
    //
    virtual IR__::ContainedSeq* contents(CORBA__::DefinitionKind limit_type,
                                         CORBA::Boolean exclude_inherited)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/lookup_name:1.0
    //
    virtual IR__::ContainedSeq* lookup_name(const char* search_name,
                                            CORBA::Long levels_to_search,
                                            CORBA__::DefinitionKind limit_type,
                                            CORBA::Boolean exclude_inherited)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/describe_contents:1.0
    //
    virtual IR__::Container::DescriptionSeq* describe_contents(CORBA__::DefinitionKind limit_type,
                                                               CORBA::Boolean exclude_inherited,
                                                               CORBA::Long max_returned_objs)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_module:1.0
    //
    virtual IR__::ModuleDef_ptr create_module(const char* id,
                                              const char* name,
                                              const char* version)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_constant:1.0
    //
    virtual IR__::ConstantDef_ptr create_constant(const char* id,
                                                  const char* name,
                                                  const char* version,
                                                  IR__::IDLType_ptr type,
                                                  const CORBA::Any& value)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_struct:1.0
    //
    virtual IR__::StructDef_ptr create_struct(const char* id,
                                              const char* name,
                                              const char* version,
                                              const IR__::StructMemberSeq& members)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_union:1.0
    //
    virtual IR__::UnionDef_ptr create_union(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::IDLType_ptr discriminator_type,
                                            const IR__::UnionMemberSeq& members)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_enum:1.0
    //
    virtual IR__::EnumDef_ptr create_enum(const char* id,
                                          const char* name,
                                          const char* version,
                                          const IR__::EnumMemberSeq& members)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_alias:1.0
    //
    virtual IR__::AliasDef_ptr create_alias(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::IDLType_ptr original_type)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_interface:1.0
    //
    virtual IR__::InterfaceDef_ptr create_interface(const char* id,
                                                    const char* name,
                                                    const char* version,
                                                    const IR__::InterfaceDefSeq& base_interfaces,
                                                    CORBA::Boolean is_abstract)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_value:1.0
    //
    virtual IR__::ValueDef_ptr create_value(const char* id,
                                            const char* name,
                                            const char* version,
                                            CORBA::Boolean is_custom,
                                            CORBA::Boolean is_abstract,
                                            IR__::ValueDef_ptr base_value,
                                            CORBA::Boolean is_truncatable,
                                            const IR__::ValueDefSeq& abstract_base_values,
                                            const IR__::InterfaceDefSeq& supported_interfaces,
                                            const IR__::InitializerSeq& initializers)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_stream_type:1.0
    //
    virtual IR__::StreamTypeDef_ptr create_stream_type(const char* id,
                                            const char* name,
                                            const char* version)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_value_box:1.0
    //
    virtual IR__::ValueBoxDef_ptr create_value_box(const char* id,
                                                   const char* name,
                                                   const char* version,
                                                   IR__::IDLType_ptr original_type_def)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_exception:1.0
    //
    virtual IR__::ExceptionDef_ptr create_exception(const char* id,
                                                    const char* name,
                                                    const char* version,
                                                    const IR__::StructMemberSeq& members)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Container/create_native:1.0
    //
    virtual IR__::NativeDef_ptr create_native(const char* id,
                                              const char* name,
                                              const char* version)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentRepository/create_component:1.0
    //
    virtual IR__::ComponentDef_ptr create_component(const char* id,
                                                    const char* name,
                                                    const char* version,
                                                    IR__::ComponentDef_ptr base_component,
                                                    const IR__::InterfaceDefSeq& supports_interfaces)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentRepository/create_home:1.0
    //
    virtual IR__::HomeDef_ptr create_home(const char* id,
                                          const char* name,
                                          const char* version,
                                          IR__::HomeDef_ptr base_home,
                                          IR__::ComponentDef_ptr managed_component,
										  const IR__::InterfaceDefSeq& supports_interfaces,
                                          IR__::ValueDef_ptr primary_key)
        throw(CORBA::SystemException);
};


} // namespace QEDO_ComponentRepository

#endif

