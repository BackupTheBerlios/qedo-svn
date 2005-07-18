//**************************************************************
//
//**************************************************************

#ifndef PROPERTIESREPOSITORY
#define PROPERTIESREPOSITORY

#include <vector>
#include <CORBA.h>
#ifdef _WIN32
#include "NodeProperties.h"
#endif

//using namespace std;

// Structure of a property : name, value and mode
struct propertydef {
  char*	property_name;
  CORBA::Any	property_value;
};

typedef struct propertydef PropertyDef;

// Vector of properties
typedef std::vector<PropertyDef *>       PropertyDefs;

// Vector of types
typedef std::vector<CORBA::TypeCode_var> PropertyTypes;

// exception thrown if the PropertyRepository object can't be initialized
class PropertiesRepositoryInitializationException {};

class InvalidPropertyName {};
class UnsupportedProperty {};
class ConflictingProperty {};
class UnsupportedTypeCode {};

class PropertiesRepository {

private:
	// Vector of properties
	PropertyDefs  properties_vector;

	// Vector of allowed properties
	PropertyDefs  allowed_properties_vector;

	// Returns true if the parameter is not ""
	bool is_property_name_valid (const char *);

	// Vector of allowed types
	PropertyTypes allowed_types_vector;

	// Returns true if the parameter is in the vector of types
	bool is_property_type_allowed (CORBA::TypeCode_ptr);
	
	void definition (const char *property_name, const CORBA::Any &property_value)
	throw (InvalidPropertyName, UnsupportedProperty);

    bool is_property_allowed (const char *name, const CORBA::Any &value);
    
    void initialize_properties_();
    const char * NameOfProperty_(int i);
    void retrieve_property_(const char * name);

    #ifdef _WIN32
    NodeProperties* nodeprop_;
    #endif

    int prop_counter;

        //NodeInformation interface stuff
    // Indexes of the properties. These indexes are used in loops and
//  for the vector of refresh rates.
static const int OSNAME	 =	0;
static const int OSVERSION =	1;
static const int OSDIRECTORY =	2;
static const int OSVENDOR =	3;
static const int PROCNUMBER =	4;
static const int PROCTYPE =	5;
static const int PROCVENDOR  =	6;
static const int COMPCLASS      =	7;
static const int CPULOAD	=	8;
static const int AVCPULOAD =	9;
static const int NUMBERPROC =	10;
static const int INSTALLMEM =	11;
static const int FREEMEM =		12;
static const int AVFREEMEM =	13;
static const int COMPUTNAME =	14;
static const int IPADDRESS =	15;
static const int NETWORKTYP =	16;
static const int MAXBANDWID =	17;
static const int COMMLOAD =	18;
static const int PROTOCOLS =	19;
static const int INSTALLORB =	20;

static const int NUMBEROFPROPERTIES =	21;
static const int TIMEINTERVAL =	5000;


public:
	// Constructor without parameters
	PropertiesRepository();

	// Constructor with initialization
	PropertiesRepository(const PropertyDefs &);

	// Destructor
	~PropertiesRepository();

	// Returns the vector of properties
	PropertyDefs *  get_properties_vector();

	// Returns the vector of allowed properties
	PropertyDefs *  get_allowed_properties_vector();
	
	void define_property(const char *prop_name, const CORBA::Any &property_value);
    bool get_index (const char *property_name, int *ind);
    char* get_name (int ind);
    CORBA::Any* get_value (int ind);
    

};

#endif
