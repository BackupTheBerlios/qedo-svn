#include "GeneratorVC7.h"
#include "Debug.h"
#include <string>


namespace QEDO_CIDL_Generator {


GeneratorVC7::GeneratorVC7
( QEDO_ComponentRepository::CIDLRepository_impl *repository)
: CPPBase ( repository )
{
}


GeneratorVC7::~GeneratorVC7
()
{
}


void
GeneratorVC7::generate(std::string target, std::string fileprefix)
{
	initialize(target, fileprefix);
	doGenerate();
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
	int guid = 0;

	//
	// build file name for executor project and open file
	//
	std::string id = composition->id();
	std::string project_name;
	std::string composition_name;
	std::string idl_file_prefix = target_->name();
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
	filename_ = project_name + ".vcproj";
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
	out << "ProjectGUID=\"{" << guid++ << "}\"\n";
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
	out << "Name=\"Debug|Win32\"\n";
	out << "OutputDirectory=\"Debug\"\n";
	out << "IntermediateDirectory=\"Debug\"\n";
	out << "ConfigurationType=\"2\"\n";
	out << "CharacterSet=\"2\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCLCompilerTool\"\n";
	out << "Optimization=\"0\"\n";
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/ComponentIDL;$(ORBACUS)\\include;$(ORBACUS)\\include\\OB;../IDL\"\n";
	out << "PreprocessorDefinitions=\"WIN32;_DEBUG;_WINDOWS;_USRDLL;EXECUTORMODULE_EXPORTS\"\n";
	out << "MinimalRebuild=\"TRUE\"\n";
	out << "BasicRuntimeChecks=\"3\"\n";
	out << "RuntimeLibrary=\"2\"\n";
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
	out << "AdditionalLibraryDirectories=\"$(QEDO)\\ComponentIDL\\Debug;$(ORBACUS)\\lib\"\n";
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
	out << "Name=\"VCPostBuildEventTool\"\n";
	out << "CommandLine=\"wzzip.exe " << project_name << ".zip $(TargetPath) philosophers.idl philosopher.csd ";
	out << composition_name << ".ccd\n";
	out << "copy $(TargetPath) &quot;$(QEDO)\\..\\runtime&quot;\"/>\n";
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
	out << "RelativePath=\"" << idl_file_prefix << "_BUSINESS.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_BUSINESS_skel.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL.cpp\">\n";
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
	out << "RelativePath=\"" << idl_file_prefix << "_BUSINESS.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_BUSINESS_skel.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL.h\">\n";
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
	out << "RelativePath=\"" << target_file_name_ << "\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DWIN32 -I$(QEDO)/ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB --business --target " << target_->id() << " " << target_file_name_ << "\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_LOCAL.idl;" << idl_file_prefix << "_EQUIVALENT.idl;";
	out << idl_file_prefix << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_BUSINESS.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << idl_file_prefix << "_BUSINESS.idl\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_BUSINESS.h;" << idl_file_prefix << "_BUSINESS.cpp;";
	out << idl_file_prefix << "_BUSINESS_skel.h;" << idl_file_prefix << "_BUSINESS_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << idl_file_prefix << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_EQUIVALENT.h;" << idl_file_prefix << "_EQUIVALENT.cpp;";
	out << idl_file_prefix << "_EQUIVALENT_skel.h;" << idl_file_prefix << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)/bin/idl -DWIN32 -I$(QEDO)/ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << idl_file_prefix << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_LOCAL.h;" << idl_file_prefix << "_LOCAL.cpp;";
	out << idl_file_prefix << "_LOCAL_skel.h;" << idl_file_prefix << "_LOCAL_skel.cpp\"/>\n";
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

