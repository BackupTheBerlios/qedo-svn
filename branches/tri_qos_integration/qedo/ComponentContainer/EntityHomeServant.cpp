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

#include "EntityHomeServant.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: EntityHomeServant.cpp,v 1.5.8.1 2003/09/08 10:34:42 tom Exp $";


namespace Qedo {


EntityHomeServant::EntityHomeServant()
{
}


EntityHomeServant::EntityHomeServant (const EntityHomeServant& entity_home)
: HomeServantBase (entity_home)
{
}


EntityHomeServant& EntityHomeServant::operator= (const EntityHomeServant& entity_home)
{
	return *this;
}


EntityHomeServant::~EntityHomeServant()
{
}

} // namespace Qedo
