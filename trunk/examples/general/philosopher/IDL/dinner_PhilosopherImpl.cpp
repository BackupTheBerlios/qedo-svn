//
// generated by Qedo
//

#include "dinner_PhilosopherImpl.h"


// BEGIN USER INSERT SECTION file
#include <iostream>

using namespace std;

namespace dinner {

JTCThreadWithTimer::JTCThreadWithTimer()
{
}


JTCThreadWithTimer::~JTCThreadWithTimer()
{
	cout << "JTCThreadWithTimer: Destructor called" << endl;
}


void
JTCThreadWithTimer::timer_sleep (long millis)
{
	JTCSynchronized synchronized (*this);	

	bool done_ = false;

	while (! done_)
	{
		try
		{ 
			this -> wait (millis);
			done_ = true;
		}
		catch (JTCInterruptedException&)
		{
		}
	}
}


void
JTCThreadWithTimer::wake_up()
{
	JTCSynchronized synchronized (*this);	

	this->notify();
}

}
// END USER INSERT SECTION file


namespace dinner {


// BEGIN USER INSERT SECTION PhilosopherSessionImpl
void
PhilosopherSessionImpl::run()
{
	bool have_left = false, have_right = false;
	Components::Cookie_var leftcook = 0;
	Components::Cookie_var rightcook = 0;
	
	dinner::Fork_var left_hand = context_->get_connection_left_hand();
	dinner::Fork_var right_hand = context_->get_connection_right_hand();
	dinner::PhilosopherStatus status;
	dinner::PhilosopherState_var report;
	unsigned short dead_counter;

	while (! stopped_)
	{
		status = dinner::THINKING;
		cout << "PhilosopherSessionImpl: Philosopher is thinking -> " << id_ << endl;
		report = new PhilosopherState_impl (status, id_.c_str(),
			dinner::Philosopher::_narrow (context_->get_CCM_object()));
		context_->push_philosopher_state (report);
		this->timer_sleep (tsec_ *1000);
	
		if (stopped_)
			break;

		status = dinner::HUNGRY;
		cout << "PhilosopherSessionImpl: Philosopher is hungry -> " << id_ << endl;
		report = new PhilosopherState_impl (status, id_.c_str(),
			dinner::Philosopher::_narrow (context_->get_CCM_object()));
		context_->push_philosopher_state (report);
		dead_counter = 4;

		while ( status == dinner::HUNGRY && ! stopped_)
		{
			this->timer_sleep (2000);

			if (--dead_counter == 0)
			{
				cout << "PhilosopherSessionImpl: Philosopher is dead... aaaaaahhhhhhhhhhhhhh... -> " << id_ << endl;
				status = dinner::DEAD;
				report = new PhilosopherState_impl (status, id_.c_str(),
					dinner::Philosopher::_narrow (context_->get_CCM_object()));
				context_->push_philosopher_state (report);

				while (! stopped_)
				{
					JTCSynchronized synchronized (*this);
					this->wait();
				}
			}
			try
			{
				// Philosophers with even eating seconds first try to get the left fork, the others the right fork
				if (esec_ % 2)
				{
					rightcook = right_hand->obtain_fork();
					have_right = true;

					cout << "PhilosopherSessionImpl: Got right fork -> " << id_ << endl;
				}
				else
				{
					leftcook = left_hand->obtain_fork();
					have_left = true;

					cout << "PhilosopherSessionImpl: Got left fork -> " << id_ << endl;
				}
			}
			catch (dinner::ForkNotAvailable&)
			{
				cout << "PhilosopherSessionImpl: Fork in use -> " << id_ << endl;
				continue;
			}
			catch (CORBA::SystemException& ex)
			{
				cerr << "PhilosopherSessionImpl: CORBA system exception during obtain_fork(), continue..." << endl;
				cerr << ex << endl;
				continue;
			}

			try
			{
				// Philosophers with even eating seconds second try to get the right fork, the others the left fork
				if (esec_ % 2)
				{
					leftcook = left_hand->obtain_fork();
					have_left = true;

					cout << "PhilosopherSessionImpl: Got left fork -> " << id_ << endl;
				}
				else
				{
					rightcook = right_hand->obtain_fork();
					have_right = true;

					cout << "PhilosopherSessionImpl: Got right fork -> " << id_ << endl;
				}
			}
			catch (dinner::ForkNotAvailable&)
			{
				cout << "PhilosopherSessionImpl: Fork in use -> " << id_ << endl;

				if (esec_ % 2)
				{
					right_hand->release_fork (rightcook);
					have_right = false;
				}
				else
				{
					left_hand->release_fork (leftcook);
					have_left = false;
				}

				continue;
			}
			catch (CORBA::SystemException&)
			{
				cerr << "PhilosopherSessionImpl: CORBA system exception during obtain_fork(), continue..." << endl;
				continue;
			}

			break;
		}

		if (stopped_)
			break;

		status = dinner::EATING;
		cout << "PhilosopherSessionImpl: Philosopher is eating -> " << id_ << endl;
		report = new PhilosopherState_impl (status, id_.c_str(),
			dinner::Philosopher::_narrow (context_->get_CCM_object()));
		context_->push_philosopher_state (report);
		this->timer_sleep (esec_*1000);

		if (stopped_)
			break;

		try
		{
			right_hand->release_fork (rightcook);
			have_right = false;

			left_hand->release_fork (leftcook);
			have_left = false;
		}
		catch (dinner::NotTheEater&)
		{
			cout << "PhilosopherSessionImpl: Unexpected dinner::NotTheEater exception. I'm in hell, aborting... -> " << id_ << endl;
			abort();
		}
		catch (CORBA::SystemException&)
		{
			cout << "PhilosopherSessionImpl: CORBA system exception during release_fork(). I'm in hell, aborting... -> " << id_ << endl;
			abort();
		}

		status = dinner::SLEEPING;
		cout << "PhilosopherSessionImpl: Philosopher is sleeping -> " << id_ << endl;
		report = new PhilosopherState_impl (status, id_.c_str(),
			dinner::Philosopher::_narrow (context_->get_CCM_object()));
			context_->push_philosopher_state (report);
		this->timer_sleep (ssec_ * 1000);

		if (stopped_)
			break;
	}

	// Remove this thread friendly
	do
	{
		try
		{
			my_thread_handle_->join();
		}
		catch (...)
		{
			cerr << "Exception during join()" << endl;
		}
	} while (my_thread_handle_->isAlive());
}
// END USER INSERT SECTION PhilosopherSessionImpl


PhilosopherSessionImpl::PhilosopherSessionImpl()
: ref_count_ (1)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::PhilosopherSessionImpl
	my_thread_handle_ = this;
	stopped_ = false;
// END USER INSERT SECTION PhilosopherSessionImpl::PhilosopherSessionImpl
}


