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
Revision 1.6  2003/11/18 11:48:54  boehme
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


#include <string>    // for template instantiation
#include <cassert>




class URI {

public:

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
  URI();

  /*
  Construct a URI from an existing null-terminated character buffer.
  bool aAdoptBuffer: if true, the URI assumes ownership of the buffer and does 
                     not allocate new memory; the content of the buffer may
                     change due to URI normalization
  */
  URI( const char * const aString,
        bool aAdoptBuffer = false );

  /*
  Same as above, but since strings tend to want to own their buffers, this
  constructor does not allow adoption.
  */
  URI( const std::string & aString );

  /*
  Copy constructor. Since the underlying Rep is not copied, this is a very
  lightweight operation, so URIs can be passed around "by value"
  */
  URI( const URI & aOther );


  virtual ~URI();


  /*
  Returns a pointer to the normalized, null terminated URI buffer, involves
  no processing
  */
  const char * getText() const;


  /*
  These accessors return various parts of the URI as strings; direct buffer
  access is not possible because the parts themselves are not null terminated
  */
  std::string toString() const;
  std::string getScheme() const;
  std::string getAuthority() const;
  std::string getPath() const;
  std::string getQuery() const;
  std::string getFragment() const;


  /*
  Return the scheme (file, http, ftp etc.) of the URI; returns SCHEME_OTHER
  if the scheme was present, but not one of "http", "https", "ftp" or "file";
  returns SCHEME_EMPTY if the scheme was empty or none was given
  */
  SchemeT getSchemeT() const;


  /*
  Checks if another URI points to the same document
  */
  bool operator==( const char * const aText ) const;
  bool operator==( const std::string & aText ) const;
  bool operator==( const URI & aOther ) const;

  bool operator!=( const char * const aText ) const;
  bool operator!=( const std::string & aText ) const;
  bool operator!=( const URI & aOther ) const;

  void operator=( const char * const aText );
  void operator=( const std::string & aText );
  void operator=( const URI & aOther );


  /*
  Trivial ...
  */
  bool isRelative() const;


  /*
  Checks if a URI is prefixed by another
  */
  bool hasPrefix( const URI & aBase ) const;


  /*
  Returns a new relative URI such that base + result == this; if base differs
  from this in its scheme or authority part, this URI is returned unchanged;
  throws an exception if either base or this is relative
  */
  URI makeRelative( const URI & aBase ) const;


  /*
  Returns a new absolute URI such that base + this == result;
  throws an exception if either base is relative or this is absolute
  */
  URI makeAbsolute( const URI & aBase ) const;


  /*
  Convenience method equivalent to, but potentially more efficient than
  makeRelative( aSrcBase ).makeAbsolute( aDstBase ); this is useful for
  pruning a URI in one tree by removing its base, and grafting it into
  another tree with a new base
  */
  URI makeRelAbs( const URI & aSrcBase, const URI & aDstBase ) const;

  /*
  Convenience method equivalent to, but potentially more efficient than
  makeAbsolute( aSrcBase ).makeRelative( aDstBase ); this is useful for
  moving a relative link from one base to another, and still have it point
  to the same place
  */
  URI makeAbsRel( const URI & aSrcBase, const URI & aDstBase ) const;


  /******  User documentation ends here, proceed at your own peril :-)  *******/


#if 0
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
#endif

private:
    // inner Representation class (defined later)
    class Rep;

    // ctor
    URI( Rep * aOther );

    // class members
    Rep * mRep;

public:
    // class constants
    static const char * const SCHEME_CONST[ SCHEME_NUM ];
    static const char * const DEFAULT_PORT[ SCHEME_NUM ];
    static const URI EMPTY_URI;

private:
    class Rep {

    public:
		 int nr;
		 static int cnt;
        Rep( const char * aText, bool aAdoptBuffer );

        // "operators"
        bool operator==( const Rep * aOther ) const ;
        
        bool operator==( const char * aText ) const ;

        // transformations
        void parse() ;
        
        Rep * makeRelative( const Rep * bRep ) const ;

        Rep * makeAbsolute( const Rep * bRep ) const ;

        // reference counting
        unsigned getRef() const ;
        void acquire() ;
        void release() ;

        char * const mText;             
        char * mScheme; unsigned mSchemeLen;
        char * mAuth;   unsigned mAuthLen;
        char * mPath;   unsigned mPathLen;
        char * mQuery;  unsigned mQueryLen;
        char * mFrag;   unsigned mFragLen;
        SchemeT mSchemeT;

        // helper functions
        static unsigned strLen( const char * const aString ) ;
        static void strCopy( char * const aDst, const char * const aSrc, const unsigned aNumChars ) ;
        static void strCopy( char * const aDst, const char * const aSrc ) ;
        static char * strDup( const char * const aSrc ) ;

        // if different, returns index of first diff, -1 else
        static int strCmp( const char * aFirst, const char * aSecond, const unsigned aNumChars ) ;
        static int strCmp( const char * aFirst, const char * aSecond ) ;

        static bool isOneOf( const char aChar, const char* const aCharSet ) ;

    private:
        Rep()
        { 
            assert( 0 ); 
        }

        ~Rep() ;

        unsigned mRef;
    };
};

#endif // __URI_H__
