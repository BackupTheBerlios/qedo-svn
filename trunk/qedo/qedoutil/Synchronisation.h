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

#ifndef __THREADS_H__
#define __THREADS_H__


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



#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class QedoLock;

struct MutexDelegate;

/**
 * a mutex for Qedo
 */
class CONTAINERDLL_API QedoMutex 
{
	/** makes use of this */
	friend class QedoLock;
	/** makes use of this */
	friend class QedoCond;

private:

	/** the mutex */
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
	 * lock an object
	 */
	void lock_object();

	/**
	 * unlock an object
	 */
	void unlock_object();
};


/**
 * a lock for Qedo
 */
class CONTAINERDLL_API QedoLock
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
 * bla
 */
class CONTAINERDLL_API QedoCond
{

private:
	/// bla
	struct CondDelegate* delegate_;

public:
	/**
	 * constructor
	 */
	QedoCond();

	/**
	 * constructor
	 */
	QedoCond (char*);

	/**
	 * destructor
	 */
	~QedoCond();

	/**
	 * wait
	 */
	void wait (const QedoMutex&);

	/**
	 * wait
	 */
	void wait (const QedoMutex*);

	/**
	 * wait
	 */
	bool wait_timed (const QedoMutex&, unsigned long );

	/**
	 * wait_timed
	 */
	bool wait_timed (const QedoMutex*, unsigned long );

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
 * a read/write mutex for Qedo
 */
class CONTAINERDLL_API QedoReadWriteMutex : private QedoMutex
{
	/** makes use of this */
	friend class QedoLock;
	/** makes use of this */
	friend class QedoCond;

private:

	/** the mutex */
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
	 * read lock an object
	 */
	void read_lock_object();

	/**
	 * write lock an object
	 */
	void write_lock_object();

	/**
	 * unlock an object
	 */
	void unlock_object();
};

struct ThreadDelegate;

class CONTAINERDLL_API QedoThread {
	public:
	ThreadDelegate *delegate_;
	QedoThread();
	void stop();
	void join();
};

/**
 * add comment!
 */
#ifdef QEDO_WINTHREAD
DWORD WINAPI startFunc(LPVOID p);
#else
extern "C" void* startFunc(void* p);
#endif


/**
 * add comment!
 */
CONTAINERDLL_API QedoThread*
qedo_startDetachedThread(void* (*p)(void*), void* arg);


struct T_Start 
{
	void* (*p)(void*);
	void* a;
};


/** @} */

} // name space Qedo

#endif
