//
// generated by Qedo
//

#include "auction_AuctioneerImpl.h"


// BEGIN USER INSERT SECTION file
#include <iostream>

using namespace std;

#ifdef _WIN32
#define sleep(X) Sleep(X*1000)
#endif
// END USER INSERT SECTION file


namespace auction {


// BEGIN USER INSERT SECTION AuctioneerSessionImpl

ItemEntry::ItemEntry() :
  item(0),
  minimum(0),
  contract(0),
  seller(0)
{
}

ItemEntry::ItemEntry(const ItemEntry& e)
{
	CORBA::string_free(item);
	item = CORBA::string_dup(e.item);
	minimum = e.minimum;
	contract = e.contract;
	seller = e.seller;
}

ItemEntry::~ItemEntry()
{
	CORBA::string_free(item);
}

const ItemEntry&
ItemEntry::operator=(const ItemEntry& e)
{
	if(&e != this)
	{
		CORBA::string_free(item);
		item = CORBA::string_dup(e.item);
		minimum = e.minimum;
		contract = e.contract;
		seller = e.seller;
	}
	return *this;
}

void*
AuctioneerSessionImpl::run(void *p)
{
	AuctioneerSessionImpl* impl;


	bool no_timeout = true;

	impl = static_cast<AuctioneerSessionImpl*>(p);

	impl->current_item_mutex->lock();

	while (! impl->stopped)
	{
		if (impl->time)
		{
			no_timeout = impl->current_item_cond->wait_timed(impl->current_item_mutex,impl->time);
		}
		else
		{
			impl->current_item_cond->wait(impl->current_item_mutex);
		}

		if ( ! no_timeout )
		{
			impl->current_item_mutex->unlock();
			impl->timeout();
			impl->current_item_mutex->lock();
		}
	}

	impl->current_item_mutex->unlock();

	return 0;
}

void
AuctioneerSessionImpl::stop()
{
	stopped = true;
	current_item_cond->signal();
	auctioneer_thread->join();
}

void
AuctioneerSessionImpl::timeout()
{
	current_item_mutex->lock();
	if ( have_current_item )
	{
		if ( count > 0 )
		{
			call_out_item();
		}
		else {
			sell_item();
		}
	}
	current_item_mutex->unlock();
}

void
AuctioneerSessionImpl::call_out_item()
{
	// send current_item to all bidders
	GiveBidImpl b(current_item.item,current_price);
	context_->push_current_bid(&b);
	count -= 1;
	time = 5000;
	current_item_cond->signal();
}

void
AuctioneerSessionImpl::sell_item()
{
	// do sell
	current_bidder->sold(current_price);
	current_item.seller->pay(current_item.contract,current_price);
	get_new_item();
}

void
AuctioneerSessionImpl::get_new_item()
{
	item_list_mutex->lock();
	if ( !item_list.empty() )
	{
		current_item = *(item_list.begin());
		item_list.pop_front();
		current_price = current_item.minimum;
		count = 3;
		call_out_item();
	}
	else
	{
		std::cout << "Wait for a new item" << std::endl;
		have_current_item = false;
		time = 0;
	}
	item_list_mutex->unlock();
}

// END USER INSERT SECTION AuctioneerSessionImpl


AuctioneerSessionImpl::AuctioneerSessionImpl()
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::AuctioneerSessionImpl
	stopped = false;
	have_current_item=false;
	time = 0;
	current_price = 0;
	contracts = 0;
// END USER INSERT SECTION AuctioneerSessionImpl::AuctioneerSessionImpl
}


AuctioneerSessionImpl::~AuctioneerSessionImpl()
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::~AuctioneerSessionImpl
	item_list_mutex->destroy();
	current_item_cond->destroy();
	current_item_mutex->destroy();
// END USER INSERT SECTION AuctioneerSessionImpl::~AuctioneerSessionImpl

}


void
AuctioneerSessionImpl::set_context(::auction::CCM_Auctioneer_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::auction::CCM_Auctioneer_ContextImpl::_duplicate(context);
}


void
AuctioneerSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::configuration_complete
	item_list_mutex = context_->create_mutex();
	current_item_mutex = context_->create_mutex();
	current_item_cond = context_->create_cond();
	auctioneer_thread = context_->start_thread(run,this);
// END USER INSERT SECTION AuctioneerSessionImpl::configuration_complete
}


void
AuctioneerSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::remove
// END USER INSERT SECTION AuctioneerSessionImpl::remove
}


