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
#include "GeneratorPersistenceH.h"


namespace QEDO_CIDL_Generator {

GeneratorPersistenceH::GeneratorPersistenceH
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository), 
  bAbstract_(true), 
  bASHKey_(true),
  strFilename_(""),
  strActBasename_("")
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
	
	strFilename_ = file_prefix_ + "_PSS.h";
	
	out.open(strFilename_.c_str());
	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#ifndef _" << file_prefix_ << "_PSS_H_\n";
	out << "#define _" << file_prefix_ << "_PSS_H_\n\n\n";
	out << "// BEGIN USER INSERT SECTION file_pre\n";
	out << "// END USER INSERT SECTION file_pre\n\n";
	out << "#include <CORBA.h>\n";
	out << "#include \"CORBADepends.h\"\n";
	out << "#include \"GlobalHelpers.h\"\n";
	out << "#include \"StorageObject.h\"\n";
	out << "#include \"StorageHomeBase.h\"\n";
	out << "#include \"Catalog.h\"\n";
	out << "#include \"" << file_prefix_ << "_EQUIVALENT.h\"\n";
	out << "#include \"" << file_prefix_ << "_FD.h\"\n\n";
	out << "using namespace Qedo;\n\n";
	out << "// BEGIN USER INSERT SECTION file_post\n";
	out << "// END USER INSERT SECTION file_post\n";

	doGenerate();

	out << "\n#endif\n";
	out.close();
}

