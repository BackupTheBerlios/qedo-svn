//
// generated by Qedo
//

#include "DCI_Basics_NodeManagerImpl.h"


// BEGIN USER INSERT SECTION file
#include "../Utils/NamingUtils.h"
#include "Utility_class.h"
// END USER INSERT SECTION file


namespace DCI_Basics {


// BEGIN USER INSERT SECTION NodeManagerSessionImpl

	void NodeManagerSessionImpl::get_host_name ( std::string& name) const
	{
		 name = _hostname ;
	}

	void NodeManagerSessionImpl::invalid_name (CosNaming::NamingContext_var ns, CosNaming::Name name_, DCI_Basics::NodeManager_var obj_nm_, std::string& new_node_name)
	{
		std::cout << "Please enter the new host name:  ";
		std::cin >> new_node_name;

		char *out_ = _strlwr( _strdup( new_node_name.c_str() ) );
		name_[2].id = CORBA::string_dup (out_);
		name_[2].kind= CORBA::string_dup ("");

		bool already_bound = NamingUtil::bind_name(name_, obj_nm_ , ns , 2  );

		if (already_bound)
		{
			new_node_name = "";
			//return ;
		}
	};

	// If the string property_name is in the allowed_properties_vector, true
	// is returned and the index of the property in the vector is stored at the place
	// specified by the parameter ind ; else false is returned.
	CORBA::Boolean NodeManagerSessionImpl::get_index (const char *property_name, CORBA::ULong *ind)
	{
		CORBA::ULong length = get_number_of_properties();
		CORBA::Boolean successful = false;

		for (CORBA::ULong idx = 0; idx < length; idx++)
		{
			if (strcmp(CORBA::string_dup(get_name(idx)),property_name) == 0)
			{
				successful = true; // The property is found.
				*ind = idx; // The index of the property is stored.
				break;
			}
		}

		return(successful);
	}

	// This method returns the name of the property whose index in the properties_vector
	// is specified by the parameter ind.
	CosPropertyService::PropertyName NodeManagerSessionImpl::get_name (CORBA::ULong ind)
	{
		assert(ind < get_number_of_properties ()); // The index has to be correct.
		return(CORBA::string_dup((*properties_vector)[ind]->property_name)); // Returns the name.
	}

	// This method returns the value of the property whose index in the properties_vector
	// is specified by the parameter ind.
	CORBA::Any* NodeManagerSessionImpl::get_value (CORBA::ULong ind)
	{
		assert(ind < get_number_of_properties ()); // The index has to be correct.
		return(&((*properties_vector)[ind]->property_value)); // Returns the value.
	}

	// Returns true if the argument name is not "".
	CORBA::Boolean NodeManagerSessionImpl::is_property_name_valid (const char *name)
	{
		if (strcmp (name, "") == 0) // name is void.
			return(false); // The name is not valid.

		return(true);  // name is not void and is valid.
	}

	// If allowed_types_vector is void, returns true ; if not, returns true if the parameter
	// property_type is in the vector of types.
	CORBA::Boolean NodeManagerSessionImpl::is_property_type_allowed (CORBA::TypeCode_ptr property_type)
	{
		CORBA::ULong len = allowed_types_vector->size(); 

		if (len == 0) // allowed_types_vector is void.
			return TRUE; // All types are allowed.
		
		for (CORBA::ULong ind = 0; ind < len; ind++) // allowed_types_vector is not void
		{ 
			if (property_type->equal((*allowed_types_vector)[ind]))
				return(true); // The two types are identical.
		}

		return(false);
	}
	
