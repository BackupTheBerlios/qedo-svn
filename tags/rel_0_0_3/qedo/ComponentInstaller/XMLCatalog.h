#ifndef __XMLCATALOG_H__
#define __XMLCATALOG_H__


#ifdef _MSC_VER
#pragma warning (disable : 4786) // identifier was truncated to '255' characters ...
#endif

#include <xercesc/parsers/DOMParser.hpp>
#include "Uri.h"
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
    XMLCatalog (DOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute = true);
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

    bool lookup (const std::string & aPublicId, URI & aTarget) const;
};


class RemapEntry : public virtual RemapEntryBase
{
private:
    URI mSystemId;
    URI mTarget;
public:
    RemapEntry (const URI & aSystemId, const URI & aTarget);

    bool lookup (const URI & aSystemId, URI & aTarget) const;
};


class DelegateEntry : public virtual Entry
{
private:
    std::string mPrefix;
    long mPrefixLen;
    XMLCatalog mCatalog;
public:
    DelegateEntry (const std::string & aPrefix, DOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute);

    bool lookup (const std::string & aPublicId, URI & aTarget) const;
};


class ExtendEntry : public virtual Entry, public virtual RemapEntryBase
{
private:
    XMLCatalog mCatalog;
public:
    ExtendEntry (DOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute);

    bool lookup (const std::string & aPublicId, URI & aTarget) const;
    bool lookup (const URI & aSystemId, URI & aTarget) const;
};


}


#endif
