#include "GeneratorMakefile.h"
#include "Debug.h"
#include <string>


#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#include <objbase.h>
#else
#include "sys/stat.h"
#endif


namespace QEDO_CIDL_Generator {


GeneratorMakefile::GeneratorMakefile
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository), uid_(0)
{
}


GeneratorMakefile::~GeneratorMakefile
()
{
}

void
GeneratorMakefile::generate(std::string target, std::string fileprefix)
{
	try { initialize(target, fileprefix); }
	catch (InitializeError) { return; }

	doGenerate();
	generateServant();
}


//
// module
//
void
GeneratorMakefile::doModule(IR__::ModuleDef_ptr module)
{
	// contained modules
	handleModule(module);

	// contained compositions
	handleComposition(repository_);
}

//
// composition
//
void
GeneratorMakefile::doComposition(CIDL::CompositionDef_ptr composition)
{
	//
	// build file name for executor project and open file
	//
	std::string id = composition->id();
	std::string project_name;
	std::string servant_project_name;
	std::string composition_name;
	IR__::Contained_ptr module_def = 0;
	std::string::size_type pos = id.find_last_of("/");
	if(pos != std::string::npos)
	{
		id.replace(pos, std::string::npos, ":1.0");
		module_def = repository_->lookup_id(id.c_str());
		composition_name = getAbsoluteName(module_def, "_");
		composition_name.append("_");
	}
	composition_name.append(composition->name());
	project_name = composition_name;
	servant_project_name = composition_name + "_SERVANT";

#ifdef WIN32
	_mkdir(project_name.c_str());
#else
	mkdir(project_name.c_str(), 0755);
#endif
	filename_ = project_name + "/Makefile";
	out.open(filename_.c_str());

	out << "ORB_IDL_INCLUDE = -I..\n\n";

	out << "CIDL_FILES = ../" << target_file_name_ << "\n\n";
	out << "IDL_FILES = " << composition_name << "_LOCAL.idl \\\n";
	out << "\t" << composition_name << "_EQUIVALENT.idl \\\n";
	out << "\t" << composition_name << "_BUSINESS.idl \n\n";

	out << "CPP_FILES = " << composition_name << "_BUSINESS.cpp \\\n";
//	out << "\t" << composition_name << "_EQUIVALENT.cpp \\\n";
//	out << "\t" << composition_name << "_LOCAL.cpp \\\n";
	out << "\t" << composition_name << ".cpp \\\n";
	out << "\tvaluetypes.cpp \n\n";


	out << "OBJ_FILES = ${CPP_FILES:%.cpp=%.o} \n\n";

	out << "CLEAN_FILES = OBJ_FILES lib" << composition_name << ".so " << composition_name << ".zip\n\n";

	out << "LIBS += -L../" << composition_name << "_SERVANT -l";
	out << composition_name << "_SERVANT \n\n";

	out << "CXXFLAGS += -I. -g\n\n";

	out << "include ../MakeComponentVars\n\n";

	out << "all: lib" << composition_name << ".so \n\n";

	out << "lib" << composition_name << ".so: ${OBJ_FILES} \n\n";

	out << "${IDL_FILES} valuetypes.cpp : ${CIDL_FILES} \n";
	out << "\t${CIDL_GEN} -I${QEDO}/idl -I${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \\\n";
	out << "\t--business --target \"" << composition->id() << "\" $< \n\n";

	out << composition_name << "_BUSINESS.cpp: " << composition_name << "_EQUIVALENT.h ";
	out << composition_name << "_LOCAL.h \n\n";

	out << composition_name << ".cpp: " << composition_name << "_BUSINESS.h\n\n";

	out << "package: " << composition_name << ".zip\n\n";

	out << composition_name << ".zip : meta-inf/" << composition_name << ".ccd ";
	out << "meta-inf/" << composition_name <<".csd lib" << composition_name << ".so\n";
	out << "\tzip " << composition_name << ".zip -j ../" << composition_name;
	out << "_SERVANT/lib" << composition_name << "_SERVANT.so ";
	out << "lib" << composition_name << ".so $(CIDL_FILES)\n";
	out << "\tzip " << composition_name << ".zip meta-inf/" << composition_name;
	out << ".ccd meta-inf/" << composition_name << ".csd\n\n";

	out << "meta-inf/" << composition_name;
	out << ".ccd meta-inf/" << composition_name << ".csd :\n";
	out << "\t[ -d meta-inf ] || mkdir ./meta-inf\n";
	out << "\t(cd meta-inf && ${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \\\n";
	out << "\t-d --target \"" << composition->id() << "\" ../$(CIDL_FILES) )\n\n";

//
// close output file
//
	out.close();
}




/**
 *
 */
void
GeneratorMakefile::generateServant()
{
    std::string uuid_string = uuidgen();
//
// build file name for servant project and open file
//
    std::string project_name;
    std::string target_name;
    IR__::Contained_ptr module_def = 0;
    std::string target_id = target_->id();
    std::string::size_type pos = target_id.find_last_of("/");
    if(pos != std::string::npos)
    {
	target_id.replace(pos, std::string::npos, ":1.0");
	module_def = repository_->lookup_id(target_id.c_str());
	project_name = getAbsoluteName(module_def, "_");
	project_name.append("_");
    }
    project_name.append(target_->name());
    target_name = project_name;
    project_name.append("_SERVANT");

#ifdef WIN32
    _mkdir(project_name.c_str());
#else
    mkdir(project_name.c_str(), 0775);
#endif

    filename_ = project_name + "/Makefile";
    out.open(filename_.c_str());

//
// write makefile
//
    out << "ORB_IDL_INCLUDE = -I..\n\n";

    out << "CIDL_FILES = ../" << target_file_name_ <<  "\n\n";

    out << "IDL_FILES = " << target_name << "_LOCAL.idl \\\n";
    out << "\t" << target_name << "_EQUIVALENT.idl\n\n";

    out << "CPP_FILES = " << target_name << "_EQUIVALENT.cpp \\\n";
    out << "\t" << target_name << "_EQUIVALENT_skel.cpp \\\n";
    out << "\t" << target_name << "_LOCAL.cpp \\\n";
    out << "\t" << target_name << "_SERVANT.cpp\n\n";

    out << "OBJ_FILES = ${CPP_FILES:%.cpp=%.o}\n\n";

    out << "CLEAN_FILES = OBJ_FILES lib" << target_name << "_SERVANT.so\n\n";
    
    out << "CXXFLAGS += -I.\n\n";

    out << "include ../MakeComponentVars\n\n";

    out << "all: lib" << target_name << "_SERVANT.so\n\n";

    out << "lib" << target_name << "_SERVANT.so: ${OBJ_FILES}\n\n";

    out << "${IDL_FILES} " << target_name << "_SERVANT.cpp: ${CIDL_FILES}\n";
    out << "\t${CIDL_GEN} -I${QEDO}/idl ${ORB_IDL_INCLUDE} ${CIDL_ORB_DEF} \\\n";
    out << "\t--servant --target \"" << target_->id() << "\" $<\n\n";

}

} // namespace
