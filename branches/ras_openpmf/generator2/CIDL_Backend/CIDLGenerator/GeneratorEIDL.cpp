#include "GeneratorEIDL.h"
#include "Debug.h"

#include <string>

#ifdef _WIN32
#define unlink _unlink
#else
#include <unistd.h>
#endif

namespace QEDO_CIDL_Generator {


GeneratorEIDL::GeneratorEIDL
( CIDL::CIDLRepository_ptr repository, CORBA::ORB_ptr orb )
: IDLBase(repository), m_recursion_set()
{
	_orb = CORBA::ORB::_duplicate( orb );
}


GeneratorEIDL::~GeneratorEIDL
()
{
}


bool
GeneratorEIDL::check_stream_CCM_object (IR__::ComponentDef_ptr component)
{
	if (CORBA::is_nil (component))
		return false;

	IR__::ComponentDef_var base = component->base_component();
	IR__::SourceDefSeq_var sources_seq = component->sources();
	IR__::SinkDefSeq_var sinks_seq = component->sinks();

	if (sources_seq->length() || sinks_seq->length())
		return true;
	else
		return check_stream_CCM_object (base);
}


void
GeneratorEIDL::planInterfaceContent(IR__::Contained_ptr item)
{
	IR__::Contained_var scope = IR__::Contained::_narrow(item->defined_in());
	if(CORBA::is_nil(scope)) {
		return;
	}

	std::string id = scope->id();
	if(interface_def_map_.find(id) == interface_def_map_.end())
	{
		IR__::ContainedSeq* def_seq = new IR__::ContainedSeq();
		def_seq->length(1);
		(*def_seq)[0] = IR__::Contained::_duplicate(item);
		interface_def_map_[id] = def_seq;
	}
	else
	{
		IR__::ContainedSeq* seq = interface_def_map_[id];
		CORBA::ULong len = seq->length();
		bool already_contained = false;
		for (CORBA::ULong i = 0 ; i < len ; i++) {
			if (!strcmp((*seq)[i]->id(), item->id())) {
				already_contained = true;
				continue;
			}
		}

		if(!already_contained) {
			seq->length(len + 1);
			(*seq)[len] = IR__::Contained::_duplicate(item);
		}
	}
}


void
GeneratorEIDL::doInterfaceContent(IR__::InterfaceDef_ptr item)
{
	std::string id = item->id();
	if(interface_def_map_.find(id) != interface_def_map_.end())
	{
		IR__::ContainedSeq_var seq = interface_def_map_[id];
		CORBA::ULong len = seq->length();
		for (CORBA::ULong i = 0 ; i < len ; i++) {
			generate_the_item((*seq)[i]);
		}
	}
}


void
GeneratorEIDL::check_for_generation(IR__::Contained_ptr item)
{
	//
	// check if item is already known
	//
	IR__::Contained_var restricted_contained = IR__::Contained::_narrow(item->defined_in());
	if (!CORBA::is_nil(restricted_contained )) {
		std::string id = restricted_contained ->id();

		if (!id.compare("IDL:Components/Deployment:1.0") ||
			!id.compare("IDL:omg.org/Components/Deployment:1.0")) {
			return;
		};
		if (!id.compare("IDL:omg.org/Components:1.0") ||
		    !id.compare("IDL:Components:1.0"))
		{
			return;
		}
		if (!id.compare("IDL:omg.org/Components/Extension:1.0") ||
		    !id.compare("IDL:Components/Extension:1.0"))
		{
			return;
		}
		if (!id.compare("IDL:omg.org/CORBA:1.0") ||
		    !id.compare("IDL:CORBA:1.0"))
		{
			return;
		}
		if (!id.compare("IDL:omg.org/CosPropertyService:1.0") ||
			!id.compare("IDL:CosPropertyService:1.0") )
		{
			std::string name = "CosProperty.idl";
			if(includes_.find(name) == includes_.end())
			{
				includes_[name] = true;
			}

			return;
		};
		if (!id.compare("IDL:omg.org/CosNaming:1.0") ||
			!id.compare("IDL:CosNaming:1.0") )
		{
			std::string name = "CosNaming.idl";
			if(includes_.find(name) == includes_.end())
			{
				includes_[name] = true;
			}
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

		break; }
	case CORBA__::dk_Home : {
		IR__::HomeDef_var a_home = IR__::HomeDef::_narrow(item);
		
		// base home
		IR__::HomeDef_var base_home = a_home->base_home();
		if (!CORBA::is_nil(base_home)) {
			this->check_for_generation(base_home);
		}

		// supported interfaces
		IR__::InterfaceDefSeq_var interf_seq = a_home->supported_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		}

		// insert this interface in generation list
		this->insert_to_generate(item);

		// content
		IR__::ContainedSeq_var contained_seq = a_home->contents(CORBA__::dk_all, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		// managed component
		IR__::ComponentDef_var a_component = a_home->managed_component();
		this->check_for_generation(a_component);

		//valuetype for Primarykey defined in Home
		/*
		IR__::PrimaryKeyDef_var a_pk = a_home->primary_key();
		if(!CORBA::is_nil(a_pk))
		{
			IR__::ValueDef_var a_valuetype = a_pk->primary_key();
			check_for_generation(a_valuetype);
		}
		*/
		break; }
	case CORBA__::dk_Component : {
		IR__::ComponentDef_var a_component = IR__::ComponentDef::_narrow(item);

		// base component
		IR__::ComponentDef_var base_component = a_component->base_component();
		if ( ! CORBA::is_nil(base_component)) {
			this->check_for_generation(base_component);
		}

		// supported interfaces
		IR__::InterfaceDefSeq_var interf_seq = a_component->supported_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		}

		// insert this interface in generation list
		this->insert_to_generate(item);

		// attributes
		IR__::ContainedSeq_var contained_seq = a_component->contents(CORBA__::dk_Attribute, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}
		
		// provided interfaces
		IR__::ProvidesDefSeq_var provides_seq = a_component->provides_interfaces();
		len = provides_seq->length();
		for(i = 0; i < len; i++)
		{
			IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow((*provides_seq)[i]->interface_type());
			if( !CORBA::is_nil(intf) )
			{
				this->check_for_generation( intf );
			}
		}

		// used interfaces
		IR__::UsesDefSeq_var uses_seq = a_component->uses_interfaces();
		len = uses_seq->length();
		for(i = 0; i < len; i++)
		{
			IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow((*uses_seq)[i]->interface_type());
			if( !CORBA::is_nil(intf) )
			{
				this->check_for_generation( intf );
			}
		}

		// emits_events
		IR__::EmitsDefSeq_var emits_seq = a_component->emits_events();
		len = emits_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*emits_seq)[i]->event());
		};

		// publish events
		IR__::PublishesDefSeq_var publish_seq = a_component->publishes_events();
		len = publish_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*publish_seq)[i]->event());
		};

		// consumes_events
		IR__::ConsumesDefSeq_var consumes_seq = a_component->consumes_events();
		len = consumes_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*consumes_seq)[i]->event());
		};

		// sinks
		IR__::SinkDefSeq_var sink_seq = a_component->sinks();
		len = sink_seq->length();
		for(i = 0; i < len; i++) {
			IR__::StreamTypeDef_var stream_type = (*sink_seq)[i]->stream_type();
			IR__::Contained_var transported_type = IR__::Contained::_narrow (stream_type->transported_type());
			if (!CORBA::is_nil (transported_type))
				this->check_for_generation (transported_type);
		};

		// sources
		IR__::SourceDefSeq_var source_seq = a_component->sources();
		len = source_seq->length();
		for(i = 0; i < len; i++) {
			IR__::StreamTypeDef_var stream_type = (*source_seq)[i]->stream_type();
			IR__::Contained_var transported_type = IR__::Contained::_narrow (stream_type->transported_type());
			if (!CORBA::is_nil (transported_type))
				this->check_for_generation (transported_type);
		};

		break; }
	case CORBA__::dk_Interface : {
		IR__::InterfaceDef_var act_interface = IR__::InterfaceDef::_narrow(item);
		
		// base interfaces
		IR__::InterfaceDefSeq_var interf_seq = act_interface->base_interfaces();
		len = interf_seq->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*interf_seq)[i]);
		}

		// insert this interface in generation list
		this->insert_to_generate(item);

		// content
		IR__::ContainedSeq_var contained_seq = act_interface->contents(CORBA__::dk_all, true);
		len = contained_seq->length();
		for(i = 0; i < len; i++)
		{
			check_for_generation((*contained_seq)[i]);
		}

		break; }
	case CORBA__::dk_Value : {
		IR__::ValueDef_var act_value = IR__::ValueDef::_narrow(item);

		// base value

		// supports

		// members
		IR__::ContainedSeq_var contained_seq = act_value->contents(CORBA__::dk_ValueMember, true);
		len = contained_seq->length();
		IR__::IDLType_var act_idl_type;
		IR__::Contained_var contained_type;
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

		this->insert_to_generate(act_value);
		break; }
	case CORBA__::dk_Operation : {
		IR__::OperationDef_var act_operation = IR__::OperationDef::_narrow(item);

		// return value
		IR__::IDLType_var act_idl_type = act_operation->result_def();
		IR__::Contained_var return_contained = IR__::Contained::_narrow(act_idl_type);
		if (!CORBA::is_nil(return_contained)) {
			this->check_for_generation(return_contained);
		}		

		// parameters
		IR__::ParDescriptionSeq_var act_params = act_operation -> params();
		len = act_params->length();
		IR__::Contained_var contained_type;
		for(i = 0; i < len; i++)
		{
			act_idl_type = (*act_params)[i].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation(contained_type);
			};
		};

		// exceptions
		IR__::ExceptionDefSeq_var act_exceptions = act_operation->exceptions();
		len = act_exceptions->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*act_exceptions)[i]);
		};

		break; }
	case CORBA__::dk_Factory :
	case CORBA__::dk_Finder : {
		IR__::OperationDef_var act_operation = IR__::OperationDef::_narrow(item);

		// parameters
		IR__::IDLType_var act_idl_type;
		IR__::ParDescriptionSeq_var act_params = act_operation -> params();
		len = act_params->length();
		IR__::Contained_var contained_type;
		for(i = 0; i < len; i++)
		{
			act_idl_type = (*act_params)[i].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation(contained_type);
			};
		};

		// exceptions
		IR__::ExceptionDefSeq_var act_exceptions = act_operation->exceptions();
		len = act_exceptions->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*act_exceptions)[i]);
		};

		break; }
	case CORBA__::dk_Attribute : {
		IR__::AttributeDef_var a_attribute = IR__::AttributeDef::_narrow(item);
		
		// type
		IR__::IDLType_var a_idl_type = a_attribute->type_def();
		IR__::Contained_var a_contained = IR__::Contained::_narrow(a_idl_type);
		if (!CORBA::is_nil(a_contained)) {
			this->check_for_generation(a_contained);
		};

		// exceptions
		IR__::ExceptionDefSeq_var act_exceptions = a_attribute->get_exceptions();
		len = act_exceptions->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*act_exceptions)[i]);
		};
		act_exceptions = a_attribute->put_exceptions();
		len = act_exceptions->length();
		for(i = 0; i < len; i++) {
			this->check_for_generation((*act_exceptions)[i]);
		};

		break; }
	case CORBA__::dk_Exception : {
		IR__::ExceptionDef_var a_exception = IR__::ExceptionDef::_narrow(item);

		// members 
		IR__::StructMemberSeq_var act_struct_members = a_exception->members();
		len = act_struct_members->length();
		IR__::IDLType_var a_idl_type;
		IR__::Contained_var contained_type;
		for(i = 0; i < len; i++)
		{
			a_idl_type = (*act_struct_members)[i].type_def;
			contained_type = IR__::Contained::_narrow(a_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation(contained_type);
			};
		};
		
		if(!definedInInterface(a_exception)) {
			this->insert_to_generate(item);
		}
		break; }
	case CORBA__::dk_Struct : {
		IR__::StructDef_var act_struct = IR__::StructDef::_narrow(item);

		// members
		IR__::StructMemberSeq_var act_struct_members = act_struct->members();
		len = act_struct_members->length();
		IR__::IDLType_var act_idl_type;
		IR__::Contained_var contained_type;
		for(i = 0; i < len; i++)
		{
			act_idl_type = (*act_struct_members)[i].type_def;
			contained_type = IR__::Contained::_narrow(act_idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation(contained_type);
			};
		};
		std::string id = item->id();
		if(!definedInInterface(item)) {
			this->insert_to_generate(item);
		}
		else {
			planInterfaceContent(item);
		}
		break; }
	case CORBA__::dk_Union : {
		IR__::UnionDef_var a_union = IR__::UnionDef::_narrow(item);
		IR__::IDLType_var idl_type;
		IR__::Contained_var contained_type;

		// discriminator
		idl_type = a_union->discriminator_type_def();
		contained_type = IR__::Contained::_narrow(idl_type);
		if (!CORBA::is_nil(contained_type)) {
			this->check_for_generation(contained_type);
		};

		// members
		IR__::UnionMemberSeq_var members = a_union->members();
		len = members->length();
		for(i = 0; i < len; i++)
		{
			idl_type = (*members)[i].type_def;
			contained_type = IR__::Contained::_narrow(idl_type);
			if (!CORBA::is_nil(contained_type)) {
				this->check_for_generation(contained_type);
			};
		};
		std::string id = item->id();
		if(!definedInInterface(item)) {
			this->insert_to_generate(item);
		}
		else {
			planInterfaceContent(item);
		}
		break; }
	case CORBA__::dk_Enum : {
		if(!definedInInterface(item)) {
			this->insert_to_generate(item);
		}
		else {
			planInterfaceContent(item);
		}
		break; }
	case CORBA__::dk_Alias : {
		IR__::AliasDef_var a_alias = IR__::AliasDef::_narrow(item);

		// original type
		IR__::Contained_var a_contained = IR__::Contained::_narrow(a_alias->original_type_def());
		if (!CORBA::is_nil(a_contained)) {
			this->check_for_generation(a_contained);
		}

		// sequence
		else if(a_alias->original_type_def()->def_kind() == CORBA__::dk_Sequence) {
			IR__::SequenceDef_var a_seq = IR__::SequenceDef::_narrow(a_alias->original_type_def());
			a_contained = IR__::Contained::_narrow(a_seq->element_type_def());
			if (!CORBA::is_nil(a_contained)) {
				this->check_for_generation(a_contained);
			}
		}

		if(!definedInInterface(item)) {
			this->insert_to_generate(item);
		}
		else {
			planInterfaceContent(item);
		}
		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
};


