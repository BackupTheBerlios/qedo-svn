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
: IDLBase(repository), m_recursion_stack()
{
	m_to_generate_seq = new IR__::ContainedSeq();
	m_to_generate_seq->length(0);

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
			}
			break;
		}
    default: {}
    }
}

bool
GeneratorEIDL::already_included (IR__::Contained_ptr item) {
	CORBA::ULong i;
	CORBA::ULong len;

	len = m_to_generate_seq -> length();
	if (len == 0 ) 
		return false;
	for (i = 0 ; i < len ; i++) {
		if (!strcmp((*m_to_generate_seq)[i]->id(), item->id())) {
			return true;
		};
	};
	return false;
};

void 
GeneratorEIDL::insert_to_generate(IR__::Contained_ptr item) {

	// test if it is under the target

	// or test if it is not in standard Modules as CORBA or Components


	switch (item->def_kind()) {
	case CORBA__::dk_Operation:

		return;
		break;
	case CORBA__::dk_Value:
	case CORBA__::dk_Component:
	case CORBA__::dk_Home:
	case CORBA__::dk_Interface:
	case CORBA__::dk_Exception:
	case CORBA__::dk_Enum:
	case CORBA__::dk_Module:
		// check if already included in the list
		if (this->already_included (item)) {
			return;
		};
		// insert the  item
		m_to_generate_seq->length(m_to_generate_seq->length()+1);
		m_to_generate_seq[m_to_generate_seq->length()-1] = IR__::Contained::_duplicate( item );
		break;
	default:
		return;
	}
};


void
GeneratorEIDL::check_for_generation ( IR__::Contained_ptr item ) {

// stop never ending recursion by checkin if already included
if ((this->m_recursion_stack.find(item->id())) == m_recursion_stack.end()) {
	m_recursion_stack.insert(item->id());
} else {
	return;
};;

//
CORBA::ULong len;
CORBA::ULong i;
CORBA::ULong len2;
CORBA::ULong i2;

IR__::ContainedSeq_var contained_seq2;

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
IR__::ExceptionDefSeq_var act_exceptions;
IR__::ExceptionDef_var act_exception;
IR__::StructMemberSeq_var act_struct_members;
IR__::ValueDef_var act_value;


	switch (item->describe()->kind) {
	case CORBA__::dk_Module:
		act_module = IR__::ModuleDef::_narrow(item);

		//	traverse module
		contained_seq2 = act_module->contents(CORBA__::dk_Module, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			act_module2 = IR__::ModuleDef::_narrow(((*contained_seq2)[i2]));
			check_for_generation(act_module2);
		}
		// check for homes
		contained_seq2 = act_module->contents(CORBA__::dk_Home, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			IR__::HomeDef_var act_home = IR__::HomeDef::_narrow(((*contained_seq2)[i2]));
			check_for_generation(act_home);
		}

		// included modules

		this->insert_to_generate(act_module);

//		this->doModule(act_module);
		break;
	case CORBA__::dk_Home:
		act_home = IR__::HomeDef::_narrow(item);
		
		// traverse Home
		// base home
		base_home = act_home->base_home();
		if (!CORBA::is_nil(base_home)) 
			this->check_for_generation(base_home);

		// supported interfaces
		interf_seq = act_home->supported_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		};

		// factory operations


		// finder operations


		// managed component

		act_component = act_home->managed_component();
		this->check_for_generation(act_component);

		//after traversing the home add it to the generation list
		insert_to_generate ( item );
		break;
	case CORBA__::dk_Component:
		act_component = IR__::ComponentDef::_narrow(item);
		// traverse the component

		//base component
		base_component = act_component->base_component();
		if ( ! CORBA::is_nil(base_component)) {
			this->check_for_generation(base_component);
		}

		// supported interfaces
		interf_seq = act_component->supported_interfaces();
		len2 = interf_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*interf_seq)[i2]);
		};

		// attributes
		// atributes
		contained_seq2 = act_component->contents(CORBA__::dk_Attribute, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			IR__::AttributeDef_var act_attribute = IR__::AttributeDef::_narrow(((*contained_seq2)[i2]));
			check_for_generation(act_attribute);
		}
		

		// provides interfaces
		provides_seq = act_component->provides_interfaces();
		len2 = provides_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*provides_seq)[i2]->interface_type());
