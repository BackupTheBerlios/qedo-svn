#include "GeneratorValuetypesC.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorValuetypesC::GeneratorValuetypesC
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}


GeneratorValuetypesC::~GeneratorValuetypesC
()
{
}


void
GeneratorValuetypesC::check_for_generation(IR__::Contained_ptr item)
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
		IR__::EventDef_ptr event;
		
		IR__::ConsumesDefSeq_var consumes_seq;
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

		IR__::EmitsDefSeq_var emits_seq;
		emits_seq = a_composition->ccm_component()->emits_events();
		len = emits_seq->length();
		for(i = 0; i < len; i++)
		{
			// insert each emited event (check whether already inserted)
			event = ((*emits_seq)[i])->event();
			if (id_list_.find(event->id()) == id_list_.end())
			{
				id_list_.insert(event->id());
				this->insert_to_generate(event);
			}
		}

		IR__::PublishesDefSeq_var publishes_seq;
		publishes_seq = a_composition->ccm_component()->publishes_events();
		len = publishes_seq->length();
		for(i = 0; i < len; i++)
		{
			// insert each published event (check whether already inserted)
			event = ((*publishes_seq)[i])->event();
			if (id_list_.find(event->id()) == id_list_.end())
			{
				id_list_.insert(event->id());
				this->insert_to_generate(event);
			}
		}

		IR__::PrimaryKeyDef_ptr pk = a_composition->ccm_home()->primary_key();
		if(!CORBA::is_nil(pk))
		{
			this->insert_to_generate(pk);
		}

		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
};


void
GeneratorValuetypesC::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	//
	// parse for user sections and open file
	//
	out.initUserSections("valuetypes.cpp");
	out.open("valuetypes.cpp");
	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#include \"valuetypes.h\"\n";
	out << "#include \"Output.h\"\n";
	out << "#include \"RefCountBase.h\"\n\n\n";
	out.insertUserSection("file", 2);

	doGenerate();

	//
	// close file
	//
	out.close();
}
	

void
GeneratorValuetypesC::doValue(IR__::ValueDef_ptr value)
{
	open_module(out, value);
	class_name_ = mapName(value) + "Impl";
	
	out << "void\n";
	out << class_name_ << "::operator= (const " << class_name_ << "& v)\n{\n";
	out.indent();
	handleValueMember(value);
	out.insertUserSection(class_name_ + "::operator=", 0);
	out.unindent();
	out << "}\n\n\n";

	out << class_name_ << "::" << class_name_ << "(const " << class_name_ << "& v)\n{\n";
	out.indent();
	handleValueMember(value);
	out.insertUserSection(class_name_ + "::" + class_name_ + "1", 0);
	out.unindent();
	out << "}\n\n\n";

	// check whether this value(eventtype) has members.
	IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_ValueMember, false);
	if( contained_seq->length() > 0 ) // if has some, generate the constructor with parameters
	{
		out << class_name_ << "::" << class_name_ << "(";
		generateMemberParam( value, false );
		out << ")\n: " << mapFullNameWithPrefix(value, "OBV_") << "(";
		generateMemberInit( value, false );
		out << ")\n{\n";
		out.indent();
		out.insertUserSection(class_name_ + "::" + class_name_ + "2", 0);
		out.unindent();
		out << "}\n\n\n";
	}

	out << class_name_ << "::" << class_name_ << "()\n{\n";
	out.indent();
	out.insertUserSection(class_name_ + "::" + class_name_ + "3", 0);
	out.unindent();
	out << "}\n\n\n";

	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.indent();
	out.insertUserSection(class_name_ + "::~" + class_name_, 0);
	out.unindent();
	out << "}\n\n\n";

	out << "CORBA::ValueBase*\n";
	out << class_name_ << "::_copy_value()\n{\n";
	out.indent();
	out << class_name_ << " *val = new " << class_name_ << "(* this);\n";
	out.insertUserSection(class_name_ + "::_copy_value", 0);
	out << "return val;\n";
	out.unindent();
	out << "}\n\n\n";

	//
	// supported interfaces
	//
	CORBA::ULong i;
	handled_interfaces_.clear();
	IR__::InterfaceDefSeq_var supp_intfs = value->supported_interfaces();
	for(i = 0; i < supp_intfs->length(); i++)
	{
		handleAttribute((*supp_intfs)[i]);
		handleOperation((*supp_intfs)[i]);
	};
	//
	// base value
	//
	IR__::ValueDef_var base = value->base_value();
	if(! CORBA::is_nil(base))
	{
		// todo
	}
	//
	// abstract base values
	//
	IR__::ValueDefSeq_var abstr = value->abstract_base_values();
	for(i = 0; i < abstr->length(); i++)
	{
		// todo
	};

	//
	// value type factory
	//
	out << "CORBA::ValueBase *\n";
	out << value->name() << "FactoryImpl::create_for_unmarshal ()\n{\n";
	out.indent();
	out << "return new " << mapFullName( value ) << "Impl();\n";
	out.unindent();
	out << "}\n\n\n";

	//
	// initializers
	//
	IR__::InitializerSeq_var ini = value->initializers();
	for(i = 0; i < ini->length(); i++)
	{
		// todo
	};

	//
	// static factory cleaner
	//
	out << "static Qedo::ValueFactoryCleaner " << value->name() << "Factory_cleaner( new ";
	out << value->name() << "FactoryImpl(), \"" << value->id() << "\" );\n";

	close_module(out, value);
}


