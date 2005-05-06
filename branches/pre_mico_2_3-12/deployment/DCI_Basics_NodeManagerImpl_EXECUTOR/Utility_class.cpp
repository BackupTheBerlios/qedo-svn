/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

// Utility_class.cpp: Implementierung der Klasse Utility_class.
//
//////////////////////////////////////////////////////////////////////

#include "Utility_class.h"
#ifdef WIN32
#include "direct.h"
#endif
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Utility_class::Utility_class()
{

}

Utility_class::~Utility_class()
{

}


// If the integer parameter (type) is equal to FILE, this function returns true if a file
// with a pathname equal to the string parameter (object) exists, false else.
// If the integer parameter (type) is equal to DIRECTORY, this function returns true if a
// directory with a pathname equal to the string parameter (object) exists, false else.
// If the integer parameter (type) is equal to DIRECTORY_OR_FILE, this function returns true
// if an object (directory or file) with a pathname equal to the string parameter (object)
// exists, false else.

bool Utility_class::exists(std::string object,int type) 
{
  struct stat statbuff;
  int rt = stat(object.c_str(), &statbuff);

  if (rt < 0)
	return(false); // No object with this pathname exists.
  else 
  { // An object exists.
    if (type == DIRECTORY_OR_FILE)
		return(true);
    else if (type == DIRECTORY) // Is it a directory ?
      switch(statbuff.st_mode & S_IFMT) 
		{
        case S_IFDIR: return(true); // It is a directory.
        default: return(false); // It is not a directory.
		}
    else if (type == FILE) // Is it a file ?
      switch(statbuff.st_mode & S_IFMT) {
        case S_IFREG: return(true); // It is a file.
        default: return(false); // It is not a file.
      }
    else // Integer parameter (type) has an invalid value.
		return(false);
  }
}

int Utility_class::makedir(std::string dir,  bool quiet_mode) {
  if (exists(dir,DIRECTORY_OR_FILE)) { // An object with the "dir" pathname already exists.
    return(1); // No directory created.
  }
  else { // A directory has to be created.
#ifdef _WINDOWS
    int err = _mkdir(dir.c_str());
#else
    int err = mkdir(dir.c_str(),0755);
#endif
    if ((!exists(dir,DIRECTORY)) || (err != 0)) { // The "dir" directory can not been created.
		if(!quiet_mode)	
			std::cout << "Problem creating the directory " << dir << '\n';
		return(2); // No directory created.
    }
    else // Directory created.
      return(0);
  }
}

// This function removes the object whose pathname is specified by the string parameter
// (object). The returned value is 0 if the object to destroy exists, 1 else.

int Utility_class::suppression(std::string object, bool is_NT) {
  if (exists(object,DIRECTORY_OR_FILE)) { // The object to destroy exists.
#ifdef _WINDOWS
    if (exists(object,DIRECTORY)) {
		std::string command;
      if (is_NT)
        command = std::string("rmdir /S /Q ") + object;
      else
        command = std::string("deltree /Y ") + object;
      system(command.c_str());
    } else {
		if (is_NT) {
        std::string command = std::string("del /F /Q ") + object;
        system(command.c_str());
      } else
        ::DeleteFile(object.c_str());
	}
#else
    std::string command = std::string("\\rm -rf ") + object;
    system(command.c_str());
#endif
    return(0);
  }
  else // The object to destroy does not exist.
    return(1);
}

std::string Utility_class::int2string(int num) {
	std::string ret = "";
	if (num < 0)
		return(std::string("-")+int2string(-num));
	else {
		int number = num;
		char chara;
		while (number > 9) {
			int temp = number % 10;
			chara = '0' + temp;
			ret = chara + ret;
			number = number - temp;
			number = number/10;
		} // end while
		chara = '0' + number;
		ret = chara + ret;
	} // end else
	return(ret);
} // end int2string


// Returns the name of the object (directory or file) without the part corresponding to the path.

std::string Utility_class::name_without_path(std::string pathname) 
{
  std::string name = pathname;
  int i;
  i = name.find_last_of("/");
  if ((i >= 0) && (i < name.size()))
    name.replace(0,i+1,std::string(""));
  return(name);
}

std::string Utility_class::name_without_path_w(std::string pathname) 
{
  std::string name = pathname;
  int i;
  i = name.find_last_of("\\");
  if ((i >= 0) && (i < name.size()))
    name.replace(0,i+1,std::string(""));
  return(name);
}

std::string Utility_class::path_name(std::string pathname)
{
	std::string name = pathname;
	int i;
	i = name.find_last_of("\\"); // in C++ syntax symbol: \ 
    name.erase(i, name.length());
  return(name);
}

std::string Utility_class::name_without_end(std::string pathname)
{
	std::string name = pathname;
  int i;
  i = name.find_last_of(".");
    name.erase(i,4);
  return(name);
}

// Moves an objet (directory or file). The first string parameter (source) specifies
// the object and the second (destination) the destination directory pathname.
// The return value is 1 if the destination directory exists, 0 else.

