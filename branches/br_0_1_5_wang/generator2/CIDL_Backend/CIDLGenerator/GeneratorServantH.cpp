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
GeneratorServantH::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	//
	// open file
	//
	std::string header_name = file_prefix_ + "_SERVANT";
	std::string filename = header_name + ".h";
	out.open(filename.c_str());
	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#ifndef _" << header_name << "_H_\n";
	out << "#define _" << header_name << "_H_\n\n\n";
	out << "#include <CORBA.h>\n";
	out << "#include <sstream>\n";
	out << "#include \"" << file_prefix_ << "_LOCAL_skel.h\"\n";
	out << "#include \"SessionContext.h\"\n";
	out << "#include \"EntityContext.h\"\n";
	out << "#include \"ExtensionContext.h\"\n";
	out << "#include \"ServantBase.h\"\n";
	out << "#ifndef _QEDO_NO_STREAMS\n";
	out << "#include \"PrimaryStreamServant.h\"\n";
	out << "#include \"SinkStreamPortServant.h\"\n";
	out << "#endif\n";
	out << "#ifndef _QEDO_NO_QOS\n";
	out << "#include \"ExtensionHomeServant.h\"\n";
	out << "#endif\n";
	out << "#include \"SessionHomeServant.h\"\n";
	out << "#include \"EntityHomeServant.h\"\n";
	out << "#include \"Connector.h\"\n";
	out << "#include \"Catalog.h\"\n\n";
	out << "using namespace Qedo;\n\n";

	//
	// dynamic library identifier
	//
	out << "\n//\n// dynamic library identifier\n//\n";
	out << "extern \"C\" {\n";
	out << "#ifdef _WIN32\n";
	out << "__declspec(dllexport)\n";
	out << "#endif\n";
	out << "void set_library_id( CORBA::Long id );\n";
	out << "CORBA::Long get_library_id();\n";
	out << "}\n\n";

	doGenerate();

	//
	// close file
	//
	out << "#endif\n";
	out.close();
}
	

void
GeneratorServantH::check_for_generation(IR__::Contained_ptr item)
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

		// homes
		contained_seq = a_module->contents(CORBA__::dk_Home, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// compositions
		contained_seq = repository_->contents(CORBA__::dk_Composition, true);
		len = contained_seq->length();
		CIDL::CompositionDef_var a_composition;
		for(i = 0; i < len; i++)
		{
			a_composition = CIDL::CompositionDef::_narrow((*contained_seq)[i]);
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

		// home
		check_for_generation(a_composition->ccm_home());
		insert_to_generate(item);
		break; }
	case CORBA__::dk_Home : {
		IR__::HomeDef_var a_home = IR__::HomeDef::_narrow(item);
		
		// insert this interface in generation list
		this->insert_to_generate(item);

		// managed component
		IR__::ComponentDef_var a_component = a_home->managed_component();
		this->check_for_generation(a_component);

		break; }
	case CORBA__::dk_Component : {
		IR__::ComponentDef_var a_component = IR__::ComponentDef::_narrow(item);

		/*// provided interfaces
		IR__::ProvidesDefSeq_var provides_seq = a_component->provides_interfaces();
		len = provides_seq->length();
		for(i = 0; i < len; i++) {
			// insert the interface in generation list
			this->insert_to_generate((*provides_seq)[i]);
		}

		// consumed events
		IR__::ConsumesDefSeq_var consumes_seq = a_component->consumes_events();
		len = consumes_seq->length();
		for(i = 0; i < len; i++) {
			// insert the event in generation list
			this->insert_to_generate((*consumes_seq)[i]);
		}*/

		// insert this interface in generation list
		this->insert_to_generate(item);

		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
};


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
	genOperation(factory, component_);
}


void
GeneratorServantH::doFinder(IR__::FinderDef_ptr finder)
{
	genOperation(finder, component_);
}