void
GeneratorValuetypesC::doEvent(IR__::EventDef_ptr event)
{
	doValue(event);
}


void 
GeneratorValuetypesC::doValueMember(IR__::ValueMemberDef_ptr member)
{
	IR__::IDLType_ptr type = member->type_def();
	std::string member_name = mapName(member);
	out << member_name << "( v." << member_name << "() );\n";
}


bool
GeneratorValuetypesC::generateMemberParam(IR__::ValueDef_ptr value, bool comma )
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


bool
GeneratorValuetypesC::generateMemberInit(IR__::ValueDef_ptr value, bool comma )
{
	bool set_comma = comma;

	//
	// inheritance
	//
	// base value
	IR__::ValueDef_var base = value->base_value();
	if(! CORBA::is_nil(base))
	{
		set_comma = generateMemberInit( base, set_comma );
	}
	// abstract base values
	IR__::ValueDefSeq_var abstr = value->abstract_base_values();
	CORBA::ULong i;
	for( i = 0; i < abstr->length(); i++ )
	{
		set_comma = generateMemberInit( abstr[i], set_comma );
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
		out << mapName(string(a_member->name()));
		set_comma = true;
	};

	return set_comma;
}


void
GeneratorValuetypesC::doAttribute(IR__::AttributeDef_ptr attribute)
{
	std::string attribute_name = mapName(attribute);

	//
	// not read only
	//
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void\n";
		out << class_name_ << "::" << attribute_name << "(";
		out << map_in_parameter_type(attribute->type_def()) << " param)\n";
		out << "	throw(CORBA::SystemException";
		handleException(attribute);
		out << ")\n{\n";
		out.insertUserSection(class_name_ + "::_" + attribute->name(), 0);
		out << "}\n\n\n";
	}

	out << map_return_type(attribute->type_def()) << "\n";
	out << class_name_ << "::" << attribute_name << "()\n";
	out << "	throw(CORBA::SystemException";
	handleException(attribute);
	out << ")\n{\n";
	out.insertUserSection(class_name_ + "::" + attribute->name(), 0);
	out << "}\n\n\n";
}


void 
GeneratorValuetypesC::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}


void
GeneratorValuetypesC::doOperation(IR__::OperationDef_ptr operation)
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
GeneratorValuetypesC::doInterface(IR__::InterfaceDef_ptr intf)
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
	CORBA::ULong len = base_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		doInterface((*base_seq)[i]);
	}

	handleAttribute(intf);
	handleOperation(intf);
}


} //
