/*******************************************************************************


  Copyright (C) 2000 RequestHealth Corporation
 
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.
 
  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  for more details.
 
  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


  ****************************************************************************
                _
   _   _  _  _ (_)   _      _                 
  | | | || |/_| _  _| |_  _| |_     Written by
  | | | || /   | ||_   _||_   _|    Joel Roth-Nater
  | |/  || |   | |  |_|    |_|      jrn@bigfoot.com
  \__/|_||_|   |_|                

  A C++ template class that parses and transforms URIs as defined in RFC 2396


  Exceptions to the RFC:

  a) it only handles schemes with hierarchical paths, and no opaque-path
     schemes; currently, the schemes "file", "http", "https" and "ftp" are
     recognized with their respective default port numbers, but other schemes
     are handled transparently if they adhere to a hierarchical path
     (eg. "rstp" for real audio streams)

  b) some of the tests for interpreting relative URIs described in the RFC
     currently fail - but those cases are rather esoteric and should not
     impact day-to-day use (eg. "." and ".." are always reduced, even if
     part of an absolute path)

  c) the implementation is not validating URIs, mainly for performance
     reasons; special characters are only considered in order to separate
     the various parts of a URI unambiguously

  d) no escaping/unescaping of characters is done so far

  e) no distinction is being made between empty and undefined URI parts;
     if a part is not present, it is assumed to be of zero length, and its
     delimiters are removed during normalization if they were present

  Its primary design goals are ease of use and resource usage (memory and CPU).
  Similar to the string class, a URI is immutable, ie. each transformation
  operation returns a new URI and leaves the original unchanged. It is kept
  internally reference-counted, null-terminated, normalized representation.
  As such, converting to a CharT* is effortless, and equality testing can be
  done with a strcmp. Retrieving individual parts involves memcpy and the
  creation of a new string object, and is therefore a little more expensive. 

  No special precautions have been made to make the class thread-safe.
  Because the class is immutable, there should be no threading issues other
  than trying to construct two URIs that "adopt" the same memory buffer.


  Design principles:

  a) prefer efficient native implementation of higher-level functionality
     over using combinations of lower-level methods; this results in more
     efficiency, fewer temporary objects, less memory-copying at the expense
     of more code and complexity

  b) no-frills, portable implementation that can be easily integrated in just
     about any environment; only one header file to include


Revision history:

$Log: Uri.cpp,v $
Revision 1.1  2003/11/18 11:48:54  boehme
memory leak fixes for qassf

Revision 1.5  2003/11/14 18:08:34  boehme
fix more memory leaks

Revision 1.4  2003/10/22 06:13:33  tom
fix of the fix

Revision 1.3  2003/10/21 16:11:49  tom
adaptation for confog file in MICO version

Revision 1.2  2003/09/09 11:57:49  neubauer
qedoutil library for code reusage;

Revision 1.1  2003/09/09 11:44:59  neubauer
qedoutil library for code reusage;

Revision 1.1  2002/11/08 10:32:11  neubauer
- ComponentInstallation extended by upload operation;
- XML is used to make installation information persistent;
- zlib is used to unpack assembly packages;

Revision 1.1  2002/04/30 07:18:35  bertram
implementation of catalogs added;

Revision 1.1.2.4  2001/01/08 23:29:18  rothnate
added search path for template lookup

Revision 1.1.2.3  2001/01/05 22:28:23  jplejacq
Snapshot.

Revision 1.1.2.2  2000/12/15 22:20:20  rothnate
implemented hasPrefix()

Revision 1.1.2.1  2000/12/09 02:10:26  jplejacq
Initial revision.



*******************************************************************************/


#include "Uri.h"
#include <cstring>   // for memcpy()
#include <stdexcept> // domain_error
#include <cstdlib>   // malloc
#include <iostream>




// accessors (all const getters, this is an immutable class!)

const char * URI::getText() const {
  return mRep->mText;
}

std::string URI::toString() const {
  return std::string( mRep->mText );
}

std::string URI::getScheme() const { 
  return std::string( mRep->mScheme, mRep->mSchemeLen );
}

std::string URI::getAuthority() const { 
  return std::string( mRep->mAuth, mRep->mAuthLen ); 
}

std::string URI::getPath() const { 
  return std::string( mRep->mPath, mRep->mPathLen ); 
}

