# Microsoft Developer Studio Project File - Name="CIDLRepositoryLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CIDLRepositoryLib - Win32 Debug_tao
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "CIDLRepositoryLib.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "CIDLRepositoryLib.mak" CFG="CIDLRepositoryLib - Win32 Debug_tao"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "CIDLRepositoryLib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "CIDLRepositoryLib - Win32 Debug_mico" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "CIDLRepositoryLib - Win32 Debug_orbacus" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "CIDLRepositoryLib - Win32 Debug_tao" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "CIDLRepositoryLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CIDLRepositoryLib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CIDLRepositoryLib - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLRepositoryLib___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "CIDLRepositoryLib___Win32_Debug_mico"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CIDLRepositoryLib___Win32_Debug_mico"
# PROP Intermediate_Dir "CIDLRepositoryLib___Win32_Debug_mico"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\IFRidl" /I "..\ComponentRepositoryLib" /I "$(ORBACUS)\include" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\IFRidl" /I "..\ComponentRepositoryLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"CIDLRepositoryLib.lib"
# ADD LIB32 /nologo /out:"CIDLRepositoryLib.lib"

!ELSEIF  "$(CFG)" == "CIDLRepositoryLib - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLRepositoryLib___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "CIDLRepositoryLib___Win32_Debug_orbacus"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_orbacus_vc6"
# PROP Intermediate_Dir "Debug_orbacus_vc6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\IFRidl" /I "..\ComponentRepositoryLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\IFRidl" /I "..\ComponentRepositoryLib" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\ob" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"CIDLRepositoryLib.lib"
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CIDLRepositoryLib - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLRepositoryLib___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "CIDLRepositoryLib___Win32_Debug_tao"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_tao"
# PROP Intermediate_Dir "Debug_tao"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\IFRidl" /I "..\ComponentRepositoryLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\IFRidl" /I "..\ComponentRepositoryLib" /I "$(TAO)\TAO" /I "$(TAO)\TAO\tao" /I "$(TAO)" /I "$(TAO)\TAO\tao\DynamicAny" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"CIDLRepositoryLib.lib"
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "CIDLRepositoryLib - Win32 Release"
# Name "CIDLRepositoryLib - Win32 Debug_mico"
# Name "CIDLRepositoryLib - Win32 Debug_orbacus"
# Name "CIDLRepositoryLib - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CIDLRepository_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\CompositionDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExecutorDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeExecutorDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\SegmentDef_impl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CIDLRepository_impl.h
# End Source File
# Begin Source File

SOURCE=.\CompositionDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ExecutorDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\HomeExecutorDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\SegmentDef_impl.h
# End Source File
# End Group
# End Target
# End Project
