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

#ifndef __CCM_CONTEXT_H__
#define __CCM_CONTEXT_H__


#include <CORBA.h>
#include <Components.h>
#include "CCMObjectExecutor.h"
#include "RefCountBase.h"
#include "Util.h"
#include "ContainerInterfaceImpl.h"


namespace Qedo {


/**
 * @defgroup Runtime Component Runtime Environment
 * This is the Qedo runtime support for CORBA components.
 * The Qedo project is designed to work with arbitrary ORB implementations
 * which support at least a basic set of features. This set comprises OBV, ...
 * Anyway, for each ORB implementation some minimal changes have to be done.
 * Currently ORBacus 4.1 and MICO are supported by deafault. In order to install
 * Qedo a supported ORB implementation has to be installed on the target host.
 * Pay attention that it has to be dynamically linked and the linker can find
 * the according libraries.
 *
 *	ORBacus	      ---> available at http://www.orbacus.com
 *	
 * or
 *	
 *	Mico          ---> available at http://www.mico.org
 *	All the instructions for compiling under Windows and Linux/Unix are
 *	given in the Mico package.
 *
 * According to the CCM specification the Qedo project makes use of software
 * packaging. In order to install Qedo the zlib 1.1.4 or a later version has
 * to be installed on the target host.
 *
 *	Zlib          ---> available at http://www.gzip.org/zlib/
 *	All the instructions for compiling under Linux/Unix are given in the
 *	Zlib package.
 *
 * The Qedo project furthermore requires the xerces-c2_1 XML library to
 * handle the deployment XML descriptors.
 *
 *	Xerces-c      ---> available at xml.apache.org/dist/xerces-c
 *	All the instructions for compiling under Windows and Linux/Unix are
 *	given in the Xerces-c package.
 *
 * Automatic packaging under Windows requires the command line version of winzip,
 * to be downloaded from www.winzip.com. Make sure, it is in your path.
 * @{
 */


/**
 * @defgroup ComponentContainer Component Container
 * dynamic library ...
 * @{
 */


class ContainerInterfaceImpl;
class ServiceReferenceEntry;


class CONTAINERDLL_API ThreadSupport : public virtual Components::CCMContext
{
	public:
	/**
	 * implements IDL:omg.org/Components/CCMContext/start_thread:1.0
	 */

   Components::Thread_ptr start_thread( Components::Function func, Components::FunctionData data );

	/**
	 * implements IDL:omg.org/Components/CCMContext/create_mutex:1.0
	 */

   Components::Mutex_ptr create_mutex();

	/**
	 * implements IDL:omg.org/Components/CCMContext/create_cond:1.0
	 */

   Components::Cond_ptr create_cond();
};

/**
 * implementation of IDL:omg.org/Components/CCMContext:1.0
 */
class CONTAINERDLL_API CCMContext : public virtual Components::CCMContext,
									public virtual RefCountLocalObject,
									public virtual ThreadSupport
{
	/** needs access to ccm_object_executor_ */
	friend class InternalConfiguration;

protected:
	/** the object executor for the component */
	CCMObjectExecutor*						ccm_object_executor_;

	/** the container interface where the components home is installed in */
	ContainerInterfaceImpl*					container_;

	/** the list of component instance specific service references */
	std::vector < ServiceReferenceEntry >	service_references_;

public:
	/**
	 * constructor
	 */
	CCMContext();

	/**
	 * destructor
	 */
	~CCMContext();

	/**
	 * sets the container where the home of the component is installed in
	 * \param container The container where the home of the component is installed in.
	 */
	void container(ContainerInterfaceImpl*);

	/**
	 * qeue events for delivering
	 * \param consumer The consumer is the receiver of the event.
	 * \param ev The ev is the event to be deliver.
	 */
	void queue_event(Components::EventConsumerBase_ptr, Components::EventBase*, CORBA::Long);

	/**
	 * qeue events for delivering
	 * \param consumers The consumers are the receivers of the event.
	 * \param ev The ev is the event to be deliver.
	 */
	void queue_event(const SubscribedConsumerVector&, Components::EventBase*, CORBA::Long);

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_caller_principal:1.0
	 * (not implemented yet)
	 * \return The caller principal.
	 */
	Components::Principal get_caller_principal();

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_CCM_home:1.0
	 * provide the home of the component
	 * \return The object reference of the component home. 
	 */
	Components::CCMHome_ptr get_CCM_home();

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_rollback_only:1.0
	 * (not implemented yet)
	 */
    CORBA::Boolean get_rollback_only()
		throw (Components::IllegalState);

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_user_transaction:1.0
	 * (not implemented yet)
	 */
    Components::Transaction::UserTransaction_ptr get_user_transaction()
		throw (Components::IllegalState);

	/**
	 * implements IDL:omg.org/Components/CCMContext/is_caller_in_role:1.0
	 * (not implemented yet)
	 */
    CORBA::Boolean is_caller_in_role (const char*);

	/**
	 * implements IDL:omg.org/Components/CCMContext/set_rollback_only:1.0
	 * (not implemented yet)
	 */
    void set_rollback_only()
		throw (Components::IllegalState);

	/**
	 * implements IDL:omg.org/Components/CCMContext/resolve_service_reference:1.0
     * Qedo CCM extension to allow generic handling of service integration
	 */
    CORBA::Object_ptr resolve_service_reference(const char*)
		throw (Components::CCMException);
};


/**
 * context for an executor
 */
class CONTAINERDLL_API ExecutorContext : public virtual CCMContext
{
public:
	/**
	 * constructor
	 */
	ExecutorContext();

	/**
	 * destructor
	 */
	~ExecutorContext();

	/**
	 * sets the object executor
	 * \param ccm_object_exec The object executor.
	 */
	void ccm_object_executor (CCMObjectExecutor*);
};


/**
 * context for an home executor
 */
class CONTAINERDLL_API HomeExecutorContext : public virtual Components::CCMContext,
											 public virtual RefCountLocalObject,
											 public virtual ThreadSupport
{
private:
	Components::CCMHome_var my_home_ref_;

public:
	/**
	 * constructor
	 */
	HomeExecutorContext (Components::CCMHome_ptr);

	/**
	 * destructor
	 */
	~HomeExecutorContext();

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_caller_principal:1.0
	 * (not implemented yet)
	 * \return The caller principal.
	 */
	Components::Principal get_caller_principal();

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_CCM_home:1.0
	 * provide the home of the component
	 * \return The object reference of the component home. 
	 */
	Components::CCMHome_ptr get_CCM_home();

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_rollback_only:1.0
	 * (not implemented yet)
	 */
    CORBA::Boolean get_rollback_only()
		throw (Components::IllegalState);

	/**
	 * implements IDL:omg.org/Components/CCMContext/get_user_transaction:1.0
	 * (not implemented yet)
	 */
    Components::Transaction::UserTransaction_ptr get_user_transaction()
		throw (Components::IllegalState);

	/**
	 * implements IDL:omg.org/Components/CCMContext/is_caller_in_role:1.0
	 * (not implemented yet)
	 */
    CORBA::Boolean is_caller_in_role (const char*);

	/**
	 * implements IDL:omg.org/Components/CCMContext/set_rollback_only:1.0
	 * (not implemented yet)
	 */
    void set_rollback_only()
		throw (Components::IllegalState);

	/**
	 * implements IDL:omg.org/Components/CCMContext/resolve_service_reference:1.0
     * Qedo CCM extension to allow generic handling of service integration
	 */
    CORBA::Object_ptr resolve_service_reference(const char*)
		throw (Components::CCMException);
};


/** @} */

} // namespace Qedo


#endif