//
// module
//
void
GeneratorEIDL::doModule(IR__::ModuleDef_ptr module)
{
};


//
// interface
//
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

	// content with potential order problems
	doInterfaceContent(intface);

	// content without order problems
	handleException(intface);
	handleAttribute(intface);
	handleOperation(intface);

	out.unindent();
	out << "};\n\n";
}


//
// home
//
void
GeneratorEIDL::doHome(IR__::HomeDef_ptr home)
{	
	//
	// implicit home
	//
	IR__::PrimaryKeyDef_ptr pk = home->primary_key();

	if(!CORBA::is_nil(pk))
	{
		//"copying" declaration of valuetype defined for primary key into EIDL. 
		//At the moment this is the better way to handle with it, however, 
		//it should be improved, for it is possible, that one primary key is
		//used by several different homes.
		/*
		out << "//\n// valuetype for primary key\n//\n";
		IR__::ValueDef_var act_value = pk->primary_key();
		out << "valuetype " << act_value->name() << "\n";
		out.indent();
		out << ": Components::PrimaryKeyBase\n";
		IR__::ValueDefSeq_var support_seq = act_value->abstract_base_values();
		CORBA::ULong len = support_seq->length();
		for(CORBA::ULong i = 0; i < len; i++)
		{
			char* szTemp = ((*support_seq)[i])->name();
			if(strcmp(szTemp, "PrimaryKeyBase")==0)
				continue;

			if(i==0)
				out << ": " << szTemp << "\n";
			else
				out << ", " << szTemp << "\n";
		}
		out.unindent();
		out << "{\n";

		//only attributes can be defined in a valuetype which is specially for a primary key
		IR__::ContainedSeq_var contained_seq = act_value->contents(CORBA__::dk_ValueMember, true);
		len = contained_seq->length();
		out.indent();
		for(i = 0; i < len; i++)
		{
			IR__::ValueMemberDef_var vMember = IR__::ValueMemberDef::_narrow((*contained_seq)[i]);
			(vMember->access()==CORBA__::PUBLIC_MEMBER) ? out << "public " : out << "private ";
			out << map_idl_type(vMember->type_def()) << " " << vMember->name() << ";\n";
		}
		out.unindent();
		out << "};\n\n";
		*/
		out << "//\n// implicit home for " << home->id() << "\n//\n";
		out << "interface " << home->name() << "Implicit\n";
		out << "{\n";
		out.indent();
		
		char* szt = pk->name();

		out << map_absolute_name(home->managed_component()) << " create(in " << pk->name() << " key)\n";
		out.indent();
		out << "raises (Components::CreateFailure, Components::DuplicateKeyValue, Components::InvalidKey);\n\n";
		out.unindent();

		out << map_absolute_name(home->managed_component()) << " find_by_primary_key(in " << pk->name() << " key)\n";
		out.indent();
		out << "raises (Components::FinderFailure, Components::UnknownKeyValue, Components::InvalidKey);\n\n";
		out.unindent();

		out << "void remove(in " << pk->name() << " key)\n";
		out.indent();
		out << "raises (Components::RemoveFailure, Components::UnknownKeyValue, Components::InvalidKey);\n\n";
		out.unindent();

		out << pk->name() << " get_primary_key(in " << map_absolute_name(home->managed_component()) << " comp);\n";
		
		out.unindent();
		out << "};\n\n";
	}
	else
	{
		out << "//\n// implicit home for " << home->id() << "\n//\n";
		out << "interface " << home->name() << "Implicit : ::Components::KeylessCCMHome\n";
		out << "{\n";
		out.indent();
		out << map_absolute_name(home->managed_component()) << " create() raises (Components::CreateFailure);\n";
		out.unindent();
		out << "};\n\n";
	}

	//
	// explicit home
	//
	out << "//\n// explicit home for " << home->id() << "\n//\n";
	out << "interface " << home->name() << "Explicit : ";
	IR__::HomeDef_var base = home->base_home();
	if(base) {
		out << map_absolute_name(base);
		out << "Explicit";
	}
	else {
		out << "::Components::CCMHome";
	}

	// supported interfaces
	IR__::InterfaceDefSeq_var supp_intfs = home -> supported_interfaces();
	for(CORBA::ULong i = 0; i < supp_intfs->length(); i++) {
		out << ", " << map_absolute_name((*supp_intfs)[i]);
	};

	out << "\n{\n";
	out.indent();

	managed_component_ = map_absolute_name(home->managed_component());

	// content with potential order problems
	doInterfaceContent(home);

	// content without order problems
	handleException(home);
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
	out << "interface " << home->name() << " : " << home->name() << "Implicit, ";
	out << home->name() << "Explicit\n{\n};\n\n";
};


