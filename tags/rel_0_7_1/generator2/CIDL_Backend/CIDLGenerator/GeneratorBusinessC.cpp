#include "GeneratorBusinessC.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorBusinessC::GeneratorBusinessC
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository),
  pc_generator_(new GeneratorPersistenceC(repository))
{
}


GeneratorBusinessC::~GeneratorBusinessC
()
{
}


void
GeneratorBusinessC::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	doGenerate();

	// generate source code for PSS
	pc_generator_->generate(target, fileprefix);
	pc_generator_->destroy();
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
GeneratorBusinessC::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
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
GeneratorBusinessC::doFactory(IR__::FactoryDef_ptr factory)
{
	std::string factory_name = mapName(factory);

	out << "::Components::EnterpriseComponent_ptr\n";
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
	out << "	throw(CORBA::SystemException";
	handleException(factory);
	out << ")\n{\n";
	out.insertUserSection(class_name_ + "::" + factory->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doFinder(IR__::FinderDef_ptr finder)
{
	std::string finder_name = mapName(finder);

	out << "::Components::EnterpriseComponent_ptr\n";
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
	out << "	throw(CORBA::SystemException";
	handleException(finder);
	out << ")\n{\n";
	out.insertUserSection(class_name_ + "::" + finder->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doInterface(IR__::InterfaceDef_ptr intf)
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


void
GeneratorBusinessC::doComponent(IR__::ComponentDef_ptr component)
{
	//
	// handle base component
	//
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		doComponent(base);
	}

	handleAttribute(component);
	handleSupportedInterface(component);

	//
	// contained provides
	//
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	handled_interfaces_.clear();
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ProvidesDef_var act_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		bool realized_by_segment = false;

		//
		// exclude facets realized by a segment
		//
		CIDL::SegmentDefSeq_var segment_seq = composition_->executor_def()->segments();
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
			IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow(act_provides->interface_type());
			if( !CORBA::is_nil(intf) )
			{
				doInterface(intf);
			}
		}
	}

	// consumes
	if(component->contents(CORBA__::dk_Consumes, false)->length() && need_push_)
	{
		out << "void\n";
		out << class_name_ << "::push_event (Components::EventBase* ev)\n";
		out << "    throw (CORBA::SystemException)\n{\n";
		out.insertUserSection(class_name_ + "::push_event", 0);
		out << "}\n\n\n";
		need_push_ = false;
	}

	handleConsumes(component);
	handleSink(component);
}


void
GeneratorBusinessC::doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component)
{
    // push_...
	out << "void\n";
	out << class_name_ << "::push_" << consumes->event()->name() << "(" << mapFullName(consumes->event()) << "* ev)\n";
	out << "    throw (CORBA::SystemException)\n{\n";
	out.insertUserSection(class_name_ + "::push_" + consumes->event()->name(), 0);
	out << "}\n\n\n";
}


