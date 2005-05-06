
#ifndef REPOSITORY_CONNECTOR_H_
#define REPOSITORY_CONNECTOR_H_

//#include "stdafx.h"
#include <fstream>
#include "Exceptions.h"
#include "MDE.h"
#include "RepositoryRoot.h"


using namespace std;

namespace CCMGenerator {

class RepositoryConnector
{
	::Reflective::RefPackageSet* _package_set;

public:
	
	void set_package_set ( ::Reflective::RefPackageSet* );
	MDE::MDEPackage_var _mde_package;
	MDE::BaseIDL::BaseIDLPackage_var _base_idl_pkg_ref;
	
	//BaseIDL Package
	MDE::BaseIDL::TypedClass_var _typed_ref;
	MDE::BaseIDL::IDLTypeClass_var _idltype_ref;
	MDE::BaseIDL::TypedBy_var _typed_by_ref;
	MDE::BaseIDL::ParameterDefClass_var _parameter_def_ref;
	MDE::BaseIDL::ContainedClass_var _contained_ref;
	MDE::BaseIDL::ContainerClass_var _container_ref;
	MDE::BaseIDL::Contains_var _contains_ref;
	MDE::BaseIDL::ConstantDefClass_var _constant_def_ref;
	MDE::BaseIDL::ModuleDefClass_var _module_def_ref;
	MDE::BaseIDL::TypedefDefClass_var _typedef_def_ref;
	MDE::BaseIDL::FieldClass_var _field_ref;
	MDE::BaseIDL::StructDefClass_var _struct_def_ref;
	MDE::BaseIDL::UnionDefClass_var _union_def_ref;
	MDE::BaseIDL::UnionFieldClass_var _union_field_ref;
	MDE::BaseIDL::DiscriminatedBy_var _discriminated_by_ref;
	MDE::BaseIDL::EnumDefClass_var _enum_def_ref;
	MDE::BaseIDL::AliasDefClass_var _alias_def_ref;
	MDE::BaseIDL::StringDefClass_var _string_def_ref;
	MDE::BaseIDL::WstringDefClass_var _wstring_def_ref;
	MDE::BaseIDL::FixedDefClass_var _fixed_def_ref;
	MDE::BaseIDL::SequenceDefClass_var _sequence_def_ref;
	MDE::BaseIDL::ArrayDefClass_var _array_def_ref;
	MDE::BaseIDL::PrimitiveDefClass_var _primitive_def_ref;
	MDE::BaseIDL::ValueMemberDefClass_var _value_member_def_ref;
	MDE::BaseIDL::ValueDefClass_var _value_def_ref;
	MDE::BaseIDL::InterfaceDefClass_var _interface_def_ref;
	MDE::BaseIDL::InterfaceDerivedFrom_var _interface_derived_from_ref;
	MDE::BaseIDL::Supportss_var _supportss_ref;
	MDE::BaseIDL::ValueDerivedFrom_var _value_derived_from_ref;
	MDE::BaseIDL::AbstractDerivedFrom_var _abstract_derived_from_ref;
	MDE::BaseIDL::ValueBoxDefClass_var _value_box_def_ref;
	MDE::BaseIDL::OperationDefClass_var _operation_def_ref;
	MDE::BaseIDL::ExceptionDefClass_var _exception_def_ref;
	MDE::BaseIDL::CanRaise_var _can_raise_ref;
	MDE::BaseIDL::AttributeDefClass_var _attribute_def_ref;
	MDE::BaseIDL::SetRaisesEx_var _set_raises_ex_ref;
	MDE::BaseIDL::GetRaisesEx_var _get_raises_ex_ref;
	MDE::BaseIDL::ValueFactoryDefClass_var _value_factory_def_ref;

	void connectRepository (/*::Reflective::RefPackageSet**/);

public:
	RepositoryConnector (/*::Reflective::RefPackageSet* */);
	//RepositoryConnector ( );
	virtual ~RepositoryConnector();

