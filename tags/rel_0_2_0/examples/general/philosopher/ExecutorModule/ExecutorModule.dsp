# Microsoft Developer Studio Project File - Name="ExecutorModule" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ExecutorModule - Win32 Debug_tao
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ExecutorModule.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ExecutorModule.mak" CFG="ExecutorModule - Win32 Debug_tao"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ExecutorModule - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ExecutorModule - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ExecutorModule - Win32 Debug_orbacus" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ExecutorModule - Win32 Debug_tao" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ExecutorModule - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "ExecutorModule - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ExecutorModule___Win32_Debug"
# PROP BASE Intermediate_Dir "ExecutorModule___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ExecutorModule___Win32_Debug_vc6"
# PROP Intermediate_Dir "ExecutorModule___Win32_Debug_vc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(QEDO)/ComponentIDL" /I "$(QEDO)/ComponentContainer" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /I "../IDL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /D "VC6" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ComponentIDL.lib obd.lib jtcd.lib /nologo /dll /debug /machine:I386 /out:"../../../../Runtime/philosopherE.dll" /pdbtype:sept /libpath:"$(QEDO)/ComponentIDL/Debug_orbacus_vc6" /libpath:"$(ORBACUS)\lib"

!ELSEIF  "$(CFG)" == "ExecutorModule - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ExecutorModule___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "ExecutorModule___Win32_Debug_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ExecutorModule___Win32_Debug_orbacus"
# PROP Intermediate_Dir "ExecutorModule___Win32_Debug_orbacus"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(QEDO)/ComponentIDL" /I "$(QEDO)/ComponentContainer" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /I "../IDL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /D "VC6" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(QEDO)/ComponentIDL" /I "$(QEDO)/ComponentContainer" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /I "../IDL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /D "VC6" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ComponentIDL.lib obd.lib jtcd.lib /nologo /dll /debug /machine:I386 /out:"../../../../Runtime/philosopherE.dll" /pdbtype:sept /libpath:"$(QEDO)/ComponentIDL/Debug_orbacus_vc6" /libpath:"$(ORBACUS)\lib"
# ADD LINK32 ComponentIDL.lib obd.lib jtcd.lib /nologo /dll /debug /machine:I386 /out:"../../../../Runtime/philosopherE.dll" /pdbtype:sept /libpath:"$(QEDO)/ComponentIDL/Debug_orbacus_vc6" /libpath:"$(ORBACUS)\lib"

!ELSEIF  "$(CFG)" == "ExecutorModule - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ExecutorModule___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "ExecutorModule___Win32_Debug_tao"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ExecutorModule___Win32_Debug_tao"
# PROP Intermediate_Dir "ExecutorModule___Win32_Debug_tao"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(QEDO)/ComponentIDL" /I "$(QEDO)/ComponentContainer" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /I "../IDL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /D "VC6" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(QEDO)/ComponentIDL" /I "$(QEDO)/ComponentContainer" /I "$(TAO)\TAO" /I "$(TAO)" /I "$(TAO)\tao\tao" /I "$(TAO)\tao\tao\PortableServer" /I "$(TAO)\tao\tao\IFR_Client" /I "$(TAO)\TAO\orbsvcs\orbsvcs" /I "../IDL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "EXECUTORMODULE_EXPORTS" /D "VC6" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ComponentIDL.lib obd.lib jtcd.lib /nologo /dll /debug /machine:I386 /out:"../../../../Runtime/philosopherE.dll" /pdbtype:sept /libpath:"$(QEDO)/ComponentIDL/Debug_orbacus_vc6" /libpath:"$(ORBACUS)\lib"
# ADD LINK32 ComponentIDL.lib obd.lib jtcd.lib /nologo /dll /debug /machine:I386 /out:"../../../../Runtime/philosopherE.dll" /pdbtype:sept /libpath:"$(QEDO)/ComponentIDL/Debug_orbacus_vc6" /libpath:"$(ORBACUS)\lib"

!ENDIF 

# Begin Target

# Name "ExecutorModule - Win32 Release"
# Name "ExecutorModule - Win32 Debug"
# Name "ExecutorModule - Win32 Debug_orbacus"
# Name "ExecutorModule - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\IDL\dinner_CutleryImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\IDL\dinner_ObserverImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\IDL\dinner_PhilosopherImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExecutorValuetypes.cpp
# End Source File
# Begin Source File

SOURCE=.\RefCountLocalObject.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\IDL\dinner_CutleryImpl.h
# End Source File
# Begin Source File

SOURCE=..\IDL\dinner_ObserverImpl.h
# End Source File
# Begin Source File

SOURCE=..\IDL\dinner_PhilosopherImpl.h
# End Source File
# Begin Source File

SOURCE=.\ExecutorValuetypes.h
# End Source File
# Begin Source File

SOURCE=.\RefCountLocalObject.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
