# Microsoft Developer Studio Project File - Name="CIDLFrontendLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CIDLFrontendLib - Win32 Debug_tao
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "CIDLFrontendLib.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "CIDLFrontendLib.mak" CFG="CIDLFrontendLib - Win32 Debug_tao"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "CIDLFrontendLib - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "CIDLFrontendLib - Win32 Debug_mico" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "CIDLFrontendLib - Win32 Debug_orbacus" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "CIDLFrontendLib - Win32 Debug_tao" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "CIDLFrontendLib"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CIDLFrontendLib - Win32 Release"

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

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLFrontendLib___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "CIDLFrontendLib___Win32_Debug_mico"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CIDLFrontendLib___Win32_Debug_mico"
# PROP Intermediate_Dir "CIDLFrontendLib___Win32_Debug_mico"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "KC_DEPRECATED" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /D "YYERROR_VERBOSE" /D "YYDEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"CIDLFrontendLib.lib"
# ADD LIB32 /nologo /out:"CIDLFrontendLib.lib"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLFrontendLib___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "CIDLFrontendLib___Win32_Debug_orbacus"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_orbacus_vc6"
# PROP Intermediate_Dir "Debug_orbacus_vc6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GR /GX /ZI /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /ZI /Od /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "$(ORBACUS)\include" /I "$(ORBACUS)\include\ob" /D "KC_DEPRECATED" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /D "YYERROR_VERBOSE" /D "YYDEBUG" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"CIDLFrontendLib.lib"
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CIDLFrontendLib___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "CIDLFrontendLib___Win32_Debug_tao"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_tao"
# PROP Intermediate_Dir "Debug_tao"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "$(MICO)\include" /I "$(MICO)\include\windows" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /I "..\..\CIDL_Repository\IFRidl" /I "..\..\CIDL_Repository\ComponentRepositoryLib" /I "..\..\CIDL_Repository\CIDLRepositoryLib" /I "$(TAO)\TAO" /I "$(TAO)\TAO\tao" /I "$(TAO)" /I "$(TAO)\TAO\tao\DynamicAny" /D "KC_DEPRECATED" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /D "YYERROR_VERBOSE" /D "YYDEBUG" /D "_WINDOWS" /D "TAO_ORB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"CIDLFrontendLib.lib"
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "CIDLFrontendLib - Win32 Release"
# Name "CIDLFrontendLib - Win32 Debug_mico"
# Name "CIDLFrontendLib - Win32 Debug_orbacus"
# Name "CIDLFrontendLib - Win32 Debug_tao"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\cg_io.cpp
# End Source File
# Begin Source File

SOURCE=.\cidl.cpp
# End Source File
# Begin Source File

SOURCE=.\cidl_attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\debug.cpp
# End Source File
# Begin Source File

SOURCE=.\error.cpp
# End Source File
# Begin Source File

SOURCE=.\frontend.cpp
# End Source File
# Begin Source File

SOURCE=.\getopt.c
# End Source File
# Begin Source File

SOURCE=.\getopt1.c
# End Source File
# Begin Source File

SOURCE=.\global.cpp
# End Source File
# Begin Source File

SOURCE=.\k.cpp
# End Source File
# Begin Source File

SOURCE=.\lexana.cpp
# End Source File
# Begin Source File

SOURCE=.\options.cpp
# End Source File
# Begin Source File

SOURCE=.\pretty.cpp
# End Source File
# Begin Source File

SOURCE=.\print_idl.cpp
# End Source File
# Begin Source File

SOURCE=.\printer.cpp
# End Source File
# Begin Source File

SOURCE=.\repository.cpp
# End Source File
# Begin Source File

SOURCE=.\resolve_symtab.cpp
# End Source File
# Begin Source File

SOURCE=.\symtab.cpp
# End Source File
# Begin Source File

SOURCE=.\tree.cpp
# End Source File
# Begin Source File

SOURCE=.\unpk.cpp
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# Begin Source File

SOURCE=.\version.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\attributes.h
# End Source File
# Begin Source File

SOURCE=.\cg_io.h
# End Source File
# Begin Source File

SOURCE=.\cidl.h
# End Source File
# Begin Source File

SOURCE=.\cidl_attributes.h
# End Source File
# Begin Source File

SOURCE=.\debug.h
# End Source File
# Begin Source File

SOURCE=.\errmsg.h
# End Source File
# Begin Source File

SOURCE=.\error.h
# End Source File
# Begin Source File

SOURCE=.\frontend.h
# End Source File
# Begin Source File

SOURCE=.\getopt.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\k.h
# End Source File
# Begin Source File

SOURCE=.\lexana.h
# End Source File
# Begin Source File

SOURCE=.\options.h
# End Source File
# Begin Source File

SOURCE=.\pretty.h
# End Source File
# Begin Source File

SOURCE=.\print_idl.h
# End Source File
# Begin Source File

SOURCE=.\printer.h
# End Source File
# Begin Source File

SOURCE=.\repository.h
# End Source File
# Begin Source File

SOURCE=.\resolve_symtab.h
# End Source File
# Begin Source File

SOURCE=.\symtab.h
# End Source File
# Begin Source File

SOURCE=.\tree.h
# End Source File
# Begin Source File

SOURCE=.\unpk.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# End Group
# Begin Group "Kimwitu"

# PROP Default_Filter "k"
# Begin Source File

SOURCE=.\attributes.k
# End Source File
# Begin Source File

SOURCE=.\cg_io.k
# End Source File
# Begin Source File

SOURCE=.\cidl_attributes.k
# End Source File
# Begin Source File

SOURCE=.\debug.k
# End Source File
# Begin Source File

