#include "GeneratorBusinessC.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorBusinessC::GeneratorBusinessC
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: GeneratorBase(repository)
{
}


GeneratorBusinessC::~GeneratorBusinessC
()
{
}


void
GeneratorBusinessC::open_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) {
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->open_module(act_mod);
		out << "namespace " << mapName(act_mod) << " {\n";
	}
};


void
GeneratorBusinessC::close_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) {
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->close_module(act_mod);
		out << "};\n";
	}
};


void
GeneratorBusinessC::generate(string target)
{
	target_ = target;
	doGenerate(target);
}
	

void
GeneratorBusinessC::doModule(IR__::ModuleDef_ptr module)
{
	IR__::ContainedSeq_var contained_seq;

	// contained compositions
	contained_seq = repository_->contents(CORBA__::dk_Composition, true);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		CIDL::CompositionDef_var act_composition = CIDL::CompositionDef::_narrow(((*contained_seq)[i]));
		doComposition(act_composition);
	}
}


void
GeneratorBusinessC::doValue(IR__::ValueDef_ptr value)
{
	class_name_ = mapName(value) + "::";
	handleValueMember(value);

	//
	// value type factory
	//
	out << "CORBA::ValueBase *\n";
	out << value->name() << "_factory::create_for_unmarshal ()\n{\n";
	out.indent();
	out << "return new " << map_absolute_under_name(value) << "_impl;\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorBusinessC::doValueMember(IR__::ValueMemberDef_ptr member)
{
	IR__::IDLType_ptr type = member->type_def();
	std::string member_name = mapName(member);

	switch (type->type()->kind()) {
	case CORBA::tk_string:
		out << "void\n";
		out << class_name_ << member_name << "(char* _p)\n{\n";
		out.indent();
		out << "_m." << member_name << " = CORBA::string_dup(_p);\n";
		out.unindent();
		out << "}\n\n\n";

		out << "void\n";
		out << class_name_ << member_name << "(const char* _p)\n{\n";
		out.indent();
		out << "_m." << member_name << " = CORBA::string_dup(_p);\n";
		out.unindent();
		out << "}\n\n\n";

		out << "void\n";
		out << class_name_ << member_name << "(const CORBA::String_var& _p)\n{\n";
		out.indent();
		out << "_m." << member_name << " = CORBA::string_dup(_p);\n";
		out.unindent();
		out << "}\n\n\n";

		out << "const char*\n";
		out << class_name_ << member_name << "() const\n{\n";
		out.indent();
		out << "return CORBA::string_dup(_m." << member_name << ");\n";
		out.unindent();
		out << "}\n\n\n";
		break;
		
	case CORBA::tk_enum:
		out << "void\n";
		out << class_name_ << member_name << "(" << map_in_parameter_type(type) << " _p)\n{\n";
		out.indent();
		out << "_m." << member_name << " = _p;\n";
		out.unindent();
		out << "}\n\n\n";

		out << map_value_return_type(type) << "\n";
		out << class_name_ << member_name << "()\n{\n";
		out.indent();
		out << "return _m." << member_name << ";\n";
		out.unindent();
		out << "}\n\n\n";

		out << "const " << map_value_return_type(type) << "\n";
		out << class_name_ << member_name << "() const\n{\n";
		out.indent();
		out << "return _m." << member_name << ";\n";
		out.unindent();
		out << "}\n\n\n";
		break;

	default:
		out << "void\n";
		out << class_name_ << member_name << "(" << map_in_parameter_type(type) << " _p)\n{\n";
		out.indent();
		out << "_m." << member_name << " = _p;\n";
		out.unindent();
		out << "}\n\n\n";

		out << map_value_return_type(type) << "\n";
		out << class_name_ << member_name << "() const\n{\n";
		out.indent();
		out << "return _m." << member_name << ";\n";
		out.unindent();
		out << "}\n\n\n";
	}
}


void
GeneratorBusinessC::doAttribute(IR__::AttributeDef_ptr attribute)
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
GeneratorBusinessC::doOperation(IR__::OperationDef_ptr operation)
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
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	}
	out << ")\n{\n";
	out.insertUserSection(class_name_ + "::" + operation->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doFactory(IR__::FactoryDef_ptr factory)
{
	std::string factory_name = mapName(factory);

	out << map_return_type(composition_->ccm_component()) << "\n";
	out << class_name_ << "::" << factory_name << "(";

	//
	// Parameter of the operation
	//
	IR__::ParDescriptionSeq* pards = factory->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	}
	out << ")\n";
	out << "{\n";
	out.insertUserSection(class_name_ + "::" + factory->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doFinder(IR__::FinderDef_ptr finder)
{
	std::string finder_name = mapName(finder);

	out << map_return_type(composition_->ccm_component()) << "\n";
	out << class_name_ << "::" << finder_name << "(";

	//
	// parameters
	//
	IR__::ParDescriptionSeq* pards = finder->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	}
	out << ")\n";
	out << "{\n";
	out.insertUserSection(class_name_ + "::" + finder->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doInterface(IR__::InterfaceDef_ptr intf)
{
	// base interfaces
	IR__::InterfaceDefSeq_var base_seq = intf->base_interfaces();
	CORBA::ULong len = base_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		doInterface((*base_seq)[i]);
	}

	handleAttribute(intf);
	handleOperation(intf);
}


void
GeneratorBusinessC::doComponent(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		doComponent(base);
	}

	handleAttribute(component);
	handleSupportedInterface(component);

	// contained provides
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ProvidesDef_var act_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		bool realized_by_segment = false;

		// exclude facets realized by a segment
		CIDL::SegmentDefSeq_var segment_seq = composition_->executor()->segments();
		for (CORBA::ULong ii = 0; ii < segment_seq->length(); ii++)
		{
			// for each implemented facet
			IR__::ProvidesDefSeq_var provided_seq = segment_seq[ii]->provided_facets();
			for (CORBA::ULong iii = 0; iii < provided_seq->length(); iii++)
			{
				if(!strcmp(act_provides->name(), provided_seq[iii]->name()))
				{
					realized_by_segment = true;
					break;
				}
			}
		}

		if(!realized_by_segment)
		{
			doInterface(act_provides->interface_type());
		}
	}

	// consumes
	if(component->contents(CORBA__::dk_Consumes, false)->length() && need_push_)
	{
		out << "void\n";
		out << class_name_ << "::push_event (Components::EventBase* ev)\n{\n";
		out.insertUserSection(class_name_ + "::push_event", 0);
		out << "}\n\n\n";
		need_push_ = false;
	}
	handleConsumes(component);
}


