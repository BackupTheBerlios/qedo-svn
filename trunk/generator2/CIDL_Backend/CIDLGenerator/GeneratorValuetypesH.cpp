#include "GeneratorValuetypesH.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorValuetypesH::GeneratorValuetypesH
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}


GeneratorValuetypesH::~GeneratorValuetypesH
()
{
}


void
GeneratorValuetypesH::check_for_generation(IR__::Contained_ptr item)
{
	//
	// check if item is already known
	//
	if (item_well_known(item))
	{
		return;
	}

	//
	// check if item is already in the list or currently processed
	//
	if ((this->m_recursion_set.find(item->id())) != m_recursion_set.end() || this->already_included (item)) {
		return;
	} 
	else {
		m_recursion_set.insert(item->id());
	}

	CORBA::ULong len;
	CORBA::ULong i;
	IR__::ContainedSeq_var composition_seq = repository_->contents(CORBA__::dk_Composition, true);
	switch (item->def_kind()) {
	case CORBA__::dk_Module : {
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(item);

		// modules
		IR__::ContainedSeq_var contained_seq = a_module->contents(CORBA__::dk_Module, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// compositions
		len = composition_seq->length();
		CIDL::CompositionDef_var a_composition;
		for(i = 0; i < len; i++)
		{
			a_composition = CIDL::CompositionDef::_narrow((*composition_seq)[i]);
			std::string id = a_composition->id();
			std::string::size_type pos = id.find_last_of("/");
			if(pos != std::string::npos) 
			{
				id.replace(pos, std::string::npos, ":1.0");
				if(!id.compare(a_module->id())) 
				{
					check_for_generation(a_composition);
				}
			}
		}

		break; }
	case CORBA__::dk_Composition : {
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(item);
		IR__::ConsumesDefSeq_var consumes_seq;
		IR__::EventDef_ptr event;
		consumes_seq = a_composition->ccm_component()->consumes_events();
		len = consumes_seq->length();
		for(i = 0; i < len; i++)
		{
			// insert each consumed event (check whether already inserted)
			event = ((*consumes_seq)[i])->event();
			if (id_list_.find(event->id()) == id_list_.end())
			{
				id_list_.insert(event->id());
				this->insert_to_generate(event);
			}
		}

		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
};


void
GeneratorValuetypesH::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	//
	// parse for user sections and open file
	//
	out.initUserSections("valuetypes.h");
	out.open("valuetypes.h");
	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#ifndef _VALUETYPES_H_\n";
	out << "#define _VALUETYPES_H_\n\n\n"; 
	out << "#include <CORBA.h>\n";
	out << "#include \"" << file_prefix_ << "_EQUIVALENT.h\"\n\n\n";
	out.insertUserSection("file", 2);

	doGenerate();

	//
	// close file
	//
	out << "#endif\n";
	out.close();
}
	

void
GeneratorValuetypesH::doValue(IR__::ValueDef_ptr value)
{	
	std::string value_name = value->name();
	std::string class_name = mapName(value_name) + "Impl";

	//
	// value type
	//
	open_module(out, value);
	out << "\n\n//\n// " << value->id() << "\n//\n";
	out << "class " << class_name << "\n";
	out << ": virtual public " << mapFullNameWithPrefix(value, "OBV_") << "\n";
	out << ", virtual public CORBA::DefaultValueRefCountBase\n";
	out.insertUserSection(string("INHERITANCE_") + value_name, 0);
	out << "{\nprivate:\n\n";
	out.indent();
	out << "void operator= (const " << class_name << "& v);\n";
	out << class_name << " (const " << class_name << "& v);\n\n";
	out.unindent();
	out << "public:\n\n";
	out.indent();
	out << class_name << "(";
	generateMemberParam( value, false );
	out << ");\n";
	out << class_name << "();\n";
	out << "~" << class_name << "();\n\n";
	out << "CORBA::ValueBase* _copy_value();\n\n";
	// supported interfaces
	CORBA::ULong i;
	handled_interfaces_.clear();
	IR__::InterfaceDefSeq_var supp_intfs = value->supported_interfaces();
	for(i = 0; i < supp_intfs->length(); i++)
	{
		handleAttribute((*supp_intfs)[i]);
		handleOperation((*supp_intfs)[i]);
	};
	// base value
	IR__::ValueDef_var base = value->base_value();
	if(! CORBA::is_nil(base))
	{
		// todo
	}
	// abstract base values
	IR__::ValueDefSeq_var abstr = value->abstract_base_values();
	for(i = 0; i < abstr->length(); i++)
	{
		// todo
	};
	out.unindent();
	out.insertUserSection(value_name, 0);
	out << "};\n\n\n";

	//
	// value type factory
	//
	out << "class " << value_name << "FactoryImpl\n";
	out << ": virtual public CORBA::ValueFactoryBase\n{\n";
	out << "private:\n\n";
	out.indent();
	out << "virtual CORBA::ValueBase * create_for_unmarshal();\n\n";
	out.unindent();
	out << "public:\n\n";
	out.indent();
	out << value_name << "FactoryImpl();\n";
	out << value_name << "~FactoryImpl();\n\n";
	// initializers
	IR__::InitializerSeq_var ini = value->initializers();
	for(i = 0; i < ini->length(); i++)
	{
		// todo
	};
	out.unindent();
	out.insertUserSection(value_name + "_factory", 0);
	out << "};\n\n\n";

	close_module(out, value);
}


void
GeneratorValuetypesH::doEvent(IR__::EventDef_ptr event)
{
	doValue(event);
}


bool
GeneratorValuetypesH::generateMemberParam(IR__::ValueDef_ptr value, bool comma )
{
	bool set_comma = comma;

	//
	// inheritance
	//
	// base value
	IR__::ValueDef_var base = value->base_value();
	if(! CORBA::is_nil(base))
	{
		set_comma = generateMemberParam( base, set_comma );
	}
	// abstract base values
	IR__::ValueDefSeq_var abstr = value->abstract_base_values();
	CORBA::ULong i;
	for( i = 0; i < abstr->length(); i++ )
	{
		set_comma = generateMemberParam( abstr[i], set_comma );
	};

	//
	// members
	//
	IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_ValueMember, false);
	CORBA::ULong len = contained_seq->length();
	for( i = 0; i < len; i++ )
	{
		if(set_comma)
		{
			out << ", ";
		}
		IR__::ValueMemberDef_var a_member = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
		out << map_in_parameter_type (a_member->type_def()) << " ";
		out << mapName(string(a_member->name()));
		set_comma = true;
	};

	return set_comma;
}


void
GeneratorValuetypesH::doAttribute(IR__::AttributeDef_ptr attribute)
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
GeneratorValuetypesH::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}


void
GeneratorValuetypesH::doOperation(IR__::OperationDef_ptr operation)
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
GeneratorValuetypesH::doInterface(IR__::InterfaceDef_ptr intf)
{
	//
	// check whether this interface was already handled
	//
	if (handled_interfaces_.find(intf->id()) != handled_interfaces_.end())
	{
		return;
	} 
	handled_interfaces_.insert(intf->id());

	//
	// base interfaces
	//
	IR__::InterfaceDefSeq_var base_seq = intf->base_interfaces();
	for(CORBA::ULong i = 0; i < base_seq->length(); i++)
	{
		doInterface((*base_seq)[i]);
	}

	handleAttribute(intf);
	handleOperation(intf);
}


} // namespace
