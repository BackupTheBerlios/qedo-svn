#include "GeneratorServantC.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorServantC::GeneratorServantC
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: GeneratorBase(repository)
{
}


GeneratorServantC::~GeneratorServantC
()
{
}


bool
GeneratorServantC::open_module(IR__::Contained* cur_cont, std::string prefix)
{
	IR__::Container_ptr a_container = cur_cont->defined_in();
	if(a_container->def_kind() == CORBA__::dk_Module) 
	{
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(a_container);
		out << "namespace ";
		if(! this->open_module(a_module))
		{
			out << prefix;
		}
		out << a_module->name() << " {\n";
		out.indent();
		return true;
	}

	return false;
};


void
GeneratorServantC::close_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) 
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->close_module(act_mod);
		out.unindent();
		out << "};\n";
	}
};


void
GeneratorServantC::generate(string target)
{
	target_ = target;
	doGenerate(target);
}
	

void
GeneratorServantC::doModule(IR__::ModuleDef_ptr module)
{
	handleComposition(repository_);
}


void
GeneratorServantC::doAttribute(IR__::AttributeDef_ptr attribute)
{
	// attribute mode
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void" << "\n";
		out << class_name_ << "::" << attribute->name() << "(";
		out << map_in_parameter_type(attribute->type_def()) << " param)\n";
		out << "throw(CORBA::SystemException";
		handleException(attribute);
		out << ")\n{\n";
		out.indent();
		out << "try\n{\n";
		out.indent();
		out << "current_executor_ = executor_locator_->obtain_executor(\"" << executor_name_ << "\");\n";
		out.unindent();
		out << "}\ncatch (...)\n{\n";
		out.indent();
		out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
		out.unindent();
		out << "}\n\n";
		out << interface_name_ << "_ptr facet = dynamic_cast<";
		out << interface_name_ << "_ptr>(current_executor_);\n";
		out << "if (CORBA::is_nil (facet))\n{\n";
		out.indent();
		out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
		out.unindent();
		out << "}\n\n";
		out << "facet->" << attribute->name() << "(param);\n";
		out.unindent();
		out << "}\n\n\n";
	}

	out << map_return_type(attribute->type_def()) << "\n";
	out << class_name_ << "::" << attribute->name() << "()\n";
	out << "throw(CORBA::SystemException";
	handleException(attribute);
	out << ")\n{\n";
	out.indent();
	out << "try\n{\n";
	out.indent();
	out << "current_executor_ = executor_locator_->obtain_executor(\"" << executor_name_ << "\");\n";
	out.unindent();
	out << "}\ncatch (...)\n{\n";
	out.indent();
	out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
	out.unindent();
	out << "}\n\n";
	out << interface_name_ << "_ptr facet = dynamic_cast<";
	out << interface_name_ << "_ptr>(current_executor_);\n";
	out << "if (CORBA::is_nil (facet))\n{\n";
	out.indent();
	out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
	out.unindent();
	out << "}\n\n";
	out << "return facet->" << attribute->name() << "();\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << map_absolute_name(except);
}