void
GeneratorPersistenceH::check_for_generation(IR__::Contained_ptr item)
{
	// check if item is already known
	if (item_well_known(item))
		return;

	// check if item is already in the list or currently processed
	if ((this->sRecursion_.find(item->id())) != sRecursion_.end() || this->already_included (item))
		return;
	else
		sRecursion_.insert(item->id());

	CORBA::ULong i;
	CORBA::ULong ulLen;

	switch (item->def_kind())
	{
	case CORBA__::dk_Module : 
	{
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(item);

		// modules
		IR__::ContainedSeq_var contained_seq = a_module->contents(CORBA__::dk_Module, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
			check_for_generation((*contained_seq)[i]);

		// abstract storagehomes
		contained_seq = a_module->contents(CORBA__::dk_AbstractStorageHome, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
			check_for_generation((*contained_seq)[i]);

		// storagehomes
		contained_seq = a_module->contents(CORBA__::dk_StorageHome, true);
		ulLen = contained_seq->length();
		for(i=0; i<ulLen; i++)
			check_for_generation((*contained_seq)[i]);

		break; 
	}
	case CORBA__::dk_AbstractStorageType :
	{
		IR__::AbstractStorageTypeDef_var abs_storagetype = IR__::AbstractStorageTypeDef::_narrow(item);
		// insert this interface in generation list
		this->insert_to_generate(item);

		break;
	}
	case CORBA__::dk_StorageType :
	{
		IR__::StorageTypeDef_var storagetype = IR__::StorageTypeDef::_narrow(item);
		// insert this interface in generation list
		this->insert_to_generate(item);

		break;
	}
    case CORBA__::dk_AbstractStorageHome :
	{
		IR__::AbstractStorageHomeDef_var abs_storagehome = IR__::AbstractStorageHomeDef::_narrow(item);
		// insert this interface in generation list
		this->insert_to_generate(item);

		// managed abstract storage type
		IR__::AbstractStorageTypeDef_var abs_storagetype = abs_storagehome->managed_abstract_storagetype();
		this->check_for_generation(abs_storagetype);

		break;
	}
	case CORBA__::dk_StorageHome : 
	{
		IR__::StorageHomeDef_var storagehome = IR__::StorageHomeDef::_narrow(item);
		// insert this interface in generation list
		this->insert_to_generate(item);

		// managed storage type
		IR__::StorageTypeDef_var storagetype = storagehome->managed_storagetype();
		this->check_for_generation(storagetype);

		break;
	}
	default:
		break;
	};

	sRecursion_.erase(item->id());
};

void
GeneratorPersistenceH::genDuplAndDown(std::string strClassName)
{
	//generate _duplicate and _downcast operation
	out << "\nstatic " << strClassName << "* _duplicate(const " << strClassName << "* obj);\n";
    out << "static " << strClassName << "* _downcast(const " << strClassName << "* obj);\n";
}

void
GeneratorPersistenceH::genMemberVariable(IR__::StorageTypeDef_ptr storagetype)
{
	IR__::AttributeDefSeq state_members;
	storagetype->get_state_members(state_members, CORBA__::dk_Variable);
	CORBA::ULong ulLen = state_members.length();
	
	out << "protected:\n\n";
	out.indent();

	for(CORBA::ULong i=0; i<ulLen; i++)
	{
		IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(state_members[i]);
		std::string attribute_name = mapName(attribute);
		out << map_attribute_type(attribute->type_def()) << " " << attribute_name << "_;\n";
	}

	out.unindent();
}

void
GeneratorPersistenceH::genAttributeWithNomalType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind)
{
	std::string attribute_name = mapName(attribute);
	IR__::IDLType_var attr_type = attribute->type_def();

	switch ( attr_type->type()->kind() )
	{
		case CORBA::tk_string:
		case CORBA::tk_wstring:
			if(bAbstract_) out << "virtual ";
			out << map_psdl_return_type(attr_type, false) << " " << attribute_name << "(";
			out << map_psdl_parameter_type(attr_type, false) << " param)";
			bAbstract_ ? out << " = 0;\n" : out << ";\n";
	}

	if(bAbstract_) out << "virtual ";
	out << "void " << attribute_name << "(";
	out << map_psdl_parameter_type(attr_type, true) << " param)";
	bAbstract_ ? out << " = 0;\n" : out << ";\n";

	// the fourth operation only for string and wstring
	if(attr_type->type()->kind()==CORBA::tk_string)
	{
		if(bAbstract_) out << "virtual ";
		out << "void " << attribute_name << "(CORBA::String_var& param)";
		bAbstract_ ? out << " = 0;\n" : out << ";\n";
	}
	else if(attr_type->type()->kind()==CORBA::tk_wstring)
	{
		if(bAbstract_) out << "virtual ";
		out << "void " << attribute_name << "(CORBA::WString_var& param)";
		bAbstract_ ? out << " = 0;\n" : out << ";\n";
	}
}

void
GeneratorPersistenceH::genAttributeWithOtherType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind)
{
	std::string attribute_name = mapName(attribute);
	IR__::IDLType_var attr_type = attribute->type_def();

	switch ( attr_type->type()->kind() )
	{
		case CORBA::tk_string:
		case CORBA::tk_wstring:
			if(bAbstract_) out << "virtual ";
			out << map_psdl_return_type(attr_type, false) << " " << attribute_name << "(";
			out << map_psdl_parameter_type(attr_type, false) << " param)";
			bAbstract_ ? out << " = 0;\n" : out << ";\n";
	}

	if(bAbstract_) out << "virtual ";
	out << map_psdl_return_type(attr_type, false) << " " << attribute_name << "(";
	out << "CosPersistentState::ForUpdate fu)";
	bAbstract_ ? out << " = 0;\n" : out << ";\n";

	if(bAbstract_) out << "virtual ";
	out << "void " << attribute_name << "(";
	out << map_psdl_parameter_type(attr_type, true) << " param)";
	bAbstract_ ? out << " = 0;\n" : out << ";\n";
}

