//
// generated by Qedo
//

#include "CCMGenerator_CCDBackEnd_compo.h"


// BEGIN USER INSERT SECTION file
// include alle *.h files

#include <iostream>
#include "Exceptions.h"
#include "HelpFunctions.h"
 
// END USER INSERT SECTION file


namespace CCMGenerator {


// BEGIN USER INSERT SECTION CCDBackendSessionImpl

void CCDBackendSessionImpl::connect_the_whole_repository ()
{
	
	M2C::MOFRepository::RepositoryRoot_var repository_root = 
		M2C::MOFRepository::RepositoryRoot::_narrow ( _root );

	if( CORBA::is_nil ( repository_root ) )
	{
		std::cerr << "I got a nil reference for the repository root reference" << std::endl;
		exit (1);
	}
	::Reflective::RefPackageSet* package_set = repository_root -> get_root_packages();
	_repconnector.set_package_set (package_set); 
	_repconnector.connectRepository();
	_base_idl_pkg_ref =		_repconnector._base_idl_pkg_ref;
	_cif_ref  =				_repconnector._cif_ref;
	_component_idl_ref =	_repconnector._component_idl_ref ;
	_deployment_ref =		_repconnector._deployment_ref;
}

void CCDBackendSessionImpl::begin ( ostream& out )
{
	out << "<?xml version=\"1.0\" ?>";
	HelpFunctions::new_line ( out, 0 );
	out << "<!DOCTYPE corbacomponent PUBLIC \"-//OMG//DTD CORBA Component Descriptor\" \"corbacomponent.dtd\">";
	HelpFunctions::new_line ( out, 0 );
}

/*std::string CCDBackendSessionImpl::extract_component_category (std::string str)
{
	std::string category = "";
	static const basic_string <char>::size_type npos = -1;
	//index_ = str.find ( "Session" );
	if ( str.find ( "Session" ) != npos )
      return category = "session";
	if ( str.find ( "Entity" )!= npos )
		return category = "entity";
	if ( str.find ( "Process" )!= npos )
		return category = "process";
	if ( str.find ( "Service" )!= npos )
		return category = "service";
	return category;
}*/
std::string CCDBackendSessionImpl::extract_component_category ( MDE::CIF::ComponentImplDef_ptr comp_impl )
{
	std::string category = "";

	if ( comp_impl->category() == MDE::CIF::SESSION )
      return category = "session";
	if ( comp_impl->category() == MDE::CIF::ENTITY )
		return category = "entity";
	if ( comp_impl->category() == MDE::CIF::PROCESS )
		return category = "process";
	if ( comp_impl->category() == MDE::CIF::SERVICE )
		return category = "service";
	return category;
}

void CCDBackendSessionImpl::_generte_componentkind_element( MDE::ComponentIDL::ComponentDef_ptr component_, MDE::CIF::ComponentImplDef_ptr comp_impl, ostream& out, unsigned long & indent_level )
{
	cout << "generte_componentkind_element:" << component_->identifier() << endl;
	MDE::CIF::ComponentImplDefSet_var segs_ = component_->segs();
	MDE::CIF::ComponentImplDef_var selected_comp_;
	for (CORBA::ULong i = 0; i < segs_->length (); i++)
	{
		MDE::ComponentIDL::ComponentDef_var temp_ = segs_[i]->component_end();
		if ( ! strcmp (component_->repository_id(), temp_->repository_id() ) )
		{
			selected_comp_ = segs_[i];
		}
	}
	if( CORBA::is_nil ( selected_comp_ ) )
	{
		std::cerr << "generte_componentkind_element: selected component doesn't have a ComponentImpl " << std::endl;
		exit (1);
	}
	std::string category_ = extract_component_category ( comp_impl );
	out << "<componentkind>";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<" << category_ << ">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<servant lifetime = \"container\"/>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</" << category_ << ">";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</componentkind>";
	HelpFunctions::new_line ( out, indent_level );
	
}
void CCDBackendSessionImpl::_generate_homefeatures_element 
( MDE::ComponentIDL::HomeDef_ptr home, std::string id, std::string rep_id, ostream& out, unsigned long & indent_level )
{
	out << "<homefeatures name = \"" << id << "\" repid=\"" << HelpFunctions::convert_uml_string_in_path(rep_id) << "\">";
	MDE::BaseIDL::InterfaceDefSet_var set_ = home->base();
	
	CORBA::ULong l_ = set_->length ();
	if (l_ == 1)
	{				
		MDE::ComponentIDL::HomeDef_var inherit_ = MDE::ComponentIDL::HomeDef::_narrow ( set_[set_->length ()-1] );
		if( CORBA::is_nil ( inherit_ ) ) 
			{
				throw NilObjectRef ( "Narrow problem: Base Component for Component!" );
			}
		HelpFunctions::inc_indent_level ( indent_level );
		HelpFunctions::new_line ( out, indent_level );
		out << "<inheritshome repid=" << HelpFunctions::convert_uml_string_in_path( inherit_->repository_id() ) << "\">" ;
		HelpFunctions::dec_indent_level ( indent_level );
	}
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<operationpolicies>" ;
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<operation name=\"*\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<transaction use=\"never\"/>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</operation>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</operationpolicies>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</homefeatures>";
	HelpFunctions::new_line ( out, indent_level );
}
void CCDBackendSessionImpl::_generate_support_interface( MDE::BaseIDL::InterfaceDef_ptr s_itf, ostream& out, unsigned long & indent_level )
{
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<operationpolicies>" ;
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<operation name=\"*\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<transaction use=\"never\"/>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</operation>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</operationpolicies>";
	
}
void CCDBackendSessionImpl::_generate_component_facet 
( MDE::ComponentIDL::ProvidesDefSet_var facets, ostream& out, unsigned long & indent_level )
{
	CORBA::ULong how_much_ = facets->length ();
	for (CORBA::ULong i = 0; i < facets->length (); i++)
		{
			out << "<provides";
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			std::string str_ = facets[i]->identifier();
			str_.erase(str_.find("_provides"), 9 );
			out << "providesname=\"" << str_ << "\"";
			HelpFunctions::new_line ( out, indent_level );
			MDE::BaseIDL::InterfaceDef_var provides_itf_ = facets[i]->provides_itf ();
			out << "repid=\"" << HelpFunctions::convert_uml_string_in_path( provides_itf_->repository_id() ) << "\""; 
			HelpFunctions::new_line ( out, indent_level );
			//HelpFunctions::new_line ( out, indent_level );
			// operation
			bool b_ = false;
			int op_counter_ = 0;
			MDE::BaseIDL::ContainedSet_var nested_ = provides_itf_->contents ();
			for ( CORBA::ULong j = 0; j < nested_->length (); j++ )
			{
				MDE::BaseIDL::OperationDef_var op_ = MDE::BaseIDL::OperationDef::_narrow ( (*nested_)[j] );

				if ( !CORBA::is_nil ( op_ ) )
				{
					if (b_ == false)
					{
						out << "facettag=\" \">";
						HelpFunctions::new_line ( out, indent_level );
						out << "<operationpolicies>";
						HelpFunctions::inc_indent_level ( indent_level );
						HelpFunctions::new_line ( out, indent_level );
						b_ = true;
					}
					
					out << "<operation name=\"" << op_->identifier() << "\">";
					HelpFunctions::new_line ( out, indent_level );
					out << "</operation>";
					op_counter_ = op_counter_++;
				}

			}
			if (!op_counter_)
			{
				out << "facettag=\" \"/>";
				HelpFunctions::dec_indent_level ( indent_level );
				HelpFunctions::new_line ( out, indent_level );
			}
			else
			{
				HelpFunctions::dec_indent_level ( indent_level );
				HelpFunctions::new_line ( out, indent_level );
				out << "</operationpolicies>";
				HelpFunctions::dec_indent_level ( indent_level );
				HelpFunctions::new_line ( out, indent_level );
				out << "</provides>";
				HelpFunctions::new_line ( out, indent_level );
			}
			
		}
}

void CCDBackendSessionImpl::_generate_component_receptacle 
( MDE::ComponentIDL::UsesDefSet_var receptacles, ostream& out, unsigned long & indent_level )
{
	for (CORBA::ULong i = 0; i < receptacles->length (); i++)
		{
			out << "<uses";
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			std::string str_ = receptacles[i]->identifier();
			str_.erase(str_.find("_uses"), 5 );
			out << "usesname=\"" << str_ << "\"";
			HelpFunctions::new_line ( out, indent_level );
			MDE::BaseIDL::InterfaceDef_var uses_itf_ = receptacles[i]->uses_itf ();
			out << "repid=\"" << HelpFunctions::convert_uml_string_in_path( uses_itf_->repository_id() ) << "\"/>"; 
			HelpFunctions::dec_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
		}
}
void CCDBackendSessionImpl::_generate_component_consumes 
( MDE::ComponentIDL::ConsumesDefSet_var consumes, ostream& out, unsigned long & indent_level )
{
	for (CORBA::ULong i = 0; i < consumes->length (); i++)
		{
			out << "<consumes";
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			std::string str_ = consumes[i]->identifier();
			str_.erase(str_.find("_consumes"), 9 );
			out << "consumesname=\"" << str_ << "\"";
			HelpFunctions::new_line ( out, indent_level );
			MDE::ComponentIDL::EventDef_var consumes_type_ = consumes[i]->type ();
			out << "eventtype=\"" << consumes_type_->identifier() << "\">";
			HelpFunctions::new_line ( out, indent_level );
			out << "<eventpolicy policy=\"normal\"/>";
			HelpFunctions::dec_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			out << "</consumes>";
			HelpFunctions::new_line ( out, indent_level );
		}
}

void CCDBackendSessionImpl::_generate_component_emits 
( MDE::ComponentIDL::EmitsDefSet_var emits, ostream& out, unsigned long & indent_level )
{
	for (CORBA::ULong i = 0; i < emits->length (); i++)
		{
			out << "<emits";
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			std::string str_ = emits[i]->identifier();
			str_.erase(str_.find("_emits"), 6 );
			out << "emitsname=\"" << str_ << "\"";
			HelpFunctions::new_line ( out, indent_level );
			MDE::ComponentIDL::EventDef_var emits_type_ = emits[i]->type ();
			out << "eventtype=\"" << emits_type_->identifier() << "\">";
			HelpFunctions::new_line ( out, indent_level );
			out << "<eventpolicy policy=\"normal\"/>";
			HelpFunctions::dec_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			out << "</emits>";
			HelpFunctions::new_line ( out, indent_level );
		}
}
void CCDBackendSessionImpl::_generate_component_publishes 
( MDE::ComponentIDL::PublishesDefSet_var publishes, ostream& out, unsigned long & indent_level )
{
	for (CORBA::ULong i = 0; i < publishes->length (); i++)
		{
			out << "<publishes";
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			std::string str_ = publishes[i]->identifier();
			str_.erase(str_.find("_publishes"), 10 );
			out << "publishesname=\"" << str_ << "\"";
			HelpFunctions::new_line ( out, indent_level );
			MDE::ComponentIDL::EventDef_var publishes_type_ = publishes[i]->type ();
			out << "eventtype=\"" << publishes_type_->identifier() << "\">";
			HelpFunctions::new_line ( out, indent_level );
			out << "<eventpolicy policy=\"normal\"/>";
			HelpFunctions::dec_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			out << "</publishes>";
			HelpFunctions::new_line ( out, indent_level );
		}
}

void CCDBackendSessionImpl::_generate_ports_element 
(MDE::ComponentIDL::ComponentDef_ptr component_, ostream& out, unsigned long & indent_level )
{
	bool b_ = false;
	MDE::ComponentIDL::ProvidesDefSet_var facets_ = component_->facet();
	MDE::ComponentIDL::UsesDefSet_var receptacle_ = component_->receptacle ();
	MDE::ComponentIDL::ConsumesDefSet_var consumes_ = component_->consumess();
	MDE::ComponentIDL::EmitsDefSet_var emits_ = component_->emitss();
	MDE::ComponentIDL::PublishesDefSet_var publishes_ = component_->publishess();
	/*if ( (facets_->length () > 0) || (receptacle_->length () > 0) || (publishes_->length () > 0) || (consumes_->length () > 0) || (emits_->length () > 0) )
		b_ = true;
	if ( b_ == false )
		return;*/
	out << "<ports>";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	if (facets_->length () > 0)
		this->_generate_component_facet (facets_, out, indent_level );
	if (receptacle_->length () > 0)
		this->_generate_component_receptacle (receptacle_, out, indent_level );
	if (consumes_->length () > 0)
		this->_generate_component_consumes (consumes_, out, indent_level );
	if (emits_->length () > 0)
		this->_generate_component_emits (emits_, out, indent_level );
	if (publishes_->length () > 0)
		this->_generate_component_publishes (publishes_, out, indent_level );

	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</ports>";		
}
void CCDBackendSessionImpl::add_generated_interface ( MDE::BaseIDL::InterfaceDef_var itf )
{
	//MDE::BaseIDL::InterfaceDefSet* temp = new MDE::BaseIDL::InterfaceDefSet;
	_all_generated_itfs->length ( _all_generated_itfs->length () + 1);
	_all_generated_itfs[ _all_generated_itfs->length () - 1 ] = itf;
}
bool CCDBackendSessionImpl::is_contaned_generated_interface(  MDE::BaseIDL::InterfaceDef_ptr itf )
{
	std::string str2 = itf->repository_id();
	for ( CORBA::ULong i = 0; i < _all_generated_itfs->length (); i++)
	{
		MDE::BaseIDL::InterfaceDef_var itf_temp = _all_generated_itfs[i];
		if ( ! strcmp (_all_generated_itfs[i]->repository_id(), str2.c_str() ) )
			return true;
	}
	return false;
}
void CCDBackendSessionImpl::_generate_all_interfaces 
	( MDE::ComponentIDL::ComponentDef_ptr component_, ostream& out, unsigned long & indent_level )
{
	//HelpFunctions::inc_indent_level ( indent_level );
	CORBA::ULong i;
	bool provides_ = false;
	// generate supported interfaces
	if ( _supported_itfs->length () > 0 )
	{
		for (i = 0; i < _supported_itfs->length (); i++)
		{
			if (! is_contaned_generated_interface (_supported_itfs[i]) )
			{
				out << "<interface name=\"" << _supported_itfs[i]->identifier() << "\" repid=\""<< HelpFunctions::convert_uml_string_in_path( _supported_itfs[i]->repository_id() ) << "\" />";
				this->add_generated_interface( _supported_itfs [i]);
				HelpFunctions::new_line ( out, indent_level );
			}
		}
	}
	MDE::ComponentIDL::ProvidesDefSet_var facets_ = component_->facet();
	MDE::ComponentIDL::UsesDefSet_var receptacle_ = component_->receptacle ();
	// generate provided interfaces
	if ( facets_->length () > 0)
	{
		provides_ = true;
		for (i = 0; i < facets_->length (); i++)
		{
			if (! is_contaned_generated_interface (facets_[i]->provides_itf () ) )
			{
				//MDE::BaseIDL::InterfaceDef_var provides_itf_ = facets_[i]->provides_itf ();
				out << "<interface name=\"" << facets_[i]->provides_itf ()->identifier() << "\" repid=\""<< HelpFunctions::convert_uml_string_in_path( facets_[i]->provides_itf ()->repository_id() );  
				this->add_generated_interface( facets_[i]->provides_itf () );
				MDE::BaseIDL::InterfaceDefSet_var bases_ = facets_[i]->provides_itf ()->base();
				if ( bases_->length () > 0 )
				{
					out << "\">";
					HelpFunctions::inc_indent_level ( indent_level );
					_bases_itfs = bases_;
					for (CORBA::ULong j = 0; j < bases_->length (); j++)
					{
						HelpFunctions::new_line ( out, indent_level );
						out << "<inheritsinterface repid=\"" << HelpFunctions::convert_uml_string_in_path( bases_[j]->repository_id() ) << "\" />";
						this->add_generated_interface( bases_ [j]);
					}
					HelpFunctions::dec_indent_level ( indent_level );
				}
				out << "\"/>";
				HelpFunctions::new_line ( out, indent_level );
			}
		}
	// generate inherit interaces
		if ( _bases_itfs->length () > 0 )
			{
				for (i = 0; i < _bases_itfs->length (); i++)
				{
					if (! is_contaned_generated_interface (_bases_itfs[i]) )
					{
						out << "<interface name=\"" << _bases_itfs[i]->identifier() << "\" repid=\""<< HelpFunctions::convert_uml_string_in_path( _bases_itfs[i]->repository_id() ) << "\"/>";;  
						HelpFunctions::new_line ( out, indent_level );
						this->add_generated_interface( _bases_itfs [i]);
					}
				}
			}
	}
	// generate uses interfaces
	if (receptacle_->length () > 0)
	{
		CORBA::ULong i;
		if (receptacle_->length () > 0)
		{
			for (i = 0; i < receptacle_->length (); i++)
			{
				if (! is_contaned_generated_interface (receptacle_[i]->uses_itf () ) )
				{
					MDE::BaseIDL::InterfaceDef_var uses_itf_ = receptacle_[i]->uses_itf ();
					out << "<interface name=\"" << uses_itf_->identifier() << "\" repid=\""<< HelpFunctions::convert_uml_string_in_path( uses_itf_->repository_id() );  
					this->add_generated_interface( receptacle_[i]->uses_itf () );
					MDE::BaseIDL::InterfaceDefSet_var bases_ = uses_itf_->base();
					if ( bases_->length () > 0 )
					{
						out << "\">";
						HelpFunctions::inc_indent_level ( indent_level );
						_bases_itfs = bases_;
						for (CORBA::ULong j = 0; j < bases_->length (); j++)
						{
							HelpFunctions::new_line ( out, indent_level );
							out << "<inheritsinterface repid=\"" << HelpFunctions::convert_uml_string_in_path( bases_[j]->repository_id() )<< "\" />";
						}
						HelpFunctions::dec_indent_level ( indent_level );
					}
					out << "\"/>";
					HelpFunctions::new_line ( out, indent_level );
				}
			}
		// generate inherit interaces
			if ( provides_  && _bases_itfs->length () > 0 )
				{
					for (i = 0; i < _bases_itfs->length (); i++)
					{
						if (! is_contaned_generated_interface (_bases_itfs[i]) )
						{
							out << "<interface name=\"" << _bases_itfs[i]->identifier() << "\" repid=\""<< HelpFunctions::convert_uml_string_in_path( _bases_itfs[i]->repository_id() ) << "\"/>";;  
							HelpFunctions::new_line ( out, indent_level );
							this->add_generated_interface( _bases_itfs [i]);
						}
					}
				}
		}
	}
	//HelpFunctions::dec_indent_level ( indent_level );
}
void CCDBackendSessionImpl::_generate_componentfeatures_element 
	( MDE::ComponentIDL::ComponentDef_ptr component_, ostream& out, unsigned long & indent_level )
{
	out << "<componentfeatures name = \"" << component_->identifier() << "\" repid=\"" << HelpFunctions::convert_uml_string_in_path( component_->repository_id() ) << "\">";
	MDE::BaseIDL::InterfaceDefSet_var set_ = component_->base();
	CORBA::ULong l_ = set_->length ();
	if (l_ == 1)
	{	
		HelpFunctions::inc_indent_level ( indent_level );
		HelpFunctions::new_line ( out, indent_level );
		MDE::ComponentIDL::ComponentDef_var inherit_ = MDE::ComponentIDL::ComponentDef::_narrow ( set_[set_->length ()-1] );
		if( CORBA::is_nil ( inherit_ ) ) 
			{
				throw NilObjectRef ( "Narrow problem: Base Component for Component!" );
			}
		_base = MDE::ComponentIDL::ComponentDef::_duplicate(inherit_);
		out << "<inheritscomponent repid=" << HelpFunctions::convert_uml_string_in_path( inherit_->repository_id() ) << "\">" ;
		HelpFunctions::dec_indent_level ( indent_level );
	}
	MDE::BaseIDL::InterfaceDefSet_var s_itfs_ = component_->supports_itf();
	CORBA::ULong s_ = s_itfs_->length ();
	if ( s_ > 0 )
	{
		_supported_itfs = s_itfs_;
		if ( l_ == 1)
		{
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			for (CORBA::ULong i = 0; i < s_itfs_->length (); i++)
			{
				out << "<supportsinterface repid=\"" << HelpFunctions::convert_uml_string_in_path( s_itfs_[i]->repository_id() ) << "\">" ;
				this->_generate_support_interface( s_itfs_[i], out, indent_level );
			}
			HelpFunctions::dec_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			out << "</supportsinterface>";
			HelpFunctions::dec_indent_level ( indent_level );
		}
		if ( l_ != 1)
		{
			HelpFunctions::inc_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			for (CORBA::ULong i = 0; i < s_itfs_->length (); i++)
			{
				out << "<supportsinterface repid=" << HelpFunctions::convert_uml_string_in_path( s_itfs_[i]->repository_id() ) << "\">" ;
				this->_generate_support_interface( s_itfs_[i], out, indent_level );
			}
			HelpFunctions::dec_indent_level ( indent_level );
			HelpFunctions::new_line ( out, indent_level );
			out << "</supportsinterface>";
			HelpFunctions::dec_indent_level ( indent_level );
		}
	}
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	this->_generate_ports_element( component_, out, indent_level );
	
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</componentfeatures>";
	HelpFunctions::new_line ( out, indent_level );
}
// END USER INSERT SECTION CCDBackendSessionImpl


CCDBackendSessionImpl::CCDBackendSessionImpl()
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::CCDBackendSessionImpl
	_all_generated_itfs = new MDE::BaseIDL::InterfaceDefSet;
	_all_generated_itfs->length(0);
	_bases_itfs = new MDE::BaseIDL::InterfaceDefSet;
	_bases_itfs->length(0);
	_supported_itfs = new MDE::BaseIDL::InterfaceDefSet;
	_supported_itfs->length(0);
	
// END USER INSERT SECTION CCDBackendSessionImpl::CCDBackendSessionImpl
}


