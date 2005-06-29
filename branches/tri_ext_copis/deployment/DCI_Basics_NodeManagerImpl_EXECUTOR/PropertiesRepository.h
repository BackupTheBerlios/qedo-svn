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


#ifndef PROPERTIESREPOSITORY
#define PROPERTIESREPOSITORY

#include <OB/CORBA.h>

#include "DCI_Basics_NodeManagerImpl_EQUIVALENT.h"
#include <vector>

//using namespace std;

// Structure of a property : name, value and mode
struct propertydef {
  CosPropertyService::PropertyName	property_name;
  CORBA::Any						property_value;
  DCI_Basics::PropertyMode			property_mode;  // sure, PropertyMode come from DCI_Manager
};

typedef struct propertydef PropertyDef;

// Vector of properties
typedef std::vector<PropertyDef *>       PropertyDefs;

// Vector of types
typedef std::vector<CORBA::TypeCode_var> PropertyTypes;

// exception thrown if the PropertyRepository object can't be initialized
class PropertiesRepositoryInitializationException {};


class PropertiesRepository {

private:
	// Vector of properties
	PropertyDefs  properties_vector;

	// Vector of allowed types
	PropertyTypes allowed_types_vector;

	// Vector of allowed properties
	PropertyDefs  allowed_properties_vector;

	// Returns true if the parameter is not ""
	bool is_property_name_valid (const char *);

	// Returns true if the parameter is in the vector of types
	bool is_property_type_allowed (CORBA::TypeCode_ptr);

public:
	// Constructor without parameters
	PropertiesRepository();

	// Constructor with initialization
	PropertiesRepository(const PropertyTypes &, const PropertyDefs &);

	// Destructor
	~PropertiesRepository();

	// Returns the vector of properties
	PropertyDefs *  get_properties_vector();

	// Returns the vector of allowed types
	PropertyTypes * get_allowed_types_vector();

	// Returns the vector of allowed properties
	PropertyDefs *  get_allowed_properties_vector();

};

#endif