//
// attribute
//
void
GeneratorEIDL::doAttribute(IR__::AttributeDef_ptr attribute)
{
	out << "\n//\n// " << attribute->id() << "\n//\n";

	// attribute mode
	if(attribute->mode() == IR__::ATTR_READONLY) {
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


//
// operation
//
void
GeneratorEIDL::doOperation(IR__::OperationDef_ptr operation)
{
	out << "\n//\n// " << operation->id() << "\n//\n";

	// operation mode
	if(operation->mode() == IR__::OP_ONEWAY) {
		out << "oneway ";
	}
	
	out << tcToName(operation->result()) << " " << operation->name() << "(";

	// parameters
	IR__::ParDescriptionSeq_var para_seq = operation->params();
	CORBA::ULong len = para_seq->length();
	CORBA::ULong i;
	for( i= len; i > 0; i--)
	{
		if(i < len) {
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
		if(!i) {
			out.indent();
			out << "\nraises(";
		}
		else {
			out << ", ";
		}

		out << tcToName((*exception_seq)[i]->type());
	}
	if(i) {
		out.unindent();
		out << ")";
	}

	out << ";\n";
}


//
// factory
//
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
		if(i < len) {
			out << ", ";
		}

		out << "in " << tcToName((*para_seq)[i - 1].type) << " " << string((*para_seq)[i - 1].name);
	}
	out << ")";

	// exceptions
	IR__::ExceptionDefSeq_var exception_seq = factory->exceptions();
	for(i = 0; i < exception_seq->length(); i++)
	{
		if(!i) {
			out << " raises(";
		}
		else {
			out << ", ";
		}

		out << tcToName((*exception_seq)[i]->type());
	}
	if(i) {
		out << ")";
	}

	out << ";\n";
}


//
// finder
//
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


//
// exception
//
void
GeneratorEIDL::doException(IR__::ExceptionDef_ptr except)
{
	out << "//\n// " << except->id() << "\n//\n";
	out << "exception " << except->name() << "\n{\n";
	out.indent();

	IR__::StructMemberSeq_var member_seq = except->members();
	for(CORBA::ULong i = 0; i < member_seq->length(); i++)
	{
		out << tcToName((*member_seq)[i].type) << " " << string((*member_seq)[i].name) << ";\n";
	}

	out.unindent();
	out << "};\n\n";
};


//
// value
//
void
GeneratorEIDL::doValue(IR__::ValueDef_ptr value)
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
	
	out << "valuetype " << value->name() << "\n";

	//handle supported interfaces
	IR__::ValueDefSeq_var support_seq = value->abstract_base_values();
	CORBA::ULong len = support_seq->length();
	out.indent();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		char* szTemp = ((*support_seq)[i])->name();
		
		(i==0) ? out << ": " : out << ", ";

		if(strcmp(szTemp, "PrimaryKeyBase")==0)
			out << "Components::PrimaryKeyBase";

		out << "\n";
	}
	out.unindent();

	out << " {\n";
	out.indent();

	// contents
	handleValueMember(value);

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

			out << "in " << tcToName(member_seq[ii - 1].type) << " " << string(member_seq[ii - 1].name);
		}

		out << ");\n";
	}
	out.unindent();
	out << "\n};\n\n";
};