void
GeneratorBusinessC::doConsumes(IR__::ConsumesDef_ptr consumes)
{
    // push_...
	out << "void\n";
	out << class_name_ << "::push_" << consumes->event()->name() << "(" << mapFullName(consumes->event());
	out << "* ev)\n{\n";
	out.insertUserSection(class_name_ + "::push_" + consumes->event()->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doHome(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base)
	{ 
		doHome(base);
	}

	handleAttribute(home);
	handleOperation(home);
	handleFactory(home);
	handleFinder(home);
}


void
GeneratorBusinessC::doComposition(CIDL::CompositionDef_ptr composition)
{
	CORBA::ULong i;
	composition_ = CIDL::CompositionDef::_duplicate(composition);
	filename_ = "";
	CIDL::SegmentDefSeq_var segment_seq = composition->executor()->segments();

	
	string id = composition->id();
	IR__::Contained_ptr module_def = 0;
	string::size_type pos = id.find_last_of("/");
	if(pos != string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		filename_ = mapAbsoluteName(module_def, "_");
		filename_.append("_");
	}
	filename_.append(composition->name());
	string header_name = filename_ + ".h";
	filename_.append(".cpp");
	

	//
	// parse for user sections and write header in output file
	//
	out.initUserSections(filename_.c_str());
	out.open(filename_.c_str());
	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#include \"" << header_name << "\"\n\n\n";
	out.insertUserSection("file", 2);

	// open module
	if(module_def)
	{
		open_module(module_def);
		out << "namespace " << mapName(module_def) << " {\n\n\n";
	}

	std::string context_name = mapFullNameLocal(composition->ccm_component()) + "_Context";

	//
	// executor
	//
	class_name_ = mapName(composition->executor());
	out.insertUserSection(class_name_, 2);

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::" + class_name_, 0);
	out << "}\n\n\n";

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::~" + class_name_, 0);
	out << "}\n\n\n";
	
	// set_context
	out << "void\n";
	out << class_name_ << "::set_context(" << context_name << "_ptr context)\n{\n";
	out.indent();
    out << "context_ = " << context_name << "::_duplicate(context);\n";
	out.unindent();
	out << "}\n\n\n";

	// configuration_complete
	out << "void\n";
	out << class_name_ << "::configuration_complete()\n{\n";
	out.insertUserSection(class_name_ + "::configuration_complete", 0);	
	out << "}\n\n\n";

	// stop
	out << "void\n";
	out << class_name_ << "::stop()\n{\n";
	out.insertUserSection(class_name_ + "::stop", 0);	
	out << "}\n\n\n";

	// remove
	out << "void\n";
	out << class_name_ << "::remove()\n{\n";
	out.insertUserSection(class_name_ + "::remove", 0);	
	out << "}\n\n\n";

	need_push_ = true;
	doComponent(composition->ccm_component());


	//
	// segment
	//
	for (i = 0; i < segment_seq->length(); i++)
	{
		class_name_ = mapName(segment_seq[i]);
		out.insertUserSection(class_name_, 2);

		// constructor
		out << class_name_ << "::" << class_name_ << "()\n{\n";
		out.insertUserSection(class_name_ + "::" + class_name_, 0);
		out << "}\n\n\n";

		// destructor
		out << class_name_ << "::~" << class_name_ << "()\n{\n";
		out.insertUserSection(class_name_ + "::~" + class_name_, 0);
		out << "}\n\n\n";

		// set context
		out << "void\n";
		out << class_name_ << "::set_context(" << context_name << "_ptr context)\n{\n";
		out.indent();
		out << "context_ = " << context_name << "::_duplicate(context);\n";
		out.unindent();
		out << "}\n\n\n";

		// configuration complete
		out << "void\n";
		out << class_name_ << "::configuration_complete()\n{\n";
		out.insertUserSection(class_name_ + "::configuration_complete", 0);
		out << "}\n\n\n";

		// for each implemented facet
		IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
		for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
		{
			doInterface(provided_seq[ii]->interface_type());
		}
	}
	

	//
	// executor locator
	//
	class_name_ = mapName(composition);
	out.insertUserSection(class_name_, 2);

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n";
	out.indent();
	out << ": component_(new " << mapName(composition->executor()) << "())\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << ", " << segment_seq[i]->name() << "_(new " << mapName(segment_seq[i]) << "())\n";
	}
	out.unindent();
	out << "{\n";
	out.insertUserSection(class_name_ + "::" + class_name_, 0);
	out << "}\n\n\n";

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.indent();
	out << "component_->_remove_ref();\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "_->_remove_ref();\n";
	}
	out.unindent();
	out << "\n";
	out.insertUserSection(class_name_ + "::~" + class_name_, 0);
	out << "}\n\n\n";

	// obtain executor
	out << "::CORBA::Object*\n";
	out << class_name_ << "::obtain_executor(const char* name)\n{\n";
	out.indent();
	out << "if (! strcmp ( name, \"component\" ) ) {\n";
	out.indent();
	out << "return Components::EnterpriseComponent::_duplicate (component_);\n";
	out.unindent();
	out << "}\n\n";
	IR__::ProvidesDefSeq_var provides_seq = composition->ccm_component()->provides_interfaces();
	string impl_by;
	for (i = 0; i < provides_seq->length(); i++) {
		// for each facet
		impl_by = "component";
		out << "else if (! strcmp (name, \"" << provides_seq[i]->name() << "\")) {\n";
		out.indent();
		out << "return Components::EnterpriseComponent::_duplicate (";
		// determine segment implementing the facet
		for (CORBA::ULong ii = 0; ii < segment_seq->length(); ii++)	{
			IR__::ProvidesDefSeq_var impl_seq = segment_seq[ii]->provided_facets();
			for (CORBA::ULong iii = 0; iii < impl_seq->length(); iii++) {
				if(! strcmp(provides_seq[i]->name(), impl_seq[iii]->name())) {
					impl_by = segment_seq[ii]->name();
				}
			}
		}
		out << impl_by << "_);\n";
		out.unindent();
		out << "}\n\n";
	}
	out << "return Components::EnterpriseComponent::_nil();\n";
	out.unindent();
	out << "}\n\n\n";

	// release executor
	out << "void\n";
	out << class_name_ << "::release_executor(::CORBA::Object_ptr executor)\n{\n";
	out.indent();
	out << "CORBA::release (executor);\n";
	out.unindent();
	out << "}\n\n\n";

	// configuration complete
	out << "void\n";
	out << class_name_ << "::configuration_complete()\n{\n";
	out.indent();
	out << "component_->configuration_complete();\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "_->configuration_complete();\n";
	}
	out.unindent();
	out << "\n";
	out.insertUserSection(class_name_ + "::configuration_complete", 0);
	out << "}\n\n\n";

	// set session context
	out << "void\n";
	out << class_name_ << "::set_session_context(::Components::SessionContext_ptr context)\n{\n";
	out.indent();
    out << "context_ = " << context_name << "::_narrow(context);\n\n";
	out << "component_->set_context(context_);\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "_->set_context(context_);\n";
	}
	out.unindent();
	out << "}\n\n\n";

	// ccm_activate
	out << "void\n";
	out << class_name_ << "::ccm_activate()\n{\n";
	out.insertUserSection(class_name_ + "::ccm_activate", 0);
	out << "}\n\n\n";

	// ccm_passivate
	out << "void\n";
	out << class_name_ << "::ccm_passivate()\n{\n";
	out.insertUserSection(class_name_ + "::ccm_passivate", 0);
	out << "}\n\n\n";

	// ccm_remove
	out << "void\n";
	out << class_name_ << "::ccm_remove()\n{\n";
	out.insertUserSection(class_name_ + "::ccm_remove", 0);
	out << "}\n\n\n";

	
	//
	// home executor
	//
	class_name_ = mapName(composition->home_executor());
	out.insertUserSection(class_name_, 2);

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::" + class_name_, 0);
	out << "}\n\n\n";

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::~" + class_name_, 0);
	out << "}\n\n\n";

	// set context
	out << "void\n";
	out << class_name_ << "::set_context(Components::CCMContext_ptr ctx)\n{\n";
	out.indent();
    out << "context_ = " << context_name << "::_narrow(ctx);\n";
	out.unindent();
	out << "}\n\n\n";

	// create
	out << "::Components::ExecutorLocator_ptr\n";
	out << class_name_ << "::create ()\n{\n";
	out.indent();
	out.insertUserSection(class_name_ + "::create", 0);
	out << "return new " << mapName(composition) << "();\n";
	out.unindent();
	out << "}\n\n\n";

	doHome(composition->ccm_home());

	// close module
	if(module_def)
	{
		out << "};\n";
		close_module(module_def);
	}


	//
	// entry point
	//
	out << "\n\n//\n// entry point\n//\n";
	out << "::Components::HomeExecutorBase_ptr\n";
	out << "create_" << composition->ccm_home()->name() << "E(void)\n{\n";
	out.indent();
	out.insertUserSection(string("create_") + composition->ccm_home()->name());
	out << "return new " << mapFullName(module_def) << "::";
	out << mapName(composition->home_executor()) << "();\n";
	out.unindent();
	out << "}\n\n";

	out.close();
}

} //