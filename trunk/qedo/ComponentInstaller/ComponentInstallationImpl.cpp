/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

static char rcsid[] = "$Id: ComponentInstallationImpl.cpp,v 1.12 2003/05/19 15:10:23 tom Exp $";

#include "ComponentInstallationImpl.h"

#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#else
#include <unistd.h>
#endif

namespace Qedo {


std::string	ComponentInstallationImpl::inst_file_;


ComponentInstallationImpl::ComponentInstallationImpl (CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
	// Initialize the XML4C2 system once for all instances
	static XMLInitializer ini;

	if (inst_file_ == "")
	{
		inst_file_ = g_qedo_dir + "/deployment/installedComponentImplementations.xml";
	}
}


ComponentInstallationImpl::~ComponentInstallationImpl()
{
}


void
ComponentInstallationImpl::initialize()
{
	try
	{
		CORBA::Object_var root_poa_obj = orb_->resolve_initial_references ("RootPOA");
		root_poa_ = PortableServer::POA::_narrow (root_poa_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		std::cerr << "ComponentInstallationImpl: Fatal error - no root POA available." << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ComponentInstallationImpl: Fatal error - cannot narrow root POA." << std::endl;
		throw CannotInitialize();
	}

	root_poa_manager_ = root_poa_->the_POAManager();

	root_poa_manager_->activate();

	// get NameService
    if ( !initNameService(orb_))
    {
        throw CannotInitialize();
    }

	// bind in NameService
	CORBA::Object_var my_ref = this->_this();
    std::string name = "Qedo/ComponentInstallation/";
    char hostname[256];
	if (gethostname (hostname, 256))
	{
		std::cerr << "ComponentInstallationImpl: Cannot determine my hostname" << std::endl;
		throw CannotInitialize();
	}
    name.append(hostname);
    if ( !registerName(name, my_ref, true))
    {
        throw CannotInitialize();
    }

	std::cout << "..... bound under " << name << std::endl;

	//
	// deployment directory
	//
	if (makeDir(g_qedo_dir + "/deployment"))
	{
		std::cerr << "deployment directory can not be created" << std::endl;
		throw CannotInitialize();
	}

	//
	// directory to put the component packages
	//
	packageDirectory_ = g_qedo_dir + "/deployment/packages";
	if (makeDir(packageDirectory_))
	{
		std::cerr << "componentPackages directory can not be created" << std::endl;
		throw CannotInitialize();
	}

	//
	// directory to put the component implementations
	//
	installationDirectory_ = g_qedo_dir + "/deployment/components";
	if (makeDir(installationDirectory_))
	{
		std::cerr << "componentImplementations directory can not be created" << std::endl;
		throw CannotInitialize();
	}

	//
	// read information about deployed components
	//
	if ( !readInstalledComponents())
	{
		throw CannotInitialize();
	}

	std::cout << "..... number of already installed components: " << installed_components_.size() << std::endl;
	std::cout << std::endl;
}


bool
ComponentInstallationImpl::readInstalledComponents ()
{
	//
	// is there already a deployment file ?
	//
	if ( ! checkExistence(inst_file_.c_str(), IS_FILE)) 
	{
		std::ofstream deployment_file(inst_file_.c_str());
		if ( ! deployment_file)
		{
			std::cerr << "..... Cannot open file " << inst_file_ << std::endl;
			return false;
		}
		deployment_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
		deployment_file << "<deployed>\n";
		deployment_file << "</deployed>" << std::endl;
		deployment_file.close();

		return true;
	}
	
	//
	// parse the descriptor file
    //
	DOMXMLParser* parser = new DOMXMLParser();
    if (parser->parse(strdup(inst_file_.c_str())) != 0) 
    {
		std::cerr << "Error during parsing " << inst_file_ << std::endl;
        return false;
    }

	DOMDocument* doc = parser->getDocument();
	DOMElement* root = doc->getDocumentElement();
	DOMNodeList* aNodeList = root->getElementsByTagName(X("implementation"));
	for (unsigned int i = 0; i < aNodeList->getLength(); i++)
	{
		DOMElement* iElement = (DOMElement*) aNodeList->item(i);
		DOMElement* sElement = (DOMElement*) (iElement->getElementsByTagName(X("servants"))->item(0));
		DOMElement* bElement = (DOMElement*) (iElement->getElementsByTagName(X("business"))->item(0));
		
        //
        // extract descriptions
		//
		std::string uu_id = XMLString::transcode(iElement->getAttribute(X("id")));
		std::string servants_DLL_name = XMLString::transcode(sElement->getAttribute(X("code")));
		std::string servants_DLL_entry_point_function = XMLString::transcode(sElement->getAttribute(X("entry")));
		std::string executors_DLL_name = XMLString::transcode(bElement->getAttribute(X("code")));
		std::string executors_DLL_entry_point_function = XMLString::transcode(bElement->getAttribute(X("entry")));
		
		//
		// create new ComponentImplementation
		//
		ComponentImplementation newImplementation(uu_id, servants_DLL_name, servants_DLL_entry_point_function,
			                                      executors_DLL_name, executors_DLL_entry_point_function);
		installed_components_.push_back(newImplementation);
	}

	// delete parser
    delete parser;

	return true;
}


bool
ComponentInstallationImpl::addInstalledComponent (ComponentImplementation* aComponentImplementation)
{
	//
	// parse the descriptor file
    //
	DOMXMLParser* parser = new DOMXMLParser();
    if (parser->parse(strdup(inst_file_.c_str())) != 0) 
	{
		std::cerr << "Error during parsing " << inst_file_ << std::endl;
        return false;
	}

	//
	// add the new implementation
	//
	DOMDocument* doc = parser->getDocument();
	DOMElement* root = doc->getDocumentElement();
	root->appendChild(doc->createTextNode(X("\n    ")));

	DOMElement* servants = doc->createElement(X("servants"));
	servants->appendChild(doc->createTextNode(X("\n        ")));
	servants->setAttribute(X("code"), X(aComponentImplementation->servant_module_.c_str()));
	servants->setAttribute(X("entry"), X(aComponentImplementation->servant_entry_point_.c_str()));

	DOMElement* business = doc->createElement(X("business"));
	business->appendChild(doc->createTextNode(X("\n        ")));
	business->setAttribute(X("code"), X(aComponentImplementation->executor_module_.c_str()));
	business->setAttribute(X("entry"), X(aComponentImplementation->executor_entry_point_.c_str()));

	DOMElement* impl = doc->createElement(X("implementation"));
	impl->setAttribute(X("id"), X(aComponentImplementation->uuid_.c_str()));
	impl->appendChild (doc->createTextNode(X("\n        ")));
	impl->appendChild (servants);
	impl->appendChild (doc->createTextNode(X("\n        ")));
	impl->appendChild (business);
	impl->appendChild (doc->createTextNode(X("\n    ")));
	root->appendChild (impl);
	root->appendChild (doc->createTextNode(X("\n")));

	//
	// write the new list
	//
	try
    {
		//
		// get a serializer, an instance of DOMWriter
		//
		XMLCh tempStr[100];
		XMLString::transcode("LS", tempStr, 99);
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
		DOMWriter *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

		if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
		{
			theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}

		XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(inst_file_.c_str());

		//
		// do the serialization through DOMWriter::writeNode();
		//
		theSerializer->writeNode(myFormTarget, *doc);

		delete theSerializer;
		delete myFormTarget;
	}
    catch (XMLException& e)
	{
		std::cerr << "An error occurred during creation of output transcoder. Msg is:" << std::endl;
		std::cerr << StrX(e.getMessage()) << std::endl;
    }

	// delete parser
	delete parser;

	return true;
}


void 
ComponentInstallationImpl::install (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
	//
	// The description may have 2 forms:
	//
	// 1) servant_module:servant_entry_point:executor_module:executor_entry_point
	// 2) PACKAGE=<packagename>
	//

	std::cout << "..... installing Component type with UUID: " << implUUID << std::endl;

	// First test for duplicate UUIDs
	std::vector < ComponentImplementation >::const_iterator inst_iter;
	for (inst_iter = installed_components_.begin(); inst_iter != installed_components_.end(); inst_iter++)
	{
		if ((*inst_iter).uuid_ == implUUID)
		{
			std::cout << ".......... already installed !" << std::endl;
			return;
		}
	}

	//
	// component_loc contains PACKAGE location
	//
	std::string::size_type pos;
	std::string desc = component_loc;
	if( !desc.compare(0, 8, "PACKAGE="))
	{
		//
		// check whether the package exists
		//
		std::string comp_loc = packageDirectory_ + "/" + desc.substr(8);
		if (!checkExistence(comp_loc, IS_FILE))
		{
			std::cerr << ".......... missing package " << comp_loc << std::endl;
			std::cerr << ".......... upload before installing" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}

		//
		// create new implementation
		//
		ComponentImplementation newComponentImplementation(implUUID, installationDirectory_, comp_loc);
		bool ok = newComponentImplementation.install();
		// remove the package
		removeFileOrDirectory(comp_loc);
		
		if (ok)
		{
			installed_components_.push_back(newComponentImplementation);
			addInstalledComponent(&newComponentImplementation);
		}
		else
		{
			throw Components::Deployment::InstallationFailure();
		}
	}
	//
	// component_loc contains local code location
	//
	else
	{
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			std::cerr << "ComponentInstallationImpl: Cannot extract servant module name" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}
		std::string servant_module = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			std::cerr << "ComponentInstallationImpl: Cannot extract servant entry point" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}
		std::string servant_entry_point = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		if (pos == std::string::npos)
		{
			std::cerr << "ComponentInstallationImpl: Cannot extract executor module name" << std::endl;
			throw Components::Deployment::InvalidLocation();
		}
		std::string executor_module = desc.substr (0, pos);

		desc = desc.substr (pos + 1);
		std::string executor_entry_point = desc;

		//
		// create new implementation
		//
		ComponentImplementation newComponentImplementation(implUUID, servant_module, servant_entry_point, executor_module, executor_entry_point);
		installed_components_.push_back (newComponentImplementation);
		addInstalledComponent(&newComponentImplementation);
	}

