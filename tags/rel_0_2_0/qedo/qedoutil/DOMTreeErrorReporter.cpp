/*
 * $Log: DOMTreeErrorReporter.cpp,v $
 * Revision 1.2  2003/01/21 10:52:28  neubauer
 * migration to Xerces 2_1;
 *
 * Revision 1.1  2002/11/08 10:32:11  neubauer
 * - ComponentInstallation extended by upload operation;
 * - XML is used to make installation information persistent;
 * - zlib is used to unpack assembly packages;
 *
 * Revision 1.2  2002/03/15 10:41:38  bertram
 * xerces version is now 1.7.0, the include paths changed;
 *
 * Revision 1.1  2002/02/28 15:44:13  bertram
 * initial deployment version
 *
 * Revision 1.9  2001/05/11 13:24:53  tng
 * Copyright update.
 *
 * Revision 1.8  2001/05/04 19:01:05  tng
 * DOMPrint fix.  Check error before continuing.
 *
 * Revision 1.7  2001/05/03 15:59:32  tng
 * Schema: samples update with schema
 *
 * Revision 1.6  2000/08/24 22:36:22  andyh
 * Fix DOMPrint crash when input xml file is not found.
 *
 * Revision 1.5  2000/05/15 22:31:06  andyh
 * Replace #include<memory.h> with <string.h> everywhere.
 *
 * Revision 1.4  2000/03/02 19:53:40  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.3  2000/02/06 07:47:18  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.2  1999/12/03 00:14:53  andyh
 * Removed transcoding stuff, replaced with DOMString::transcode.
 *
 * Tweaked xml encoding= declaration to say ISO-8859-1.  Still wrong,
 * but not as wrong as utf-8
 *
 * Revision 1.1.1.1  1999/11/09 01:09:51  twl
 * Initial checkin
 *
 * Revision 1.6  1999/11/08 20:43:35  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

#include <xercesc/sax/SAXParseException.hpp>
#include "DOMTreeErrorReporter.h"
#include <iostream>
#include <stdlib.h>
#include <string>


void DOMTreeErrorReporter::warning(const SAXParseException&)
{
    //
    // Ignore all warnings.
    //
}

void DOMTreeErrorReporter::error(const SAXParseException& toCatch)
{
    fSawErrors = true;
	std::cerr << "Error at file \"" << StrX(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
		 << "\n   Message: " << StrX(toCatch.getMessage()) << std::endl;
}

void DOMTreeErrorReporter::fatalError(const SAXParseException& toCatch)
{
    fSawErrors = true;
	std::cerr << "Fatal Error at file \"" << toCatch.getSystemId()
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
		 << "\n   Message: " << StrX(toCatch.getMessage()) << std::endl;
}

void DOMTreeErrorReporter::resetErrors()
{
    // No-op in this case
}