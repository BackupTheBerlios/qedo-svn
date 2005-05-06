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


#ifndef __InstalledUuid_HEAD
#define __InstalledUuid_HEAD

#include <string>
#include <vector>

//using namespace std;
class InstalledUuid 
{
  private:
	std::string uuid; // Id of the component implementation.

    std::string path; // Pathname of the installation repository of the component.

    int counter;

	// Number of installation requests of this component.

  public:
	   
    InstalledUuid (std::string); // Constructor

    bool operator == (InstalledUuid); // Definition of this operator. Two
                                      // InstalledUuid objects are equals
                                      // if their uuid attributes are equals.

    std::string get_uuid(); // Returns the uuid attribute.

    void set_path(std::string); // This procedure allows to set the path atribute.

    std::string get_path(); // Returns the path attribute.

    void incr(); // Increments the counter attribute of one unit.

    void decr(); // Decrements the counter attribute of one unit.

    int get_counter(); // Returns the counter attribute.

};

typedef std::vector <InstalledUuid> InstallRepositoryVector;
#endif