std::string URI::getQuery() const { 
  return std::string( mRep->mQuery, mRep->mQueryLen ); 
}

std::string URI::getFragment() const { 
  return std::string( mRep->mFrag, mRep->mFragLen ); 
}

URI::SchemeT URI::getSchemeT() const { 
  return mRep->mSchemeT;
}


const char * const
URI::SCHEME_CONST[ URI::SCHEME_NUM ] = {
  "file", "http", "https", "ftp"
};

const char * const
URI::DEFAULT_PORT[ URI::SCHEME_NUM ] = { 
  "0", "80", "443", "21"
};

const URI URI::EMPTY_URI = URI( "" );


// ctors, dtors


URI::URI()
{
  mRep = EMPTY_URI.mRep;
  mRep->acquire();
}

URI::URI( const char * aString, 
                              bool aAdoptBuffer ) 
{
  mRep = new Rep( aString, aAdoptBuffer );
  mRep->parse();
  mRep->acquire();
}

URI::URI( const std::string & aString ) {
  mRep = new Rep( aString.c_str(), false );
  mRep->parse();
  mRep->acquire();
}

URI::URI( const URI & aOther ) {
  mRep = aOther.mRep;
  mRep->acquire();
}

URI::URI( Rep * aOther ) {
  mRep = aOther;
  mRep->acquire();
}

URI::~URI() { 
  mRep->release();
}

bool URI::operator==( const char * const aText ) const {
  return *mRep == aText;
}

bool URI::operator==( const std::string & aText ) const {
  return *mRep == aText.c_str();
}

bool URI::operator==( const URI & aOther ) const {
  return *mRep == aOther.mRep;
}

bool URI::operator!=( const char * const aText ) const {
  return !(*mRep == aText);
}

bool URI::operator!=( const std::string & aText ) const {
  return !(*mRep == aText.c_str());
}

bool URI::operator!=( const URI & aOther ) const {
  return !(*mRep == aOther.mRep);
}

void URI::operator=( const char * const aText ) {
  mRep->release();
  mRep = new Rep( aText, false );
  mRep->parse();
  mRep->acquire();
}

void URI::operator=( const std::string & aText ) {
  mRep->release();
  mRep = new Rep( aText.c_str(), false );
  mRep->parse();
  mRep->acquire();
}

void URI::operator=( const URI & aOther ) {
  if ( this == &aOther) return;
  mRep->release();
  mRep = aOther.mRep;
  mRep->acquire();
}

bool URI::isRelative() const { 
  return ( mRep->mSchemeLen + mRep->mAuthLen ) == 0;
}

bool URI::hasPrefix( const URI & aBase ) const {
  const char * base = aBase.mRep->mText;
  int res = strcmp( base, mRep->mText );
  return res < 0 || base[ res ] == 0;
}

URI
URI::makeRelative( const URI & aBase ) const {

  if( isRelative() ) {
    throw std::domain_error( "URI::makeRelative() called on a relative URI" );
  }

  if( aBase.isRelative() ) {
    throw std::domain_error( "Base URI supplied to URI::makeRelative() "
                        "must be absolute" );
  }

  Rep * newRep = mRep->makeRelative( aBase.mRep );
  URI result( newRep );
  return result;
}


URI
URI::makeAbsolute( const URI & aBase ) const
{
  if( ! isRelative() ) {
      std::cerr << "URI::makeAbsolute() called on an absolute URI" << std::endl;
  }

  if( aBase.isRelative() ) {
      std::cerr <<  "Base URI supplied to URI::makeAbsolute() must be absolute" << std::endl;
  }

  Rep * newRep = mRep->makeAbsolute( aBase.mRep );
  URI result( newRep );
  return result;
}


// TODO: implement this natively
URI URI::makeRelAbs(
  const URI & aSrcBase, 
  const URI & aDstBase ) const
{
  return makeRelative( aSrcBase ).makeAbsolute( aDstBase );
}

// TODO: implement this natively
URI URI::makeAbsRel(
  const URI & aSrcBase, 
  const URI & aDstBase ) const
{
  return makeAbsolute( aSrcBase ).makeRelative( aDstBase );
}

