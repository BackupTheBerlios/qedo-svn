#ifndef __URI_H__
#define __URI_H__


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

$Log: Uri.h,v $
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


#include <string>    // for template instantiation
#include <cstring>   // for memcpy()
#include <cassert>
#include <stdexcept> // domain_error
#include <cstdlib>   // malloc
#include <iostream>


// forward-declaration needed for instantiation
template< class charT, class stringT > class URI_;


// instantiate the most commonly used types
typedef URI_< char, std::string > URI;
// typedef URI_< wchar, wstring > WURI;


template< class charT, class stringT >
class URI_ {

public:


  /*
  These are not used internally, but defined so they can be referenced outside
  */
  typedef charT   CharT;
  typedef stringT StringT;


  /*
  This type is returned by getSchemeT()
  */
  typedef enum {
    SCHEME_FILE, SCHEME_HTTP,  SCHEME_HTTPS, SCHEME_FTP,   
    SCHEME_NUM,   // constant used to count known schemes
    SCHEME_UNDEF, // no scheme defined, currently only used internally
    SCHEME_EMPTY, // scheme string has zero length
    SCHEME_OTHER  // scheme specified, but not recognized
  } SchemeT;


  /*
  Construct an empty URI - ie. a relative one that points to the current doc.
  The result is equivalent to using URI( "" ), but it is much more efficient
  because a shared Rep can be used.
  */
  URI_();

  /*
  Construct a URI from an existing null-terminated character buffer.
  bool aAdoptBuffer: if true, the URI assumes ownership of the buffer and does 
                     not allocate new memory; the content of the buffer may
                     change due to URI normalization
  */
  URI_( const charT * const aString,
        bool aAdoptBuffer = false );

  /*
  Same as above, but since strings tend to want to own their buffers, this
  constructor does not allow adoption.
  */
  URI_( const stringT & aString );

  /*
  Copy constructor. Since the underlying Rep is not copied, this is a very
  lightweight operation, so URIs can be passed around "by value"
  */
  URI_( const URI_ & aOther );


  virtual ~URI_();


  /*
  Returns a pointer to the normalized, null terminated URI buffer, involves
  no processing
  */
  const charT * getText() const;


  /*
  These accessors return various parts of the URI as strings; direct buffer
  access is not possible because the parts themselves are not null terminated
  */
  stringT toString() const;
  stringT getScheme() const;
  stringT getAuthority() const;
  stringT getPath() const;
  stringT getQuery() const;
  stringT getFragment() const;


  /*
  Return the scheme (file, http, ftp etc.) of the URI; returns SCHEME_OTHER
  if the scheme was present, but not one of "http", "https", "ftp" or "file";
  returns SCHEME_EMPTY if the scheme was empty or none was given
  */
  SchemeT getSchemeT() const;


  /*
  Checks if another URI points to the same document
  */
  bool operator==( const charT * const aText ) const;
  bool operator==( const stringT & aText ) const;
  bool operator==( const URI_ & aOther ) const;

  bool operator!=( const charT * const aText ) const;
  bool operator!=( const stringT & aText ) const;
  bool operator!=( const URI_ & aOther ) const;

  void operator=( const charT * const aText );
  void operator=( const stringT & aText );
  void operator=( const URI_ & aOther );


  /*
  Trivial ...
  */
  bool isRelative() const;


  /*
  Checks if a URI is prefixed by another
  */
  bool hasPrefix( const URI_ & aBase ) const;


  /*
  Returns a new relative URI such that base + result == this; if base differs
  from this in its scheme or authority part, this URI is returned unchanged;
  throws an exception if either base or this is relative
  */
  URI_ makeRelative( const URI_ & aBase ) const;


  /*
  Returns a new absolute URI such that base + this == result;
  throws an exception if either base is relative or this is absolute
  */
  URI_ makeAbsolute( const URI_ & aBase ) const;


  /*
  Convenience method equivalent to, but potentially more efficient than
  makeRelative( aSrcBase ).makeAbsolute( aDstBase ); this is useful for
  pruning a URI in one tree by removing its base, and grafting it into
  another tree with a new base
  */
  URI_ makeRelAbs( const URI_ & aSrcBase, const URI_ & aDstBase ) const;

  /*
  Convenience method equivalent to, but potentially more efficient than
  makeAbsolute( aSrcBase ).makeRelative( aDstBase ); this is useful for
  moving a relative link from one base to another, and still have it point
  to the same place
  */
  URI_ makeAbsRel( const URI_ & aSrcBase, const URI_ & aDstBase ) const;


  /******  User documentation ends here, proceed at your own peril :-)  *******/