	MDE::BaseIDL::ModuleDef_var _root;

	Reflective::RefObject_ptr internal_lookup_simple ( MDE::BaseIDL::Container_ptr base, const char* simple_name );
	Reflective::RefObject_ptr internal_lookup_scoped ( MDE::BaseIDL::Container_ptr base, const char* name );

	std::string get_absolute_name ( MDE::BaseIDL::Contained_ptr obj );

	// ContainedDef
	// lookup with relative name, starting at base container
	MDE::BaseIDL::Contained_ptr lookup_contained ( MDE::BaseIDL::Container_ptr base, const char* name );
	// lookup with full scoped name "::CORBA::some_type"
	MDE::BaseIDL::Contained_ptr lookup_contained ( const char* name );
	bool test_contained ( const char* name );

	// ContainerDef
	MDE::BaseIDL::Container_ptr lookup_container ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::Container_ptr lookup_container ( const char* name );
	bool test_container ( const char* name );

	// ModuleDef
	MDE::BaseIDL::ModuleDef_ptr lookup_module ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::ModuleDef_ptr lookup_module ( const char* name );
	bool test_module ( const char* name );

	// InterfaceDef
	MDE::BaseIDL::InterfaceDef_ptr lookup_interface ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::InterfaceDef_ptr lookup_interface ( const char* name );
	bool test_interface ( const char* name );

	// ValueDef
	MDE::BaseIDL::ValueDef_ptr lookup_value ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::ValueDef_ptr lookup_value ( const char* name );
	bool test_value ( const char* name );

	// ExceptionDef
	MDE::BaseIDL::ExceptionDef_ptr lookup_exception ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::ExceptionDef_ptr lookup_exception ( const char* name );
	bool test_exception ( const char* name );

	// StructDef
	MDE::BaseIDL::StructDef_ptr lookup_struct ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::StructDef_ptr lookup_struct ( const char* name );
	bool test_struct ( const char* name );

	// UnionDef
	MDE::BaseIDL::UnionDef_ptr lookup_union ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::UnionDef_ptr lookup_union ( const char* name );
	bool test_union ( const char* name );

	// TypedefDef
	MDE::BaseIDL::TypedefDef_ptr lookup_typedef ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::TypedefDef_ptr lookup_typedef ( const char* name );
	bool test_typedef ( const char* name );

	// EnumDef
	MDE::BaseIDL::EnumDef_ptr lookup_enum ( MDE::BaseIDL::Container_ptr base, const char* name );
	MDE::BaseIDL::EnumDef_ptr lookup_enum ( const char* name );
	bool test_enum ( const char* name );

	void set_defined_in ( MDE::BaseIDL::Container_ptr container, MDE::BaseIDL::Contained_ptr contained );


};

//CCMRepositoryConnector

class CCMRepositoryConnector : public virtual RepositoryConnector 
{

public:

	MDE::CIF::CIFPackage_var _cif_ref;
	MDE::ComponentIDL::ComponentIDLPackage_var _component_idl_ref;
	MDE::Deployment::DeploymentPackage_var _deployment_ref;

	// classes
	// Deployment package
	MDE::Deployment::AssemblyClass_var							_assembly_ref;
	MDE::Deployment::PropOwnerClass_var							_prop_owner_ref;
	MDE::Deployment::PropertyClass_var							_property_ref;
	MDE::Deployment::DeploymentUnitClass_var					_deployment_unit_ref;
	MDE::Deployment::FileClass_var								_file_ref;
	MDE::Deployment::DependentFileClass_var						_dependent_file_ref;
	MDE::Deployment::DeploymentRequirementClass_var				_deployment_requirement_ref;
	MDE::Deployment::ContainedFileClass_var						_contained_file_ref;
	MDE::Deployment::RuleOwnerClass_var							_rule_owner_ref;
	MDE::Deployment::RuleClass_var								_rule_ref;
	MDE::Deployment::ConfigurationClass_var						_configuration_ref;
	MDE::Deployment::ConnectionClass_var						_connection_ref;
	MDE::Deployment::ConnectionEndClass_var						_connection_end_ref;
	MDE::Deployment::ComponentInstantiationClass_var			_component_instantiation_ref;
	MDE::Deployment::RegisterComponentInstanceClass_var			_register_component_instance_ref;
	MDE::Deployment::ExternalInstanceClass_var					_external_instance_ref;
	MDE::Deployment::FinderServiceClass_var						_finder_service_ref;
	MDE::Deployment::HomeInstantiationClass_var					_home_instantiation_ref;
	MDE::Deployment::InstallationClass_var						_installation_ref;
	MDE::Deployment::ProcessCollocationClass_var				_process_collocation_ref;
	

