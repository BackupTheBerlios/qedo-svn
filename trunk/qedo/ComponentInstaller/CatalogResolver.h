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

#ifndef __CATALOGRESOLVER_H__
#define __CATALOGRESOLVER_H__


#include "XMLCatalog.h"
#include <map>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>


namespace Qedo {


class CatalogResolver : public EntityResolver
{
public:
    CatalogResolver (const XMLCatalog & aCatalog);
    virtual ~CatalogResolver();
    InputSource* resolveEntity( const XMLCh* const publicId, 
                                const XMLCh* const systemId );

private:
    XMLCatalog mCatalog;
};


}
#endif

