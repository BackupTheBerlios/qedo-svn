#include "GeneratorBusinessH.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorBusinessH::GeneratorBusinessH
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository)
{
}


GeneratorBusinessH::~GeneratorBusinessH
()
{
}


void
GeneratorBusinessH::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	doGenerate();
}
	

void
GeneratorBusinessH::doModule(IR__::ModuleDef_ptr module)
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
GeneratorBusinessH::doValue(IR__::ValueDef_ptr value)
{
	out << "\n//\n// " << value->id() << "\n//\n";
	std::string value_name = value->name();
	std::string class_name = mapName(value_name);

	// value type
	out << "class " << class_name << "\n";
	out << ": virtual public OBV_" << value->name() << "\n";
	out << ", virtual public CORBA::DefaultValueRefCountBase\n{\n";
	out << "public:\n\n";
	out.indent();
	handleValueMember(value);
	out.unindent();
	out << "};\n\n\n";

	//
	// value type factory
	//
	out << "class " << value_name << "_factory\n";
	out << ": virtual public CORBA::ValueFactoryBase\n{\n";
	out << "public:\n\n";
	out.indent();
	out << "CORBA::ValueBase * create_for_unmarshal();\n";
	out << "};\n\n\n";
}


void 
GeneratorBusinessH::doValueMember(IR__::ValueMemberDef_ptr member)
{
	IR__::IDLType_ptr type = member->type_def();
	std::string name = mapName(member);

	switch (type->type()->kind()) {
	case CORBA::tk_string:
		out << "void " << name << "(char* _p);\n";
		out << "void " << name << "(const char* _p);\n";
		out << "void " << name << "(const CORBA::String_var& _p);\n";
		out << "const char* " << name << "() const;\n\n";
		break;
		
	case CORBA::tk_enum:
		out << "void " << name << "(" << map_in_parameter_type(type) << " _p);\n";
		out << map_value_return_type(type) << " " << name << "();\n";
		out << "const " << map_value_return_type(type) << " " << name << "() const;\n\n";
		break;

	default:
		out << "void " << name << "(" << map_in_parameter_type(type);
		out << " _p);\n";
		out << map_value_return_type(type) << " " << name << "() const;\n\n";
	}
}


void
GeneratorBusinessH::doAttribute(IR__::AttributeDef_ptr attribute)
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
GeneratorBusinessH::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << mapFullName(except);
}


void
GeneratorBusinessH::doOperation(IR__::OperationDef_ptr operation)
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
GeneratorBusinessH::doFactory(IR__::FactoryDef_ptr factory)
{
	out << "\n//\n// " << factory->id() << "\n//\n";

	out << "virtual ::Components::EnterpriseComponent_ptr " << mapName(factory) << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = factory->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(std::string(pardescr.name));
	};
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(factory);
	out << ");\n";
}


void
GeneratorBusinessH::doFinder(IR__::FinderDef_ptr finder)
{
	out << "\n//\n// " << finder->id() << "\n//\n";

	out << "virtual ::Components::EnterpriseComponent_ptr " << mapName(finder) << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = finder->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << mapName(string(pardescr.name));
	};
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(finder);
	out << ");\n";
}


void
GeneratorBusinessH::doInterface(IR__::InterfaceDef_ptr intf)
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


void
GeneratorBusinessH::doComponent(IR__::ComponentDef_ptr component)
{
	//
	// base component
	//
	IR__::ComponentDef_ptr base = component->base_component();
	if(! CORBA::is_nil(base))
	{
		doComponent(base);
	}

	handleAttribute(component);
	handleSupportedInterface(component);

	// provides
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	handled_interfaces_.clear();
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::ProvidesDef_var act_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		bool realized_by_segment = false;

		// exclude facets realized by a segment
		CIDL::SegmentDefSeq_var segment_seq = composition_->executor_def()->segments();
		for (CORBA::ULong i = 0; i < segment_seq->length(); i++)
		{
			// for each implemented facet
			IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
			for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
			{
				if(!strcmp(act_provides->name(), provided_seq[ii]->name()))
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
		out << "\n//\n// IDL:Components/EventConsumerBase/push_event:1.0\n//\n";
		out << "virtual void push_event (Components::EventBase* ev)\n";
		out << "    throw (CORBA::SystemException);\n\n";
		need_push_ = false;
	}
	handleConsumes(component);
}


void
GeneratorBusinessH::doConsumes(IR__::ConsumesDef_ptr consumes)
{
	out << "\n//\n// " << consumes->id() << "\n//\n";

	// push operation
	out << "void push_" << mapName(consumes->event()) << "(" << mapFullName(consumes->event()) << "* ev)\n";
	out << "    throw (CORBA::SystemException);\n\n";
}


void
GeneratorBusinessH::doSource(IR__::SourceDef_ptr source)
{
#if 0
	IR__::StreamTypeDef* st_def = source->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", getAbsoluteName(st_def))) {
		out << "virtual CCMStream::h323Stream_ptr ";
		out /*<< map_absolute_under_name(component_def)*/  << "_provide_" << source->name() << "()\n";
		out << "    throw (CORBA::SystemException);\n\n";
	}
	if (!strcmp("Components::CCMStream::QoSRealStream", getAbsoluteName(st_def))) {
		out << "virtual CCMStream::QoSRealStream_ptr ";
		out /*<< map_absolute_under_name(component_def)*/  << "_provide_" << source->name() << "()\n";
		out << "    throw (CORBA::SystemException);\n\n";
	}
#endif
}