//
// event
//
void
GeneratorEIDL::doEvent(IR__::EventDef_ptr event)
{
	out << "//\n// " << event->id() << "\n//\n";
	
	if(event->is_abstract())
	{
		out << "abstract ";
	}
	
	if(event->is_custom())
	{
		out << "custom ";
	}
	
	if(event->is_truncatable())
	{
		out << "truncatable ";
	}
	
	out << "valuetype " << event->name();
	out << " : Components::EventBase\n";
	out << "{\n";
	out.indent();

	// contents
	handleValueMember(event);

	// initializers
	IR__::InitializerSeq_var initializers = event->initializers();
	for(CORBA::ULong i = 0; i < initializers->length(); i++)
	{
		out << "\nfactory " << string((*initializers)[i].name) << "(";
		
		IR__::StructMemberSeq member_seq = (*initializers)[i].members;
		CORBA::ULong len = member_seq.length();
		for(CORBA::ULong ii = len; ii > 0; ii--)
		{
			if(ii < len) {
				out << ", ";
			}

			out << "in " << tcToName(member_seq[ii - 1].type) << " " << string(member_seq[ii - 1].name);
		}

		out << ");\n";
	}
	out.unindent();
	out << "\n};\n\n";

	//
	// event interface
	//
	out << "interface " << event->name() << "Consumer : Components::EventConsumerBase\n{\n";
	out.indent();
	out << "void " << "push_" << event->name() << "(in " << event->name() << " ev);\n";
	out.unindent();
	out << "};\n\n";
};


