/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

#ifndef __SESSION_HOME_SERVANT_H__
#define __SESSION_HOME_SERVANT_H__

#include "CCMHomeServant.h"
#include "Util.h"

namespace Qedo {

class CONTAINERDLL_API SessionHomeServant : public CCMHomeServant
{
private:
	void before_remove_component (Components::ExecutorLocator_ptr);
	void do_finalize_component_incarnation (Components::ExecutorLocator_ptr);

public:
	SessionHomeServant ();
	SessionHomeServant (const SessionHomeServant&);
	SessionHomeServant& operator= (const SessionHomeServant&);
	~SessionHomeServant();
};

} // namespace Qedo

#endif

