#include <fstream>
#include <sys/stat.h>

#include <CORBA.h>
#include <Components.h>
#include <Output.h>

#include "MDE.h"
//#include "..\DCI_SERVANT\DCI_EQUIVALENT.h"


using namespace std;

#define REPREFPREFIX  "RepRef="

class RepUtils {

public:
	static void save_file(const char * filepath, const CORBA::OctetSeq* file);

	static void get_file(const char * filepath, CORBA::OctetSeq* file);

	static CORBA::Object_ptr convert_strRef(const string ref);

	static CORBA::Object_ptr get_repRef(const string repref);

	static string get_strRef(CORBA::Object_ptr obj);

	static string get_strRefRep(CORBA::Object_ptr obj);

//	static ::MDE::Deployment::DeploymentPackage_ptr get_rep_root(::DCI::RepositoryDeploymentRoot_ptr repo);

	static CORBA::OctetSeq* get_OctetSeq(const char* str);

	static const char* get_String(CORBA::OctetSeq octet_key);
};