#ifndef __UNZIP_HEAD
#define __UNZIP_HEAD
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


//#include <OB/CORBA.h>

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef unix
# include <unistd.h>
# include <utime.h>
#else
# include <direct.h>
# include <io.h>
# include <wtypes.h>
#endif

#include "libunzip.h"
#include <list>

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)


// To extract files from an archive, an Unzip object has to be created
typedef std::list<std::string> FoundFileList;
class Unzip 
{
  private:
	  std::string _zipfilename;
	  FoundFileList _desciptors;

    void change_file_date(const char*,uLong,tm_unz);
    int mymkdir(const char*);
    int makedir(char* newdir);
    int do_extract_currentfile(unzFile,const int*,int*);
    int do_extract_onefile(unzFile,std::string,int,int);

  public:
// Constructor of the class. The string argument is
                        // the name of the archive file.
    Unzip(std::string); 

// Returns the list of pathnames of the descriptor files from the one type ("csd" or "cad"...)
// within the archive or the required file name from the archive
    void find_files_with_end( FoundFileList&, std::string ); 

    int extract(std::string); // Extracts a file from the archive. The file is
                              // specified by the string argument which represents
                              // the pathname of the file within the archive.
							  // The return value is 0 if no error.

	struct ArchiveOpenError_err
	{
		std::string _err;
		ArchiveOpenError_err(std::string err_) {_err = err_;}
	};
	struct ArchiveInfo_err
	{
		std::string _err;
		ArchiveInfo_err(std::string err_) {_err = err_;}
	};

	struct NotInArchive_err
	{
		std::string _err;
		NotInArchive_err(std::string err_) {_err = err_;}
	};

	struct GoToNextFile_err
	{
		std::string _err;
		GoToNextFile_err(std::string err_) {_err = err_;}
	};
};

#endif
