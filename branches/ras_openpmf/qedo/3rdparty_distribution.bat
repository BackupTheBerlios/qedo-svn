@echo off
set qedo=%QEDO%
if not "%qedo%" == "" goto START
echo ************ Please set first the QEDO Environment variable to the target path!
goto ENDSETUP


:START

echo ************ Start Distribution.
set actdir=%qedo%
echo *** Create QEDO Root-Directory at %actdir%...
mkdir %actdir%

echo ************ Copy MICO DLLs ************ 
set actdir=%qedo%\bin
echo *** Create %actdir%...
mkdir %actdir%
copy %MICO%\win32-bin\micocoss2311.dll %actdir%
copy %MICO%\win32-bin\mico2311.dll %actdir%
copy %MICO%\win32-bin\idl2311.dll %actdir%
copy %MICO%\win32-bin\idl.exe %actdir%
copy %MICO%\win32-bin\mico-cpp.exe %actdir%
copy %MICO%\win32-bin\nsd.exe %actdir%


echo ************ Copy MICO ************ 
set actdir=%qedo%\include
echo *** Create %actdir%...
mkdir %actdir%

set actdir=%qedo%\include\mico
echo *** Create %actdir%...
mkdir %actdir%

copy %MICO%\include\* %actdir%

mkdir %actdir%\coss
copy %MICO%\include\coss %actdir%\coss

mkdir %actdir%\mico
copy %MICO%\include\mico %actdir%\mico
mkdir %actdir%\mico\os-thread
copy %MICO%\include\mico\os-thread %actdir%\mico\os-thread
mkdir %actdir%\mico\security
copy %MICO%\include\mico\security %actdir%\mico\security
mkdir %actdir%\mico\transport
copy %MICO%\include\mico\transport %actdir%\mico\transport

mkdir %actdir%\windows
copy %MICO%\include\windows %actdir%\windows

set actdir=%qedo%\lib
echo *** Create %actdir%...
mkdir %actdir%
copy %MICO%\win32-bin\lib\idl2311.lib %actdir%
copy %MICO%\win32-bin\lib\mico2311.lib %actdir%
copy %MICO%\win32-bin\lib\micocoss2311.lib %actdir%

echo ************ Copy PTHREADS ************ 
set actdir=%qedo%\include\pthreads
echo *** Create %actdir%...
mkdir %actdir%

copy %PTHREADS%\include %actdir%

set actdir=%qedo%\lib
echo *** Create %actdir%...
mkdir %actdir%

copy %PTHREADS%\lib\pthreadVC2.lib %actdir%

set actdir=%qedo%\bin
echo *** Create %actdir%...
mkdir %actdir%

copy %PTHREADS%\lib\pthreadVC2.dll %actdir%

echo ************ Copy XERCES ************ 
set actdir=%qedo%\bin
echo *** Create %actdir%...
mkdir %actdir%

copy %XERCES%\bin\xerces-c_2_6D.dll %actdir%
copy %XERCES%\bin\xerces-c_2_6.dll %actdir%


echo ************ Copy ZIP/ZLIB ************ 
set actdir=%qedo%\bin
echo *** Create %actdir%...
mkdir %actdir%

copy %ZLIB%\zlib1.dll %actdir%
copy %CYGWIN%\zip.exe %actdir%
copy %CYGWIN%\cygwin1.dll %actdir%

echo ************ Copy WXWIDGETS ************ 
set actdir=%qedo%\bin
echo *** Create %actdir%...
mkdir %actdir%

copy %WXWIDGETS%\lib\vc_dll\wxmsw26d_core_vc_custom.dll %actdir%
copy %WXWIDGETS%\lib\vc_dll\wxbase26d_vc_custom.dll %actdir%
copy %WXWIDGETS%\lib\vc_dll\wxmsw26d_html_vc_custom.dll %actdir%

copy %WXWIDGETS%\lib\vc_dll\wxmsw26_core_vc_custom.dll %actdir%
copy %WXWIDGETS%\lib\vc_dll\wxbase26_vc_custom.dll %actdir%
copy %WXWIDGETS%\lib\vc_dll\wxmsw26_html_vc_custom.dll %actdir%



echo ************ End Distribution.

:ENDSETUP

