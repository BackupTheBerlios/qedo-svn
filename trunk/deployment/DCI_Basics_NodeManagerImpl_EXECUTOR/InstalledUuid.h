//**************************************************************
//
// T-Nova
// Deutsche Telekom Innovationsgesellschaft mbH
// Technologiezentrum Darmstadt
//
// Xavier Testa
//
// InstalledUuid.h
//
// Copyright (c) T-Nova Deutsche Telekom
// Innovationsgesellschaft mbH + 2000
//
// "This software is copyrighted. It may only be used for the 
// purposes stipulated in the license agreement, subject to 
// copyright regulations, in particular to §§ 69 a ff. of the 
// German Copyright Act. Any usage not within the scope of 
// Copyright Act without T-Nova's consent is inadmissible and 
// liable to prosecution.
//
// T-Nova has installed the copyright notice stipulated herein
// in the computer program. In the event of a user being
// authorized to duplicate the computer program, this
// copyright notice always is to be included. The copyright
// notice must neither be changed nor destroyed.
//
// All rights reserved. 
// This program is globally copyrighted."
//**************************************************************

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
