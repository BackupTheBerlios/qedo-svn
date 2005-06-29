# Microsoft Developer Studio Project File - Name="Assembly" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=Assembly - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Assembly.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Assembly.mak" CFG="Assembly - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Assembly - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Assembly - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Assembly - Win32 Release"

# PROP BASE Use_MFC
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f Assembly.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Assembly.exe"
# PROP BASE Bsc_Name "Assembly.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f Assembly.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "Assembly.exe"
# PROP Bsc_Name "Assembly.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Assembly - Win32 Debug"

# PROP BASE Use_MFC
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f Assembly.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Assembly.exe"
# PROP BASE Bsc_Name "Assembly.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "wzzip.exe ..\..\AssemblyStarter\dinner.zip ..\CutleryExecutor\cutlery.zip ..\PhilosophersExecutors\philosopher.zip  ..\PhilosophersExecutors\observer.zip philosophers.cad atze.cpf bob.cpf charly.cpf"
# PROP Rebuild_Opt ""
# PROP Target_File "must_be_here_to_force_generation"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Assembly - Win32 Release"
# Name "Assembly - Win32 Debug"

!IF  "$(CFG)" == "Assembly - Win32 Release"

!ELSEIF  "$(CFG)" == "Assembly - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "xml"

# PROP Default_Filter "xml"
# End Group
# Begin Source File

SOURCE=.\atze.cpf
# End Source File
# Begin Source File

SOURCE=.\bob.cpf
# End Source File
# Begin Source File

SOURCE=.\charly.cpf
# End Source File
# Begin Source File

SOURCE=.\philosophers.cad
# End Source File
# End Target
# End Project
