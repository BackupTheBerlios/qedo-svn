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

#include "HomeFinderEntry.h"

static char rcsid[] UNUSED = "$Id: HomeFinderEntry.cpp,v 1.6 2004/04/01 15:13:51 tom Exp $";


namespace Qedo {


HomeFinderEntry::HomeFinderEntry(const char* home_repid, const char* comp_repid, const char* name, Components::CCMHome_ptr home)
: home_repid_(home_repid)
, comp_repid_(comp_repid)
, name_(name)
, home_(Components::CCMHome::_duplicate(home))
{
	cookie_ = new Cookie_impl();
}


HomeFinderEntry::HomeFinderEntry (const HomeFinderEntry& entry)
: cookie_(entry.cookie_)
, home_repid_(entry.home_repid_)
, comp_repid_(entry.comp_repid_)
, name_(entry.name_)
, home_(Components::CCMHome::_duplicate(const_cast<HomeFinderEntry&>(entry).home_))
{
	cookie_->_add_ref();
}


HomeFinderEntry&
HomeFinderEntry::operator= (const HomeFinderEntry& entry)
{
	if (&entry == this)
	{
		return *this;
	}

	home_repid_ = entry.home_repid_;
	comp_repid_ = entry.comp_repid_;
	name_ = entry.name_;

	home_ = Components::CCMHome::_duplicate(const_cast<HomeFinderEntry&>(entry).home_);

	entry.cookie_ -> _add_ref();

	assert (cookie_);
	cookie_->_remove_ref();

	cookie_ = entry.cookie_;

	return *this;
}


HomeFinderEntry::~HomeFinderEntry()
{
	cookie_->_remove_ref();
}


} // namespace
