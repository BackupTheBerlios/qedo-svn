#include "GeneratorLIDL.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorLIDL::GeneratorLIDL
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: IDLBase(repository)
{
}


GeneratorLIDL::~GeneratorLIDL
()
{
}


void
GeneratorLIDL::check_for_generation(IR__::Contained_ptr item)
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

IR__::ContainedSeq_var contained_seq;

IR__::ModuleDef_var act_module;
IR__::ComponentDef_var act_component;
IR__::ComponentDef_var base_component;
IR__::HomeDef_var act_home;
IR__::HomeDef_var base_home;

	switch (item->describe()->kind) {
	case CORBA__::dk_Module:
		act_module = IR__::ModuleDef::_narrow(item);

		// modules
		contained_seq = act_module->contents(CORBA__::dk_Module, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// homes
		contained_seq = act_module->contents(CORBA__::dk_Home, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// compositions
		contained_seq = repository_->contents(CORBA__::dk_Composition, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow((*contained_seq)[i]);
			/*IR__::ModuleDef_var other_module = IR__::ModuleDef::_narrow(a_composition->defined_in());
			if (!CORBA::is_nil(other_module))
			{
				if(!strcmp(act_module->id(), other_module->id()))
				{
					check_for_generation(a_composition);
				}
			}*/
			std::string id = a_composition->id();
			std::string::size_type pos = id.find_last_of("/");
			if(pos != std::string::npos) 
			{
				id.replace(pos, std::string::npos, ":1.0");
				if(!id.compare(act_module->id())) 
				{
					check_for_generation(a_composition);

				}
			}
		}

		break;
	case CORBA__::dk_Home:
		act_home = IR__::HomeDef::_narrow(item);
		
		// base home
		base_home = act_home->base_home();
		if (!CORBA::is_nil(base_home)) {
			this->check_for_generation(base_home);
		}

		// managed component
		act_component = act_home->managed_component();
		this->check_for_generation(act_component);

		insert_to_generate(item);
		break;
	case CORBA__::dk_Component: {
		act_component = IR__::ComponentDef::_narrow(item);

		// base component
		base_component = act_component->base_component();
		if ( ! CORBA::is_nil(base_component)) {
			this->check_for_generation(base_component);
		}

		// supported interfaces
		IR__::InterfaceDefSeq_var interf_seq = act_component->supported_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		}

		// provided interfaces
		IR__::ProvidesDefSeq_var provides_seq = act_component->provides_interfaces();
		len = provides_seq->length();
		for(i = 0; i < len; i++)
		{
			IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow((*provides_seq)[i]->interface_type());
			if( !CORBA::is_nil(intf) )
			{
				this->check_for_generation(intf);
			}
		}

		// consumed events
		IR__::ConsumesDefSeq_var consumes_seq = act_component->consumes_events();
		len = consumes_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*consumes_seq)[i]->event());
		}

		this->insert_to_generate(item);
		break; }
	case CORBA__::dk_Value:
	case CORBA__::dk_Interface: {
		this->insert_to_generate(item);
		break; }
	case CORBA__::dk_Composition : {
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(item);

		// home
		check_for_generation(a_composition->ccm_home());

		insert_to_generate(a_composition);

		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
};


void
GeneratorLIDL::doModule(IR__::ModuleDef_ptr module)
{
}


void 
GeneratorLIDL::doInterface(IR__::InterfaceDef_ptr intface)
{
	out << "//\n// " << intface->id() << "\n//\n";
	out << "local interface CCM_" << intface->name() << " : ";
	out << map_absolute_name(intface) << ", ::Components::EnterpriseComponent\n{\n";
	out << "};\n\n";
}


void
GeneratorLIDL::doValue(IR__::ValueDef_ptr value)
{
}

void
GeneratorLIDL::doEvent(IR__::EventDef_ptr event)
{
	out << "//\n// " << event->id() << "\n//\n";
	out << "local interface CCM_" << event->name() << "Consumer : ";
	out << map_absolute_name(event) << "Consumer, ::Components::EnterpriseComponent\n{\n";
	out << "};\n\n";
}