void
GeneratorServantC::doOperation(IR__::OperationDef_ptr operation)
{
	bool is_void = false;
	if(operation->result_def()->type()->kind() == CORBA::tk_void)
	{
		is_void = true;
	}

	out << map_return_type(operation->result_def()) << "\n";
	out << class_name_ << "::" << operation->name() << "(";
	IR__::ParDescriptionSeq* pards = operation->params();
	CORBA::ULong len = pards->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
	}
	out << ")\n";
	out << "throw(CORBA::SystemException";
	handleException(operation);
	out << ")\n{\n";
	out.indent();
	out << "try\n{\n";
	out.indent();
	out << "current_executor_ = executor_locator_->obtain_executor(\"" << executor_name_ << "\");\n";
	out.unindent();
	out << "}\ncatch (...)\n{\n";
	out.indent();
	out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
	out.unindent();
	out << "}\n\n";
	out << interface_name_ << "_ptr facet = dynamic_cast<";
	out << interface_name_ << "_ptr>(current_executor_);\n";
	out << "if (CORBA::is_nil (facet))\n{\n";
	out.indent();
	out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
	out.unindent();
	out << "}\n\n";
	if(!is_void)
	{
		out << "return ";
	}
	out << "facet->" << operation->name() << "(";
	for(i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << string(pardescr.name);
	}
	out << ");\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doFactory(IR__::FactoryDef_ptr factory)
{
	out << map_return_type(composition_->ccm_component()) << "\n";
	out << class_name_ << "::" << factory->name() << "(";
	IR__::ParDescriptionSeq* pards = factory->params();
	CORBA::ULong len = pards->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
	};
	out << ")\n";
	out << "throw(CORBA::SystemException";
	handleException(factory);
	out << ")\n{\n";
	out.indent();
	out << mapLocalName(home_) << "_ptr home_executor = dynamic_cast <";
	out << mapLocalName(home_) << "_ptr> (home_executor_.in());\n";
	out << "if (! home_executor)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "return home_executor->" << factory->name() << "(";
	for(i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << string(pardescr.name);
	};
	out << ");\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doFinder(IR__::FinderDef_ptr finder)
{
	out << map_return_type(composition_->ccm_component()) << "\n";
	out << class_name_ << "::" << finder->name() << "(";
	IR__::ParDescriptionSeq* pards = finder->params();
	CORBA::ULong len = pards->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
	};
	out << ")\n";
	out << "throw(CORBA::SystemException";
	handleException(finder);
	out << ")\n{\n";
	out.indent();
	out << mapLocalName(home_) << "_ptr home_executor = dynamic_cast <";
	out << mapLocalName(home_) << "_ptr> (home_executor_.in());\n";
	out << "if (! home_executor)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "return home_executor->" << finder->name() << "(";
	for(i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << string(pardescr.name);
	};
	out << ");\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doInterface(IR__::InterfaceDef_ptr intf)
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
GeneratorServantC::doComponent(IR__::ComponentDef_ptr component)
{
	genFacetServants(component);
	genConsumerServants(component);
	genContextServantBegin(component);
	genContextServant(component);
	genComponentServantBegin(component);
	genComponentServant(component);
}


void
GeneratorServantC::doProvides(IR__::ProvidesDef_ptr provides)
{
	// provide_...
	out << map_absolute_name(provides->interface_type()) << "_ptr\n";
	out << class_name_ << "::provide_" << provides->name() << "()\n";
	out << "throw (CORBA::SystemException)\n{\n";
	out.indent();
	out << map_absolute_name(provides->interface_type()) << "_var prov = ";
	out << map_absolute_name(provides->interface_type()) << "::_narrow (ccm_object_executor_->provide_facet(\"";
	out << provides->name() << "\"));\n\n";
	out	<< "return prov._retn();\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doUses(IR__::UsesDef_ptr uses)
{
	// get_connection_...
	out << map_absolute_name(uses->interface_type()) << "_ptr\n";
	out << class_name_ << "::get_connection_" << uses->name() << "()\n";
	out << "throw (CORBA::SystemException)\n{\n";
	out.indent();
	out << "Components::ConnectedDescriptions* connections = ccm_object_executor_->get_connections(\"";
	out << uses->name() << "\");\n\n";
	out << map_absolute_name(uses->interface_type()) << "_var " << uses->name() << " = ";
	out << map_absolute_name(uses->interface_type()) << "::_narrow ((*connections)[0]->objref());\n\n";
	out << "return " << map_absolute_name(uses->interface_type()) << "::_duplicate(";
	out << uses->name() << ");\n";
	out.unindent();
	out << "}\n\n\n";

	// disconnect_...
    out << map_absolute_name(uses->interface_type()) << "_ptr\n";
	out << class_name_ << "::disconnect_" << uses->name() << "()\n";
	out << "throw(Components::NoConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << map_absolute_name(uses->interface_type()) << "_var " << uses->name() << " = get_connection_";
	out << uses->name() << "();\n\n";
	out << "ccm_object_executor_->disconnect(\"" << uses->name() << "\", (Components::Cookie*)0);\n\n";
	out << "return " << uses->name() << "._retn();\n";
	out.unindent();
	out << "}\n\n\n";

	// connect_...
    out << "void\n";
	out << class_name_ << "::connect_" << uses->name() << "(";
	out << map_absolute_name(uses->interface_type()) << "_ptr conxn)\n";
	out << "throw (Components::AlreadyConnected, Components::InvalidConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << "ccm_object_executor_->connect(\"" << uses->name() << "\", conxn);\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doEmits(IR__::EmitsDef_ptr emits)
{
	// disconnect_...
	out << map_absolute_name(emits->event()) << "Consumer*\n";
	out << class_name_ << "::disconnect_" << emits->name() << "()\n";
    out << "throw (Components::NoConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << "CORBA::Object_var " << emits->name() << "_obj = ccm_object_executor_->disconnect_consumer(\"";
	out << emits->name() << "\");\n\n";
	out << "return " << map_absolute_name(emits->event()) << "Consumer::_narrow(";
	out << emits->name() << "_obj);\n";
	out.unindent();
	out << "}\n\n\n";

	// connect_...
    out << "void\n";
	out << class_name_ << "::connect_" << emits->name() << "(";
	out << map_absolute_name(emits->event()) << "Consumer_ptr consumer)\n";
    out << "throw (Components::AlreadyConnected, CORBA::SystemException)\n{\n";
	out.indent();
	out << "ccm_object_executor_->connect_consumer(\"" << emits->name() << "\", consumer);\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doPublishes(IR__::PublishesDef_ptr publishes)
{
	out << "\n//\n// " << publishes->id() << "\n//\n";
}


void
GeneratorServantC::doConsumes(IR__::ConsumesDef_ptr consumes)
{
	// get_consumer_...
	out << map_absolute_name(consumes->event()) << "Consumer_ptr\n";
	out << class_name_ << "::get_consumer_" << consumes->name() << "()\n";
	out << "throw(CORBA::SystemException)\n{\n";
	out.indent();
	out << "Components::EventConsumerBase_var base = ccm_object_executor_->get_consumer(\"";
	out << consumes->name() << "\");\n";
	out << map_absolute_name(consumes->event()) << "Consumer_var consumer = ";
	out << map_absolute_name(consumes->event()) << "Consumer::_narrow(base);\n\n";
	out << "return consumer._retn();\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doHome(IR__::HomeDef_ptr home)
{
	genHomeServantBegin(home);
	genHomeServant(home);
}


void
GeneratorServantC::doComposition(CIDL::CompositionDef_ptr composition)
{
	composition_ = CIDL::CompositionDef::_duplicate(composition);
	filename_ = mapAbsoluteName(composition->ccm_component(), "_");
	filename_.append("_SERVANT");
	string header_name = filename_ + ".h";
	filename_.append(".cpp");
	out.open(filename_.c_str());


	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#include \"" << header_name << "\"\n";
	out << "#include \"Output.h\"\n\n\n";

	// achtung: wenn kein modul, sollte vielleicht Servant_ der prefix für alle servants sein?
	open_module(composition->ccm_component(), "Servants_");
	out << "\n\n";

	doComponent(composition->ccm_component());
	doHome(composition->ccm_home());

	close_module(composition->ccm_component());


	//
	// entry point
	//
	out << "\n\n//\n// entry point\n//\n";
	out << "Qedo::HomeServantBase*\n";
	out << "create_" << composition->ccm_home()->name() << "S(void)\n{\n";
	out.indent();
	out << "return new Servants_" << map_absolute_name(composition->ccm_home()) << "_servant();\n";
	out.unindent();
	out << "}\n\n";

	out.close();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
GeneratorServantC::genFacetServants(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base)) { genFacetServants(base); }

	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		//
		// facet servant
		//
		IR__::ProvidesDef_var provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		class_name_ = string(provides->name()) + "_servant";

		// header
		out << "// ================================================\n";
		out << "// " << class_name_ << "\n";
		out << "// ================================================\n\n";
		
		// constructor
		out << class_name_ << "::" << class_name_ << "()\n{\n}\n\n\n";
		
		// destructor
		out << class_name_ << "::~" << class_name_ << "()\n{\n}\n\n\n";

		executor_name_ = provides->name();
		interface_name_ = string(mapLocalName(provides->interface_type()));
		doInterface(provides->interface_type());

		
		//
		// facet servant factory
		//

		// header
		out << "// ================================================\n";
		out << "// " << class_name_ << "Factory\n";
		out << "// ================================================\n\n";

		out << "class " << class_name_ << "Factory : public Qedo::ServantFactory\n{\n";
		out << "public:\n";
		out.indent();
		out << "Qedo::ServantBase* create_servant() { return new " << class_name_ << "(); }\n";
		out.unindent();
		out << "};\n";
		out << "static class " << class_name_ << "Factory *_" << class_name_ << "Factory = new ";
		out << class_name_ << "Factory();\n\n\n";
	}
}


void
GeneratorServantC::genConsumerServants(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base)) { genConsumerServants(base); }

	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Consumes, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		//
		// consumer servant
		//
		IR__::ConsumesDef_var consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
		class_name_ = string(consumes->name()) + "_servant";

		// header
		out << "// ================================================\n";
		out << "// " << class_name_ << "\n";
		out << "// ================================================\n\n";
		
		// constructor
		out << class_name_ << "::" << class_name_ << "()\n{\n}\n\n\n";
		
		// destructor
		out << class_name_ << "::~" << class_name_ << "()\n{\n}\n\n\n";

		// push_event
		out << "void\n";
		out << class_name_ << "::push_event (Components::EventBase* ev) throw (CORBA::SystemException)\n{\n";
		out.indent();
		out.unindent();
		out << "}\n\n\n";

		// push_...
		out << "void\n";
		out << class_name_ << "::push_" << consumes->event()->name() << "(" << map_absolute_name(consumes->event());
		out << "* ev)\n{\n";
		out.indent();
		out.unindent();
		out << "}\n\n\n";


		//
		// consumer servant factory
		//

		// header
		out << "// ================================================\n";
		out << "// " << class_name_ << "Factory\n";
		out << "// ================================================\n\n";

		out << "class " << class_name_ << "Factory : public Qedo::ServantFactory\n{\n";
		out << "public:\n";
		out.indent();
		out << "Qedo::ServantBase* create_servant() { return new " << class_name_ << "(); }\n";
		out.unindent();
		out << "};\n";
		out << "static class " << class_name_ << "Factory *_" << class_name_ << "Factory = new ";
		out << class_name_ << "Factory();\n\n\n";
	}
}


void
GeneratorServantC::genComponentServantBegin(IR__::ComponentDef_ptr component)
{
	class_name_ = string(component->name()) + "_servant";

	// factory header
	out << "// ================================================\n";
	out << "// " << class_name_ << "Factory\n";
	out << "// ================================================\n\n";

	out << "class " << class_name_ << "Factory : public Qedo::ServantFactory\n{\n";
	out << "public:\n";
	out.indent();
	out << "Qedo::ServantBase* create_servant() { return new " << class_name_ << "(); }\n";
	out.unindent();
	out << "};\n";
	out << "static class " << class_name_ << "Factory *_" << class_name_ << "Factory = new ";
	out << class_name_ << "Factory();\n\n\n";

	// header
	out << "// ================================================\n";
	out << "// " << class_name_ << "\n";
	out << "// ================================================\n\n";

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"servant: Constructor called\");\n";
	out.unindent();
	out << "}\n\n\n";

	// desctructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"servant: Destructor called\");\n";
	out.unindent();
	out << "}\n\n\n";

	executor_name_ = "component";
	interface_name_ = string(mapLocalName(component)) + "_Executor";
}


void
GeneratorServantC::genComponentServant(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base)) { genComponentServant(base); }

	handleAttribute(component);
	handleSupportedInterface(component);
	handleProvides(component);
	handleUses(component);
	handleEmits(component);
	handlePublishes(component);
	if(component->contents(CORBA__::dk_Consumes, false)->length())
	{
		// push_event
		out << "void\n";
		out << class_name_ << "::push_event (Components::EventBase* ev) throw (CORBA::SystemException)\n{\n";
		out.indent();
		out.unindent();
		out << "}\n\n\n";

		handleConsumes(component);
	}
}


void
GeneratorServantC::genContextServantBegin(IR__::ComponentDef_ptr component)
{
	class_name_ = string(component->name()) + "_Context_callback";

	// header
	out << "// ================================================\n";
	out << "// " << class_name_ << "\n";
	out << "// ================================================\n\n";

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"servantContext: Constructor called\");\n";
	out.unindent();
	out << "}\n\n\n";

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"servantContext: Destructor called\");\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::genContextServant(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base)) { genContextServant(base); }

	// uses ports
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::UsesDef_var a_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
		
		// get_connection_...
		out << map_absolute_name(a_uses->interface_type()) << "_ptr\n";
		out << class_name_ << "::get_connection_" << a_uses->name() << "()\n{\n";
		out.indent();
		out << "Components::ConnectedDescriptions_var connections;\n";
		out << "connections = ccm_object_executor_->get_connections(\"";
		out << a_uses->name() << "\");\n\n";
		out << "if (! connections->length())\n{\n";
		out.indent();
		out << "return " << map_absolute_name(a_uses->interface_type()) << "::_nil();\n";
		out.unindent();
		out << "}\n\n";
		out << map_absolute_name(a_uses->interface_type()) << "_var ";
		out << a_uses->name() << " = ";
		out << map_absolute_name(a_uses->interface_type()) << "::_narrow (connections[0]->objref());\n\n";
		out << "return " << a_uses->name() << "._retn();\n";
		out.unindent();
		out << "}\n\n\n";
	}

	// emits ports
	contained_seq = component->contents(CORBA__::dk_Emits, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++) 
	{
		IR__::EmitsDef_var a_emits = IR__::EmitsDef::_narrow(((*contained_seq)[i]));
		
		// push_...
		out << "void\n";
		out << class_name_ << "::push_" << a_emits->name() << "(" << map_absolute_name(a_emits->event());
		out << "* ev)\n{\n";
		out.indent();
		out.unindent();
		out << "}\n\n\n";
	}
}