//
// value member
//
void
GeneratorEIDL::doValueMember(IR__::ValueMemberDef_ptr member)
{
	if(member->access() == CORBA__::PRIVATE_MEMBER) {
		out << "private ";
	}
	else {
		out << "public ";
	}
	
	out << tcToName(member->type()) << " " << member->name() << ";\n";
};


//
// enum
//
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


//
// alias
//
void
GeneratorEIDL::doAlias(IR__::AliasDef_ptr adef)
{
	out << "//\n// " << adef->id() << "\n//\n";
	switch(adef->original_type_def()->def_kind())
	{
	case CORBA__::dk_Alias :
	case CORBA__::dk_Struct :
	case CORBA__::dk_Union :
	case CORBA__::dk_Enum :
	case CORBA__::dk_Value :
	case CORBA__::dk_ValueBox : {
		out << "typedef " << map_absolute_name(adef->original_type_def()) << " " << adef -> name () << ";\n";
		break; }
	case CORBA__::dk_Primitive : {
		IR__::PrimitiveDef_var prim = IR__::PrimitiveDef::_narrow(adef->original_type_def());
		out << "typedef " << tcToName(prim->type ()) << " " << adef -> name () << ";\n";
		break; }
    case CORBA__::dk_String : {
		IR__::StringDef_var str = IR__::StringDef::_narrow(adef->original_type_def());
		out << "typedef string [" << str->bound() << "] " << adef -> name () << ";\n";
		break; }
	case CORBA__::dk_Sequence : {
		IR__::SequenceDef_var seq = IR__::SequenceDef::_narrow(adef->original_type_def());
		out << "typedef sequence<" << tcToName(seq-> element_type () ) << "> " << adef -> name () << ";\n";
		break; }
	case CORBA__::dk_Array : {
		IR__::ArrayDef_var arr = IR__::ArrayDef::_narrow(adef->original_type_def());
		out << "typedef " << "todo" << " " << adef -> name () << ";\n";
		break; }
    case CORBA__::dk_Wstring : {
		IR__::WstringDef_var str = IR__::WstringDef::_narrow(adef->original_type_def());
		out << "typedef wstring [" << str->bound() << "] " << adef -> name () << ";\n";
		break; }
	case CORBA__::dk_Fixed : {
		out << "typedef " << "todo" << " " << adef -> name () << ";\n";
		break; }
    case CORBA__::dk_Native : {
		out << "typedef " << "todo" << " " << adef -> name () << ";\n";
		break; }
	case CORBA__::dk_Interface : {
		out << "typedef " << map_absolute_name(adef->original_type_def()) << " " << adef -> name () << ";\n";
		 break; }
	default : 
		out << "todo\n";
		break; 
	}
}