void
GeneratorLIDL::doAttribute(IR__::AttributeDef_ptr attribute)
{
	out << "\n//\n// " << attribute->id() << "\n//\n";

	// attribute mode
	if(attribute->mode() == IR__::ATTR_READONLY)
	{
		out << "readonly ";
	}

	out << "attribute " << tcToName(attribute->type()) << " " << attribute->name();

	// exceptions
	IR__::ExceptionDefSeq_var exception_seq = attribute->get_exceptions();
	CORBA::ULong i;
	for( i= 0; i < exception_seq->length(); i++)
	{
	}

	out << ";\n";
}

void
GeneratorLIDL::doComposition(CIDL::CompositionDef_ptr composition)
{
	//
	// determin the lifecycle
	//
	CIDL::LifecycleCategory lc = composition->lifecycle();

	//
	// detemine the component
	//
	component_ = composition->ccm_component();

/*
	//
	// generate
	//

	open_module(component_);
	//
	// container specific context interface 
	//
	out << "//\n// container interface for the context for " << component_->id() << "\n//\n";
	out << "local interface CCM_" << component_->name() << "_ContextImpl : ";
	out << "CCM_" << component_->name() << "_Context,\n";

	switch(lc) {
	case (CIDL::lc_Session) : 
		{
			out << "::Components::SessionContext";
			break;
		}
	case (CIDL::lc_Extension) :
		{
			out << "::Components::ExtensionContext";
			break;
		}
	default:
		{
			//unsupported lifecycle category
			std::cerr << "unsupported lifecycle category" << std::endl;
		}
	}

	out << "\n{ };\n\n";

	close_module(component_);
	*/
	this -> generate_component(component_, lc);
}

void 
GeneratorLIDL::generate_component(IR__::ComponentDef* a_component, CIDL::LifecycleCategory lc)
 {
	// base component
	IR__::ComponentDef_var base_component = a_component->base_component();
	if ( ! CORBA::is_nil(base_component)) {
		this->generate_component(base_component, lc);

	}
	//
	// generate
	//

	open_module(a_component);
	//
	// container specific context interface 
	//
	out << "//\n// container interface for the context for " << a_component->id() << "\n//\n";
	out << "local interface CCM_" << a_component->name() << "_ContextImpl : ";
	out << "CCM_" << a_component->name() << "_Context,\n";

	switch(lc) {
	case (CIDL::lc_Session) : 
		{
			out << "::Components::SessionContext";
			break;
		}
	case (CIDL::lc_Extension) :
		{
			out << "::Components::ExtensionContext";
			break;
		}
	default:
		{
			//unsupported lifecycle category
			std::cerr << "unsupported lifecycle category" << std::endl;
		}
	}

	out << "\n{ };\n\n";

	close_module(a_component);

}

void
GeneratorLIDL::doComponent(IR__::ComponentDef_ptr component)
{
	
	component_ = IR__::ComponentDef::_duplicate(component);

	handleSink(component);

	//
	// executor
	//
	out << "//\n// executor for " << component->id() << "\n//\n";
	out << "local interface CCM_" << component->name() << "_Executor : ";
	
	// base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{
		out << getLocalName(base) << "_Executor";
	}
	else
	{
		out << "::Components::EnterpriseComponent";
	}

	// supported interfaces
	IR__::InterfaceDefSeq_var supported_seq = component->supported_interfaces();
	CORBA::ULong len = supported_seq->length();
	if(len)
	{
		CORBA::ULong i;
		for( i= 0; i < len; i++)
		{
			out << ", " << map_absolute_name((*supported_seq)[i]);
		}
	}

	// sinks
	IR__::SinkDefSeq_var sink_seq = component->sinks();
	len = sink_seq->length();
	if(len)
	{
		CORBA::ULong i;
		for( i= 0; i < len; i++)
		{
			out << ", CCM_" << component->name() << "_" << (*sink_seq)[i]->name() << "_Sink";
		}
	}


	out << "\n{\n";
	out.indent();

	handleAttribute(component);

	out.unindent();
	out << "};\n\n";

	//
	// context
	//
	out << "//\n// context for " << component->id() << "\n//\n";
	out << "local interface CCM_" << component->name() << "_Context : ";
	
	// base component
	if(!CORBA::is_nil(base))
	{
		out << getLocalName(base) << "_Context";
	}
	else
	{
		out << "::Components::CCMContext";
	}
	out << "\n{\n";
	out.indent();

	handleUses(component);
	handleEmits(component);
	handlePublishes(component);
	handleSource(component);

	out.unindent();
	out << "};\n\n";
}


