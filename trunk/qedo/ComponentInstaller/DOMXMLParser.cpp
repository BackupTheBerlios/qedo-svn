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

#include "DOMXMLParser.h"


namespace Qedo {


/**
 *
 */
XMLInitializer::XMLInitializer()
{
	// Initialize the XML4C2 system
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch(const XMLException& toCatch)
    {
        std::cerr << "Error during Xerces-c Initialization" << std::endl;
        std::cerr << "  Exception message:" << toCatch.getMessage() << std::endl;
    }
}


/**
 *
 */
XMLInitializer::~XMLInitializer()
{
}


/**
 *
 */
DOMXMLParser::DOMXMLParser()
{
	// Initialize the XML4C2 system once for all instances
	static XMLInitializer ini;

	valScheme_ = DOMParser::Val_Auto;
    doNamespaces_ = false;
    doSchema_ = false;
    doCreate_ = false;
    
    //  Create our parser, then attach an error handler to the parser.
    //  The parser will call back to methods of the ErrorHandler if it
    //  discovers errors during the course of parsing the XML document.
    parser_ = new DOMParser;
    parser_->setValidationScheme( valScheme_ );
    parser_->setDoNamespaces( doNamespaces_ );
    parser_->setDoSchema( doSchema_ );
    errReporter_ = new DOMTreeErrorReporter();
    parser_->setErrorHandler( errReporter_ );
    parser_->setCreateEntityReferenceNodes( doCreate_ );
    parser_->setToCreateXMLDeclTypeNode( true );

    // set catalog and resolver
    std::string uri = "file:///";
    
#ifdef _WIN32
	TCHAR tchBuffer[256];
	LPTSTR lpszSystemInfo = tchBuffer;
	DWORD dwResult = ExpandEnvironmentStrings("%QEDO%", lpszSystemInfo, 256); 
    uri.append(lpszSystemInfo);

	// replace \ by /
    std::string::size_type f = uri.find_first_of("\\");
    while ((f >= 0) && (f < uri.size()))
    {
        uri.replace(f, 1, "/");
        f = uri.find_first_of("\\");
    }
#else
	TODO
#endif
    uri.append("/etc/catalog.xml");
    mXMLCatalog = new XMLCatalog(*parser_, uri, true);
    parser_->setEntityResolver(new CatalogResolver(*mXMLCatalog));
}


/**
 *
 */
DOMXMLParser::~DOMXMLParser()
{
    //  Clean up the error handler. The parser does not adopt handlers
    //  since they could be many objects or one object installed for multiple
    //  handlers.
    delete errReporter_;

    //  Delete the parser itself.
    delete parser_;
}


/**
 *
 */
int
DOMXMLParser::parse(char* fileName)
{
	int error = 0;
    xmlFile_ = fileName;

    //  Parse the XML file, catching any XML exceptions that might propogate
    //  out of it.
    try
    {
        parser_->parse( xmlFile_ );
        error = parser_->getErrorCount();
    }
    catch (const XMLException& e)
    {
        std::cerr << "An error occured during parsing\n   Message: "
             << DOMString(e.getMessage()) << std::endl;
        error = 1;
    }
    catch (const DOM_DOMException& e)
    {
        std::cerr << "A DOM error occured during parsing\n   DOMException code: "
             << e.code << std::endl;
        error = 1;
    }
    catch (...)
    {
        std::cerr << "An error occured during parsing\n " << std::endl;
        error = 1;
    }

    if ( ! error &&  ! errReporter_->getSawErrors() )
    {
        document_ = parser_->getDocument();
    }

    //  The DOM document and its contents are reference counted, and need
    //  no explicit deletion.
    return error;
}


/**
 *
 */
DOM_Document
DOMXMLParser::getDocument()
{
	return parser_->getDocument();
}


}