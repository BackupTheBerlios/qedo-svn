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

#include "ControllerNotebook.h"
#include "NSBrowser.h"
#include "wx/button.h"
#include "Launcher.h"
#include "Deployment.h"
#include "QCexplorer.h"
#include "QedoExplorer.h"


BEGIN_EVENT_TABLE(ControllerNotebook, wxNotebook)
    EVT_BUTTON(NSD_TREE_REFRESH,  ControllerNotebook::OnNSDRefresh)
	EVT_BUTTON(EXPLORER_TREE_REFRESH, ControllerNotebook::OnExplorerRefresh)

END_EVENT_TABLE()

ControllerNotebook::ControllerNotebook(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style)
    : wxNotebook(parent, id, pos, size, style)
{
    // Empty
}


void ControllerNotebook::CreateControllerPages(wxBoxSizer * sizerFrame)
{
	 sizerNotebook_ = new wxNotebookSizer(this);
	 sizerFrame->Add(sizerNotebook_, 1, wxEXPAND | wxALL, 4);

	 // create launcher
	 launcher_panel_ = new Launcher (this, Launcher_ID, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	 AddPage(launcher_panel_, wxT("Launcher"), FALSE,0);

	// create ns_browser page
	ns_browser_panel = new wxPanel(this);
	ns_browser_ = new NSBrowserTreeCtrl (ns_browser_panel, NSBrowserTree_Ctrl, wxDefaultPosition, wxSize(400,400), wxTR_DEFAULT_STYLE );
	AddPage( ns_browser_panel, wxT("NS Browser"), FALSE, 0 );

	// create Deployment page
	 deployment_panel_ = new Deployment(this, DEPLOYMENT_ID, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	 AddPage(deployment_panel_, wxT("Deployment"), FALSE,0);

    // create Explorer page
	 //qcexplorer_panel = new wxPanel(this);
	// qcexplorer_=new QCexplorerTreeCtrl (qcexplorer_panel, QCexplorerTree_Ctrl, wxDefaultPosition, wxSize(200,200), wxTR_DEFAULT_STYLE);
	// AddPage(qcexplorer_panel, wxT("Explorer"), FALSE,0);

	// create Explorer page
	 explorer_panel=new QedoExplorer(this, QEDOEXPLORER_ID, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	 AddPage(explorer_panel,wxT("Explorer"), FALSE,0);

	 


    SetSelection(0);

}

void 
ControllerNotebook::OnNSDRefresh(wxCommandEvent& WXUNUSED(event))
{
//	int sel = event.GetSelection();
//	if (sel == 1)
//	{
		// rebiuld NS Browser Tree
	ns_browser_ -> OnNSDRefresh();
//	};

};

void
ControllerNotebook::OnExplorerRefresh(wxCommandEvent& WXUNUSED(event))
{

	qcexplorer_ -> OnExplorerRefresh();

}



