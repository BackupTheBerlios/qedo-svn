#include "GeneratorBusinessH.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorBusinessH::GeneratorBusinessH
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: GeneratorBase(repository)
{
}


GeneratorBusinessH::~GeneratorBusinessH
()
{
}


void
GeneratorBusinessH::open_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) {
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->open_module(act_mod);
		out << "namespace " << act_mod->name() << " {\n";
		out.indent();
	}
};


void
GeneratorBusinessH::close_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) {
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->close_module(act_mod);
		out.unindent();
		out << "};\n";
	}
};


void
GeneratorBusinessH::generate(string target)
{
	target_ = target;
	doGenerate(target);
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

	// value type
	out << "class " << map_absolute_under_name(value) << "_impl\n";
	out << ": virtual public OBV_" << map_absolute_name(value) << "\n";
	out << ", virtual public CORBA::DefaultValueRefCountBase\n{\n";
	out << "public:\n\n";
	out.indent();
	handleValueMember(value);
	out.unindent();
	out << "};\n\n\n";

	// value type factory
	out << "class " << map_absolute_under_name(value) << "_factory\n";
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
	switch (type->type()->kind()) {
	case CORBA::tk_string:
		out << "void " << member->name() << "(char* _p);\n";
		out << "void " << member->name() << "(const char* _p);\n";
		out << "void " << member->name() << "(const CORBA::String_var& _p);\n";
		out << "const char* " << member->name() << "() const;\n\n";
		break;
		
	case CORBA::tk_enum:
		out << "void " << member->name() << "(" << map_in_parameter_type(type) << " _p);\n";
		out << map_value_return_type(type) << " " << member->name() << "();\n";
		out << "const " << map_value_return_type(type) << " " << member->name() << "() const;\n\n";
		break;

	default:
		out << "void " << member->name() << "(" << map_in_parameter_type(type);
		out << " _p);\n";
		out << map_value_return_type(type) << " " << member->name() << "() const;\n\n";
	}
}


void
GeneratorBusinessH::doAttribute(IR__::AttributeDef_ptr attribute)
{
	out << "\n//\n// " << attribute->id() << "\n//\n";

	// attribute mode
	if(attribute->mode() == IR__::ATTR_NORMAL)
	{
		out << "void " << attribute->name() << "(";
		out << map_in_parameter_type(attribute->type_def()) << " param)\n";
		out << "	throw(CORBA::SystemException";
		handleException(attribute);
		out << ");\n";
	}

	out << map_return_type(attribute->type_def()) << " " << attribute->name() << "()\n";
	out << "	throw(CORBA::SystemException";
	handleException(attribute);
	out << ");\n";
}


void 
GeneratorBusinessH::doException(IR__::ExceptionDef_ptr except)
{
	out << ", " << map_absolute_name(except);
}


void
GeneratorBusinessH::doOperation(IR__::OperationDef_ptr operation)
{
	out << "\n//\n// " << operation->id() << "\n//\n";

	out << "virtual " << map_return_type(operation->result_def()) << " " << operation->name() << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = operation->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
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

	out << "virtual " << map_return_type(composition_->ccm_component()) << " " << factory->name() << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = factory->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
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

	out << "virtual " << map_return_type(composition_->ccm_component()) << " " << finder->name() << "(";
	// Parameter of the operation
	IR__::ParDescriptionSeq* pards = finder->params();
	for(CORBA::ULong i = pards->length(); i > 0; i--)
	{
		if(i < pards->length())
		{
			out << ", ";
		}
		IR__::ParameterDescription pardescr = (*pards)[i - 1];
		out << map_in_parameter_type (pardescr.type_def) << " " << string(pardescr.name);
	};
	out << ")\n";
	out << "	throw(CORBA::SystemException";
	handleException(finder);
	out << ");\n";
}


void
GeneratorBusinessH::doInterface(IR__::InterfaceDef_ptr intf)
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
GeneratorBusinessH::doComponent(IR__::ComponentDef_ptr component)
{
	// base component
	IR__::ComponentDef_ptr base = component->base_component();
	if(! CORBA::is_nil(base))
	{
		doComponent(base);
	}

	
	handleAttribute(component);
	handleSupportedInterface(component);


	// provides
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::ProvidesDef_var act_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		bool realized_by_segment = false;

		// exclude facets realized by a segment
		CIDL::SegmentDefSeq_var segment_seq = composition_->executor()->segments();
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
		out << "virtual void push_event (Components::EventBase* ev);\n";
		need_push_ = false;
	}
	handleConsumes(component);
}