//			this->insert_to_generate((*provides_seq)[i2]->interface_type());
		};

		// uses interfaces

		// emits_events
		emits_seq = act_component->emits_events();
		len2 = emits_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*emits_seq)[i2]->event());
//			this->insert_to_generate((*publish_seq)[i2]->event());
		};

		// publish events
		publish_seq = act_component->publishes_events();
		len2 = publish_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*publish_seq)[i2]->event());
//			this->insert_to_generate((*publish_seq)[i2]->event());
		};


		// consumes_events
		consumes_seq = act_component->consumes_events();
		len2 = consumes_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*consumes_seq)[i2]->event());
//			this->insert_to_generate((*consumes_seq)[i2]->event());
		};


		// sinks

		// sources

		// sisos


		/// after traversing the component add it to the generation list
		this->insert_to_generate ( item );
		break;
	case CORBA__::dk_Interface:
		act_interface = IR__::InterfaceDef::_narrow(item);

		// traverse interface
		
		// base interfaces
		interf_seq = act_interface->base_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		};

		// atributes
		contained_seq2 = act_interface->contents(CORBA__::dk_Attribute, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			IR__::AttributeDef_var act_attribute = IR__::AttributeDef::_narrow(((*contained_seq2)[i2]));
			check_for_generation(act_attribute);
		}

		//operationen
		contained_seq2 = act_interface->contents(CORBA__::dk_Operation, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			IR__::OperationDef_var act_operation = IR__::OperationDef::_narrow(((*contained_seq2)[i2]));
			check_for_generation(act_operation);
		}


		// after traversing add it to the genration list.
		this-> insert_to_generate ( item );

		break;
	case CORBA__::dk_Value:
		act_value = IR__::ValueDef::_narrow(item);

		// traverse the value

		// base value

		// supports

		// member
		contained_seq2 = act_value->contents(CORBA__::dk_ValueMember, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			IR__::ValueMemberDef_var act_valuemember = IR__::ValueMemberDef::_narrow(((*contained_seq2)[i2]));
			act_idl_type = act_valuemember->type_def();
			try {
				contained_type = IR__::Contained::_narrow(act_idl_type);
			
				if (!CORBA::is_nil(contained_type)) {
					this->check_for_generation (contained_type );
					this->insert_to_generate(contained_type );
				};
				} catch (...) {}
		}

		// attribute
		contained_seq2 = act_value->contents(CORBA__::dk_Attribute, true);
		len2 = contained_seq2->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			IR__::AttributeDef_var act_attribute = IR__::AttributeDef::_narrow(((*contained_seq2)[i2]));
			check_for_generation(act_attribute);

		}

		// finally insert the value into the list of genration_item

		this->insert_to_generate ( act_value );
		break;

	case CORBA__::dk_Operation:
		act_operation = IR__::OperationDef::_narrow(item);

		// traverse the operation

		// return value
		act_idl_type = act_operation->result_def();
		return_contained = IR__::Contained::_narrow(act_idl_type);

		// check if atomar
		// if not traverse it


		// operation parameters
		act_params = act_operation -> params();
		len2 = act_params->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			act_idl_type = (*act_params)[i2].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation (contained_type );
				this->insert_to_generate(contained_type );
			};
		};

		// operation exceptsion
		act_exceptions = act_operation->exceptions();
		len2 = act_exceptions->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*act_exceptions)[i2]);
		};

		// insert the types into the generated items

		//this->insert_to_generate ( return_contained) ;
		break;
	case CORBA__::dk_Exception:
		act_exception = IR__::ExceptionDef::_narrow(item);

		// traverse 
		act_struct_members = act_exception->members();
		len2 = act_struct_members->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			act_idl_type = (*act_struct_members)[i2].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation (contained_type );
				this->insert_to_generate(contained_type );
			};
		};
		

		this->insert_to_generate(act_exception);
		break;

	case CORBA__::dk_Attribute:
		act_attribute = IR__::AttributeDef::_narrow(item);
		// traverse attribute
		
		//type
		act_idl_type = act_attribute->type_def ();
		contained_type = IR__::Contained::_narrow(act_idl_type);
		if (!CORBA::is_nil(contained_type)) {
			this->check_for_generation (contained_type );
			this->insert_to_generate(contained_type );
		};
		// exceptions

		// the attribute itself must not added to the generation list.
		break;
	case CORBA__::dk_Enum:
		this->insert_to_generate(item);
		break;

	default:
		break;
	};
	m_recursion_stack.erase(item->id());
};


