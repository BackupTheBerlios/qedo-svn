#include "GeneratorPersistenceC.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {

GeneratorPersistenceC::GeneratorPersistenceC
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}

GeneratorPersistenceC::~GeneratorPersistenceC
()
{
}

void
GeneratorPersistenceC::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }
	
	filename_ = file_prefix_ + "_PSS.cpp";
	
	out.open(filename_.c_str());
	out << "#include \"" << file_prefix_ << "_PSS.h\"";

	doGenerate();

	out.close();
}

void
GeneratorPersistenceC::doAttribute(IR__::AttributeDef_ptr attribute)
{
	std::string attribute_name = mapName(attribute);

	//
	// not read only
	//
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void\n";
		out << class_name_ << "::" << attribute_name << "(";
		out << map_in_parameter_type(attribute->type_def()) << " param)\n{\n";
		out.insertUserSection(class_name_ + "::_" + attribute->name(), 0);
		out << "}\n\n\n";
	}

	out << map_return_type(attribute->type_def()) << "\n";
	out << class_name_ << "::" << attribute_name << "()\n{\n";
	out.insertUserSection(class_name_ + "::" + attribute->name(), 0);
	out << "}\n\n\n";
}

void
GeneratorPersistenceC::doOperation(IR__::OperationDef_ptr operation)
{
	std::string operation_name = mapName(operation);

	out << map_return_type(operation->result_def()) << "\n";
	out << class_name_ << "::" << operation_name << "(";

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
	}
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(operation);
	out << ")\n{\n";
	out.insertUserSection(class_name_ + "::" + operation->name(), 0);
	out << "}\n\n\n";
}

void 
GeneratorPersistenceC::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}

void 
GeneratorPersistenceC::doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storage_home)
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
GeneratorPersistenceC::doAbstractStorageType(IR__::AbstractStorageTypeDef_ptr abs_storage_type)
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
GeneratorPersistenceC::doStorageHome(IR__::StorageHomeDef_ptr storage_home)
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
GeneratorPersistenceC::doStorageType(IR__::StorageTypeDef_ptr storage_type)
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
GeneratorPersistenceC::doFactory(IR__::FactoryDef_ptr factory)
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
GeneratorPersistenceC::doPSSKey(IR__::PSSKeyDef_ptr psskey)
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

} //
