# input Parameter 1 should be the Qedo install directory (e.g. /opt/qedo)

#### start distribution ####
mkdir -p $1;
#### bin dir ####
mkdir -p $1/bin;
cp ComponentInstaller/qci $1/bin;
cp ComponentServerActivator/qcsa $1/bin;
cp ComponentServer/qcs $1/bin;
cp HomeFinder/homefinder $1/bin;
cp DeploymentClient/qdeploy $1/bin;
cp AssemblyFactory/qassf $1/bin;

#### etc dir ####
mkdir -p $1/etc;
cp etc/*.* $1/etc;

mkdir -p $1/include;
cp ComponentIDL/*.h $1/include;
cp ComponentContainer/*.h $1/include;

mkdir -p $1/idl;
cp ComponentIDL/*.idl $1/idl;

mkdir -p $1/lib;
cp ComponentIDL/libComponentIDL.so $1/lib;
cp ComponentContainer/libComponentContainer.so /$1/lib;


