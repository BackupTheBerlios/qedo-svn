# Microsoft Developer Studio Project File - Name="ComponentRepositoryLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ComponentRepositoryLib - Win32 Debug_tao
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComponentRepositoryLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComponentRepositoryLib.mak" CFG="ComponentRepositoryLib - Win32 Debug_tao"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComponentRepositoryLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ComponentRepositoryLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ComponentRepositoryLib - Win32 Debug_mico" (based on "Win32 (x86) Static Library")
!MESSAGE "ComponentRepositoryLib - Win32 Debug_orbacus" (based on "Win32 (x86) Static Library")
!MESSAGE "ComponentRepositoryLib - Win32 Debug_tao" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "ComponentRepositoryLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComponentRepositoryLib - Win32 Release"

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

!ELSEIF  "$(CFG)" == "ComponentRepositoryLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(ORBACUS)\include" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ComponentRepositoryLib.lib"

!ELSEIF  "$(CFG)" == "ComponentRepositoryLib - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentRepositoryLib___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "ComponentRepositoryLib___Win32_Debug_mico"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentRepositoryLib___Win32_Debug_mico"
# PROP Intermediate_Dir "ComponentRepositoryLib___Win32_Debug_mico"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(ORBACUS)\include" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"ComponentRepositoryLib.lib"
# ADD LIB32 /nologo /out:"ComponentRepositoryLib.lib"

!ELSEIF  "$(CFG)" == "ComponentRepositoryLib - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentRepositoryLib___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "ComponentRepositoryLib___Win32_Debug_orbacus"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentRepositoryLib___Win32_Debug_orbacus_vc6"
# PROP Intermediate_Dir "ComponentRepositoryLib___Win32_Debug_orbacus_vc6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\ob" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"ComponentRepositoryLib.lib"
# ADD LIB32 /nologo /out:"ComponentRepositoryLib.lib"

!ELSEIF  "$(CFG)" == "ComponentRepositoryLib - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComponentRepositoryLib___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "ComponentRepositoryLib___Win32_Debug_tao"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ComponentRepositoryLib___Win32_Debug_tao"
# PROP Intermediate_Dir "ComponentRepositoryLib___Win32_Debug_tao"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "..\IFRidl" /I "$(TAO)\TAO" /I "$(TAO)\TAO\tao" /I "$(TAO)" /I "$(TAO)\TAO\tao\DynamicAny" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"ComponentRepositoryLib.lib"
# ADD LIB32 /nologo /out:"ComponentRepositoryLib.lib"

!ENDIF 

# Begin Target

# Name "ComponentRepositoryLib - Win32 Release"
# Name "ComponentRepositoryLib - Win32 Debug"
# Name "ComponentRepositoryLib - Win32 Debug_mico"
# Name "ComponentRepositoryLib - Win32 Debug_orbacus"
# Name "ComponentRepositoryLib - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AliasDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\Anonymous.cpp
# End Source File
# Begin Source File

SOURCE=.\AttributeDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComponentDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComponentRepository_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ConstantDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsumesDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\Contained_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\Container_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\EmitsDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\EventDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\EventPortDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExceptionDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\FactoryDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\FinderDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\HomeDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\IDLType_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\InterfaceDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\IRObject_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ModuleDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\OperationDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimaryKeyDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ProvidesDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\PublishesDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\Repository_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\Sink.cpp
# End Source File
# Begin Source File

SOURCE=.\SiSoDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\SourceDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\StreamPortDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\StreamTypeDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\StructDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\TypedefDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\UnionDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\UsesDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueDef_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueMemberDef_impl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AliasDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\Anonymous.h
# End Source File
# Begin Source File

SOURCE=.\AttributeDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ComponentDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ComponentRepository_impl.h
# End Source File
# Begin Source File

SOURCE=.\ConstantDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ConsumesDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\Contained_impl.h
# End Source File
# Begin Source File

SOURCE=.\Container_impl.h
# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\EmitsDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\EnumDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\EventDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\EventPortDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ExceptionDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\FactoryDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\FinderDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\HomeDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\IDLType_impl.h
# End Source File
# Begin Source File

SOURCE=.\InterfaceDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\IRObject_impl.h
# End Source File
# Begin Source File

SOURCE=.\ModuleDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\NativeDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\OperationDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\PrimaryKeyDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ProvidesDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\PublishesDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\Repository_impl.h
# End Source File
# Begin Source File

SOURCE=.\Sink_impl.h
# End Source File
# Begin Source File

SOURCE=.\SiSoDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\SourceDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\StreamPortDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\StreamTypeDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\StructDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\TypedefDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\UnionDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\UsesDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ValueDef_impl.h
# End Source File
# Begin Source File

SOURCE=.\ValueMemberDef_impl.h
# End Source File
# End Group
# End Target
# End Project
