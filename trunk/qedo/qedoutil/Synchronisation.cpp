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
#include "Output.h"

#ifdef QEDO_PTHREAD
#include <pthread.h>
#include <signal.h>
#endif

static char rcsid[] UNUSED = "$Id: Synchronisation.cpp,v 1.19 2003/08/27 06:32:48 neubauer Exp $";


namespace Qedo {

struct MutexDelegate 
{
#ifdef QEDO_WINTHREAD
	HANDLE mutex_;
#else
	pthread_mutex_t mutex_;
#endif
};

struct CondDelegate 
{
#ifdef QEDO_WINTHREAD
	HANDLE event_handle_;
#else
	pthread_cond_t cond_;
#endif
};

struct ThreadDelegate {
#ifdef QEDO_WINTHREAD
       HANDLE th_handle_;
       DWORD th_id_;
#else
       pthread_t t_;
#endif
};

QedoMutex::QedoMutex() 
{
    delegate_ = new MutexDelegate();
#ifdef QEDO_WINTHREAD
	delegate_->mutex_ = CreateMutex (NULL,FALSE,NULL);
#else
	pthread_mutex_init (&(delegate_->mutex_), NULL);
#endif
}


QedoMutex::~QedoMutex() 
{
#ifdef QEDO_WINTHREAD
#else
	pthread_mutex_destroy( &(delegate_->mutex_));
#endif
	delete delegate_;
}


void
QedoMutex::lock_object() 
{
#ifdef QEDO_WINTHREAD
	if (WaitForSingleObject (delegate_->mutex_, INFINITE) != WAIT_OBJECT_0)
	{
		std::cerr << "QedoMutex: lock_object() failed: " << GetLastError() << std::endl;
		assert (0);
	}
#else
	pthread_mutex_lock (&(delegate_->mutex_));
#endif
}


void
QedoMutex::unlock_object() 
{
#ifdef QEDO_WINTHREAD
	if (! ReleaseMutex (delegate_->mutex_))
	{
		std::cerr << "QedoMutex: unlock_object() failed: " << GetLastError() << std::endl;
		assert (0);
	}
#else
	pthread_mutex_unlock (&(delegate_->mutex_));
#endif
}


QedoLock::QedoLock (const QedoMutex* m) 
{
	mutex_ = const_cast<QedoMutex* const> (m);
	mutex_->lock_object();
}


QedoLock::QedoLock (QedoMutex* m) 
{
	mutex_ = m;
	mutex_->lock_object();
}


QedoLock::QedoLock (const QedoMutex& m) 
{
	mutex_ = const_cast<QedoMutex* const> (&m);
	mutex_->lock_object();
}


QedoLock::~QedoLock() 
{
	mutex_->unlock_object();
}


QedoCond::QedoCond() 
{
	delegate_ = new CondDelegate;
#ifdef QEDO_WINTHREAD
		delegate_->event_handle_ = CreateEvent (0, FALSE /*manual-reset*/, FALSE /*initial: non-signaled*/, 0);
#else
		pthread_cond_init (&(delegate_->cond_), 0);
#endif
}

QedoCond::QedoCond (char * sig_name) 
{
	delegate_ = new CondDelegate;
#ifdef QEDO_WINTHREAD
		delegate_->event_handle_ = CreateEvent (0, FALSE /*manual-reset*/, FALSE /*initial: non-signaled*/, sig_name);
#else
		pthread_cond_init (&(delegate_->cond_), 0);
#endif
}


QedoCond::~QedoCond() 
{
#ifdef QEDO_WINTHREAD
#else
	pthread_cond_destroy (&(delegate_->cond_));
#endif
	delete delegate_;
}


void
QedoCond::wait (const QedoMutex& m) 
{
#ifdef QEDO_WINTHREAD
	const_cast<QedoMutex* const>(&m)->unlock_object();
	if (WaitForMultipleObjects(1, &(delegate_->event_handle_), TRUE, INFINITE /*wait for ever*/) == WAIT_FAILED)
	{
		std::cerr << "QedoCond: wait() failed: " << GetLastError() << std::endl;
		assert (0);
	}
	const_cast<QedoMutex* const>(&m)->lock_object();
#else
	pthread_cond_wait (&(delegate_->cond_),&(m.delegate_->mutex_));
#endif
}

void
QedoCond::wait(const QedoMutex* m) 
{
#ifdef QEDO_WINTHREAD
	const_cast<QedoMutex* const>(m)->unlock_object();
	if (WaitForMultipleObjects(1, &(delegate_->event_handle_), TRUE, INFINITE /*wait for ever*/) == WAIT_FAILED)
	{
		std::cerr << "QedoCond: qedo_wait() failed: " << GetLastError() << std::endl;
		assert (0);
	}
	const_cast<QedoMutex* const>(m)->lock_object();
#else
	pthread_cond_wait (&(delegate_->cond_),&(m->delegate_->mutex_));
#endif
}


void
QedoCond::signal() 
{
#ifdef QEDO_WINTHREAD
	if (! SetEvent(delegate_->event_handle_))
	{
		std::cerr << "QedoCond: qedo_signal() failed: " << GetLastError() << std::endl;
		assert (0);
	}
#else
	pthread_cond_signal (&(delegate_->cond_));
#endif
}

QedoThread::QedoThread()
{
       delegate_ = new ThreadDelegate;
};

void
QedoThread::stop()
{
#ifdef QEDO_WINTHREAD
       DWORD exitcode;
       if(!TerminateThread(delegate_->th_handle_,exitcode)) 
               DEBUG_OUT("Error while TerminateThread");
#else
       if(pthread_cancel(delegate_->t_)) DEBUG_OUT("Error while pthread_cancel");
#endif
}

void
QedoThread::join()
{
#ifdef QEDO_WINTHREAD
#else
       void *state;
       if(pthread_join(delegate_->t_,&state)) DEBUG_OUT("Error while pthread_join");
#endif
}

#ifdef QEDO_WINTHREAD
DWORD WINAPI startFunc(LPVOID p) {
#else
void* startFunc(void* p) {
#endif

	T_Start* t = (T_Start*) p;
	void* (*f)(void*) = t->p;
	void* arg = t->a;

	delete t;

	(f)(arg);

	return 0;
}

QedoThread*
qedo_startDetachedThread(void* (*p)(void*), void* arg) {

	T_Start* startParams = new T_Start();
	startParams->p = p;
	startParams->a = arg;
	QedoThread * thread = new QedoThread();

#ifdef QEDO_WINTHREAD
	thread->delegate_->th_handle_ = CreateThread(NULL,
							0,
							startFunc,
							(LPVOID) startParams,
							NULL,
							&(thread->delegate_->th_id_));
#else
	pthread_attr_t detached_attr;
	pthread_attr_init(&detached_attr);
	pthread_attr_setdetachstate(&detached_attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&(thread->delegate_->t_), &detached_attr, startFunc, startParams);
#endif
	return thread;
}


} // end namespace Qedo