CORBA::Long
AuctioneerSessionImpl::sell(auction::SellerForAuctioneer_ptr seller, const char* item, CORBA::Long minimum)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::sell
	current_item_mutex->lock();
	CORBA::Long ret;
	if(have_current_item)
	{
		item_list_mutex->lock();
		ItemEntry e;
		e.item = CORBA::string_dup(item);
		e.minimum = minimum;
		e.contract = ++contracts;
		e.seller = auction::SellerForAuctioneer::_duplicate(seller);
		item_list.push_back(e);
		item_list_mutex->unlock();
	}
	else
	{
		CORBA::string_free(current_item.item);
		current_item.item = CORBA::string_dup(item);
		current_item.minimum = minimum;
		current_item.seller = auction::SellerForAuctioneer::_duplicate(seller);
		current_item.contract = ++contracts;
		current_price = minimum;
		have_current_item = true;
		count = 3;
		call_out_item();
	}
	ret = contracts;
	current_item_mutex->unlock();
	return ret;
// END USER INSERT SECTION AuctioneerSessionImpl::sell
}


void
AuctioneerSessionImpl::push_event (Components::EventBase* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::push_event
// END USER INSERT SECTION AuctioneerSessionImpl::push_event
}


void
AuctioneerSessionImpl::push_Bid(::auction::Bid* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION AuctioneerSessionImpl::push_Bid
	current_item_mutex->lock();
	if(ev->price() > current_price)
	{
		current_bidder = ::auction::BidderForAuctioneer::_duplicate(ev->bidder());
		current_price = ev->price();
		count = 3;
		call_out_item();
	}
	current_item_mutex->unlock();
// END USER INSERT SECTION AuctioneerSessionImpl::push_Bid
}


// BEGIN USER INSERT SECTION AuctioneerImpl
// END USER INSERT SECTION AuctioneerImpl


AuctioneerImpl::AuctioneerImpl()
:component_(new AuctioneerSessionImpl())
{
// BEGIN USER INSERT SECTION AuctioneerImpl::AuctioneerImpl
// END USER INSERT SECTION AuctioneerImpl::AuctioneerImpl
}


AuctioneerImpl::~AuctioneerImpl()
{
// BEGIN USER INSERT SECTION AuctioneerImpl::~AuctioneerImpl
// END USER INSERT SECTION AuctioneerImpl::~AuctioneerImpl

    component_->_remove_ref();
}


::CORBA::Object*
AuctioneerImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "for_seller")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
AuctioneerImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
AuctioneerImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION AuctioneerImpl::configuration_complete
// END USER INSERT SECTION AuctioneerImpl::configuration_complete
}


void
AuctioneerImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::auction::CCM_Auctioneer_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::auction::CCM_Auctioneer_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::auction::CCM_Auctioneer_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::auction::CCM_Auctioneer_ContextImpl::_nil();
        
    #else
    context_ = ::auction::CCM_Auctioneer_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
AuctioneerImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION AuctioneerImpl::ccm_activate
// END USER INSERT SECTION AuctioneerImpl::ccm_activate
}


void
AuctioneerImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION AuctioneerImpl::ccm_passivate
// END USER INSERT SECTION AuctioneerImpl::ccm_passivate
}


void
AuctioneerImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION AuctioneerImpl::ccm_remove
	cout << "AuctioneerImpl: ccm_remove() called" << endl;

	component_->stop();
// END USER INSERT SECTION AuctioneerImpl::ccm_remove
}


// BEGIN USER INSERT SECTION AuctioneerHomeImpl
// END USER INSERT SECTION AuctioneerHomeImpl


AuctioneerHomeImpl::AuctioneerHomeImpl()
{
// BEGIN USER INSERT SECTION AuctioneerHomeImpl::AuctioneerHomeImpl
// END USER INSERT SECTION AuctioneerHomeImpl::AuctioneerHomeImpl
}


AuctioneerHomeImpl::~AuctioneerHomeImpl()
{
// BEGIN USER INSERT SECTION AuctioneerHomeImpl::~AuctioneerHomeImpl
// END USER INSERT SECTION AuctioneerHomeImpl::~AuctioneerHomeImpl

}


void
AuctioneerHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
AuctioneerHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION AuctioneerHomeImpl::create
// END USER INSERT SECTION AuctioneerHomeImpl::create
    return new AuctioneerImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_AuctioneersE(void)
{
// BEGIN USER INSERT SECTION create_Auctioneers
// END USER INSERT SECTION create_Auctioneers

    return new ::auction::AuctioneerHomeImpl();
}