void
GeneratorPersistenceH::doAttribute(IR__::AttributeDef_ptr attribute)
{
	out << "\n//\n// " << attribute->id() << "\n//\n";
	std::string attribute_name = mapName(attribute);
	IR__::IDLType_var attr_type = attribute->type_def();
		
	// read only
	if(bAbstract_) out << "virtual ";
	out << map_psdl_return_type(attr_type, true) << " " << attribute_name << "() const";
	bAbstract_ ? out << " = 0;\n" : out << ";\n";

	// not read only
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		CORBA::TCKind att_type_kind = attr_type->type()->kind();
		switch ( att_type_kind )
		{
			case CORBA::tk_short:
			case CORBA::tk_long:
			case CORBA::tk_longlong:
			case CORBA::tk_ushort:
			case CORBA::tk_ulong:
			case CORBA::tk_ulonglong:
			case CORBA::tk_float:
			case CORBA::tk_double:
			case CORBA::tk_longdouble:
			case CORBA::tk_boolean:
			case CORBA::tk_char:
			case CORBA::tk_wchar:
			case CORBA::tk_octet:
			case CORBA::tk_string:
			case CORBA::tk_wstring:
				genAttributeWithNomalType(attribute, att_type_kind);
				break;
			default:
				genAttributeWithOtherType(attribute, att_type_kind);
		}
	}
}