void
GeneratorLIDL::doHome(IR__::HomeDef_ptr home)
{	
	//
	// implicit home
	//
	out << "//\n// implicit home for " << home->id() << "\n//\n";
	out << "local interface CCM_" << home->name() << "Implicit\n";
	out << "{\n";
	out.indent();
	out << "::Components::EnterpriseComponent create() raises (Components::CreateFailure);\n";
	out.unindent();
	out << "};\n\n";


	//
	// explicit home
	//
	out << "//\n// explicit home for " << home->id() << "\n//\n";
	out << "local interface CCM_" << home->name() << "Explicit : ";
	IR__::HomeDef_var base = home->base_home();
	if(base)
	{
		out << getLocalName(base);
	}
	else
	{
		out << "::Components::HomeExecutorBase";
	}

	// supported interfaces
	IR__::InterfaceDefSeq_var supp_intfs = home -> supported_interfaces();
	for(CORBA::ULong i = 0; i < supp_intfs->length(); i++) {
		out << ", " << map_absolute_name((*supp_intfs)[i]);
	};
	
	out << "\n{\n";
	out.indent();

	managed_component_ = map_absolute_name(home->managed_component());

	handleAttribute(home);
	handleOperation(home);
	handleFactory(home);
	handleFinder(home);

	out.unindent();
	out << "};\n\n";
	

	//
	// home
	//
	out << "//\n// " << home->id() << "\n//\n";
	out << "local interface CCM_" << home->name() << " : CCM_" << home->name() << "Implicit, CCM_";
	out << home->name() << "Explicit\n{\n};\n\n";
}


void
GeneratorLIDL::doOperation(IR__::OperationDef_ptr operation)
{
	out << "\n//\n// " << operation->id() << "\n//\n";

	// operation mode
	if(operation->mode() == IR__::OP_ONEWAY)
	{
		out << "oneway ";
	}
	
	out << tcToName(operation->result()) << " " << operation->name() << "(";

	// parameters
	IR__::ParDescriptionSeq_var para_seq = operation->params();
	CORBA::ULong len = para_seq->length();
	CORBA::ULong i;
	for( i= len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}
		switch((*para_seq)[i - 1].mode)
		{
		case IR__::PARAM_IN :
			out << "in ";
			break;
		case IR__::PARAM_OUT :
			out << "out ";
			break;
		case IR__::PARAM_INOUT :
			out << "inout ";
			break;
		default : {}
		}
		out << tcToName((*para_seq)[i - 1].type) << " " << string((*para_seq)[i - 1].name);
	}
	out << ")";

	// exceptions
	IR__::ExceptionDefSeq_var exception_seq = operation->exceptions();
	for(i = 0; i < exception_seq->length(); i++)
	{
		if(!i)
		{
			out << " raises(";
		}
		else
		{
			out << ", ";
		}
		out << tcToName((*exception_seq)[i]->type());
	}
	if(i)
	{
		out << ")";
	}
	out << ";\n";
}


void
GeneratorLIDL::doFactory(IR__::FactoryDef_ptr factory)
{
	out << "\n//\n// " << factory->id() << "\n//\n";
	out << "::Components::EnterpriseComponent " << factory->name() << "(";
	
	// parameters
	IR__::ParDescriptionSeq_var para_seq = factory->params();
	CORBA::ULong len = para_seq->length();
	CORBA::ULong i;
	for( i= len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}

		out << "in " << tcToName((*para_seq)[i - 1].type) << " " << string((*para_seq)[i - 1].name);
	}
	out << ")";

	// exceptions
	IR__::ExceptionDefSeq_var exception_seq = factory->exceptions();
	for(i = 0; i < exception_seq->length(); i++)
	{
		if(!i)
		{
			out << " raises(";
		}
		else
		{
			out << ", ";
		}
		out << tcToName((*exception_seq)[i]->type());
	}
	if(i)
	{
		out << ")";
	}
	out << ";\n";
}


