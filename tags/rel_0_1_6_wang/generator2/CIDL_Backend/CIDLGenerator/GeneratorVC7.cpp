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

#ifdef WIN32
	_mkdir(project_name.c_str());
#else
	mkdir(project_name.c_str(), 0755);
#endif
	filename_ = project_name + "/";
	filename_ = filename_ + project_name;
	filename_ = filename_ + ".vcproj";
	out.open(filename_.c_str());

	//
	// build export define needed for MICO on windows
	//
	std::string export_prefix_;
	for (unsigned long i = 0; i < project_name.size(); i++) {
		export_prefix_+= toupper(project_name[i]);
    }

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
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(ORBACUS)/include;$(ORBACUS)/include/OB;\"\n";
	out << "PreprocessorDefinitions=\"ORBACUS_ORB;WIN32;_DEBUG;_USRDLL;EXECUTORMODULE_EXPORTS;_QEDO_NO_QOS\"\n";
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
	out << "AdditionalDependencies=\"ComponentIDL.lib ComponentContainer.lib obd.lib jtcd.lib\"\n";
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
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(MICO)/include;\"\n";
	out << "PreprocessorDefinitions=\"";
	out << "BUILD_" << export_prefix_ << "_DLL;MICO_ORB;WIN32;_DEBUG;_USRDLL;HAVE_THREADS;HAVE_PTHREADS;PtW32NoCatchWarn;__CLEANUP_C;_WIN32_WINNT=0x400;_QEDO_NO_QOS\"\n";
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
	out << "AdditionalDependencies=\"ComponentIDL.lib ComponentContainer.lib  mico2311.lib pthreadVC.lib\"\n";
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
	// TAO
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
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(MICO)/include;\"\n";
	out << "PreprocessorDefinitions=\"MICO_ORB;WIN32;_DEBUG;_USRDLL;EXECUTORMODULE_EXPORTS;_QEDO_NO_QOS\"\n";
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
	out << "AdditionalDependencies=\"ComponentIDL.lib ComponentContainer.lib mico2311.lib\"\n";
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
	out << "RelativePath=\"valuetypes.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_BUSINESS.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_BUSINESS_skel.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_EQUIVALENT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_LOCAL.cpp\">\n";
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
	out << "RelativePath=\"valuetypes.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_BUSINESS.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_BUSINESS_skel.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_EQUIVALENT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_LOCAL.h\">\n";
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
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling CIDL\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB --business -d --target " << composition->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << project_name << "_LOCAL.idl;" << project_name << "_EQUIVALENT.idl;";
	out << project_name << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling CIDL\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DMICO_ORB -DMICO_CIDL_GEN -DWIN32";
	out << " -I$(QEDO)/idl -I$(MICO)/include -I$(MICO)/include/mico --business -d --target ";
	out << composition->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << project_name << "_LOCAL.idl;" << project_name << "_EQUIVALENT.idl;";
	out << project_name << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";

	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_BUSINESS.idl\">\n";
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling business IDL\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << project_name << "_BUSINESS.idl\"\n";
	out << "Outputs=\"" << project_name << "_BUSINESS.h;" << project_name << "_BUSINESS.cpp;";
	out << project_name << "_BUSINESS_skel.h;" << project_name << "_BUSINESS_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling business IDL\"\n";
	out << "CommandLine=\"$(MICO)/win32-bin/idl -DMICO_ORB -DWIN32 -I$(MICO)/include -I$(MICO)/include/mico -I$(QEDO)/idl ";
	out << " --any --typecode --c++-skel --c++-suffix cpp --relative-paths --windows-dll ";
	out << project_name << " " << project_name << "_BUSINESS.idl\n";
	out << "copy " << project_name << "_BUSINESS.h " << project_name << "_BUSINESS_skel.h\"\n";
	out << "Outputs=\"" << project_name << "_BUSINESS.h;" << project_name << "_BUSINESS.cpp;";
	out << project_name << "_BUSINESS_skel.h;" << project_name << "_BUSINESS_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";

	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_EQUIVALENT.idl\">\n";
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling equivalent IDL\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << project_name << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << project_name << "_EQUIVALENT.h;" << project_name << "_EQUIVALENT.cpp;";
	out << project_name << "_EQUIVALENT_skel.h;" << project_name << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling equivalent IDL\"\n";
	out << "CommandLine=\"$(MICO)/win32-bin/idl -DMICO_ORB -DWIN32 -I$(MICO)/include -I$(MICO)/include/mico -I$(QEDO)/idl  ";
	out << "--any --typecode --c++-skel --c++-suffix cpp --relative-paths --windows-dll ";
	out << project_name << " " << project_name << "_EQUIVALENT.idl\n";
	out << "copy " << project_name << "_EQUIVALENT.h " << project_name << "_EQUIVALENT_skel.h\"\n";
	out << "Outputs=\"" << project_name << "_EQUIVALENT.h;" << project_name << "_EQUIVALENT.cpp;";
	out << project_name << "_EQUIVALENT_skel.h;" << project_name << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";

	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << project_name << "_LOCAL.idl\">\n";
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling local IDL\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << project_name << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << project_name << "_LOCAL.h;" << project_name << "_LOCAL.cpp;";
	out << project_name << "_LOCAL_skel.h;" << project_name << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling local IDL\"\n";
	out << "CommandLine=\"$(MICO)/win32-bin/idl -DMICO_ORB -DWIN32 -I$(MICO)/include -I$(MICO)/include/mico -I$(QEDO)/idl ";
	out << "--any --typecode --c++-skel --c++-suffix cpp --relative-paths --windows-dll ";
	out << project_name << " " << project_name << "_LOCAL.idl\n";
	out << "copy " << project_name << "_LOCAL.h " << project_name << "_LOCAL_skel.h\"\n";
	out << "Outputs=\"" << project_name << "_LOCAL.h;" << project_name << "_LOCAL.cpp;";
	out << project_name << "_LOCAL_skel.h;" << project_name << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
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
	out << "RelativePath=\"" << composition_name << ".ccd\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << composition_name << ".csd\">\n";
	out.unindent();
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
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
	std::string uuid_string = uuidgen();

	//
	// build file name for servant project and open file
	//
	std::string project_name;
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
	project_name.append("_SERVANT");