	// CIF Package
	MDE::CIF::ArtifactDefClass_var								_artifact_def_ref;
	MDE::CIF::SegmentDefClass_var								_segment_def_ref;	
	MDE::CIF::PolicyClass_var									_policy_ref;	
	MDE::CIF::ComponentImplDefClass_var							_component_impl_def_ref;	
	MDE::CIF::HomeImplDefClass_var								_home_impl_def_ref;
	// Component Package
	MDE::ComponentIDL::ComponentFeatureClass_var				_component_feature_ref;
	MDE::ComponentIDL::ComponentDefClass_var					_component_def_ref;
	MDE::ComponentIDL::ProvidesDefClass_var						_provides_def_ref;
	MDE::ComponentIDL::HomeDefClass_var							_home_def_ref;
	MDE::ComponentIDL::ComponentHome_var						_component_home_ref;
	MDE::ComponentIDL::FactoryDefClass_var						_factory_def_ref;
	MDE::ComponentIDL::FinderDefClass_var						_finder_def_ref;
	MDE::ComponentIDL::EventPortDefClass_var					_event_port_def_ref;
	MDE::ComponentIDL::EventDefClass_var						_event_def_ref;	
	MDE::ComponentIDL::EmitsDefClass_var						_emits_def_ref;
	MDE::ComponentIDL::ConsumesDefClass_var						_consumes_def_ref;
	MDE::ComponentIDL::UsesDefClass_var							_uses_def_ref;
	MDE::ComponentIDL::PublishesDefClass_var					_publishes_def_ref;
	MDE::ComponentIDL::StreamPortDefClass_var					_stream_port_def_ref;
	MDE::ComponentIDL::MediaTypeClass_var						_media_type_ref;	
	MDE::ComponentIDL::SourceDefClass_var						_source_def_ref;
	MDE::ComponentIDL::SinkDefClass_var							_sink_def_ref;
	MDE::ComponentIDL::SiSouDefClass_var						_si_sou_def_ref;	
	MDE::BaseIDL::ContainerClass_var							_containerClass;
	
	// associations
	// CIF Package
	MDE::CIF::ImplementedBy_var									_implemented_by_ref;
	MDE::CIF::SegmentArtifact_var								_segment_artifact_ref;
	MDE::CIF::AssPolicies_var									_ass_policies_ref;
	MDE::CIF::HomeImplements_var								_home_implements_ref;
	MDE::CIF::ComponentImplements_var							_component_implements_ref;
	MDE::CIF::Manages_var										_manages_ref;
	// Component Package
	MDE::ComponentIDL::EventTypeAss_var							_event_type_ass_ref;
	MDE::ComponentIDL::MediatoType_var							_mediato_type_ref;
	MDE::ComponentIDL::Sinks_var								_sinks_ref;
	MDE::ComponentIDL::Sources_var								_sources_ref;
	MDE::ComponentIDL::SiSous_var								_si_sous_ref;
	

public:
	CCMRepositoryConnector (/*::Reflective::RefPackageSet**/  );
	//CCMRepositoryConnector ( );
	virtual ~CCMRepositoryConnector ();

	void connectRepository ( );
};


}

#endif