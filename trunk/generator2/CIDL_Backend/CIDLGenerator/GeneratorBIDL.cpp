#include "GeneratorBIDL.h"
#include "Debug.h"
#include <map>


namespace QEDO_CIDL_Generator {


GeneratorBIDL::GeneratorBIDL
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: IDLBase(repository)
{
}


GeneratorBIDL::~GeneratorBIDL
()
{
}


void
GeneratorBIDL::check_for_generation(IR__::Contained_ptr item)
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
	switch (item->describe()->kind)
	{
	case CORBA__::dk_Module : {
		IR__::ModuleDef_var act_module = IR__::ModuleDef::_narrow(item);

		// modules
		IR__::ContainedSeq_var contained_seq = act_module->contents(CORBA__::dk_Module, true);
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

		break; }
	case CORBA__::dk_Composition : {
		insert_to_generate(item);
		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
}


void
GeneratorBIDL::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	filename_ = file_prefix_ + "_BUSINESS.idl";
	
	out.open(filename_.c_str());
	out << "#ifndef __" << file_prefix_ << "_BUSINESS_IDL\n";
	out << "#define __" << file_prefix_ << "_BUSINESS_IDL\n\n";
	out << "#include \"" << file_prefix_ << "_LOCAL.idl\"\n\n\n";
	out << "//\n// local interfaces for each executor or segment\n//\n\n\n";

	doGenerate();

	out << "\n#endif\n";
	out.close();
}
	

//
// composition
//
void
GeneratorBIDL::doComposition(CIDL::CompositionDef_ptr composition)
{
	//
	// get the module where the composition is defined in and open it
	//
	string id = composition->id();
	IR__::Contained_ptr module_def = 0;
	string::size_type pos = id.find_last_of("/");
	if(pos != string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		open_module(module_def);
		out << "\nmodule " << module_def->name() << "\n{\n";
		out.indent();
	}

	string facet_type;
	map < string, bool > facet_types;
	map < string, bool > implemented_facets;
	CORBA::ULong i;

	//
	// local interface for each segment
	//
	CIDL::SegmentDefSeq_var segment_seq = composition->executor_def()->segments();
	CORBA::ULong len = segment_seq->length();
	for (i = 0; i < len; i++)
	{
		facet_types.clear();
		out << "//\n// " << segment_seq[i]->id() << "\n//\n";
		out << "local interface CCM_" << segment_seq[i]->name() << " : ::Components::EnterpriseComponent";

		// inherit from each implemented facet type
		IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
		for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
		{
			implemented_facets[provided_seq[ii]->name()] = true;
			IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow(provided_seq[ii]->interface_type());
			if( !CORBA::is_nil(intf) )
			{
				facet_type = intf->id();
			}
			else
			{
				facet_type = "IDL:omg.org/CORBA/Object:1.0";
			}
			
			// if type already inherited, skip it
			if(facet_types.find(facet_type) == facet_types.end())
			{
				out << ", " << getLocalName(provided_seq[ii]->interface_type());
				facet_types[facet_type] = true;
			}
		}
		out << "\n{\n};\n\n";
	}


	//
	// local interface for the executor
	//
	facet_types.clear();
	out << "//\n// " << composition->executor_def()->id() << "\n//\n";
	out << "local interface CCM_" << composition->executor_def()->name() << " : ";
	out << getLocalName(composition->ccm_component()) << "_Executor";
	
	//
	// inherit from each implemented facet type
	//
	IR__::ProvidesDefSeq_var provides_seq = composition->ccm_component()->provides_interfaces();
	len = provides_seq->length();
	for (i = 0; i < len; i++)
	{
		IR__::InterfaceDef_var intf = IR__::InterfaceDef::_narrow(provides_seq[i]->interface_type());
		if( CORBA::is_nil(intf) )
		{
			continue;
		}

		//
		// facet not already implemented by segment
		//
		if(implemented_facets.find(provides_seq[i]->name()) == implemented_facets.end())
		{
			// if type already inherited, skip it
			facet_type = intf->id();
			if(facet_types.find(facet_type) == facet_types.end())
			{
				facet_types[facet_type] = true;
				if(!facet_types.empty()) {
					out << ", ";
				}
				out << getLocalName(intf);
			}
		}
	}

	// inherit from consumer for each event
	facet_types.clear();
	IR__::ConsumesDefSeq_var consumes_seq = composition->ccm_component()->consumes_events();
	len = consumes_seq->length();
	for (i = 0; i < len; i++)
	{
		facet_type = consumes_seq[i]->event()->id();
			
		// if type already inherited, skip it
		if(facet_types.find(facet_type) == facet_types.end())
		{
			facet_types[facet_type] = true;
			out << ", " << getLocalName(consumes_seq[i]->event()) << "Consumer";
		}
	}

	out << "\n{\n};\n\n";


	if(module_def)
	{
		out.unindent();
		out << "};\n";
		close_module(module_def);
	}
}

} //

