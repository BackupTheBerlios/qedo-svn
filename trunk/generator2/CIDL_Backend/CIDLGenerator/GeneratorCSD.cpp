#include "GeneratorCSD.h"
#include "Debug.h"

#include <string>


namespace QEDO_CIDL_Generator {


GeneratorCSD::GeneratorCSD
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase ( repository )
{
}


GeneratorCSD::~GeneratorCSD
()
{
}


void
GeneratorCSD::check_for_generation(IR__::Contained_ptr item)
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
GeneratorCSD::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	idlfilename_ = file_prefix_ + "_EQUIVALENT.idl";

	doGenerate();
}


//
// composition
//
void
GeneratorCSD::doComposition(CIDL::CompositionDef_ptr composition)
{
	//
	// obtain uuid for the implementation
	//
	std::string uuid_string = "";
#ifdef _WIN32
	GUID guid;
	CoCreateGuid(&guid);
	LPOLESTR lpolestr;
	StringFromCLSID(guid, &lpolestr);
	uuid_string = *lpolestr;
	CoTaskMemFree(lpolestr);
#endif
	
	// open output file
	std::string name = mapAbsoluteName(composition, "_");
	filename_ = name + ".csd";
	out.open(filename_.c_str());

	out << "<?xml version = '1.0' ?>\n";
	out << "<!DOCTYPE softpkg PUBLIC \"-//OMG//DTD Software Package Descriptor\"";
	out << " \"http://cif.sourceforge.net/softpkg.dtd\">\n\n";
	out << "<softpkg name=\"" << composition->name() << "_softpkg\" version=\"1,0\">\n\n";
	out.indent();
    out << "<pkgtype>CORBA Component</pkgtype>\n";
    out << "<title></title>\n";
    out << "<author></author>\n";
    out << "<description></description>\n";
    out << "<license href=\"\" />\n";
	// the id should be of the component but is of the home currently for deployment reason
    out << "<idl id=\"" << composition->ccm_home()->id() << "\">\n";
	out.indent();
	out << "<fileinarchive name=\"" << idlfilename_ << "\"/>\n";
	out.unindent();
	out << "</idl>\n\n";

    out << "<implementation id=\"" << uuid_string << "\">\n";
	out.indent();
    out << "<os name=\"Win\" />\n";
    out << "<processor name=\"x86\" />\n";
    out << "<compiler name=\"VC++\" version=\"7,0\" />\n";
    out << "<programminglanguage name=\"C++\" />\n";
    out << "<dependency type=\"DLL\"><localfile name=\"jtcd.dll\"/></dependency>\n";
    out << "<dependency type=\"DLL\"><localfile name=\"obd.dll\"/></dependency>\n";
    out << "<descriptor type=\"CORBA-Component\">\n";
	out.indent();
    out << "<fileinarchive name=\"" << name << ".ccd\" />\n";
	out.unindent();
    out << "</descriptor>\n";
    out << "<code type=\"DLL\">\n";
	out.indent();
    out << "<fileinarchive name=\"" << name << "E.dll\"/>\n";
	out.indent();
    out << "<entrypoint>create_" << composition->ccm_home()->name() << "E</entrypoint>\n";
	out << "<usage>executor</usage>\n";
	out.unindent();
    out << "</code>\n\n";
	out << "<code type=\"DLL\">\n";
	out.indent();
    out << "<fileinarchive name=\"" << name << "S.dll\"/>\n";
	out.indent();
    out << "<entrypoint>create_" << composition->ccm_home()->name() << "S</entrypoint>\n";
	out << "<usage>servant</usage>\n";
	out.unindent();
    out << "</code>\n";
	out.unindent();
    out << "</implementation>\n";

	out.unindent();
	out << "</softpkg>\n";
	
	// close file
	out.close();
}


} // namespace

