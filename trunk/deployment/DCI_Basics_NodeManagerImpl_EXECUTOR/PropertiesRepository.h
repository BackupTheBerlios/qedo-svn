

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