int Utility_class::mv(std::string unix_source, std::string destination, bool is_NT) {
  if (exists(destination,DIRECTORY)) {
    std::string source = unix_source;
// add by lth on 4.19
  /*  std::string label;
    P924::ProgressBar_var pBar;

    if (use_gui) {
      label= std::string("install ") + source;
      pBar =pBarFactory->create(label.c_str());
	} */
//
#ifdef _WINDOWS // For Windows
    source = change_path_format(unix_source);
	std::string command;
    if (is_NT) { // For Windows NT/2000
      std::string destination_object = destination + "\\";
      destination_object = destination_object + name_without_path(unix_source);
      if (exists(destination_object,DIRECTORY_OR_FILE))
        suppression(destination_object, is_NT);
      command = std::string("move ") + source + std::string(" ") + destination;
    } else // For Windows 95/98
      command = std::string("move /Y ") + source + std::string(" ") + destination;
#else // For Unix and Linux
    std::string command = std::string("\\mv ") + source + std::string(" ") + destination;
#endif
    system(command.c_str());
// add by lth on 4.19
    /*if (use_gui) {
      for (int i =20; i <= 100; i+=20) {
        pBar->update(i);
        Sleep(600);          //miseconds;
	  }
      pBarFactory->destroy(pBar);
	}*/
//
    return(0);
  }
  else
    return(1);
}


// Transforms a UNIX pathname into a WINDOWS pathname.

std::string Utility_class::change_path_format(std::string pth)
{
  std::string modified = pth;
  int f = modified.find_first_of("/");
  while ((f >= 0) && (f < modified.size())) {
    modified.replace(f,1,"\\");
    f = modified.find_first_of("/");
  }

  return(modified);
}


// Returns the string corresponding to the current directory.

std::string Utility_class::get_current_directory() {
#ifdef _WINDOWS // For Windows
  char path[1024];
  ::GetCurrentDirectory(1024,path);
  return(std::string(path));
#else // For Unix and Linux
  return(std::string(getenv("PWD")));
#endif
}

std::string Utility_class::correct(std::string directory, Repository UuidRepository) 
{
  int i = 2;
  std::string dir = directory;
  bool incorrect = UuidRepository.find_path(dir);
  bool exist = Utility_class::exists(dir,DIRECTORY_OR_FILE);
  while (exist || incorrect) 
  {
	dir = directory + int2string(i++);
	exist = Utility_class::exists(dir,DIRECTORY_OR_FILE);
    incorrect = UuidRepository.find_path(dir);
  }
  return(dir);
}

void Utility_class::copy_file_to_file(std::string from_file, std::string to_file)
{
	std::ifstream from (from_file.c_str());
	std::ofstream to; 
	to.open ( to_file.c_str(), std::ios_base::out );
	char ch;
	while (from.get(ch)) to.put(ch); 
	to.close();
	from.close();
}

void Utility_class::copy_archive_to_file (const DCI_Basics::ComponentArchive& archive, std::string pathname)
{
	std::ofstream out;
	out.open ( pathname.c_str(), std::ios_base::binary | std::ios_base::out );
	int size = archive.length();
	for (long i=0; i<size;i++) 
	{
		out << archive[i];
	}
	out.close();
}

void Utility_class::copy_file_to_archive (const std::string pathname, DCI_Basics::ComponentArchive& archive)
{
	std::ifstream in_;
	in_.open ( pathname.c_str(), std::ios_base::binary | std::ios_base::in  );
	int size_ = in_.rdbuf()->in_avail();
	int is_o = in_.is_open();
	char ch;
	archive.length(0);
	long int i = 0;
	while ( in_.read(&ch, 1) )
	{
		archive.length(archive.length()+1);
		archive[i++] = ch;
	}
	std::cout << "ZIP-File is read in Implementation Archive !!!";
	in_.close();
}


void Utility_class::copy_file_to_string (const std::string pathname, std::string& out_string)
{
	std::ifstream in_;
	in_.open ( pathname.c_str(),  std::ios_base::in  );
	int size_ = in_.rdbuf()->in_avail();
	int is_o = in_.is_open();
	char ch;
	long int i = 0;
	while ( in_.read(&ch, 1) )
	{
		out_string = out_string + ch;
	}
	in_.close();
}

void Utility_class::copy_string_to_file (const std::string out_string , std::string& pathname)
{
	std::ofstream out;
	out.open ( pathname.c_str(), std::ios_base::out );
	int size = out_string.length();
	for (long i=0; i<size;i++) 
	{
		out << out_string[i];
	}
	out.close();
}

void Utility_class::show_chuck (const CosNaming::BindingList &bl) //helper function
{
	for (CORBA::ULong i = 0; i < bl.length(); i++)
	{
		std::cout << bl[i].binding_name[0].id;
		if (bl[i].binding_name[0].kind != '\0')
			std::cout << "(" <<bl[i].binding_name[0].kind << ")";
		if (bl[i].binding_type == CosNaming::ncontext)
			std::cout << ":  context" << std::endl;
		else
			std::cout << ":  reference" << std::endl;
	}
};	

void Utility_class::list_context (CosNaming::NamingContext_ptr nc)
{
	CosNaming::BindingIterator_var it;
	CosNaming::BindingList_var bl;
	const CORBA::ULong CHUCK = 100;
	nc -> list (CHUCK, bl, it);
	Utility_class::show_chuck (bl);
	if (!CORBA::is_nil(it)) 
	{
		while (it->next_n(CHUCK, bl))
			Utility_class::show_chuck (bl);
			it->destroy();
	}
};

std::string Utility_class::strip (std::string str)
{
	char *target;
   int i = 0;
   int len = str.length();
   int begin = 0;
   int end   = 0;
   char saveCh = NULL;

   for (i = 0; str[i] != '\0'; i++)
       if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
           continue;
       else
           break;
   begin = i;

   for (i = len - 1; i >= 0; i--)
       if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
           continue;
       else
           break;
   end = i + 1;

   int nlen = len - begin - (len - end);
   target = new char[nlen + 1];
   for (i = 0; i < nlen; i++)
       target[i] = str[begin + i];
   target[i] = '\0';


   // memory of target is to be released by caller!!
   return target; 
}