	// If allowed_properties_vector is void, returns true ; if not, returns true if, in
	// the allowed_properties_vector, the property specified by the parameter name has the same
	// type as the type of the parameter value and if the mode of this property is undefined or
	// is the same as the parameter mode_type.
	CORBA::Boolean NodeManagerSessionImpl::is_property_allowed (const char *name, const CORBA::Any &value, const DCI_Basics::PropertyMode &mode_type)
	{
		CORBA::ULong len = this->allowed_properties_vector->size ();

		if (len == 0) // allowed_porperties_vector is void
			return(true); // All the properties are allowed.

		for (CORBA::ULong ind = 0; ind < len; ind++) // allowed_properties_vector is not void
		{ 
			if (strcmp (name, ((*allowed_properties_vector)[ind])->property_name) == 0)
			{
				CORBA::TypeCode_ptr type1 = value.type();
				CORBA::TypeCode_ptr type2 = (*allowed_properties_vector)[ind]->property_value.type();

				if (type1->equal (type2)) // The two types are identical.
				{ 
					if (((*allowed_properties_vector)[ind]->property_mode == mode_type) || // The two modes are identical.
						((*allowed_properties_vector)[ind]->property_mode == DCI_Basics::undefined)) // The allowed mode is undefined.
						return(true); // The property is allowed.
				}
			}
		}
		
		return(false); // The property is not allowed
	}

	// Returns true if the mode of the property specified by the index ind is normal_readonly
	// or fixed_readonly.
	CORBA::Boolean NodeManagerSessionImpl::is_property_readonly (CORBA::ULong ind)
	{
		assert(ind < get_number_of_properties ());

		if (((*properties_vector)[ind]->property_mode == DCI_Basics::normal_readonly) ||
			((*properties_vector)[ind]->property_mode == DCI_Basics::fixed_readonly))
			return(true);

		return(false);
	}

	// Returns true if the mode of the property specified by the index ind is fixed_normal
	// or fixed_readonly.
	CORBA::Boolean NodeManagerSessionImpl::is_property_fixed (CORBA::ULong ind)
	{
		assert(ind < get_number_of_properties ());

		if (((*properties_vector)[ind]->property_mode == DCI_Basics::fixed_normal) ||
			((*properties_vector)[ind]->property_mode == DCI_Basics::fixed_readonly))
			return(true);

		return(false);
	}

	// Defines a property specified by its name (property_name), its value (property_value)
	// and its mode (mode_type).
	// Exceptions:
	//	CosPropertyService::InvalidPropertyName
	//	CosPropertyService::UnsupportedTypeCode
	//	CosPropertyService::UnsupportedProperty
	//	CosPropertyService::ReadOnlyProperty
	//	CosPropertyService::ConflictingProperty
	void NodeManagerSessionImpl::definition (const char *property_name, const CORBA::Any &property_value, const DCI_Basics::PropertyMode &mode_type)
	{
		if (! is_property_name_valid (property_name))
			throw (CosPropertyService::InvalidPropertyName ()); // The name is not correct.

		CORBA::TypeCode_var prop_type = property_value.type();

		if (! is_property_type_allowed (prop_type))
			throw (CosPropertyService::UnsupportedTypeCode ()); // The type is not allowed.

		if (! is_property_allowed (property_name, property_value, mode_type))
			throw (CosPropertyService::UnsupportedProperty ()); // The property is not allowed.

		CORBA::ULong ind;
		CORBA::Boolean successful = get_index(property_name, &ind);

		if (successful) // The property already exists.
		{ 
			if (is_property_readonly (ind))
				throw (CosPropertyService::ReadOnlyProperty ()); // The property is read-only.

 			CORBA::TypeCode_var old_property_type = (*properties_vector)[ind]->property_value.type ();
			
			if (! (old_property_type->equal (prop_type)) )
				throw (CosPropertyService::ConflictingProperty ()); // The new type is not the same as the old one.
			
			(*properties_vector)[ind]->property_value = property_value; // The value is modified.
		}
		else // The property does not exist.
		{ 
			PropertyDef * new_property = new PropertyDef (); // Creation of a new property.
			new_property->property_name  = CORBA::string_dup (property_name);
			new_property->property_value = property_value;
			new_property->property_mode  = mode_type;
			properties_vector->push_back(new_property); // Insertion of th new property in the properties_vector.
		}
	}