void
GeneratorServantH::doInterface(IR__::InterfaceDef_ptr intf)
{
	// base interfaces
	IR__::InterfaceDefSeq_var base_seq = intf->base_interfaces();
	CORBA::ULong i;
	for( i= 0; i < base_seq->length(); i++)
	{
		doInterface((*base_seq)[i]);
	}

	handleAttribute(intf);
	handleOperation(intf);
}

void 
GeneratorServantH::doComposition(CIDL::CompositionDef_ptr composition)
{
	//
	// determine the componentDef and HomeDef
	//
	component_ = composition->ccm_component();
	IR__::HomeDef_var home = composition->ccm_home();

	//
	// determine lifecycle
	//
	CIDL::LifecycleCategory lc = composition->lifecycle();

	//
	// generate home
	//

	// achtung: wenn kein modul, sollte vielleicht Servant_ der prefix f�r alle servants sein?
	open_module(out, component_, "SERVANT_");
	out << "\n\n";

	genHomePersistence(home, lc);
	genHomeServantBegin(home, lc);
	genHomeServant(home, lc);
	
	out.unindent();
	out << "};\n\n\n";

	close_module(out, component_);

	//
	// entry point
	//
	out << "\n//\n// entry point\n//\n";
	out << "extern \"C\" {\n";
	out << "#ifdef _WIN32\n";
	out << "__declspec(dllexport)\n";
	out << "#else\n";
	out << "#endif\n";
	out << "Qedo::HomeServantBase* create_" << home->name() << "S(void);\n";
	out << "}\n\n";

	//
	// generate component
	//
	open_module(out, component_, "SERVANT_");
	out << "\n\n";

	genContextServant(component_, lc);
	genComponentPersistence(component_, lc);
	genComponentServant(component_, lc);
	
	close_module(out, component_);

}

void
GeneratorServantH::doComponent(IR__::ComponentDef_ptr component)
{
	/*
	// achtung: wenn kein modul, sollte vielleicht Servant_ der prefix f�r alle servants sein?
	open_module(out, component, "SERVANT_");
	out << "\n\n";

	genContextServant(component);
	genComponentServant(component);

	close_module(out, component);
	*/
}


void
GeneratorServantH::doProvides(IR__::ProvidesDef_ptr provides, IR__::ComponentDef_ptr component)
{

	// provide_...
	out << mapFullName_(provides->interface_type()) << "_ptr provide_" << provides->name() << "()\n";
	out << "    throw (CORBA::SystemException);\n\n";
}


void 
GeneratorServantH::doUses(IR__::UsesDef_ptr uses, IR__::ComponentDef_ptr component)
{

	out << "\n//\n// " << uses->id() << "\n//\n";
	std::string interface_name = mapFullName_(uses->interface_type());

	//
	// multiple
	//
	if(uses->is_multiple())
	{
		// connect_...
		out << "Components::Cookie* " << "connect_" << uses->name() << "(" << interface_name << "_ptr conx)\n";
		out << "	throw (Components::ExceededConnectionLimit, Components::InvalidConnection, CORBA::SystemException);\n";
			
		// disconnect_...
		out << interface_name << "_ptr disconnect_" << uses->name() << "(Components::Cookie* ck)\n";
		out << "    throw (Components::InvalidConnection, CORBA::SystemException);\n";

		// get_connections_...
		out << mapFullName(component_) << "::" << uses->name() << "Connections* ";
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
GeneratorServantH::doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component)
{
};

void 
GeneratorServantH::doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component)
{
};


void 
GeneratorServantH::doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component)
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
GeneratorServantH::doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component)
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
GeneratorServantH::doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component)
{

	out << "\n//\n// " << consumes->id() << "\n//\n";
	
	// get_consumer_...
	out << mapFullName(consumes->event()) << "Consumer* get_consumer_" << consumes->name();
    out << "() throw(CORBA::SystemException);\n";
}