void
GeneratorEIDL::generate_the_item ( IR__::Contained_ptr item ) {
	IR__::HomeDef_var act_home;
	IR__::ComponentDef_var act_component;
	IR__::InterfaceDef_var act_interface;
	IR__::AliasDef_var act_alias;
	IR__::ValueDef_var act_value;
	IR__::EventDef_var act_event;
	IR__::ExceptionDef_var act_exception;
	IR__::EnumDef_var act_enum;
	IR__::ModuleDef_var act_module;

	std::cout << "Debug: item to generate: " << item->name() << std::endl;
	this->open_module (item);
	switch (item->describe()->kind) {
	case CORBA__::dk_Module:
		act_module = IR__::ModuleDef::_narrow(item);
		beginModule (act_module);
		endModule(act_module);
		break;
	case CORBA__::dk_Home:
		act_home = IR__::HomeDef::_narrow(item);
		
		doHome(act_home);
		
		break;
	case CORBA__::dk_Component:
		act_component = IR__::ComponentDef::_narrow(item);
		doComponent(act_component);
		break;
	case CORBA__::dk_Interface:
		act_interface = IR__::InterfaceDef::_narrow(item);
		doInterface ( act_interface );
		break;
	case CORBA__::dk_Value:
		act_event = IR__::EventDef::_narrow(item);
		if (!CORBA::is_nil ( act_event ) ) {
			doEvent ( act_event );
		} else {
			act_value = IR__::ValueDef::_narrow(item);
			doValue(act_value);
		}
		break;
	case CORBA__::dk_Alias:
		act_alias = IR__::AliasDef::_narrow(item);
		doAlias (act_alias);
		break;
	case CORBA__::dk_Exception:
		act_exception = IR__::ExceptionDef::_narrow(item);
		doException(act_exception);
		break;

	case CORBA__::dk_Enum:
		act_enum = IR__::EnumDef::_narrow(item);
		doEnum(act_enum);
		break;

	default:
		break;
		//return;
	};
	this->close_module(item);
	
}

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
	IR__::ContainedSeq_var contained_seq;
	CORBA::ULong len;
	CORBA::ULong i;

/*
	// find  items to generate starting from the components
	contained_seq = module->contents(CORBA__::dk_Home, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::HomeDef_var act_home = IR__::HomeDef::_narrow(((*contained_seq)[i]));
		check_for_generation(act_home);
	}
	contained_seq = module->contents(CORBA__::dk_Module, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ModuleDef_var act_module = IR__::ModuleDef::_narrow(((*contained_seq)[i]));
		check_for_generation(act_module);
	}
*/
	this->check_for_generation(module);

//	beginModule ( module );

	len = m_to_generate_seq->length();
	for (i = 0; i < len ; i++) {
		generate_the_item ((*m_to_generate_seq)[i]);
	}


//	endModule ( module );
};

void
GeneratorEIDL::beginModule(IR__::ModuleDef_ptr module)
{	
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
}


void
GeneratorEIDL::generate(std::string target, std::string fileprefix)
{
	initialize(target, fileprefix);

	//
	// write temp file without includes
	//
	filename_ = file_prefix_ + "_EQUIVALENT.idl";
	string temp_filename = filename_ + ".temp";
	out.open(temp_filename.c_str());
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