	// Defines a set of properties.
	// Exceptions:
	// CosPropertyService::MultipleExceptions
	void NodeManagerSessionImpl::definitions (const CosPropertyService::Properties &nproperties, const DCI_Basics::PropertyMode &mode_type)
	{
		CORBA::ULong len = nproperties.length();
		assert(len > 0); 

		CosPropertyService::MultipleExceptions multexcpt;

		for (CORBA::ULong ind = 0; ind < len; ind++) // Definition of all the properties.
		{ 
			try
			{
				definition (nproperties[ind].property_name,nproperties[ind].property_value,mode_type);
			}
			catch (CosPropertyService::InvalidPropertyName)
			{
				CORBA::ULong multlen = multexcpt.exceptions.length ();
				multexcpt.exceptions.length(len + 1);
				multexcpt.exceptions[len].reason = CosPropertyService::invalid_property_name;
				multexcpt.exceptions[len].failing_property_name = nproperties[ind].property_name;
			}
			catch (CosPropertyService::ConflictingProperty)
			{
				CORBA::ULong multlen = multexcpt.exceptions.length ();
				multexcpt.exceptions.length(len + 1);
				multexcpt.exceptions[len].reason = CosPropertyService::conflicting_property;
				multexcpt.exceptions[len].failing_property_name = nproperties[ind].property_name;
			}
			catch (CosPropertyService::UnsupportedTypeCode)
			{
				CORBA::ULong multlen = multexcpt.exceptions.length ();
				multexcpt.exceptions.length(len + 1);
				multexcpt.exceptions[len].reason = CosPropertyService::unsupported_type_code;
				multexcpt.exceptions[len].failing_property_name = nproperties[ind].property_name;
			}
			catch (CosPropertyService::UnsupportedProperty)
			{
				CORBA::ULong multlen = multexcpt.exceptions.length ();
				multexcpt.exceptions.length(len + 1);
				multexcpt.exceptions[len].reason = CosPropertyService::unsupported_property;
				multexcpt.exceptions[len].failing_property_name = nproperties[ind].property_name;
			}
			catch (CosPropertyService::ReadOnlyProperty)
			{
				CORBA::ULong multlen = multexcpt.exceptions.length ();
				multexcpt.exceptions.length(len + 1);
				multexcpt.exceptions[len].reason = CosPropertyService::read_only_property;
				multexcpt.exceptions[len].failing_property_name = nproperties[ind].property_name;
			}
		}
		
		if (multexcpt.exceptions.length () != 0)
	//		throw (CosPropertyService::MultipleExceptions (multexcpt));
			throw (multexcpt);
	}

// END USER INSERT SECTION NodeManagerSessionImpl


NodeManagerSessionImpl::NodeManagerSessionImpl()
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::NodeManagerSessionImpl
	pr = new PropertiesRepository();
	
	properties_vector = pr->get_properties_vector();

// END USER INSERT SECTION NodeManagerSessionImpl::NodeManagerSessionImpl
}


NodeManagerSessionImpl::~NodeManagerSessionImpl()
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::~NodeManagerSessionImpl
// END USER INSERT SECTION NodeManagerSessionImpl::~NodeManagerSessionImpl
}


void
NodeManagerSessionImpl::set_context(::DCI_Basics::CCM_NodeManager_Context_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::DCI_Basics::CCM_NodeManager_Context::_duplicate(context);
}


void
NodeManagerSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::configuration_complete
	char buffer [30];
	int size_buff_ = sizeof(buffer);
	
	gethostname(buffer, size_buff_);
	//std::cout << buffer << "\n";
	char *out_ = _strlwr( _strdup( buffer ) );
	//std::cout << out_ << "\n";
	strcpy (_hostname, out_);

// END USER INSERT SECTION NodeManagerSessionImpl::configuration_complete
}


void
NodeManagerSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::remove
// END USER INSERT SECTION NodeManagerSessionImpl::remove
}