CCDBackendSessionImpl::~CCDBackendSessionImpl()
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::~CCDBackendSessionImpl
// END USER INSERT SECTION CCDBackendSessionImpl::~CCDBackendSessionImpl

}


void
CCDBackendSessionImpl::set_context(::CCMGenerator::CCM_CCDBackend_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::CCMGenerator::CCM_CCDBackend_ContextImpl::_duplicate(context);
}


void
CCDBackendSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::configuration_complete
	cout << "configuration_complete() by CCDBackEnd was called!!! " <<  endl;
// END USER INSERT SECTION CCDBackendSessionImpl::configuration_complete
}


void
CCDBackendSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::remove
// END USER INSERT SECTION CCDBackendSessionImpl::remove
}


void
CCDBackendSessionImpl::rep_ref(CORBA::Object_ptr param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::_rep_ref
	
	_root = CORBA::Object::_duplicate(param);
	if( CORBA::is_nil ( _root ) ) 
		{
			throw NilObjectRef ( "Repository root is NIL: narrow problem!" );
		}
// END USER INSERT SECTION CCDBackendSessionImpl::_rep_ref
}


CORBA::Object_ptr
CCDBackendSessionImpl::rep_ref()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::rep_ref
	return _root._retn();
// END USER INSERT SECTION CCDBackendSessionImpl::rep_ref
}


