//**************************************************************
//
//**************************************************************

#include "PropertiesRepository.h"


// This private method returns true if the parameter name is correct, i.e. different
// from the void string.
bool PropertiesRepository::is_property_name_valid (const char *name) {
	if (strcmp (name, "") == 0)
		return false;
	return(true);
}


// Constructor.
PropertiesRepository::PropertiesRepository():
prop_counter(0)
{
   nodeprop_ = new NodeProperties();
   initialize_properties_();
}


// Constructor with initialization of the allowed_types_vector and
// allowed_properties_vector attributes.
PropertiesRepository::PropertiesRepository(const PropertyDefs &apv) {
	int len = apv.size();

	for (int ind = 0; ind < len; ind++) {
		if (! is_property_name_valid(apv[ind]->property_name)) {
			PropertiesRepositoryInitializationException exc;
			throw (exc);
		}

		PropertyDef * new_property = new PropertyDef();
		new_property->property_name = CORBA::string_dup(apv[ind]->property_name);
		new_property->property_value = apv[ind]->property_value;

		if (! is_property_type_allowed(apv[ind]->property_value.type())) {
			PropertiesRepositoryInitializationException exc;
			throw (exc);
		}

		allowed_properties_vector.push_back(new_property); 
	}
}

	void PropertiesRepository::define_property(const char *prop_name, const CORBA::Any &property_value)
    {
        definition(prop_name,property_value);
    }
        

void PropertiesRepository::definition (const char *property_name, const CORBA::Any &property_value) {
	if (! is_property_name_valid (property_name))
		throw (InvalidPropertyName ()); // The name is not correct.

	CORBA::TypeCode_var prop_type = property_value.type();

	if (! is_property_allowed (property_name, property_value))
		throw (UnsupportedProperty ()); // The property is not allowed.

	int ind;
	bool successful = get_index(property_name, &ind);

	if (successful) { // The property already exists.
 		CORBA::TypeCode_var old_property_type = properties_vector[ind]-> property_value.type ();
		if (! (old_property_type->equal (prop_type)) )
			throw (ConflictingProperty ()); // The new type is not the same as the old one.
		properties_vector[ind]->property_value = property_value; // The value is modified.
	} else { // The property does not exist.
		PropertyDef * new_property = new PropertyDef (); // Creation of a new property.
		new_property->property_name  = strdup (property_name);
		new_property->property_value = property_value;
		properties_vector.push_back(new_property); // Insertion of th new property in the properties_vector.
	}
}


bool PropertiesRepository::is_property_allowed (const char *name, const CORBA::Any &value) {
	int len = allowed_properties_vector.size ();
	if (len == 0) // allowed_porperties_vector is void
		return(true); // All the properties are allowed.

	for (int ind = 0; ind < len; ind++) { // allowed_properties_vector is not void
		if (strcmp (name, (allowed_properties_vector[ind])->property_name) == 0) {
			CORBA::TypeCode_ptr type1 = value.type();
			CORBA::TypeCode_ptr type2 = allowed_properties_vector[ind]->property_value.type();
			if (type1->equal (type2)) { // The two types are identical.
					return(true); // The property is allowed.
			}
		}
	}
	return(false); // The property is not allowed
}


// This private method returns true if the parameter property_type belongs to the
// vector of allowed types.
bool PropertiesRepository::is_property_type_allowed (CORBA::TypeCode_ptr property_type) {
	int len = allowed_types_vector.size (); 
	if (len == 0)
		return true;
	for (int ind = 0; ind < len; ind++) {
		if (property_type->equal(allowed_types_vector[ind]))
			return true;
	}
	return false;
}

// Destructor.
PropertiesRepository::~PropertiesRepository() {
}


// Returns the address of the vector of defined properties.
PropertyDefs *  PropertiesRepository::get_properties_vector() {
  return(&properties_vector);
}


// Returns the address of the vector of allowed properties.
PropertyDefs *  PropertiesRepository::get_allowed_properties_vector() {
  return(&allowed_properties_vector);
}

bool PropertiesRepository::get_index (const char *property_name, int *ind) {
	int length = properties_vector.size();
	bool successful = false;
	for (int idx = 0 ; idx < length ; idx++) {
		if (strcmp(strdup(get_name(idx)),property_name) == 0) {
			successful = true; // The property is found.
			*ind = idx; // The index of the property is stored.
			break;
		}
	}
	return(successful);
}

// This method returns the name of the property whose index in the properties_vector
// is specified by the parameter ind.
char* PropertiesRepository::get_name (int ind) {
	assert (ind < properties_vector.size ()); // The index has to be correct.
	return(strdup(properties_vector[ind]->property_name)); // Returns the name.
}

// This method returns the value of the property whose index in the properties_vector
// is specified by the parameter ind.
CORBA::Any* PropertiesRepository::get_value (int ind) {
	assert (ind < properties_vector.size ()); // The index has to be correct.
	retrieve_property_(NameOfProperty_(ind));
	return(&(properties_vector[ind]->property_value)); // Returns the value.
}

// Interactions with NodeInformation Interface below

void PropertiesRepository::initialize_properties_(){
	for (int i = 0 ; i < NUMBEROFPROPERTIES ; i++) {
		char* name = strdup(NameOfProperty_(i)); // Name of the property.
		retrieve_property_(name);
	}
}

