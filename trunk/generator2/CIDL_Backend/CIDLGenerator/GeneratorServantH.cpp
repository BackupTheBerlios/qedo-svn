#include "GeneratorServantH.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorServantH::GeneratorServantH
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}


GeneratorServantH::~GeneratorServantH
()
{
}


void
GeneratorServantH::generate(string target)
{
	target_ = target;
	doGenerate(target);
}
	

void
GeneratorServantH::doModule(IR__::ModuleDef_ptr module)
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
GeneratorServantH::doAttribute(IR__::AttributeDef_ptr attribute)
{
	out << "\n//\n// " << attribute->id() << "\n//\n";
	std::string attribute_name = mapName(attribute);

	//
	// not read only
	//
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void " << attribute_name << "(";
		out << map_in_parameter_type(attribute->type_def()) << " param)\n";
		out << "	throw(CORBA::SystemException";
		handleException(attribute);
		out << ");\n";
	}

	out << map_return_type(attribute->type_def()) << " " << attribute_name << "()\n";
	out << "	throw(CORBA::SystemException";
	handleException(attribute);
	out << ");\n";
}


void 
GeneratorServantH::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}


void
GeneratorServantH::doOperation(IR__::OperationDef_ptr operation)
{
	genOperation(operation, operation->result_def());
}


void
GeneratorServantH::doFactory(IR__::FactoryDef_ptr factory)
{
	genOperation(factory, composition_->ccm_component());
}


void
GeneratorServantH::doFinder(IR__::FinderDef_ptr finder)
{
	genOperation(finder, composition_->ccm_component());
}


void
GeneratorServantH::doInterface(IR__::InterfaceDef_ptr intf)
{
	// base interfaces
	IR__::InterfaceDefSeq_var base_seq = intf->base_interfaces();
	for(CORBA::ULong i = 0; i < base_seq->length(); i++)
	{
		doInterface((*base_seq)[i]);
	}

	handleAttribute(intf);
	handleOperation(intf);
}


void
GeneratorServantH::doComponent(IR__::ComponentDef_ptr component)
{
	genFacetServants(component);
	genConsumerServants(component);
	genContextServantBegin(component);
	genContextServant(component);

	out.unindent();
	out << "};\n\n\n";

	genComponentServantBegin(component);
	genComponentServant(component);

	out.unindent();
	out << "};\n\n\n";
}


void
GeneratorServantH::doProvides(IR__::ProvidesDef_ptr provides)
{
	out << "\n//\n// " << provides->id() << "\n//\n";

	// provide_...
	out << mapFullName(provides->interface_type()) << "_ptr provide_" << provides->name() << "()\n";
	out << "    throw (CORBA::SystemException);\n\n";
}


void 
GeneratorServantH::doUses(IR__::UsesDef_ptr uses)
{
	out << "\n//\n// " << uses->id() << "\n//\n";
	std::string interface_name = mapFullName(uses->interface_type());

	//
	// multiple
	//
	if(uses->is_multiple() == true)
	{
		// connect_...
		out << "Components::Cookie* " << "connect_" << uses->name() << "(" << interface_name << "_ptr conx)\n";
		out << "	throw (Components::ExceededConnectionLimit, Components::InvalidConnection, CORBA::SystemException);\n";
			
		// disconnect_...
		out << interface_name << "_ptr disconnect_" << uses->name() << "(Components::Cookie* ck)\n";
		out << "    throw (Components::InvalidConnection, CORBA::SystemException);\n";

		// get_connections_...
		out << mapFullName(composition_->ccm_component()) << "::" << uses->name() << "Connections* ";
		out << "get_connections_" << uses->name() << "()\n";
		out << "	throw (CORBA::SystemException);\n";
	}
	//
	// not multiple
	//
	else
	{
		// get_connection_...
		out << interface_name << "_ptr get_connection_" << uses->name() << "()\n";
		out << "	throw (CORBA::SystemException);\n";

		// disconnect_...
		out << interface_name << "_ptr disconnect_" << uses->name() << "()\n";
		out << "	throw (Components::NoConnection, CORBA::SystemException);\n";

		// connect_...
		out << "void connect_" << uses->name() << "(";
		out << interface_name << "_ptr conxn)\n";
		out << "	throw (Components::AlreadyConnected, Components::InvalidConnection, CORBA::SystemException);\n";
	}
}


