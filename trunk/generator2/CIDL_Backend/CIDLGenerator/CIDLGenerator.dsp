# Microsoft Developer Studio Project File - Name="CIDLGenerator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=CIDLGenerator - Win32 Debug_tao
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CIDLGenerator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CIDLGenerator.mak" CFG="CIDLGenerator - Win32 Debug_tao"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CIDLGenerator - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "CIDLGenerator - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "CIDLGenerator - Win32 Debug_mico" (based on "Win32 (x86) Console Application")
!MESSAGE "CIDLGenerator - Win32 Debug_orbacus" (based on "Win32 (x86) Console Application")
!MESSAGE "CIDLGenerator - Win32 Debug_tao" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "CIDLGenerator"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CIDLGenerator - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "CIDLGenerator - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /FD /GZ /Zm500 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib OBD.lib JTCD.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"$(enagoCCM)\bin\cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib"

!ELSEIF  "$(CFG)" == "CIDLGenerator - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLGenerator___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "CIDLGenerator___Win32_Debug_mico"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CIDLGenerator___Win32_Debug_mico"
# PROP Intermediate_Dir "CIDLGenerator___Win32_Debug_mico"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /FD /GZ /Zm500 /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /D "_WINDOWS" /FD /GZ /Zm600 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib OBD.lib JTCD.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"$(enagoCCM)\bin\cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib"
# ADD LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib mico236.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib" /libpath:"$(MICO)\win32-bin\lib"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=distribution
PostBuild_Cmds=md ..\..\..\qedo_dist_mico_d	md ..\..\..\qedo_dist_mico_d\bin	copy cidl_gen.exe ..\..\..\qedo_dist_mico_d\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CIDLGenerator - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLGenerator___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "CIDLGenerator___Win32_Debug_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CIDLGenerator___Win32_Debug_orbacus_vc6"
# PROP Intermediate_Dir "CIDLGenerator___Win32_Debug_orbacus_vc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /D "_WINDOWS" /FD /GZ /Zm500 /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\ob" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /D "_WINDOWS" /FD /GZ /Zm900 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib mico236.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"$(enagoCCM)\bin\cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib" /libpath:"$(MICO)\win32-bin\lib"
# ADD LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib obd.lib jtcd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib" /libpath:"$(ORBACUS)\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=distribution
PostBuild_Cmds=md     ..\..\..\qedo_dist_orbacus_d    	md     ..\..\..\qedo_dist_orbacus_d\bin    	copy     cidl_gen.exe     ..\..\..\qedo_dist_orbacus_d\bin    	mkdir     $(QEDO)\bin    	copy     cidl_gen.exe     $(QEDO)\bin\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CIDLGenerator - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLGenerator___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "CIDLGenerator___Win32_Debug_tao"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CIDLGenerator___Win32_Debug_tao"
# PROP Intermediate_Dir "CIDLGenerator___Win32_Debug_tao"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /D "_WINDOWS" /FD /GZ /Zm500 /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "..\..\CIDL_Frontend\CIDLFrontendLib" /I "$(TAO)\TAO" /I "$(TAO)\TAO\tao" /I "$(TAO)" /I "$(TAO)\TAO\tao\DynamicAny" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "__DEBUG__" /D "_WINDOWS" /FD /GZ /Zm900 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib mico236.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"$(enagoCCM)\bin\cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib" /libpath:"$(MICO)\win32-bin\lib"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 CIDLFrontendLib.lib CIDLRepositoryLib.lib ComponentRepositoryLib.lib IFRidl.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib aced.lib TAOd.lib TAO_PortableServerd.lib TAO_DynamicAnyd.lib /nologo /subsystem:console /debug /machine:I386 /out:"cidl_gen.exe" /pdbtype:sept /libpath:"..\..\CIDL_Frontend\CIDLFrontendLib" /libpath:"..\..\CIDL_Repository\IFRidl" /libpath:"..\..\CIDL_Repository\ComponentRepositoryLib" /libpath:"..\..\CIDL_Repository\CIDLRepositoryLib" /libpath:"$(ACE_ROOT)\ace" /libpath:"$(TAO)\TAO\tao" /libpath:"$(TAO)\TAO\tao\PortableServer" /libpath:"$(TAO)\TAO\tao\DynamicAny"
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=distribution
PostBuild_Cmds=md ..\..\..\qedo_dist_tao_d	md ..\..\..\qedo_dist_tao_d\bin	copy cidl_gen.exe ..\..\..\qedo_dist_tao_d\bin
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CIDLGenerator - Win32 Release"
# Name "CIDLGenerator - Win32 Debug"
# Name "CIDLGenerator - Win32 Debug_mico"
# Name "CIDLGenerator - Win32 Debug_orbacus"
# Name "CIDLGenerator - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CPPBase.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorBase.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorBIDL.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorBusinessC.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorBusinessH.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorCCD.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorEIDL.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorLIDL.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorServantC.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorServantH.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratorVC7.cpp
# End Source File
# Begin Source File

SOURCE=.\IDLBase.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Printer.cpp
# End Source File
# Begin Source File

SOURCE=.\TestMode.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CPPBase.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorBase.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorBIDL.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorBusinessC.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorBusinessH.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorCCD.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorEIDL.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorLIDL.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorServantC.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorServantH.h
# End Source File
# Begin Source File

SOURCE=.\GeneratorVC7.h
# End Source File
# Begin Source File

SOURCE=.\IDLBase.h
# End Source File
# Begin Source File

SOURCE=.\Printer.h
# End Source File
# Begin Source File

SOURCE=.\TestMode.h
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
