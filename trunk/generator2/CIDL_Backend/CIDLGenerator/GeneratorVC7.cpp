#include "GeneratorVC7.h"
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


GeneratorVC7::GeneratorVC7
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase(repository), uid_(0)
{
}


GeneratorVC7::~GeneratorVC7
()
{
}


void
GeneratorVC7::generate(std::string target, std::string fileprefix)
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
GeneratorVC7::doModule(IR__::ModuleDef_ptr module)
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
GeneratorVC7::doComposition(CIDL::CompositionDef_ptr composition)
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
		composition_name = mapAbsoluteName(module_def, "_");
		composition_name.append("_");
	}
	composition_name.append(composition->name());
	project_name = composition_name + "_EXECUTOR";
	servant_project_name = composition_name + "_SERVANT";

#ifdef WIN32
	_mkdir(project_name.c_str());
#else
	mkdir(project_name.c_str(), 0);
#endif
	filename_ = project_name + "/";
	filename_ = filename_ + project_name;
	filename_ = filename_ + ".vcproj";
	out.open(filename_.c_str());

	//
	// print executor project file
	//
	out << "<?xml version=\"1.0\" encoding = \"Windows-1252\"?>\n";
	out << "<VisualStudioProject\n";
	out.indent();
	out << "ProjectType=\"Visual C++\"\n";
	out << "Version=\"7.00\"\n";
	out << "Name=\"" << project_name << "\"\n";
	out << "ProjectGUID=\"{" << uid_++ << "}\"\n";
	out << "Keyword=\"Win32Proj\">\n";

	//
	// platforms
	//
	out << "<Platforms>\n";
	out.indent();
	out << "<Platform\n";
	out.indent();
	out << "Name=\"Win32\"/>\n";
	out.unindent();
	out.unindent();
	out << "</Platforms>\n";

	//
	// configurations
	//
	out << "<Configurations>\n";
	out.indent();
	out << "<Configuration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\"\n";
	out << "OutputDirectory=\"Debug\"\n";
	out << "IntermediateDirectory=\"Debug\"\n";
	out << "ConfigurationType=\"2\"\n";
	out << "CharacterSet=\"2\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCLCompilerTool\"\n";
	out << "Optimization=\"0\"\n";
	out << "AdditionalIncludeDirectories=\".;$(QEDO)\\include;$(ORBACUS)\\include;$(ORBACUS)\\include\\OB;../IDL\"\n";
	out << "PreprocessorDefinitions=\"ORBACUS_ORB;WIN32;_DEBUG;_WINDOWS;_USRDLL;EXECUTORMODULE_EXPORTS\"\n";
	out << "MinimalRebuild=\"TRUE\"\n";
	out << "BasicRuntimeChecks=\"3\"\n";
	out << "RuntimeLibrary=\"3\"\n";
	out << "RuntimeTypeInfo=\"TRUE\"\n";
	out << "UsePrecompiledHeader=\"0\"\n";
	out << "WarningLevel=\"3\"\n";
	out << "Detect64BitPortabilityProblems=\"FALSE\"\n";
	out << "DebugInformationFormat=\"4\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCLinkerTool\"\n";
	out << "AdditionalDependencies=\"ComponentIDL.lib obd.lib jtcd.lib\"\n";
	out << "OutputFile=\"$(OutDir)/" << project_name << ".dll\"\n";
	out << "LinkIncremental=\"2\"\n";
	out << "AdditionalLibraryDirectories=\"$(QEDO)\\lib;$(ORBACUS)\\lib\"\n";
	out << "GenerateDebugInformation=\"TRUE\"\n";
	out << "ProgramDatabaseFile=\"$(OutDir)/" << project_name << ".pdb\"\n";
	out << "SubSystem=\"2\"\n";
	out << "ImportLibrary=\"$(OutDir)/" << project_name << ".lib\"\n";
	out << "TargetMachine=\"1\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCMIDLTool\"/>\n";
	out.unindent();

	//
	// packaging
	//
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPostBuildEventTool\"\n";
	out << "CommandLine=\"wzzip.exe " << composition_name << ".zip ";
	out << "Debug/" << project_name << ".dll ";
	out << "Debug/" << servant_project_name << ".dll ";
	out << file_prefix_ << "_EQUIVALENT.idl ";
	out << composition_name << ".ccd ";
	out << composition_name << ".csd\"/>\n";
	out.unindent();

	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreLinkEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCResourceCompilerTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebServiceProxyGeneratorTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebDeploymentTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</Configuration>\n";
	out.unindent();
	out << "</Configurations>\n";
	out << "<Files>\n";
	out.indent();
	//
	// source files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"Source Files\"\n";
	out << "Filter=\"cpp;c;cxx;def;odl;idl;hpj;bat;asm\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_BUSINESS.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_BUSINESS_skel.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// header files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"Header Files\"\n";
	out << "Filter=\"h;hpp;hxx;hm;inl;inc\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_BUSINESS.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_BUSINESS_skel.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL.h\">\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// idl files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"idl\"\n";
	out << "Filter=\"idl;cidl\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"../" << target_file_name_ << "\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DORBACUS_ORB -DWIN32 -I$(QEDO)/include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB --business --target " << target_->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.idl;" << file_prefix_ << "_EQUIVALENT.idl;";
	out << file_prefix_ << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_BUSINESS.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_BUSINESS.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_BUSINESS.h;" << file_prefix_ << "_BUSINESS.cpp;";
	out << file_prefix_ << "_BUSINESS_skel.h;" << file_prefix_ << "_BUSINESS_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_EQUIVALENT.h;" << file_prefix_ << "_EQUIVALENT.cpp;";
	out << file_prefix_ << "_EQUIVALENT_skel.h;" << file_prefix_ << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// resource files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"Resource Files\"\n";
	out << "Filter=\"rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\">\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// xml files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"xml\"\n";
	out << "Filter=\"ccd;csd\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".csd\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".ccd\">\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	out.unindent();
	out << "</Files>\n";
	out << "<Globals>\n";
	out << "</Globals>\n";
	out.unindent();
	out << "</VisualStudioProject>\n";

	//
	// close executor file
	//
	out.close();
}