PhilosopherSessionImpl::~PhilosopherSessionImpl()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::~PhilosopherSessionImpl
	cout << "PhilosopherSessionImpl: Destructor called" << endl;
// END USER INSERT SECTION PhilosopherSessionImpl::~PhilosopherSessionImpl
assert (ref_count_ == 0);
}


void
PhilosopherSessionImpl::_add_ref()
{
    ++ref_count_;
}


void
PhilosopherSessionImpl::_remove_ref()
{
    if (--ref_count_ == 0)
    {
        delete this;
    }
}


unsigned long
PhilosopherSessionImpl::_get_refcount()
{
    return ref_count_;
}


void
PhilosopherSessionImpl::set_context(::dinner::CCM_Philosopher_Context_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::dinner::CCM_Philosopher_Context::_duplicate(context);
}


void
PhilosopherSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::configuration_complete
	this->start();
// END USER INSERT SECTION PhilosopherSessionImpl::configuration_complete
}


void
PhilosopherSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::remove
// END USER INSERT SECTION PhilosopherSessionImpl::remove
}


void
PhilosopherSessionImpl::thinking_seconds(CORBA::ULong param)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::_thinking_seconds
	tsec_ = param;
// END USER INSERT SECTION PhilosopherSessionImpl::_thinking_seconds
}


CORBA::ULong
PhilosopherSessionImpl::thinking_seconds()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::thinking_seconds
	return tsec_;
// END USER INSERT SECTION PhilosopherSessionImpl::thinking_seconds
}


void
PhilosopherSessionImpl::eating_seconds(CORBA::ULong param)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::_eating_seconds
	esec_ = param;
// END USER INSERT SECTION PhilosopherSessionImpl::_eating_seconds
}


CORBA::ULong
PhilosopherSessionImpl::eating_seconds()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::eating_seconds
	return esec_;
// END USER INSERT SECTION PhilosopherSessionImpl::eating_seconds
}


void
PhilosopherSessionImpl::sleeping_seconds(CORBA::ULong param)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::_sleeping_seconds
	ssec_ = param;
