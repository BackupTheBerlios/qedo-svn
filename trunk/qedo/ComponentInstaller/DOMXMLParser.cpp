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
	//
	// Initialize the XML4C2 system
	//
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch(const XMLException& toCatch)
    {
        std::cerr << "Error during Xerces-c Initialization";
        std::cerr << "  Exception message:" << StrX(toCatch.getMessage()) << std::endl;
    }
}


/**
 *
 */
XMLInitializer::~XMLInitializer()
{
	XMLPlatformUtils::Terminate();
}


/**
 *
 */
DOMXMLParser::DOMXMLParser()
{
	valScheme_ =			XercesDOMParser::Val_Auto;
    doNamespaces_ =			false;
    doSchema_ =				false;
	doSchemaFullChecking_ = false;
    doCreate_ =				false;
    
    //  Create our parser, then attach an error handler to the parser.
    //  The parser will call back to methods of the ErrorHandler if it
    //  discovers errors during the course of parsing the XML document.
    parser_ = new XercesDOMParser;
    parser_->setValidationScheme(valScheme_);
    parser_->setDoNamespaces(doNamespaces_);
    parser_->setDoSchema(doSchema_);
	parser_->setValidationSchemaFullChecking(doSchemaFullChecking_);
	parser_->setCreateEntityReferenceNodes(doCreate_);

    errReporter_ = new DOMTreeErrorReporter();
    parser_->setErrorHandler(errReporter_);
    
    //parser_->setToCreateXMLDeclTypeNode( true );

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
	char* e = getenv("QEDO");
   if(e)
	{
		uri.append(e);
	}
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
    delete errReporter_;
    delete parser_;
}


/**
 *
 */
int
DOMXMLParser::parse(char* fileName)
{
    xmlFile_ = fileName;
	std::cout << "..... parsing " << fileName << std::endl;

	bool errorsOccured = false;
	LocalFileInputSource input(X(xmlFile_)); 
    try
    {
        parser_->parse(input);
    }
    catch (const XMLException& e)
    {
		std::cerr << ".......... An error occurred during parsing\n   Message: "
			<< StrX(e.getMessage()) << std::endl;
        errorsOccured = true;
    }
    catch (const DOMException& e)
    {
		std::cerr << ".......... A DOM error occurred during parsing\n   DOMException code: "
			<< e.code << std::endl;
        errorsOccured = true;
    }
    catch (...)
    {
		std::cerr << ".......... An error occurred during parsing\n " << std::endl;
        errorsOccured = true;
    }

    if ( !errorsOccured &&  !errReporter_->getSawErrors())
    {
        document_ = parser_->getDocument();
    }

    return errorsOccured;
}


/**
 *
 */
DOMDocument*
DOMXMLParser::getDocument()
{
	return parser_->getDocument();
}


}

