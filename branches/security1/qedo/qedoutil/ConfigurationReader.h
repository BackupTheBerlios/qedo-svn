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

#ifndef __CONFIGURATION_READER_H__
#define __CONFIGURATION_READER_H__


#include "qedoutil.h"
#include "DOMXMLParser.h"


namespace Qedo {


class QEDOUTIL_API ConfigurationReader
{
private:
	static ConfigurationReader* instance_;
	ConfigurationReader();

	DOMXMLParser parser_;
	DOMElement* config_top_;
	bool broken_config_file_;

public:
	const char* lookup_config_value (const char* name);
	static ConfigurationReader* instance();
};

} // namespace Qedo

#endif
