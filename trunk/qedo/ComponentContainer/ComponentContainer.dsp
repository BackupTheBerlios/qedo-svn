# Microsoft Developer Studio Project File - Name="ComponentContainer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ComponentContainer - Win32 Debug_tao
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComponentContainer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComponentContainer.mak" CFG="ComponentContainer - Win32 Debug_tao"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComponentContainer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentContainer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentContainer - Win32 Debug_orbacus" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComponentContainer - Win32 Debug_tao" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComponentContainer - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "ComponentContainer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentContainer___Win32_Debug"
# PROP BASE Intermediate_Dir "ComponentContainer___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentContainer___Win32_Debug_vc6"
# PROP Intermediate_Dir "ComponentContainer___Win32_Debug_vc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentValuetypes" /I "$(ORBACUS)\include" /D "CONTAINERDLL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /D "VC6" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentContainer.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"

!ELSEIF  "$(CFG)" == "ComponentContainer - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentContainer___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "ComponentContainer___Win32_Debug_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentContainer___Win32_Debug_orbacus_vc6"
# PROP Intermediate_Dir "ComponentContainer___Win32_Debug_orbacus_vc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentValuetypes" /I "$(ORBACUS)\include" /D "CONTAINERDLL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /D "VC6" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentValuetypes" /I "$(ORBACUS)\include" /D "CONTAINERDLL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /D "VC6" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentContainer.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# ADD LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentContainer.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"

!ELSEIF  "$(CFG)" == "ComponentContainer - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentContainer___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "ComponentContainer___Win32_Debug_tao"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentContainer___Win32_Debug_tao"
# PROP Intermediate_Dir "ComponentContainer___Win32_Debug_tao"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentValuetypes" /I "$(ORBACUS)\include" /D "CONTAINERDLL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /D "VC6" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentValuetypes" /I "$(ORBACUS)\include" /D "CONTAINERDLL_EXPORTS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "COMPONENTCONTAINER_EXPORTS" /D "VC6" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentContainer.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# ADD LINK32 jtcd.lib obd.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../Runtime/ComponentContainer.dll" /pdbtype:sept /libpath:"$(ORBACUS)\lib"

!ENDIF 

# Begin Target

# Name "ComponentContainer - Win32 Release"
# Name "ComponentContainer - Win32 Debug"
# Name "ComponentContainer - Win32 Debug_orbacus"
# Name "ComponentContainer - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCMContext.cpp
# End Source File
# Begin Source File

SOURCE=.\CCMHomeServant.cpp
# End Source File
# Begin Source File

SOURCE=.\CCMObjectExecutor.cpp
# End Source File
# Begin Source File

SOURCE=.\ComponentInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsumerPort.cpp
# End Source File
# Begin Source File

SOURCE=.\ContainerInterfaceImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\EmitterPort.cpp
# End Source File
# Begin Source File

SOURCE=.\EntityHomeServant.cpp
# End Source File
# Begin Source File

SOURCE=.\FacetPort.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalHelpers.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeServantBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Key.cpp
# End Source File
# Begin Source File

SOURCE=.\Output.cpp
# End Source File
# Begin Source File

SOURCE=.\PortBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PublisherPort.cpp
# End Source File
# Begin Source File

SOURCE=.\ReceptaclePort.cpp
# End Source File
# Begin Source File

SOURCE=.\RefCountBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ServantBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ServantLocator.cpp
# End Source File
# Begin Source File

SOURCE=.\ServantRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\SessionContext.cpp
# End Source File
# Begin Source File

SOURCE=.\SessionHomeServant.cpp
# End Source File
# Begin Source File

SOURCE=.\Valuetypes.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCMContext.h
# End Source File
# Begin Source File

SOURCE=.\CCMHomeServant.h
# End Source File
# Begin Source File

SOURCE=.\CCMObjectExecutor.h
# End Source File
# Begin Source File

SOURCE=.\ComponentInstance.h
# End Source File
# Begin Source File

SOURCE=.\ConsumerPort.h
# End Source File
# Begin Source File

SOURCE=.\ContainerInterfaceImpl.h
# End Source File
# Begin Source File

SOURCE=.\EmitterPort.h
# End Source File
# Begin Source File

SOURCE=.\EntityHomeServant.h
# End Source File
# Begin Source File

SOURCE=.\FacetPort.h
# End Source File
# Begin Source File

SOURCE=.\GlobalHelpers.h
# End Source File
# Begin Source File

SOURCE=.\HomeServantBase.h
# End Source File
# Begin Source File

SOURCE=.\Key.h
# End Source File
# Begin Source File

SOURCE=.\Output.h
# End Source File
# Begin Source File

SOURCE=.\PortBase.h
# End Source File
# Begin Source File

SOURCE=.\PortEntry.h
# End Source File
# Begin Source File

SOURCE=.\PublisherPort.h
# End Source File
# Begin Source File

SOURCE=.\ReceptaclePort.h
# End Source File
# Begin Source File

SOURCE=.\RefCountBase.h
# End Source File
# Begin Source File

SOURCE=.\ServantBase.h
# End Source File
# Begin Source File

SOURCE=.\ServantLocator.h
# End Source File
# Begin Source File

SOURCE=.\ServantRegistry.h
# End Source File
# Begin Source File

SOURCE=.\SessionContext.h
# End Source File
# Begin Source File

SOURCE=.\SessionHomeServant.h
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# Begin Source File

SOURCE=.\Valuetypes.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
