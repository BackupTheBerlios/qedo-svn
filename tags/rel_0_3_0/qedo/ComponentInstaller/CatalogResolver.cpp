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

#include "CatalogResolver.h"


#include <string>
#include <iostream>
#include <xercesc/framework/URLInputSource.hpp>


namespace Qedo {

	
CatalogResolver::CatalogResolver (const XMLCatalog & aCatalog)
	: mCatalog (aCatalog)
{
}


CatalogResolver::~CatalogResolver ()
{
}


InputSource*
CatalogResolver::resolveEntity (const XMLCh* const publicId, const XMLCh* const systemId)
{
    URI target;
    if (publicId && mCatalog.lookup(std::string(XMLString::transcode(publicId)), target))
    {
        target = mCatalog.lookup(target);
    }
    else
    {
        if (!(systemId && mCatalog.lookup(URI(XMLString::transcode(systemId)), target)))
        {
            // lookup failed
            std::cerr << "CatalogResolver: unable to resolve public id \"" << XMLString::transcode(publicId) << "\"\n";
            return 0;
        }
    }

    return new URLInputSource(XMLURL(target.getText()));
}

} // namespace HU_CCM_Container