void
CCDBackendSessionImpl::generate(const char* target, const char* output)
	throw(CORBA::SystemException, ::CCMGenerator::OutputError)
{
// BEGIN USER INSERT SECTION CCDBackendSessionImpl::generate
	try{

		this->connect_the_whole_repository ();

		MDE::CIF::HomeImplDefSet_var all_homeimpls_= 
			_repconnector._home_impl_def_ref->all_of_class_home_impl_def();
		int all_ = all_homeimpls_->length ();
		MDE::ComponentIDL::ComponentDef_var component_;
		MDE::ComponentIDL::HomeDef_var home_;
		MDE::CIF::ComponentImplDef_var comp_impl_;
		std::string home_rep_id_;
		std::string home_id_;
		std::string comp_rep_id_ = "";
		for (CORBA::ULong i = 0; i < all_homeimpls_->length (); i++)
		{
			if ( ! strcmp ( all_homeimpls_[i]->repository_id(), target) )
			{
				comp_impl_ = all_homeimpls_[i]->component_impl();
				home_ = all_homeimpls_[i]->home_end();
				component_ = comp_impl_->component_end();
				comp_rep_id_ =  component_->repository_id();
				home_id_ = home_->identifier();
				home_rep_id_ = home_->repository_id();
				break;
			}
		}
		if ( comp_rep_id_ == "" )
			throw NilObjectRef ( "ComponentID wasn't identified!!!" );

		ofstream out;
		out.open ( output );
		unsigned long indent_level = 0;
		begin(out);
		HelpFunctions::new_line ( out, indent_level );
		HelpFunctions::new_line ( out, indent_level );
		out << "<corbacomponent>" ;
		HelpFunctions::inc_indent_level ( indent_level );
		HelpFunctions::new_line ( out, indent_level );
		out << "<corbaversion> 3.0 </corbaversion>";
		HelpFunctions::new_line ( out, indent_level );
		out << "<componentrepid repid=\"" << HelpFunctions::convert_uml_string_in_path(comp_rep_id_) << "\"/>";
		HelpFunctions::new_line ( out, indent_level );
		out << "<homerepid repid=\"" << HelpFunctions::convert_uml_string_in_path(home_rep_id_) << "\"/>";
		HelpFunctions::new_line ( out, indent_level );
		this->_generte_componentkind_element ( component_, comp_impl_, out, indent_level );
		out << "<threading policy=\"multithread\"/>";
		HelpFunctions::new_line ( out, indent_level );
		out << "<configurationcomplete set=\"true\"/>";
		HelpFunctions::new_line ( out, indent_level );
		this->_generate_homefeatures_element( home_, home_id_, home_rep_id_, out, indent_level );
		this->_generate_componentfeatures_element ( component_,  out, indent_level );
		// inherit component
		if( ! CORBA::is_nil ( _base ) ) 
			this->_generate_componentfeatures_element ( _base,  out, indent_level );
		this->_generate_all_interfaces ( component_,  out, indent_level );
		HelpFunctions::dec_indent_level ( indent_level );
		HelpFunctions::new_line ( out, indent_level );
		out << "</corbacomponent>" ;
		out.close();
	}
	catch (CORBA::SystemException& e)
	{
		throw e;

	}

// END USER INSERT SECTION CCDBackendSessionImpl::generate
}