void
NodeManagerSessionImpl::install(const char* implUUID, const char* component_loc)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::install
// END USER INSERT SECTION NodeManagerSessionImpl::install
}


void
NodeManagerSessionImpl::replace(const char* implUUID, const char* component_loc)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::replace
// END USER INSERT SECTION NodeManagerSessionImpl::replace
}


void
NodeManagerSessionImpl::remove(const char* implUUID)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::remove
// END USER INSERT SECTION NodeManagerSessionImpl::remove
}


char*
NodeManagerSessionImpl::get_implementation(const char* implUUID)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_implementation
	std::string location;
	location = context_->get_connection_orig_component_installation()->get_implementation(implUUID) ;
	return CORBA::string_dup(location.c_str());

// END USER INSERT SECTION NodeManagerSessionImpl::get_implementation
}


void
NodeManagerSessionImpl::upload(const DCI_Basics::ComponentArchive& archive)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::upload
// END USER INSERT SECTION NodeManagerSessionImpl::upload
}


Components::Deployment::ComponentServer_ptr
NodeManagerSessionImpl::create_component_server(const Components::ConfigValues& config)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::create_component_server
	return Components::Deployment::ComponentServer::_duplicate (context_->get_connection_orig_server_activator()->create_component_server(config));

// END USER INSERT SECTION NodeManagerSessionImpl::create_component_server
}


void
NodeManagerSessionImpl::remove_component_server(Components::Deployment::ComponentServer_ptr server)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::remove_component_server
// END USER INSERT SECTION NodeManagerSessionImpl::remove_component_server
}


Components::Deployment::ComponentServers*
NodeManagerSessionImpl::get_component_servers()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_component_servers
return context_->get_connection_orig_server_activator()->get_component_servers();
// END USER INSERT SECTION NodeManagerSessionImpl::get_component_servers
}


void
NodeManagerSessionImpl::define_property(const char* property_name, const CORBA::Any& property_value)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::define_property
// END USER INSERT SECTION NodeManagerSessionImpl::define_property
}


void
NodeManagerSessionImpl::define_properties(const CosPropertyService::Properties& nproperties)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::define_properties
// END USER INSERT SECTION NodeManagerSessionImpl::define_properties
}


CORBA::ULong
NodeManagerSessionImpl::get_number_of_properties()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_number_of_properties
	return(properties_vector->size());
// END USER INSERT SECTION NodeManagerSessionImpl::get_number_of_properties
}


void
NodeManagerSessionImpl::get_all_property_names(CORBA::ULong how_many, CosPropertyService::PropertyNames_out property_names, CosPropertyService::PropertyNamesIterator_out rest)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_all_property_names
// END USER INSERT SECTION NodeManagerSessionImpl::get_all_property_names
}


CORBA::Any*
NodeManagerSessionImpl::get_property_value(const char* property_name)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_property_value
	if (! is_property_name_valid(property_name)) // The name is not valid.
		throw (CosPropertyService::InvalidPropertyName());

	CORBA::ULong ind;
	CORBA::Boolean successful = get_index(property_name,&ind);

	if (successful) // The property exists.
	{ 
		CORBA::Any *res = new CORBA::Any ((*properties_vector)[ind]->property_value);
		return(res);
	} 

	throw (CosPropertyService::PropertyNotFound ());

	return(NULL);
// END USER INSERT SECTION NodeManagerSessionImpl::get_property_value
}


CORBA::Boolean
NodeManagerSessionImpl::get_properties(const CosPropertyService::PropertyNames& property_names, CosPropertyService::Properties_out nproperties)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_properties
	return 0;
// END USER INSERT SECTION NodeManagerSessionImpl::get_properties
}


void
NodeManagerSessionImpl::get_all_properties(CORBA::ULong how_many, CosPropertyService::Properties_out nproperties, CosPropertyService::PropertiesIterator_out rest)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_all_properties
// END USER INSERT SECTION NodeManagerSessionImpl::get_all_properties
}