void
GeneratorServantC::genHomeServantBegin(IR__::HomeDef_ptr home)
{
	class_name_ = string(home->name()) + "_servant";

	// header
	out << "// ================================================\n";
	out << "// " << class_name_ << "\n";
	out << "// ================================================\n\n";

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n";
	out << ": HomeServantBase(\"" << home->id() << "\")\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"homeservant: Constructor called\");\n";
	out.unindent();
	out << "}\n\n\n";

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"homeservant: Destructor called\");\n";
	out.unindent();
	out << "}\n\n\n";

	// create
	out << map_absolute_name(composition_->ccm_component()) << "_ptr\n";
	out << class_name_ << "::create()\n";
	out << "throw(CORBA::SystemException, Components::CreateFailure)\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"Home_servant: create() called\");\n\n";
	out << mapLocalName(home) << "_ptr home_executor = dynamic_cast <";
	out << mapLocalName(home) << "_ptr> (home_executor_.in());\n";
	out << "if (! home_executor)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "Components::EnterpriseComponent_var enterprise_component;\n\n";
	out << "try\n{\n";
	out.indent();
	out << "enterprise_component = home_executor->create();\n";
	out.unindent();
	out << "}\n";
	out << "catch (Components::CCMException&)\n{\n";
	out.indent();
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "Components::ExecutorLocator_var executor_locator;\n\n";
	out << "try\n{\n";
	out.indent();
	out << "executor_locator = Components::ExecutorLocator::_narrow (enterprise_component);\n";
	out.unindent();
	out << "}\n";
	out << "catch (CORBA::SystemException&)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: This container can only handle locator-based implementations\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "Components::SessionComponent_var session_component;\n\n";
	out << "try\n{\n";
	out.indent();
	out << "session_component = Components::SessionComponent::_narrow (enterprise_component);\n";
	out.unindent();
	out << "}\n";
	out << "catch (CORBA::SystemException&)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: This is a session container, but created component is not a session component\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "// Create a new context\n";
	out << mapLocalName(home->managed_component()) << "_Context_var new_context = new ";
	out << home->managed_component()->name() << "_Context_callback();\n\n";
	out << "// Set context on component\n";
	out << "session_component->set_session_context (new_context.in());\n\n";
	out << "// Incarnate our component instance (create reference, register servant factories, ...\n";
	out << "Qedo::ComponentInstance& component_instance = this->incarnate_component\n";
	out << "	(\"" << home->managed_component()->id() << "\", executor_locator,";
	out << "dynamic_cast <Qedo::ExecutorContext*>(new_context.in()));\n\n";
	out << "// use of servant factories\n";
	out << "servant_registry_->register_servant_factory(component_instance.object_id_, _";
	out << home->managed_component()->name() << "_servantFactory);\n\n";
	out << "// Extract our Key out of the object reference\n";
	out << "CORBA::OctetSeq_var key = Qedo::Key::key_value_from_object_id(component_instance.object_id_);\n\n";
	out << "// register all ports\n";
	genFacetRegistration(home);
	genReceptacleRegistration(home);
	genEmitterRegistration(home);
	genPublisherRegistration(home);
	genConsumerRegistration(home);
	out << "\nthis->finalize_component_incarnation(component_instance.object_id_);\n\n";
	out << map_absolute_name(home->managed_component()) << "_var servant = ";
	out << map_absolute_name(home->managed_component()) << "::_narrow (component_instance.component_ref());\n\n";
	out << "return servant._retn();\n";
	out.unindent();
	out << "}\n\n\n";

	// create_component
	out << "Components::CCMObject_ptr\n";
	out << class_name_ << "::create_component()\n";
	out << "throw(CORBA::SystemException,Components::CreateFailure)\n{\n";
	out.indent();
	out << "return this->create();\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::genFacetRegistration(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base){ genFacetRegistration(base); }

	IR__::ProvidesDefSeq_var facets = home->managed_component()->provides_interfaces();
	CORBA::ULong len = facets->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		std::string name = (*facets)[i]->name();
		out << "CORBA::Object_var "	<< name << "_ref = this->create_object_reference(key, \"";
		out << (*facets)[i]->id() << "\");\n";
		out << "PortableServer::ObjectId_var " << name << "_object_id = this->reference_to_oid (";
		out << name << "_ref);\n";
		out << "servant_registry_->register_servant_factory (";
		out << name << "_object_id, _" << name << "_servantFactory);\n";
		out << "component_instance.ccm_object_executor_->add_facet(\"";
		out << name << "\", \"" << (*facets)[i]->interface_type()->id() << "\", " << name << "_ref);\n\n";
	}
}


