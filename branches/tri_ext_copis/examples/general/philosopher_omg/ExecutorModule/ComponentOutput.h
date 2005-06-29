//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: ComponentOutput.h,v 1.1 2002/10/30 23:13:58 tom Exp $
//

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <JTC/JTC.h>

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include <iostream>

using namespace std;

namespace dinner_Implementation {


extern JTCMonitor* component_monitor;


#define WITH_PID_OUT(x) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cout << "[" << getpid() << "]: " << x << endl; \
}


#define WITH_PID_OUT2(x,y) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cout << "[" << getpid() << "]: " << x << y << endl; \
}


#define WITH_PID_OUT3(x,y,z) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cout << "[" << getpid() << "]: " << x << y << z << endl; \
}


#define WITH_PID_ERR(x) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cerr << "[" << getpid() << "]: " << x << endl; \
}


#define WITH_PID_ERR2(x,y) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cerr << "[" << getpid() << "]: " << x << y << endl; \
}


#define WITH_PID_ERR3(x,y,z) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cerr << "[" << getpid() << "]: " << x << y << z << endl; \
}


// Debug stuff
#define DEBUG_WITH_PID_OUT(x) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cerr << "[" << getpid() << "]: " << x << endl; \
}


#define DEBUG_WITH_PID_OUT2(x,y) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cerr << "[" << getpid() << "]: " << x << y << endl; \
}


#define DEBUG_WITH_PID_OUT3(x,y,z) \
{ \
	JTCSynchronized synchronized ( *dinner_Implementation::component_monitor ); \
	cerr << "[" << getpid() << "]: " << x << y << z << endl; \
}


} // namespace dinner_Implementation

#endif