//
// struct
//
void
GeneratorEIDL::doStruct(IR__::StructDef_ptr sdef)
{
	out << "//\n// " << sdef->id() << "\n//\n";
	out << "struct " << sdef -> name () << "{\n";
	IR__::StructMemberSeq_var str_seq = sdef->members();
	CORBA::ULong len = str_seq->length();
	for (CORBA::ULong i = 0; i < len; i++) {
		out << "   " << tcToName(str_seq[i].type) << " " << str_seq[i].name.in() << ";\n";
	};
	out << "};\n";
}


//
// union
//
void 
GeneratorEIDL::doUnion(IR__::UnionDef_ptr udef)
{
	out << "//\n// " << udef->id() << "\n//\n";
	out << "union " << udef -> name () << " switch(" << tcToName(udef->discriminator_type()) << ") {\n";
	IR__::UnionMemberSeq_var members = udef->members();
	CORBA::ULong len = members->length();
	for (CORBA::ULong i = 0; i < len; i++) {
		CORBA::Any a_any = members[i].label;
		std::stringstream label;

		// default
		if (udef->discriminator_type()->kind() == CORBA::tk_octet)
		{
			out << "   default : " << tcToName(members[i].type) << " " << members[i].name.in() << ";\n";
			continue;
		}

		// case
		switch (udef->discriminator_type()->kind()) {
			case CORBA::tk_short:
			case CORBA::tk_long:
			case CORBA::tk_longlong:
			case CORBA::tk_ushort:
			case CORBA::tk_ulong:
			case CORBA::tk_ulonglong: {
				CORBA::Long l;
				a_any >>= l;
				label << l;
									  }
			case CORBA::tk_boolean: {
				CORBA::Boolean b;
				a_any >>= CORBA::Any::to_boolean(b);
				label << b;
									}
			case CORBA::tk_char: {
				CORBA::Char c;
				a_any >>= CORBA::Any::to_char(c);
				label << c;
								 }
			case CORBA::tk_wchar: {
				CORBA::WChar w;
				a_any >>= CORBA::Any::to_wchar(w);
				label << w;
								  }
			case CORBA::tk_enum: {
				DynamicAny::DynAnyFactory_var factory;
				try
				{
					factory = DynamicAny::DynAnyFactory::_narrow( _orb->resolve_initial_references( "DynAnyFactory" ) );
				}
				catch ( ... )
				{
					std::cerr << "Error during DynAny stuff" << std::endl;
				}
				DynamicAny::DynEnum_var dyn_enum;
				dyn_enum = DynamicAny::DynEnum::_narrow ( factory -> create_dyn_any( a_any ) );
				label << dyn_enum->get_as_string();
								 }
			case CORBA::tk_alias: {
				// todo
								  }
			default: {}
		}
		out << "   case " << label.str() << " : " << tcToName(members[i].type) << " " << members[i].name.in() << ";\n";
	};
	out << "};\n";
}