void
GeneratorServantH::doHome(IR__::HomeDef_ptr home)
{
	/*
	component_ = IR__::ComponentDef::_duplicate(home->managed_component());

	// achtung: wenn kein modul, sollte vielleicht Servant_ der prefix f�r alle servants sein?
	open_module(out, component_, "SERVANT_");
	out << "\n\n";

	genHomeServantBegin(home);
	genHomeServant(home);
	out.unindent();
	out << "};\n\n\n";

	close_module(out, component_);

	//
	// entry point
	//
	out << "\n//\n// entry point\n//\n";
	out << "extern \"C\" {\n";
	out << "#ifdef _WIN32\n";
	out << "__declspec(dllexport)\n";
	out << "#else\n";
	out << "#endif\n";
	out << "Qedo::HomeServantBase* create_" << home->name() << "S(void);\n";
	out << "}\n\n";
	*/
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
	CORBA::ULong i;
	for( i= pards->length(); i > 0; i--)
	{
		if(i < pards->length()) { out << ", "; }
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		if (pardescr.mode == IR__::PARAM_IN) {
			out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_OUT) {
			out << map_out_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		};
		if (pardescr.mode == IR__::PARAM_INOUT) {
			out << map_inout_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		};

	};

	out << ")\n";
	out.indent();
	out << "throw(CORBA::SystemException";
	handleException(operation);
	out << ");\n";
	out.unindent();
}

void
GeneratorServantH::genPersistentOperation(IR__::OperationDef_ptr operation, IR__::ComponentDef_ptr component, bool isFinder)
{
	std::string strDummy = "";
	out << component->name() << "Persistence* " << mapName(operation) << "(";

	//
	// parameters
	//
	strDummy = mapName(operation) + component->name();
	int iLength = strDummy.length() + 14;
	strDummy = "";
	strDummy.append(iLength, ' ');

	if(!isFinder)
	{
		out << "Pid* pid,\n";
		out << strDummy;
		out << "ShortPid* shortPid,\n";
		out << strDummy;
	}
	
	IR__::ParDescriptionSeq* pards = operation->params();
	for( CORBA::ULong i=pards->length(); i > 0; i--)
	{
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		if (pardescr.mode == IR__::PARAM_IN) {
			out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		}
		if (pardescr.mode == IR__::PARAM_OUT) {
			out << map_out_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		}
		if (pardescr.mode == IR__::PARAM_INOUT) {
			out << map_inout_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
		}
		if( (i-1)!=0 ) out << ",\n" << strDummy;
	}

	if(isFinder)
	{
		out << ")\n";
		out.indent();
		out << "throw(CosPersistentState::NotFound);\n";
		out.unindent();
	}
	else
		out << ");\n";
}

void
GeneratorServantH::genFacetServants(IR__::ComponentDef_ptr component)
{
	//
	// handle base component
	//
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		genFacetServants(base);
	}

	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	CORBA::ULong i;
	for( i= 0; i < contained_seq->length(); i++)
	{
		IR__::ProvidesDef_var provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		
		//
		// servant for facet
		//
		out << "\n//\n// servant for facet " << provides->name() << "\n//\n";
		std::string class_name = provides->name();
		out << "class " << class_name;
		out.indent();
		IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow(provides->interface_type());
		if( !CORBA::is_nil(intf) )
		{
			out << " : public " << mapFullNamePOA(intf) << "\n";
		}
		else
		{
			out << "//\n// for CORBA::Object no servant can be generated!\n";
			out << "// please do manually\n//\n";
			out << " : public ???\n";
		}
		out << ", public Qedo::ServantBase\n";
		out.unindent();
		out << "{\n\n";
		out << "public:\n\n";
		out.indent();
		out << class_name << "();\n";
		out << "~" << class_name << "();\n";
		if( !CORBA::is_nil(intf) )
		{
			doInterface(intf);
		}

		//
		// servantfactory for facet
		//
		out << "\n//\n// servantfactory for facet " << provides->name() << "\n//\n";
		out << "class ServantFactory : public Qedo::ServantFactory\n{\n";
		out << "public:\n";
		out.indent();
		out << "Qedo::ServantBase* create_servant() { return new " << class_name << "(); }\n";
		out.unindent();
		out << "};\n";
		out << "static class Qedo::ServantFactoryCleaner cleaner_;\n\n";

		out.unindent();
		out << "};\n\n\n";
	}
}

