#include "RepositoryConnector.h"

namespace CCMGenerator {
//BaseIDL RepositoryConnector: basis class
RepositoryConnector::RepositoryConnector ( /*::Reflective::RefPackageSet* package_set*/ ):

	_package_set(),
	_mde_package (),
	_base_idl_pkg_ref (),
	_typed_ref (),
	_idltype_ref (),
	_typed_by_ref (),
	_parameter_def_ref (),
	_contained_ref (),
	_container_ref (),
	_contains_ref (),
	_constant_def_ref (),
	_module_def_ref (),
	_typedef_def_ref (),
	_field_ref (),
	_struct_def_ref (),
	_union_def_ref (),
	_union_field_ref (),
	_discriminated_by_ref (),
	_enum_def_ref (),
	_alias_def_ref (),
	_string_def_ref (),
	_wstring_def_ref (),
	_fixed_def_ref (),
	_sequence_def_ref (),
	_array_def_ref (),
	_primitive_def_ref (),
	_value_member_def_ref (),
	_value_def_ref (),
	_interface_def_ref (),
	_interface_derived_from_ref (),
	_supportss_ref (),
	_value_derived_from_ref (),
	_abstract_derived_from_ref (),
	_value_box_def_ref (),
	_operation_def_ref (),
	_exception_def_ref (),
	_can_raise_ref (),
	_attribute_def_ref (),
	_set_raises_ex_ref (),
	_get_raises_ex_ref (),
	_value_factory_def_ref (),
	_root ()
{
	//this->connectRepository( _package_set );
}

/*RepositoryConnector::RepositoryConnector ( )
{}*/
void RepositoryConnector::set_package_set ( ::Reflective::RefPackageSet* package_set )
{
	_package_set = package_set;
}

RepositoryConnector::~RepositoryConnector ()
{
}

void RepositoryConnector::connectRepository ( /*Reflective::RefPackageSet* package_set_*/ )
{
	CORBA::Object_var obj_;
	_mde_package = MDE::MDEPackage::_narrow ( (*_package_set)[0] );

	if ( CORBA::is_nil ( _mde_package ) ) 
		throw NilObjectRef ( "Nil reference for mde package: Is repository running???" );

	obj_ = _mde_package->base_idl_ref ();
	_base_idl_pkg_ref = MDE::BaseIDL::BaseIDLPackage::_narrow ( obj_ );
	if ( CORBA::is_nil ( _base_idl_pkg_ref ) ) 
		throw NilObjectRef ( "Nil reference for base_idl package: Is repository running???" );

	_typed_ref = _base_idl_pkg_ref->typed_ref ();
	_idltype_ref = _base_idl_pkg_ref->idltype_ref ();
	_typed_by_ref = _base_idl_pkg_ref->typed_by_ref ();
	_parameter_def_ref = _base_idl_pkg_ref->parameter_def_ref ();
	_contained_ref = _base_idl_pkg_ref->contained_ref ();
	_container_ref = _base_idl_pkg_ref->container_ref ();
	_contains_ref = _base_idl_pkg_ref->contains_ref ();
	_constant_def_ref = _base_idl_pkg_ref->constant_def_ref ();
	_module_def_ref = _base_idl_pkg_ref->module_def_ref ();
	_typedef_def_ref = _base_idl_pkg_ref->typedef_def_ref ();
	_field_ref = _base_idl_pkg_ref->field_ref ();
	_struct_def_ref = _base_idl_pkg_ref->struct_def_ref ();
	_union_def_ref = _base_idl_pkg_ref->union_def_ref ();
	_union_field_ref = _base_idl_pkg_ref->union_field_ref ();
	_discriminated_by_ref = _base_idl_pkg_ref->discriminated_by_ref ();
	_enum_def_ref = _base_idl_pkg_ref->enum_def_ref ();
	_alias_def_ref = _base_idl_pkg_ref->alias_def_ref ();
	_string_def_ref = _base_idl_pkg_ref->string_def_ref ();
	_wstring_def_ref = _base_idl_pkg_ref->wstring_def_ref ();
	_fixed_def_ref = _base_idl_pkg_ref->fixed_def_ref ();
	_sequence_def_ref = _base_idl_pkg_ref->sequence_def_ref ();
	_array_def_ref = _base_idl_pkg_ref->array_def_ref ();
	_primitive_def_ref = _base_idl_pkg_ref->primitive_def_ref ();
	_value_member_def_ref = _base_idl_pkg_ref->value_member_def_ref ();
	_value_def_ref = _base_idl_pkg_ref->value_def_ref ();
	_interface_def_ref = _base_idl_pkg_ref->interface_def_ref ();
	_interface_derived_from_ref = _base_idl_pkg_ref->interface_derived_from_ref ();
	_supportss_ref = _base_idl_pkg_ref->supportss_ref ();
	_value_derived_from_ref = _base_idl_pkg_ref->value_derived_from_ref ();
	_abstract_derived_from_ref = _base_idl_pkg_ref->abstract_derived_from_ref ();
	_value_box_def_ref = _base_idl_pkg_ref->value_box_def_ref ();
	_operation_def_ref = _base_idl_pkg_ref->operation_def_ref ();
	_exception_def_ref = _base_idl_pkg_ref->exception_def_ref ();
	_can_raise_ref = _base_idl_pkg_ref->can_raise_ref ();
	_attribute_def_ref = _base_idl_pkg_ref->attribute_def_ref ();
	_set_raises_ex_ref = _base_idl_pkg_ref->set_raises_ex_ref ();
	_get_raises_ex_ref = _base_idl_pkg_ref->get_raises_ex_ref ();
	_value_factory_def_ref = _base_idl_pkg_ref->value_factory_def_ref ();

}

Reflective::RefObject_ptr RepositoryConnector::internal_lookup_simple ( MDE::BaseIDL::Container_ptr base, const char* simple_name ) {

	std::string name_( simple_name );

	if ( name_.empty () )
		throw NotFoundInRep ( "Empty name", simple_name );

	MDE::BaseIDL::ContainedSet_var set = base->contents();
	unsigned long idx = 0;
	while ( idx < set->length() ) 
	{
		std::string str1 ( (*set)[idx]->identifier() );
		if ( strcmp ( (*set)[idx]->identifier(), simple_name ) == 0 ) 
			return MDE::BaseIDL::Contained::_duplicate ( (*set)[idx] );
		++idx;
	}

	throw NotFoundInRep ( "Not found", simple_name );

	return MDE::BaseIDL::Contained::_nil();
}

Reflective::RefObject_ptr RepositoryConnector::internal_lookup_scoped ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ret = base->lookup ( name );

