#include <CORBA.h>
#include <mico/throw.h>

#ifndef __QEDO_MICO_H__
#define __QEDO_MICO_H__

namespace Components {
	typedef void * (*x) (void*);
	typedef x MICO_Native_Components_Function;
	typedef void * MICO_Native_Components_FunctionData;
};

#endif // __QEDO_MICO_H__
