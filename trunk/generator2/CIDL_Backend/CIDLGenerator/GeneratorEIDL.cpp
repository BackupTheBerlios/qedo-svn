#include "GeneratorEIDL.h"
#include "Debug.h"

#include <string>

#ifdef WIN32
#define unlink _unlink
#else
#include <unistd.h>
#endif

namespace QEDO_CIDL_Generator {


GeneratorEIDL::GeneratorEIDL
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: IDLBase(repository), m_recursion_set()
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
		{/*
			// compare the id of the type with that of the target
			std::string id = type->id();
			std::string::size_type len = target_scope_id_.size() - 4;
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
			}*/
			break;
		}
    default: {}
    }
}


void
GeneratorEIDL::check_for_generation ( IR__::Contained_ptr item )
{
	//
	// check if item is already known
	//
	IR__::Contained_var restricted_contained = IR__::Contained::_narrow(item->defined_in());
	if (!CORBA::is_nil(restricted_contained )) {

		if (!strcmp(restricted_contained ->id(), "IDL:Deployment:1.0")) {
			return;
		};
		if (!strcmp(restricted_contained ->id(), "IDL:omg.org/Components:1.0")) {
			return;
		};
		if (!strcmp(restricted_contained ->id(), "IDL:Components:1.0")) {
			return;
		}
		if (!strcmp(restricted_contained ->id(), "IDL:omg.org/CORBA:1.0")) {
			return;
		};
		if (!strcmp(restricted_contained ->id(), "IDL:CORBA:1.0")) {
			return;
		}
		if (!strcmp(restricted_contained ->id(), "IDL:omg.org/CosPropertyService:1.0")) {
			return;
		};
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
IR__::ModuleDef_var act_module2;
IR__::ComponentDef_var act_component;
IR__::ComponentDef_var base_component;
IR__::HomeDef_var act_home;
IR__::HomeDef_var base_home;
IR__::InterfaceDef_var act_interface;
IR__::InterfaceDefSeq_var interf_seq;
IR__::OperationDef_var act_operation;
IR__::IDLType_var act_idl_type;
IR__::Contained_var return_contained;
IR__::Contained_var contained_type ;
IR__::AttributeDef_var act_attribute;
IR__::PublishesDefSeq_var publish_seq;
IR__::ConsumesDefSeq_var consumes_seq;
IR__::EmitsDefSeq_var emits_seq;
IR__::ParDescriptionSeq_var act_params;
IR__::ProvidesDefSeq_var provides_seq;
IR__::UsesDefSeq_var uses_seq;
IR__::ExceptionDefSeq_var act_exceptions;
IR__::ExceptionDef_var act_exception;
IR__::StructMemberSeq_var act_struct_members;
IR__::ValueDef_var act_value;
IR__::StructDef_var act_struct;
IR__::AliasDef_var act_alias;
IR__::Contained_var act_contained;
	CIDL::CompositionDef_var a_composition;

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
			a_composition = CIDL::CompositionDef::_narrow((*contained_seq)[i]);
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
	case CORBA__::dk_Composition : {
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(item);

		// home
		check_for_generation(a_composition->ccm_home());

		break; }
	case CORBA__::dk_Home:
		act_home = IR__::HomeDef::_narrow(item);
		
		// base home
		base_home = act_home->base_home();
		if (!CORBA::is_nil(base_home)) {
			this->check_for_generation(base_home);
		}

		// supported interfaces
		interf_seq = act_home->supported_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		}

		// operations
		contained_seq = act_home->contents(CORBA__::dk_Operation, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// factories
		contained_seq = act_home->contents(CORBA__::dk_Factory, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			//check_for_generation((*contained_seq)[i]);
		}

		// finders
		contained_seq = act_home->contents(CORBA__::dk_Finder, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			//check_for_generation((*contained_seq)[i]);
		}

		// attributes
		contained_seq = act_home->contents(CORBA__::dk_Attribute, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// managed component
		act_component = act_home->managed_component();
		this->check_for_generation(act_component);

		insert_to_generate(item);
		break;
	case CORBA__::dk_Component:
		act_component = IR__::ComponentDef::_narrow(item);

		// base component
		base_component = act_component->base_component();
		if ( ! CORBA::is_nil(base_component)) {
			this->check_for_generation(base_component);
		}

		// supported interfaces
		interf_seq = act_component->supported_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		}

		// attributes
		contained_seq = act_component->contents(CORBA__::dk_Attribute, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}
		
		// provided interfaces
		provides_seq = act_component->provides_interfaces();
		len = provides_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*provides_seq)[i]->interface_type());
		}

		// used interfaces
		uses_seq = act_component->uses_interfaces();
		len = uses_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*uses_seq)[i]->interface_type());
		}

		// emits_events
		emits_seq = act_component->emits_events();
		len = emits_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*emits_seq)[i]->event());
		};

		// publish events
		publish_seq = act_component->publishes_events();
		len = publish_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*publish_seq)[i]->event());
		};

		// consumes_events
		consumes_seq = act_component->consumes_events();
		len = consumes_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*consumes_seq)[i]->event());
		};

		// sinks

		// sources

		// sisos

		this->insert_to_generate ( item );
		break;
	case CORBA__::dk_Interface:
		act_interface = IR__::InterfaceDef::_narrow(item);
		
		// base interfaces
		interf_seq = act_interface->base_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
			//this->insert_to_generate((*interf_seq)[i]);
		};

		// atributes
		contained_seq = act_interface->contents(CORBA__::dk_Attribute, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// operations
		contained_seq = act_interface->contents(CORBA__::dk_Operation, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		this->insert_to_generate(item);
		break;
	case CORBA__::dk_Value:
		act_value = IR__::ValueDef::_narrow(item);

		// base value

		// supports

		// members
		contained_seq = act_value->contents(CORBA__::dk_ValueMember, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			IR__::ValueMemberDef_var act_valuemember = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
			act_idl_type = act_valuemember->type_def();
			try {
				contained_type = IR__::Contained::_narrow(act_idl_type);
			
				if (!CORBA::is_nil(contained_type)) {
					this->check_for_generation (contained_type );
				};
				} catch (...) {}
		}

		// attribute
		contained_seq = act_value->contents(CORBA__::dk_Attribute, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);

		}

		this->insert_to_generate ( act_value );
		break;
	case CORBA__::dk_Struct:
		act_struct = IR__::StructDef::_narrow(item);

		// members
		act_struct_members = act_struct->members();
		len = act_struct_members->length();
		for(i = 0; i < len; i++)
		{
			act_idl_type = (*act_struct_members)[i].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation (contained_type );
			};
		};

		this->insert_to_generate(item);
		break;
	case CORBA__::dk_Sequence :
		break;
	case CORBA__::dk_Operation :
	case CORBA__::dk_Factory :
	case CORBA__::dk_Finder :
		act_operation = IR__::OperationDef::_narrow(item);

		// return value
		act_idl_type = act_operation->result_def();
		return_contained = IR__::Contained::_narrow(act_idl_type);
		if (!CORBA::is_nil(return_contained)) {
			this->check_for_generation (return_contained );
		}		

		// parameters
		act_params = act_operation -> params();
		len = act_params->length();
		for(i = 0; i < len; i++)
		{
			act_idl_type = (*act_params)[i].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation(contained_type);
			};
		};

		// exceptions
		act_exceptions = act_operation->exceptions();
		len = act_exceptions->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*act_exceptions)[i]);
		};

		// not included itself
		break;
	case CORBA__::dk_Exception:
		act_exception = IR__::ExceptionDef::_narrow(item);

		// members 
		act_struct_members = act_exception->members();
		len = act_struct_members->length();
		for(i = 0; i < len; i++)
		{
			act_idl_type = (*act_struct_members)[i].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation (contained_type );
			};
		};
		
		this->insert_to_generate(act_exception);
		break;
	case CORBA__::dk_Attribute:
		act_attribute = IR__::AttributeDef::_narrow(item);
		
		// type
		act_idl_type = act_attribute->type_def ();
		contained_type = IR__::Contained::_narrow(act_idl_type);
		if (!CORBA::is_nil(contained_type)) {
			this->check_for_generation(contained_type);
		};

		// exceptions

		// the attribute itself must not added to the generation list.
		break;
	case CORBA__::dk_Enum:
		this->insert_to_generate(item);
		break;
	case CORBA__::dk_Alias:
		act_alias = IR__::AliasDef::_narrow(item);
		if (act_alias -> original_type_def() -> def_kind() == CORBA__::dk_Sequence) {
			IR__::SequenceDef_var seq = IR__::SequenceDef::_narrow(act_alias->original_type_def());
			act_contained = IR__::Contained::_narrow(seq-> element_type_def () );
			if (!CORBA::is_nil(act_contained)) {
				this->check_for_generation( act_contained);
			}
		}

		this->insert_to_generate(item);
		break;
	default:
		break;
	};

	m_recursion_set.erase(item->id());
};


