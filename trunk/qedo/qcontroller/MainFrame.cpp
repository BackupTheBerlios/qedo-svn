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
#include "qedologo.xpm"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                 long style)
    : wxFrame((wxWindow *) NULL, -1, title, pos, size, style)
{

	  panel_ = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize,
        wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_BORDER);

    wxSize notebook_size(800,600);
    wxPoint notebook_point(5,5);

	 notebook_ = new ControllerNotebook(panel_, ID_NOTEBOOK, notebook_point, notebook_size);

	 // create image list
	wxSize imagesize (32,32);
	wxImageList* notebook_image_list = new wxImageList(imagesize.GetWidth(), imagesize.GetHeight(), TRUE);

	notebook_image_list -> Add ( wxArtProvider::GetIcon(wxART_INFORMATION, wxART_OTHER, imagesize));

	notebook_ -> SetImageList(notebook_image_list);


	 sizerFrame_ = new wxBoxSizer(wxBOTH);
	 panel_->SetSizer(sizerFrame_);

	 notebook_ -> CreateControllerPages(sizerFrame_);


	 // set Logo
	wxBitmap qedologo_xpm( qedologo_xpm );
    wxStaticBitmap* qedo_logo = new wxStaticBitmap( panel_, wxID_STATIC, qedologo_xpm, wxPoint(605,20), wxSize(105, 31), 0 );


	 panel_->SetAutoLayout(TRUE);

//	 sizerFrame_->Fit(this);

//	 Centre(wxBOTH);
	 


}

MainFrame::~MainFrame() {

};

