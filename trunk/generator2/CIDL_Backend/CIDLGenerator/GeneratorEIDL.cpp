#include "GeneratorEIDL.h"
#include "Debug.h"

#include <string>


namespace QEDO_CIDL_Generator {


GeneratorEIDL::GeneratorEIDL
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: IDLBase(repository)
{
}


GeneratorEIDL::~GeneratorEIDL
()
{
}


void
GeneratorEIDL::checkForInclude(CORBA::TypeCode_ptr type)
{
	switch(type->kind())
    {
    case CORBA::tk_objref:
    case CORBA::tk_abstract_interface:
    case CORBA::tk_local_interface:
    case CORBA::tk_native:
    case CORBA::tk_struct:
    case CORBA::tk_except:
	case CORBA::tk_union:
	case CORBA::tk_enum:
	case CORBA::tk_sequence:
    case CORBA::tk_array:
	case CORBA::tk_alias:
    case CORBA::tk_value_box:
	case CORBA::tk_value:
		{
			// compare the id of the type with that of the target
			std::string id = type->id();
			std::string::size_type len = target_scope_id_.size() -4;
			if(! id.compare(0, len, target_scope_id_, 0, len))
			{
				// type is from another module than target
				id.erase(0, 4);
				len = id.find_first_of("/:");
				id.erase(len, std::string::npos);
		
				// already included ?
				if(id.compare("CORBA"))
				{
				}
				else if(includes_.find(id) == includes_.end())
				{
					includes_[id + ".h"] = true;
				}
			}
			break;
		}
    default: {}
    }
}


void
GeneratorEIDL::beginModule(IR__::ModuleDef_ptr module)
{	
	out << "//\n// " << module->id() << "\n//\n";
	out << "module " << module->name() << " {\n\n";
	out.indent();

	// forward declaration for interfaces and components
	out << "// forward declarations\n";
	IR__::ContainedSeq_var contained_seq = module->contents(CORBA__::dk_Interface, true);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		out << "interface " << (*contained_seq)[i]->name() << ";\n";
	}

	contained_seq = module->contents(CORBA__::dk_Component, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		out << "interface " << (*contained_seq)[i]->name() << ";\n";
	}
	out << "\n";
};


void
GeneratorEIDL::endModule(IR__::ModuleDef_ptr module)
{	
	out.unindent();
	out << "}; // module " << module->name() << "\n\n";
};


void
GeneratorEIDL::beginInterface(IR__::InterfaceDef_ptr intface)
{	
	out << "//\n// " << intface->id() << "\n//\n";
	out << "interface " << intface->name();
	
	//
	// base interfaces
	//
	IR__::InterfaceDefSeq_var base_seq = intface->base_interfaces();
	CORBA::ULong len = base_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		checkForInclude((*base_seq)[i]->type());

		if(i)
		{
			out << ", ";
		}
		else
		{
			out << " : ";
		}
		out << map_absolute_name((*base_seq)[i]);
	}
	out << "\n{\n";
	out.indent();
};


void
GeneratorEIDL::endInterface(IR__::InterfaceDef_ptr intface)
{	
	out.unindent();
	out << "};\n\n";
};


void
GeneratorEIDL::beginHome(IR__::HomeDef_ptr home)
{	
	checkForInclude(home->managed_component()->type());

	//
	// implicit home
	//
	out << "//\n// implicit home for " << home->id() << "\n//\n";
	out << "interface " << home->name() << "Implicit : ::Components::KeylessCCMHome\n";
	out << "{\n";
	out.indent();
	out << map_absolute_name(home->managed_component()) << " create();\n";
	out.unindent();
	out << "};\n\n";

	//
	// explicit home
	//
	out << "//\n// explicit home for " << home->id() << "\n//\n";
	out << "interface " << home->name() << "Explicit : ";
	IR__::HomeDef_var base = home->base_home();
	if(base)
	{
		checkForInclude(base->type());
		out << map_absolute_name(base);
	}
	else
	{
		out << "::Components::CCMHome";
	}
	
	out << "\n{\n";
	out.indent();

	managed_component_ = map_absolute_name(home->managed_component());
};


void
GeneratorEIDL::endHome(IR__::HomeDef_ptr home)
{
	out.unindent();
	out << "};\n\n";
	
	//
	// home
	//
	out << "//\n// " << home->id() << "\n//\n";
	out << "interface " << home->name() << " : " << home->name() << "Implicit, ";
	out << home->name() << "Explicit\n{\n};\n\n";
};