SOURCE=.\error.k
# End Source File
# Begin Source File

SOURCE=.\frontend.k

!IF  "$(CFG)" == "CIDLFrontendLib - Win32 Release"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_mico"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_orbacus"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_tao"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\global.k
# End Source File
# Begin Source File

SOURCE=.\options.k
# End Source File
# Begin Source File

SOURCE=.\pretty.k
# End Source File
# Begin Source File

SOURCE=.\print_idl.k
# End Source File
# Begin Source File

SOURCE=.\printer.k
# End Source File
# Begin Source File

SOURCE=.\repository.k
# End Source File
# Begin Source File

SOURCE=.\resolve_symtab.k
# End Source File
# Begin Source File

SOURCE=.\symtab.k
# End Source File
# Begin Source File

SOURCE=.\tree.k

!IF  "$(CFG)" == "CIDLFrontendLib - Win32 Release"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_mico"

# Begin Custom Build
InputPath=.\tree.k

BuildCmds= \
	$(KC++) --no-rewrite --no-csgio --no-printdot --covariant=no --yystype  --suffix=cpp *.k

"k.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"k.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"unpk.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"unpk.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"attributes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"attributes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cg_io.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cg_io.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl_attributes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl_attributes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"debug.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"debug.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"error.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"frontend.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"frontend.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"global.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"global.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"options.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"options.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pretty.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pretty.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"print_idl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"print_idl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"printer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"printer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"repository.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"repository.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"resolve_symtab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"resolve_symtab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"symtab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"symtab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tree.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tree.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"util.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"util.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_orbacus"

# Begin Custom Build
InputPath=.\tree.k

BuildCmds= \
	$(KC++) --no-rewrite --no-csgio --no-printdot --covariant=no --yystype  --suffix=cpp *.k

"k.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"k.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"unpk.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"unpk.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"attributes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"attributes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cg_io.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cg_io.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl_attributes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl_attributes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"debug.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"debug.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"error.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"frontend.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"frontend.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"global.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"global.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"options.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"options.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pretty.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pretty.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"print_idl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"print_idl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"printer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"printer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"repository.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"repository.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"resolve_symtab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"resolve_symtab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"symtab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"symtab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tree.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tree.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"util.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"util.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_tao"

# Begin Custom Build
InputPath=.\tree.k

BuildCmds= \
	$(KC++) --no-rewrite --no-csgio --no-printdot --covariant=no --yystype  --suffix=cpp *.k

"k.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"k.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"unpk.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"unpk.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"attributes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"attributes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cg_io.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cg_io.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl_attributes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl_attributes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"debug.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"debug.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"error.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"error.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"frontend.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"frontend.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"global.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"global.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"options.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"options.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pretty.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"pretty.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"print_idl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"print_idl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"printer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"printer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"repository.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"repository.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"resolve_symtab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"resolve_symtab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"symtab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"symtab.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tree.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tree.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"util.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"util.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\util.k
# End Source File
# End Group
# Begin Group "lex"

# PROP Default_Filter "l"
# Begin Source File

SOURCE=.\lexana.l

!IF  "$(CFG)" == "CIDLFrontendLib - Win32 Release"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_mico"

# Begin Custom Build
InputPath=.\lexana.l

"lexana.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(LEX) -tw -Sflex.skel lexana.l  > lexana.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_orbacus"

# Begin Custom Build
InputPath=.\lexana.l

"lexana.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(LEX) -tw -Sflex.skel lexana.l  > lexana.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_tao"

# Begin Custom Build
InputPath=.\lexana.l

"lexana.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(LEX) -tw -Sflex.skel lexana.l  > lexana.cpp

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "yacc"

# PROP Default_Filter "y"
# Begin Source File

SOURCE=.\cidl.output

!IF  "$(CFG)" == "CIDLFrontendLib - Win32 Release"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_mico"

# Begin Custom Build
InputPath=.\cidl.output

BuildCmds= \
	"$(PYTHON)" errmsg.py < cidl.output > errmsg.cpp \
	echo extern char *error_message[];  > errmsg.h \
	

"errmsg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"errmsg.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_orbacus"

# Begin Custom Build
InputPath=.\cidl.output

BuildCmds= \
	"$(PYTHON)" errmsg.py < cidl.output > errmsg.cpp \
	echo extern char *error_message[];  > errmsg.h \
	

"errmsg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"errmsg.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_tao"

# Begin Custom Build
InputPath=.\cidl.output

BuildCmds= \
	"$(PYTHON)" errmsg.py < cidl.output > errmsg.cpp \
	echo extern char *error_message[];  > errmsg.h \
	

"errmsg.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"errmsg.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cidl.y

!IF  "$(CFG)" == "CIDLFrontendLib - Win32 Release"

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_mico"

# Begin Custom Build
InputPath=.\cidl.y

BuildCmds= \
	env LC_ALL=C $(YACC) -y -v -d -o cidl.cpp cidl.y \
	copy cidl.hpp cidl.h \
	

"cidl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.output" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_orbacus"

# Begin Custom Build
InputPath=.\cidl.y

BuildCmds= \
	env LC_ALL=C $(YACC) -y -v -d -o cidl.cpp cidl.y \
	copy cidl.hpp cidl.h \
	

"cidl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.output" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CIDLFrontendLib - Win32 Debug_tao"

# Begin Custom Build
InputPath=.\cidl.y

BuildCmds= \
	env LC_ALL=C $(YACC) -y -v -d -o cidl.cpp cidl.y \
	copy cidl.hpp cidl.h \
	

"cidl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.hpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"cidl.output" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
