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

#include "Synchronisation.h"

#ifdef QEDO_PTHREAD
#include <pthread.h>
#include <signal.h>
#endif

static char rcsid[] UNUSED = "$Id: Synchronisation.cpp,v 1.14 2003/08/05 14:21:50 boehme Exp $";

namespace Qedo {

struct mutex_delegate {
#ifdef QEDO_WINTHREAD
	HANDLE m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif
};

struct cond_delegate {
#ifdef QEDO_WINTHREAD
	HANDLE m_event_handle;
#else
	pthread_cond_t m_cond;
#endif
};

qedo_mutex::qedo_mutex() {
    delegate = new mutex_delegate;
#ifdef QEDO_WINTHREAD
	delegate->m_mutex = CreateMutex(NULL,FALSE,NULL);
#else
	pthread_mutex_init(&(delegate->m_mutex), NULL);
#endif
}


qedo_mutex::~qedo_mutex() {

#ifdef QEDO_WINTHREAD
#else
	pthread_mutex_destroy(&(delegate->m_mutex));
#endif
	delete delegate;
}


void
qedo_mutex::qedo_lock_object() {

#ifdef QEDO_WINTHREAD
	WaitForSingleObject(delegate->m_mutex, INFINITE);
#else
	pthread_mutex_lock(&(delegate->m_mutex));
#endif
}


void
qedo_mutex::qedo_unlock_object() {

#ifdef QEDO_WINTHREAD
	ReleaseMutex(delegate->m_mutex);
#else
	pthread_mutex_unlock(&(delegate->m_mutex));
#endif
}


qedo_lock::qedo_lock(const qedo_mutex* m) {
	m_mutex = const_cast<qedo_mutex* const>(m);
	m_mutex->qedo_lock_object();
}

qedo_lock::qedo_lock(qedo_mutex* m) {
	m_mutex = m;
	m_mutex->qedo_lock_object();
}

qedo_lock::qedo_lock(const qedo_mutex& m) {
	m_mutex = const_cast<qedo_mutex* const>(&m);
	m_mutex->qedo_lock_object();
}


qedo_lock::~qedo_lock() {
	m_mutex->qedo_unlock_object();
}


qedo_cond::qedo_cond() {
	delegate = new cond_delegate;
#ifdef QEDO_WINTHREAD
		delegate->m_event_handle = CreateEvent (0, FALSE /*manua-reset*/, FALSE
		/*initial: non-signaled*/, 0);
#else
		pthread_cond_init(&(delegate->m_cond), 0);
#endif
}

qedo_cond::qedo_cond(char * sig_name) {
	delegate = new cond_delegate;
#ifdef QEDO_WINTHREAD
		delegate->m_event_handle = CreateEvent (0, FALSE /*manua-reset*/, FALSE /*initial: non-signaled*/, sig_name);
#else
		pthread_cond_init(&(delegate->m_cond), 0);
#endif
}


qedo_cond::~qedo_cond() {
#ifdef QEDO_WINTHREAD
#else
	pthread_cond_destroy(&(delegate->m_cond));
#endif
	delete delegate;
}


void
qedo_cond::qedo_wait(const qedo_mutex& m) {

#ifdef QEDO_WINTHREAD
	m.qedo_unlock_object();
	WaitForMultipleObjects(1, &(delegate->m_event_handle), TRUE, INFINITE /*wait for ever*/);
	m.qedo_lock_object();
#else
	pthread_cond_wait(&(delegate->m_cond),&(m.delegate->m_mutex));
#endif
}

void
qedo_cond::qedo_wait(const qedo_mutex* m) {

#ifdef QEDO_WINTHREAD
	m.qedo_unlock_object();
	WaitForMultipleObjects(1, &(delegate->m_event_handle), TRUE, INFINITE /*wait for ever*/);
	m.qedo_lock_object();
#else
	pthread_cond_wait(&(delegate->m_cond),&(m->delegate->m_mutex));
#endif
}


void
qedo_cond::qedo_signal() {

#ifdef QEDO_WINTHREAD
	SetEvent(delegate->m_event_handle);
#else
	pthread_cond_signal(&(delegate->m_cond));
#endif
}


#ifdef QEDO_WINTHREAD
DWORD WINAPI startFunc(LPVOID p) {
#else
void* startFunc(void* p) {
#endif

	t_start* t = (t_start*) p;
	void* (*f)(void*) = t->p;
	void* arg = t->a;

	delete t;

	(f)(arg);

	return 0;
}

void
qedo_startDetachedThread(void* (*p)(void*), void* arg) {

	t_start* startParams = new t_start;
	startParams->p = p;
	startParams->a = arg;

#ifdef QEDO_WINTHREAD
	HANDLE th_handle;
	DWORD th_id;
	th_handle = CreateThread(NULL,
							0,
							startFunc,
							(LPVOID) startParams,
							NULL,
							&th_id);
#else
	pthread_t t;
	pthread_attr_t detached_attr;
	pthread_attr_init(&detached_attr);
	pthread_attr_setdetachstate(&detached_attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&t, &detached_attr, startFunc, startParams);
#endif
}


} // end namespace Qedo
