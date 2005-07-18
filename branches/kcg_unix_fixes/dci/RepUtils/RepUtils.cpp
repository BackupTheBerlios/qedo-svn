#include "RepUtils.h"

void
RepUtils::save_file(const char * filepath, const CORBA::OctetSeq* file){
	std::ofstream ofs(filepath, std::ios::binary|std::ios::out);
	if (!ofs)
	{
		NORMAL_ERR2( "save_file(): file can not be saved locally path=", filepath );
		throw Components::Deployment::InstallationFailure();
	}
	const CORBA::Octet* it = file->get_buffer();
	ofs.write((char*)it, file->length());
	ofs.close();
}

void
RepUtils::get_file(const char * filepath, CORBA::OctetSeq* file){
	struct stat statbuff;
	int rt = stat(filepath, &statbuff);
	long size = statbuff.st_size;
	file->length(size);
	std::ifstream ifs(filepath, std::ios::binary|std::ios::in);
	if (!ifs)
	{
		NORMAL_ERR2( "get_file(): file can not read path=", filepath);
		throw Components::Deployment::InstallationFailure();
	}
	ifs.read((char*)file->get_buffer(), size);
	ifs.close();
}


CORBA::Object_ptr
RepUtils::convert_strRef(const string ref){
	// TODO: CORBA::ORB_var orb = context_->resolve_service_reference("ORB");
	int dummy = 0;
	CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);
	CORBA::Object_var obj;
	if (ref.empty())
	{
		NORMAL_ERR("convert_strRef(): ref empty!");
		throw ::Components::Deployment::InvalidLocation();
	}
	else
		try {
			obj = orb->string_to_object(ref.c_str());
		}
		catch(...) {
			NORMAL_ERR2("convert_strRef(): string_to_object failed! ref=", ref);
			throw ::Components::Deployment::InvalidLocation();
		};
	if( CORBA::is_nil(obj.in()) ) 
	{
		NORMAL_ERR2("convert_strRef(): obj reference nil! ref=", ref);
		throw ::Components::Deployment::InvalidLocation();
	}
	return obj._retn();
}

CORBA::Object_ptr
RepUtils::get_repRef(const string repref){
	string repPraefix(REPREFPREFIX);
	if(repref.substr(0,repPraefix.length()) != repPraefix) {
		NORMAL_ERR2("get_repRef(): repref invalid! repref=", repref);
		throw ::Components::Deployment::InvalidLocation();
	}
    return convert_strRef(repref.substr(repPraefix.length(),repref.length()-repPraefix.length()));
}

string
RepUtils::get_strRef(CORBA::Object_ptr obj){
	// TODO: CORBA::ORB_var orb = context_->resolve_service_reference("ORB");
	int dummy = 0;
	CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);
	std::string location("RepRef=");
	return orb->object_to_string(obj);
}

string
RepUtils::get_strRefRep(CORBA::Object_ptr obj){
	return REPREFPREFIX+get_strRef(obj);
}

//::MDE::Deployment::DeploymentPackage_ptr 
//RepUtils::get_rep_root(DCI::RepositoryDeploymentRoot_ptr repo) {
//
//	//if ( CORBA::is_nil ( context_ ) ) {
//	//	NORMAL_ERR("get_rep_root(): context_ nil!");
//	//	throw CORBA::SystemException();
//	//}
//	//DCI::RepositoryDeploymentRoot_ptr repo = context_->get_connection_rep_root();
//	if ( CORBA::is_nil ( repo ) ) {
//		NORMAL_ERR("get_rep_root(): repo nil!");
//		throw CORBA::SystemException();
//	}
//	CORBA::Object_ptr ptr;
//	try {
//		ptr = repo->get_root_package();
//	}
//	catch(...) {
//		NORMAL_ERR("get_rep_root(): connection_rep_root nil!");
//		throw CORBA::SystemException();
//	}
//    MDE::Deployment::DeploymentPackage_var deployment_pkg_ref;
//	try {
//		deployment_pkg_ref = MDE::Deployment::DeploymentPackage::_narrow(ptr);
//	}
//	catch(...) {
//		NORMAL_ERR("get_rep_root(): connection_rep_root nil!");
//		throw CORBA::SystemException();
//	}
//	if ( CORBA::is_nil ( deployment_pkg_ref ) ) {
//		NORMAL_ERR("get_rep_root(): deployment_pkg_ref nil!");
//		throw CORBA::SystemException();
//	}
//	return deployment_pkg_ref._retn();
//}
//
CORBA::OctetSeq*
RepUtils::get_OctetSeq(const char* str)
{
	CORBA::OctetSeq* octet_key = new CORBA::OctetSeq();

	unsigned int str_len = strlen (str);
	octet_key->length (str_len);

	for (unsigned int i = 0; i < str_len; i++)
	{
		(*octet_key)[i] = str[i];
	}

	return octet_key;
}

const char*
RepUtils::get_String(CORBA::OctetSeq octet_key)
{
	CORBA::String_var str = CORBA::string_alloc(octet_key.length()+1); 
	for (unsigned int i = 0; i < octet_key.length(); i++)
	{
		str.inout()[i] = octet_key[i];
	}
	str.inout()[i] = 0; //NULL terminated string!
	return str._retn();
}