// BEGIN USER INSERT SECTION CCDBackEnd_compo
// END USER INSERT SECTION CCDBackEnd_compo


CCDBackEnd_compo::CCDBackEnd_compo()
:component_(new CCDBackendSessionImpl())
{
// BEGIN USER INSERT SECTION CCDBackEnd_compo::CCDBackEnd_compo
// END USER INSERT SECTION CCDBackEnd_compo::CCDBackEnd_compo
}


CCDBackEnd_compo::~CCDBackEnd_compo()
{
// BEGIN USER INSERT SECTION CCDBackEnd_compo::~CCDBackEnd_compo
// END USER INSERT SECTION CCDBackEnd_compo::~CCDBackEnd_compo

    component_->_remove_ref();
}


::CORBA::Object*
CCDBackEnd_compo::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "control")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
CCDBackEnd_compo::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
CCDBackEnd_compo::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION CCDBackEnd_compo::configuration_complete
// END USER INSERT SECTION CCDBackEnd_compo::configuration_complete
}


void
CCDBackEnd_compo::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::CCMGenerator::CCM_CCDBackend_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::CCMGenerator::CCM_CCDBackend_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::CCMGenerator::CCM_CCDBackend_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::CCMGenerator::CCM_CCDBackend_ContextImpl::_nil();
        
    #else
    context_ = ::CCMGenerator::CCM_CCDBackend_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