  void dump( std::ostream & aOstr ) const {
    aOstr << "u=0x" << hex << long( this ) << " "
          << "r=0x" << long( mRep ) << " "
          << "ref=" << dec << mRep->getRef() << hex << " "
          << "t=0x" << long( mRep->mText ) << dec << " "
          << "s=" << long( mRep->mScheme - mRep->mText) << "[" << mRep->mSchemeLen << "] "
          << "a=" << long( mRep->mAuth   - mRep->mText) << "[" << mRep->mAuthLen   << "] "
          << "p=" << long( mRep->mPath   - mRep->mText) << "[" << mRep->mPathLen   << "] "
          << "q=" << long( mRep->mQuery  - mRep->mText) << "[" << mRep->mQueryLen  << "] "
          << "f=" << long( mRep->mFrag   - mRep->mText) << "[" << mRep->mFragLen   << "]";
  }


private:
    // inner Representation class (defined later)
    class Rep;

    // ctor
    URI_( Rep * aOther );

    // class members
    Rep * mRep;

public:
    // class constants
    static const charT * const SCHEME_CONST[ SCHEME_NUM ];
    static const charT * const DEFAULT_PORT[ SCHEME_NUM ];
    static const URI_ EMPTY_URI;

private:
    class Rep {

    public:
        Rep( const charT * aText, bool aAdoptBuffer )
            : mText( aAdoptBuffer? const_cast< charT* >( aText ): strDup( aText ) ), mRef( 0 )
        {
        };

        // "operators"
        bool operator==( const Rep * aOther ) const
        {
            if( this == aOther ) { return true; }
            if( mText == aOther->mText ) { return true; }
            return strCmp( mText, aOther->mText ) < 0;
        };
        
        bool operator==( const charT * aText ) const
        {
            if( mText == aText ) { return true; }
            return strCmp( mText, aText ) < 0;
        };

        // transformations
        void parse()
        {
            // remove empty parts, eg. authority, query, fragment
            // remove "." segments from path
            // remove ".." segments from path with preceding segment
            // reduce multiple "/" from path
            // if there's no authority and path doesn't start with '/', discard scheme
            // remove default ports from host, depending on scheme (not done)
            // escape/unescape chars (not done)

            charT * src = mText;

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
                        if( strCmp( mScheme, SCHEME_CONST[ i ], mSchemeLen ) < 0 ) {
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
                charT * lastColon = 0;
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
                        strCmp( lastColon+1, DEFAULT_PORT[ mSchemeT ], portLen-1 ) < 0 )
                    {
                        strCopy( lastColon, src );
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
                        strCopy( mText, src );
                        mScheme  = mText; mSchemeLen = 0;
                        mSchemeT = SCHEME_UNDEF;
                        mAuth    = mText; mAuthLen   = 0;
                        mPath    = mText;
                        src      = mText;
                    }
                }