void
GeneratorPersistenceH::genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type)
{
	out << "\n//\n// " << operation->id() << "\n//\n";
	if(bAbstract_) out << "virtual ";
	out << map_psdl_return_type(ret_type, false) << " " << mapName(operation) << "(";

	// parameters
	IR__::ParDescriptionSeq_var pards = operation->params();
	for( CORBA::ULong i=0; i<pards->length(); i++)
	{
		IR__::ParameterDescription pardescr = (*pards)[i];
		if (pardescr.mode == IR__::PARAM_IN) {
			out << map_in_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_OUT) {
			out << map_out_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_INOUT) {
			out << map_inout_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if((i+1)!=pards->length()) { out << ", "; }
	};

	bAbstract_ ? out << ") = 0;\n" : out << ");\n";
}

void
GeneratorPersistenceH::doOperation(IR__::OperationDef_ptr operation)
{
	genOperation(operation, operation->result_def());
}

void
GeneratorPersistenceH::genFactory(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type)
{
	out << "\n//\n// " << operation->id() << "\n//\n";

	int iLength = 0;
	std::string strDummy = "";
	stringstream strDisplay;

	if(bAbstract_) 
		strDisplay << "virtual ";
	strDisplay << map_psdl_return_type(ret_type, false) << " " << mapName(operation) << "(";
	out << strDisplay.str();

	iLength = strDisplay.str().length();
	strDummy.append(iLength, ' ');
	
	out << "Pid* pid,\n";
	out << strDummy.c_str();
	out << "ShortPid* shortPid,\n";

	// parameters
	IR__::ParDescriptionSeq_var pards = operation->params();
	for( CORBA::ULong i=0; i<pards->length(); i++)
	{
		out << strDummy.c_str();
		IR__::ParameterDescription pardescr = (*pards)[i];
		if (pardescr.mode == IR__::PARAM_IN) {
			out << map_in_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_OUT) {
			out << map_out_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_INOUT) {
			out << map_inout_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if((i+1)!=pards->length()) { out << ",\n"; }
	};

	bAbstract_ ? out << ") = 0;\n" : out << ");\n";
}

void
GeneratorPersistenceH::doFactory(IR__::FactoryDef_ptr factory, IR__::InterfaceDef_ptr inf_def)
{
	if( (bAbstract_==TRUE) || (bAbstract_==FALSE && bASHKey_==TRUE) )
	{
		IR__::AbstractStorageTypeDef_var abs_storagetype;
		IR__::AbstractStorageHomeDef_var abs_storagehome = IR__::AbstractStorageHomeDef::_narrow(inf_def);
		if(!CORBA::is_nil(abs_storagehome))
			abs_storagetype = abs_storagehome->managed_abstract_storagetype();
		if(!CORBA::is_nil(abs_storagetype))
			genFactory(factory, abs_storagetype);
	}
	else
	{
		IR__::StorageTypeDef_var storagetype;
		IR__::StorageHomeDef_var storagehome = IR__::StorageHomeDef::_narrow(inf_def);
		if(!CORBA::is_nil(storagehome))
			storagetype = storagehome->managed_storagetype();
		if(!CORBA::is_nil(storagetype))
			genFactory(factory, storagetype);
	}
}

void
GeneratorPersistenceH::genKey(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type, bool bRef)
{
	if(!bRef) out << "\n//\n// " << operation->id() << "\n//\n";
	if(bAbstract_) out << "virtual ";
	char* szReturnType = map_psdl_return_type(ret_type, false);

	//since the definition of a abstract stoage type is not yet supported, 
	//we have to replcace the "*" with "Ref" for operation find_by_ref_... 
	if(bRef)
	{
		char* pdest = strstr( szReturnType, "*" );
		if( pdest != NULL )
		{
			memset(pdest, '\0', 1);
			strcat(szReturnType, "Ref");
		}
	}
	
	out << szReturnType;
	bRef ? out << " find_ref_by_" : out << " find_by_";
	out << mapName(operation) << "(";

	// parameters
	IR__::ParDescriptionSeq* pards = operation->params();
	for( CORBA::ULong i=0; i<pards->length(); i++)
	{
		IR__::ParameterDescription pardescr = (*pards)[i];
		if (pardescr.mode == IR__::PARAM_IN) {
			out << map_in_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_OUT) {
			out << map_out_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_INOUT) {
			out << map_inout_parameter_type (pardescr.type_def) << " " << std::string(pardescr.name);
		};
		if((i+1)!=pards->length()) { out << ", "; }
	};

	out << ")";
	
	if(!bRef)
	{
		out << "\n";
		out.indent();
		out << "throw(CosPersistentState::NotFound";
		handleException(operation);
		out << ")";
		out.unindent();
	}
	
	bAbstract_ ? out << " = 0;\n" : out << ";\n";
}

void
GeneratorPersistenceH::doKey(IR__::KeyDef_ptr key, IR__::InterfaceDef_ptr inf_def)
{
	if( (bAbstract_==TRUE) || (bAbstract_==FALSE && bASHKey_==TRUE) )
	{
		IR__::AbstractStorageTypeDef_var abs_storagetype;
		IR__::AbstractStorageHomeDef_var abs_storagehome = IR__::AbstractStorageHomeDef::_narrow(inf_def);
		if(!CORBA::is_nil(abs_storagehome))
			abs_storagetype = abs_storagehome->managed_abstract_storagetype();
		if(!CORBA::is_nil(abs_storagetype))
		{
			genKey(key, abs_storagetype, false);
			genKey(key, abs_storagetype, true);
		}
	}
	else
	{
		IR__::StorageTypeDef_var storagetype;
		IR__::StorageHomeDef_var storagehome = IR__::StorageHomeDef::_narrow(inf_def);
		if(!CORBA::is_nil(storagehome))
			storagetype = storagehome->managed_storagetype();
		if(!CORBA::is_nil(storagetype))
		{
			genKey(key, storagetype, false);
			genKey(key, storagetype, true);
		}
	}
}

void 
GeneratorPersistenceH::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}

void 
GeneratorPersistenceH::genAbstractStorageTypeBody(IR__::AbstractStorageTypeDef_ptr abs_storagetype/*, bool bRef*/)
{
	std::string strClassName = std::string(abs_storagetype->name());

	out << "class " << strClassName << "\n";
	//bRef ? out << "Ref\n" : out << "\n";
	out.indent();
	
	IR__::InterfaceDefSeq_var abs_storagetype_seq = abs_storagetype->base_abstract_storagetypes();
	if(abs_storagetype_seq->length()==0)
	{
		out << ": public virtual CosPersistentState::StorageObject\n";
		//bRef ? out << "Ref\n" : out << "\n";
	}
	else
	{
		for(CORBA::ULong i=0; i<abs_storagetype_seq->length(); i++) 
		{
			i==0 ? out << ": " : out << ", ";
			out << "public virtual " << ((*abs_storagetype_seq)[i])->name() << "\n";
			//bRef ? out << "Ref\n" : out << "\n";
		}
	}

	out.unindent();
	out << "{\n\npublic:\n\n";
	out.indent();
    //out << strClassName;
	//bRef ? out << "Ref();\n" : out << "();\n";
	//out << "~" << strClassName;
	//bRef ? out << "Ref();\n" : out << "();\n";

	bAbstract_ = true;
	handleAttribute(abs_storagetype);
	handleOperation(abs_storagetype);
	
	//generate _duplicate and _downcast operation
	//genDuplAndDown(strClassName);

	out.unindent();
	out << "};\n\n";

	out << "#ifdef ORBACUS_ORB\n";
	out << "typedef OB::ObjVar< " << strClassName;
	//if(bRef) out << "Ref";
	out	<< " > " << strClassName;
	//if(bRef) out << "Ref"; 
	out << "_var;\n";
	out << "typedef OB::ObjVar< " << strClassName;
	//if(bRef) out << "Ref";
	out << " > " << strClassName;
	//if(bRef) out << "Ref";
	out << "_out;\n";
	out << "#endif\n";
	out << "#ifdef MICO_ORB\n";
	out << "typedef ObjVar< " << strClassName;
	//if(bRef) out << "Ref";
	out	<< " > " << strClassName;
	//if(bRef) out << "Ref"; 
	out << "_var;\n";
	out << "typedef ObjVar< " << strClassName;
	//if(bRef) out << "Ref";
	out << " > " << strClassName;
	//if(bRef) out << "Ref";
	out << "_out;\n";
	out << "#endif\n\n\n";
}

void
GeneratorPersistenceH::genBaseRefBody(std::string strTypeName)
{
	out << "public:\n\n";
	out.indent();
	out << "typedef " << strTypeName << " _target_type;\n\n";
	out << strTypeName << "Ref() throw();\n";
	out << strTypeName << "Ref(" << strTypeName << "* obj) throw();\n";
	out << strTypeName << "Ref(const " << strTypeName << "Ref& ref) throw();\n";
	out << "virtual ~" << strTypeName << "Ref() throw();\n\n";
	out << strTypeName << "Ref& operator=(const " << strTypeName << "Ref& ref) throw();\n";
	out << strTypeName << "Ref& operator=(" << strTypeName << "* obj) throw();\n";
	out << strTypeName << "* deref() const throw(CORBA::SystemException);\n";
	out << strTypeName << "* operator->() const throw(CORBA::SystemException);\n\n";
	out << "void release() throw();\n";
	out << "void destroy_object() throw(CORBA::SystemException);\n\n";
	out << "Pid* get_pid() const throw(CORBA::SystemException);\n";
	out << "ShortPid* get_short_pid() const throw(CORBA::SystemException);\n\n";
	out << "CORBA::Boolean is_null() const throw();\n";
	out << strActBasename_ << "* get_storage_home() const throw(CORBA::SystemException);\n\n";
	out << "static " << strTypeName << "Ref _duplicate(const " << strTypeName << "Ref ref);\n";
	out << "static " << strTypeName << "Ref _downcast(const " << strTypeName << "Ref ref);\n\n";
	out.unindent();
}

void
GeneratorPersistenceH::genAbstractRefBody(IR__::AbstractStorageTypeDef_ptr abs_storagetype)
{
	std::string strClassName = std::string(abs_storagetype->name());
	out << "class " << strClassName << "Ref\n";
	out << "{\n";
	genBaseRefBody(strClassName);
	
	// generate conversion operators
	out.indent();
	out << "//conversion operators\n";
	out << "//... to do ...\n\n";
	out.unindent();
	out << "private:\n\n";
	out.indent();
	out << strClassName << "* pObj_;\n";
	out.unindent();
	out << "};\n";
}

void 
GeneratorPersistenceH::doAbstractStorageType(IR__::AbstractStorageTypeDef_ptr abs_storagetype)
{
	out << "\n\n";
	open_module(out, abs_storagetype, "");
	out << "\n\n";

	// generate normal class
	genAbstractStorageTypeBody(abs_storagetype/*, false*/);
	// generate ref class
	// Don't known how to build a Ref-class :-(
	//genAbstractStorageTypeBody(abs_storagetype, true);
	genAbstractRefBody(abs_storagetype); // Hopefully it's right!

	close_module(out, abs_storagetype);
}

void
GeneratorPersistenceH::genAbstractObjsForConcreteType(IR__::AbstractStorageTypeDef_ptr abs_storagetype)
{
	IR__::InterfaceDefSeq_var abs_storagetype_seq = abs_storagetype->base_abstract_storagetypes();
	for(CORBA::ULong i=0; i<abs_storagetype_seq->length(); i++) 
	{
		bAbstract_ = false;
		handleAttribute((*abs_storagetype_seq)[i]);
		handleOperation((*abs_storagetype_seq)[i]);
	}

	bAbstract_ = false;
	handleAttribute(abs_storagetype);
	handleOperation(abs_storagetype);
}

void
GeneratorPersistenceH::genStorageTypeBody(IR__::StorageTypeDef_ptr storagetype/*, bool bRef*/)
{
	std::string strClassName = std::string(storagetype->name());

	out << "class " << strClassName << "\n";
	//bRef ? out << "Ref\n" : out << "\n";
	out.indent();
	
	IR__::StorageTypeDef_var base_storagetype = storagetype->base_storagetype();
	if(base_storagetype)
	{
		out << ": public virtual " << base_storagetype->name() << "\n";
		//bRef ? out << "Ref\n" : out << "\n";
	}
	else
	{
		out << ": public virtual StorageObjectImpl\n";
		//if(bRef) out << "Ref";
		//out << "Impl\n";
	}

	IR__::InterfaceDefSeq_var supported_infs = storagetype->supported_interfaces();
	for(CORBA::ULong i=0; i<supported_infs->length(); i++)
	{
		out << ", public virtual " << ((*supported_infs)[i])->name() << "\n";
		//bRef ? out << "Ref\n" : out << "\n";
	};

	out << "// BEGIN USER INSERT SECTION INHERITANCE_" << strClassName << "\n";
	//bRef ? out << "Ref\n" : out << "\n";
	out << "// END USER INSERT SECTION INHERITANCE_" << strClassName << "\n";
	//bRef ? out << "Ref\n" : out << "\n";
	out.unindent();
	out << "{\n\npublic:\n\n";
	out.indent();
    out << strClassName << "();\n";
	//bRef ? out << "Ref();\n" : out << "();\n";
	out << "~" << strClassName << "();\n";
	//bRef ? out << "Ref();\n" : out << "();\n";

	for(CORBA::ULong i=0; i<supported_infs->length(); i++) 
	{
		IR__::AbstractStorageTypeDef_var abs_storagetype_inh;
		abs_storagetype_inh = IR__::AbstractStorageTypeDef::_narrow((*supported_infs)[i]);
		genAbstractObjsForConcreteType(abs_storagetype_inh);
	};

	bAbstract_ = false;
	handleAttribute(storagetype);
	handleOperation(storagetype);

	out << "\nvoid setValue(std::map<std::string, CORBA::Any> valueMap);\n";
	
	//generate _duplicate and _downcast operation
	//genDuplAndDown(strClassName);
	out.unindent();

	genMemberVariable(storagetype);
	
	out << "\n// BEGIN USER INSERT SECTION " << strClassName << "\n";
	//bRef ? out << "Ref\n" : out << "\n";
	out << "// END USER INSERT SECTION " << strClassName << "\n\n";
	//bRef ? out << "Ref\n" : out << "\n\n";
	out << "};\n\n\n";
}

void
GeneratorPersistenceH::genRefBody(IR__::StorageTypeDef_ptr storagetype)
{
	std::string strClassName = std::string(storagetype->name());
	out << "class " << strClassName << "Ref\n";
	out << "{\n";
	genBaseRefBody(strClassName);
	
	// generate conversion operators
	out.indent();
	out << "//conversion operators\n";
	out << "//... to do ...\n\n";
	out.unindent();
	out << "private:\n\n";
	out.indent();
	out << strClassName << "* pObj_;\n";
	out.unindent();
	out << "};\n";
}

void 
GeneratorPersistenceH::doStorageType(IR__::StorageTypeDef_ptr storagetype)
{
	// achtung: wenn kein modul, sollte vielleicht PSS_ der prefix f�r alle pss sein?
	out << "\n\n";	
	open_module(out, storagetype, "");
	out << "\n\n";

	// generate normal class
	genStorageTypeBody(storagetype/*, false*/);
	// generate ref class
	// Don't known how to build a Ref-class :-(
	//genStorageTypeBody(storagetype, true);
	genRefBody(storagetype); // Hopefully it's right!

	close_module(out, storagetype);
}

void 
GeneratorPersistenceH::doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome)
{
	IR__::AbstractStorageTypeDef_var abs_storagetype = abs_storagehome->managed_abstract_storagetype();

	// achtung: wenn kein modul, sollte vielleicht PSS_ der prefix f�r alle pss sein?
	out << "\n\n";
	open_module(out, abs_storagetype, "");
	out << "\n\n";

	std::string strClassName = std::string(abs_storagehome->name());
	strActBasename_ = strClassName;

	out << "class " << strClassName << "\n";
	out.indent();
	
	IR__::InterfaceDefSeq_var abs_storagehome_seq = abs_storagehome->base_abstract_storagehomes();
	if(abs_storagehome_seq->length()==0)
		out << ": public virtual CosPersistentState::StorageHomeBase\n";
	else
		for(CORBA::ULong i=0; i<abs_storagehome_seq->length(); i++)
		{
			i==0 ? out << ": " : out << ", ";
			out << "public virtual " << ((*abs_storagehome_seq)[i])->name() << "\n";
		};

	out.unindent();
	out << "{\n\npublic:\n\n";
	out.indent();
    //out << strClassName << "();\n";
	//out << "~" << strClassName << "();\n";

	bAbstract_ = true;
	handleAttribute(abs_storagehome);
	handleOperation(abs_storagehome);
	handleFactory(abs_storagehome);
	handleKey(abs_storagehome);
	
	//generate _duplicate and _downcast operation
	//genDuplAndDown(strClassName);

	out.unindent();
	out << "};\n\n";
	out << "#ifdef ORBACUS_ORB\n";
	out << "typedef OB::ObjVar< " << strClassName << " > " << strClassName << "_var;\n";
	out << "typedef OB::ObjVar< " << strClassName << " > " << strClassName << "_out;\n";
	out << "#endif\n";
    out << "#ifdef MICO_ORB\n";
	out << "typedef ObjVar< " << strClassName << " > " << strClassName << "_var;\n";
	out << "typedef ObjVar< " << strClassName << " > " << strClassName << "_out;\n";
	out << "#endif\n";
	out << "\n\n";

	close_module(out, abs_storagetype);
}

