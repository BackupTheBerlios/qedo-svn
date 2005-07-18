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

#ifndef __Repository_HEAD
#define __Repository_HEAD

#include "InstalledUuid.h"


class Repository 
{
  private:

	  InstallRepositoryVector repository;

  public:
	Repository();
	virtual ~Repository();

	  int find(std::string); // Returns the position of the InstalledUuid object
                      // corresponding to the uuid specified by the string
                      // parameter.

    std::string get_uuid(int); // Returns the uuid of the InstalledUuid object
                          // whose place in the repository is defined by
                          // the integer parameter.

    void set_path(std::string,int); // Sets the pathname of the installation
                               // directory for the InstalledUuid object
                               // whose place in the repository is defined
                               // by the integer parameter.

    std::string get_path(int); // Returns the pathname of the installation
                          // directory for the InstalledUuid object whose
                          // place in the repository is defined by the
                          // integer parameter.

    bool find_path(std::string); // Returns true if there is an InstalledUuid object
                            // in the repository whose path is equal to the
                            // string parameter.

    void incr(int); // Increments the installation counter for the
                    // InstalledUuid object whose place in the repository
                    // is defined by the integer parameter.

    void decr(int); // Decrements the installation counter for the
                    // InstalledUuid object whose place in the repository
                    // is defined by the integer parameter.

    int get_counter(int); // Returns the value of the installation counter
                          // for the InstalledUuid object whose place in the
                          // repository is defined by the integer parameter.

    int insert(std::string); // This function adds an InstalledUuid object whose
                        // uuid attribute is specified by the string parameter.
                        // This object is added to the repository and the
                        // function returns its place.

    void erase(std::string); // This function removes the InstalledUuid object
                        // whose uuid attribute is equal to the string
                        // parameter.

};
#endif