	if ( CORBA::is_nil ( ret ) )
		throw NotFoundInRep ( name, "" );

	return ret._retn ();
}

std::string RepositoryConnector::get_absolute_name ( MDE::BaseIDL::Contained_ptr obj ) 
{
	std::string ret;

	if ( strcmp ( obj->identifier (), "" ) == 0 )
		return "::";

	if ( strcmp ( obj->defined_in ()->identifier (), "" ) != 0 )
	{
		ret =
			this->get_absolute_name ( obj->defined_in () );
	}

	ret += "::";
	CORBA::String_var str = obj->identifier ();
	ret += str;

	return ret;
}

MDE::BaseIDL::Contained_ptr RepositoryConnector::lookup_contained ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::Contained_var ret_ = MDE::BaseIDL::Contained::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a contained", "" );

	return ret_._retn();
}

MDE::BaseIDL::Contained_ptr RepositoryConnector::lookup_contained ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_contained ( _root, name + 2 );
}

bool RepositoryConnector::test_contained ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::Contained_var tmp =
			this->lookup_contained ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::Container_ptr RepositoryConnector::lookup_container ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::Container_var ret_ = MDE::BaseIDL::Container::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a container", name );

	return ret_._retn();
}

MDE::BaseIDL::Container_ptr RepositoryConnector::lookup_container ( const char* name ) {

	if ( strlen ( name ) == 0 )
		return MDE::BaseIDL::ModuleDef::_duplicate ( _root );

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_container ( _root, name + 2 );
}

bool RepositoryConnector::test_container ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::Container_var tmp =
			this->lookup_container ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::ModuleDef_ptr RepositoryConnector::lookup_module ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	if ( strlen ( name ) == 0 )
		return MDE::BaseIDL::ModuleDef::_duplicate ( _root );

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::ModuleDef_var ret_ = MDE::BaseIDL::ModuleDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a module", name );

	return ret_._retn();
}

MDE::BaseIDL::ModuleDef_ptr RepositoryConnector::lookup_module ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_module ( _root, name + 2 );
}