void 
GeneratorServantH::doEmits(IR__::EmitsDef_ptr emits)
{
	out << "\n//\n// " << emits->id() << "\n//\n";
	std::string event_name = mapFullName(emits->event());
	
	// disconnect_...
	out << event_name << "Consumer* disconnect_" << emits->name() << "()\n";
    out << "	throw (Components::NoConnection, CORBA::SystemException);\n";

	// connect_...
    out << "void connect_" << emits->name() << "(";
	out << event_name << "Consumer* consumer)\n";
    out << "	throw (Components::AlreadyConnected, CORBA::SystemException);\n";
}


void 
GeneratorServantH::doPublishes(IR__::PublishesDef_ptr publishes)
{
	out << "\n//\n// " << publishes->id() << "\n//\n";
	std::string event_name = mapFullName(publishes->event());

	// subscribe_...
	out << "::Components::Cookie* subscribe_" << publishes->name() << "(";
	out << event_name << "Consumer_ptr consumer)\n";
	out << "	throw (Components::ExceededConnectionLimit, CORBA::SystemException);\n";

	// unsubscribe_...
	out << event_name << "Consumer* unsubscribe_" << publishes->name() << "(";
	out << "::Components::Cookie* ck)\n";
	out << "	throw (Components::InvalidConnection, CORBA::SystemException);\n";
}


void
GeneratorServantH::doConsumes(IR__::ConsumesDef_ptr consumes)
{
	out << "\n//\n// " << consumes->id() << "\n//\n";
	
	// get_consumer_...
	out << mapFullName(consumes->event()) << "Consumer* get_consumer_" << consumes->name();
    out << "() throw(CORBA::SystemException);\n";
}


void
GeneratorServantH::doHome(IR__::HomeDef_ptr home)
{
	genHomeServantBegin(home);
	genHomeServant(home);
	
	out.unindent();
	out << "};\n\n\n";
}


void
GeneratorServantH::doComposition(CIDL::CompositionDef_ptr composition)
{
	composition_ = CIDL::CompositionDef::_duplicate(composition);
	filename_ = mapAbsoluteName(composition->ccm_component(), "_");
	filename_.append("_SERVANT");
	string header_name = filename_;
	filename_.append(".h");
	out.open(filename_.c_str());


	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#ifndef _" << header_name << "_H_\n";
	out << "#define _" << header_name << "_H_\n\n\n"; 

	out << "#include <OB/CORBA.h>\n";
	out << "#include \"" << target_ << "_LOCAL_skel.h\"\n";
	out << "#include \"SessionContext.h\"\n";
	out << "#include \"ServantBase.h\"\n";
	out << "#include \"SessionHomeServant.h\"\n\n\n";

	// achtung: wenn kein modul, sollte vielleicht Servant_ der prefix für alle servants sein?
	open_module(out, composition->ccm_component(), "Servants_");
	out << "\n\n";

	doComponent(composition->ccm_component());
	doHome(composition->ccm_home());

	close_module(out, composition->ccm_component());


	//
	// entry point
	//
	out << "\n//\n// entry point\n//\n";
	out << "extern \"C\" {\n";
	out << "#ifdef WIN32\n";
	out << "__declspec(dllexport)\n";
	out << "#else\n";
	out << "#endif\n";
	out << "Qedo::HomeServantBase* create_" << composition->ccm_home()->name() << "S(void);\n";
	out << "}\n\n";


	out << "#endif";
	out.close();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
GeneratorServantH::genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type)
{
	out << "\n//\n// " << operation->id() << "\n//\n";
	out << map_return_type(ret_type) << " " << mapName(operation) << "(";

	//
	// parameters
	//
	IR__::ParDescriptionSeq* pards = operation->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length()) { out << ", "; }
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
	};

	out << ")\n";
	out.indent();
	out << "throw(CORBA::SystemException";
	handleException(operation);
	out << ");\n";
	out.unindent();
}


void
GeneratorServantH::genFacetServants(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		genFacetServants(base);
	}

	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::ProvidesDef_var provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		std::string class_name = std::string(provides->name()) + "_servant";
		out << "class " << class_name;
		out.indent();	
		out << ": public " << mapFullNamePOA(provides->interface_type()) << "\n";
		out << ", public Qedo::ServantBase\n";
		out.unindent();
		out << "{\n\n";
		out << "public:\n\n";
		out.indent();
		out << class_name << "();\n";
		out << "~" << class_name << "();\n";
		doInterface(provides->interface_type());
		out.unindent();
		out << "};\n\n\n";
	}
}


