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

#ifndef __DOM_XML_PARSER_H__
#define __DOM_XML_PARSER_H__


#include "qedoutil.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <string>
#include <stdlib.h>

#include "CatalogResolver.h"
#include "DOMTreeErrorReporter.h"
#include "XMLCatalog.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif


namespace Qedo {


/**
 * this class is only used to initialize the XML system
 */
class QEDOUTIL_API XMLInitializer
{
public:
	XMLInitializer();
	~XMLInitializer();
};


/**
 *
 */
class QEDOUTIL_API DOMXMLParser
{
private:
    char*							xmlFile_;
    bool							doNamespaces_;
    bool							doSchema_;
	bool							doSchemaFullChecking_;
    bool							doCreate_;

	const XMLCh*					gOutputEncoding;
	const XMLCh*					gMyEOLSequence;
	bool							gSplitCdataSections;
	bool							gDiscardDefaultContent;
	bool							gUseFilter;
	bool							gFormatPrettyPrint;

    XercesDOMParser::ValSchemes		valScheme_;
	DOMTreeErrorReporter*			errReporter_;
	XercesDOMParser*				parser_;
	DOMDocument*					document_;
    XMLCatalog*						mXMLCatalog;

public:
	DOMXMLParser();
	virtual ~DOMXMLParser();

	//
	int parse(char*);

	//
	DOMDocument* getDocument();
};


} // namespace


#endif