void
GeneratorServantH::genSinkServants(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		genSinkServants(base);
	}

	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Sink, false);
	CORBA::ULong i;
	for( i= 0; i < contained_seq->length(); i++)
	{
		IR__::SinkDef_var sink = IR__::SinkDef::_narrow(((*contained_seq)[i]));
		std::string stream_type_name = mapFullName(sink->stream_type());

		//
		// servant for sink
		//
		std::string sink_name = sink->name();
		out << "\n//\n// servant for sink " << sink_name << "\n//\n";
		out << "class " << sink_name << " : public virtual Qedo::SinkStreamPortServant\n";
		out << "{\n";
		out << "public:\n";	out.indent();
		out << sink_name << "();\n";
		out << "virtual ~" << sink_name << "();\n\n";
		out << "//\n// IDL:omg.org/StreamComponents/SinkStreamPort/begin_stream:1.0\n//\n";
		out << "void begin_stream (const char*, const Components::ConfigValues&)\n"; out.indent();
		out << "throw (StreamComponents::UnsupportedStreamtype,\n"; out.indent();
		out << "StreamComponents::DuplicateStream,\n";
		out << "CORBA::SystemException);\n\n"; out.unindent(); out.unindent();

		out << "//\n// IDL:omg.org/StreamComponents/SinkStreamPort/end_stream:1.0\n//\n";
		out << "void end_stream()\n"; out.indent();
		out << "throw (StreamComponents::NoStream,\n"; out.indent();
		out << "CORBA::SystemException);\n\n"; out.unindent(); out.unindent();

		out << "//\n// servant factory for SinkStreamPort " << sink_name << "\n//\n";
		out << "class ServantFactory : public Qedo::ServantFactory\n";
		out << "{\n";
		out << "public:\n"; out.indent();
		out << "Qedo::ServantBase* create_servant() { return new " << sink_name << "(); }\n"; out.unindent();
		out << "};\n";
		out << "static class Qedo::ServantFactoryCleaner cleaner_;\n\n"; out.unindent();
		out << "};\n\n";

		out << "//\n// dispatcher for sink " << sink_name << "\n//\n";
		out << "class " << sink_name << "_dispatcher : public Qedo::StreamDataDispatcher\n";
		out << "{\n";
		out << "private:\n"; out.indent();
		out << mapFullName (IR__::Contained::_narrow(component->defined_in()));
		out << "::CCM_" << component->name() << "_" << sink_name << "_Sink_var the_sink_;\n\n"; out.unindent();
		out << "public:\n"; out.indent();
		out << sink_name << "_dispatcher (Components::ExecutorLocator_ptr);\n";
		out << "virtual ~" << sink_name << "_dispatcher();\n\n";
		out << "void begin_stream (const char*, const Components::ConfigValues&);\n";
		out << "void end_stream();\n";
		out << "void failed_stream();\n";
		out << "void receive_stream (StreamComponents::StreamingBuffer_ptr);\n"; out.unindent();
		out << "};\n\n";

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
	CORBA::ULong i;
	for( i= 0; i < len; i++)
	{
		IR__::ConsumesDef_var consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
		std::string class_name = consumes->name();
		std::string full_event_name = mapFullName(consumes->event());

		//
		// servant for consumer
		//
		out << "\n//\n// servant for consumer " << consumes->name() << "\n//\n";
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

		//
		// servantfactory for consumer
		//
		out << "\n//\n// servantfactory for consumer " << consumes->name() << "\n//\n";
		out << "class ServantFactory : public Qedo::ServantFactory\n{\n";
		out << "public:\n";
		out.indent();
		out << "Qedo::ServantBase* create_servant() { return new " << class_name << "(); }\n";
		out.unindent();
		out << "};\n";
		out << "static class Qedo::ServantFactoryCleaner cleaner_;\n\n";

		out.unindent();
		out << "};\n\n\n";
	}
}