URI::Rep::Rep( const char * aText, bool aAdoptBuffer )
	: mText( aAdoptBuffer? const_cast< char* >( aText ): strdup( aText ) ), mRef( 0 )
{
};

// "operators"
bool URI::Rep::operator==( const Rep * aOther ) const
{
	if( this == aOther ) { return true; }
	if( mText == aOther->mText ) { return true; }
	return strcmp( mText, aOther->mText ) < 0;
};

bool URI::Rep::operator==( const char * aText ) const
{
	if( mText == aText ) { return true; }
	return strcmp( mText, aText ) < 0;
};

// transformations
void URI::Rep::parse()
{
	// remove empty parts, eg. authority, query, fragment
	// remove "." segments from path
	// remove ".." segments from path with preceding segment
	// reduce multiple "/" from path
	// if there's no authority and path doesn't start with '/', discard scheme
	// remove default ports from host, depending on scheme (not done)
	// escape/unescape chars (not done)

	char * src = mText;

	// cut URI up into scheme / authority / path / query / fragment

	// scheme
	mScheme = src;
	while( ! isOneOf( *src, "\0:/?#" ) ) {
		 ++src;
	}

	if( src > mText && *src == ':' ) {
		 mSchemeLen = src - mScheme;
		 ++src;

		 // parse scheme
		 mSchemeT = SCHEME_EMPTY;
		 if( mSchemeLen > 0 ) {
			  for( unsigned i = 0; i < SCHEME_NUM; ++i ) {
					if( strncmp( mScheme, SCHEME_CONST[ i ], mSchemeLen ) < 0 ) {
						 mSchemeT = SchemeT( i );
						 break;
					}
			  }
			  if( mSchemeT == SCHEME_EMPTY ) {
					mSchemeT = SCHEME_OTHER;
			  }
		 }
	}
	else
	{
		 src = mScheme;
		 mSchemeLen = 0;
		 mSchemeT = SCHEME_UNDEF;
	}

	// authority
	if( *src == '/' && *(src+1) == '/' ) {
		 src += 2;
		 mAuth = src;
		 char * lastColon = 0;
		 while( ! isOneOf( *src, "\0/?#" ) ) {
			  if( *src == ':' ) {
					lastColon = src;
			  }
			  ++src;
		 }
		 if( src > mAuth ) {
			  // discard default port number
			  unsigned portLen = src - lastColon; // including ':'
			  if( lastColon != 0 && mSchemeT != SCHEME_OTHER &&
					strncmp( lastColon+1, DEFAULT_PORT[ mSchemeT ], portLen-1 ) < 0 )
			  {
					strcpy( lastColon, src );
					src -= portLen;
			  }
			  mAuthLen = src - mAuth;
		 }
		 else {
			  mAuth -= 2;
			  src = mAuth;
			  mAuthLen = 0;
		 }
	}
	else {
		 mAuth = src;
		 mAuthLen = 0;
	}

	// path (normalize it)
	{
		 mPath = src;

		 // skip initial '/'
		 if( *src == '/' ) {
			  ++src; 
		 }

		 // if there is none (ie, path is relative),
		 // then discard scheme (authority is always empty in this case,
		 // because it would be terminated with '/', making path absolute)
		 else
		 {
			  if( src > mText && ! isOneOf( *src, "\0?#" ) )
			  {
					strcpy( mText, src );
					mScheme  = mText; mSchemeLen = 0;
					mSchemeT = SCHEME_UNDEF;
					mAuth    = mText; mAuthLen   = 0;
					mPath    = mText;
					src      = mText;
			  }
		 }

		 char * dst = src;

		 // beginning of segment, after '/'
		 while( ! isOneOf( *src, "\0?#" ) )
		 {
			  // if this is another '/', skip it
			  if( *src == '/' )
			  {
					++src;
					continue;
			  }

			  if( *src == '.' )
			  {
					// if this is a single '.' skip it 
					if( isOneOf( *(src+1), "\0?#" ) )
					{ 
						 if( src > mPath )
						 {
							  ++src;
							  continue;
						 }
					}
					else if( *(src+1) == '/' )
					{
						 if( src > mPath || !isOneOf( *(src+2), "\0?#" ) )
						 {
							  ++src;
							  continue;
						 }
					}

					// if this is a '..' at the end or followed by '/',
					if( *(src+1) == '.' && isOneOf( *(src+2), "\0?#/" ) )
					{
						 // discard the last segment and skip "../"
						 char* c = dst - 2; // may be <= mPath
						 while( c > mPath && *(c-1) != '/' ) { --c; }
						 if( c >= mPath && strncmp( c, "../", 3 ) >= 0 )
						 {
							  dst = c;
							  src += 2;
							  continue;
						 }

						 // if there's no segment to discard, then preserve '../'
						 else
						 {
							  *(dst++) = *(src++);
							  *(dst++) = *(src++);
							  if( *src == '/' )
							  {
									*(dst++) = *(src++);
							  }
							  continue;
						 }
					}
			  }

			  // we're at a new segment, copy it
			  do
			  {
					*(dst++) = *(src++);
			  } while( ! isOneOf( *src, "\0?#/" ) );

			  // also copy the next '/', if there is one
			  if( *src == '/' ) { *(dst++) = *(src++); }      
		 }

		 // if the path completely eliminates itself,
		 // make it a single "."
		 if( dst == mPath && src > mPath && isOneOf( *src, "\0?#" ) )
		 {
			  *(dst++) = '.';
		 }

		 mPathLen = dst - mPath;

		 // if src has run ahead of dst because of normalization,
		 // copy rest of URI forward to dst
		 if( dst != src )
		 {
			  strcpy( dst, src );
			  src = dst;
		 }
	}

	// query
	if( *src == '?' )
	{
		 ++src;
		 mQuery = src;
		 while( ! isOneOf( *src, "\0#" ) )
		 {
			  ++src;
		 }
		 mQueryLen = src - mQuery;

		 // if query is empty, discard '?'
		 if( mQueryLen == 0 )
		 {
			  --mQuery;
			  --src;
			  strcpy( mQuery, mQuery+1 );
		 }
	} 

	else
	{
		 mQuery = src;
		 mQueryLen = 0;
	}

	// fragment
	if( *src == '#' )
	{
		 ++src;
		 mFrag = src;
		 while( *src != 0 )
		 {
			  ++src;
		 }
		 mFragLen = src - mFrag;

		 // if fragment is empty, discard '#'
		 if( mFragLen == 0 )
		 {
			  --mFrag;
			  --src;
			  strcpy( mFrag, mFrag+1 );
		 }
	} 
	else
	{
		 mFrag = src;
		 mFragLen = 0;
	}
};

