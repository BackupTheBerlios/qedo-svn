# input Parameter 1 should be the Qedo install directory (e.g. /opt/qedo)

#### start distribution ####
mkdir -p $2;
#### bin dir ####
mkdir -p $2/bin;
cp ComponentInstaller/ci $2/bin;
cp ComponentServerActivator/csa $2/bin;
cp ComponentServer/cs $2/bin;
cp HomeFinder/homefinder $2/bin;
cp DeploymentClient/deploy $2/bin;
cp AssemblyFactory/assf $2/bin;

#### etc dir ####
mkdir -p $2/etc;
cp etc/*.* $2/etc;

mkdir -p $2/include;
cp ComponentIDL/*.h $2/include;
cp ComponentContainer/*.h $2/include;

mkdir -p $2/idl;
cp ComponentIDL/*.idl $2/idl;

mkdir -p $2/lib;
cp ComponentIDL/libComponentIDL.so $2/lib;
cp ComponentContainer/libComponentContainer.so /$2/lib;