void
GeneratorServantC::genReceptacleRegistration(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base){ genReceptacleRegistration(base); }

	IR__::UsesDefSeq_var receptacles = home->managed_component()->uses_interfaces();
	CORBA::ULong len = receptacles->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		out << "component_instance.ccm_object_executor_->add_receptacle(\"";
		out << (*receptacles)[i]->name() << "\", \"" << (*receptacles)[i]->interface_type()->id() << "\", ";
		if((*receptacles)[i]->is_multiple()) { 
			out << "true);\n\n";
		}
		else { 
			out << "false);\n\n";
		}
	}
}


void
GeneratorServantC::genEmitterRegistration(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base){ genEmitterRegistration(base); }

	IR__::EmitsDefSeq_var emits = home->managed_component()->emits_events();
	CORBA::ULong len = emits->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		std::string id = (*emits)[i]->event()->id();
		id.insert(id.find_last_of(":"), "Consumer");
		out << "component_instance.ccm_object_executor_->add_emitter(\"";
		out << (*emits)[i]->name() << "\", \"" << id << "\");\n\n";
	}
}


void
GeneratorServantC::genPublisherRegistration(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base){ genPublisherRegistration(base); }

	IR__::PublishesDefSeq_var publishes = home->managed_component()->publishes_events();
	CORBA::ULong len = publishes->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		std::string id = (*publishes)[i]->event()->id();
		id.insert(id.find_last_of(":"), "Consumer");
		out << "component_instance.ccm_object_executor_->add_publisher(\"";
		out << (*publishes)[i]->name() << "\", \"" << id << "\");\n\n";
	}
}


