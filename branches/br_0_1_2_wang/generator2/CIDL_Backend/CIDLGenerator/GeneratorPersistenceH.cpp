#include "GeneratorPersistenceH.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {

GeneratorPersistenceH::GeneratorPersistenceH
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}

GeneratorPersistenceH::~GeneratorPersistenceH
()
{
}

void
GeneratorPersistenceH::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	doGenerate();
}

void
GeneratorPersistenceH::doAttribute(IR__::AttributeDef_ptr attribute)
{
	out << "\n//\n// " << attribute->id() << "\n//\n";
	std::string name = mapName(attribute);

	//
	// not read only
	//
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void " << name << "(";
		out << map_in_parameter_type(attribute->type_def()) << " param)\n";
		out << "	throw(CORBA::SystemException";
		handleException(attribute);
		out << ");\n";
	}

	out << map_return_type(attribute->type_def()) << " " << name << "()\n";
	out << "	throw(CORBA::SystemException";
	handleException(attribute);
	out << ");\n";
}

void
GeneratorPersistenceH::doOperation(IR__::OperationDef_ptr operation)
{
	out << "\n//\n// " << operation->id() << "\n//\n";
	std::string name = mapName(operation);

	out << "virtual " << map_return_type(operation->result_def()) << " " << name << "(";
	
	//
	// parameters
	//
	IR__::ParDescriptionSeq* pards = operation->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		if (pardescr.mode == IR__::PARAM_IN) {
			out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
		}
		if (pardescr.mode == IR__::PARAM_OUT) {
			out << map_out_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
		}
		if (pardescr.mode == IR__::PARAM_INOUT) {
			out << map_inout_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
		}

	};
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(operation);
	out << ");\n";
}

void 
GeneratorPersistenceH::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}

void 
GeneratorPersistenceH::doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storage_home)
{
	//
	// base storage homes
	//
	IR__::InterfaceDefSeq_var inh_intfs = abs_storage_home -> base_abstract_storage_homes();
	for(CORBA::ULong i = 0; i < inh_intfs->length(); i++) {
		if(! CORBA::is_nil((*inh_intfs)[i]))
		{
			IR__::InterfaceDef_ptr temp_if = (*inh_intfs)[i];
			IR__::AbstractStorageHomeDef_ptr abs_temp_if = dynamic_cast <IR__::AbstractStorageHomeDef_ptr> (temp_if);
			doAbstractStorageHome(abs_temp_if);
		}	
	};

	handleAttribute(abs_storage_home);
	handleOperation(abs_storage_home);
	handleFactory(abs_storage_home);
	handlePSSKey(abs_storage_home);
}

void 
GeneratorPersistenceH::doAbstractStorageType(IR__::AbstractStorageTypeDef_ptr abs_storage_type)
{
	//
	// base storage types
	//
	IR__::InterfaceDefSeq_var inh_intfs = abs_storage_type -> base_abstract_storage_types();
	for(CORBA::ULong i = 0; i < inh_intfs->length(); i++) {
		if(! CORBA::is_nil((*inh_intfs)[i]))
		{
			IR__::InterfaceDef_ptr temp_if = (*inh_intfs)[i];
			IR__::AbstractStorageTypeDef_ptr abs_temp_if = dynamic_cast <IR__::AbstractStorageTypeDef_ptr> (temp_if);
			doAbstractStorageType(abs_temp_if);
			handleAttribute(abs_storage_type);
		}	
	};
}

void 
GeneratorPersistenceH::doStorageHome(IR__::StorageHomeDef_ptr storage_home)
{
	// base storage home
	IR__::StorageHomeDef_var base = storage_home->base_storage_home();
	if(! CORBA::is_nil(base))
	{
		doStorageHome(base);
	}

	// supported interfaces
	IR__::InterfaceDefSeq_var supp_intfs = storage_home -> supported_interfaces();
	for(CORBA::ULong i = 0; i < supp_intfs->length(); i++) {
		handleAttribute((*supp_intfs)[i]);
		handleOperation((*supp_intfs)[i]);
	};

	handleAttribute(storage_home);
	handleOperation(storage_home);
	handleFactory(storage_home);
	handlePSSKey(storage_home);
}

void 
GeneratorPersistenceH::doStorageType(IR__::StorageTypeDef_ptr storage_type)
{
	//
	// base storage type
	//
	IR__::StorageTypeDef_ptr base = storage_type->base_storage_type();
	if(! CORBA::is_nil(base))
	{
		doStorageType(base);
	}

	handleAttribute(storage_type);
	handleSupportedInterface(storage_type);
}

void
GeneratorPersistenceH::doFactory(IR__::FactoryDef_ptr factory)
{
	out << "\n//\n// " << factory->id() << "\n//\n";

	out << "virtual ::Components::EnterpriseComponent_ptr " << mapName(factory) << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = factory->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(std::string(pardescr.name));
	};
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(factory);
	out << ");\n";
}

void
GeneratorPersistenceH::doPSSKey(IR__::PSSKeyDef_ptr psskey)
{
	out << "\n//\n// " << psskey->id() << "\n//\n";

	out << "virtual ::Components::EnterpriseComponent_ptr " << mapName(psskey) << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = psskey->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	};
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(psskey);
	out << ");\n";
}

} // namespace
