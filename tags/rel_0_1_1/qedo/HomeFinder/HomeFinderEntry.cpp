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

static char rcsid[] = "$Id: HomeFinderEntry.cpp,v 1.2 2003/04/01 07:50:10 neubauer Exp $";

#include "HomeFinderEntry.h"


namespace Qedo {


HomeFinderEntry::HomeFinderEntry(const char* home_repid, const char* comp_repid, const char* name, Components::CCMHome_ptr home)
: home_repid_(home_repid)
, comp_repid_(comp_repid)
, name_(name)
, home_(Components::CCMHome::_duplicate(home))
{
	cookie_ = new Cookie_impl();
}


HomeFinderEntry::~HomeFinderEntry()
{
}


} // namespace