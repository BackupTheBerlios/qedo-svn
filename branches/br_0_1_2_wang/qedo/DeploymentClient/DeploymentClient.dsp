# Microsoft Developer Studio Project File - Name="DeploymentClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DeploymentClient - Win32 Debug_tao
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "DeploymentClient.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "DeploymentClient.mak" CFG="DeploymentClient - Win32 Debug_tao"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "DeploymentClient - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "DeploymentClient - Win32 Debug_orbacus" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "DeploymentClient - Win32 Release_orbacus" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "DeploymentClient - Win32 Debug_mico" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "DeploymentClient - Win32 Debug_tao" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DeploymentClient - Win32 Release"

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
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "DeploymentClient - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_orbacus"
# PROP BASE Intermediate_Dir "Debug_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_orbacus_vc6"
# PROP Intermediate_Dir "Debug_orbacus_vc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# ADD LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug_orbacus_vc6/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# Begin Special Build Tool
TargetPath=.\Debug_orbacus_vc6\deploy.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Distribution:
PostBuild_Cmds=mkdir $(QEDO)\bin	copy $(TargetPath) $(QEDO)\bin
# End Special Build Tool

!ELSEIF  "$(CFG)" == "DeploymentClient - Win32 Release_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DeploymentClient___Win32_Release_orbacus"
# PROP BASE Intermediate_Dir "DeploymentClient___Win32_Release_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DeploymentClient___Win32_Release_orbacus"
# PROP Intermediate_Dir "DeploymentClient___Win32_Release_orbacus"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# ADD LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"

!ELSEIF  "$(CFG)" == "DeploymentClient - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DeploymentClient___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "DeploymentClient___Win32_Debug_mico"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DeploymentClient___Win32_Debug_mico"
# PROP Intermediate_Dir "DeploymentClient___Win32_Debug_mico"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# ADD LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"

!ELSEIF  "$(CFG)" == "DeploymentClient - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DeploymentClient___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "DeploymentClient___Win32_Debug_tao"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_tao"
# PROP Intermediate_Dir "Debug_tao"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(TAO)\TAO" /I "$(TAO)" /I "$(TAO)\tao\tao" /I "$(TAO)\tao\tao\PortableServer" /I "$(TAO)\tao\tao\IFR_Client" /I "$(TAO)\TAO\orbsvcs\orbsvcs" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "TAO_ORB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 CosNamingd.lib obd.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/deploy.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib"
# ADD LINK32 aced.lib TAOd.lib TAO_PortableServerd.lib TAO_DynamicAnyd.lib TAO_CosNamingd.lib TAO_IFR_Clientd.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug_tao/deploy.exe" /pdbtype:sept /libpath:"$(ACE_ROOT)\ace" /libpath:"$(TAO)\TAO\tao" /libpath:"$(TAO)\TAO\tao\PortableServer" /libpath:"$(TAO)\TAO\tao\DynamicAny" /libpath:"$(TAO)\TAO\orbsvcs\orbsvcs" /libpath:"$(TAO)\TAO\tao\IFR_Client"
# Begin Special Build Tool
TargetPath=.\Debug_tao\deploy.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Distribution:
PostBuild_Cmds=mkdir $(QEDO)\bin	copy $(TargetPath) $(QEDO)\bin
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "DeploymentClient - Win32 Release"
# Name "DeploymentClient - Win32 Debug_orbacus"
# Name "DeploymentClient - Win32 Release_orbacus"
# Name "DeploymentClient - Win32 Debug_mico"
# Name "DeploymentClient - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DeploymentClient.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\NameServiceBase.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DeploymentClient.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\NameServiceBase.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
