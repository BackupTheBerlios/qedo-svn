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
GeneratorLIDL::beginModule(IR__::ModuleDef_ptr module)
{	
	out << "//\n// " << module->id() << "\n//\n";
	out << "module " << module->name() << " {\n\n";
	out.indent();
};


void
GeneratorLIDL::endModule(IR__::ModuleDef_ptr module)
{	
	out.unindent();
	out << "}; // module " << module->name() << "\n\n";
};


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
	out << "//\n// " << value->id() << "\n//\n";
	out << "local interface CCM_" << value->name() << "Consumer : ";
	out << map_absolute_name(value) << "Consumer, ::Components::EnterpriseComponent\n{\n";
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
	for(CORBA::ULong i = 0; i < exception_seq->length(); i++)
	{
	}

	out << ";\n";
}


void
GeneratorLIDL::doComponent(IR__::ComponentDef_ptr component)
{
	component_ = IR__::ComponentDef::_duplicate(component);

	//
	// executor
	//
	out << "//\n// executor for " << component->id() << "\n//\n";
	out << "local interface CCM_" << component->name() << "_Executor : ";
	
	// base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{
		out << mapLocalName(base) << "_Executor";
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
		for(CORBA::ULong i = 0; i < len; i++)
		{
			out << ", " << map_absolute_name((*supported_seq)[i]);
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
		out << mapLocalName(base) << "_Context";
	}
	else
	{
		out << "::Components::SessionContext";
	}
	out << "\n{\n";
	out.indent();

	handleUses(component);
	handleEmits(component);
	handlePublishes(component);

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
	out << "::Components::EnterpriseComponent create();\n";
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
		out << mapLocalName(base);
	}
	else
	{
		out << "::Components::HomeExecutorBase";
	}
	
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
	for(CORBA::ULong i = len; i > 0; i--)
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
	for(CORBA::ULong i = len; i > 0; i--)
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
GeneratorLIDL::doUses(IR__::UsesDef_ptr uses)
{
	out << "\n//\n// " << uses->id() << "\n//\n";

	// multiple
	if(uses->is_multiple() == true)
	{
		out << map_absolute_name(component_) << "::" << uses->name() << "Connections ";
		out << "get_connections_" << uses->name() << "();\n";
	}
	// not multiple
	else
	{
		out << map_absolute_name(uses->interface_type()) << " get_connection_" << uses->name() << "();\n";
	}
}


void
GeneratorLIDL::doEmits(IR__::EmitsDef_ptr emits)
{
	out << "\n//\n// " << emits->id() << "\n//\n";
	
	out << "void push_" << emits->name() << "(in " << map_absolute_name(emits->event()) << " evt);\n";
}


void
GeneratorLIDL::doPublishes(IR__::PublishesDef_ptr publishes)
{
	out << "\n//\n// " << publishes->id() << "\n//\n";

	out << "void push_" << publishes->name() << "(in " << map_absolute_name(publishes->event()) << " evt);\n";
}


void
GeneratorLIDL::open_module(IR__::Contained* cur_cont)
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
GeneratorLIDL::close_module(IR__::Contained* cur_cont)
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
GeneratorLIDL::generate(string target)
{
	filename_ = target + "_LOCAL.idl";
	
	out.open(filename_.c_str());
	out << "#ifndef __" << target << "_LOCAL_IDL\n";
	out << "#define __" << target << "_LOCAL_IDL\n";
	out << "\n#include \"" << target << "_EQUIVALENT.idl\"\n\n\n";
	out << "// local interfaces\n\n";

	doGenerate(target);

	out << "\n#endif\n";
	out.close();
}
	

} //