	//
	// build file name for servant project and open file
	//
	project_name = composition_name + "_SERVANT";
	filename_ = project_name + ".vcproj";
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
	out << "ProjectGUID=\"{" << guid++ << "}\"\n";
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
	out << "Name=\"Debug|Win32\"\n";
	out << "OutputDirectory=\"Debug\"\n";
	out << "IntermediateDirectory=\"Debug\"\n";
	out << "ConfigurationType=\"2\"\n";
	out << "CharacterSet=\"2\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCLCompilerTool\"\n";
	out << "Optimization=\"0\"\n";
	out << "AdditionalIncludeDirectories=\".;$(QEDO)/ComponentIDL;$(ORBACUS)/include;$(ORBACUS)/include/OB;$(QEDO)/ComponentContainer\"\n";
	out << "PreprocessorDefinitions=\"WIN32;_DEBUG;_WINDOWS;_USRDLL;SERVANTMODULE_EXPORTS\"\n";
	out << "MinimalRebuild=\"TRUE\"\n";
	out << "BasicRuntimeChecks=\"3\"\n";
	out << "RuntimeLibrary=\"2\"\n";
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
	out << "AdditionalDependencies=\"ComponentContainer.lib;ComponentIDL.lib;obd.lib;jtcd.lib\"\n";
	out << "OutputFile=\"$(OutDir)/" << project_name << ".dll\"\n";
	out << "LinkIncremental=\"2\"\n";
	out << "AdditionalLibraryDirectories=\"$(QEDO)/ComponentContainer/Debug;$(QEDO)/ComponentIDL/Debug;$(ORBACUS)/lib\"\n";
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
	out << "Name=\"VCPostBuildEventTool\"\n";
	out << "CommandLine=\"wzzip.exe " << project_name << ".zip $(TargetPath) philosophers.idl philosopher.csd ";
	out << composition_name << ".ccd\n";
	out << "copy $(TargetPath) &quot;$(QEDO)\\..\\runtime&quot;\"/>\n";
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
	out << "RelativePath=\"" << mapAbsoluteName(composition->ccm_home(), "_") << "_SERVANT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT_skel.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL.cpp\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL_skel.cpp\">\n";
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
	out << "RelativePath=\"" << mapAbsoluteName(composition->ccm_home(), "_") << "_SERVANT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT_skel.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL.h\">\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL_skel.h\">\n";
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
	out << "RelativePath=\"" << target_file_name_ << "\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(QEDO)/bin/cidl_gen -DWIN32 -I$(QEDO)/ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB --servant --target " << target_->id() << " " << target_file_name_ << "\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_LOCAL.idl;" << idl_file_prefix << "_EQUIVALENT.idl;";
	out << idl_file_prefix << "_BUSINESS.idl\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_EQUIVALENT.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)\\bin\\idl -DWIN32 -I$(QEDO)\\ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << idl_file_prefix << "_EQUIVALENT.idl\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_EQUIVALENT.h;" << idl_file_prefix << "_EQUIVALENT.cpp;";
	out << idl_file_prefix << "_EQUIVALENT_skel.h;" << idl_file_prefix << "_EQUIVALENT_skel.cpp\"/>\n";
	out.unindent();
	out.unindent();
	out << "</FileConfiguration>\n";
	out.unindent();
	out << "</File>\n";
	out << "<File\n";
	out.indent();
	out << "RelativePath=\"" << idl_file_prefix << "_LOCAL.idl\">\n";
	out << "<FileConfiguration\n";
	out.indent();
	out << "Name=\"Debug|Win32\">\n";
	out << "<Tool\n";
	out.indent();
	out << "Name=\"VCCustomBuildTool\"\n";
	out << "CommandLine=\"$(ORBACUS)\\bin\\idl -DWIN32 -I$(QEDO)\\ComponentIDL -I$(ORBACUS)/idl ";
	out << "-I$(ORBACUS)/idl/OB " << idl_file_prefix << "_LOCAL.idl\"\n";
	out << "Outputs=\"" << idl_file_prefix << "_LOCAL.h;" << idl_file_prefix << "_LOCAL.cpp;";
	out << idl_file_prefix << "_LOCAL_skel.h;" << idl_file_prefix << "_LOCAL_skel.cpp\"/>\n";
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