CCDBackEnd_compo::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CCDBackEnd_compo::ccm_activate
// END USER INSERT SECTION CCDBackEnd_compo::ccm_activate
}


void
CCDBackEnd_compo::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CCDBackEnd_compo::ccm_passivate
// END USER INSERT SECTION CCDBackEnd_compo::ccm_passivate
}


void
CCDBackEnd_compo::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CCDBackEnd_compo::ccm_remove
// END USER INSERT SECTION CCDBackEnd_compo::ccm_remove
}


// BEGIN USER INSERT SECTION CCDBackendHomeImpl
// END USER INSERT SECTION CCDBackendHomeImpl


CCDBackendHomeImpl::CCDBackendHomeImpl()
{
// BEGIN USER INSERT SECTION CCDBackendHomeImpl::CCDBackendHomeImpl
// END USER INSERT SECTION CCDBackendHomeImpl::CCDBackendHomeImpl
}


CCDBackendHomeImpl::~CCDBackendHomeImpl()
{
// BEGIN USER INSERT SECTION CCDBackendHomeImpl::~CCDBackendHomeImpl
// END USER INSERT SECTION CCDBackendHomeImpl::~CCDBackendHomeImpl

}


void
CCDBackendHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
CCDBackendHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION CCDBackendHomeImpl::create
// END USER INSERT SECTION CCDBackendHomeImpl::create
    return new CCDBackEnd_compo();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_CCDBackendHomeE(void)
{
// BEGIN USER INSERT SECTION create_CCDBackendHome
// END USER INSERT SECTION create_CCDBackendHome

    return new ::CCMGenerator::CCDBackendHomeImpl();
}