void
GeneratorEIDL::doAttribute(IR__::AttributeDef_ptr attribute)
{
	checkForInclude(attribute->type());
	out << "\n//\n// " << attribute->id() << "\n//\n";

	// attribute mode
	if(attribute->mode() == IR__::ATTR_READONLY)
	{
		out << "readonly ";
	}

	out << "attribute " << tcToName(attribute->type()) << " " << attribute->name();

	// exceptions
	IR__::ExceptionDefSeq_var exception_seq = attribute->get_exceptions();
	for(CORBA::ULong i = 0; i < exception_seq->length(); i++)
	{
	}

	out << ";\n";
}


void
GeneratorEIDL::doOperation(IR__::OperationDef_ptr operation)
{
	out << "\n//\n// " << operation->id() << "\n//\n";

	// operation mode
	if(operation->mode() == IR__::OP_ONEWAY)
	{
		out << "oneway ";
	}
	
	checkForInclude(operation->result());
	out << tcToName(operation->result()) << " " << operation->name() << "(";

	// parameters
	IR__::ParDescriptionSeq_var para_seq = operation->params();
	CORBA::ULong len = para_seq->length();
	for(CORBA::ULong i = len; i > 0; i--)
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

		checkForInclude((*para_seq)[i - 1].type);
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

		checkForInclude((*exception_seq)[i]->type());
		out << tcToName((*exception_seq)[i]->type());
	}
	if(i)
	{
		out << ")";
	}

	out << ";\n";
}


void
GeneratorEIDL::doFactory(IR__::FactoryDef_ptr factory)
{
	out << "\n//\n// " << factory->id() << "\n//\n";
	
	out << managed_component_ << " " << factory->name() << "(";

	// parameters
	IR__::ParDescriptionSeq_var para_seq = factory->params();
	CORBA::ULong len = para_seq->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}

		checkForInclude((*para_seq)[i - 1].type);
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

		checkForInclude((*exception_seq)[i]->type());
		out << tcToName((*exception_seq)[i]->type());
	}
	if(i)
	{
		out << ")";
	}

	out << ";\n";
}


void
GeneratorEIDL::doFinder(IR__::FinderDef_ptr finder)
{
	out << "\n//\n// " << finder->id() << "\n//\n";
	
	out << managed_component_ << " " << finder->name() << "(";

	// parameters
	IR__::ParDescriptionSeq_var para_seq = finder->params();
	CORBA::ULong len = para_seq->length();
	for(CORBA::ULong i = len; i > 0; i--)
	{
		if(i < len)
		{
			out << ", ";
		}

		checkForInclude((*para_seq)[i - 1].type);
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

		checkForInclude((*exception_seq)[i]->type());
		out << tcToName((*exception_seq)[i]->type());
	}
	if(i)
	{
		out << ")";
	}

	out << ";\n";
}


void
GeneratorEIDL::doException(IR__::ExceptionDef_ptr except)
{
	out << "//\n// " << except->id() << "\n//\n";
	out << "exception " << except->name() << "\n{\n";
	out.indent();

	IR__::StructMemberSeq_var member_seq = except->members();
	for(CORBA::ULong i = 0; i < member_seq->length(); i++)
	{
		checkForInclude((*member_seq)[i].type);
		out << string((*member_seq)[i].name) << " " << tcToName((*member_seq)[i].type) << "\n";
	}

	out.unindent();
	out << "};\n\n";
};


void
GeneratorEIDL::beginValue(IR__::ValueDef_ptr value)
{
	out << "//\n// " << value->id() << "\n//\n";
	
	if(value->is_abstract())
	{
		out << "abstract ";
	}
	
	if(value->is_custom())
	{
		out << "custom ";
	}
	
	if(value->is_truncatable())
	{
		out << "truncatable ";
	}
	
	out << "valuetype " << value->name();
	// ACHTUNG HACK fuer event type
	out << " : Components::EventBase\n";
	out << "{\n";
	out.indent();
};


void
GeneratorEIDL::endValue(IR__::ValueDef_ptr value)
{	
	// initializers
	IR__::InitializerSeq_var initializers = value->initializers();
	for(CORBA::ULong i = 0; i < initializers->length(); i++)
	{
		out << "\nfactory " << string((*initializers)[i].name) << "(";
		
		IR__::StructMemberSeq member_seq = (*initializers)[i].members;
		CORBA::ULong len = member_seq.length();
		for(CORBA::ULong ii = len; ii > 0; ii--)
		{
			if(ii < len)
			{
				out << ", ";
			}

			checkForInclude(member_seq[ii - 1].type);
			out << "in " << tcToName(member_seq[ii - 1].type) << " " << string(member_seq[ii - 1].name);
		}

		out << ");\n";
	}
	out.unindent();
	out << "\n};\n\n";

	//
	// event interface
	//
	out << "interface " << value->name() << "Consumer : Components::EventConsumerBase\n{\n";
	out.indent();
	out << "void " << "push_" << value->name() << "(in " << value->name() << " ev);\n";
	out.unindent();
	out << "};\n\n";
};