void
GeneratorBusinessH::doSink(IR__::SinkDef_ptr sink)
{
/*	IR__::StreamTypeDef* st_def = (*act_sinks)[sink_n]->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", getAbsoluteName(st_def))) {
		hserv << "virtual void " << endl;
		hserv << map_absolute_under_name(component_def)  << "_connect_" << (*act_sinks)[sink_n]->name();
		hserv << "( CCMStream::h323Stream_ptr str) = 0;" << endl;
	}
	if (!strcmp("Components::CCMStream::QoSRealStream", getAbsoluteName(st_def))) {
		hserv << "virtual void " << endl;
		hserv << map_absolute_under_name(component_def)  << "_connect_" << (*act_sinks)[sink_n]->name();
		hserv << "( CCMStream::QoSRealStream_ptr str) = 0;" << endl;
	}*/
}


void
GeneratorBusinessH::doSiSo(IR__::SiSoDef_ptr siso)
{
/*	IR__::StreamTypeDef* st_def = (*act_sisos)[siso_n]->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", getAbsoluteName(st_def))) {
		hserv << "virtual CCMStream::h323Stream_ptr" << endl;
		hserv << map_absolute_under_name(component_def)  << "_provide_" << (*act_sisos)[siso_n]->name();
		hserv << "() = 0;" << endl;

		hserv << "virtual void" << endl;
		hserv << map_absolute_under_name(component_def)  << "_connect_" << (*act_sisos)[siso_n]->name();
		hserv << "( CCMStream::h323Stream_ptr str) = 0;" << endl;

	}
	if (!strcmp("Components::CCMStream::QoSRealStream", getAbsoluteName(st_def))) {
		hserv << "virtual CCMStream::QoSRealStream_ptr" << endl;
		hserv << map_absolute_under_name(component_def)  << "_provide_" << (*act_sisos)[siso_n]->name();
		hserv << "() = 0;" << endl;

		hserv << "virtual void" << endl;
		hserv << map_absolute_under_name(component_def)  << "_connect_" << (*act_sisos)[siso_n]->name();
		hserv << "( CCMStream::QoSRealStream_ptr str) = 0;" << endl;
	}*/
}


void
GeneratorBusinessH::doHome(IR__::HomeDef_ptr home)
{
	//
	// base home
	//
	IR__::HomeDef_var base = home->base_home();
	if(! CORBA::is_nil(base))
	{
		doHome(base);
	}
	//
	// supported interfaces
	//
	IR__::InterfaceDefSeq_var supp_intfs = home -> supported_interfaces();
	for(CORBA::ULong i = 0; i < supp_intfs->length(); i++) {
		handleAttribute((*supp_intfs)[i]);
		handleOperation((*supp_intfs)[i]);
	};

	handleAttribute(home);
	handleOperation(home);
	handleFactory(home);
	handleFinder(home);
}


