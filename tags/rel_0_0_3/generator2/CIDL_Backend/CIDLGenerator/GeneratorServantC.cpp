#include "GeneratorServantC.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorServantC::GeneratorServantC
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}


GeneratorServantC::~GeneratorServantC
()
{
}


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
	std::string attribute_name = mapName(attribute);

	// not read only
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void" << "\n";
		out << class_name_ << "::" << attribute_name << "(";
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
		out << "facet->" << attribute_name << "(param);\n";
		out.unindent();
		out << "}\n\n\n";
	}

	out << map_return_type(attribute->type_def()) << "\n";
	out << class_name_ << "::" << attribute_name << "()\n";
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
	out << "return facet->" << attribute_name << "();\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}


void
GeneratorServantC::doOperation(IR__::OperationDef_ptr operation)
{
	bool is_void = false;
	std::string operation_name = mapName(operation);

	if(operation->result_def()->type()->kind() == CORBA::tk_void)
	{
		is_void = true;
	}

	out << map_return_type(operation->result_def()) << "\n";
	out << class_name_ << "::" << operation_name << "(";
	IR__::ParDescriptionSeq* pards = operation->params();
	CORBA::ULong len = pards->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
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
	out << "facet->" << operation_name << "(";
	for(i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << mapName(string(pardescr.name));
	}
	out << ");\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doFactory(IR__::FactoryDef_ptr factory)
{
	std::string factory_name = mapName(factory);
	std::string home_name = mapFullNameLocal(home_);
	std::string component_name = mapFullName(home_->managed_component());

	out << map_return_type(composition_->ccm_component()) << "\n";
	out << class_name_ << "::" << factory_name << "(";
	IR__::ParDescriptionSeq* pards = factory->params();
	CORBA::ULong len = pards->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	};
	out << ")\n";
	out << "throw(CORBA::SystemException";
	handleException(factory);
	out << ")\n{\n";
	out.indent();
	out << home_name << "_ptr home_executor = dynamic_cast <";
	out << home_name << "_ptr> (home_executor_.in());\n";
	out << "if (! home_executor)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "Components::EnterpriseComponent_var enterprise_component;\n\n";
	out << "try\n{\n";
	out.indent();
	out << "enterprise_component = home_executor->" << factory_name << "(";
	for(i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << mapName(string(pardescr.name));
	};
	out << ");\n";
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
	out << mapFullNameLocal(home_->managed_component()) << "_Context_var new_context = new ";
	out << home_->managed_component()->name() << "_Context_callback();\n\n";
	out << "// Set context on component\n";
	out << "session_component->set_session_context (new_context.in());\n\n";
	out << "// Incarnate our component instance (create reference, register servant factories, ...\n";
	out << "Qedo::ComponentInstance& component_instance = this->incarnate_component\n";
	out << "	(\"" << home_->managed_component()->id() << "\", executor_locator,";
	out << "dynamic_cast <Qedo::ExecutorContext*>(new_context.in()));\n\n";
	out << "// use of servant factories\n";
	out << "servant_registry_->register_servant_factory(component_instance.object_id_, _";
	out << home_->managed_component()->name() << "_servantFactory);\n\n";
	out << "// Extract our Key out of the object reference\n";
	out << "CORBA::OctetSeq_var key = Qedo::Key::key_value_from_object_id(component_instance.object_id_);\n\n";
	out << "// register all ports\n";
	genFacetRegistration(home_);
	genReceptacleRegistration(home_);
	genEmitterRegistration(home_);
	genPublisherRegistration(home_);
	genConsumerRegistration(home_);
	out << "\nthis->finalize_component_incarnation(component_instance.object_id_);\n\n";
	out << component_name << "_var servant = ";
	out << component_name << "::_narrow (component_instance.component_ref());\n\n";
	out << "return servant._retn();\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doFinder(IR__::FinderDef_ptr finder)
{
	std::string finder_name = mapName(finder);
	std::string home_name = mapFullNameLocal(home_);
	std::string component_name = mapFullName(home_->managed_component());

	out << map_return_type(composition_->ccm_component()) << "\n";
	out << class_name_ << "::" << finder_name << "(";
	IR__::ParDescriptionSeq* pards = finder->params();
	CORBA::ULong len = pards->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	};
	out << ")\n";
	out << "throw(CORBA::SystemException";
	handleException(finder);
	out << ")\n{\n";
	out.indent();
	out << home_name << "_ptr home_executor = dynamic_cast <";
	out << home_name << "_ptr> (home_executor_.in());\n";
	out << "if (! home_executor)\n{\n";
	out.indent();
	out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
	out << "throw Components::CreateFailure();\n";
	out.unindent();
	out << "}\n\n";
	out << "Components::EnterpriseComponent_var enterprise_component;\n\n";
	out << "try\n{\n";
	out.indent();
	out << "enterprise_component = home_executor->" << finder_name << "(";
	for(i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << mapName(string(pardescr.name));
	};
	out << ");\n";
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
	out << mapFullNameLocal(home_->managed_component()) << "_Context_var new_context = new ";
	out << home_->managed_component()->name() << "_Context_callback();\n\n";
	out << "// Set context on component\n";
	out << "session_component->set_session_context (new_context.in());\n\n";
	out << "// Incarnate our component instance (create reference, register servant factories, ...\n";
	out << "Qedo::ComponentInstance& component_instance = this->incarnate_component\n";
	out << "	(\"" << home_->managed_component()->id() << "\", executor_locator,";
	out << "dynamic_cast <Qedo::ExecutorContext*>(new_context.in()));\n\n";
	out << "// use of servant factories\n";
	out << "servant_registry_->register_servant_factory(component_instance.object_id_, _";
	out << home_->managed_component()->name() << "_servantFactory);\n\n";
	out << "// Extract our Key out of the object reference\n";
	out << "CORBA::OctetSeq_var key = Qedo::Key::key_value_from_object_id(component_instance.object_id_);\n\n";
	out << "// register all ports\n";
	genFacetRegistration(home_);
	genReceptacleRegistration(home_);
	genEmitterRegistration(home_);
	genPublisherRegistration(home_);
	genConsumerRegistration(home_);
	out << "\nthis->finalize_component_incarnation(component_instance.object_id_);\n\n";
	out << component_name << "_var servant = ";
	out << component_name << "::_narrow (component_instance.component_ref());\n\n";
	out << "return servant._retn();\n";
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
	out << mapFullName(provides->interface_type()) << "_ptr\n";
	out << class_name_ << "::provide_" << provides->name() << "()\n";
	out << "throw (CORBA::SystemException)\n{\n";
	out.indent();
	out << mapFullName(provides->interface_type()) << "_var prov = ";
	out << mapFullName(provides->interface_type()) << "::_narrow (ccm_object_executor_->provide_facet(\"";
	out << provides->name() << "\"));\n\n";
	out	<< "return prov._retn();\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doUses(IR__::UsesDef_ptr uses)
{
	std::string interface_name = mapFullName(uses->interface_type());

	// get_connection_...
	out << interface_name << "_ptr\n";
	out << class_name_ << "::get_connection_" << uses->name() << "()\n";
	out << "throw (CORBA::SystemException)\n{\n";
	out.indent();
	out << "Components::ConnectedDescriptions* connections = ccm_object_executor_->get_connections(\"";
	out << uses->name() << "\");\n\n";
	out << interface_name << "_var use = ";
	out << interface_name << "::_narrow ((*connections)[0]->objref());\n\n";
	out << "return " << interface_name << "::_duplicate(use);\n";
	out.unindent();
	out << "}\n\n\n";

	// disconnect_...
    out << interface_name << "_ptr\n";
	out << class_name_ << "::disconnect_" << uses->name() << "()\n";
	out << "throw(Components::NoConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << interface_name << "_var use = get_connection_" << uses->name() << "();\n\n";
	out << "ccm_object_executor_->disconnect(\"" << uses->name() << "\", (Components::Cookie*)0);\n\n";
	out << "return use._retn();\n";
	out.unindent();
	out << "}\n\n\n";

	// connect_...
    out << "void\n";
	out << class_name_ << "::connect_" << uses->name() << "(";
	out << interface_name << "_ptr conxn)\n";
	out << "throw (Components::AlreadyConnected, Components::InvalidConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << "ccm_object_executor_->connect(\"" << uses->name() << "\", conxn);\n";
	out.unindent();
	out << "}\n\n\n";
}


void 
GeneratorServantC::doEmits(IR__::EmitsDef_ptr emits)
{
	out << "\n//\n// " << emits->id() << "\n//\n";
	std::string event_name = mapFullName(emits->event());

	// disconnect_...
	out << event_name << "Consumer*\n";
	out << class_name_ << "::disconnect_" << emits->name() << "()\n";
    out << "throw (Components::NoConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << "CORBA::Object_var emi = ccm_object_executor_->disconnect_consumer(\"";
	out << emits->name() << "\");\n\n";
	out << "return " << event_name << "Consumer::_narrow(emi);\n";
	out.unindent();
	out << "}\n\n\n";

	// connect_...
    out << "void\n";
	out << class_name_ << "::connect_" << emits->name() << "(";
	out << event_name << "Consumer_ptr consumer)\n";
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
	std::string event_name = mapFullName(publishes->event());

	// subscribe_...
	out << "::Components::Cookie*\n";
	out << class_name_ << "::subscribe_" << publishes->name() << "(";
	out << event_name << "Consumer_ptr consumer)\n";
	out << "throw (Components::ExceededConnectionLimit, CORBA::SystemException)\n{\n";
	out.indent();
	out << "return ccm_object_executor_->subscribe(\"" << publishes->name() << "\", consumer);\n";
	out.unindent();
	out << "}\n\n\n";

	// unsubscribe_...
	out << event_name << "Consumer_ptr\n";
	out << class_name_ << "::unsubscribe_" << publishes->name() << "(";
	out << "::Components::Cookie* ck)\n";
	out << "throw (Components::InvalidConnection, CORBA::SystemException)\n{\n";
	out.indent();
	out << "return " << event_name << "Consumer::_narrow(ccm_object_executor_->unsubscribe(\"" << publishes->name() << "\", ck));\n";
	out.unindent();
	out << "}\n\n\n";
}


void
GeneratorServantC::doConsumes(IR__::ConsumesDef_ptr consumes)
{
	std::string event_name = mapFullName(consumes->event());

	// get_consumer_...
	out << event_name << "Consumer_ptr\n";
	out << class_name_ << "::get_consumer_" << consumes->name() << "()\n";
	out << "throw(CORBA::SystemException)\n{\n";
	out.indent();
	out << "Components::EventConsumerBase_var base = ccm_object_executor_->get_consumer(\"";
	out << consumes->name() << "\");\n";
	out << event_name << "Consumer_var consumer = " << event_name << "Consumer::_narrow(base);\n\n";
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

	// achtung: wenn kein modul, sollte vielleicht Servant_ der prefix f�r alle servants sein?
	open_module(out, composition->ccm_component(), "Servants_");
	out << "\n\n";

	doComponent(composition->ccm_component());
	doHome(composition->ccm_home());

	close_module(out, composition->ccm_component());


	//
	// entry point
	//
	out << "\n\n//\n// entry point\n//\n";
	out << "Qedo::HomeServantBase*\n";
	out << "create_" << composition->ccm_home()->name() << "S(void)\n{\n";
	out.indent();
	out << "return new " << mapFullNameServant(composition->ccm_home()) << "_servant();\n";
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
	if(!CORBA::is_nil(base))
	{ 
		genFacetServants(base);
	}

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
		interface_name_ = mapFullNameLocal(provides->interface_type());
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
	if(!CORBA::is_nil(base))
	{ 
		genConsumerServants(base);
	}

	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Consumes, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		//
		// consumer servant
		//
		IR__::ConsumesDef_var consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
		class_name_ = string(consumes->name()) + "_servant";
		std::string event_consumer = mapFullNameLocal(consumes->event()) + "Consumer";
		std::string event_name = mapFullName(consumes->event());

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
		out << event_name << "* event = " << event_name << "::_downcast (ev);\n\n";
		out << "if (!event)\n{\n";
		out.indent();
        out << "// handle error\n";
        out << "throw ::CORBA::INTERNAL(42,::CORBA::COMPLETED_NO);\n";
		out.unindent();
		out << "}\n\n";
		out << "push_" << consumes->event()->name() << "(event);\n";
		out.unindent();
		out << "}\n\n\n";

		// push_...
		out << "void\n";
		out << class_name_ << "::push_" << consumes->event()->name() << "(" << event_name;
		out << "* ev)\n{\n";
		out.indent();
		out << "try\n{\n";
		out.indent();
        out << "current_executor_ = executor_locator_->obtain_executor(\"component\");\n";
		out.unindent();
		out << "}\n";
		out << "catch (...)\n{\n";
		out.indent();
        out << "// handle error\n";
		out << "DEBUG_OUT (\"servantContext: can not obtain executor\");\n";
        out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
		out.unindent();
		out << "}\n\n";
		out << event_consumer << "_ptr consumer_ptr = ";
		out << "dynamic_cast <" << event_consumer << "_ptr>(current_executor_);\n\n";
		out << "if (CORBA::is_nil (consumer_ptr))\n{\n";
		out.indent();
        out << "// handle error\n";
		out << "DEBUG_OUT (\"servantContext: can not cast consumer\");\n";
        out << "throw CORBA::INTERNAL (42, CORBA::COMPLETED_NO);\n";
		out.unindent();	
		out << "}\n\n";
	    out << "consumer_ptr->push_" << consumes->event()->name() << "(ev);\n";
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
	interface_name_ = mapFullNameLocal(component) + "_Executor";
}


void
GeneratorServantC::genComponentServant(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		genComponentServant(base);
	}

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
		out << "// not implemented yet, please report : 274772\n";
		out << "throw CORBA::NO_IMPLEMENT();\n";
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
	if(!CORBA::is_nil(base))
	{ 
		genContextServant(base);
	}

	// uses ports
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::UsesDef_var a_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
		std::string interface_name = mapFullName(a_uses->interface_type());
		
		// get_connection_...
		out << interface_name << "_ptr\n";
		out << class_name_ << "::get_connection_" << a_uses->name() << "()\n{\n";
		out.indent();
		out << "Components::ConnectedDescriptions_var connections;\n";
		out << "connections = ccm_object_executor_->get_connections(\"";
		out << a_uses->name() << "\");\n\n";
		out << "if (! connections->length())\n{\n";
		out.indent();
		out << "return " << interface_name << "::_nil();\n";
		out.unindent();
		out << "}\n\n";
		out << interface_name << "_var use = ";
		out << interface_name << "::_narrow (connections[0]->objref());\n\n";
		out << "return use._retn();\n";
		out.unindent();
		out << "}\n\n\n";
	}

	// emits ports
	contained_seq = component->contents(CORBA__::dk_Emits, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++) 
	{
		IR__::EmitsDef_var a_emits = IR__::EmitsDef::_narrow(((*contained_seq)[i]));
		std::string event_name = mapFullName(a_emits->event());
		
		// push_...
		out << "void\n";
		out << class_name_ << "::push_" << a_emits->name() << "(" << event_name << "* ev)\n{\n";
		out.indent();
		out << event_name << "Consumer_var consumer = " << event_name;
		out << "Consumer::_narrow(ccm_object_executor_->get_consumer_for_emitter(\"";
		out << a_emits->name() << "\"));\n\n";
		out << "if (! CORBA::is_nil (consumer))\n{\n";
		out.indent();
		out << "try\n{\n";
		out.indent();
		out << "consumer->push_" << mapName(a_emits->event()) << "(ev);\n";
		out.unindent();
		out << "}\n";
		out << "catch (CORBA::SystemException& ex)\n{\n";
		out.indent();
		out << "std::cerr << \"exception when pushing event : \" << ex << std::endl;\n";
		out.unindent();
		out << "}\n";
		out.unindent();
		out << "}\n";
		out.unindent();
		out << "}\n\n\n";
	}

	// publishes ports
	contained_seq = component->contents(CORBA__::dk_Publishes, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++) 
	{
		IR__::PublishesDef_var a_publishes = IR__::PublishesDef::_narrow(((*contained_seq)[i]));
		std::string event_name = mapFullName(a_publishes->event());
		
		// push_...
		out << "void\n";
		out << class_name_ << "::push_" << a_publishes->name() << "(" << mapFullName(a_publishes->event());
		out << "* ev)\n{\n";
		out.indent();
		out << "const Qedo::SubscribedConsumerVector& consumers = "; 
		out << "ccm_object_executor_->get_consumers_for_publisher (\"" << a_publishes->name() << "\");\n\n";
		out << "for (int i = consumers.size(); i; i--)\n{\n";
		out.indent();
		out << event_name << "Consumer_var consumer = ";
		out << event_name << "Consumer::_narrow (consumers[i-1].consumer());\n\n";
		out << "if (! CORBA::is_nil (consumer))\n{\n";
		out.indent();
		out << "consumer->push_" << mapName(a_publishes->event()) << "(ev);\n";
		out.unindent();
		out << "}\n";
		out.unindent();	
		out << "}\n";
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
	out << mapFullName(composition_->ccm_component()) << "_ptr\n";
	out << class_name_ << "::create()\n";
	out << "throw(CORBA::SystemException, Components::CreateFailure)\n{\n";
	out.indent();
	out << "DEBUG_OUT (\"Home_servant: create() called\");\n\n";
	out << mapFullNameLocal(home) << "_ptr home_executor = dynamic_cast <";
	out << mapFullNameLocal(home) << "_ptr> (home_executor_.in());\n";
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
	out << mapFullNameLocal(home->managed_component()) << "_Context_var new_context = new ";
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
	out << mapFullName(home->managed_component()) << "_var servant = ";
	out << mapFullName(home->managed_component()) << "::_narrow (component_instance.component_ref());\n\n";
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
	if(base)
	{ 
		genFacetRegistration(base);
	}

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
	if(base)
	{ 
		genReceptacleRegistration(base);
	}

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
	if(base)
	{ 
		genEmitterRegistration(base);
	}

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
	if(base)
	{ 
		genPublisherRegistration(base);
	}

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
	if(base)
	{ 
		genConsumerRegistration(base);
	}

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
	if(base)
	{ 
		genHomeServant(base);
	}
	
	home_ = IR__::HomeDef::_duplicate(home);
	std::string home_name = mapFullNameLocal(home);

	// attributes
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Attribute, false);
	CORBA::ULong len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(((*contained_seq)[i]));
		std::string attribute_name = mapName(attribute);
		
		// not read only
		if(attribute->mode() == IR__::ATTR_NORMAL)
		{
			out << "void" << "\n";
			out << class_name_ << "::" << attribute_name << "(";
			out << map_in_parameter_type(attribute->type_def()) << " param)\n";
			out << "throw(CORBA::SystemException";
			handleException(attribute);
			out << ")\n{\n";
			out.indent();
			out << home_name << "_ptr home_executor = dynamic_cast <";
			out << home_name << "_ptr> (home_executor_.in());\n";
			out << "if (! home_executor)\n{\n";
			out.indent();
			out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
			out << "throw Components::CreateFailure();\n";
			out.unindent();
			out << "}\n\n";
			out << "home_executor->" << attribute_name << "(param);\n";
			out.unindent();
			out << "}\n\n\n";
		}

		out << map_return_type(attribute->type_def()) << "\n";
		out << class_name_ << "::" << attribute_name << "()\n";
		out << "throw(CORBA::SystemException";
		handleException(attribute);
		out << ")\n{\n";
		out.indent();
		out << home_name << "_ptr home_executor = dynamic_cast <";
		out << home_name << "_ptr> (home_executor_.in());\n";
		out << "if (! home_executor)\n{\n";
		out.indent();
		out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
		out << "throw Components::CreateFailure();\n";
		out.unindent();
		out << "}\n\n";
		out << "return home_executor->" << attribute_name << "();\n";
		out.unindent();
		out << "}\n\n\n";
	}

	// operations
	contained_seq = home->contents(CORBA__::dk_Operation, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::OperationDef_var operation = IR__::OperationDef::_narrow(((*contained_seq)[i]));
		std::string operation_name = mapName(operation);

		bool is_void = false;
		if(operation->result_def()->type()->kind() == CORBA::tk_void) { is_void = true; }

		out << map_return_type(operation->result_def()) << "\n";
		out << class_name_ << "::" << operation_name << "(";
		IR__::ParDescriptionSeq* pards = operation->params();
		CORBA::ULong len = pards->length();
		for(ii = len; ii > 0; ii--)
		{
			if(ii < len) { out << ", "; }
			IR__::ParameterDescription pardescr = (*pards)[ii - 1];
			out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
		}
		out << ")\n";
		out << "throw(CORBA::SystemException";
		handleException(operation);
		out << ")\n{\n";
		out.indent();
		out << home_name << "_ptr home_executor = dynamic_cast <";
		out << home_name << "_ptr> (home_executor_.in());\n";
		out << "if (! home_executor)\n{\n";
		out.indent();
		out << "NORMAL_ERR (\"Home_servant: Cannot cast my executor\");\n";
		out << "throw Components::CreateFailure();\n";
		out.unindent();
		out << "}\n\n";
		if(!is_void) { out << "return "; }
		out << "home_executor->" << operation_name << "(";
		for(ii = len; ii > 0; ii--)
		{
			if(ii < len) { out << ", "; }
			IR__::ParameterDescription pardescr = (*pards)[ii - 1];
			out << mapName(string(pardescr.name));
		}
		out << ");\n";
		out.unindent();
		out << "}\n\n\n";
	}

	handleFactory(home);
	handleFinder(home);
}


} //