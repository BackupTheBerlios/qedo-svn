# Microsoft Developer Studio Project File - Name="IDL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=IDL - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "IDL.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "IDL.mak" CFG="IDL - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "IDL - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "IDL - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
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
# PROP BASE Output_Dir "IDL___Win32_Debug"
# PROP BASE Intermediate_Dir "IDL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "IDL___Win32_Debug_vc6"
# PROP Intermediate_Dir "IDL___Win32_Debug_vc6"
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
# ADD LIB32 /nologo /out:"./IDL.lib"

!ENDIF 

# Begin Target

# Name "IDL - Win32 Release"
# Name "IDL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DiningPhilosophers_BUSINESS.cpp
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_BUSINESS_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_EQUIVALENT.cpp
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_EQUIVALENT_skel.cpp
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_LOCAL.cpp
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_LOCAL_skel.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DiningPhilosophers_BUSINESS.h
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_BUSINESS_skel.h
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_EQUIVALENT.h
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_EQUIVALENT_skel.h
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_LOCAL.h
# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_LOCAL_skel.h
# End Source File
# End Group
# Begin Group "cidl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dinner.cidl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\dinner.cidl

BuildCmds= \
	$(QEDO)\bin\cidl_gen -I%QEDO%\ComponentIDL -I%ORBACUS%\idl\ob  -I%ORBACUS%\idl -DWIN32 --business --servant --target DiningPhilosophers dinner.cidl \
	time /T > last_build_time \
	

"last_build_time" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_LOCAL.idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_EQUIVALENT.idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_BUSINESS.idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "idl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DiningPhilosophers_BUSINESS.idl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\DiningPhilosophers_BUSINESS.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I../../../Container2/ComponentIDL -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -I$(QEDO)\ComponentIDL -DWIN32 DiningPhilosophers_BUSINESS.idl

"DiningPhilosophers_BUSINESS.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_BUSINESS.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_BUSINESS_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_BUSINESS_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_EQUIVALENT.idl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\DiningPhilosophers_EQUIVALENT.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I../../../Container2/ComponentIDL -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -I$(QEDO)\ComponentIDL -DWIN32 DiningPhilosophers_EQUIVALENT.idl

"DiningPhilosophers_EQUIVALENT.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_EQUIVALENT.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_EQUIVALENT_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_EQUIVALENT_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DiningPhilosophers_LOCAL.idl

!IF  "$(CFG)" == "IDL - Win32 Release"

!ELSEIF  "$(CFG)" == "IDL - Win32 Debug"

# Begin Custom Build
InputPath=.\DiningPhilosophers_LOCAL.idl

BuildCmds= \
	$(ORBACUS)\bin\idl -I../../../Container2/ComponentIDL -I$(ORBACUS)/idl -I$(ORBACUS)/idl/OB -I$(QEDO)\ComponentIDL -DWIN32 DiningPhilosophers_LOCAL.idl

"DiningPhilosophers_LOCAL.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_LOCAL.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_LOCAL_skel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DiningPhilosophers_LOCAL_skel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
