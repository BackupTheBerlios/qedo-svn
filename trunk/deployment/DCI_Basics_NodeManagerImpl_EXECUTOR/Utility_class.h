// Utility_class.h: Schnittstelle für die Klasse Utility_class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_UTILITY_CLASS_H__4F4B2942_C3F4_4FA8_B3D7_7C5C61648424__INCLUDED_)
#define AFX_UTILITY_CLASS_H__4F4B2942_C3F4_4FA8_B3D7_7C5C61648424__INCLUDED_

#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <string>
#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include "Deployment_dpe.hh"
#include "DCI_Basics_NodeManagerImpl_EQUIVALENT_skel.h"
#include "Repository.h"
#include "../Unzip/Unzip.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Utility_class  
{

protected:

public:
	Utility_class();
	virtual ~Utility_class();

	//static Repository UuidRepository;
	static enum Status { DIRECTORY_OR_FILE, DIRECTORY, FILE };

	static bool exists(std::string,int type); // If the integer parameter is equal to FILE, this function
                             // returns true if a file with a pathname equal to the string
                             // parameter exists, false else.
                             // If the integer parameter is equal to DIRECTORY, this function
                             // returns true if a directory with a pathname equal to the
                             // string parameter exists, false else.
                             // If the integer parameter is equal to DIRECTORY_OR_FILE, this
                             // function returns true if an object with a pathname equal to
                             // the string parameter exists, false else.
	static int makedir(std::string, bool quiet_mode); // Makes the directory whose pathname is specified by the string
                         // parameter. The return value is 1 if the object already exists,
                         // 2 if there is a problem creating it and 0 else.
	static int suppression(std::string, bool is_NT); // This function removes the object whose pathname is specified
                             // by the string parameter. The returned value is 0 if the object
                             // to destroy exists, 1 else.
	static std::string int2string(int num);
	static std::string name_without_path(std::string );
	static std::string name_without_path_w(std::string );
	static std::string name_without_end(std::string );
	static std::string path_name(std::string pathname);
	static int mv(std::string unix_source, std::string destination, bool is_NT);
	static std::string change_path_format(std::string pth);
	static std::string get_current_directory();
	static std::string correct(std::string, Repository); // This function adds a suffix to the string parameter if the
                            // directory named by this string already exists and the function
                            // returns the possibly modified string.
	static void copy_file_to_file(std::string , std::string );
	static void  show_chuck (const CosNaming::BindingList &bl);
	static void list_context (CosNaming::NamingContext_ptr nc);
	static std::string strip (std::string);
	static void copy_archive_to_file (const DCI_Basics::ComponentArchive& archive, std::string pathname);
	static void copy_file_to_string (const std::string pathname, std::string& out_string);
	static void copy_file_to_archive (const std::string pathname, DCI_Basics::ComponentArchive& archive);
	static void copy_string_to_file (const std::string out_string , std::string& pathname);
};

#endif // !defined(AFX_UTILITY_CLASS_H__4F4B2942_C3F4_4FA8_B3D7_7C5C61648424__INCLUDED_)
