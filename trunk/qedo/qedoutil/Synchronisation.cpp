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

#ifdef _WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif

static char rcsid[] UNUSED = "$Id: Synchronisation.cpp,v 1.24 2003/10/17 13:22:41 stoinski Exp $";


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

enum  lock_state_t
{
		READ_LOCK,
		WRITE_LOCK
};

struct ReadWriteMutexDelegate
{
	ReadWriteMutexDelegate();
	~ReadWriteMutexDelegate();
	lock_state_t state;
	unsigned long readers;
	unsigned long writers;
	QedoCond* reader_cond;
	QedoCond* writer_cond;
};


ReadWriteMutexDelegate::ReadWriteMutexDelegate()
	: state(READ_LOCK), readers(0), writers(0)
{
	reader_cond = new QedoCond();
	writer_cond = new QedoCond();
}

ReadWriteMutexDelegate::~ReadWriteMutexDelegate()
{
	delete writer_cond;
	delete reader_cond;
}

QedoMutex::QedoMutex() 
{
    delegate_ = new MutexDelegate();
#ifdef QEDO_WINTHREAD
	delegate_->mutex_ = CreateMutex (NULL,FALSE,NULL);
#else
	int ret;
	ret = pthread_mutex_init (&(delegate_->mutex_), NULL);

	if ( ret )
	{
		std::cerr << "QedoMutex::QedoMutex: " << strerror(ret) << std::endl;
		abort();
	}
#endif
}


QedoMutex::~QedoMutex() 
{
#ifdef QEDO_WINTHREAD
	if (! CloseHandle (delegate_->mutex_))
	{
		std::cerr << "QedoMutex::~QedoMutex: " << GetLastError() << std::endl;
		abort();
	}
#else
	int ret;

	ret = pthread_mutex_destroy( &(delegate_->mutex_));

	if ( ret )
	{
		std::cerr << "QedoMutex::~QedoMutex: " << strerror(ret) << std::endl;
	}
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
	int ret;

	ret = pthread_mutex_lock (&(delegate_->mutex_));

	if ( ret )
	{
		std::cerr << "QedoMutex::lock_object: " << strerror(ret) << std::endl;
	}
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
	int ret;
	
	ret = pthread_mutex_unlock (&(delegate_->mutex_));

	if ( ret )
	{
		std::cerr << "QedoMutex::unlock_object: " << strerror(ret) << std::endl;
	}
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
	int ret;

	ret = pthread_cond_init (&(delegate_->cond_), 0);

	if ( ret )
	{
		std::cerr << "QedoCond::QedoCond: " << strerror(ret) << std::endl;
		abort();
	}
#endif
}

QedoCond::QedoCond (char * sig_name) 
{
	delegate_ = new CondDelegate;
#ifdef QEDO_WINTHREAD
		delegate_->event_handle_ = CreateEvent (0, FALSE /*manual-reset*/, FALSE /*initial: non-signaled*/, sig_name);
#else
	int ret;

	ret = pthread_cond_init (&(delegate_->cond_), 0);

	if ( ret )
	{
		std::cerr << "QedoCond::QedoCond: " << strerror(ret) << std::endl;
		abort();
	}
#endif
}


QedoCond::~QedoCond() 
{
#ifdef QEDO_WINTHREAD
	if (! CloseHandle (delegate_->event_handle_))
	{
		std::cerr << "QedoCond::~QedoCond: " << GetLastError() << std::endl;
	}
#else
	int ret;

	ret = pthread_cond_destroy (&(delegate_->cond_));

	if ( ret )
	{
		std::cerr << "QedoCond::~QedoCond: " << strerror(ret) << std::endl;
	}
#endif
	delete delegate_;
}


void
QedoCond::wait (const QedoMutex& m) 
{
	wait(&m);
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
	int ret;

	ret = pthread_cond_wait (&(delegate_->cond_),&(m->delegate_->mutex_));

	if ( ret )
	{
		std::cerr << "QedoCond::wait: " << strerror(ret) << std::endl;
	}
#endif
}

bool
QedoCond::wait_timed (const QedoMutex& m, unsigned long timeout) 
{
	return wait_timed(&m,timeout);
}