bool RepositoryConnector::test_module ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::ModuleDef_var tmp =
			this->lookup_module ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::InterfaceDef_ptr RepositoryConnector::lookup_interface ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::InterfaceDef_var ret_ = MDE::BaseIDL::InterfaceDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not an interface", name );

	return ret_._retn();
}

MDE::BaseIDL::InterfaceDef_ptr RepositoryConnector::lookup_interface ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name" , name);

	return this->lookup_interface ( _root, name + 2 );
}

bool RepositoryConnector::test_interface ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::InterfaceDef_var tmp =
			this->lookup_interface ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::ValueDef_ptr RepositoryConnector::lookup_value ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::ValueDef_var ret_ = MDE::BaseIDL::ValueDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a value", name );

	return ret_._retn();
}

MDE::BaseIDL::ValueDef_ptr RepositoryConnector::lookup_value ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_value ( _root, name + 2 );
}

bool RepositoryConnector::test_value ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::ValueDef_var tmp =
			this->lookup_value ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::ExceptionDef_ptr RepositoryConnector::lookup_exception ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::ExceptionDef_var ret_ = MDE::BaseIDL::ExceptionDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not an exception", name );

	return ret_._retn();
}

MDE::BaseIDL::ExceptionDef_ptr RepositoryConnector::lookup_exception ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name" , name);

	return this->lookup_exception ( _root, name + 2 );
}

bool RepositoryConnector::test_exception ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name" , name);

	try 
	{
		MDE::BaseIDL::ExceptionDef_var tmp =
			this->lookup_exception ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::StructDef_ptr RepositoryConnector::lookup_struct ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::StructDef_var ret_ = MDE::BaseIDL::StructDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a struct" , name);

	return ret_._retn();
}

MDE::BaseIDL::StructDef_ptr RepositoryConnector::lookup_struct ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_struct ( _root, name + 2 );
}

bool RepositoryConnector::test_struct ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::StructDef_var tmp =
			this->lookup_struct ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::UnionDef_ptr RepositoryConnector::lookup_union ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::UnionDef_var ret_ = MDE::BaseIDL::UnionDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not an union", name );

	return ret_._retn();
}

MDE::BaseIDL::UnionDef_ptr RepositoryConnector::lookup_union ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_union ( _root, name + 2 );
}

bool RepositoryConnector::test_union ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	try 
	{
		MDE::BaseIDL::UnionDef_var tmp =
			this->lookup_union ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::TypedefDef_ptr RepositoryConnector::lookup_typedef ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::TypedefDef_var ret_ = MDE::BaseIDL::TypedefDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a typedef", name );

	return ret_._retn();
}

MDE::BaseIDL::TypedefDef_ptr RepositoryConnector::lookup_typedef ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_typedef ( _root, name + 2 );
}

bool RepositoryConnector::test_typedef ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name" , name);

	try 
	{
		MDE::BaseIDL::TypedefDef_var tmp =
			this->lookup_typedef ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

MDE::BaseIDL::EnumDef_ptr RepositoryConnector::lookup_enum ( MDE::BaseIDL::Container_ptr base, const char* name ) {

	Reflective::RefObject_var ref_ = internal_lookup_scoped ( base, name );
	
	MDE::BaseIDL::EnumDef_var ret_ = MDE::BaseIDL::EnumDef::_narrow ( ref_ );

	if ( CORBA::is_nil ( ret_ ) )
		throw NotFoundInRep ( "Not a enum" , name);

	return ret_._retn();
}

MDE::BaseIDL::EnumDef_ptr RepositoryConnector::lookup_enum ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name", name );

	return this->lookup_enum ( _root, name + 2 );
}

bool RepositoryConnector::test_enum ( const char* name ) {

	if ( name[0] != ':' || name[1] != ':' )
		throw NotFoundInRep ( "Not a full scoped name" , name);

	try 
	{
		MDE::BaseIDL::EnumDef_var tmp =
			this->lookup_enum ( _root, name + 2 );

		return true;
	}
	catch(NotFoundInRep& )
	{
	}

	return false;
}

void RepositoryConnector::set_defined_in ( MDE::BaseIDL::Container_ptr container, MDE::BaseIDL::Contained_ptr contained )
{
	container->add_contents ( contained );
	contained->set_defined_in ( container );
}

//CCMRepositoryConnector includes ComponentIDL, CIF and Deployment packages

