echo Starting mico Nameservice on 12356
REM start nsd -ORBIIOPAddr inet:tri:12356
echo Starting Component Installer
start ci
echo Starting Assembly Manager Factory
start assf.exe
echo Starting Component Server Activator
start csa.exe
echo starting HomeFinder
start homefinder.exe