void
GeneratorEIDL::doValueMember(IR__::ValueMemberDef_ptr member)
{
	if(member->access() == CORBA__::PRIVATE_MEMBER)
	{
		out << "privat ";
	}
	else
	{
		out << "public ";
	}
	
	checkForInclude(member->type());
	out << tcToName(member->type()) << " " << member->name() << ";\n";
};


void
GeneratorEIDL::doEnum(IR__::EnumDef_ptr enumeration)
{
	out << "//\n// " << enumeration->id() << "\n//\n";
	out << "enum " << enumeration->name() << "\n{\n";
	out.indent();

	IR__::EnumMemberSeq_var member_seq = enumeration->members();
	for(CORBA::ULong i = 0; i < member_seq->length(); i++)
	{
		if(i)
		{
			out << ",\n"; 
		}
		out << string((*member_seq)[i]);
	}

	out.unindent();
	out << "\n};\n\n";
};


void
GeneratorEIDL::open_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module)
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->open_module(act_mod);
		out << "module " << act_mod->name() << " {\n";
	}
};


void
GeneratorEIDL::close_module(IR__::Contained* cur_cont) 
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) 
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->close_module(act_mod);
		out <<  "};\n";
	}

};


void
GeneratorEIDL::beginComponent(IR__::ComponentDef_ptr component)
{
	out << "//\n// " << component->id() << "\n//\n";
	out << "interface " << component->name() << " : ";
	
	// base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{
		checkForInclude(base->type());
		out << map_absolute_name(base);
	}
	else
	{
		out << "::Components::CCMObject";
	}

	// supported interfaces
	IR__::InterfaceDefSeq_var supported_seq = component->supported_interfaces();
	CORBA::ULong len = supported_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		checkForInclude((*supported_seq)[i]->type());
		out << ", " << map_absolute_name((*supported_seq)[i]);
	}
	out << "\n{\n";
	out.indent();
}


void 
GeneratorEIDL::endComponent(IR__::ComponentDef_ptr component)
{
	out.unindent();
	out << "};\n\n";
}


void
GeneratorEIDL::doProvides(IR__::ProvidesDef_ptr provides)
{
	out << "\n//\n// " << provides->id() << "\n//\n";
	
	checkForInclude(provides->interface_type()->type());
	out << provides->interface_type()->name() << " provide_" << provides->name() << "();\n";
}


void
GeneratorEIDL::doUses(IR__::UsesDef_ptr uses)
{
	out << "\n//\n// " << uses->id() << "\n//\n";
	checkForInclude(uses->interface_type()->type());

	//
	// multiple
	//
	if(uses->is_multiple() == true)
	{
		out << "struct " << uses->name() << "Connection {\n";
		out.indent();
		out << uses->interface_type()->absolute_name() << " objref;\n";
		out << "Components::Cookie ck;\n";
		out.unindent();
		out << "};\n";
		out << "typedef sequence < " << uses->name() << "Connection > " << uses->name() << "Connections;\n\n";
			
		out << "Components::Cookie " << "connect_" << uses->name();
		out << "( in " << uses->interface_type()->absolute_name() << " conx)\n";
		out << "    raises (Components::ExceededConnectionLimit, Components::InvalidConnection);\n\n";
			
		out << uses->interface_type()->absolute_name() << " disconnect_" << uses->name();
		out << "(in Components::Cookie ck)\n";
		out << "    raises (Components::InvalidConnection);\n\n";

		out << uses->name() << "Connections " << "get_connections_" << uses->name() << "();\n\n";
	}
	//
	// not multiple
	//
	else
	{
		out << uses->interface_type()->name() << " get_connection_" << uses->name() << "();\n";
		
		out << uses->interface_type()->name() << " disconnect_" << uses->name();
		out << "() raises (::Components::NoConnection);\n";
		
		out << "void connect_" << uses->name() << "(in " << uses->interface_type()->name();
		out << " conxn) raises (::Components::AlreadyConnected, ::Components::InvalidConnection);\n";
	}
}