void
GeneratorServantH::genComponentServant(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc)
{
	// TODO if not defined in module, use prefix SERVANT_
	std::string class_name = component->name();

	//
	// servant for component
	//
	out << "//\n// servant for component " << class_name << "\n//\n";
	out << "class " << class_name << "\n";
	out.indent();
	out << ": public " << mapFullNamePOA(component) << "\n";

	// Test for stream features
	IR__::SourceDefSeq_var sources_seq = component->sources();
	IR__::SinkDefSeq_var sinks_seq = component->sinks();
	if (sources_seq->length() || sinks_seq->length())
		out << ", public Qedo::PrimaryStreamServant\n";
	else
		out << ", public Qedo::PrimaryServant\n";

	out.unindent();
	out << "{\n\n";
	out << "public:\n\n";
	out.indent();
	out << class_name << "();\n";
	out << "~" << class_name << "();\n";

	//
	// servantfactory for component
	//
	out << "\n//\n// servantfactory for component " << class_name << "\n//\n";
	out << "class ServantFactory : public Qedo::ServantFactory\n{\n";
	out << "public:\n";
	out.indent();
	out << "Qedo::ServantBase* create_servant() { return new " << class_name << "(); }\n";
	out.unindent();
	out << "};\n";
	out << "static class Qedo::ServantFactoryCleaner cleaner_;\n\n";

	genFacetServants(component);
	genSinkServants(component);
	genConsumerServants(component);
	genComponentServantBody(component,lc);
	out.unindent();
	out << "};\n\n\n";
}


void
GeneratorServantH::genComponentServantBody(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc)
{
	//handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		genComponentServantBody(base, lc);
	}

	handleAttribute(component);
	handleSupportedInterface(component);
	handleProvides(component);
	handleUses(component);
	handleEmits(component);
	handlePublishes(component);
	if(component->contents(CORBA__::dk_Consumes, false)->length())
	{
		out << "\n//\n// IDL:Components/EventConsumerBase/push_event:1.0\n//\n";
		out << "virtual void push_event (Components::EventBase* ev) throw (CORBA::SystemException);\n";
		handleConsumes(component);
	}
	handleSink(component);
	handleSource(component);
}

void
GeneratorServantH::genMemberVariable(IR__::ComponentDef_ptr component)
{
	IR__::AttributeDefSeq state_members;
	component->get_state_members(state_members, CORBA__::dk_Variable);
	CORBA::ULong ulLen = state_members.length();
	
	out << "private:\n\n";
	out.indent();

	for(CORBA::ULong i=0; i<ulLen; i++)
	{
		IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(state_members[i]);
		std::string attribute_name = mapName(attribute);
		
		if( strcmp("char*", (const char*)(map_attribute_type(attribute->type_def())))==0 )
			out << "std::string ";
		else
            out << map_attribute_type(attribute->type_def()) << " ";
		out << attribute_name << "_;\n";
	}

	out.unindent();
}