/**
 *
 */
void
GeneratorVC7::generateServant()
{
	std::string uuid_string = "";
#ifdef _WIN32
	// create uuid
	GUID guid;
	CoCreateGuid(&guid);
	LPOLESTR lpolestr;
	StringFromCLSID(guid, &lpolestr);
	int i = wcstombs(NULL, lpolestr, 0);
    char *buf = (char *)malloc(i);
    wcstombs(buf, lpolestr, i);
	// remove { and }
	buf[i - 1] = '\0';
	uuid_string = buf;
	uuid_string.erase(0, 1);
	free(buf);
	CoTaskMemFree(lpolestr);
#endif

	//
	// build file name for servant project and open file
	//
	std::string project_name = file_prefix_ + "_SERVANT";

#ifdef WIN32
	_mkdir(project_name.c_str());
#else
	mkdir(project_name.c_str(), 0);
#endif

	filename_ = project_name + "/";
	filename_ = filename_ + project_name;
	filename_ = filename_ + ".vcproj";
	out.open(filename_.c_str());

	//
	// print servant project file
	//
	out << "<?xml version=\"1.0\" encoding = \"Windows-1252\"?>\n";
	out << "<VisualStudioProject\n";
	out.indent();
	out << "ProjectType=\"Visual C++\"\n";
	out << "Version=\"7.00\"\n";
	out << "Name=\"" << project_name << "\"\n";
	out << "ProjectGUID=\"{" << uuid_string << "}\"\n";
	out << "Keyword=\"Win32Proj\">\n";

	//
	// platforms
	//
	out << "<Platforms>\n";
	out.indent();
	out << "<Platform\n";
	out.indent();
	out << "Name=\"Win32\"/>\n";
	out.unindent();
	out.unindent();
	out << "</Platforms>\n";

	//
	// configurations
	//
	out << "<Configurations>\n";
	out.indent();
	//
	// orbacus
	//
	out << "<Configuration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\"\n";
	out << "OutputDirectory=\"Debug_orbacus\"\n";
	out << "IntermediateDirectory=\"Debug_orbacus\"\n";
	out << "ConfigurationType=\"2\"\n";
	out << "CharacterSet=\"2\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCLCompilerTool\"\n";
	out << "Optimization=\"0\"\n";
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(ORBACUS)/include;$(ORBACUS)/include/OB\"\n";
	out << "PreprocessorDefinitions=\"WIN32;_DEBUG;_WINDOWS;_USRDLL;SERVANTMODULE_EXPORTS\"\n";
	out << "MinimalRebuild=\"TRUE\"\n";
	out << "BasicRuntimeChecks=\"3\"\n";
	out << "RuntimeLibrary=\"3\"\n";
	out << "RuntimeTypeInfo=\"TRUE\"\n";
	out << "UsePrecompiledHeader=\"0\"\n";
	out << "WarningLevel=\"3\"\n";
	out << "Detect64BitPortabilityProblems=\"FALSE\"\n";
	out << "DebugInformationFormat=\"4\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCLinkerTool\"\n";
	out << "AdditionalDependencies=\"ComponentContainer.lib ComponentIDL.lib obd.lib jtcd.lib\"\n";
	out << "OutputFile=\"$(OutDir)/" << project_name << ".dll\"\n";
	out << "LinkIncremental=\"2\"\n";
	out << "AdditionalLibraryDirectories=\"$(QEDO)/lib;$(ORBACUS)/lib\"\n";
	out << "GenerateDebugInformation=\"TRUE\"\n";
	out << "ProgramDatabaseFile=\"$(OutDir)/" << project_name << ".pdb\"\n";
	out << "SubSystem=\"2\"\n";
	out << "ImportLibrary=\"$(OutDir)/" << project_name << ".lib\"\n";
	out << "TargetMachine=\"1\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCMIDLTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPostBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreLinkEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCResourceCompilerTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebServiceProxyGeneratorTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebDeploymentTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</Configuration>\n";
	//
	// mico
	//
	out << "<Configuration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\"\n";
	out << "OutputDirectory=\"Debug_mico\"\n";
	out << "IntermediateDirectory=\"Debug_mico\"\n";
	out << "ConfigurationType=\"2\"\n";
	out << "CharacterSet=\"2\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCLCompilerTool\"\n";
	out << "Optimization=\"0\"\n";
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(MICO)/include;$(MICO)/include/windows\"\n";
	out << "PreprocessorDefinitions=\"WIN32;_DEBUG;_WINDOWS;_USRDLL;SERVANTMODULE_EXPORTS\"\n";
	out << "MinimalRebuild=\"TRUE\"\n";
	out << "BasicRuntimeChecks=\"3\"\n";
	out << "RuntimeLibrary=\"3\"\n";
	out << "RuntimeTypeInfo=\"TRUE\"\n";
	out << "UsePrecompiledHeader=\"0\"\n";
	out << "WarningLevel=\"3\"\n";
	out << "Detect64BitPortabilityProblems=\"FALSE\"\n";
	out << "DebugInformationFormat=\"4\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCLinkerTool\"\n";
	out << "AdditionalDependencies=\"ComponentContainer.lib ComponentIDL.lib mico239.lib\"\n";
	out << "OutputFile=\"$(OutDir)/" << project_name << ".dll\"\n";
	out << "LinkIncremental=\"2\"\n";
	out << "AdditionalLibraryDirectories=\"$(QEDO)/lib;$(MICO)/win32-bin/lib\"\n";
	out << "GenerateDebugInformation=\"TRUE\"\n";
	out << "ProgramDatabaseFile=\"$(OutDir)/" << project_name << ".pdb\"\n";
	out << "SubSystem=\"2\"\n";
	out << "ImportLibrary=\"$(OutDir)/" << project_name << ".lib\"\n";
	out << "TargetMachine=\"1\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCMIDLTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPostBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreLinkEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCResourceCompilerTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebServiceProxyGeneratorTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebDeploymentTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</Configuration>\n";
	//
	// tao
	//
	out << "<Configuration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\"\n";
	out << "OutputDirectory=\"Debug_tao\"\n";
	out << "IntermediateDirectory=\"Debug_tao\"\n";
	out << "ConfigurationType=\"2\"\n";
	out << "CharacterSet=\"2\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCLCompilerTool\"\n";
	out << "Optimization=\"0\"\n";
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(TAO)\"\n";
	out << "PreprocessorDefinitions=\"WIN32;_DEBUG;_WINDOWS;_USRDLL;SERVANTMODULE_EXPORTS\"\n";
	out << "MinimalRebuild=\"TRUE\"\n";
	out << "BasicRuntimeChecks=\"3\"\n";
	out << "RuntimeLibrary=\"3\"\n";
	out << "RuntimeTypeInfo=\"TRUE\"\n";
	out << "UsePrecompiledHeader=\"0\"\n";
	out << "WarningLevel=\"3\"\n";
	out << "Detect64BitPortabilityProblems=\"FALSE\"\n";
	out << "DebugInformationFormat=\"4\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCLinkerTool\"\n";
	out << "AdditionalDependencies=\"ComponentContainer.lib ComponentIDL.lib aced.lib TAOd.lib\"\n";
	out << "OutputFile=\"$(OutDir)/" << project_name << ".dll\"\n";
	out << "LinkIncremental=\"2\"\n";
	out << "AdditionalLibraryDirectories=\"$(QEDO)/lib;$(ORBACUS)/lib\"\n";
	out << "GenerateDebugInformation=\"TRUE\"\n";
	out << "ProgramDatabaseFile=\"$(OutDir)/" << project_name << ".pdb\"\n";
	out << "SubSystem=\"2\"\n";
	out << "ImportLibrary=\"$(OutDir)/" << project_name << ".lib\"\n";
	out << "TargetMachine=\"1\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCMIDLTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPostBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreBuildEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCPreLinkEventTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCResourceCompilerTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebServiceProxyGeneratorTool\"/>\n";
	out.unindent();
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCWebDeploymentTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</Configuration>\n";

	out.unindent();
	out << "</Configurations>\n";

	//
	// files
	//
	out << "<Files>\n";
	out.indent();
	//
	// source files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"Source Files\"\n";
	out << "Filter=\"cpp;c;cxx;def;odl;idl;hpj;bat;asm\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_SERVANT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT_skel.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL_skel.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// header files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"Header Files\"\n";
	out << "Filter=\"h;hpp;hxx;hm;inl;inc\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_SERVANT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT_skel.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL_skel.h\">\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// idl files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"idl\"\n";
	out << "Filter=\"idl;cidl\">\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"../" << target_file_name_ << "\">\n";
	//
	// orbacus
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DWIN32 -DORBACUS_ORB -I$(QEDO)/include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB --servant --target " << target_->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.idl;" << file_prefix_ << "_EQUIVALENT.idl;";
	out << file_prefix_ << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	//
	// mico
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DWIN32 -DMICO_ORB -I$(QEDO)/include -I$(MICO)/idl ";
	out << "-I$(ORBACUS)/idl/OB --servant --target " << target_->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.idl;" << file_prefix_ << "_EQUIVALENT.idl;";
	out << file_prefix_ << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	//
	// tao
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DWIN32 -DTAO_ORB -I$(QEDO)/include -I$(TAO)/idl ";
	out << "-I$(ORBACUS)/idl/OB --servant --target " << target_->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.idl;" << file_prefix_ << "_EQUIVALENT.idl;";
	out << file_prefix_ << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_EQUIVALENT.idl\">\n";
	//
	// orbacus
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)\\bin\\idl -DORBACUS_ORB -DWIN32 -I$(QEDO)\\include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_EQUIVALENT.h;" << file_prefix_ << "_EQUIVALENT.cpp;";
	out << file_prefix_ << "_EQUIVALENT_skel.h;" << file_prefix_ << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	//
	// mico
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(MICO)\\win32-bin\\idl -I$(MICO)\\include -I$(MICO)\\include\\mico --any --c++-suffix cpp --c++-skel -DWIN32 -I$(QEDO)\\include ";
	out << file_prefix_ << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_EQUIVALENT.h;" << file_prefix_ << "_EQUIVALENT.cpp;";
	out << file_prefix_ << "_EQUIVALENT_skel.h;" << file_prefix_ << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	//
	// tao
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(TAO)\\bin\\tao_idl -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp -DTAO_ORB -DWIN32 -I$(QEDO)\\include ";
	out << "-I$(TAO)/idl " << file_prefix_ << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_EQUIVALENT.h;" << file_prefix_ << "_EQUIVALENT.cpp;";
	out << file_prefix_ << "_EQUIVALENT_skel.h;" << file_prefix_ << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << file_prefix_ << "_LOCAL.idl\">\n";
	//
	// orbacus
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)\\bin\\idl -DORBACUS_ORB -DWIN32 -I$(QEDO)\\include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	//
	// mico
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)\\bin\\idl -DWIN32 -I$(QEDO)\\include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	//
	// tao
	//
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)\\bin\\idl -DWIN32 -I$(QEDO)\\include -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out.unindent();
	out << "</Filter>\n";
	//
	// resource files
	//
	out << "<Filter\n";
	out.indent();
	out << "Name=\"Resource Files\"\n";
	out << "Filter=\"rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\">\n";
	out.unindent();
	out << "</Filter>\n";
	out.unindent();
	out << "</Files>\n";
	out << "<Globals>\n";
	out << "</Globals>\n";
	out.unindent();
	out << "</VisualStudioProject>\n";

	//
	// close servant file
	//
	out.close();
}


}
