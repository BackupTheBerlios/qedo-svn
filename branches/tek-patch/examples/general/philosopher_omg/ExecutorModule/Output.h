//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: Output.h,v 1.1 2002/10/30 23:13:58 tom Exp $
//

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#ifndef WIN32
#include CORBA_H
#endif

#if defined(HAVE_JTC) || defined(WIN32)
#include <JTC/JTC.h>
#else
#ifdef HAVE_PTHREAD_H
// if have to check for MICO and threads
#include  "mico/os-thread.h"
#else
#error No threads configured
#endif /* HAVE_PTHREAD_H */
#endif /* HAVE_JTC */

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif

#include <iostream>

using namespace std;


namespace HU_CCM_Container {


#if defined(HAVE_JTC) || defined(WIN32)
extern JTCMonitor* container_monitor;
typedef JTCMonitor Monitor;
typedef JTCSynchronized Synchronized;

#else
#ifdef HAVE_PTHREAD_H
// if have to check for MICO and threads
extern MICOMT::Mutex* container_monitor;
typedef MICOMT::Mutex Monitor;

class Synchronized {
	MICOMT::Mutex& mutex;
public:
	Synchronized(MICOMT::Mutex& m) : mutex(m) { mutex.lock(); }
	~Synchronized() { mutex.unlock(); }
};
#endif /* HAVE_PTHREAD_H */
#endif /* HAVE_JTC */

#define SYNC_WITH_CONTAINER  \
	HU_CCM_Container::Synchronized synchronized ( *HU_CCM_Container::container_monitor );

#define NORMAL_OUT(x) \
{ \
	SYNC_WITH_CONTAINER \
	cout << x << endl; \
}


#define NORMAL_OUT2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	cout << x << y << endl; \
}


#define NORMAL_OUT3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	cout << x << y << z << endl; \
}


#define NORMAL_ERR(x) \
{ \
	SYNC_WITH_CONTAINER \
	cerr << x << endl; \
}


#define NORMAL_ERR2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	cerr << x << y << endl; \
}


#define NORMAL_ERR3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	cerr << x << y << z << endl; \
}


#define WITH_PID_OUT(x) \
{ \
	SYNC_WITH_CONTAINER \
	cout << "[" << getpid() << "]: " << x << endl; \
}


#define WITH_PID_OUT2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	cout << "[" << getpid() << "]: " << x << y << endl; \
}


#define WITH_PID_OUT3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	cout << "[" << getpid() << "]: " << x << y << z << endl; \
}


#define WITH_PID_ERR(x) \
{ \
	SYNC_WITH_CONTAINER \
	cerr << "[" << getpid() << "]: " << x << endl; \
}


#define WITH_PID_ERR2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	cerr << "[" << getpid() << "]: " << x << y << endl; \
}


#define WITH_PID_ERR3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	cerr << "[" << getpid() << "]: " << x << y << z << endl; \
}


// Debug stuff
#define DEBUG_OUT(x) \
{ \
	SYNC_WITH_CONTAINER \
	cout << x << endl; \
}


#define DEBUG_OUT2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	cout << x << y << endl; \
}


#define DEBUG_OUT3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	cout << x << y << z << endl; \
}


#define DEBUG_WITH_PID_OUT(x) \
{ \
	SYNC_WITH_CONTAINER \
	cout << "[" << getpid() << "]: " << x << endl; \
}


#define DEBUG_WITH_PID_OUT2(x,y) \
{ \
	SYNC_WITH_CONTAINER \
	cout << "[" << getpid() << "]: " << x << y << endl; \
}


#define DEBUG_WITH_PID_OUT3(x,y,z) \
{ \
	SYNC_WITH_CONTAINER \
	cout << "[" << getpid() << "]: " << x << y << z << endl; \
}


} // namespace HU_CCM_Container

#endif