	std::cout << "..... done (" << implUUID << ")" << std::endl;
}


void 
ComponentInstallationImpl::replace (const char* implUUID, const char* component_loc)
throw (Components::Deployment::InvalidLocation, Components::Deployment::InstallationFailure)
{
}


void 
ComponentInstallationImpl::remove (const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::RemoveFailure)
{
}


Components::Deployment::Location 
ComponentInstallationImpl::get_implementation( const char* implUUID)
throw (Components::Deployment::UnknownImplId, Components::Deployment::InstallationFailure)
{
    std::cout << "get_implementation " << implUUID << std::endl;
	// Scan through the installed components
	std::vector < ComponentImplementation >::const_iterator inst_iter;

	for (inst_iter = installed_components_.begin(); inst_iter != installed_components_.end(); inst_iter++)
	{
		if ((*inst_iter).uuid_ == implUUID)
		{
			// Component found
			std::string description = (*inst_iter).servant_module_ + ";";
			description += (*inst_iter).servant_entry_point_ + ";";
			description += (*inst_iter).executor_module_ + ";";
			description += (*inst_iter).executor_entry_point_;

			return CORBA::string_dup (description.c_str());
		}
	}

	throw Components::Deployment::UnknownImplId();
}


char* 
ComponentInstallationImpl::upload (const char* implUUID, const ::CORBA::OctetSeq& package)
throw (Components::Deployment::InstallationFailure)
{
	std::string theName(implUUID);
	std::string theFile = packageDirectory_ + "/" + theName;

    //
	// check if already uploaded
    //
	if (checkExistence(theFile, IS_FILE))
    {
        return CORBA::string_dup(theName.c_str());
    }

	//
	// save to disk
	//
	std::ofstream file(theFile.c_str(), std::ios::binary|std::ios::app);
    if (!file)
    {
		std::cerr << "Package " << theName << " can not be locally saved !!!" << std::endl;
        throw Components::Deployment::InstallationFailure();
    }
    const CORBA::Octet* it = package.get_buffer();
    file.write((char*)it, package.length());
    file.close();

	//
	// ensure the file is stored
	//
#ifdef _WIN32
	Sleep(1000);
#else
  sleep(1);
#endif
  
    return CORBA::string_dup(theName.c_str());
}

} // namespace Qedo
