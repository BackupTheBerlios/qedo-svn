@echo off
set qedo=%QEDO%
if not "%qedo%" == "" goto CHECKPARAM
echo ************ Please set first the QEDO Environment variable to the target path!
goto ENDSETUP
:CHECKPARAM
if not "%1" == "" goto START
echo ************ Please specify the output-directory of generation $(OutDir)!
goto ENDSETUP
:START
rem Goto rootdir
%~d0
cd %~p0

echo ************ Start Distribution.
set actdir=%qedo%
echo *** Create QEDO Root-Directory at %actdir%...
mkdir %actdir%

set actdir=%qedo%\bin
echo *** Create %actdir%...
mkdir %actdir%

set actdir=%qedo%\etc
echo *** Create %actdir%...
mkdir %actdir%
copy etc\*.* %actdir%

set actdir=%qedo%\include
echo *** Create %actdir%...
mkdir %actdir%
copy ComponentIDL\*.h %actdir%
copy ComponentContainer\*.h %actdir%

set actdir=%qedo%\idl
echo *** Create %actdir%...
mkdir %actdir%
copy ComponentIDL\*.idl %actdir%

set actdir=%qedo%\lib
echo *** Create %actdir%...
mkdir %actdir%
copy ComponentIDL\%1\ComponentIDL.lib %actdir%
copy ComponentContainer\%1\ComponentContainer.lib %actdir%

echo ************ End Distribution.

:ENDSETUP