void PropertiesRepository::retrieve_property_(const char * name) {

    int i;
    bool found = this -> get_index(name, &i);
    if(!found){
        //std::cerr << "PropertiesRepository::retrieve_property: Adding new Property " << name << std::endl;
        i = prop_counter;
        prop_counter++;
    }
		try {
			CORBA::Any a;
			switch (i) {
				case OSNAME :
				{
					char *ret = nodeprop_ -> get_OSName();
					a <<= ret;
					break;
				}
				case OSVERSION :
				{
					char *ret = nodeprop_ -> get_OSVersion();
					a <<= ret;
					break;
				}
				case OSDIRECTORY :
				{
					char *ret = nodeprop_ -> get_OSDirectory();
					a <<= ret;
					break;
				}
				case OSVENDOR :
				{
					char *ret = nodeprop_ -> get_OSVendor();
					a <<= ret;
					break;
				}
				case PROCNUMBER :
				{
					CORBA::Long ret = nodeprop_ -> get_ProcessorsNumber();
					a <<= ret;
					break;
				}
				case PROCTYPE :
				{
					char *ret = nodeprop_ -> get_ProcessorsType();
					a <<= ret;
					break;
				}
				case PROCVENDOR :
				{
					char *ret = nodeprop_ -> get_ProcessorsVendor();
					a <<= ret;
					break;
				}
				case COMPCLASS :
				{
					char *ret = nodeprop_ -> get_ProcessorsCompatibilityClass();
					a <<= ret;
					break;
				}
				case CPULOAD :
				{
					CORBA::Long ret = nodeprop_ -> get_CPULoad();
					a <<= ret;
					break;
				}
				case AVCPULOAD :
				{
					CORBA::Long ret = nodeprop_ -> get_AverageCPULoad(TIMEINTERVAL);
					a <<= ret;
					break;
				}
				case NUMBERPROC :
				{
					CORBA::Long ret = nodeprop_ -> get_NumberOfProcesses();
					a <<= ret;
					break;
				}
				case INSTALLMEM :
				{
					CORBA::Long ret = nodeprop_ -> get_InstalledMemory();
					a <<= ret;
					break;
				}
				case FREEMEM :
				{
					CORBA::Long ret = nodeprop_ -> get_FreeMemory();
					a <<= ret;
					break;
				}
				case AVFREEMEM :
				{
					CORBA::Long ret = nodeprop_ -> get_AverageFreeMemory(TIMEINTERVAL);
					a <<= ret;
					break;
				}
				case COMPUTNAME :
				{
					char *ret = nodeprop_ -> get_ComputerName();
					a <<= ret;
					break;
				}
				case IPADDRESS :
				{
					char *ret = nodeprop_ -> get_IPAddresses();
					a <<= ret;
					break;
				}
				case NETWORKTYP :
				{
					char *ret = nodeprop_ -> get_NetworkType();
					a <<= ret;
					break;
				}
				case MAXBANDWID :
				{
					char *ret = nodeprop_ -> get_MaxBandwidth();
					a <<= ret;
					break;
				}
				case COMMLOAD :
				{
					char *ret = nodeprop_ -> get_CommunicationLoad();
					a <<= ret;
					break;
				}
				case PROTOCOLS :
				{
					char *ret = nodeprop_ -> get_Protocols();
					a <<= ret;
					break;
				}
				case INSTALLORB :
				{
					char *ret = nodeprop_ -> get_InstalledOrbs();
					a <<= ret;
					break;
				}
			}
			this -> define_property(name,a);
		} catch (...) {
			//std::cout<< "???\n"; // Can't be reached
		}
}

// Returns the name of the property corresponding to the number. This name is used for the
// call to methods of the Monitoring interface (e.g. define_property). For the list of the
// numbers, cf. the list of #define at the beginning of the Mediator.h file.
const char * PropertiesRepository::NameOfProperty_(int i) {
	switch (i) {
		case OSNAME :
			return("OSName");
		case OSVERSION :
			return("OSVersion");
		case OSDIRECTORY :
			return("OSDirectory");
		case OSVENDOR :
			return("OSVendor");
		case PROCNUMBER :
			return("ProcessorsNumber");
		case PROCTYPE :
			return("ProcessorsType");
		case PROCVENDOR :
			return("ProcessorsVendor");
		case COMPCLASS :
			return("ProcessorsCompatibilityClass");
		case CPULOAD :
			return("CPULoad");
		case AVCPULOAD :
			return("AverageCPULoad");
		case NUMBERPROC :
			return("NumberOfProcesses");
		case INSTALLMEM :
			return("InstalledMemory");
		case FREEMEM :
			return("FreeMemory");
		case AVFREEMEM :
			return("AverageFreeMemory");
		case COMPUTNAME :
			return("ComputerName");
		case IPADDRESS :
			return("IPAddresses");
		case NETWORKTYP :
			return("NetworkType");
		case MAXBANDWID :
			return("MaxBandwidth");
		case COMMLOAD :
			return("CommunicationLoad");
		case PROTOCOLS :
			return("Protocols");
		case INSTALLORB :
			return("InstalledOrbs");
		default :
			return("Undefined");
	}
}



