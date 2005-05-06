# Microsoft Developer Studio Project File - Name="IDL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=IDL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IDL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IDL.mak" CFG="IDL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IDL - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "IDL - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IDL - Win32 Release"

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
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(QEDO)\ComponentIDL" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\OB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "IDL - Win32 Release"
# Name "IDL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\simple_BUSINESS.cpp
# End Source File
# Begin Source File

SOURCE=.\simple_BUSINESS_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\simple_EQUIVALENT.cpp
# End Source File
# Begin Source File

SOURCE=.\simple_EQUIVALENT_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\simple_LOCAL.cpp
# End Source File
# Begin Source File

SOURCE=.\simple_LOCAL_skel.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\simple_BUSINESS.h
# End Source File
# Begin Source File

SOURCE=.\simple_BUSINESS_skel.h
# End Source File
# Begin Source File

SOURCE=.\simple_EQUIVALENT.h
# End Source File
# Begin Source File

SOURCE=.\simple_EQUIVALENT_skel.h
# End Source File
# Begin Source File

SOURCE=.\simple_LOCAL.h
# End Source File
# Begin Source File

SOURCE=.\simple_LOCAL_skel.h
# End Source File
# End Group
# Begin Group "cidl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\simple.cidl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\simple.cidl

BuildCmds= \
	$(QEDO)\bin\cidl_gen -I%QEDO%\ComponentIDL -I%ORBACUS%\idl\ob  -I%ORBACUS%\idl -DWIN32 -DORBACUS_ORB  --business --servant --target simple simple.cidl \
	time /T > last_build_time \
	

"last_build_time" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_LOCAL.idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_EQUIVALENT.idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_BUSINESS.idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\simple.idl
# End Source File
# End Group
# Begin Group "idl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\simple_BUSINESS.idl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\simple_BUSINESS.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I../../../Container2/ComponentIDL -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -I$(QEDO)\ComponentIDL -DWIN32 -DORBACUS_ORB simple_BUSINESS.idl

"simple_BUSINESS.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_BUSINESS.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_BUSINESS_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_BUSINESS_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\simple_EQUIVALENT.idl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\simple_EQUIVALENT.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I../../../Container2/ComponentIDL -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -I$(QEDO)\ComponentIDL -DWIN32 -DORBACUS_ORB simple_EQUIVALENT.idl

"simple_EQUIVALENT.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_EQUIVALENT.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_EQUIVALENT_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_EQUIVALENT_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\simple_LOCAL.idl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\simple_LOCAL.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I../../../Container2/ComponentIDL -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -I$(QEDO)\ComponentIDL -DWIN32 -DORBACUS_ORB  simple_LOCAL.idl

"simple_LOCAL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_LOCAL.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_LOCAL_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"simple_LOCAL_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