void
NodeManagerSessionImpl::delete_property(const char* property_name)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::delete_property
// END USER INSERT SECTION NodeManagerSessionImpl::delete_property
}


void
NodeManagerSessionImpl::delete_properties(const CosPropertyService::PropertyNames& property_names)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::delete_properties
// END USER INSERT SECTION NodeManagerSessionImpl::delete_properties
}


CORBA::Boolean
NodeManagerSessionImpl::delete_all_properties()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::delete_all_properties
	CORBA::ULong length = get_number_of_properties();
	CORBA::Boolean successful = true;

	for (CORBA::ULong ind = 0 ; ind < length ; ind++)
	{
		if (!is_property_fixed(ind))
		{
			PropertyDef * prop = (*properties_vector)[ind];
			properties_vector->erase(properties_vector->begin() + ind);
			delete(prop);
		}
		else
		{
			successful = false; // A property could not been deleted.
		}
	}

	return(successful);
// END USER INSERT SECTION NodeManagerSessionImpl::delete_all_properties
}


CORBA::Boolean
NodeManagerSessionImpl::is_property_defined(const char* property_name)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::is_property_defined
	if (! is_property_name_valid (property_name)) // The name is not valid.
		throw (CosPropertyService::InvalidPropertyName ());

	CORBA::ULong unused;

	return(get_index(property_name,&unused));
// END USER INSERT SECTION NodeManagerSessionImpl::is_property_defined
}


void
NodeManagerSessionImpl::define_property_with_mode(const char* property_name, const CORBA::Any& property_value, DCI_Basics::PropertyMode property_mode)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::define_property_with_mode
// END USER INSERT SECTION NodeManagerSessionImpl::define_property_with_mode
}


DCI_Basics::PropertyMode
NodeManagerSessionImpl::get_property_mode(const char* property_name)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_property_mode
	if (! is_property_name_valid(property_name))
		throw (CosPropertyService::InvalidPropertyName()); // The name is not valid.
	
	CORBA::ULong ind;
	CORBA::Boolean success = get_index(property_name, &ind);

	if (success == FALSE)
		throw (CosPropertyService::PropertyNotFound()); // The property is not defined.

	return((*properties_vector)[ind]->property_mode); 
// END USER INSERT SECTION NodeManagerSessionImpl::get_property_mode
}


void
NodeManagerSessionImpl::set_property_mode(const char* property_name, DCI_Basics::PropertyMode property_mode)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::set_property_mode
// END USER INSERT SECTION NodeManagerSessionImpl::set_property_mode
}


char*
NodeManagerSessionImpl::get_node_properties()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_node_properties
	std::string pathname = Utility_class::get_current_directory();
	pathname = pathname + "\\" +_hostname + "_properties.npd";
	std::string xmlstring_;
	Utility_class::copy_file_to_string (pathname, xmlstring_);

	return  CORBA::string_dup(xmlstring_.c_str());
// END USER INSERT SECTION NodeManagerSessionImpl::get_node_properties
}


Components::CCMHomes*
NodeManagerSessionImpl::get_all_homes()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION NodeManagerSessionImpl::get_all_homes
	std::string host_name_;
	get_host_name (host_name_);
	Components::CCMHomes* all_homes_ = new Components::CCMHomes;
	Components::Deployment::ComponentServers* comp_servs_ = context_->get_connection_orig_server_activator()->get_component_servers();
	CORBA::ULong length_cs = comp_servs_->length();

	if (length_cs != 0)
	{
		for (CORBA::ULong i = 0; i < length_cs; i++)
		{	
//			Components::Deployment::ComponentServer_var cont_ = Components::Deployment::ComponentServer::_narrow ( (comp_servs_[i]) );
			Components::Deployment::Containers* containers_ = (*comp_servs_)[i]->get_containers();
		//	cont_.
			CORBA::ULong length_c = containers_->length();
			
			if (length_c != 0)
			{
				for (CORBA::ULong j = 0; j < length_c; j++)
				{
					Components::CCMHomes* homes_ = (*containers_)[j]->get_homes();
					CORBA::ULong length_h = homes_->length();
					
					if (length_h != 0)
					{
						for (CORBA::ULong k = 0; k < length_h; k++)
						{
							CORBA::ULong idx = all_homes_->length();
							all_homes_->length(all_homes_->length() + 1);
							(*all_homes_)[idx] = (*homes_)[k];
						}
					}
					else
					{
						std::cerr << "One of containers doesn't have homes, it's empty ! \n";
					}	
				}
			}
			else
			{
				std::cerr << "One of component servers doesn't have containers, it's empty ! \n";
			}	
		}
	}
	else
	{
		std::cerr << "There are not running component servers on the  " << host_name_ << " node !\n";
		return 0;
	}

	CORBA::ULong length = all_homes_->length();

	if (length == 0)
	{
		std::cerr << "There are not running homes on the  " << host_name_ << " node !\n";
		return 0;
	}
	else
	{
		return all_homes_;
	}	