void
GeneratorEIDL::doEmits(IR__::EmitsDef_ptr emits)
{
	out << "\n//\n// " << emits->id() << "\n//\n";
	checkForInclude(emits->event()->type());

	out << "void " << "connect_" << emits->name();
	out << "(in " << map_absolute_name(emits->event()) << "Consumer consumer);\n\n";

	out << map_absolute_name(emits->event()) << "Consumer" << " disconnect_" << emits->name();
	out << "();\n\n";
}


void
GeneratorEIDL::doPublishes(IR__::PublishesDef_ptr publishes)
{
	out << "\n//\n// " << publishes->id() << "\n//\n";
	checkForInclude(publishes->event()->type());

	out << "Components::Cookie" << " subscribe_" << publishes->name();
	out << "( in " << map_absolute_name(publishes->event()) << "Consumer";
	out << " consumer);\n\n";

	out << map_absolute_name(publishes->event()) << "Consumer ";
	out << "unsubscribe_" << publishes->name() << "(in Components::Cookie ck);\n\n";
}


void
GeneratorEIDL::doConsumes(IR__::ConsumesDef_ptr consumes)
{
	out << "//\n// " << consumes->id() << "\n//\n";
	checkForInclude(consumes->event()->type());

	out << map_absolute_name(consumes->event()) << "Consumer get_consumer_" << consumes->name() << "();\n\n";
}


void
GeneratorEIDL::doSink(IR__::SinkDef_ptr sink)
{
	out << "//\n// " << sink->id() << "\n//\n";

	IR__::StreamTypeDef* st_def = sink->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", map_absolute_name(st_def)))
	{
		out << "void " << "connect_" << sink->name() << "(in CCMStream::h323Stream str);\n";

		out << "CCMStream::h323Stream " << "disconnect_" << sink->name() << "();\n";

	}
	if (!strcmp("Components::CCMStream::QoSRealStream", map_absolute_name(st_def)))
	{
		out << "void " << "connect_" << sink->name() << "(in CCMStream::QoSRealStream str);\n";
	}
}


void
GeneratorEIDL::doSource(IR__::SourceDef_ptr source)
{
	out << "//\n// " << source->id() << "\n//\n";

	IR__::StreamTypeDef* st_def = source->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", map_absolute_name(st_def)))
	{
		out << "CCMStream::h323Stream" << " provide_" << source->name() << "();\n";
	}
	if (!strcmp("Components::CCMStream::QoSRealStream", map_absolute_name(st_def)))
	{
		out << "CCMStream::QoSRealStream" << " provide_" << source->name() << "();\n";
	}
}


void
GeneratorEIDL::doSiSo(IR__::SiSoDef_ptr siso)
{
	out << "//\n// " << siso->id() << "\n//\n";

	IR__::StreamTypeDef* st_def = siso->stream_type();
	IR__::Contained::Description* c_descr = st_def->describe(); 
	IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("simple::h323_stream", map_absolute_name(st_def)))
	{
		out << "CCMStream::h323Stream" << " provide_" << siso->name() << "();\n";

		out << "void" << " connect_" << siso->name() << "(in CCMStream::h323Stream str);\n";
	}
	if (!strcmp("Components::CCMStream::QoSRealStream", map_absolute_name(st_def)))
	{
		out << "CCMStream::QoSRealStream" << " provide_" << siso->name() << "();\n";

		out << "void" << " connect_" << siso->name() << "(in CCMStream::QoSRealStream str);\n";
	}
}


void
GeneratorEIDL::doComposition(CIDL::CompositionDef_ptr composition)
{
}


void
GeneratorEIDL::generate(string target)
{
	//
	// write temp file without includes
	//
	filename_ = target + "_EQUIVALENT.idl";
	string temp_filename = filename_ + ".temp";
	out.open(temp_filename.c_str());
	doGenerate(target);
	out.close();


	//
	// insert includes
	//
	std::ifstream temp_file;
	temp_file.open(temp_filename.c_str());
	out.open(filename_.c_str());
	out << "#ifndef __" << target << "_EQUIVALENT_IDL\n";
	out << "#define __" << target << "_EQUIVALENT_IDL\n\n";
	out << "#include \"Components.idl\"\n";
	
	std::map < std::string, bool > ::iterator it;
	for(it = includes_.begin(); it != includes_.end(); it++)
	{
		out << "#include \"" << it->first << "\";\n";
	}
	out << "\n";

	out << temp_file;
	out << "\n#endif\n";
	out.close();
	temp_file.close();
	_unlink(temp_filename.c_str());
}


} // namespace HU_CIDL_Generator