void
GeneratorServantH::genConsumerServants(IR__::ComponentDef_ptr component)
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
		IR__::ConsumesDef_var consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
		std::string class_name = string(consumes->name()) + "_servant";
		std::string full_event_name = mapFullName(consumes->event());

		out << "class " << class_name << "\n";
		out.indent();
		out << ": public " << mapFullNamePOA(consumes->event()) << "Consumer\n";
		out << ", public Qedo::ServantBase\n";
		out.unindent();
		out << "{\n\n";
		out << "public:\n\n";
		out.indent();
		out << class_name << "();\n";
		out << "~" << class_name << "();\n";
		out << "\n//\n// IDL:Components/EventConsumerBase/push_event:1.0\n//\n";
		out << "virtual void push_event (Components::EventBase* ev) throw (CORBA::SystemException);\n";
		out << "virtual void push_" << consumes->event()->name() << "(" << full_event_name << "* ev);\n";
		out.unindent();
		out << "};\n\n\n";
	}
}


void
GeneratorServantH::genComponentServantBegin(IR__::ComponentDef_ptr component)
{
	std::string class_name = string(component->name()) + "_servant";

	out << "class " << class_name << "\n";
	out.indent();
	out << ": public " << mapFullNamePOA(component) << "\n";
	out << ", public Qedo::PrimaryServant \n";
	out.unindent();
	out << "{\n\n";
	out << "public:\n\n";
	out.indent();
	out << class_name << "();\n";
	out << "~" << class_name << "();\n";
}


void
GeneratorServantH::genComponentServant(IR__::ComponentDef_ptr component)
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
		out << "\n// IDL:Components/EventConsumerBase/push_event:1.0\n";
		out << "virtual void push_event (Components::EventBase* ev) throw (CORBA::SystemException);\n";
		handleConsumes(component);
	}
}


void
GeneratorServantH::genContextServantBegin(IR__::ComponentDef_ptr component)
{
	std::string class_name = string(component->name()) + "_Context_callback";

	out << "class " << class_name << "\n";
	out.indent();
	out << ": public " << mapFullNameLocal(component) << "_Context\n";
	out << ", public Qedo::SessionContext\n";
	out.unindent();
	out << "{\n\n";
	out << "public:\n\n";
	out.indent();
    out << class_name << "();\n";
	out << "~" << class_name << "();\n";
}


void
GeneratorServantH::genContextServant(IR__::ComponentDef_ptr component)
{
	// uses ports
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::UsesDef_var a_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
		out << "\n";
		
		//
		// multiple
		//
		if(a_uses->is_multiple() == true)
		{
			out << mapFullName(composition_->ccm_component()) << "::" << a_uses->name() << "Connections* ";
			out << "get_connections_" << a_uses->name() << "()\n";
			out << "	throw (CORBA::SystemException);\n";
		}
		//
		// not multiple
		//
		else
		{
			out << mapFullName(a_uses->interface_type()) << "_ptr get_connection_" << a_uses->name() << "();\n";
		}
	}

	// emits ports
	contained_seq = component->contents(CORBA__::dk_Emits, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++) 
	{
		IR__::EmitsDef_var a_emits = IR__::EmitsDef::_narrow(((*contained_seq)[i]));
		out << "\n";
		out << "void push_" << a_emits->name() << "(" << mapFullName(a_emits->event()) << "* ev);\n";
	}

	// publishes ports
	contained_seq = component->contents(CORBA__::dk_Publishes, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++) 
	{
		IR__::PublishesDef_var a_publishes = IR__::PublishesDef::_narrow(((*contained_seq)[i]));
		out << "\n";
		out << "void push_" << a_publishes->name() << "(" << mapFullName(a_publishes->event()) << "* ev);\n";
	}
}


void
GeneratorServantH::genHomeServantBegin(IR__::HomeDef_ptr home)
{
	std::string class_name = string(home->name()) + "_servant";

	out << "class " << class_name << "\n";
	out.indent();
	out << ": public " << mapFullNamePOA(home) << "\n";
	out << ", public Qedo::SessionHomeServant\n";
	out.unindent();
	out << "{\n\n";
	out << "public:\n\n";
	out.indent();
    out << class_name << "();\n";
    out << "~" << class_name << "();\n\n";
	out << mapFullName(composition_->ccm_component()) << "_ptr create()\n"; 
	out << "	throw(CORBA::SystemException, Components::CreateFailure);\n\n";
	out << "Components::CCMObject_ptr create_component()\n";
	out << "	throw(CORBA::SystemException,Components::CreateFailure);\n";
}


void
GeneratorServantH::genHomeServant(IR__::HomeDef_ptr home)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base)
	{ 
		genHomeServant(base);
	}

	handleAttribute(home);
	handleOperation(home);
	handleFactory(home);
	handleFinder(home);
}


} //