                charT * dst = src;

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
                            if( c >= mPath && strCmp( c, "../", 3 ) >= 0 )
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
                    strCopy( dst, src );
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
                    strCopy( mQuery, mQuery+1 );
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
                    strCopy( mFrag, mFrag+1 );
                }
            } 
            else
            {
                mFrag = src;
                mFragLen = 0;
            }
        };
        
        Rep * makeRelative( const Rep * bRep ) const
        {
            // if the scheme/authority parts differ, return a copy of this
            if(  mSchemeLen + mAuthLen != bRep->mSchemeLen + bRep->mAuthLen ||
                strCmp( mScheme, bRep->mScheme, mSchemeLen + mAuthLen ) >= 0 )
            {
                return const_cast< Rep* >( this );
            }

            // determine how much of path is common
            const charT * thisPos = mPath; 
            const charT * basePos = bRep->mPath; 
  
            const charT * maxThisPos = thisPos + mPathLen;
            const charT * maxBasePos = basePos + bRep->mPathLen;
  
            const charT * thisSlashPos = thisPos;
            const charT * baseSlashPos = basePos;
  
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
            for( const charT * i = basePos; i < maxBasePos; ++i )
            {
                if( *i == '/' ) { ++numBaseSlashes; }
            }
  
            // create new Rep with big enough mText
            unsigned thisSize = strLen( thisPos ) + 1;
            charT * newText = new charT[ numBaseSlashes * 3 + thisSize ];

            Rep * const rRep = new Rep( newText, true );

            charT * newPathPos = rRep->mText;

            // add appropriate number of "../"
            for( unsigned i = 0; i < numBaseSlashes; ++i ) {
                strCopy( newPathPos, "../" );
                newPathPos += 3;
            }

            // rest of path, query, fragment
            strCopy( newPathPos, thisPos, thisSize );
            rRep->parse();

            return rRep;
        };

        Rep * makeAbsolute( const Rep * bRep ) const
        {
            // calculate last position of base to be used to form new URI
            const charT * lastBasePos;
            const charT * firstThisPos = mPath;

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
                    while( strCmp( firstThisPos, "..", 2 ) < 0 && isOneOf( *(firstThisPos+2), "\0/" ) )
                    {
          
                        // try going back one '/' in base
                        const charT * p = lastBasePos;
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
            charT * const rText = new charT[ baseSize + thisSize + 1 ];
            Rep * const rRep = new Rep( rText, true );

            // concatenate base and this into a new buffer;
            strCopy( rRep->mText, bRep->mText, baseSize );
            strCopy( rRep->mText + baseSize, firstThisPos );

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
        unsigned getRef() const { return mRef; }
        void acquire() { ++mRef; }
        void release() { if( --mRef == 0 ) { delete this; } }

        charT * const mText;             
        charT * mScheme; unsigned mSchemeLen;
        charT * mAuth;   unsigned mAuthLen;
        charT * mPath;   unsigned mPathLen;
        charT * mQuery;  unsigned mQueryLen;
        charT * mFrag;   unsigned mFragLen;
        SchemeT mSchemeT;

        // helper functions
        static unsigned strLen( const charT * const aString )
        {
            unsigned size = 0;
            const charT * c = aString; 
            while( *c != 0 ) { ++c; ++size; }
            return size;
        };
        static void strCopy( charT * const aDst, const charT * const aSrc, const unsigned aNumChars )
        {
            memcpy( aDst, aSrc, aNumChars * sizeof( charT ) );
        };
        static void strCopy( charT * const aDst, const charT * const aSrc )
        {
            unsigned size = strLen( aSrc ) + 1;
            memcpy( aDst, aSrc, size * sizeof( charT ) );
        };
        static charT * strDup( const charT * const aSrc )
        {
            const unsigned size = strLen( aSrc ) + 1;
            charT * const result = new charT[ size ];
            memcpy( result, aSrc, size * sizeof( charT ) );
            return result;
        };

        // if different, returns index of first diff, -1 else
        static int strCmp( const charT * aFirst, const charT * aSecond, const unsigned aNumChars )
        {
            for( unsigned i = 0; i < aNumChars; ++i )
            {
                if( *(aFirst++) != *(aSecond++) ) { return i; }
            }
            return -1;
        };
        static int strCmp( const charT * aFirst, const charT * aSecond )
        {
            for( unsigned i = 0; *aFirst != 0; ++i )
            {
                if( *(aFirst++) != *(aSecond++) ) { return i; }
            }
            return -1;
        };

        static bool isOneOf( const charT aChar, const charT* const aCharSet )
        {
            const charT * c = aCharSet;
            if( *c == 0 && aChar == 0 ) { return true; }
            for( ++c; *c != 0; ++c ) {
                if( aChar == *c ) { return true; }
            }
            return false;
        };

    private:
        Rep()
        { 
            assert( 0 ); 
        }

        ~Rep()
        {
            delete [] mText;
        };

        unsigned mRef;
    };
};

// accessors (all const getters, this is an immutable class!)

template< class charT, class stringT >
const charT * URI_< charT, stringT >::getText() const {
  return mRep->mText;
}

template< class charT, class stringT >
stringT URI_< charT, stringT >::toString() const {
  return stringT( mRep->mText );
}

template< class charT, class stringT >
stringT URI_< charT, stringT >::getScheme() const { 
  return stringT( mRep->mScheme, mRep->mSchemeLen );
}

template< class charT, class stringT >
stringT URI_< charT, stringT >::getAuthority() const { 
  return stringT( mRep->mAuth, mRep->mAuthLen ); 
}

template< class charT, class stringT >
stringT URI_< charT, stringT >::getPath() const { 
  return stringT( mRep->mPath, mRep->mPathLen ); 
}

template< class charT, class stringT >
stringT URI_< charT, stringT >::getQuery() const { 
  return stringT( mRep->mQuery, mRep->mQueryLen ); 
}

template< class charT, class stringT >
stringT URI_< charT, stringT >::getFragment() const { 
  return stringT( mRep->mFrag, mRep->mFragLen ); 
}

template< class charT, class stringT >
URI_< charT, stringT >::SchemeT URI_< charT, stringT >::getSchemeT() const { 
  return mRep->mSchemeT; 
}


template< class charT, class stringT >
const charT * const 
URI_< charT, stringT >::SCHEME_CONST[ URI_< charT, stringT >::SCHEME_NUM ] = {
  "file", "http", "https", "ftp"
};

template< class charT, class stringT >
const charT * const 
URI_< charT, stringT >::DEFAULT_PORT[ URI_< charT, stringT >::SCHEME_NUM ] = { 
  "0", "80", "443", "21"
};

template< class charT, class stringT >
const URI_< charT, stringT > 
URI_< charT, stringT >::EMPTY_URI = URI_< charT, stringT >( "" );


