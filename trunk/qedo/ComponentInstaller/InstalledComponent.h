/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

#ifndef __INSTALLED_COMPONENT_H__
#define __INSTALLED_COMPONENT_H__

#include <string>

namespace Qedo {

class ComponentInstallationImpl;

class InstalledComponent
{
friend class ComponentInstallationImpl;

private:
	std::string description_;
	std::string uuid_;
	std::string servant_module_;
	std::string servant_entry_point_;
	std::string executor_module_;
	std::string executor_entry_point_;

public:
	InstalledComponent (std::string, std::string, std::string, std::string, std::string);
	~InstalledComponent();
};

} // namespace Qedo

#endif
