@echo off
set qedo=%QEDO%
if not "%qedo%" == "" goto START
echo ************ Please set first the QEDO Environment variable to the target path!
goto ENDSETUP
:START
echo ************ Start Setup.
set actdir=%qedo%
echo ************ Create QEDO Root-Directory at %actdir%...
md %actdir%

set actdir=%qedo%\bin
echo ************ Create %actdir%...
md %actdir%

set actdir=%qedo%\etc
echo ************ Create %actdir%...
md %actdir%
copy etc\*.* %actdir%

set actdir=%qedo%\include
echo ************ Create %actdir%...
md %actdir%
copy ComponentIDL\*.idl %actdir%
copy ComponentContainer\*.h %actdir%

set actdir=%qedo%\lib
echo ************ Create %actdir%...
md %actdir%

echo ************ End Setup.

:ENDSETUP

