echo Starting mico Nameservice on 12356
start nsd -ORBIIOPAddr inet:haw:12356
echo Starting Component Installer
start qci
echo Starting Assembly Manager Factory
start qassf.exe
echo Starting Component Server Activator
start qcsa.exe
echo starting HomeFinder
start homefinder.exe
