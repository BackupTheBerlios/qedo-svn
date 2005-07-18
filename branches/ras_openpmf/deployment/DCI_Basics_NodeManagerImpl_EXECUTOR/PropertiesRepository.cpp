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

#include "PropertiesRepository.h"


// This private method returns true if the parameter name is correct, i.e. different
// from the void string.
bool PropertiesRepository::is_property_name_valid (const char *name) {
	if (strcmp (name, "") == 0)
		return FALSE;
	return(TRUE);
}


// This private method returns true if the parameter property_type belongs to the
// vector of allowed types.
bool PropertiesRepository::is_property_type_allowed (CORBA::TypeCode_ptr property_type) {
	CORBA::ULong len = allowed_types_vector.size (); 
	if (len == 0)
		return TRUE;
	for (CORBA::ULong ind = 0; ind < len; ind++) {
		if (property_type->equal(allowed_types_vector[ind]))
			return TRUE;
	}
	return FALSE;
}


// Constructor.
PropertiesRepository::PropertiesRepository() {
}


// Constructor with initialization of the allowed_types_vector and
// allowed_properties_vector attributes.
PropertiesRepository::PropertiesRepository(const PropertyTypes &atv,
										   const PropertyDefs &apv) {
	CORBA::ULong len = atv.size();

	for (CORBA::ULong ind = 0; ind < len; ind++)
		allowed_types_vector.push_back(atv[ind]);

	len = apv.size();

	for (ind = 0; ind < len; ind++) {
		if (! is_property_name_valid(apv[ind]->property_name)) {
			PropertiesRepositoryInitializationException exc;
			throw (exc);
		}

		if (! is_property_type_allowed(apv[ind]->property_value.type())) {
			PropertiesRepositoryInitializationException exc;
			throw (exc);
		}

		PropertyDef * new_property = new PropertyDef();
		new_property->property_name = CORBA::string_dup(apv[ind]->property_name);
		new_property->property_value = apv[ind]->property_value;
		new_property->property_mode  = apv[ind]->property_mode;

		allowed_properties_vector.push_back(new_property); 
	}
}


// Destructor.
PropertiesRepository::~PropertiesRepository() {
}


// Returns the address of the vector of defined properties.
PropertyDefs *  PropertiesRepository::get_properties_vector() {
  return(&properties_vector);
}


// Returns the address of the vector of allowed types.
PropertyTypes * PropertiesRepository::get_allowed_types_vector() {
  return(&allowed_types_vector);
}


// Returns the address of the vector of allowed properties.
PropertyDefs *  PropertiesRepository::get_allowed_properties_vector() {
  return(&allowed_properties_vector);
}