void
GeneratorPersistenceH::genAbstractObjsForConcreteHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome)
{
	IR__::InterfaceDefSeq_var abs_storagehome_seq = abs_storagehome->base_abstract_storagehomes();
	for(CORBA::ULong i=0; i<abs_storagehome_seq->length(); i++) 
	{
		IR__::AbstractStorageHomeDef_var abs_storagehome_inh;
		abs_storagehome_inh = IR__::AbstractStorageHomeDef::_narrow((*abs_storagehome_seq)[i]);
		bAbstract_ = false;
		bASHKey_ = true;
		handleAttribute(abs_storagehome_inh);
		handleOperation(abs_storagehome_inh);
		handleFactory(abs_storagehome_inh);
		handleKey(abs_storagehome_inh);
	}

	bAbstract_ = false;
	bASHKey_ = true;
	handleAttribute(abs_storagehome);
	handleOperation(abs_storagehome);
	handleFactory(abs_storagehome);
	handleKey(abs_storagehome);
}

void
GeneratorPersistenceH::genCreateOperation(IR__::StorageHomeDef_ptr storagehome, bool bRef)
{
	int iLength = 0;
	std::string strDummy = "";
	char* szDisplay = map_psdl_return_type(storagehome->managed_storagetype(), false);
	bRef ? iLength = strlen(szDisplay) + 11 : iLength = strlen(szDisplay) + 9;

	if(bRef)
	{
		char* pdest = strstr( szDisplay, "*" );
		if( pdest != NULL )
		{
			memset(pdest, '\0', 1);
			strcat(szDisplay, "Ref");
		}
	}
	
	out << szDisplay << " _create(";
	out << "Pid* pid,\n";
	strDummy.append(iLength, ' ');
	out << strDummy.c_str();
	out << "ShortPid* shortPid,\n";
	
	IR__::AttributeDefSeq state_members;
	storagehome->managed_storagetype()->get_state_members(state_members, CORBA__::dk_Create);
	CORBA::ULong ulLen = state_members.length();
	for(CORBA::ULong i=0; i<ulLen; i++)
	{
		IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(state_members[i]);
		out << strDummy.c_str() << map_in_parameter_type(attribute->type_def()) << " " << mapName(attribute);
		if( (i+1)!=ulLen )
			out << ",\n";
	}
	
	if(bRef)
		out << ",\n" << strDummy.c_str() << "CosPersistentState::YieldRef yr";

	out << ");\n\n";
}