// END USER INSERT SECTION PhilosopherSessionImpl::_sleeping_seconds
}


CORBA::ULong
PhilosopherSessionImpl::sleeping_seconds()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::sleeping_seconds
	return ssec_;
// END USER INSERT SECTION PhilosopherSessionImpl::sleeping_seconds
}


void
PhilosopherSessionImpl::name(const char* param)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::_name
	cout << "PhilosopherSessionImpl: Name set to " << param << endl;

	id_ = CORBA::string_dup (param);
// END USER INSERT SECTION PhilosopherSessionImpl::_name
}


char*
PhilosopherSessionImpl::name()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::name
	cout << "PhilosopherSessionImpl: Name is " << id_.c_str() << endl;

	return CORBA::string_dup (id_.c_str());
// END USER INSERT SECTION PhilosopherSessionImpl::name
}


// BEGIN USER INSERT SECTION PhilosopherImpl
// END USER INSERT SECTION PhilosopherImpl


PhilosopherImpl::PhilosopherImpl()
: ref_count_ (1)
, component_(new PhilosopherSessionImpl())
{
// BEGIN USER INSERT SECTION PhilosopherImpl::PhilosopherImpl
// END USER INSERT SECTION PhilosopherImpl::PhilosopherImpl
}


PhilosopherImpl::~PhilosopherImpl()
{
    component_->_remove_ref();

// BEGIN USER INSERT SECTION PhilosopherImpl::~PhilosopherImpl
	cout << "PhilosopherImpl: Destructor called" << endl;
// END USER INSERT SECTION PhilosopherImpl::~PhilosopherImpl
assert (ref_count_ == 0);
}


void
PhilosopherImpl::_add_ref()
{
    ++ref_count_;
}


void
PhilosopherImpl::_remove_ref()
{
    if (--ref_count_ == 0)
    {
        delete this;
    }
}


unsigned long
PhilosopherImpl::_get_refcount()
{
    return ref_count_;
}


::CORBA::Object*
PhilosopherImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
PhilosopherImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
PhilosopherImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION PhilosopherImpl::configuration_complete
// END USER INSERT SECTION PhilosopherImpl::configuration_complete
}


void
PhilosopherImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = dynamic_cast<::dinner::CCM_Philosopher_Context*>(context);
    
    component_->set_context(context_);
}


void
PhilosopherImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PhilosopherImpl::ccm_activate
	cout << "PhilosopherImpl: ccm_activate() called" << endl;
// END USER INSERT SECTION PhilosopherImpl::ccm_activate
}


void
PhilosopherImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PhilosopherImpl::ccm_passivate
	cout << "PhilosopherImpl: ccm_passivate() called" << endl;
// END USER INSERT SECTION PhilosopherImpl::ccm_passivate
}


void
PhilosopherImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION PhilosopherImpl::ccm_remove
	cout << "PhilosopherImpl: ccm_remove() called" << endl;
// END USER INSERT SECTION PhilosopherImpl::ccm_remove
}


// BEGIN USER INSERT SECTION PhilosopherHomeImpl
// END USER INSERT SECTION PhilosopherHomeImpl


PhilosopherHomeImpl::PhilosopherHomeImpl()
: ref_count_ (1)
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::PhilosopherHomeImpl
// END USER INSERT SECTION PhilosopherHomeImpl::PhilosopherHomeImpl
}


PhilosopherHomeImpl::~PhilosopherHomeImpl()
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::~PhilosopherHomeImpl
	cout << "PhilosopherHomeImpl: Destructor called" << endl;
// END USER INSERT SECTION PhilosopherHomeImpl::~PhilosopherHomeImpl
assert (ref_count_ == 0);
}


void
PhilosopherHomeImpl::_add_ref()
{
    ++ref_count_;
}


void
PhilosopherHomeImpl::_remove_ref()
{
    if (--ref_count_ == 0)
    {
        delete this;
    }
}


unsigned long
PhilosopherHomeImpl::_get_refcount()
{
    return ref_count_;
}


void
PhilosopherHomeImpl::set_context(Components::CCMContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::CCMContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
PhilosopherHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::create
// END USER INSERT SECTION PhilosopherHomeImpl::create
    return new PhilosopherImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_PhilosopherHomeE(void)
{
// BEGIN USER INSERT SECTION create_PhilosopherHome
// END USER INSERT SECTION create_PhilosopherHome

    return new ::dinner::PhilosopherHomeImpl();
}

