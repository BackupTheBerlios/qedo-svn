@echo off
rem goto rootdir
%~d0
cd %~p0

copy %ACE_ROOT%\TAO\tao\IFR_Client\IFR_BasicC.h  ComponentIDL\IFR_Basic.h
copy %ACE_ROOT%\TAO\tao\IFR_Client\IFR_BasicC.h  ComponentIDL\IFR_Basic_skel.h

copy %ACE_ROOT%\TAO\tao\PortableServer\PortableServerC.h  ComponentIDL\PortableServer.h
copy %ACE_ROOT%\TAO\tao\PortableServer\PortableServerC.h  ComponentIDL\PortableServer_skel.h

copy %ACE_ROOT%\TAO\orbsvcs\orbsvcs\CosNamingC.h  ComponentIDL\CosNaming.h
copy %ACE_ROOT%\TAO\orbsvcs\orbsvcs\CosNamingC.h  ComponentIDL\CosNaming_skel.h
