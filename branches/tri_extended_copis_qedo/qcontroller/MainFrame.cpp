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

#include "MainFrame.h"
#include "ControllerNotebook.h"
#include "qcontroller.h"
#include "wx/artprov.h"
#include "wx/statbmp.h"
#include "HelpFrame.h"
#include "qedologo.xpm"

#include "wx/imaglist.h"

#include "wx/html/helpctrl.h"

#include "qedoicon.xpm"
#include "launcher.xpm"

#include "qedoutil.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(ID_HELP_BUTTON, MainFrame::onHelp)
	EVT_BUTTON(ID_QUIT_CONTROLLER, MainFrame::onClose)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                 long style)
    : wxFrame((wxWindow *) NULL, -1, title, pos, size, style)
{
	hf = 0;
	// set icon
	SetIcon(wxIcon(qedoicon_xpm));
	

	
	panel_ = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize,
        wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_BORDER );

	
    wxSize notebook_size(800,600);
    wxPoint notebook_point(5,5);

	hf=0;

	notebook_ = new ControllerNotebook(panel_, ID_NOTEBOOK, notebook_point, notebook_size);

	// create image list
	wxSize imagesize (32,32);
	wxImageList* notebook_image_list = new wxImageList(imagesize.GetWidth(), imagesize.GetHeight(), TRUE);

	notebook_image_list -> Add ( wxIcon(launcher_xpm));
	notebook_image_list -> Add ( wxIcon(qedoicon_xpm));

	notebook_ -> SetImageList(notebook_image_list);


	wxBoxSizer *hori_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hori_sizer2 = new wxBoxSizer(wxVERTICAL);

	sizerFrame_ = new wxBoxSizer(wxHORIZONTAL);
	sizerFrame_->Add(hori_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);
	sizerFrame_->Add(hori_sizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	panel_->SetSizer(sizerFrame_);

	notebook_ -> CreateControllerPages(hori_sizer);

	
	// set Logo
	wxBitmap qedologo_xpm( qedologo_xpm );
    wxStaticBitmap* qedo_logo = new wxStaticBitmap( panel_, wxID_STATIC, qedologo_xpm, wxDefaultPosition, wxSize(105, 31), 0 );
	hori_sizer2->Add(qedo_logo, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);



	wxSize buttonsize(110,25);
	help = new wxButton(panel_, ID_HELP_BUTTON, _T("Help"),/*wxPoint(630,470) */ wxDefaultPosition,buttonsize,0);
	hori_sizer2->Add(help, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	quit = new wxButton(panel_, ID_QUIT_CONTROLLER, _T("Close"), /* wxPoint(630,510)*/ wxDefaultPosition ,buttonsize,0);
	hori_sizer2->Add(quit, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	panel_->SetAutoLayout(TRUE);
	
}

MainFrame::~MainFrame() {

};

void MainFrame::onHelp(wxCommandEvent& event)
{

	/*
	hf = new HelpFrame("Help",wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE);
	int t=hf->Show();
	*/
	wxHtmlHelpController *help=new wxHtmlHelpController(wxHF_DEFAULT_STYLE);
	
	std::string qedo_doc = Qedo::getEnvironment ("QEDO");
	qedo_doc.append("/qedodoc/controllerdoc.hhp");

	help->AddBook(qedo_doc.c_str(),true);
	help->Display("Contents");


}

void MainFrame::onClose(wxCommandEvent& event)

{	if (hf)
	{
		hf->Destroy();
	}

	delete(this);
}
