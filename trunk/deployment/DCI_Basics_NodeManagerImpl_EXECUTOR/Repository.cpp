
#include "Repository.h"

Repository::Repository()
{
}

Repository::~Repository()
{
}


// Returns the position of the InstalledUuid object corresponding
// to the uuid specified by the string parameter.

int Repository::find(std::string id) 
{
  int i=0;
  int imax=repository.size(); // Number of InstalledUuid objects in the repository.
  bool found=false; // If the InstalledUuid object (corresponding to the string id) is found.
  InstalledUuid uuid(id);

  while ((i < imax) && (!found)) 
  {
    if (uuid == repository[i])
      found = true; // The right InstalledUuid object has been found.
    i++;
  }
  if (found)
    return(--i); // The position of the right InstalledUuid object.
  else
    return(-1); // InstalledUuid object not found.
}


// Returns the uuid of the InstalledUuid object whose place in
// the repository is defined by the integer parameter.

std::string Repository::get_uuid(int pos) 
{
  return(repository[pos].get_uuid());
}


// Sets the pathname of the installation directory for the
// InstalledUuid object whose place in the repository is defined
// by the integer parameter.

void Repository::set_path(std::string pth,int pos) 
{
  repository[pos].set_path(pth);
}


// Returns the pathname of the installation directory for the
// InstalledUuid object whose place in the repository is defined
// by the integer parameter.

std::string Repository::get_path(int pos) 
{
  return(repository[pos].get_path());
}


// Returns true if there is an InstalledUuid object in the
// repository whose path is equal to the string parameter.

bool Repository::find_path(std::string pth) 
{
  int i=0;
  int imax=repository.size(); // Number of InstalledUuid objects in the repository.
  bool found=false; // If the pathname is found.

  while ((i < imax) && (!found)) {
    if (repository[i].get_path() == pth)
      found = true; // A pathname corresponding to pth has been found.
    i++;
  }
  return(found);
}

// Increments the installation counter for the InstalledUuid object
// whose place in the repository is defined by the integer parameter.

void Repository::incr(int pos) 
{
  repository[pos].incr();
}


// Decrements the installation counter for the InstalledUuid object
// whose place in the repository is defined by the integer parameter.

void Repository::decr(int pos) 
{
  repository[pos].decr();
}


// Returns the value of the installation counter for the InstalledUuid
// object whose place in the repository is defined by the integer parameter.

int Repository::get_counter(int pos) 
{
  return(repository[pos].get_counter());
}


// This function adds an InstalledUuid object whose uuid attribute is
// specified by the string parameter. This object is added to the
// repository and the function returns its place.

int Repository::insert(std::string id) 
{
  int position = find(id); // Position of the InstalledUuid object corresponding to the uuid specified by the string id.
  if (position == -1) 
  { // Not found.
    InstalledUuid uuid(id);
    repository.push_back(uuid); // The new object is inserted at the end of the repository.
    return(repository.end() - repository.begin() - 1); // Returns the position of the last object.
  } 
  else
    return(-1);
}


// This function removes the InstalledUuid object whose
// uuid attribute is equal to the string parameter.

void Repository::erase(std::string id) 
{
  int position = find(id); // Position of the InstalledUuid object corresponding to the uuid specified by the string id.
  if (position != -1) { // Found.
	  std::vector<InstalledUuid>::iterator il = repository.begin(); // Creation of an interator.
    for(int i=0 ; i < position ; i++)
      il++;
    repository.erase(il); // Object found and removed from the repository.
  }
}