/*
GeneratorEIDL::open_scope(IR__::Contained_ptr item) {

};


GeneratorEIDL::close_scope(IR__::Contained_ptr item) {

};
*/

//
// module
//
void
GeneratorEIDL::doModule(IR__::ModuleDef_ptr module)
{
	beginModule ( module );
	endModule ( module );
};

void
GeneratorEIDL::beginModule(IR__::ModuleDef_ptr module)
{	
/*
	out << "//\n// " << module->id() << "\n//\n";
	out << "module " << module->name() << " {\n\n";
	out.indent();

	// forward declaration for interfaces and components
	out << "// forward declarations\n";
	IR__::ContainedSeq_var contained_seq;
	//= module->contents(CORBA__::dk_Interface, true);
	CORBA::ULong len = m_to_generate_seq->length();
	CORBA::ULong i;
	for( i= 0; i < len; i++)
	{
		if ((*m_to_generate_seq)[i]->describe()->kind == CORBA__::dk_Interface) 
		out << "interface " << (*m_to_generate_seq)[i]->name() << ";\n";
		if ((*m_to_generate_seq)[i]->describe()->kind == CORBA__::dk_Component) 
		out << "interface " << (*m_to_generate_seq)[i]->name() << ";\n";

	}

	out << "\n";
	*/
};