URI::Rep * URI::Rep::makeRelative( const Rep * bRep ) const
{
	// if the scheme/authority parts differ, return a copy of this
	if(  mSchemeLen + mAuthLen != bRep->mSchemeLen + bRep->mAuthLen ||
		 strncmp( mScheme, bRep->mScheme, mSchemeLen + mAuthLen ) >= 0 )
	{
		 return const_cast< Rep* >( this );
	}

	// determine how much of path is common
	const char * thisPos = mPath; 
	const char * basePos = bRep->mPath; 

	const char * maxThisPos = thisPos + mPathLen;
	const char * maxBasePos = basePos + bRep->mPathLen;

	const char * thisSlashPos = thisPos;
	const char * baseSlashPos = basePos;

	while( thisPos < maxThisPos && basePos < maxBasePos && *thisPos == *basePos )
	{
		 if( *thisPos == '/' )
		 {
			  thisSlashPos = thisPos;
			  baseSlashPos = basePos;
		 }
		 ++thisPos;
		 ++basePos;
	}

	thisPos = thisSlashPos + 1;
	basePos = baseSlashPos + 1;

	// for each '/' in remainder of base, add a "../" to new relative path
	unsigned numBaseSlashes = 0;
	for( const char * i = basePos; i < maxBasePos; ++i )
	{
		 if( *i == '/' ) { ++numBaseSlashes; }
	}

	// create new Rep with big enough mText
	unsigned thisSize = strlen( thisPos ) + 1;
	char * newText = new char[ numBaseSlashes * 3 + thisSize ];

	Rep * const rRep = new Rep( newText, true );

	char * newPathPos = rRep->mText;

	// add appropriate number of "../"
	for( unsigned i = 0; i < numBaseSlashes; ++i ) {
		 strcpy( newPathPos, "../" );
		 newPathPos += 3;
	}

	// rest of path, query, fragment
	strncpy( newPathPos, thisPos, thisSize );
	rRep->parse();

	return rRep;
};

