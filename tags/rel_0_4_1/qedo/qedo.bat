echo Starting mico Nameservice on 12356
REM start nsd -ORBIIOPAddr inet:tri:12356
echo Starting Component Installer
start qci
echo Starting Assembly Manager Factory
start qassf.exe
echo Starting Component Server Activator
start qcsa.exe
echo starting HomeFinder
start homefinder.exe