CCMRepositoryConnector::CCMRepositoryConnector ( /*::Reflective::RefPackageSet* package_set */)
:	RepositoryConnector ( /*package_set*/ ),
	_artifact_def_ref (),
	_segment_def_ref (),	
	_policy_ref(),	
	_component_impl_def_ref(),	
	_home_impl_def_ref(),
	_component_feature_ref(),
	_component_def_ref (),
	_provides_def_ref (),
	_home_def_ref (),
	_component_home_ref (),
	_factory_def_ref (),
	_finder_def_ref (),
	_event_port_def_ref (),
	_event_def_ref (),	
	_emits_def_ref (),
	_consumes_def_ref (),
	_uses_def_ref (),
	_publishes_def_ref (),
	_stream_port_def_ref (),
	_media_type_ref (),	
	_source_def_ref (),
	_sink_def_ref (),
	_si_sou_def_ref (),	
	_containerClass (),
	_implemented_by_ref (),
	_segment_artifact_ref (),
	_ass_policies_ref (),
	_home_implements_ref (),
	_component_implements_ref (),
	_manages_ref (),
	_event_type_ass_ref (),
	_mediato_type_ref (),
	_sinks_ref (),
	_sources_ref (),
	_si_sous_ref (),
	_assembly_ref (),
	_prop_owner_ref (),
	_property_ref () ,
	_deployment_unit_ref () ,
	_file_ref () ,
	_dependent_file_ref () ,
	_deployment_requirement_ref () ,
	_contained_file_ref () ,
	_rule_owner_ref () ,
	_rule_ref () ,
	_configuration_ref () ,
	_connection_ref () ,
	_connection_end_ref () ,
	_component_instantiation_ref () ,
	_register_component_instance_ref () ,
	_external_instance_ref () ,
	_finder_service_ref () ,
	_home_instantiation_ref () ,
	_installation_ref () ,
	_process_collocation_ref ()
{
}

/*CCMRepositoryConnector::CCMRepositoryConnector ( )
:	RepositoryConnector ( ),
	_artifact_def_ref (),
	_segment_def_ref (),	
	_policy_ref(),	
	_component_impl_def_ref(),	
	_home_impl_def_ref(),
	_component_feature_ref(),
	_component_def_ref (),
	_provides_def_ref (),
	_home_def_ref (),
	_component_home_ref (),
	_factory_def_ref (),
	_finder_def_ref (),
	_event_port_def_ref (),
	_event_def_ref (),	
	_emits_def_ref (),
	_consumes_def_ref (),
	_uses_def_ref (),
	_publishes_def_ref (),
	_stream_port_def_ref (),
	_media_type_ref (),	
	_source_def_ref (),
	_sink_def_ref (),
	_si_sou_def_ref (),	
	_containerClass (),
	_implemented_by_ref (),
	_segment_artifact_ref (),
	_ass_policies_ref (),
	_home_implements_ref (),
	_component_implements_ref (),
	_manages_ref (),
	_event_type_ass_ref (),
	_mediato_type_ref (),
	_sinks_ref (),
	_sources_ref (),
	_si_sous_ref (),
	_assembly_ref (),
	_prop_owner_ref (),
	_property_ref () ,
	_deployment_unit_ref () ,
	_file_ref () ,
	_dependent_file_ref () ,
	_deployment_requirement_ref () ,
	_contained_file_ref () ,
	_rule_owner_ref () ,
	_rule_ref () ,
	_configuration_ref () ,
	_connection_ref () ,
	_connection_end_ref () ,
	_component_instantiation_ref () ,
	_register_component_instance_ref () ,
	_external_instance_ref () ,
	_finder_service_ref () ,
	_home_instantiation_ref () ,
	_installation_ref () ,
	_process_collocation_ref ()
{
}
*/
CCMRepositoryConnector::~CCMRepositoryConnector ()
{
}