#ifdef WIN32
	_mkdir(project_name.c_str());
#else
	mkdir(project_name.c_str(), 0755);
#endif

	filename_ = project_name + "/" + project_name + ".vcproj";
	out.open(filename_.c_str());

	//
	// biuld eport define needed for MICO on windows
	//
	std::string export_prefix_;
	for (unsigned long i = 0; i < file_prefix_.size(); i++) {
		export_prefix_+= toupper(file_prefix_[i]);
    }

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
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(ORBACUS)/include;$(ORBACUS)/include/OB;\"\n";
	out << "PreprocessorDefinitions=\"_DEBUG;_USRDLL;SERVANTMODULE_EXPORTS;_QEDO_NO_QOS\"\n";
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
	out << "AdditionalDependencies=\"ComponentIDL.lib ComponentContainer.lib qedoutil.lib obd.lib jtcd.lib\"\n";
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
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/include;$(MICO)/include;$(MICO)/include/windows;\"\n";
	out << "PreprocessorDefinitions=\"";
	out << "BUILD_" << export_prefix_ << "_DLL;MICO_ORB;WIN32;_DEBUG;_USRDLL;HAVE_THREADS;HAVE_PTHREADS;PtW32NoCatchWarn;__CLEANUP_C;_WIN32_WINNT=0x400;_QEDO_NO_QOS\"\n";
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
	out << "AdditionalDependencies=\"ComponentIDL.lib ComponentContainer.lib qedoutil.lib mico2311.lib pthreadVC.lib\"\n";
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
	out << "PreprocessorDefinitions=\"WIN32;_DEBUG;_WINDOWS;_USRDLL;SERVANTMODULE_EXPORTS;_QEDO_NO_QOS\"\n";
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
	out << "AdditionalDependencies=\"ComponentIDL.lib ComponentContainer.lib qedoutil.lib aced.lib TAOd.lib\"\n";
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
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling CIDL\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB --servant --target " << target_->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.idl;" << file_prefix_ << "_EQUIVALENT.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling CIDL\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DMICO_ORB -DMICO_CIDL_GEN -DWIN32 ";
	out << " -I$(QEDO)/idl -I$(MICO)/include -I$(MICO)/include/mico --servant --target " << target_->id() << " ../" << target_file_name_ << "\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.idl;" << file_prefix_ << "_EQUIVALENT.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DWIN32 -DTAO_ORB -I$(QEDO)/idl -I$(TAO)/idl ";
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
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling equivalent IDL\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_EQUIVALENT.h;" << file_prefix_ << "_EQUIVALENT.cpp;";
	out << file_prefix_ << "_EQUIVALENT_skel.h;" << file_prefix_ << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling equivalent IDL\"\n";
	out << "CommandLine=\"$(MICO)/win32-bin/idl -DMICO_ORB -DWIN32 -I$(MICO)/include -I$(MICO)/include/mico -I$(QEDO)/idl ";
	out << "--any --typecode --c++-skel --c++-suffix cpp --relative-paths --windows-dll ";
	out << file_prefix_ << " " << file_prefix_ << "_EQUIVALENT.idl\n";
	out << "copy " << file_prefix_ << "_EQUIVALENT.h " << file_prefix_ << "_EQUIVALENT_skel.h\"\n";
	out << "Outputs=\"" << file_prefix_ << "_EQUIVALENT.h;" << file_prefix_ << "_EQUIVALENT.cpp;";
	out << file_prefix_ << "_EQUIVALENT_skel.h;" << file_prefix_ << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(TAO)/bin/tao_idl -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp -DTAO_ORB -DWIN32 -I$(QEDO)/idl ";
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
	// orbacus
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_orbacus|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling local IDL\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DORBACUS_ORB -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << file_prefix_ << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// mico
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_mico|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "Description=\"..... compiling local IDL\"\n";
	out << "CommandLine=\"$(MICO)/win32-bin/idl -DMICO_ORB -DWIN32 -I$(MICO)/include -I$(MICO)/include/mico -I$(QEDO)/idl ";
	out << "--any --typecode --c++-skel --c++-suffix cpp --relative-paths --windows-dll ";
	out << file_prefix_ << " " << file_prefix_ << "_LOCAL.idl\n";
	out << "copy " << file_prefix_ << "_LOCAL.h " << file_prefix_ << "_LOCAL_skel.h\"\n";
	out << "Outputs=\"" << file_prefix_ << "_LOCAL.h;" << file_prefix_ << "_LOCAL.cpp;";
	out << file_prefix_ << "_LOCAL_skel.h;" << file_prefix_ << "_LOCAL_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	// tao
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug_tao|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/idl -I$(ORBACUS)/idl ";
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
