//**************************************************************
//
// T-Nova
// Deutsche Telekom Innovationsgesellschaft mbH
// Technologiezentrum Darmstadt
//
// Xavier Testa
//
// Repository.h
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