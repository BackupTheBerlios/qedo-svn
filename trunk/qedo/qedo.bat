echo Starting mico Nameservice on 3003
REM start nsd -ORBIIOPAddr inet:tri:3003
echo Starting Component Installer
start ci
echo Starting Assembly Manager Factory
start assf.exe
echo Starting Component Server Activator
start csa.exe
echo starting HomeFinder
start homefinder.exe
