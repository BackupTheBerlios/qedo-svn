/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
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

#ifndef __SYNCHRONISATION_H__
#define __SYNCHRONISATION_H__


#undef QEDO_WINTHREAD
#undef QEDO_PTHREAD

#ifdef MICO_ORB
#define QEDO_PTHREAD
#elif defined _WIN32
#define QEDO_WINTHREAD
#else
#define QEDO_PTHREAD
#endif

#ifdef _WIN32
#ifndef TAO_ORB
#include <windows.h>
#endif
#endif



#include "qedoutil.h"


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


class QedoLock;

struct MutexDelegate;

/**
 * This is a mutex implementation based on pthread mutex or  WIN32 mutex.
 */
class QEDOUTIL_API QedoMutex 
{
	/** makes use of this */
	friend class QedoLock;
	/** makes use of this */
	friend class QedoCond;

private:

	/**
	 * implementation detail data
	 */
	struct MutexDelegate* delegate_;

public:
	/**
	 * constructor
	 */
	QedoMutex();

	/**
	 * destructor
	 */
	~QedoMutex();

	/**
	 * lock the mutex
	 */
	void lock_object();

	/**
	 * unlock the mutex
	 */
	void unlock_object();
};


/**
 * This is a auto lock implementation based on pthread mutex or WIN32 mutex.
 */
class QEDOUTIL_API QedoLock
{
private:
	/** the qedo mutex */
	QedoMutex* mutex_;

public:
	/**
	 * constructor
	 * \param m The qedo mutex.
	 */
	QedoLock (const QedoMutex*);

	/**
	 * constructor
	 * \param m The qedo mutex.
	 */
	QedoLock (QedoMutex*);

	/**
	 * constructor
	 * \param m The qedo mutex.
	 */
	QedoLock (const QedoMutex&);

	/**
	 * destructor
	 */
	~QedoLock();
};


struct CondDelegate;
/**
 * This is a conditional variable implementation based on pthread conditional or WIN32 events.
 */
class QEDOUTIL_API QedoCond
{

private:
	/**
	 * implementation detail data
	 */
	struct CondDelegate* delegate_;

public:
	/**
	 * constructor
	 */
	QedoCond();

	/**
	 * constructor
	 * \param name is a name for the conditional varaibale
	 */
	QedoCond (char* name);

	/**
	 * destructor
	 */
	~QedoCond();

	/**
	 * wait for a signal on the conditional variable
	 * \param m the mutex associated to this variable
	 */
	void wait (const QedoMutex& m);

	/**
	 * wait for a signal on the conditional variable
	 * \param m the mutex associated to this variable
	 */
	void wait (const QedoMutex* m);

	/**
	 * wait for a signal on the conditional variable or return after timeout
	 * \param m the mutex associated to this variable
	 * \param timeout amount of time to wait in miliseconds
	 */
	bool wait_timed (const QedoMutex& m, unsigned long timeout);

	/**
	 * wait for a signal on the conditional variable or return after timeout
	 * \param m the mutex associated to this variable
	 * \param timeout amount of time to wait in miliseconds
	 */
	bool wait_timed (const QedoMutex* m, unsigned long timeout);

	/**
	 * unblocks at least one of the threads that are blocked on condition variable
	 */
	void signal();

#ifndef QEDO_WINTHREAD
	/**
	 * unblocks all threads currently blocked on the condition variable
	 */

	void broadcast();
#endif
};

struct ReadWriteMutexDelegate;

/**
 *  This is a read/write mutex based on normal mutex
 */
class QEDOUTIL_API QedoReadWriteMutex : private QedoMutex
{

private:

	/**
	 * implementation detail data
	 */
	struct ReadWriteMutexDelegate* rwdelegate_;

public:
	/**
	 * constructor
	 */
	QedoReadWriteMutex();

	/**
	 * destructor
	 */
	~QedoReadWriteMutex();

	/**
	 * get a read lock for the mutex
	 */
	void read_lock_object();

	/**
	 * get the exclusive write lock for the mutex
	 */
	void write_lock_object();

	/**
	 * unlock the mutex
	 */
	void unlock_object();
};

/**
 * This is a auto read lock implementation based on QedoReadWriteMutex.
 */
class QEDOUTIL_API QedoReadLock
{
private:
	/** the qedo mutex */
	QedoReadWriteMutex* rw_mutex_;

public:
	/**
	 * constructor
	 * \param m The qedo read write mutex.
	 */
	QedoReadLock (const QedoReadWriteMutex*);

	/**
	 * constructor
	 * \param m The qedo read write mutex.
	 */
	QedoReadLock (QedoReadWriteMutex*);

	/**
	 * constructor
	 * \param m The qedo read write mutex.
	 */
	QedoReadLock (const QedoReadWriteMutex&);

	/**
	 * destructor
	 */
	~QedoReadLock();
};

/**
 * This is a auto write lock implementation based on QedoReadWriteMutex.
 */
class QEDOUTIL_API QedoWriteLock
{
private:
	/** the qedo mutex */
	QedoReadWriteMutex* rw_mutex_;

public:
	/**
	 * constructor
	 * \param m The qedo read write mutex.
	 */
	QedoWriteLock (const QedoReadWriteMutex*);

	/**
	 * constructor
	 * \param m The qedo read write mutex.
	 */
	QedoWriteLock (QedoReadWriteMutex*);

	/**
	 * constructor
	 * \param m The qedo read write mutex.
	 */
	QedoWriteLock (const QedoReadWriteMutex&);

	/**
	 * destructor
	 */
	~QedoWriteLock();
};


struct ThreadDelegate;

/**
 * This is a thread abstraction class implementation
 */
class QEDOUTIL_API QedoThread {
	public:
	/**
	 * implementation detail data
	 */
	ThreadDelegate *delegate_;

	/**
	 * constructor
	 */
	QedoThread();

	/**
	 * destructor
	 */
	~QedoThread();

	/**
	 * stop and terminat the thread (deprecated)
	 */
	void stop();

	/**
	 * wait for termination of this thread
	 */
	void join();
};

/**
 * helper function for thread creation
 */
#ifdef QEDO_WINTHREAD
DWORD WINAPI startFunc(LPVOID p);
#else
extern "C" void* startFunc(void* p);
#endif


/**
 * helper function for thread creation
 */
QEDOUTIL_API QedoThread*
qedo_startDetachedThread(void* (*p)(void*), void* arg);


/** @} */

} // name space Qedo

#endif