void
GeneratorServantC::genConsumerRegistration(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base){ genConsumerRegistration(base); }

	IR__::ConsumesDefSeq_var consumes = home->managed_component()->consumes_events();
	CORBA::ULong len = consumes->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		std::string id = (*consumes)[i]->event()->id();
		id.insert(id.find_last_of(":"), "Consumer");
		std::string name = (*consumes)[i]->name();
		out << "CORBA::Object_var " << name << "_ref = this->create_object_reference (key, \"" << id << "\");\n";
		out << "PortableServer::ObjectId_var " << name << "_id = this->reference_to_oid(" << name << "_ref);\n";
		out << "servant_registry_->register_servant_factory (" << name << "_id, _" << name << "_servantFactory);\n";
		out << "Components::EventConsumerBase_var " << name << "_sink = Components::EventConsumerBase::_narrow(";
		out << name << "_ref);\n";
		out << "component_instance.ccm_object_executor_->add_consumer(\"";
		out << name << "\", \"" << id << "\", " << name << "_sink);\n\n";
	}
}


void
GeneratorServantC::genHomeServant(IR__::HomeDef_ptr home)
{
	CORBA::ULong i;
	CORBA::ULong ii;
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base){ genHomeServant(base); }
	
	home_ = IR__::HomeDef::_duplicate(home);

	// attributes
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Attribute, false);
	CORBA::ULong len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(((*contained_seq)[i]));
		
		// attribute mode
		if(attribute->mode() == IR__::ATTR_NORMAL)
		{
			out << "void" << "\n";
			out << class_name_ << "::" << attribute->name() << "(";
			out << map_in_parameter_type(attribute->type_def()) << " param)\n";
			out << "throw(CORBA::SystemException";
			handleException(attribute);
			out << ")\n{\n";
			out.indent();
			out << mapLocalName(home) << "_ptr home_executor = dynamic_cast <";
			out << mapLocalName(home) << "_ptr> (home_executor_.in());\n";
			out << "if (! home_executor)\n{\n";
			out.indent();
			out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
			out << "throw Components::CreateFailure();\n";
			out.unindent();
			out << "}\n\n";
			out << "home_executor->" << attribute->name() << "(param);\n";
			out.unindent();
			out << "}\n\n\n";
		}

		out << map_return_type(attribute->type_def()) << "\n";
		out << class_name_ << "::" << attribute->name() << "()\n";
		out << "throw(CORBA::SystemException";
		handleException(attribute);
		out << ")\n{\n";
		out.indent();
		out << mapLocalName(home) << "_ptr home_executor = dynamic_cast <";
		out << mapLocalName(home) << "_ptr> (home_executor_.in());\n";
		out << "if (! home_executor)\n{\n";
		out.indent();
		out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
		out << "throw Components::CreateFailure();\n";
		out.unindent();
		out << "}\n\n";
		out << "return home_executor->" << attribute->name() << "();\n";
		out.unindent();
		out << "}\n\n\n";
	}

	// operations
	contained_seq = home->contents(CORBA__::dk_Operation, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::OperationDef_var operation = IR__::OperationDef::_narrow(((*contained_seq)[i]));

		bool is_void = false;
		if(operation->result_def()->type()->kind() == CORBA::tk_void) { is_void = true; }

		out << map_return_type(operation->result_def()) << "\n";
		out << class_name_ << "::" << operation->name() << "(";
		IR__::ParDescriptionSeq* pards = operation->params();
		CORBA::ULong len = pards->length();
		for(ii = len; ii > 0; ii--)
		{
			if(ii < len) { out << ", "; }
			IR__::ParameterDescription pardescr = (*pards)[ii - 1];
			out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		}
		out << ")\n";
		out << "throw(CORBA::SystemException";
		handleException(operation);
		out << ")\n{\n";
		out.indent();
		out << mapLocalName(home) << "_ptr home_executor = dynamic_cast <";
		out << mapLocalName(home) << "_ptr> (home_executor_.in());\n";
		out << "if (! home_executor)\n{\n";
		out.indent();
		out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
		out << "throw Components::CreateFailure();\n";
		out.unindent();
		out << "}\n\n";
		if(!is_void) { out << "return "; }
		out << "home_executor->" << operation->name() << "(";
		for(ii = len; ii > 0; ii--)
		{
			if(ii < len) { out << ", "; }
			IR__::ParameterDescription pardescr = (*pards)[ii - 1];
			out << string(pardescr.name);
		}
		out << ");\n";
		out.unindent();
		out << "}\n\n\n";
	}

	handleFactory(home);
	handleFinder(home);
}


} //