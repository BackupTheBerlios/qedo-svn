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
 * @addtogroup ComponentInstaller
 * @{
 */


/**
 * represents a package
 */
class Package : public virtual PlatformBase
{

private:
	/** the file name */
	std::string zipfilename;

	/**
	 * bla
	 */
    void change_file_date(const char*,uLong,tm_unz);

	/**
	 * bla
	 */
	int extractCurrentfile (unzFile, std::string);

public:
	
	/**
	 * constructor
	 * \param file The name of the archive file.
	 */
	Package (std::string file); 

	/**
	 * returns the pathname of the descriptor file within the archive
	 * If the format of the archive is not correct or if there is no .csd file or if there are more
	 * than one .csd file, the string "" is returned.
	 * \param suffix
	 */
	std::string getFileNameWithSuffix (std::string suffix);

	/**
	 * extracts a file from the archive
	 * The file is specified by the string argument which represents
     * the pathname of the file within the archive. The return value is 0 if no error.
	 * \param filename_to_extract
	 * \param target
	 */
	int extractFile (std::string filename_to_extract, std::string target);

    /**
	 * extracts files
	 * \param suffix
	 * \param destination
	 */
	int extractFilesWithSuffix (std::string suffix, std::string destination);

    /**
	 * provides the package name
	 * \return The file name.
	 */
	std::string getName();
};

/** @} */

}

#endif