void
GeneratorServantH::genComponentPersistence(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc)
{
	if( lc!=CIDL::lc_Entity && lc!=CIDL::lc_Process )
		return;

	// handle base component
	IR__::ComponentDef_var base_component = component->base_component();
	if(base_component)
		genComponentPersistence(base_component, lc);

	out << "//\n// component persistence\n//\n";
	out << "class " << component->name() << "Persistence\n";
	out.indent();
	if(base_component)
		out << ": public virtual " << base_component->name() << "Persistence\n";
	else
		out << ": public virtual StorageObjectImpl\n";
	out.unindent();
	out << "{\n\npublic:\n\n";
	out.indent();
    out << component->name() << "Persistence();\n";
	out << "~" << component->name() << "Persistence();\n";
	
	handleAttribute(component);

	out << "\nvoid setValue(std::map<std::string, CORBA::Any> valueMap);\n\n";
	
	//generate _duplicate and _downcast operation
	//genDuplAndDown(strClassName);
	out.unindent();

	genMemberVariable(component);

	out << "};\n\n";

	genFactoryTemplate(false);
	out << "typedef ObjectFactory<" << component->name() << "Persistence> " << component->name() << "PersistenceFactory;\n\n";
}

void
GeneratorServantH::genContextServant(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc)
{
	std::string class_name = string(component->name()) + "_Context_callback";

	out << "//\n// servant for context of component " << component->name() << "\n//\n";
	out << "class " << class_name << "\n";
	out.indent();
	out << ": public " << mapFullNameLocal(component) << "_ContextImpl\n";
	switch (lc) {
	case (CIDL::lc_Session) :
		{
            out << ", public Qedo::SessionContext\n";
		    break;
        }
	case (CIDL::lc_Entity) :
        {
            out << ", public Qedo::EntityContext\n";
		    break;
        }
	case (CIDL::lc_Extension) :
        {
		    out << ", public Qedo::ExtensionContext\n";
		    break;
        }
	default :
        {
		    out << "// not supported lifecycle\n";
        }
	}

	out.unindent();
	out << "{\n\n";
	out << "public:\n\n";
	out.indent();
    out << class_name << "();\n";
	out << "~" << class_name << "();\n";

	genContextServantBody(component);
	out.unindent();
	out << "};\n\n\n";
}


