# Microsoft Developer Studio Project File - Name="ComponentIDL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ComponentIDL - Win32 Debug_mico
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComponentIDL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComponentIDL.mak" CFG="ComponentIDL - Win32 Debug_mico"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComponentIDL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentIDL - Win32 Debug_orbacus" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentIDL - Win32 Debug_tao" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentIDL - Win32 Release_orbacus" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentIDL - Win32 Debug_mico" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComponentIDL - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentIDL___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "ComponentIDL___Win32_Debug_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_orbacus_vc6"
# PROP Intermediate_Dir "Debug_orbacus_vc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentIDL.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:"Debug_orbacus_vc6/ComponentIDL.def" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Debug_orbacus_vc6\ComponentIDL.dll
SOURCE="$(InputPath)"
PreLink_Desc=Creating DEF file for ComponentIDL.dll
PreLink_Cmds=perl  makedef.pl Debug_orbacus_vc6/ComponentIDL.def Debug_orbacus_vc6/ComponentIDL.dll Debug_orbacus_vc6/*.obj
PostBuild_Desc=Distribution:
PostBuild_Cmds=mkdir $(QEDO)\bin	copy $(TargetPath) $(QEDO)\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentIDL___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "ComponentIDL___Win32_Debug_tao"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_tao"
# PROP Intermediate_Dir "Debug_tao"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "$(TAO)\TAO" /I "$(TAO)" /I "$(TAO)\tao\tao\PortableServer" /I "$(TAO)\tao\tao\IFR_Client" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentIDL.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 aced.lib taod.lib TAO_IFR_Clientd.lib TAO_PortableServerd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:"Debug_tao/ComponentIDL.def" /pdbtype:sept /libpath:"$(TAO)\ace" /libpath:"$(TAO)\tao\tao" /libpath:"$(TAO)/tao/tao/IFR_Client" /libpath:"$(TAO)/tao/tao/PortableServer"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Debug_tao\ComponentIDL.dll
SOURCE="$(InputPath)"
PreLink_Desc=Creating DEF file for ComponentIDL.dll
PreLink_Cmds=perl  makedef.pl Debug_tao/ComponentIDL.def Debug_tao/ComponentIDL.dll Debug_tao/*.obj
PostBuild_Desc=Distribution:
PostBuild_Cmds=mkdir $(QEDO)\bin	copy $(TargetPath) $(QEDO)\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Release_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentIDL___Win32_Release_orbacus"
# PROP BASE Intermediate_Dir "ComponentIDL___Win32_Release_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release_orbacus"
# PROP Intermediate_Dir "Release_orbacus"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /I "$(ORBACUS)\include" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentIDL.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 jtc.lib ob.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentIDL.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT LINK32 /profile /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Creating DEF file for ComponentIDL.dll
PreLink_Cmds=perl  makedef.pl ComponentIDL.def Release/ComponentIDL.dll Release_orbacus/*.obj
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentIDL___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "ComponentIDL___Win32_Debug_mico"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentIDL___Win32_Debug_mico"
# PROP Intermediate_Dir "ComponentIDL___Win32_Debug_mico"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(MICO)\include\win32" /I "$(MICO)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTIDL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentIDL.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentIDL.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# SUBTRACT LINK32 /profile /map
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Creating DEF file for ComponentIDL.dll
PreLink_Cmds=perl  makedef.pl ComponentIDL.def Debug/ComponentIDL.dll Debug_orbacus_vc6/*.obj
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ComponentIDL - Win32 Release"
# Name "ComponentIDL - Win32 Debug_orbacus"
# Name "ComponentIDL - Win32 Debug_tao"
# Name "ComponentIDL - Win32 Release_orbacus"
# Name "ComponentIDL - Win32 Debug_mico"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ComponentIDL.def

!IF  "$(CFG)" == "ComponentIDL - Win32 Release"

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_orbacus"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_tao"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Release_orbacus"

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_mico"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Components.cpp
# End Source File
# Begin Source File

SOURCE=.\Components_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\CORBADepends.cpp
# End Source File
# Begin Source File

SOURCE=.\CORBADepends_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\QedoComponents.cpp
# End Source File
# Begin Source File

SOURCE=.\QedoComponents_skel.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Components.h
# End Source File
# Begin Source File

SOURCE=.\Components_skel.h
# End Source File
# Begin Source File

SOURCE=.\CORBADepends.h
# End Source File
# Begin Source File

SOURCE=.\CORBADepends_skel.h
# End Source File
# Begin Source File

SOURCE=.\QedoComponents.h
# End Source File
# Begin Source File

SOURCE=.\QedoComponents_skel.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "idl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Components.idl

!IF  "$(CFG)" == "ComponentIDL - Win32 Release"

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Components.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I. -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -DWIN32 -DORBACUS_ORB Components.idl

"Components.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_tao"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Components.idl

BuildCmds= \
	$(TAO)\bin\tao_idl -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp  -DTAO_ORB  -I$(TAO)/tao -I$(TAO)/tao/tao  -I$(TAO)/tao/tao/PortableServer -I$(TAO)/tao/tao/IFR_Client -DWIN32 Components.idl

"Components.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Release_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Components.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I. -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -DWIN32 -DORBACUS_ORB Components.idl

"Components.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_mico"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Components.idl

BuildCmds= \
	$(MICO)\win32-bin\idl -DMICO_ORB --any --c++-suffix cpp --c++-skel -I$(MICO)\include\mico  -I$(MICO)\include  -DWIN32 Components.idl

"Components.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Components_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CORBADepends.idl

!IF  "$(CFG)" == "ComponentIDL - Win32 Release"

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CORBADepends.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I. -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -DWIN32 -DORBACUS_ORB CORBADepends.idl

"CORBADepends.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_tao"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CORBADepends.idl

BuildCmds= \
	$(TAO)\bin\tao_idl -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp  -DTAO_ORB  -I$(TAO)/tao -I$(TAO)/tao/tao -I$(TAO)/tao/tao/PortableServer -I$(TAO)/tao/tao/IFR_Client -DWIN32 CORBADepends.idl

"CORBADepends.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Release_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CORBADepends.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I. -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -DWIN32 -DORBACUS_ORB CORBADepends.idl

"CORBADepends.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_mico"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CORBADepends.idl

BuildCmds= \
	$(MICO)\win32-bin\idl -DMICO_ORB --any --c++-suffix cpp --c++-skel -I$(MICO)\include\mico  -I$(MICO)\include  -DWIN32 CORBADepends.idl

"CORBADepends.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CORBADepends_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QedoComponents.idl

!IF  "$(CFG)" == "ComponentIDL - Win32 Release"

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\QedoComponents.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I. -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -DWIN32 -DORBACUS_ORB QedoComponents.idl

"QedoComponents.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_tao"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\QedoComponents.idl

BuildCmds= \
	$(TAO)\bin\tao_idl -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp  -DTAO_ORB  -I$(TAO)/tao -I$(TAO)/tao/tao  -I$(TAO)\tao\tao\PortableServer -I$(TAO)/tao/tao/PortableServer -I$(TAO)/tao/tao/IFR_Client -DWIN32 QedoComponents.idl

"QedoComponents.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Release_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\QedoComponents.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I. -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -DWIN32 -DORBACUS_ORB QedoComponents.idl

"QedoComponents.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ComponentIDL - Win32 Debug_mico"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\QedoComponents.idl

BuildCmds= \
	$(MICO)\win32-bin\idl -DMICO_ORB --any --c++-suffix cpp --c++-skel -I$(MICO)\include\mico  -I$(MICO)\include  -DWIN32 QedoComponents.idl

"QedoComponents.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"QedoComponents_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