void 
GeneratorPersistenceH::doStorageHome(IR__::StorageHomeDef_ptr storagehome)
{
	IR__::StorageTypeDef_var storagetype = storagehome->managed_storagetype();

	// achtung: wenn kein modul, sollte vielleicht PSS_ der prefix f�r alle pss sein?
	out << "\n\n";
	open_module(out, storagetype, "");
	out << "\n\n";

	std::string strClassName = std::string(storagehome->name());
	strActBasename_ = strClassName;

	out << "class " << strClassName << "\n";
	out.indent();
	
	IR__::StorageHomeDef_var base_storagehome = storagehome->base_storagehome();
	if(base_storagehome)
		out << ": public virtual " << base_storagehome->name() << "\n";
	else
		out << ": public virtual StorageHomeBaseImpl\n";

	IR__::InterfaceDefSeq_var supported_infs = storagehome->supported_interfaces();
	for(CORBA::ULong i=0; i<supported_infs->length(); i++) 
		out << ", public virtual " << ((*supported_infs)[i])->name() << "\n";

	out << "// BEGIN USER INSERT SECTION INHERITANCE_" << strClassName << "\n";
	out << "// END USER INSERT SECTION INHERITANCE_" << strClassName << "\n";
	out.unindent();
	out << "{\n\npublic:\n\n";
	out.indent();
    out << strClassName << "();\n";
	out << "~" << strClassName << "();\n\n";

	genCreateOperation(storagehome, false);
	genCreateOperation(storagehome, true);

	for(CORBA::ULong i=0; i<supported_infs->length(); i++) 
	{
		IR__::AbstractStorageHomeDef_var abs_storagehome_inh;
		abs_storagehome_inh = IR__::AbstractStorageHomeDef::_narrow((*supported_infs)[i]);
		genAbstractObjsForConcreteHome(abs_storagehome_inh);
	};

	bAbstract_ = false;
	bASHKey_ = false;
	handleAttribute(storagehome);
	handleOperation(storagehome);
	handleFactory(storagehome);
	handleKey(storagehome);

	//generate _duplicate and _downcast operation
	//genDuplAndDown(strClassName);

	out.unindent();
	/*out << "\n\nprivate:\n\n";
	out.indent();
	out << "std::string strCreateTable_;\n";
	out.unindent();*/

	out << "\n// BEGIN USER INSERT SECTION " << strClassName << "\n";
	out << "// END USER INSERT SECTION " << strClassName << "\n\n";
	out << "};\n\n\n";

	close_module(out, storagetype);
}

} // namespace