// END USER INSERT SECTION NodeManagerSessionImpl::get_all_homes
}


// BEGIN USER INSERT SECTION NodeManagerImpl
// END USER INSERT SECTION NodeManagerImpl


NodeManagerImpl::NodeManagerImpl()
    : component_(new NodeManagerSessionImpl())
{
// BEGIN USER INSERT SECTION NodeManagerImpl::NodeManagerImpl
// END USER INSERT SECTION NodeManagerImpl::NodeManagerImpl
}


NodeManagerImpl::~NodeManagerImpl()
{
    component_->_remove_ref();

// BEGIN USER INSERT SECTION NodeManagerImpl::~NodeManagerImpl
// END USER INSERT SECTION NodeManagerImpl::~NodeManagerImpl
}


::CORBA::Object*
NodeManagerImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "component_installation")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "server_activator")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "node_information")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
NodeManagerImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
NodeManagerImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION NodeManagerImpl::configuration_complete
// END USER INSERT SECTION NodeManagerImpl::configuration_complete
}


void
NodeManagerImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = dynamic_cast<::DCI_Basics::CCM_NodeManager_Context*>(context);
    
    component_->set_context(context_);
}


void
NodeManagerImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION NodeManagerImpl::ccm_activate
// END USER INSERT SECTION NodeManagerImpl::ccm_activate
}


void
NodeManagerImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION NodeManagerImpl::ccm_passivate
// END USER INSERT SECTION NodeManagerImpl::ccm_passivate
}


void
NodeManagerImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION NodeManagerImpl::ccm_remove
// END USER INSERT SECTION NodeManagerImpl::ccm_remove
}


// BEGIN USER INSERT SECTION NodeManagerHomeImpl
// END USER INSERT SECTION NodeManagerHomeImpl


NodeManagerHomeImpl::NodeManagerHomeImpl()
{
// BEGIN USER INSERT SECTION NodeManagerHomeImpl::NodeManagerHomeImpl
// END USER INSERT SECTION NodeManagerHomeImpl::NodeManagerHomeImpl
}


NodeManagerHomeImpl::~NodeManagerHomeImpl()
{
// BEGIN USER INSERT SECTION NodeManagerHomeImpl::~NodeManagerHomeImpl
// END USER INSERT SECTION NodeManagerHomeImpl::~NodeManagerHomeImpl
}


void
NodeManagerHomeImpl::set_context(Components::CCMContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::DCI_Basics::CCM_NodeManager_Context::_narrow(ctx);
}


::Components::EnterpriseComponent_ptr
NodeManagerHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION NodeManagerHomeImpl::create
// END USER INSERT SECTION NodeManagerHomeImpl::create
    return new NodeManagerImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_NodeManagerHomeE(void)
{
// BEGIN USER INSERT SECTION create_NodeManagerHome
// END USER INSERT SECTION create_NodeManagerHome

    return new ::DCI_Basics::NodeManagerHomeImpl();
}

