#ifndef ___qedo_orbacus_h__
#define ___qedo_orbacus_h__

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4010100L)
#       error ORBacus version mismatch!
#   endif
#endif

namespace Components
{
	namespace OBNative_Components
	{
		typedef void * (*x) (void*);
		typedef x Function;
		typedef void* FunctionData;
	};
};

namespace StreamComponents
{
	namespace OBNative_StreamComponents
	{
		typedef void * BufferPtr;
	};
};

#endif
