#include "GeneratorLIDL.h"
#include "Debug.h"
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorLIDL::GeneratorLIDL
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: IDLBase(repository)
{
	m_to_generate_seq = new IR__::ContainedSeq();
	m_to_generate_seq->length(0);
}


GeneratorLIDL::~GeneratorLIDL
()
{
}


bool
GeneratorLIDL::already_included (IR__::Contained_ptr item) {
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
GeneratorLIDL::insert_to_generate(IR__::Contained_ptr item) {

	// test if it is under the target

	// or test if it is not in standard Modules as CORBA or Components
	// this will be replace with a test with repositoties of included files

	IR__::Contained_var restricted_contained = IR__::Contained::_narrow(item->defined_in());
	if (!CORBA::is_nil(restricted_contained )) {

		if (!strcmp(restricted_contained ->name(), "Deployment")) {
//			return;
		};
		if (!strcmp(restricted_contained ->name(), "Components")) {
			return;
		};
		if (!strcmp(restricted_contained ->name(), "CORBA")) {
			return;
		};
		if (!strcmp(restricted_contained ->name(), "CosPropertyService")) {
//			return;
		};
	}


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
	case CORBA__::dk_Struct:
	case CORBA__::dk_Alias:
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
GeneratorLIDL::check_for_generation ( IR__::Contained_ptr item ) {

// stop never ending recursion by checkin if already included
if ((this->m_recursion_set.find(item->id())) == m_recursion_set.end()) {
	m_recursion_set.insert(item->id());
} else {
	return;
};
IR__::Contained_var restricted_contained = IR__::Contained::_narrow(item->defined_in());
	if (!CORBA::is_nil(restricted_contained )) {

		if (!strcmp(restricted_contained ->name(), "Deployment")) {
//			return;
		};
		if (!strcmp(restricted_contained ->name(), "Components")) {
			return;
		};
		if (!strcmp(restricted_contained ->name(), "CORBA")) {
			return;
		};
		if (!strcmp(restricted_contained ->name(), "CosPropertyService")) {
//			return;
		};
	}

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
IR__::StructDef_var act_struct;
IR__::AliasDef_var act_alias;
IR__::Contained_var act_contained;

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
			this->insert_to_generate((*publish_seq)[i2]->event());
		};

		// publish events
		publish_seq = act_component->publishes_events();
		len2 = publish_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*publish_seq)[i2]->event());
			this->insert_to_generate((*publish_seq)[i2]->event());
		};


		// consumes_events
		consumes_seq = act_component->consumes_events();
		len2 = consumes_seq->length();
		for(i2 = 0; i2 < len2; i2++) {
			this->check_for_generation((*consumes_seq)[i2]->event());
			this->insert_to_generate((*consumes_seq)[i2]->event());
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
			this->insert_to_generate((*interf_seq)[i]);
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
//					this->insert_to_generate(contained_type );
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

//		this->insert_to_generate ( act_value );
		break;

	case CORBA__::dk_Struct:
		act_struct = IR__::StructDef::_narrow(item);

		//traverse te struct
		act_struct_members = act_struct->members();
		len2 = act_struct_members->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			act_idl_type = (*act_struct_members)[i2].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation (contained_type );
//				this->insert_to_generate(contained_type );
			};
		};
//		this->insert_to_generate(item);
		break;

	case CORBA__::dk_Operation:
		act_operation = IR__::OperationDef::_narrow(item);

		// traverse the operation

		// return value
		act_idl_type = act_operation->result_def();
		return_contained = IR__::Contained::_narrow(act_idl_type);
		if (!CORBA::is_nil(return_contained)) {
			this->check_for_generation (return_contained );
		}		


		// operation parameters
		act_params = act_operation -> params();
		len2 = act_params->length();
		for(i2 = 0; i2 < len2; i2++)
		{
			act_idl_type = (*act_params)[i2].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation (contained_type );
//				this->insert_to_generate(contained_type );
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
//				this->insert_to_generate(contained_type );
			};
		};
		
		
//		this->insert_to_generate(act_exception);
		break;

	case CORBA__::dk_Attribute:
		act_attribute = IR__::AttributeDef::_narrow(item);
		// traverse attribute
		
		//type
		act_idl_type = act_attribute->type_def ();
		contained_type = IR__::Contained::_narrow(act_idl_type);
		if (!CORBA::is_nil(contained_type)) {
			this->check_for_generation (contained_type );
//			this->insert_to_generate(contained_type );
		};
		// exceptions

		// the attribute itself must not added to the generation list.
		break;
	case CORBA__::dk_Enum:
//		this->insert_to_generate(item);
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
//		this->insert_to_generate(item);

	default:
		break;
	};
	m_recursion_set.erase(item->id());
};


void
GeneratorLIDL::generate_the_item ( IR__::Contained_ptr item ) {
	IR__::HomeDef_var act_home;
	IR__::ComponentDef_var act_component;
	IR__::InterfaceDef_var act_interface;
	IR__::AliasDef_var act_alias;
	IR__::ValueDef_var act_value;
	IR__::EventDef_var act_event;
	IR__::ExceptionDef_var act_exception;
	IR__::EnumDef_var act_enum;
	IR__::ModuleDef_var act_module;
	IR__::StructDef_var act_struct;

	std::cout << "Debug: item to generate: " << item->name() << std::endl;
	IR__::Contained_var act_contained = IR__::Contained::_narrow(item->defined_in());
	if (!CORBA::is_nil(act_contained)) {
		if (!strcmp(act_contained->name(), "Deployment")) {
//			return;
		};
		if (!strcmp(act_contained->name(), "Components")) {
			return;
		};
		if (!strcmp(act_contained->name(), "CORBA")) {
			return;
		};
		if (!strcmp(act_contained->name(), "CosPropertyService")) {
//			return;
		};

	}
	
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
	case CORBA__::dk_Struct:
		act_struct = IR__::StructDef::_narrow(item);
		doStruct(act_struct);

	default:
		break;
		//return;
	};
	this->close_module(item);
	
}

void
GeneratorLIDL::doModule(IR__::ModuleDef_ptr module)
{
	CORBA::ULong len;
	CORBA::ULong i;

	this->check_for_generation(module);
	len = m_to_generate_seq->length();
	for (i = 0; i < len ; i++) {
		generate_the_item ((*m_to_generate_seq)[i]);
	}

}

void
GeneratorLIDL::beginModule(IR__::ModuleDef_ptr module)
{	
	/*
	out << "//\n// " << module->id() << "\n//\n";
	out << "module " << module->name() << " {\n\n";
	out.indent();
*/
  };


void
GeneratorLIDL::endModule(IR__::ModuleDef_ptr module)
{
	/*
	out.unindent();
	out << "}; // module " << module->name() << "\n\n";
*/
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
}

void
GeneratorLIDL::doEvent(IR__::ValueDef_ptr value)
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
	CORBA::ULong i;
	for( i= 0; i < exception_seq->length(); i++)
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
		CORBA::ULong i;
		for( i= 0; i < len; i++)
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
GeneratorLIDL::generate(std::string target, std::string fileprefix)
{
	initialize(target, fileprefix);

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
	

} //
