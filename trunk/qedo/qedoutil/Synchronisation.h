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


#ifdef WIN32
#ifndef TAO_ORB
#include <windows.h>
#endif
#else
#include <pthread.h>
#include <signal.h>
#endif

#include "Util.h"

namespace Qedo {
class qedo_lock;

class CONTAINERDLL_API qedo_mutex {

	friend class qedo_lock;
        friend class qedo_cond;

private:

#ifdef WIN32
	HANDLE m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif

public:
	qedo_mutex();
	~qedo_mutex();

	void qedo_lock_object();

	void qedo_unlock_object();
};

class CONTAINERDLL_API qedo_lock {
private:
	qedo_mutex* m_mutex;

public:
	qedo_lock(const qedo_mutex* m);
	qedo_lock(qedo_mutex* m);
	~qedo_lock();
};

class CONTAINERDLL_API qedo_cond {

private:
#ifdef WIN32
	HANDLE m_event_handle;

#else
	pthread_cond_t m_cond;
#endif
public:
	qedo_cond();
	qedo_cond (char* sig_name);
	~qedo_cond();

	void qedo_wait();

	void qedo_signal();
};


#ifdef WIN32
DWORD WINAPI startFunc(LPVOID p);
#else
extern "C" void* startFunc(void* p);
#endif

void
qedo_startDetachedThread(void* (*p)(void*), void* arg);

struct t_start {
	void* (*p)(void*);
	void* a;
};

} // name space Qedo

#endif