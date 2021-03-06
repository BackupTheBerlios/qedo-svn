#include "GeneratorCCD.h"
#include "Debug.h"

#include <string>


using namespace std;


namespace QEDO_CIDL_Generator {


GeneratorCCD::GeneratorCCD
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: GeneratorBase ( repository )
{
}


GeneratorCCD::~GeneratorCCD
()
{
}


void
GeneratorCCD::generate(string target)
{
	doGenerate(target);
}


void
GeneratorCCD::doComposition(CIDL::CompositionDef_ptr composition)
{
	filename_ = "";

	string id = composition->id();
	IR__::Contained_ptr module_def = 0;
	string::size_type pos = id.find_last_of("/");
	if(pos != string::npos)
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
	out << "\"http://cif.sourceforge.net/corbacomponent.dtd\">\n\n";

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
	out << "\" repid=\"" << composition->ccm_home()->id() << "\"/>\n";
    out << "</homefeatures>\n";
    out << "<componentfeatures name=\"" << composition->ccm_component()->name();
	out << "\" repid=\"" << composition->ccm_component()->id() << "\"/>\n";
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


} // namespace HU_CIDL_Generator