void
GeneratorBusinessH::doConsumes(IR__::ConsumesDef_ptr consumes)
{
    // push operation
	out << "\n//\n// " << consumes->id() << "\n//\n"; 
	out << "void push_" << consumes->event()->name() << "(" << map_absolute_name(consumes->event());
	out << "* ev);\n";
}


void
GeneratorBusinessH::doSource(IR__::SourceDef_ptr source)
{
	IR__::StreamTypeDef* st_def = source->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", map_absolute_name(st_def))) {
		out << "virtual CCMStream::h323Stream_ptr ";
		out /*<< map_absolute_under_name(component_def)*/  << "_provide_" << source->name();
		out << "();\n\n";
	}
	if (!strcmp("Components::CCMStream::QoSRealStream", map_absolute_name(st_def))) {
		out << "virtual CCMStream::QoSRealStream_ptr ";
		out /*<< map_absolute_under_name(component_def)*/  << "_provide_" << source->name();
		out << "();\n\n";
	}
}


void
GeneratorBusinessH::doSink(IR__::SinkDef_ptr sink)
{
/*	IR__::StreamTypeDef* st_def = (*act_sinks)[sink_n]->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", map_absolute_name(st_def))) {
		hserv << "virtual void " << endl;
		hserv << map_absolute_under_name(component_def)  << "_connect_" << (*act_sinks)[sink_n]->name();
		hserv << "( CCMStream::h323Stream_ptr str) = 0;" << endl;
	}
	if (!strcmp("Components::CCMStream::QoSRealStream", map_absolute_name(st_def))) {
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
	if (!strcmp("simple::h323_stream", map_absolute_name(st_def))) {
		hserv << "virtual CCMStream::h323Stream_ptr" << endl;
		hserv << map_absolute_under_name(component_def)  << "_provide_" << (*act_sisos)[siso_n]->name();
		hserv << "() = 0;" << endl;

		hserv << "virtual void" << endl;
		hserv << map_absolute_under_name(component_def)  << "_connect_" << (*act_sisos)[siso_n]->name();
		hserv << "( CCMStream::h323Stream_ptr str) = 0;" << endl;

	}
	if (!strcmp("Components::CCMStream::QoSRealStream", map_absolute_name(st_def))) {
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
	handleAttribute(home);
	handleOperation(home);
	handleFactory(home);
	handleFinder(home);
}


void
GeneratorBusinessH::doComposition(CIDL::CompositionDef_ptr composition)
{
	composition_ = CIDL::CompositionDef::_duplicate(composition);
	filename_ = "";

	IR__::Contained_ptr module_def = 0;
	string id = composition->id();
	string::size_type pos = id.find_last_of("/");
	if(pos != string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		filename_ = mapAbsoluteName(module_def, "_");
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
	out << "#include <OB/CORBA.h>\n";
	out << "#include \"" << target_ << "_BUSINESS.h\"\n";
	out << "#include \"RefCountLocalObject.h\"\n";
	out << "#include <string>\n\n\n";
	out.insertUserSection("file_post", 2);

	if(module_def)
	{
		open_module(module_def);
		out << "namespace " << module_def->name() << "\n{\n";
		out.indent();
	}


	CIDL::SegmentDefSeq_var segment_seq = composition->executor()->segments();


	//
	// executor
	//
	string class_name = composition->executor()->name();
	out << "\n//\n// executor\n//\n";
	out << "class " << class_name << "\n";
	out.indent();
	out << ": public virtual CORBA::LocalObject\n";
	out << ", public virtual " << mapScopeName(composition) << "::CCM_" << class_name << "\n";
	out.insertUserSection(string("INHERITANCE_") + class_name, 0);
	out.unindent();
	out << "{\n\n";
	out << "private:\n\n";
	out.indent();
    out << mapLocalName(composition->ccm_component()) << "_Context_var context_;\n\n";
	out.unindent();
	out << "public:\n\n";
	out.indent();
	out << class_name << "();\n";
	out << "~" << class_name << "();\n\n";
	out << "void set_context(" << mapLocalName(composition->ccm_component()) << "_Context_ptr context);\n";
    out << "void configuration_complete();\n";
	out << "void stop();\n";
    out << "void remove();\n";
	need_push_ = true;
	doComponent(composition->ccm_component());
	out.unindent();
	out << "\n";
	out.insertUserSection(class_name);
	out << "};\n\n";


	//
	// segment
	//
	for (CORBA::ULong i = 0; i < segment_seq->length(); i++)
	{
		class_name = segment_seq[i]->name();
		out << "\n//\n// segment\n//\n";
		out << "class " << class_name << "\n";
		out.indent();
		out << ": public virtual CORBA::LocalObject\n";
		out << ", public virtual " << mapScopeName(composition) << "::CCM_" << class_name << "\n";
		out.insertUserSection(string("INHERITANCE_") + class_name, 0);
		out.unindent();
		out << "{\n\n";
		out << "private:\n\n";
		out.indent();
		out << mapLocalName(composition->ccm_component()) << "_Context_var context_;\n\n";
		out.unindent();
		out << "public:\n\n";
		out.indent();
		out << class_name << "();\n";
		out << "~" << class_name << "();\n\n";
		out << "void set_context(" << mapLocalName(composition->ccm_component());
		out << "_Context_ptr context);\n";
		out << "void configuration_complete();\n\n";
		// for each implemented facet
		IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
		for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
		{
			doInterface(provided_seq[ii]->interface_type());
		}
		out.unindent();
		out << "\n";
		out.insertUserSection(class_name);
		out << "};\n\n";
	}


	//
	// executor locator
	//
	class_name = composition->name();
	out << "\n//\n// executor locator\n//\n";
	out << "class " << class_name << "\n";
	out.indent();
	out << ": public virtual CORBA::LocalObject\n";
	out << ", public virtual Components::SessionExecutorLocator\n";
	out.insertUserSection(string("INHERITANCE_") + class_name, 0);
	out.unindent();
	out << "{\n\n";
	out << "private:\n\n";
	out.indent();
    out << mapLocalName(composition->ccm_component()) << "_Context_var context_;\n\n";
	out << composition->executor()->name() << "* component_;\n\n";
	for (CORBA::ULong i = 0; i < segment_seq->length(); i++)	{
		out << segment_seq[i]->name() << "* " << segment_seq[i]->name() << "_;\n\n";
	}
	out.unindent();
	out << "public:\n\n";
	out.indent();
    out << class_name << "();\n";
    out << "~" << class_name << "();\n";
	IR__::InterfaceDef_ptr executor_locator;
	executor_locator = IR__::InterfaceDef::_narrow(repository_->lookup_id("IDL:Components/SessionExecutorLocator:1.0"));
	doInterface(executor_locator);
	out.unindent();
	out << "\n";
	out.insertUserSection(class_name);
	out << "};\n\n";
	

	//
	// home executor
	//
	class_name = composition->home_executor()->name();
	out << "\n//\n// home executor\n//\n";
	out << "class " << class_name << "\n";
	out.indent();
	out << ": public virtual CORBA::LocalObject\n";
	out << ", public virtual " << mapLocalName(composition->ccm_home()) << "\n";
	out.insertUserSection(string("INHERITANCE_") + class_name, 0);
	out.unindent();
	out << "{\n\n";
	out << "private:\n\n";
	out.indent();
    out << "Components::CCMContext_ptr context_;\n\n";
	out.unindent();
	out << "public:\n";
	out.indent();
    out << class_name << "();\n";
    out << "~" << class_name << "();\n\n";
	out << "//\n// IDL:Components/HomeExecutorBase/set_context:1.0\n//\n";
    out << "virtual void set_context (Components::CCMContext_ptr ctx);\n\n";
    out << "//\n// IDL:.../create:1.0\n//\n";
    out << "virtual ::Components::ExecutorLocator_ptr create();\n";
	doHome(composition->ccm_home());
	out.unindent();
	out << "\n";
	out.insertUserSection(class_name);
	out << "};\n\n";


	// close namespace
	if(module_def)
	{
		out.unindent();
		out << "};\n";
		close_module(module_def);
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

	out << "#endif";
	out.close();
}

} //