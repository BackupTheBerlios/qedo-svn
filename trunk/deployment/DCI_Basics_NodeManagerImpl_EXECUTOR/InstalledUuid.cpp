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

#include "InstalledUuid.h"


// Constructor

InstalledUuid::InstalledUuid(std::string id) 
{
  uuid = id;
  counter = 0;
  path = std::string("");
}


// Definition of this operator. Two InstalledUuid objects
// are equals if their uuid attributes are equals.

bool InstalledUuid::operator == (InstalledUuid id) 
{
  if (uuid == id.uuid)
    return(true);
  else
    return(false);
}


// Returns the uuid attribute.

std::string InstalledUuid::get_uuid() 
{
  return (uuid);
}


// This procedure allows to set the path atribute.

void InstalledUuid::set_path(std::string pth) 
{
  path = pth;
}


// Returns the path attribute.

std::string InstalledUuid::get_path() 
{
  return (path);
}


// Increments the counter attribute of one unit.

void InstalledUuid::incr() 
{
  counter++;
}


// Decrements the counter attribute of one unit.

void InstalledUuid::decr() 
{
  counter--;
}


// Returns the counter attribute.

int InstalledUuid::get_counter() 
{
  return(counter);
}
