#include "GeneratorBIDL.h"
#include "Debug.h"
#include <map>

using namespace std;


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
GeneratorBIDL::open_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module)
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->open_module(act_mod);
		out << "module " << act_mod->name() << " {\n";
		out.indent();
	}
};


void
GeneratorBIDL::close_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module)
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->close_module(act_mod);
		out.unindent();
		out <<  "};\n";
	}
};


void
GeneratorBIDL::generate(string target)
{
	filename_ = target + "_BUSINESS.idl";
	
	out.open(filename_.c_str());
	out << "#ifndef __" << target << "_BUSINESS_IDL\n";
	out << "#define __" << target << "_BUSINESS_IDL\n";
	out << "\n#include \"" << target << "_LOCAL.idl\"\n\n\n";
	out << "// local interfaces for each executor or segment\n\n";

	doGenerate(target);

	out << "\n#endif\n";
	out.close();
}
	

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
	

	//
	// local interface for each segment
	//
	CIDL::SegmentDefSeq_var segment_seq = composition->executor()->segments();
	CORBA::ULong len = segment_seq->length();
	for (CORBA::ULong i = 0; i < len; i++)
	{
		facet_types.clear();
		out << "//\n// " << segment_seq[i]->id() << "\n//\n";
		out << "local interface CCM_" << segment_seq[i]->name() << " : ::Components::EnterpriseComponent";

		// inherit from each implemented facet type
		IR__::ProvidesDefSeq_var provided_seq = segment_seq[i]->provided_facets();
		for (CORBA::ULong ii = 0; ii < provided_seq->length(); ii++)
		{
			implemented_facets[provided_seq[ii]->name()] = true;
			facet_type = provided_seq[ii]->interface_type()->id();
			
			// if type already inherited, skip it
			if(facet_types.find(facet_type) == facet_types.end())
			{
				out << ", " << mapLocalName(provided_seq[ii]->interface_type());
				facet_types[facet_type] = true;
			}
		}
		out << "\n{\n};\n\n";
	}


	//
	// local interface for the executor
	//
	facet_types.clear();
	out << "//\n// " << composition->executor()->id() << "\n//\n";
	out << "local interface CCM_" << composition->executor()->name() << " : ";
	out << mapLocalName(composition->ccm_component()) << "_Executor";
	

	// inherit from each implemented facet type
	IR__::ProvidesDefSeq_var provides_seq = composition->ccm_component()->provides_interfaces();
	len = provides_seq->length();
	for (i = 0; i < len; i++)
	{
		// facet already implemented by segment?
		if(implemented_facets.find(provides_seq[i]->name()) == implemented_facets.end())
		{
			facet_type = provides_seq[i]->interface_type()->id();
			
			// if type already inherited, skip it
			if(facet_types.find(facet_type) == facet_types.end())
			{
				facet_types[facet_type] = true;
				if(!facet_types.empty())
				{
					out << ", ";
				}
				out << map_absolute_name(provides_seq[i]->interface_type());
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
			out << ", " << mapLocalName(consumes_seq[i]->event()) << "Consumer";
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