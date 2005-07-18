#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <list>
using namespace std;
namespace CCMGenerator
{
	struct Exception 
	{
		const char * _kind;
		const char * _reason;
		char * _context; // To be able to asign context later
		char * _element; // To be able to asign context later
		Exception ( const char * kind, const char * reason, const char * context, const char* element = 0 );
		Exception ( Exception& e); // Exceptions will be copied for later presentation
		//operator= (Exception& e);
		~Exception();

		const char * kind ();
		const char * reason ();
		const char * context ();
		const char * element ();
		void context ( const char * );
		void element ( const char * );
	};

	typedef list<Exception * > ExceptionList;

	struct Semantic : Exception 
	{
		Semantic ( const char * reason, const char * element );
	};

	struct Generation : Exception
	{
		Generation ( const char * reason, const char * context );
	};

	struct RepositoryException : Exception
	{
		RepositoryException ( const char * reason, const char* element );
	};

	struct NilObjectRef : RepositoryException
	{
		NilObjectRef ( const char * exception )
			: RepositoryException ( exception, ""  )
		{}
	};
	struct SystemException : RepositoryException
	{
		SystemException (const char* exception) 
		:	RepositoryException ( exception, "" ) 
		{
		}
	};

	struct ReferenceRepositoryFileNotFound : RepositoryException
	{
		ReferenceRepositoryFileNotFound (const char* exception) 
		:	RepositoryException ( exception, "" ) 
		{
		}
	};

	struct NotFoundInRep : RepositoryException
	{
		NotFoundInRep ( const char* exception, const char* name ) 
		:	RepositoryException ( exception, name ) 
		{
		}
	};
}
#endif