void CCMRepositoryConnector::connectRepository (  )
{
	RepositoryConnector::connectRepository ( );
	CORBA::Object_var obj_;
	obj_ = _mde_package->cif_ref ();
	_cif_ref = MDE::CIF::CIFPackage::_narrow ( obj_ );
	if( CORBA::is_nil(_cif_ref)) 
		throw NilObjectRef ( "Nil reference for CIF package: narrow problem" );

	obj_ = _mde_package->component_idl_ref ();
	_component_idl_ref = MDE::ComponentIDL::ComponentIDLPackage::_narrow ( obj_ );
	if( CORBA::is_nil(_component_idl_ref)) 
		throw NilObjectRef ( "Nil reference for ComponentIDLPackage: narrow problem" );

	obj_ = _mde_package->deployment_ref();
	_deployment_ref = MDE::Deployment::DeploymentPackage::_narrow ( obj_ );
	if( CORBA::is_nil(_deployment_ref)) 
		throw NilObjectRef ( "Nil reference for DeploymentPackage: narrow problem" );

// classes
	// Deployment package
	
	_assembly_ref = _deployment_ref->assembly_ref();
	_prop_owner_ref = _deployment_ref->prop_owner_ref ();
	_property_ref = _deployment_ref->property_ref() ;
	_deployment_unit_ref = _deployment_ref->deployment_unit_ref() ;
	_file_ref = _deployment_ref->file_ref() ;
	_dependent_file_ref = _deployment_ref->dependent_file_ref() ;
	_deployment_requirement_ref = _deployment_ref->deployment_requirement_ref() ;
	_contained_file_ref = _deployment_ref->contained_file_ref() ;
	_rule_owner_ref = _deployment_ref->rule_owner_ref() ;
	_rule_ref = _deployment_ref->rule_ref() ;
	_configuration_ref = _deployment_ref->configuration_ref() ;
	_connection_ref = _deployment_ref->connection_ref() ;
	_connection_end_ref = _deployment_ref->connection_end_ref() ;
	_component_instantiation_ref = _deployment_ref->component_instantiation_ref() ;
	_register_component_instance_ref = _deployment_ref->register_component_instance_ref() ;
	_external_instance_ref = _deployment_ref->external_instance_ref() ;
	_finder_service_ref = _deployment_ref->finder_service_ref() ;
	_home_instantiation_ref = _deployment_ref->home_instantiation_ref() ;
	_installation_ref = _deployment_ref->installation_ref() ;
	_process_collocation_ref = _deployment_ref->process_collocation_ref() ;

	// CIF Package
	_artifact_def_ref = _cif_ref->artifact_def_ref ();
	_segment_def_ref = _cif_ref->segment_def_ref ();	
	_policy_ref = _cif_ref->policy_ref();	
	_component_impl_def_ref = _cif_ref->component_impl_def_ref();	
	_home_impl_def_ref = _cif_ref->home_impl_def_ref();
	// Component Package
	_component_feature_ref = _component_idl_ref->component_feature_ref();
	_component_def_ref = _component_idl_ref->component_def_ref ();
	_provides_def_ref = _component_idl_ref->provides_def_ref ();
	_home_def_ref = _component_idl_ref->home_def_ref ();
	_component_home_ref = _component_idl_ref-> component_home_ref();
	_factory_def_ref = _component_idl_ref-> factory_def_ref();
	_finder_def_ref = _component_idl_ref->finder_def_ref ();
	_event_port_def_ref = _component_idl_ref->event_port_def_ref ();
	_event_def_ref = _component_idl_ref->event_def_ref ();	
	_emits_def_ref = _component_idl_ref->emits_def_ref ();
	_consumes_def_ref = _component_idl_ref-> consumes_def_ref();
	_uses_def_ref = _component_idl_ref->uses_def_ref ();
	_publishes_def_ref = _component_idl_ref->publishes_def_ref ();
	_stream_port_def_ref = _component_idl_ref->stream_port_def_ref ();
	_media_type_ref = _component_idl_ref->media_type_ref ();	
	_source_def_ref = _component_idl_ref->source_def_ref ();
	_sink_def_ref = _component_idl_ref->sink_def_ref ();
	_si_sou_def_ref = _component_idl_ref->si_sou_def_ref ();

	_containerClass = _base_idl_pkg_ref->container_ref ();
	
// associations
	// CIF Package
	_implemented_by_ref = _cif_ref->implemented_by_ref ();
	_segment_artifact_ref = _cif_ref->segment_artifact_ref ();
	_ass_policies_ref = _cif_ref->ass_policies_ref ();
	_home_implements_ref = _cif_ref->home_implements_ref ();
	_component_implements_ref = _cif_ref->component_implements_ref ();
	_manages_ref = _cif_ref->manages_ref ();
	
	// Component Package
	_event_type_ass_ref = _component_idl_ref->event_type_ass_ref ();
	_mediato_type_ref = _component_idl_ref->mediato_type_ref ();
	_sinks_ref = _component_idl_ref->sinks_ref ();
	_sources_ref = _component_idl_ref->sources_ref ();
	_si_sous_ref = _component_idl_ref->si_sous_ref ();
}

}