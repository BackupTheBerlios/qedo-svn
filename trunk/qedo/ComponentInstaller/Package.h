/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

#ifndef __PACKAGE_H__
#define __PACKAGE_H__


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
#include "PlatformBase.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)


namespace Qedo {

/**
 *
 */
class Package : public virtual PlatformBase
{

private:
	std::string zipfilename;

    void change_file_date(const char*,uLong,tm_unz);
	int extractCurrentfile (unzFile, std::string);

public:
	
	// Constructor of the class. The string argument is the name of the archive file.
	Package (std::string); 

	// Returns the pathname of the descriptor file within the archive.
	std::string getFileNameWithSuffix (std::string);

	// Extracts a file from the archive. The file is specified by the string argument which represents
    // the pathname of the file within the archive. The return value is 0 if no error.
	int extractFile (std::string, std::string);

    //
	int extractFilesWithSuffix (std::string, std::string);

    //
	std::string getName();
};

}

#endif