# Microsoft Developer Studio Project File - Name="IFRidl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=IFRidl - Win32 Debug_tao
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IFRidl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IFRidl.mak" CFG="IFRidl - Win32 Debug_tao"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IFRidl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "IFRidl - Win32 Debug_mico" (based on "Win32 (x86) Static Library")
!MESSAGE "IFRidl - Win32 Debug_orbacus" (based on "Win32 (x86) Static Library")
!MESSAGE "IFRidl - Win32 Debug_tao" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "IFRidl"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IFRidl - Win32 Release"

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

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "IFRidl___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "IFRidl___Win32_Debug_mico"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "IFRidl___Win32_Debug_mico"
# PROP Intermediate_Dir "IFRidl___Win32_Debug_mico"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"IFRidl.lib"
# ADD LIB32 /nologo /out:"IFRidl.lib"

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "IFRidl___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "IFRidl___Win32_Debug_orbacus"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "IFRidl___Win32_Debug_orbacus_vc6"
# PROP Intermediate_Dir "IFRidl___Win32_Debug_orbacus_vc6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\ob" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"IFRidl.lib"
# ADD LIB32 /nologo /out:"IFRidl.lib"

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "IFRidl___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "IFRidl___Win32_Debug_tao"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "IFRidl___Win32_Debug_tao"
# PROP Intermediate_Dir "IFRidl___Win32_Debug_tao"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\windows" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "$(TAO)\TAO" /I "$(TAO)" /D "_LIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"IFRidl.lib"
# ADD LIB32 /nologo /out:"IFRidl.lib"

!ENDIF 

# Begin Target

# Name "IFRidl - Win32 Release"
# Name "IFRidl - Win32 Debug_mico"
# Name "IFRidl - Win32 Debug_orbacus"
# Name "IFRidl - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CIDL_Extension.cpp
# End Source File
# Begin Source File

SOURCE=.\CIDL_Extension_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\IFR.cpp
# End Source File
# Begin Source File

SOURCE=.\IFR_skel.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CIDL_Extension.h
# End Source File
# Begin Source File

SOURCE=.\CIDL_Extension_skel.h
# End Source File
# Begin Source File

SOURCE=.\IFR.h
# End Source File
# Begin Source File

SOURCE=.\IFR_skel.h
# End Source File
# End Group
# Begin Group "idl"

# PROP Default_Filter "idl"
# Begin Source File

SOURCE=.\CIDL_Extension.idl

!IF  "$(CFG)" == "IFRidl - Win32 Release"

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_mico"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CIDL_Extension.idl

BuildCmds= \
	$(MICO)\win32-bin\idl --any -I. --c++-suffix cpp --c++-skel  -I$(MICO)\include\mico  -I$(MICO)\include  CIDL_Extension.idl \
	copy CIDL_Extension.h CIDL_Extension_skel.h \
	

"CIDL_Extension.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CIDL_Extension.idl

BuildCmds= \
	$(ORBACUS)\bin\idl  --c-suffix .cpp   -I$(ORBACUS)\idl  -I$(ORBACUS)\idl\OB CIDL_Extension.idl

"CIDL_Extension.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_tao"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\CIDL_Extension.idl

BuildCmds= \
	$(TAO)\bin\tao_idl  -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp -DTAO_ORB    -I$(TAO)/tao -I$(TAO)/tao/tao   CIDL_Extension.idl

"CIDL_Extension.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"CIDL_Extension_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IFR.idl

!IF  "$(CFG)" == "IFRidl - Win32 Release"

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_mico"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\IFR.idl

BuildCmds= \
	$(MICO)\win32-bin\idl --any --c++-suffix cpp --c++-skel -I$(MICO)\include\mico  -I$(MICO)\include IFR.idl \
	copy IFR.h IFR_skel.h \
	

"IFR.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_orbacus"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\IFR.idl

BuildCmds= \
	$(ORBACUS)\bin\idl  --c-suffix  .cpp   -I$(ORBACUS)\idl  -I$(ORBACUS)\idl\OB IFR.idl

"IFR.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "IFRidl - Win32 Debug_tao"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\IFR.idl

BuildCmds= \
	$(TAO)\bin\tao_idl -Sc -ss _skel.cpp -hs _skel.h -hc .h -cs .cpp  -DTAO_ORB  -I$(TAO)/tao -I$(TAO)/tao/tao  IFR.idl

"IFR.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"IFR_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
