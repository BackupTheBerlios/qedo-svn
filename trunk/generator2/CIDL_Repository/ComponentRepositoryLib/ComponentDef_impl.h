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

#ifndef __COMPONENT_DEF_IMPL_H__
#define __COMPONENT_DEF_IMPL_H__

#include <CORBA.h>
#include "IFR_skel.h"
#include "InterfaceDef_impl.h"
#include "ProvidesDef_impl.h"
#include "UsesDef_impl.h"
#include "EmitsDef_impl.h"
#include "PublishesDef_impl.h"
#include "ConsumesDef_impl.h"
#include "Sink_impl.h"
#include "SourceDef_impl.h"
#include "SiSoDef_impl.h"

#include <vector>

using namespace std;

namespace QEDO_ComponentRepository {

class ComponentDef_impl : public virtual POA_IR__::ComponentDef,
							public virtual InterfaceDef_impl
{
	ComponentDef_impl *base_component_impl_;
	vector < InterfaceDef_impl* > supported_interface_impls_;
public:
	ComponentDef_impl ( Container_impl *container,
					    Repository_impl *repository,
						ComponentDef_impl *base_component_impl );

	~ComponentDef_impl();

    //
    // IDL:omg.org/CORBA__/IRObject/def_kind:1.0
    //
	virtual CORBA__::DefinitionKind def_kind()
        throw(CORBA::SystemException)
    {
        return CORBA__::dk_Component;
    }

    //
    // IDL:omg.org/CORBA__/IRObject/destroy:1.0
    //
    virtual void destroy()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/Contained/describe:1.0
    //
    virtual IR__::Contained::Description* describe()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/supported_interfaces:1.0
    //
    virtual IR__::InterfaceDefSeq* supported_interfaces()
        throw(CORBA::SystemException);
    virtual void supported_interfaces(const IR__::InterfaceDefSeq&)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/base_component:1.0
    //
    virtual IR__::ComponentDef_ptr base_component()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/provides_interfaces:1.0
    //
    virtual IR__::ProvidesDefSeq* provides_interfaces()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/uses_interfaces:1.0
    //
    virtual IR__::UsesDefSeq* uses_interfaces()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/emits_events:1.0
    //
    virtual IR__::EmitsDefSeq* emits_events()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/publishes_events:1.0
    //
    virtual IR__::PublishesDefSeq* publishes_events()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/consumes_events:1.0
    //
    virtual IR__::ConsumesDefSeq* consumes_events()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/sinks:1.0
    //
    virtual IR__::SinkDefSeq* sinks()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/sources:1.0
    //
    virtual IR__::SourceDefSeq* sources()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/sisos:1.0
    //
    virtual IR__::SiSoDefSeq* sisos()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/is_basic:1.0
    //
    virtual CORBA::Boolean is_basic()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/create_provides:1.0
    //
    virtual IR__::ProvidesDef_ptr create_provides(const char* id,
                                          const char* name,
                                          const char* version,
                                          IR__::InterfaceDef_ptr interface_type)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/create_uses:1.0
    //
    virtual IR__::UsesDef_ptr create_uses(const char* id,
                                  const char* name,
                                  const char* version,
                                  IR__::InterfaceDef_ptr interface_type,
                                  CORBA::Boolean is_multiple)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/create_emits:1.0
    //
    virtual IR__::EmitsDef_ptr create_emits(const char* id,
                                    const char* name,
                                    const char* version,
                                    IR__::EventDef_ptr value)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/create_publishes:1.0
    //
    virtual IR__::PublishesDef_ptr create_publishes(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::EventDef_ptr value)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/create_consumes:1.0
    //
    virtual IR__::ConsumesDef_ptr create_consumes(const char* id,
                                          const char* name,
                                          const char* version,
                                          IR__::EventDef_ptr value)
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/IR__/ComponentDef/create_sink:1.0
    //
	virtual IR__::SinkDef_ptr create_sink(const char* id,
                                          const char* name,
                                          const char* version,
                                          IR__::StreamTypeDef_ptr value)
        throw(CORBA::SystemException);


    //
    // IDL:omg.org/IR__/ComponentDef/create_source:1.0
    //
	virtual IR__::SourceDef_ptr create_source(const char* id,
                                          const char* name,
                                          const char* version,
                                          IR__::StreamTypeDef_ptr value)
        throw(CORBA::SystemException);


    //
    // IDL:omg.org/IR__/ComponentDef/create_siso:1.0
    //
	virtual IR__::SiSoDef_ptr create_siso(const char* id,
                                          const char* name,
                                          const char* version,
                                          IR__::StreamTypeDef_ptr value)
        throw(CORBA::SystemException);

	// All inherited create_* operations except create_attribute from
	// InterfaceDef and ContainerDef throw an exception
    //
    // IDL:omg.org/IR__/Container/create_module:1.0
    //
    virtual IR__::ModuleDef_ptr create_module(const char* id,
                                              const char* name,
                                              const char* version)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_constant:1.0
    //
    virtual IR__::ConstantDef_ptr create_constant(const char* id,
                                                  const char* name,
                                                  const char* version,
                                                  IR__::IDLType_ptr type,
                                                  const CORBA::Any& value)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_struct:1.0
    //
    virtual IR__::StructDef_ptr create_struct(const char* id,
                                              const char* name,
                                              const char* version,
                                              const IR__::StructMemberSeq& members)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_union:1.0
    //
    virtual IR__::UnionDef_ptr create_union(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::IDLType_ptr discriminator_type,
                                            const IR__::UnionMemberSeq& members)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_enum:1.0
    //
    virtual IR__::EnumDef_ptr create_enum(const char* id,
                                          const char* name,
                                          const char* version,
                                          const IR__::EnumMemberSeq& members)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_alias:1.0
    //
    virtual IR__::AliasDef_ptr create_alias(const char* id,
                                            const char* name,
                                            const char* version,
                                            IR__::IDLType_ptr original_type)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_interface:1.0
    //
    virtual IR__::InterfaceDef_ptr create_interface(const char* id,
                                                    const char* name,
                                                    const char* version,
                                                    const IR__::InterfaceDefSeq& base_interfaces,
                                                    CORBA::Boolean is_abstract)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

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
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_value_box:1.0
    //
    virtual IR__::ValueBoxDef_ptr create_value_box(const char* id,
                                                   const char* name,
                                                   const char* version,
                                                   IR__::IDLType_ptr original_type_def)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_exception:1.0
    //
    virtual IR__::ExceptionDef_ptr create_exception(const char* id,
                                                    const char* name,
                                                    const char* version,
                                                    const IR__::StructMemberSeq& members)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/Container/create_native:1.0
    //
    virtual IR__::NativeDef_ptr create_native(const char* id,
                                              const char* name,
                                              const char* version)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}

    //
    // IDL:omg.org/IR__/InterfaceDef/create_operation:1.0
    //
    virtual IR__::OperationDef_ptr create_operation(const char* id,
                                                    const char* name,
                                                    const char* version,
                                                    IR__::IDLType_ptr result,
                                                    IR__::OperationMode mode,
                                                    const IR__::ParDescriptionSeq& params,
                                                    const IR__::ExceptionDefSeq& exceptions,
                                                    const IR__::ContextIdSeq& contexts)
        throw(CORBA::SystemException)
	{
		throw CORBA::BAD_PARAM ( 7, CORBA::COMPLETED_NO );
	}
};

} // namespace QEDO_ComponentRepository

#endif

