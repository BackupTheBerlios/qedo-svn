/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

#include <strstream>
#include <iostream>
#include "XMLCatalog.h"
#include <xercesc/framework/URLInputSource.hpp>


namespace Qedo {

	
XMLCatalog::XMLCatalog (DOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute)
  : mMakeAbsolute(aMakeAbsolute)
{
    // reuse some variables
    DOM_NodeList nl;
    DOM_Node n;
    DOM_Element e;
    URI u, v;
    std::string s;

    // parse the catalog file
	 XMLCh empty[1] = {0};

    URLInputSource uis(empty, aCatalog.getText());
    aParser.parse(uis);
    DOM_Document doc = aParser.getDocument();

    // determine catalog base
    nl = doc.getElementsByTagName("Base");
    if (nl.getLength() > 0)
    {
        n = nl.item(0);
        e = static_cast< DOM_Element & >(n);
        s = e.getAttribute("HRef").transcode();
        mBaseHref = s;
        if (mBaseHref.isRelative())
        {
            mBaseHref = mBaseHref.makeAbsolute(aCatalog);
        }
    }
    else
    {
        mBaseHref = URI("./").makeAbsolute(aCatalog);
    }

    // add Map entries to 'map' list
    unsigned i = 0;
    nl = doc.getElementsByTagName("Map");
    for (i = 0; i < nl.getLength(); ++i)
    {
        n = nl.item(i);
        e = static_cast< DOM_Element & >( n );
        s = e.getAttribute("Publicsystem-identifier").transcode();
        u = e.getAttribute("HRef").transcode();
        if( mMakeAbsolute && u.isRelative() )
        {
            u = u.makeAbsolute( mBaseHref );
        }
        mEntryList.push_back( new MapEntry( s, u ) );
    }

    // add Delegate entries to 'map' list
    nl = doc.getElementsByTagName("Delegate");
    for (i = 0; i < nl.getLength(); ++i)
    {
        n = nl.item(i);
        e = static_cast< DOM_Element & >(n);
        s = e.getAttribute("PublicId").transcode();
        u = e.getAttribute("HRef").transcode();
        if (u.isRelative())
        { 
	        u = u.makeAbsolute( mBaseHref );
        }
        mEntryList.push_back( new DelegateEntry( s, aParser, u, mMakeAbsolute ) );
    }

    // add Remap entries to 'remap' list
    nl = doc.getElementsByTagName("Remap");
    for (i = 0; i < nl.getLength(); ++i)
    {
        n = nl.item(i);
        e = static_cast< DOM_Element & >(n);
        u = e.getAttribute("SystemId").transcode();
        if (mMakeAbsolute && u.isRelative())
        { 
	        u = u.makeAbsolute(mBaseHref);
        }
        v = e.getAttribute("HRef").transcode();
        if( mMakeAbsolute && v.isRelative() )
        { 
	        v = v.makeAbsolute(mBaseHref);
        }
        mRemapEntryList.push_back( new RemapEntry( u, v ) );
    }

    // add Extend entries to 'map' and 'remap' list
    nl = doc.getElementsByTagName("Extend");
    for (i = 0; i < nl.getLength(); ++i)
    {
        n = nl.item(i);
        e = static_cast< DOM_Element & >(n);
        u = e.getAttribute("HRef").transcode();
        if (u.isRelative())
        { 
	        u = u.makeAbsolute(mBaseHref);
        }
        ExtendEntry * ee = new ExtendEntry(aParser, u, mMakeAbsolute);
        mEntryList.push_back(ee);
        mRemapEntryList.push_back(ee);
    }
}


XMLCatalog::~XMLCatalog()
{
  for (std::list< Entry * >::const_iterator i = mEntryList.begin(); i != mEntryList.end(); ++i)
  {
    delete *i;
  }
}


bool
XMLCatalog::lookup (const std::string & aPublicId, URI & aTarget) const
{
  for( std::list< Entry * >::const_iterator i = mEntryList.begin(); i != mEntryList.end(); ++i )
  {
    if ((*i)->lookup(aPublicId, aTarget))
    {
      return true;
    }
  }
  return false;
}


const URI
XMLCatalog::lookup (const std::string & aPublicId) const
{
  URI result;
  if( lookup( aPublicId, result ) )
  { 
    return result;
  }
  std::cerr << "lookup of PubID \"" << aPublicId << "\" failed\n" << std::endl;
  return result;
}


const URI
XMLCatalog::lookup (const URI & aSystemId) const
{
  URI result;
  lookup(aSystemId, result);
  return result;
}


bool
XMLCatalog::lookup (const URI & aSystemId, URI & aTarget) const
{
  URI sysid = (mMakeAbsolute && aSystemId.isRelative()) ? aSystemId.makeAbsolute(mBaseHref) : aSystemId;
  for (std::list< RemapEntryBase * >::const_iterator i = mRemapEntryList.begin(); i != mRemapEntryList.end(); ++i )
  {
    if ((*i)->lookup(sysid, aTarget))
    {
      return true;
    }
  }
  aTarget = sysid;
  return false;
}


const URI &
XMLCatalog::getBaseHref () const
{ 
	return mBaseHref;
}


DelegateEntry::DelegateEntry (const std::string & aPrefix, DOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute)
//  : mPrefix(aPrefix), mPrefixLen(aPrefix.length()), mCatalog(aParser, aCatalog, aMakeAbsolute)
: mCatalog(aParser, aCatalog, aMakeAbsolute)
{
    mPrefix = aPrefix;
    mPrefixLen = aPrefix.length();
}


bool
DelegateEntry::lookup (const std::string & aPublicId, URI & aTarget) const
{
#if __GNUG__ == 2
  if (aPublicId.compare(mPrefix, mPrefixLen, 0) == 0)
#else
  if (aPublicId.compare(0, mPrefixLen, mPrefix) == 0)
#endif
  {
    return mCatalog.lookup(aPublicId, aTarget);
  }
  return false;
}


MapEntry::MapEntry (const std::string & aPublicId, const URI & aTarget)
//  : mPublicId(aPublicId), mTarget(aTarget)
{
    mPublicId = aPublicId;
    mTarget = aTarget;
}


bool
MapEntry::lookup (const std::string & aPublicId, URI & aTarget) const
{
  if (aPublicId.compare(mPublicId) == 0)
  {
    aTarget = mTarget;
    return true;
  }
  return false;
}


RemapEntry::RemapEntry (const URI & aSystemId, const URI & aTarget)
//  : mSystemId(aSystemId), mTarget(aTarget)
{
    mSystemId = aSystemId;
    mTarget = aTarget;
}
 

bool
RemapEntry::lookup (const URI & aSystemId, URI & aTarget) const
{
  if (mSystemId == aSystemId)
  {
    aTarget = mTarget;
    return true;
  }
  return false;
}


ExtendEntry::ExtendEntry (DOMParser & aParser, const URI & aCatalog, bool aMakeAbsolute)
: mCatalog(aParser, aCatalog, aMakeAbsolute)
{
}
 

bool
ExtendEntry::lookup (const std::string & aPublicId, URI & aTarget) const
{
    return mCatalog.lookup(aPublicId, aTarget);
}


bool
ExtendEntry::lookup (const URI & aSystemId, URI & aTarget) const
{
    return mCatalog.lookup(aSystemId, aTarget);
}


} // namespace HU_CCM_Container
