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


namespace Qedo {


qedo_mutex::qedo_mutex() {

#ifdef WIN32
	m_mutex = CreateMutex(NULL,FALSE,NULL);
#else
	pthread_mutex_init(&m_mutex, NULL);
#endif
}


qedo_mutex::~qedo_mutex() {

#ifdef WIN32
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}


void
qedo_mutex::qedo_lock_object() {

#ifdef WIN32
	WaitForSingleObject(m_mutex, INFINITE);
#else
	pthread_mutex_lock(&m_mutex);
#endif
}


void
qedo_mutex::qedo_unlock_object() {

#ifdef WIN32
	ReleaseMutex(m_mutex);
#else
	pthread_mutex_unlock(&m_mutex);
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


qedo_lock::~qedo_lock() {
	m_mutex->qedo_unlock_object();
}


qedo_cond::qedo_cond(char * sig_name) {
#ifdef WIN32
		m_event_handle = CreateEvent (NULL, TRUE /*manua-reset*/, FALSE /*initial: non-signaled*/, sig_name);
#else
		pthread_cond_init(&m_cond, NULL);
#endif
}


qedo_cond::~qedo_cond() {
#ifdef WIN32

#else
	pthread_cond_destroy(&m_cond);
#endif
}


void
qedo_cond::qedo_wait() {

#ifdef WIN32
	WaitForMultipleObjects(1, &m_event_handle, TRUE, INFINITE /*wait for ever*/);
#else
	pthread_cond_signal(&m_cond);
#endif
}


void
qedo_cond::qedo_signal() {

#ifdef WIN32
	SetEvent(m_event_handle);
#else
	pthread_cond_signal(&m_cond);
#endif
}


void
qedo_cond::qedo_reset() {
#ifdef WIN32
	ResetEvent(m_event_handle);
#else
#endif
};



#ifdef WIN32
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

#ifdef WIN32
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
