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

#include "qcontroller.h"
#include "HelpFrame.h"
#include "wx/sizer.h"
#include "wx/stattext.h"

HelpFrame::HelpFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                 long style)
    : wxDialog((wxWindow *) NULL, -1, title, pos, size, style)
{
	wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	
	/*
	wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	//spacer
	sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);
*/
	// static text 
	wxStaticText *e_text = new wxStaticText( this, wxID_STATIC, _T("Change the destination of hostcollocation, processcollocation or homeplacements in:"), wxDefaultPosition, wxDefaultSize, 0 );
    sizerLauncher->Add(e_text, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);



}

HelpFrame::~HelpFrame()
{

};