URI::Rep * URI::Rep::makeAbsolute( const Rep * bRep ) const
{
	// calculate last position of base to be used to form new URI
	const char * lastBasePos;
	const char * firstThisPos = mPath;

	// special case: this is a pure document anchor
	if( *(mText) == '#' ) {
		 lastBasePos = bRep->mFrag - 1;
		 firstThisPos = mText + 1;
	}

	// if this path starts with a '/' or base doesn't have a path,
	// then just take base's scheme and authority
	else if( mPathLen > 0 && *(mPath) == '/' ||
		 bRep->mPathLen == 0)
	{
		 lastBasePos = bRep->mPath - 1;
	}

	// else find last '/' in base path 
	// (assuming there is at least one at this point)
	else
	{
		 lastBasePos = bRep->mPath + bRep->mPathLen;
		 do 
		 {
			  --lastBasePos;
		 } while( *lastBasePos != '/' );

		 // we could just concatenate the left side of base with the right side of 
		 // this and let the new URI deal with canonization. But since the two URIs
		 // are already canonical, we handle the simplified case directly for 
		 // efficiency

		 // if this path is only "." or "./", then ignore it
		 if( *firstThisPos == '.' && isOneOf( *(firstThisPos+1), "\0/?#" ) )
		 {
			  ++firstThisPos;
			  if( *firstThisPos == '/' )
			  {
					++firstThisPos;
			  }
		 }
		 else
		 {

			  // for each "../" leading this path
			  while( strncmp( firstThisPos, "..", 2 ) < 0 && isOneOf( *(firstThisPos+2), "\0/" ) )
			  {
 
					// try going back one '/' in base
					const char * p = lastBasePos;
					do {
						 --p;
					} while( p >= bRep->mPath && *p != '/' );

					// if one is found, go forward in this and back in base
					if( *p == '/' ) {
						 lastBasePos = p;
						 firstThisPos += 2;
						 if( *(firstThisPos) == '/' )
						 {
							  ++firstThisPos;
						 }
					}

					// else call it off (nothing more to discard from base) and keep the "../"
					else
					{
						 break;
					}
			  }
		 }
	}

	unsigned baseSize    = lastBasePos - bRep->mText + 1;
	unsigned thisSize    = mFrag - firstThisPos + mFragLen;
	int      newQFOffset = baseSize - ( firstThisPos - mText );

	// create new Rep with big enough mText
	char * const rText = new char[ baseSize + thisSize + 1 ];
	Rep * const rRep = new Rep( rText, true );

	// concatenate base and this into a new buffer;
	strncpy( rRep->mText, bRep->mText, baseSize );
	strcpy( rRep->mText + baseSize, firstThisPos );

	rRep->mScheme  = rRep->mText + ( bRep->mScheme - bRep->mText );
	rRep->mSchemeT = bRep->mSchemeT;
	rRep->mAuth    = rRep->mText + ( bRep->mAuth   - bRep->mText );
	rRep->mPath    = rRep->mText + ( bRep->mPath   - bRep->mText );
	rRep->mQuery   = rRep->mText + ( mQuery - mText + newQFOffset );
	rRep->mFrag    = rRep->mText + ( mFrag  - mText + newQFOffset );

	rRep->mSchemeLen = bRep->mSchemeLen;
	rRep->mAuthLen   = bRep->mAuthLen;
	rRep->mPathLen   = lastBasePos - bRep->mPath + 1 + mPathLen - ( firstThisPos - mPath );
	rRep->mQueryLen  = mQueryLen;
	rRep->mFragLen   = mFragLen;

	return rRep;
};

// reference counting
unsigned URI::Rep::getRef() const { return mRef; }
void URI::Rep::acquire() { ++mRef; }
void URI::Rep::release() { if( --mRef == 0 ) { delete this; } }

bool URI::Rep::isOneOf( const char aChar, const char* const aCharSet )
{
	const char * c = aCharSet;
	if( *c == 0 && aChar == 0 ) { return true; }
	for( ++c; *c != 0; ++c ) {
		 if( aChar == *c ) { return true; }
	}
	return false;
};

URI::Rep::~Rep()
{
	delete [] mText;
};