void
GeneratorEIDL::endModule(IR__::ModuleDef_ptr module)
{	
	/*
	out.unindent();
	out << "}; // module " << module->name() << "\n\n";
*/
};


void
GeneratorEIDL::doInterface(IR__::InterfaceDef_ptr intface)
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

	// contained constants
	handleConstant(intface);

	// contained typedefs
	handleTypedef(intface);

	// contained exceptions
	handleException(intface);

	// contained attributes
	handleAttribute(intface);

	// contained operations
	handleOperation(intface);

	out.unindent();
	out << "};\n\n";
}


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
	CORBA::ULong i;
	for( i= len; i > 0; i--)
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
	CORBA::ULong i;
	for( i= len; i > 0; i--)
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
		out << tcToName((*member_seq)[i].type) << " " << string((*member_seq)[i].name) << ";\n";
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
	//supports operations ???
	out << " {\n";
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

};

void
GeneratorEIDL::beginEvent(IR__::ValueDef_ptr value)
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
GeneratorEIDL::endEvent(IR__::ValueDef_ptr value)
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
		out << "private ";
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
GeneratorEIDL::doTypedef(IR__::TypedefDef_ptr tdef)
{
	out << "typedef " << tdef -> type() -> name () << " " << tdef->name() << ";\n";
}

//
// alias
//
void
GeneratorEIDL::doAlias(IR__::AliasDef_ptr adef)
{
//	out << "typedef " << adef -> type () -> name () << " " << adef->name() << ";\n";
	if (adef -> original_type_def() -> def_kind() == CORBA__::dk_Sequence) {
		IR__::SequenceDef_var seq = IR__::SequenceDef::_narrow(adef->original_type_def());
		out << "typedef sequence<" << tcToName(seq-> element_type () ) << "> " << adef -> name () << ";\n";
	}
		if (adef -> original_type_def() -> def_kind() == CORBA__::dk_Primitive) {
		IR__::PrimitiveDef_var prim = IR__::PrimitiveDef::_narrow(adef->original_type_def());
		out << "typedef " << tcToName(prim->type () ) <<" " << adef -> name () << ";\n";
	}
}

//
// struct
//
void
GeneratorEIDL::doStruct(IR__::StructDef_ptr sdef)
{
	out << "struct " << sdef -> name () << "{\n";
	IR__::StructMemberSeq_var str_seq = sdef->members();
	CORBA::ULong len = str_seq->length();
	for (CORBA::ULong i = 0; i < len; i++) {
		out << "   " << tcToName(str_seq[i].type) << " " << str_seq[i].name.in() << ";\n";
	};
	out << "};\n";
}


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
	out << provides->interface_type()->absolute_name() << " provide_" << provides->name() << "();\n";
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
	const IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("QedoStream::h323_stream", map_absolute_name(st_def)))
	{
		out << "void " << "connect_" << sink->name() << "(in Components::QedoStreams::H323Streamconnection str);\n";

		out << "Components::QedoStreams::H323Streamconnection " << "disconnect_" << sink->name() << "();\n";

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
	const IR__::StreamTypeDescription* st_descr;
	(c_descr->value) >>= st_descr;
	if (!strcmp("QedoStream::h323_stream", map_absolute_name(st_def)))
	{
		out << "Components::QedoStreams::H323Streamconnection" << " provide_" << source->name() << "();\n";
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
	const IR__::StreamTypeDescription* st_descr;
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
	// TODO
}


void
GeneratorEIDL::generate(std::string target, std::string fileprefix)
{
	initialize(target, fileprefix);
	
	//
	// open temp file without includes
	//
	filename_ = file_prefix_ + "_EQUIVALENT.idl";
	string temp_filename = filename_ + ".temp";
	out.open(temp_filename.c_str());

	//
	// forward declarations
	//
	out << "//\n// forward declarations\n//\n"; 
	CORBA::ULong len = m_to_generate_seq->length();
	CORBA::ULong i;
	for(i = 0; i < len; i++)
	{
		if ((*m_to_generate_seq)[i]->describe()->kind == CORBA__::dk_Interface) {
			open_module((*m_to_generate_seq)[i]);
			out << "interface " << (*m_to_generate_seq)[i]->name() << ";\n";
			close_module((*m_to_generate_seq)[i]);
		}
		if ((*m_to_generate_seq)[i]->describe()->kind == CORBA__::dk_Component) {
			open_module((*m_to_generate_seq)[i]);
			out << "interface " << (*m_to_generate_seq)[i]->name() << ";\n";
			close_module((*m_to_generate_seq)[i]);
		};
	}
	out << "\n";

	//
	// generate
	//
	doGenerate();
	out.close();

	//
	// insert includes
	//
	std::ifstream temp_file;
	temp_file.open(temp_filename.c_str());
	out.open(filename_.c_str());
	out << "#ifndef __" << file_prefix_ << "_EQUIVALENT_IDL\n";
	out << "#define __" << file_prefix_ << "_EQUIVALENT_IDL\n\n";
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
	unlink(temp_filename.c_str());
}


} // namespace HU_CIDL_Generator

