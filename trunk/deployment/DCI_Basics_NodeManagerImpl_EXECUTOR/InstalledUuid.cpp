
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
