/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

#ifndef __DOM_OUTPUT_H__
#define __DOM_OUTPUT_H__


#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/dom/DOM.hpp>
//#include <stdlib.h>
#include <iostream>


// ---------------------------------------------------------------------------
//  output operators
// ---------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& target, const DOMString& toWrite);
XMLFormatter& operator<< (XMLFormatter& strm, const DOMString& s);
//ostream& operator<<(ostream& target, DOM_Node& toWrite);


/**
 *
 */
class DOMOutput : public XMLFormatTarget
{
public:
	std::ostream& target_;
	XMLCh* encodingName_;
	XMLFormatter* formatter_;
	XMLFormatter::UnRepFlags unRepFlags_;

public:
	DOMOutput (std::ostream&);
    ~DOMOutput();

    // -----------------------------------------------------------------------
    //  Implementations of the format target interface
    // -----------------------------------------------------------------------

    void writeChars(const   XMLByte* const  toWrite,
                    const   unsigned int    count,
                            XMLFormatter * const formatter)
    {
        // Surprisingly, Solaris was the only platform on which
        // required the char* cast to print out the string correctly.
        // Without the cast, it was printing the pointer value in hex.
        // Quite annoying, considering every other platform printed
        // the string with the explicit cast to char* below.
        target_.write((char *) toWrite, (int) count);
    };

	//
	DOMOutput& operator<<( DOM_Node& toWrite );
	
private:
    // -----------------------------------------------------------------------
    //  Unimplemented methods.
    // -----------------------------------------------------------------------
    DOMOutput(const DOMOutput& other);
    void operator=(const DOMOutput& rhs);
};


/**
 *
 */
class XMLInitializer
{
public:
    XMLInitializer();
	~XMLInitializer();
};


#endif