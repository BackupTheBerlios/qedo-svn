#include "GeneratorCCD.h"
#include "Debug.h"

#include <string>


namespace QEDO_CIDL_Generator {


GeneratorCCD::GeneratorCCD
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase ( repository )
{
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
	initialize(target, fileprefix);
	doGenerate();
}


//
// module
//
void
GeneratorCCD::doModule(IR__::ModuleDef_ptr module)
{
}


//
// composition
//
void
GeneratorCCD::doComposition(CIDL::CompositionDef_ptr composition)
{
	filename_ = "";

	std::string id = composition->id();
	IR__::Contained_ptr module_def = 0;
	std::string::size_type pos = id.find_last_of("/");
	if(pos != std::string::npos)
	{
		id.replace(pos, string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		filename_ = mapAbsoluteName(module_def, "_");
		filename_.append("_");
	}
	
	// open output file
	filename_.append(composition->name());
	filename_.append(".ccd");
	out.open(filename_.c_str());

	out << "<?xml version = '1.0' ?>\n";
	out << "<!DOCTYPE corbacomponent PUBLIC \"-//OMG//DTD CORBA Component Descriptor\"";
	out << " \"http://cif.sourceforge.net/corbacomponent.dtd\">\n\n";

	out << "<corbacomponent>\n";
	out.indent();
    out << "<corbaversion>3.0</corbaversion>\n";
	out << "<componentrepid repid=\"" << composition->ccm_component()->id() << "\"/>\n";
    out << "<homerepid repid=\"" << composition->ccm_home()->id() << "\"/>\n";
    
	out << "<componentkind>\n";
	out.indent();
    out << "<session>\n";
	out.indent();
    out << "<servant lifetime=\"container\"/>\n";
	out.unindent();
    out << "</session>\n";
	out.unindent();
    out << "</componentkind>\n";

    out << "<threading policy=\"multithread\"/>\n";
    out << "<configurationcomplete set=\"true\"/>\n";
	
	//<segment name="Seg" segmenttag="">
    //    <segmentmember facettag="the_fork"/>
    //</segment>
    
	out << "<homefeatures name=\"" << composition->ccm_home()->name();
	out << "\" repid=\"" << composition->ccm_home()->id() << "\">\n";
    out << "</homefeatures>\n";
    out << "<componentfeatures name=\"" << composition->ccm_component()->name();
	out << "\" repid=\"" << composition->ccm_component()->id() << "\">\n";
    out.indent();
	out << "<ports>\n";
    //out << "        <provides providesname="the_fork" repid="IDL:dinner/Fork:1.0" facettag="the_fork"/>
    //        <provides providesname="the_name" repid="IDL:dinner/Named:1.0" facettag="the_name"/>
    out << "</ports>\n";
	out.unindent();
    out << "</componentfeatures>\n";
	out.unindent();
	out << "</corbacomponent>";

	// close file
	out.close();
}


} // namespace

