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
#include "Output.h"


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
		NORMAL_ERR( "XMLInitializer: error during Xerces-c Initialization" );
        NORMAL_ERR2( "..... Exception message: ", StrX(toCatch.getMessage()) );
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
	// Initialize the XML4C2 system once for all instances
	static XMLInitializer ini;

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
    uri.append( Qedo::getEnvironment( "QEDO" ) );
#ifdef _WIN32
	// replace \ by /
    std::string::size_type f = uri.find_first_of("\\");
    while ((f >= 0) && (f < uri.size()))
    {
        uri.replace(f, 1, "/");
        f = uri.find_first_of("\\");
    }
#endif
    uri.append("/etc/catalog.xml");
    mXMLCatalog = new XMLCatalog(*parser_, uri, true);
	 mCatalogResolver = new CatalogResolver(*mXMLCatalog);
    parser_->setEntityResolver(mCatalogResolver);
}


/**
 *
 */
DOMXMLParser::~DOMXMLParser()
{
    delete errReporter_;
    delete parser_;
	 delete mCatalogResolver;
	 delete mXMLCatalog;
}


/**
 *
 */
int
DOMXMLParser::parse(char* fileName)
{
    xmlFile_ = fileName;

	DEBUG_OUT2 ("DOMXMLParser: Parsing file ", fileName);

	bool errorsOccured = false;

	LocalFileInputSource input(X(xmlFile_)); 

    try
    {
        parser_->parse(input);
    }
    catch (const XMLException& e)
    {
		NORMAL_ERR2( "DOMXMLParser: error during parsing ", fileName );
		NORMAL_ERR2( "..... Message: ", StrX(e.getMessage()) );
        errorsOccured = true;
    }
    catch (const DOMException& e)
    {
		NORMAL_ERR2( "DOMXMLParser: error during parsing ", fileName );
		NORMAL_ERR2( "..... DOMException code: ", e.code );
        errorsOccured = true;
    }
    catch (...)
    {
		NORMAL_ERR2( "DOMXMLParser: error during parsing ", fileName );
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