// ctors, dtors


template< class charT, class stringT >
URI_< charT, stringT >::URI_()
{
  mRep = EMPTY_URI.mRep;
  mRep->acquire();
}

template< class charT, class stringT >
URI_< charT, stringT >::URI_( const charT * aString, 
                              bool aAdoptBuffer ) 
{
  mRep = new Rep( aString, aAdoptBuffer );
  mRep->parse();
  mRep->acquire();
}

template< class charT, class stringT >
URI_< charT, stringT >::URI_( const stringT & aString ) {
  mRep = new Rep( aString.c_str(), false );
  mRep->parse();
  mRep->acquire();
}

template< class charT, class stringT >
URI_< charT, stringT >::URI_( const URI_ & aOther ) {
  mRep = aOther.mRep;
  mRep->acquire();
}

template< class charT, class stringT >
URI_< charT, stringT >::URI_( Rep * aOther ) {
  mRep = aOther;
  mRep->acquire();
}

template< class charT, class stringT >
URI_< charT, stringT >::~URI_() { 
  mRep->release();
}

template< class charT, class stringT >
bool URI_< charT, stringT >::operator==( const charT * const aText ) const {
  return *mRep == aText;
}

template< class charT, class stringT >
bool URI_< charT, stringT >::operator==( const stringT & aText ) const {
  return *mRep == aText.c_str();
}

template< class charT, class stringT >
bool URI_< charT, stringT >::operator==( const URI_ & aOther ) const {
  return *mRep == aOther.mRep;
}

template< class charT, class stringT >
bool URI_< charT, stringT >::operator!=( const charT * const aText ) const {
  return !(*mRep == aText);
}

template< class charT, class stringT >
bool URI_< charT, stringT >::operator!=( const stringT & aText ) const {
  return !(*mRep == aText.c_str());
}

template< class charT, class stringT >
bool URI_< charT, stringT >::operator!=( const URI_ & aOther ) const {
  return !(*mRep == aOther.mRep);
}

template< class charT, class stringT >
void URI_< charT, stringT >::operator=( const charT * const aText ) {
  mRep->release();
  mRep = new Rep( aText, false );
  mRep->parse();
  mRep->acquire();
}

template< class charT, class stringT >
void URI_< charT, stringT >::operator=( const stringT & aText ) {
  mRep->release();
  mRep = new Rep( aText.c_str(), false );
  mRep->parse();
  mRep->acquire();
}

template< class charT, class stringT >
void URI_< charT, stringT >::operator=( const URI_ & aOther ) {
  mRep->release();
  mRep = aOther.mRep;
  mRep->acquire();
}

template< class charT, class stringT >
bool URI_< charT, stringT >::isRelative() const { 
  return ( mRep->mSchemeLen + mRep->mAuthLen ) == 0;
}

template< class charT, class stringT >
bool URI_< charT, stringT >::hasPrefix( const URI_ & aBase ) const {
  const charT * base = aBase.mRep->mText;
  int res = Rep::strCmp( base, mRep->mText );
  return res < 0 || base[ res ] == 0;
}

template< class charT, class stringT >
URI_< charT, stringT >
URI_< charT, stringT >::makeRelative( const URI_ & aBase ) const {

  if( isRelative() ) {
    throw domain_error( "URI::makeRelative() called on a relative URI" );
  }

  if( aBase.isRelative() ) {
    throw domain_error( "Base URI supplied to URI::makeRelative() "
                        "must be absolute" );
  }

  Rep * newRep = mRep->makeRelative( aBase.mRep );
  URI result = URI_( newRep );
  return result;
}


template< class charT, class stringT >
URI_< charT, stringT >
URI_< charT, stringT >::makeAbsolute( const URI_ & aBase ) const
{
  if( ! isRelative() ) {
      std::cerr << "URI::makeAbsolute() called on an absolute URI" << std::endl;
  }

  if( aBase.isRelative() ) {
      std::cerr <<  "Base URI supplied to URI::makeAbsolute() must be absolute" << std::endl;
  }

  return URI_( mRep->makeAbsolute( aBase.mRep ) );
}


// TODO: implement this natively
template< class charT, class stringT >
URI_< charT, stringT > URI_< charT, stringT >::makeRelAbs(
  const URI_ & aSrcBase, 
  const URI_ & aDstBase ) const
{
  return makeRelative( aSrcBase ).makeAbsolute( aDstBase );
}

// TODO: implement this natively
template< class charT, class stringT >
URI_< charT, stringT > URI_< charT, stringT >::makeAbsRel(
  const URI_ & aSrcBase, 
  const URI_ & aDstBase ) const
{
  return makeAbsolute( aSrcBase ).makeRelative( aDstBase );
}


#endif // __URI_H__