void
GeneratorBusinessH::doComposition(CIDL::CompositionDef_ptr composition)
{
	CORBA::ULong i ;
	composition_ = CIDL::CompositionDef::_duplicate(composition);
	filename_ = "";

	//
	// determine whether defined in module (needed for namespace opening and closing)
	//
	IR__::Contained_ptr module_def = 0;
	string id = composition->id();
	string::size_type pos = id.find_last_of("/");
	if(pos != string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		filename_ = getAbsoluteName(module_def, "_");
		filename_.append("_");
	}
	filename_.append(composition->name());
	string header_name = filename_;
	filename_.append(".h");
	
	//
	// parse for user sections and write header in the output file
	//
	out.initUserSections(filename_.c_str());
	out.open(filename_.c_str());
	out << "//\n";
	out << "// generated by Qedo\n";
	out << "//\n\n";
	out << "#ifndef _" << header_name << "_H_\n";
	out << "#define _" << header_name << "_H_\n\n\n"; 
	out.insertUserSection("file_pre", 2);
	out << "#include <CORBA.h>\n";
	out << "#include \"" << file_prefix_ << "_BUSINESS.h\"\n";
	out << "#include \"RefCountBase.h\"\n";
	out << "#include <string>\n\n\n";
	out.insertUserSection("file_post", 2);

	if(module_def)
	{
		open_module(out, module_def);
		out << "namespace " << mapName(module_def) << "\n{\n";
		out.indent();
	}

	CIDL::SegmentDefSeq_var segment_seq = composition->executor_def()->segments();
	std::string executor_name = composition->executor_def()->name();
	std::string executor_class_name = mapName(executor_name);
	std::string executor_locator_name = composition->name();
	std::string executor_locator_class_name = mapName(executor_locator_name);
	std::string home_name = composition->home_executor()->name();
	std::string home_class_name = mapName(home_name);

	//
	// executor
	//
	out << "\n//\n// executor\n//\n";
	out << "class " << executor_class_name << "\n";
	out.indent();
	out << ": public virtual CORBA::LocalObject\n";
	out << ", public virtual " << mapScopeName(composition) << "::CCM_" << executor_name << "\n";
	out.unindent(); out.unindent();
	out << "#ifndef MICO_ORB\n";
	out.indent(); out.indent();
	out << ", public virtual Qedo::RefCountLocalObject\n";
	out.unindent(); out.unindent();
	out << "#endif\n";
	out.indent(); out.indent();
	out.insertUserSection(string("INHERITANCE_") + executor_name, 0);
	out.unindent();
	out << "{\n\n";
	out << "private:\n\n";
	out.indent();
	out << "Qedo::qedo_mutex mutex_;\n\n";
    out << mapFullNameLocal(composition->ccm_component()) << "_Context_var context_;\n\n";
	out.unindent();
	out << "public:\n\n";
	out.indent();
	out << executor_class_name << "();\n";
	out << "virtual ~" << executor_class_name << "();\n\n";
	out << "void set_context(" << mapFullNameLocal(composition->ccm_component()) << "_Context_ptr context)\n";
	out << "    throw (CORBA::SystemException, Components::CCMException);\n\n";
    out << "void configuration_complete()\n";
	out << "    throw (CORBA::SystemException, Components::InvalidConfiguration);\n\n";
    out << "void remove()\n";
	out << "    throw (CORBA::SystemException);\n\n";
	// for service extension
	if(composition->lifecycle() == 0)
	{
		out << "void preinvoke(const char* comp_id, const char* operation)\n";
		out << "    throw (CORBA::SystemException);\n\n";
		out << "void postinvoke(const char* comp_id, const char* operation)\n";
		out << "    throw (CORBA::SystemException);\n\n";
	}
	need_push_ = true;
	doComponent(composition->ccm_component());
	out.unindent();
	out << "\n";
	out.insertUserSection(executor_name);
	out << "};\n\n";

	//
	// segment
	//
	for (i = 0; i < segment_seq->length(); i++)
	{
		std::string segment_name = segment_seq[i]->name();
		std::string segment_class_name = mapName(segment_name);
		out << "\n//\n// segment\n//\n";
		out << "class " << segment_class_name << "\n";
		out.indent();
		out << ": public virtual CORBA::LocalObject\n";
		out << ", public virtual " << mapScopeName(composition) << "::CCM_" << segment_name << "\n";
		out.unindent(); out.unindent();
		out << "#ifndef MICO_ORB\n";
		out.indent(); out.indent();
		out << ", public virtual Qedo::RefCountLocalObject\n";
		out.unindent(); out.unindent();
		out << "#endif\n";
		out.indent(); out.indent();
		out.insertUserSection(string("INHERITANCE_") + segment_name, 0);
		out.unindent();
		out << "{\n\n";
		out << "private:\n\n";
		out.indent();
		out << "Qedo::qedo_mutex mutex_;\n\n";
		out << mapFullNameLocal(composition->ccm_component()) << "_Context_var context_;\n\n";
		out.unindent();
		out << "public:\n\n";
		out.indent();
		out << segment_class_name << "();\n";
		out << "virtual ~" << segment_class_name << "();\n\n";
		out << "void set_context(" << mapFullNameLocal(composition->ccm_component()) << "_Context_ptr context)\n";
		out << "    throw (CORBA::SystemException, Components::CCMException);\n\n";
		out << "void configuration_complete()\n";
		out << "    throw (CORBA::SystemException, Components::InvalidConfiguration);\n\n";
		// for each implemented facet
		IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
		handled_interfaces_.clear();
		for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
		{
			doInterface(provided_seq[ii]->interface_type());
		}
		out.unindent();
		out << "\n";
		out.insertUserSection(segment_name);
		out << "};\n\n";
	}

	//
	// executor locator
	//
	out << "\n//\n// executor locator\n//\n";
	out << "class " << executor_locator_class_name << "\n";
	out.indent();
	out << ": public virtual CORBA::LocalObject\n";
	// for service extension
	if(composition->lifecycle() == 0)
	{
		out << ", public virtual Components::CCMService\n";
	}
	else
	{
		out << ", public virtual Components::SessionExecutorLocator\n";
	}
	out.unindent(); out.unindent();
	out << "#ifndef MICO_ORB\n";
	out.indent(); out.indent();
	out << ", public virtual Qedo::RefCountLocalObject\n";
	out.unindent(); out.unindent();
	out << "#endif\n";
	out.indent(); out.indent();

	out.insertUserSection(string("INHERITANCE_") + executor_locator_name, 0);
	out.unindent();
	out << "{\n\n";
	out << "private:\n\n";
	out.indent();
	out << "Qedo::qedo_mutex mutex_;\n\n";
    out << mapFullNameLocal(composition->ccm_component()) << "_Context_var context_;\n\n";
	out << mapName(composition->executor_def()) << "* component_;\n\n";
	for (i = 0; i < segment_seq->length(); i++)	{
		out << mapName(segment_seq[i]) << "* " << segment_seq[i]->name() << "_;\n\n";
	}
	out.unindent();
	out << "public:\n\n";
	out.indent();
    out << executor_locator_class_name << "();\n";
    out << "virtual ~" << executor_locator_class_name << "();\n\n";
	IR__::InterfaceDef_ptr executor_locator;
	// for service extension
	if(composition->lifecycle() == 0)
	{
		executor_locator = IR__::InterfaceDef::_narrow(repository_->lookup_id("IDL:Components/CCMService:1.0"));
	}
	else
	{
		executor_locator = IR__::InterfaceDef::_narrow(repository_->lookup_id("IDL:Components/SessionExecutorLocator:1.0"));
	}
	doInterface(executor_locator);
	out.unindent();
	out << "\n";
	out.insertUserSection(executor_locator_name);
	out << "};\n\n";

	//
	// home executor
	//
	out << "\n//\n// home executor\n//\n";
	out << "class " << home_class_name << "\n";
	out.indent();
	out << ": public virtual CORBA::LocalObject\n";
	out << ", public virtual " << getLocalName(composition->ccm_home()) << "\n";
	out.unindent(); out.unindent();
	out << "#ifndef MICO_ORB\n";
	out.indent(); out.indent();
	out << ", public virtual Qedo::RefCountLocalObject\n";
	out.unindent(); out.unindent();
	out << "#endif\n";
	out.indent(); out.indent();
	out.insertUserSection(std::string("INHERITANCE_") + home_name, 0);
	out.unindent();
	out << "{\n\n";
	out << "private:\n\n";
	out.indent();
	out << "Qedo::qedo_mutex mutex_;\n\n";
    out << "Components::CCMContext_var context_;\n\n";
	out.unindent();
	out << "public:\n";
	out.indent();
    out << home_class_name << "();\n";
    out << "virtual ~" << home_class_name << "();\n\n";
	out << "//\n// IDL:Components/HomeExecutorBase/set_context:1.0\n//\n";
	out << "virtual void set_context (Components::CCMContext_ptr ctx)\n";
	out << "    throw (CORBA::SystemException, Components::CCMException);\n\n";
    out << "//\n// IDL:.../create:1.0\n//\n";
    out << "virtual ::Components::EnterpriseComponent_ptr create()\n";
	out << "    throw (CORBA::SystemException, Components::CreateFailure);\n";
	doHome(composition->ccm_home());
	out.unindent();
	out << "\n";
	out.insertUserSection(home_name);
	out << "};\n\n";


	// close namespace
	if(module_def)
	{
		out.unindent();
		out << "};\n";
		close_module(out, module_def);
	}

	//
	// entry point
	//
	out << "\n//\n// entry point\n//\n";
	out << "extern \"C\" {\n";
	out << "#ifdef _WIN32\n";
	out << "__declspec(dllexport)\n";
	out << "#else\n";
	out << "#endif\n";
	out << "::Components::HomeExecutorBase_ptr create_" << composition->ccm_home()->name() << "E(void);\n";
	out << "}\n\n";

	out << "#endif\n";
	out.close();
}


} // namespace