void
GeneratorBusinessC::doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component)
{
	std::string sink_name = sink->name();

	// begin_stream_*
	out << "void\n";
	out << class_name_ << "::begin_stream_" << sink_name << " (const char* repos_id, const ::Components::ConfigValues& meta_data)\n";
	out << "{\n"; out.indent();
	out.insertUserSection(class_name_ + "::begin_stream_" + sink_name, 0); out.unindent();
	out << "}\n\n\n";

	// end_stream_*
	out << "void\n";
	out << class_name_ << "::end_stream_" << sink_name << "()\n";
	out << "{\n"; out.indent();
	out.insertUserSection(class_name_ + "::end_stream_" + sink_name, 0); out.unindent();
	out << "}\n\n\n";

	// failed_stream_*
	out << "void\n";
	out << class_name_ << "::failed_stream_" << sink_name << "()\n";
	out << "{\n"; out.indent();
	out.insertUserSection(class_name_ + "::failed_stream_" + sink_name, 0); out.unindent();
	out << "}\n\n\n";

	// receive_stream_*
	out << "void\n";

	IR__::StreamTypeDef_var stream_type = sink->stream_type();
	IR__::IDLType_var transported_type = stream_type->transported_type();

	if (CORBA::is_nil (transported_type))
	{
		out << class_name_ << "::receive_stream_" << sink_name << " (StreamComponents::StreamingBuffer_ptr buffer)\n";
	}
	else
	{
		out << class_name_ << "::receive_stream_" << sink_name << " (" << map_in_parameter_type (transported_type) << " data)\n";
	}

	out << "{\n"; out.indent();
	out.insertUserSection(class_name_ + "::receive_stream_" + sink_name, 0); out.unindent();
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
	//
	// supported interfaces
	//
	IR__::InterfaceDefSeq_var supp_intfs = home -> supported_interfaces();
	for(CORBA::ULong i = 0; i < supp_intfs->length(); i++) {
		doInterface((*supp_intfs)[i]);
//		handleAttribute((*supp_intfs)[i]);
//		handleOperation((*supp_intfs)[i]);
	};

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
	CIDL::SegmentDefSeq_var segment_seq = composition->executor_def()->segments();

	// get storage home
	if( composition->lifecycle()==CIDL::lc_Entity || 
		composition->lifecycle()==CIDL::lc_Process )
	{
		storagehome_ = IR__::StorageHomeDef::_duplicate(composition->home_executor()->binds_to());
	}
	
	string id = composition->id();
	IR__::Contained_ptr module_def = 0;
	string::size_type pos = id.find_last_of("/");
	if(pos != string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		filename_ = getAbsoluteName(module_def, "_");
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
		open_module(out, module_def);
		out << "namespace " << mapName(module_def) << " {\n\n\n";
	}

	std::string context_name = mapFullNameLocal(composition->ccm_component()) + "_ContextImpl";

	//
	// executor
	//
	class_name_ = mapName(composition->executor_def());
	out.insertUserSection(class_name_, 2);

	// constructor
	switch(composition->lifecycle())
	{
	case CIDL::lc_Session :
	case CIDL::lc_Extension :
		out << class_name_ << "::" << class_name_ << "()\n";
		out << "{\n";
		out.insertUserSection(class_name_ + "::" + class_name_, 0);
		out << "}\n\n\n";
		break;
	case CIDL::lc_Entity :
		out << class_name_ << "::" << class_name_ << "(" << mapFullNamePK(composition->ccm_home()->primary_key()) << "* pkey)\n";
		out << "{\n";
		out.insertUserSection(class_name_ + "::" + class_name_, 0);
		out << "}\n\n\n";
		break;
	default :
		out << "// not supported lifecycle\n";
	}

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::~" + class_name_, 1);
	out << "}\n\n\n";

	// set_context
	out << "void\n";
	out << class_name_ << "::set_context(" << context_name << "_ptr context)\n";
	out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
	out.indent();
    out << "context_ = " << context_name << "::_duplicate(context);\n";
	out.unindent();
	out << "}\n\n\n";

	// configuration_complete
	out << "void\n";
	out << class_name_ << "::configuration_complete()\n";
	out << "    throw (CORBA::SystemException, Components::InvalidConfiguration)\n{\n";
	out.insertUserSection(class_name_ + "::configuration_complete", 0);	
	out << "}\n\n\n";

	// remove
	out << "void\n";
	out << class_name_ << "::remove()\n";
	out << "    throw (CORBA::SystemException)\n{\n";
	out.insertUserSection(class_name_ + "::remove", 0);	
	out << "}\n\n\n";

	if(composition->lifecycle() == CIDL::lc_Service)
	{
		// preinvoke
		out << "void\n";
		out << class_name_ << "::preinvoke(const char* comp_id, const char* operation)\n";
		out << "    throw (CORBA::SystemException)\n{\n";
		out.insertUserSection(class_name_ + "::preinvoke", 0);	
		out << "}\n\n\n";

		// postinvoke
		out << "void\n";
		out << class_name_ << "::postinvoke(const char* comp_id, const char* operation)\n";
		out << "    throw (CORBA::SystemException)\n{\n";
		out.insertUserSection(class_name_ + "::postinvoke", 0);	
		out << "}\n\n\n";
	}

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
		out << class_name_ << "::" << class_name_ << "()\n";
		out << "{\n";
		out.insertUserSection(class_name_ + "::" + class_name_, 0);
		out << "}\n\n\n";

		// destructor
		out << class_name_ << "::~" << class_name_ << "()\n{\n";
		out.insertUserSection(class_name_ + "::~" + class_name_, 1);
		out << "}\n\n\n";

		// set context
		out << "void\n";
		out << class_name_ << "::set_context(" << context_name << "_ptr context)\n";
		out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
		out.indent();
		out << "context_ = " << context_name << "::_duplicate(context);\n";
		out.unindent();
		out << "}\n\n\n";

		// configuration complete
		out << "void\n";
		out << class_name_ << "::configuration_complete()\n";
		out << "    throw (CORBA::SystemException, Components::InvalidConfiguration)\n{\n";
		out.insertUserSection(class_name_ + "::configuration_complete", 0);
		out << "}\n\n\n";

		// for each implemented facet
		IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
		handled_interfaces_.clear();
		for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
		{
			IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow(provided_seq[ii]->interface_type());
			if( !CORBA::is_nil(intf) )
			{
				doInterface(intf);
			}
		}
	}
	
	//
	// executor locator
	//
	class_name_ = mapName(composition);
	out.insertUserSection(class_name_, 2);

	// constructor
	switch(composition->lifecycle())
	{
	case CIDL::lc_Session :
	case CIDL::lc_Extension :
		out << class_name_ << "::" << class_name_ << "()\n";
		out << ":component_(new " << mapName(composition->executor_def()) << "())\n";
		for (i = 0; i < segment_seq->length(); i++)	{
			out << ", " << segment_seq[i]->name() << "_(new " << mapName(segment_seq[i]) << "())\n";
		}
		out << "{\n";
		out.insertUserSection(class_name_ + "::" + class_name_, 0);
		out << "}\n\n\n";
		break;
	case CIDL::lc_Entity :
		out << class_name_ << "::" << class_name_ << "(" << mapFullNamePK(composition->ccm_home()->primary_key()) << "* pkey)\n";
		out << ":component_(new " << mapName(composition->executor_def()) << "(pkey))\n";
		for (i = 0; i < segment_seq->length(); i++)	{
			out << ", " << segment_seq[i]->name() << "_(new " << mapName(segment_seq[i]) << "())\n";
		}
		out << "{\n";
		out.insertUserSection(class_name_ + "::" + class_name_, 0);
		out << "}\n\n\n";
		break;
	default :
		out << "// not supported lifecycle\n";
	}

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::~" + class_name_, 1);
	out.indent();
	out << "component_->_remove_ref();\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "_->_remove_ref();\n";
	}
	out.unindent();
	out << "}\n\n\n";

	// obtain executor
	out << "::CORBA::Object*\n";
	out << class_name_ << "::obtain_executor(const char* name)\n";
	out << "    throw (CORBA::SystemException)\n{\n";
	out.indent();
	out << "if (! strcmp ( name, \"component\" ) ) {\n";
	out.indent();
	out << "return Components::EnterpriseComponent::_duplicate (component_);\n";
	out.unindent();
	out << "}\n\n";

	// facets
	IR__::ComponentDef_var component = composition->ccm_component();

	this -> gen_executor_locator_factes (component, composition);
	/*
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
*/
	// sinks
	IR__::SinkDefSeq_var sink_seq = composition->ccm_component()->sinks();
	for (i = 0; i < sink_seq->length(); i++) {
		out << "else if (! strcmp (name, \"" << sink_seq[i]->name() << "\")) {\n";
		out.indent();
		out << "return Components::EnterpriseComponent::_duplicate (component_);\n"; out.unindent();
		out << "}\n\n";
	}

	out << "return Components::EnterpriseComponent::_nil();\n";
	out.unindent();
	out << "}\n\n\n";

	// release executor
	out << "void\n";
	out << class_name_ << "::release_executor(::CORBA::Object_ptr executor)\n";
	out << "    throw (CORBA::SystemException)\n{\n";
	out.indent();
	out << "CORBA::release (executor);\n";
	out.unindent();
	out << "}\n\n\n";

	// configuration complete
	out << "void\n";
	out << class_name_ << "::configuration_complete()\n";
	out << "    throw (CORBA::SystemException, Components::InvalidConfiguration)\n{\n";
	out.indent();
	out << "component_->configuration_complete();\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "_->configuration_complete();\n";
	}
	out.unindent();
	out << "\n";
	out.insertUserSection(class_name_ + "::configuration_complete", 0);
	out << "}\n\n\n";

	// set context
	out << "void\n";
	//
	// determin the lifecycle
	//
	CIDL::LifecycleCategory lc = composition->lifecycle();
	switch(lc) {
		case (CIDL::lc_Session) : 
			{
				out << class_name_ << "::set_session_context(::Components::SessionContext_ptr context)\n";
				break;
			}
        case (CIDL::lc_Entity) : 
			{
				out << class_name_ << "::set_entity_context(::Components::EntityContext_ptr context)\n";
				break;
			}
		case (CIDL::lc_Extension) :
			{
				out << class_name_ << "::set_extension_context(::Components::ExtensionContext_ptr context)\n";
				break;
			}
		default:
			{
				//unsupported lifecycle category
			}
	}

	out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
	out.indent();
	out << "#ifdef TAO_ORB\n";
	out << mapFullNameLocal(composition->ccm_component()) << "_Context_ptr tmp_context;\n\n";
	out << "tmp_context = dynamic_cast<" << context_name << "*>(context);\n\n";
	out << "if (tmp_context)\n";
	out.indent();
	out << "context_ = " << context_name << "::_duplicate(tmp_context);\n";
	out.unindent();
	out << "else\n";
	out.indent();
	out << "context_ = " << context_name << "::_nil();\n\n";
	out.unindent();
	out << "#else\n";
	out << "context_ = " << context_name << "::_narrow(context);\n\n";
	out << "#endif\n";
	out << "component_->set_context(context_);\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "_->set_context(context_);\n";
	}

	out.unindent();
	out << "}\n\n\n";

	// unset_entity_context for entity component
	if(composition->lifecycle()==CIDL::lc_Entity)
	{
		out << "void\n";
		out << class_name_ << "::unset_entity_context()\n";
		out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
		out.insertUserSection(class_name_ + "::unset_entity_context", 0);
		out << "}\n\n\n";
	}

	// ccm_activate
	out << "void\n";
	out << class_name_ << "::ccm_activate()\n";
	out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
	out.insertUserSection(class_name_ + "::ccm_activate", 0);
	out << "}\n\n\n";

	// ccm_load and ccm_store for entity component
	if(composition->lifecycle()==CIDL::lc_Entity)
	{
		out << "void\n";
		out << class_name_ << "::ccm_load()\n";
		out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
		out.insertUserSection(class_name_ + "::ccm_load", 0);
		out << "}\n\n\n";

		out << "void\n";
		out << class_name_ << "::ccm_store()\n";
		out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";

		out.indent();
		out << "StorageObject* ccm_obj = dynamic_cast <StorageObject*> (context_->get_ccm_storage_object());\n";
		out << composition->ccm_component()->name() << "Persistence* ccm_object = dynamic_cast <" << composition->ccm_component()->name() << "Persistence*> (ccm_obj);\n";
		IR__::AttributeDefSeq state_members;
		composition->ccm_component()->get_state_members(state_members, CORBA__::dk_Create);
		CORBA::ULong ulLen = state_members.length();
		for(CORBA::ULong i=0; i<ulLen; i++)
		{
			IR__::AttributeDef_var attribute = IR__::AttributeDef::_narrow(state_members[i]);
			if(attribute->type_def()->type()->kind() != CORBA::tk_value)
				out << "ccm_object->" << mapName(attribute) << "( component_->" << mapName(attribute) << "() );\n";
		}

		if( !CORBA::is_nil(storagehome_) )
		{
			out << "\nStorageObject* obj = dynamic_cast <StorageObject*> (context_->get_storage_object());\n";
			out << storagehome_->managed_storagetype()->name() << "* object = dynamic_cast <" << storagehome_->managed_storagetype()->name() << "*> (obj);\n\n";
		}
		out.unindent();

		out.insertUserSection(class_name_ + "::ccm_store", 0);
		
		out.indent();
		out << "\nccm_object->write_state();\n";
		if( !CORBA::is_nil(storagehome_) )
			out << "object->write_state();\n";
		out.unindent();
		out << "}\n\n\n";
	}

	// ccm_passivate
	out << "void\n";
	out << class_name_ << "::ccm_passivate()\n";
	out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
	out.insertUserSection(class_name_ + "::ccm_passivate", 0);
	out << "}\n\n\n";

	// ccm_remove
	out << "void\n";
	out << class_name_ << "::ccm_remove()\n";
	out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
	out.insertUserSection(class_name_ + "::ccm_remove", 0);
	if(composition->lifecycle()==CIDL::lc_Entity)
	{
		out.indent();
		out << "StorageObject* ccm_obj = dynamic_cast <StorageObject*> (context_->get_ccm_storage_object());\n";
		out << composition->ccm_component()->name() << "Persistence* ccm_object = dynamic_cast <" << composition->ccm_component()->name() << "Persistence*> (ccm_obj);\n";
		out << "if( ccm_object->object_exists() )\n";
		out.indent();
		out << "ccm_object->destroy_object();\n";
		out.unindent();

		if( !CORBA::is_nil(storagehome_) )
		{	
			out << "\nStorageObject* obj = dynamic_cast <StorageObject*> (context_->get_storage_object());\n";
			out << storagehome_->managed_storagetype()->name() << "* object = dynamic_cast <" << storagehome_->managed_storagetype()->name() << "*> (obj);\n";
			out << "if( object->object_exists() )\n";
			out.indent();
			out << "object->destroy_object();\n";
			out.unindent();
		}
		out.unindent();
	}
	out << "}\n\n\n";

	if(composition->lifecycle() == CIDL::lc_Service)
	{
		// preinvoke
		out << "void\n";
		out << class_name_ << "::preinvoke(const char* comp_id, const char* operation)\n";
		out << "    throw (CORBA::SystemException)\n{\n";
		out.indent();
		out << "component_->preinvoke(comp_id, operation);\n";
		out.unindent();	
		out << "}\n\n\n";

		// postinvoke
		out << "void\n";
		out << class_name_ << "::postinvoke(const char* comp_id, const char* operation)\n";
		out << "    throw (CORBA::SystemException)\n{\n";
		out.indent();
		out << "component_->postinvoke(comp_id, operation);\n";
		out.unindent();
		out << "}\n\n\n";
	}

	//
	// home executor
	//
	class_name_ = mapName(composition->home_executor());
	out.insertUserSection(class_name_, 2);

	// constructor
	out << class_name_ << "::" << class_name_ << "()\n";
	out << "{\n";
	out.insertUserSection(class_name_ + "::" + class_name_, 0);
	out << "}\n\n\n";

	// destructor
	out << class_name_ << "::~" << class_name_ << "()\n{\n";
	out.insertUserSection(class_name_ + "::~" + class_name_, 1);
	out << "}\n\n\n";

	// set context
	out << "void\n";
	out << class_name_ << "::set_context(Components::HomeContext_ptr ctx)\n";
	out << "    throw (CORBA::SystemException, Components::CCMException)\n{\n";
	out.indent();
    // out << "context_ = " << context_name << "::_narrow(ctx);\n";		// this is wrong
	out << "context_ = Components::HomeContext::_duplicate(ctx);\n\n";
	out.unindent();
	out << "}\n\n\n";
	
	//operations derived from implicit home
	switch(composition->lifecycle())
	{
	case CIDL::lc_Session :
	case CIDL::lc_Extension :
		out << "::Components::EnterpriseComponent_ptr\n";
		out << class_name_ << "::create ()\n";
		out << "    throw (CORBA::SystemException, Components::CreateFailure)\n{\n";
		out.indent();
		out.insertUserSection(class_name_ + "::create", 0);
		out << "return new " << mapName(composition) << "();\n";
		out.unindent();
		out << "}\n\n\n";
		break;
	case CIDL::lc_Entity :
		out << "::Components::EnterpriseComponent_ptr\n";
		out << class_name_ << "::create(" << mapFullNamePK(composition->ccm_home()->primary_key()) << "* pkey" << ")\n";
		out << "    throw(CORBA::SystemException, Components::CreateFailure, Components::DuplicateKeyValue, Components::InvalidKey)\n{\n";
		out.indent();
		out.insertUserSection(class_name_ + "create", 0);
		out << "return new " << mapName(composition) << "(pkey);\n";
		out.unindent();
		out << "}\n\n\n";
/*
		out << "::Components::EnterpriseComponent_ptr\n";
		out << class_name_ << "::find_by_primary_key(" << mapFullNamePK(composition->ccm_home()->primary_key()) << "* pkey)\n"; 
		out << "	throw(CORBA::SystemException, Components::FinderFailure, Components::UnknownKeyValue, Components::InvalidKey)\n{\n";
		out.indent();
		out.insertUserSection(class_name_ + "find_by_primary_key", 0);
		out.unindent();
		out << "}\n\n\n";

		out << "void\n";
		out << class_name_ << "::remove(" << mapFullNamePK(composition->ccm_home()->primary_key()) << "* pkey)\n"; 
		out << "	throw(CORBA::SystemException, Components::RemoveFailure, Components::UnknownKeyValue, Components::InvalidKey)\n{\n";
		out.indent();
		out.insertUserSection(class_name_ + "remove", 0);
		out.unindent();
		out << "}\n\n\n";
*/
		//get_primary_key(...)??? !!!

		break;
	default :
		out << "// not supported lifecycle\n";
	}

	doHome(composition->ccm_home());

	// close module
	if(module_def)
	{
		out << "};\n";
		close_module(out, module_def);
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

void
GeneratorBusinessC::gen_executor_locator_factes (IR__::ComponentDef_var a_component, CIDL::CompositionDef_ptr composition)
{
	// handle base components
	IR__::ComponentDef_var base_component = a_component->base_component();
	if ( ! CORBA::is_nil(base_component)) {
		this->gen_executor_locator_factes (base_component, composition);

	}
	// generate for facets
	CIDL::SegmentDefSeq_var segment_seq = composition->executor_def()->segments();
	IR__::ProvidesDefSeq_var provides_seq = a_component->provides_interfaces();
	string impl_by;

	for (CORBA::ULong i = 0; i < provides_seq->length(); i++) {
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
}
} //
