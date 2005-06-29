#include "GeneratorCCD.h"
#include "Debug.h"

#include <string>


namespace QEDO_CIDL_Generator {


GeneratorCCD::GeneratorCCD
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase ( repository )
{
}

GeneratorCCD::GeneratorCCD
( QEDO_ComponentRepository::CIDLRepository_impl *repository, std::string dir_prefix)
: CPPBase ( repository )
{
	m_dir_prefix = dir_prefix;
}


GeneratorCCD::~GeneratorCCD
()
{
}


void
GeneratorCCD::check_for_generation(IR__::Contained_ptr item)
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
	IR__::ContainedSeq_var contained_seq;
	IR__::ModuleDef_var act_module;
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
		insert_to_generate(item);
		break; }
	default:
		break;
	};

	m_recursion_set.erase(item->id());
}


void
GeneratorCCD::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	// setting counter for facettag
	facet_number_ = 1;
	doGenerate();
}


//
// composition
//
void
GeneratorCCD::doComposition(CIDL::CompositionDef_ptr composition)
{
	filename_ = "";

	// check whether the descriptor has to be create elsewhere
	// for usage from project generator
	if (m_dir_prefix.length())
	{
		filename_ = m_dir_prefix;
	}

	std::string id = composition->id();
	IR__::Contained_ptr module_def = 0;
	std::string::size_type pos = id.find_last_of("/");
	if(pos != std::string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		filename_.append(getAbsoluteName(module_def, "_"));
		filename_.append("_");
	}
	
	// open output file
	filename_.append(composition->name());
	filename_.append(".ccd");
	out.open(filename_.c_str());

	out << "<?xml version = '1.0' ?>\n";
	out << "<!DOCTYPE corbacomponent PUBLIC \"-//OMG//DTD CORBA Component Descriptor\"";
	out << " \"http://www.qedo.org/corbacomponent.dtd\">\n\n";

	out << "<corbacomponent>\n";
	out.indent();
    out << "<corbaversion>3.0</corbaversion>\n";
	out << "<componentrepid repid=\"" << composition->ccm_component()->id() << "\"/>\n";
    out << "<homerepid repid=\"" << composition->ccm_home()->id() << "\"/>\n";
    
	out << "<componentkind>\n";
	out.indent();
	switch( composition->lifecycle() )
	{
	case CIDL::lc_Service: 
		out << "<service>\n";
		break;
	case CIDL::lc_Session: 
		out << "<session>\n";
		break;
	case CIDL::lc_Process: 
		out << "<process>\n";
		break;
	case CIDL::lc_Entity: 
		out << "<entity>\n";
		break;
	case CIDL::lc_Extension: 
		out << "<containerextension>\n";
		break;
	default : {}
	}
	out.indent();
    out << "<servant lifetime=\"container\"/>\n";
	out.unindent();
	switch( composition->lifecycle() )
	{
	case CIDL::lc_Service: 
		out << "</service>\n";
		break;
	case CIDL::lc_Session: 
		out << "</session>\n";
		break;
	case CIDL::lc_Process: 
		out << "</process>\n";
		break;
	case CIDL::lc_Entity: 
		out << "</entity>\n";
		break;
	case CIDL::lc_Extension: 
		out << "</containerextension>\n";
		break;
	default : {}
	}
	out.unindent();
    out << "</componentkind>\n";

    out << "<threading policy=\"multithread\"/>\n";
    out << "<configurationcomplete set=\"true\"/>\n\n";
	
	//<segment name="Seg" segmenttag="">
    //    <segmentmember facettag="the_fork"/>
    //</segment>

	out << "<homefeatures name=\"" << composition->ccm_home()->name();
	out << "\" repid=\"" << composition->ccm_home()->id() << "\">\n";
    out << "</homefeatures>\n\n";
    out << "<componentfeatures name=\"" << composition->ccm_component()->name();
	out << "\" repid=\"" << composition->ccm_component()->id() << "\">\n";
    out.indent();
	out << "<ports>\n";

	// manage ports
	out.indent();
	gen_ports(composition->ccm_component());

	//out << "        <provides providesname="the_fork" repid="IDL:dinner/Fork:1.0" facettag="the_fork"/>
    //        <provides providesname="the_name" repid="IDL:dinner/Named:1.0" facettag="the_name"/>
	out.unindent();
	out << "</ports>\n";
	out.unindent();
    out << "</componentfeatures>\n";
	out.unindent();
	out << "</corbacomponent>";

	// close file
	out.close();
}

void
GeneratorCCD::gen_ports(IR__::ComponentDef_ptr component) {

	// handle base component
	IR__::ComponentDef_var base = component->base_component();
	if(!CORBA::is_nil(base))
	{ 
		gen_ports(base);
	}

	// receptacles
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	CORBA::ULong i;
	for( i= 0; i < len; i++)
	{
		IR__::UsesDef_var a_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
 
		out << "<uses usesname=\"";
		out << a_uses -> name();
		out << "\" repid=\"" ;
		out << IR__::InterfaceDef::_narrow(a_uses -> interface_type()) -> id();
		out << "\"/>\n";

	}

	// facets
	contained_seq = component->contents(CORBA__::dk_Provides, false);
	len = contained_seq->length();
	for( i= 0; i < len; i++)
	{
		IR__::ProvidesDef_var a_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
 
		out << "<provides providesname=\"";
		out << a_provides -> name();
		out << "\" repid=\"" ;
		out << IR__::InterfaceDef::_narrow(a_provides -> interface_type()) -> id() << "\"" ;
		out << " facettag=\"" << facet_number_++ << "\"";
		out << "/>\n";
	}


	// emitters
	contained_seq = component->contents(CORBA__::dk_Emits, false);
	len = contained_seq->length();
	for( i= 0; i < len; i++)
	{
		IR__::EmitsDef_var a_emits = IR__::EmitsDef::_narrow(((*contained_seq)[i]));
 
		out << "<emits emitsname=\"";
		out << a_emits -> name();
		out << "\" eventtype=\"" ;
		out << a_emits -> event() -> id();
		out << "\">\n";
		out << "<eventpolicy policy=\"normal\"/>\n";
		out << "</emits>\n";
	}

	// publisher
	contained_seq = component->contents(CORBA__::dk_Publishes, false);
	len = contained_seq->length();
	for( i= 0; i < len; i++)
	{
		IR__::EventPortDef_var a_publishes = IR__::EventPortDef::_narrow(((*contained_seq)[i]));
 
		out << "<publishes publishesname=\"";
		out << a_publishes -> name();
		out << "\" eventtype=\"" ;
		out << a_publishes -> event() -> id();
		out << "\">\n";
		out << "<eventpolicy policy=\"normal\"/>\n";
		out << "</publishes>\n";
	}

	// consumer
	contained_seq = component->contents(CORBA__::dk_Consumes, false);
	len = contained_seq->length();
	for( i= 0; i < len; i++)
	{
		IR__::ConsumesDef_var a_consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
 
		out << "<consumes consumesname=\"";
		out << a_consumes -> name();
		out << "\" eventtype=\"" ;
		out << a_consumes -> event () -> id();
		out << "\">\n";
		out << "<eventpolicy policy=\"normal\"/>\n";
		out << "</consumes>\n";
	}
}


} // namespace

