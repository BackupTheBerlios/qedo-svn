#include "explore.h"
//#include "explore.cpp"

class Explore_impl : virtual public POA_Explore {
public: 

	::ComponentServerActivatorInfoList* explore_qedo() ;
	int e_argc;
	char** e_argv;
	CORBA::ORB_var e_orb;


};

class test {
};