//
// component
//
void
GeneratorEIDL::doComponent(IR__::ComponentDef_ptr component)
{
	out << "//\n// " << component->id() << "\n//\n";
	out << "interface " << component->name() << " : ";
	
	// base component
	IR__::ComponentDef_var base = component->base_component();
	IR__::SourceDefSeq_var sources_seq = component->sources();
	IR__::SinkDefSeq_var sinks_seq = component->sinks();
	bool has_streams = sources_seq->length() || sinks_seq->length();

	if(!CORBA::is_nil(base)) {
		out << map_absolute_name(base);

		if (has_streams && !check_stream_CCM_object (base))
			out << ", ::StreamComponents::StreamCCMObject";
	}
	else {
		// Test whether the component has stream features
		if (has_streams)
			out << "::StreamComponents::StreamCCMObject";
		else
			out << "::Components::CCMObject";
	}

	// supported interfaces
	IR__::InterfaceDefSeq_var supported_seq = component->supported_interfaces();
	CORBA::ULong len = supported_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		out << ", " << map_absolute_name((*supported_seq)[i]);
	}
	out << "\n{\n";
	out.indent();

	// content
	handleAttribute(component);
	handleProvides(component);
	handleUses(component);
	handleEmits(component);
	handlePublishes(component);
	handleConsumes(component);

	out.unindent();
	out << "};\n\n";

	handleSink(component);
}


//
// provides
//
void
GeneratorEIDL::doProvides(IR__::ProvidesDef_ptr provides, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << provides->id() << "\n//\n";
	/*IR__::InterfaceDef_var type = IR__::InterfaceDef::_narrow(provides->interface_type());
	if( !CORBA::is_nil(type) )
	{
		out << type->absolute_name() << " provide_" << provides->name() << "();\n";
	}
	// it is no interface, must be Object
	else
	{
		out << "Object provide_" << provides->name() << "();\n";
	}*/
	out << tcToName(provides->interface_type()->type()) << " provide_" << provides->name() << "();\n";
}


