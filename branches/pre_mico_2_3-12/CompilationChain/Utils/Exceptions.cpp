
//#include "stdafx.h"
#include <iostream>
using namespace std;
#include "Exceptions.h"

namespace CCMGenerator
{

	Exception::Exception ( const char * kind, const char * reason, const char * context, const char* element )
	: _kind ( kind ), _reason ( reason )
	{
		if (context)
		{
			_context = new char [strlen( context) +1];
			strcpy ( _context, context);
		}
		else
			_context = 0;

		if (element)
		{
			_element = new char [strlen( element) +1];
			strcpy ( _element, element);
		}
		else
			_element = 0;
	}

	Exception::Exception( Exception& e)
	: _kind (e.kind()), _reason(e.reason())
	{
		if (e.context())
		{
			_context = new char [strlen( e.context()) +1];
			strcpy ( _context, e.context());
		}
		else
			_context = 0;

		if ( e.element() )
		{
			_element = new char [strlen( e.element()) +1];
			strcpy ( _element, e.element());
		}
		else
			_element = 0;
	}

	/*Exception::operator=(Exception& e)
	{
		this->_kind = e.kind();
		this->_reason = e.reason();

		if (this->context())
			delete _context;
		if (e.context())
		{
			this->_context = new char [strlen( e.context()) +1];
			strcpy ( this->_context, e.context());
		}
		else
			this->_context = 0;

		if (this->element())
			delete _element;
		if (e.element())
		{
			_element = new char [strlen( e.element()) +1];
			strcpy ( _element, e.element());
		}
		else
			_element = 0;
	}*/

	Exception::~Exception()
	{
		if (_context) delete _context;
		if (_element) delete _element;
	}

	const char * Exception::kind ()
	{
		return _kind;
	}

	const char * Exception::reason ()
	{
		if ( _reason )
			return _reason;
		return "";
	}

	const char * Exception::context ()
	{
		if ( _context )
			return _context;
		return "";
	}

	const char * Exception::element ()
	{
		if ( _element )
			return _element;
		return "";
	}

	void Exception::context (const char * context)
	{
		if (this->context())
			delete _context;
		if (context)
		{
			this->_context = new char [strlen( context ) +1];
			strcpy ( this->_context, context );
		}
		else
			this->_context = 0;
	}

	void Exception::element (const char * element)
	{
		if (this->element())
			delete _element;
		if (element)
		{
			this->_context = new char [strlen( element ) +1];
			strcpy ( this->_element, element );
		}
		else
			this->_context = 0;
	}

	Semantic::Semantic ( const char * reason, const char * context )
	: Exception ( "Semantic", reason, context )
	{}

	Generation::Generation ( const char * reason, const char * context )
	: Exception ( "Code Generation", reason, context )
	{}

	RepositoryException::RepositoryException ( const char * reason, const char* element )
	: Exception ( "Repository", reason, element )
	{}
}