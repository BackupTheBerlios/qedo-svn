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

#ifdef QEDO_PTHREAD
#include <pthread.h>
#include <signal.h>
#endif

#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


class qedo_lock;


/**
 * a mutex for Qedo
 */
class CONTAINERDLL_API qedo_mutex {

	/** makes use of this */
	friend class qedo_lock;
	/** makes use of this */
	friend class qedo_cond;

private:

	/** the mutex */
#ifdef QEDO_WINTHREAD
	HANDLE m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif

public:
	/**
	 * constructor
	 */
	qedo_mutex();

	/**
	 * destructor
	 */
	~qedo_mutex();

	/**
	 * lock an object
	 */
	void qedo_lock_object();

	/**
	 * unlock an object
	 */
	void qedo_unlock_object();
};


/**
 * a lock for Qedo
 */
class CONTAINERDLL_API qedo_lock
{
private:
	/** the qedo mutex */
	qedo_mutex* m_mutex;

public:
	/**
	 * constructor
	 * \param m The qedo mutex.
	 */
	qedo_lock(const qedo_mutex* m);

	/**
	 * constructor
	 * \param m The qedo mutex.
	 */
	qedo_lock(qedo_mutex* m);

	/**
	 * destructor
	 */
	~qedo_lock();
};


/**
 * bla
 */
class CONTAINERDLL_API qedo_cond
{

private:
	/// bla
#ifdef QEDO_WINTHREAD
	HANDLE m_event_handle;
#else
	pthread_cond_t m_cond;
#endif

public:
	/**
	 * constructor
	 */
	qedo_cond();

	/**
	 * constructor
	 * \param sig_name
	 */
	qedo_cond (char* sig_name);

	/**
	 * destructor
	 */
	~qedo_cond();

	/**
	 * wait
	 */
	void qedo_wait();

	/**
	 * insert comments
	 */
	void qedo_signal();

	/**
	 * insert comments
	 */
	void qedo_reset();
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
void
qedo_startDetachedThread(void* (*p)(void*), void* arg);


struct t_start {
	void* (*p)(void*);
	void* a;
};


/** @} */

} // name space Qedo

#endif
