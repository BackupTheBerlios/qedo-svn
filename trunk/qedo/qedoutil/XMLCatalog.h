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

#ifndef __XMLCATALOG_H__
#define __XMLCATALOG_H__


#ifdef _MSC_VER
#pragma warning (disable : 4786) // identifier was truncated to '255' characters ...
#endif

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include "Uri.h"
#include "DOMTreeErrorReporter.h"
#include <list>


/*   The lookup algorithm works as advertised in the XMLCatalog proposal.
     Additionally, a makeAbsolute parameter is used. If it is true, relative
     URIs are converted to absolute with the catalog base in the following
     instances:

     - target URIs for PublicID mappings
     - source and target URIs for SystemID re-mappings
     - SystemID parameter for lookup

     As a consequence, a PublicID lookup always returns an absolute URI
     when successful. A SystemID lookup converts the input URI to absolute
     even if it otherwise fails to locate a replacement.

     If makeAbsolute is false, these URIs are left relative, and it is up
     to the application to further resolve relative URIs that may be coming 
     out of a lookup.
 */


namespace Qedo {


class Entry
{
public:
    virtual bool lookup (const std::string & aPublicId, URI & aTarget) const = 0;
};


class RemapEntryBase
{
public:
    virtual bool lookup (const URI & aSystemId, URI & aTarget) const = 0;
};


class XMLCatalog
{
public:
    XMLCatalog (XercesDOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute = true);
    virtual ~XMLCatalog();

    // returns false if no mapping found
    bool lookup( const std::string & aPublicId, URI & aTarget ) const;

    // returns 0 if no mapping found
    const URI lookup( const std::string & aPublicId ) const;

    // returns false if no re-mapping found
    bool lookup( const URI & aSystemId, URI & aTarget ) const;

    // returns input (possibly made absolute) if no re-mapping found
    const URI lookup( const URI & aSystemId ) const;

    const URI & getBaseHref() const;

private:
    URI mBaseHref;
    const bool mMakeAbsolute;

    std::list< Entry * > mEntryList;
    std::list< RemapEntryBase * > mRemapEntryList;
};


class MapEntry : public virtual Entry
{
private:
    std::string mPublicId;
    URI mTarget;
public:
    MapEntry (const std::string & aPublicId, const URI & aTarget);
	 virtual ~MapEntry();

    bool lookup (const std::string & aPublicId, URI & aTarget) const;
};


class RemapEntry : public virtual RemapEntryBase
{
private:
    URI mSystemId;
    URI mTarget;
public:
    RemapEntry (const URI & aSystemId, const URI & aTarget);
	 virtual ~RemapEntry();

    bool lookup (const URI & aSystemId, URI & aTarget) const;
};


class DelegateEntry : public virtual Entry
{
private:
    std::string mPrefix;
    long mPrefixLen;
    XMLCatalog mCatalog;
public:
    DelegateEntry (const std::string & aPrefix, XercesDOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute);
	 virtual ~DelegateEntry();

    bool lookup (const std::string & aPublicId, URI & aTarget) const;
};


class ExtendEntry : public virtual Entry, public virtual RemapEntryBase
{
private:
    XMLCatalog mCatalog;
public:
    ExtendEntry (XercesDOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute);
	 virtual ~ExtendEntry();

    bool lookup (const std::string & aPublicId, URI & aTarget) const;
    bool lookup (const URI & aSystemId, URI & aTarget) const;
};


}


#endif