void
GeneratorServantH::genContextServantBody(IR__::ComponentDef_ptr component)
{
	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		genContextServantBody(base);
	}

	// uses ports
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	CORBA::ULong i;
	for( i= 0; i < len; i++)
	{
		IR__::UsesDef_var a_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
		out << "\n";
		
		//
		// multiple
		//
		if(a_uses->is_multiple())
		{
			out << mapFullName(component) << "::" << a_uses->name() << "Connections* ";
			out << "get_connections_" << a_uses->name() << "()\n";
			out << "	throw (CORBA::SystemException);\n";
		}
		//
		// not multiple
		//
		else
		{
			out << mapFullName_(a_uses->interface_type()) << "_ptr get_connection_" << a_uses->name() << "();\n";
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

	// source ports
	contained_seq = component->contents(CORBA__::dk_Source, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++) 
	{
		IR__::SourceDef_var a_source = IR__::SourceDef::_narrow(((*contained_seq)[i]));
		out << "\n";
		out << "void begin_stream_" << a_source->name() << " (const char* repos_id,\n";
		out.indent(); out.indent();
		out << "const ::Components::ConfigValues& meta_data)\n";
		out.unindent();
		out << "throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream);\n\n";
		out.unindent();

		out << "void end_stream_" << a_source->name() << "()\n";
		out.indent();
		out << "throw (StreamComponents::NoStream);\n\n";
		out.unindent();

		out << "void send_stream_" << a_source->name() << " (StreamComponents::StreamingBuffer_ptr buffer)\n";
		out.indent();
		out << "throw (StreamComponents::NoStream);\n\n";
		out.unindent();
	}
}


void
GeneratorServantH::genHomeServantBegin(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc)
{
	std::string class_name = string(home->name()) + "_servant";

	out << "\n//\n// servant for home " << home->name() << "\n//\n";
	out << "class " << class_name << "\n";
	out.indent();
	out << ": public " << mapFullNamePOA(home) << "\n";
	switch (lc) {
	case (CIDL::lc_Session) :
		{
		    out << ", public Qedo::SessionHomeServant\n";
		    break;
        }
	case (CIDL::lc_Entity) :
        {
		    out << ", public Qedo::EntityHomeServant\n";
		    break;
        }
	case (CIDL::lc_Extension) :
        {
		    out << ",public Qedo::ExtensionHomeServant\n";
		    break;
        }
	default:
        {
		    out << "// not supported lifecycle\n";
        }
	}

	out.unindent();
	out << "{\n\n";
	out << "public:\n\n";
	out.indent();
    out << class_name << "();\n";
    out << "~" << class_name << "();\n\n";

	switch (lc) {
	case (CIDL::lc_Session) :
		out << mapFullName(component_) << "_ptr create()\n"; 
		out << "	throw(CORBA::SystemException, Components::CreateFailure);\n\n";
		out << "Components::CCMObject_ptr create_component()\n";
		out << "	throw(CORBA::SystemException,Components::CreateFailure);\n\n";
		break;
	case (CIDL::lc_Entity) :
		out << mapFullName(component_) << "_ptr create(" << mapFullNamePK(home->primary_key()) << "* pkey)\n"; 
		out << "	throw(CORBA::SystemException, Components::CreateFailure, Components::DuplicateKeyValue, Components::InvalidKey);\n\n";

		out << mapFullName(component_) << "_ptr find_by_primary_key(" << mapFullNamePK(home->primary_key()) << "* pkey)\n"; 
		out << "	throw(CORBA::SystemException, Components::FinderFailure, Components::UnknownKeyValue, Components::InvalidKey);\n\n";

		out << "void remove(" << mapFullNamePK(home->primary_key()) << "* pkey)\n"; 
		out << "	throw(CORBA::SystemException, Components::RemoveFailure, Components::UnknownKeyValue, Components::InvalidKey);\n\n";

		out << mapFullNamePK(home->primary_key()) << "* get_primary_key(" << mapFullName(component_) << "_ptr comp)\n"; 
		out << "	throw(CORBA::SystemException);\n\n";

		break;
	default:
		out << "// not supported lifecycle\n";
	}

	if(lc==CIDL::lc_Session)
	{
		out << "// COACH extension\n";
		out << "Components::CCMObject_ptr create_component_with_config(const Components::ConfigValues& config)\n";
		out << "	throw(CORBA::SystemException, Components::CreateFailure);\n";
	}
}


void
GeneratorServantH::genHomeServant(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc)
{
	// handle base home
	IR__::HomeDef_var base = home->base_home();
	if(base)
	{ 
		genHomeServant(base, lc);
	}

	handleAttribute(home);
	handleOperation(home);
	handleFactory(home);
	handleFinder(home);

	//
	// supported interfaces
	//
	IR__::InterfaceDefSeq_var supp_intfs = home -> supported_interfaces();
	for(CORBA::ULong i = 0; i < supp_intfs->length(); i++) {
		handleAttribute((*supp_intfs)[i]);
		handleOperation((*supp_intfs)[i]);
	};

	if(lc==CIDL::lc_Entity || lc==CIDL::lc_Process)
	{
		out << "\nvoid get_table_info(std::map<std::string, std::string>& mTables);\n\n";
		out << "void init_datastore(Connector_ptr pConn, Sessio_ptr pSession);\n";
		out.unindent();
		out << "\nprivate:\n\n";
		out.indent();
		out << "bool compare_primarykey(" << mapFullNamePK(home->primary_key()) << "* pk_a, " << mapFullNamePK(home->primary_key()) << "* pk_b);\n\n";
		out << "Sessio_var pSession_;\n";
		out << home->name() << "Persistence* " << "pCcm" << home->name() << "_;\n\n";
	}
}

void
GeneratorServantH::genFactoryTemplate(bool isHome)
{
	std::string strPre = "";
	(isHome) ? strPre = "HomeFactory" : strPre = "ObjectFactory";

	out << "template <class T>\n";
	out << "#ifdef ORBACUS_ORB\n";
	out << "class " << strPre << " : public OBNative_CosPersistentState::Storage" << strPre << "_pre\n";
	out << "#endif\n";
	out << "#ifdef MICO_ORB\n";
	out << "class " << strPre << " : public CosPersistentState::Storage" << strPre << "_pre\n";
	out << "#endif\n";
	out << "{\n";
	out.indent();
	out << "public:\n";
	out.indent();
	out << strPre << "() : refcount_(1) {};\n";
	out << "virtual ~" << strPre << "() {};\n";
	out << "virtual T* create() { return new T; };\n";
	out << "virtual void _add_ref() { refcount_++; };\n";
	out << "virtual void _remove_ref() { if( --refcount_==0 ) delete this; };\n";
	out.unindent();
	out << "\nprivate:\n";
	out.indent();
	out << "CORBA::ULong refcount_;\n";
	out.unindent();
	out.unindent();
	out << "};\n\n";
}

void
GeneratorServantH::genHomePersistence(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc)
{
	if( lc!=CIDL::lc_Entity && lc!=CIDL::lc_Process )
		return;

	// handle base home
	IR__::HomeDef_var base_home = home->base_home();
	if(base_home)
		genHomePersistence(base_home, lc);

	int iLength = 0;
	std::string strDummy = "";
	IR__::AttributeDefSeq state_members;

	out << "//\n// home persistence\n//\n";

	IR__::ComponentDef_var component = home->managed_component();
	out << "class " << component->name() << "Persistence;\n\n";
	out << "class " << home->name() << "Persistence\n";
	out.indent();
	if(base_home)
		out << ": public virtual " << home->name() << "Persistence\n";
	else
		out << ": public virtual StorageHomeBaseImpl\n";
	out.unindent();
	out << "{\n\npublic:\n\n";
	out.indent();
    out << home->name() << "Persistence();\n";
	out << "~" << home->name() << "Persistence();\n\n";

	char* szDisplay = map_psdl_return_type(component, false);
	iLength = strlen(szDisplay) + 10;
	
	out << component->name() << "Persistence* _create(";
	out << "Pid* pid,\n";
	strDummy.append(iLength, ' ');
	out << strDummy.c_str();
	out << "ShortPid* shortPid,\n";
	
	// handel other in-parameters
	component->get_state_members(state_members, CORBA__::dk_Create);
	CORBA::ULong ulLen = state_members.length();
	for(CORBA::ULong i=0; i<ulLen; i++)
	{
		IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(state_members[i]);
		out << strDummy.c_str() << map_in_parameter_type(attribute->type_def()) << " " << mapName(attribute);
		if( (i+1)!=ulLen )
			out << ",\n";
	}
	
	out << ");\n\n";

	// handel factory
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Factory, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FactoryDef_var a_factory = IR__::FactoryDef::_narrow(((*contained_seq)[i]));
		genPersistentOperation(a_factory, component, false);
	}

	out << "\n";

	// handel finder
	contained_seq = home->contents(CORBA__::dk_Finder, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::FinderDef_var a_finder = IR__::FinderDef::_narrow(((*contained_seq)[i]));
		genPersistentOperation(a_finder, component, true);
	}
	
	// generate finder for find_by_primary_key
	out << "\n";
	out << component->name() << "Persistence* find_by_primary_key(" << mapFullNamePK(home->primary_key()) << "* pkey)\n";
	out.indent();
	out << "throw(CosPersistentState::NotFound);\n";
	out.unindent();

	out.unindent();
	out << "};\n\n";

	genFactoryTemplate(true);
	out << "typedef HomeFactory<" << home->name() << "Persistence> " << home->name() << "PersistenceFactory;\n\n";
}

} //