//
// uses
//
void
GeneratorEIDL::doUses(IR__::UsesDef_ptr uses, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << uses->id() << "\n//\n";
	std::string type = tcToName(uses->interface_type()->type());

	//
	// multiple
	//
	if(uses->is_multiple())
	{
		out << "struct " << uses->name() << "Connection {\n";
		out.indent();
		out << type << " objref;\n";
		out << "Components::Cookie ck;\n";
		out.unindent();
		out << "};\n";
		out << "typedef sequence < " << uses->name() << "Connection > " << uses->name() << "Connections;\n\n";
			
		out << "Components::Cookie " << "connect_" << uses->name() << "( in " << type << " conx)\n";
		out.indent();
		out << "raises (Components::ExceededConnectionLimit, Components::InvalidConnection);\n\n";
		out.unindent();
			
		out << type << " disconnect_" << uses->name() << "(in Components::Cookie ck)\n";
		out.indent();
		out << "raises (Components::InvalidConnection);\n\n";
		out.unindent();

		out << uses->name() << "Connections " << "get_connections_" << uses->name() << "();\n\n";
	}
	//
	// not multiple
	//
	else
	{
		out << type << " get_connection_" << uses->name() << "();\n";
		
		out << type << " disconnect_" << uses->name() << "()\n";
		out.indent();
		out << "raises (::Components::NoConnection);\n";
		out.unindent();
		
		out << "void connect_" << uses->name() << "(in " << type << " conxn)\n";
		out.indent();
		out << "raises (::Components::AlreadyConnected, ::Components::InvalidConnection);\n";
		out.unindent();
	}
}


//
// emits
//
void
GeneratorEIDL::doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << emits->id() << "\n//\n";

	out << "void " << "connect_" << emits->name();
	out << "(in " << map_absolute_name(emits->event()) << "Consumer consumer);\n\n";

	out << map_absolute_name(emits->event()) << "Consumer" << " disconnect_" << emits->name();
	out << "();\n\n";
}


//
// publishes
//
void
GeneratorEIDL::doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component)
{
	out << "\n//\n// " << publishes->id() << "\n//\n";

	out << "Components::Cookie" << " subscribe_" << publishes->name();
	out << "( in " << map_absolute_name(publishes->event()) << "Consumer";
	out << " consumer);\n\n";

	out << map_absolute_name(publishes->event()) << "Consumer ";
	out << "unsubscribe_" << publishes->name() << "(in Components::Cookie ck);\n\n";
}


//
// consumes
//
void
GeneratorEIDL::doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component)
{
	out << "//\n// " << consumes->id() << "\n//\n";

	out << map_absolute_name(consumes->event()) << "Consumer get_consumer_" << consumes->name() << "();\n\n";
}


//
// sink
//
void
GeneratorEIDL::doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component)
{
	std::string sink_name = sink->name();

	out << "//\n// " << sink->id() << "\n//\n";
	out << "local interface " << component->name() << "_" << sink_name << "_Sink\n";
	out << "{\n"; out.indent();
	out << "void begin_stream_" << sink_name << " (in CORBA::RepositoryId repos_id, in Components::ConfigValues meta_data);\n";
	out << "void end_stream_" << sink_name << "();\n";
	out << "void failed_stream_" << sink_name << "();\n";

	IR__::StreamTypeDef_var stream_type = sink->stream_type();
	IR__::IDLType_var transported_type = stream_type->transported_type();

	if (CORBA::is_nil (transported_type))
	{
		out << "void receive_stream_" << sink_name << " (in StreamComponents::StreamingBuffer data);\n";
	}
	else
	{
		out << "void receive_stream_" << sink_name << " (in " << map_absolute_name(transported_type) << " data);\n";
	}
	
	out.unindent();
	out << "};\n";
}


//
// source
//
void
GeneratorEIDL::doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component)
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
GeneratorEIDL::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }
	
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
	CORBA::ULong len = m_to_generate_interface_seq->length();
	CORBA::ULong i;
	for(i = 0; i < len; i++)
	{
		if ((*m_to_generate_interface_seq)[i]->describe()->kind == CORBA__::dk_Interface) {
			open_module((*m_to_generate_interface_seq)[i]);
			out << "interface " << (*m_to_generate_interface_seq)[i]->name() << ";\n";
			close_module((*m_to_generate_interface_seq)[i]);
		}
		if ((*m_to_generate_interface_seq)[i]->describe()->kind == CORBA__::dk_Component) {
			open_module((*m_to_generate_interface_seq)[i]);
			out << "interface " << (*m_to_generate_interface_seq)[i]->name() << ";\n";
			close_module((*m_to_generate_interface_seq)[i]);
		};
		if ((*m_to_generate_interface_seq)[i]->describe()->kind == CORBA__::dk_Home) {
			open_module((*m_to_generate_interface_seq)[i]);
			out << "interface " << (*m_to_generate_interface_seq)[i]->name() << ";\n";
			close_module((*m_to_generate_interface_seq)[i]);
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
	out << "#include \"orb.idl\"\n";
	
	std::map < std::string, bool > ::iterator it;
	for(it = includes_.begin(); it != includes_.end(); it++)
	{
		out << "#include \"" << it->first << "\"\n";
	}
	out << "\n";

	out << temp_file;
	out << "\n#endif\n";
	out.close();
	temp_file.close();
	unlink(temp_filename.c_str());
}


} // namespace