bool
QedoCond::wait_timed(const QedoMutex* m, unsigned long timeout) 
{
	bool ret = true;
#ifdef QEDO_WINTHREAD
 	const_cast<QedoMutex* const>(m)->unlock_object();
	long x;
	x = WaitForSingleObject (delegate_->event_handle_, timeout);

	switch (x)
 	{
		case WAIT_FAILED:
			std::cerr << "QedoCond: qedo_wait() failed: " << GetLastError() << std::endl;
			assert (0);
			break;
		case WAIT_TIMEOUT:
			ret = false;
			break;
	};
 	const_cast<QedoMutex* const>(m)->lock_object();
#else
	int x;
	struct timespec abstime;

#ifdef _WIN32
	struct _timeb tb;

	_ftime(&tb);
	abstime.tv_sec = tb.time + timeout / 1000;
	timeout = timeout % 1000;
	timeout += tb.millitm;
	if(timeout > 1000)
	{
		abstime.tv_sec = abstime.tv_sec + 1;
		timeout -= 1000;
	}
	abstime.tv_nsec = timeout * 1000;
#else
	struct timeval tp;

	gettimeofday(&tp,0);
	abstime.tv_sec = tp.tv_sec + timeout / 1000;
	timeout = timeout % 1000;
	timeout += tp.tv_usec;
	if(timeout > 1000)
	{
		abstime.tv_sec = abstime.tv_sec + 1;
		timeout -= 1000;
	}
	abstime.tv_nsec = timeout * 1000;
#endif
	x = pthread_cond_timedwait (&(delegate_->cond_),&(m->delegate_->mutex_), &abstime);

	switch (x)
	{
		case ETIMEDOUT:
			ret = false;
			break;
		case 0:
			break;
		default:
			std::cerr << "QedoCond::wait_timed: " << strerror(x) << std::endl;
			assert (0);
			break;
	};
#endif
	return ret;
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
	int ret;

	ret = pthread_cond_signal (&(delegate_->cond_));

	if ( ret )
	{
		std::cerr << "QedoCond::signal: " << strerror(ret) << std::endl;
	}
#endif
}

void
QedoCond::broadcast() 
{
#ifdef QEDO_WINTHREAD
	// XXX must be implemented
	abort();
#else
	int ret;

	ret = pthread_cond_broadcast (&(delegate_->cond_));

	if ( ret )
	{
		std::cerr << "QedoCond::broadcast: " << strerror(ret) << std::endl;
	}
#endif
}

QedoReadWriteMutex::QedoReadWriteMutex()
{
	rwdelegate_ = new ReadWriteMutexDelegate;
}

QedoReadWriteMutex::~QedoReadWriteMutex()
{
	delete rwdelegate_;
}

void
QedoReadWriteMutex::read_lock_object()
{
	QedoLock l(this);

	while (rwdelegate_->state != READ_LOCK)
	{
		rwdelegate_->reader_cond->wait(*this);
	}

	rwdelegate_->readers += 1;
}

void
QedoReadWriteMutex::write_lock_object()
{
	QedoLock l(this);

	rwdelegate_->writers += 1;

	while (rwdelegate_->state != WRITE_LOCK )
	{
		rwdelegate_->writer_cond->wait(*this);
	}

	rwdelegate_->writers -= 1;

}

void
QedoReadWriteMutex::unlock_object()
{
	QedoLock l(this);

	switch (rwdelegate_->state)
	{
		case READ_LOCK:
			rwdelegate_->readers -= 1;
			if ( rwdelegate_->readers == 0 && rwdelegate_->writers ) 
			{
				rwdelegate_->state = WRITE_LOCK;
				rwdelegate_->writer_cond->signal();
			}
			break;
		case WRITE_LOCK:
			if ( rwdelegate_->writers )
			{
				rwdelegate_->writer_cond->signal();
			}
			else 
			{
				rwdelegate_->state = READ_LOCK;
				rwdelegate_->reader_cond->signal();
			}
			break;
	}
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
	int ret;

   ret = pthread_cancel(delegate_->t_);

	if ( ret )
	{
		std::cerr << "QedoThread::stop: " << strerror(ret) << std::endl;
	}
#endif
}

void
QedoThread::join()
{
#ifdef QEDO_WINTHREAD
	if (WaitForSingleObject (delegate_->th_handle_, INFINITE) != WAIT_OBJECT_0)
	{
        std::cerr << "QedoThread::join: " << GetLastError() << std::endl;
	}
#else
	void *state;
	int ret;

   ret = pthread_join(delegate_->t_,&state);

	if ( ret )
	{
		std::cerr << "QedoThread::join: " << strerror(ret) << std::endl;
	}
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
	int ret;
	pthread_attr_t detached_attr;

	ret = pthread_attr_init(&detached_attr);

	if ( ret )
	{
		std::cerr << "qedo_startDetachedThread: " << strerror(ret) << std::endl;
		abort();
	}

	ret = pthread_attr_setdetachstate(&detached_attr, PTHREAD_CREATE_JOINABLE);

	if ( ret )
	{
		std::cerr << "qedo_startDetachedThread: " << strerror(ret) << std::endl;
		abort();
	}

	ret = pthread_create(&(thread->delegate_->t_), &detached_attr, startFunc, startParams);

	if ( ret )
	{
		std::cerr << "qedo_startDetachedThread: " << strerror(ret) << std::endl;
		abort();
	}
#endif
	return thread;
}

} // end namespace Qedo
