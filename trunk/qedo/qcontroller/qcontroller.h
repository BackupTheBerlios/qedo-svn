/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
/*                                                                         */
/* Copyright (C) 2002-2004 by the Qedo Team                                */
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

#ifndef __QCONTROLLER_H__
#define __QCONTROLLER_H__

#include "wx/app.h"
#include "coss/CosNaming.h"


// Define a new application
class QedoController : public wxApp
{
public:
    bool OnInit();
    void OnAssert(const wxChar *file,
                          int line,
                          const wxChar *cond,
                          const wxChar *msg);

	

};

DECLARE_APP(QedoController)


enum ID_CONTROLS
{
    ID_NOTEBOOK = wxID_HIGHEST,
	NSBrowserTree_Ctrl,
	QCexplorerTree_Ctrl,
	Launcher_ID,
	DEPLOYMENT_ID,
	QEDOEXPLORER_ID,
	START_EXPLORER_BUTTON,
	ID_START_EXPLORER_BUTTON,
	ID_START_CLIENT_BUTTON,
	ID_HOSTNAME,
	ID_PORT,
	ID_HOSTNAME_CLIENT,
	ID_PORT_CLIENT,
	ID_REFRESH_EXPLORER_TREE,
	NSD,
	ID_PORTNUMBER,
	HF,
	NSD_TREE_REFRESH,
	EXPLORER_TREE_REFRESH,
	ASSF,
	SA,
	CI,
	ID_ASSNAME_TEXTCTRL,
	ID_FILE_CHOICE_BUTTON,
	ID_DEPLOY_BUTTON,
	ID_RUNNING_LISTCTRL,
	ID_UNDEPLOY_BUTTON,
	ID_ITEM_DOUBLECLICK,
	ID_ITEM_RIGHTCLICK,
	ID_HOSTNAME_NSD
	
};

#endif