void
GeneratorLIDL::doFinder(IR__::FinderDef_ptr finder)
{
	out << "\n//\n// " << finder->id() << "\n//\n";
	out << "::Components::EnterpriseComponent " << finder->name() << "(";

	// parameters
	IR__::ParDescriptionSeq_var para_seq = finder->params();
	CORBA::ULong len = para_seq->length();
	CORBA::ULong i;
	for( i= len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}

		out << "in " << tcToName((*para_seq)[i - 1].type) << " " << string((*para_seq)[i - 1].name);
	}
	out << ")";

	// exceptions
	IR__::ExceptionDefSeq_var exception_seq = finder->exceptions();
	for(i = 0; i < exception_seq->length(); i++)
	{
		if(!i)
		{
			out << " raises(";
		}
		else
		{
			out << ", ";
		}
		out << tcToName((*exception_seq)[i]->type());
	}
	if(i)
	{
		out << ")";
	}
	out << ";\n";
}


void
GeneratorLIDL::doUses(IR__::UsesDef_ptr uses, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << uses->id() << "\n//\n";

	//
	// multiple
	//
	if(uses->is_multiple())
	{
		out << map_absolute_name(component_) << "::" << uses->name() << "Connections ";
		out << "get_connections_" << uses->name() << "();\n";
	}
	//
	// not multiple
	//
	else
	{
		out << tcToName(uses->interface_type()->type()) << " get_connection_" << uses->name() << "();\n";
	}
}


void
GeneratorLIDL::doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << emits->id() << "\n//\n";
	
	out << "void push_" << emits->name() << "(in " << map_absolute_name(emits->event()) << " evt);\n";
}


void
GeneratorLIDL::doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << publishes->id() << "\n//\n";

	out << "void push_" << publishes->name() << "(in " << map_absolute_name(publishes->event()) << " evt);\n";
}


void 
GeneratorLIDL::doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << source->id() << "\n//\n";

	out << "void begin_stream_" << source->name() << " (in CORBA::RepositoryId repos_id, in Components::ConfigValues meta_data)\n";
	out.indent();
	out << "raises (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream);\n\n";
	out.unindent();

	out << "void end_stream_" << source->name() << "()\n";
	out.indent();
	out << "raises (StreamComponents::NoStream);\n\n";
	out.unindent();

	IR__::StreamTypeDef_var stream_type = source->stream_type();
	IR__::IDLType_var transported_type = stream_type->transported_type();

	if (CORBA::is_nil (transported_type))
	{
		// Multimedia stream
		out << "void send_stream_" << source->name() << " (in StreamComponents::StreamingBuffer buffer)\n";
	}
	else
	{
		// Value stream
		out << "void send_stream_" << source->name() << " (in " << map_absolute_name(transported_type) << " data)\n";
	}

	out.indent();
	out << "raises (StreamComponents::NoStream);\n\n";
	out.unindent();
}


void 
GeneratorLIDL::doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component)
{

	out << "//\n// sink executor interface for " << sink->name() << "\n//\n";
	out << "local interface CCM_" << component->name() << "_" << sink->name() << "_Sink : ";
	out << component->name() << "_" << sink->name() << "_Sink\n";
	out << "{\n";
	out << "};\n\n";
}


void
GeneratorLIDL::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	filename_ = file_prefix_ + "_LOCAL.idl";
	
	out.open(filename_.c_str());
	out << "#ifndef __" << file_prefix_ << "_LOCAL_IDL\n";
	out << "#define __" << file_prefix_ << "_LOCAL_IDL\n";
	out << "\n#include \"" << file_prefix_ << "_EQUIVALENT.idl\"\n\n\n";
	out << "// local interfaces\n\n";

	doGenerate();

	out << "\n#endif\n";
	out.close();
}
	

} // namespace
