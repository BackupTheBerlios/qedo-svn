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
#include "QedoEditor.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/statbox.h"
#include "wx/log.h"

BEGIN_EVENT_TABLE(QedoEditor, wxDialog)
	EVT_BUTTON(ID_SAVE_SETTINGS,  QedoEditor::on_save_file)
	EVT_BUTTON(ID_CQ_SETTINGS, QedoEditor::on_close)
   
END_EVENT_TABLE()


QedoEditor::QedoEditor(wxWindow *parent,wxString titel,wxString file)
     : wxDialog(parent, -1, titel, wxDefaultPosition,
					   wxSize(650,510),wxDEFAULT_DIALOG_STYLE)
{
	this->file=file;
	wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	// static text 
	wxString etext="Qedo Editor: ";
	etext.Append(file);
	wxStaticText *e_text = new wxStaticText( this, wxID_STATIC, etext, wxDefaultPosition, wxDefaultSize, 0 );
    sizerLauncher->Add(e_text, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	// TextSizer
	wxStaticBox *box3 = new wxStaticBox(this, -1, _T("&File:"));
    wxSizer *m_sizerText = new wxStaticBoxSizer(box3, wxHORIZONTAL);
	//m_sizerText->SetMinSize(150, 0);
	sizerLauncher->Add(m_sizerText, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	editctrl = new wxTextCtrl(this,-1,"",wxDefaultPosition,wxSize(600,350),wxTE_MULTILINE,wxDefaultValidator,"EditCtrl");

	editctrl->LoadFile(file);
	
	//m_sizerText->Add(editctrl, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);
	m_sizerText->Add(editctrl, 1, wxALL |
                    ( wxTE_MULTILINE ? (int)wxGROW
                                             : wxALIGN_TOP), 5);

	wxBoxSizer *downSizer=new wxBoxSizer(wxHORIZONTAL);
	sizerLauncher->Add(downSizer, 0, wxALIGN_CENTER_VERTICAL| wxALL, 5);

	wxStaticBox *downbox = new wxStaticBox(this, -1, _T("&Save or Cancel"));
	wxStaticBoxSizer *h_dow_Sizer = new wxStaticBoxSizer(downbox,wxHORIZONTAL);
	
	downSizer->Add(h_dow_Sizer, 0, wxALIGN_CENTER_VERTICAL| wxALL, 5);

	save = new wxButton(this, ID_SAVE_SETTINGS, _T("Save settings"));
	h_dow_Sizer->Add(save , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//spacer
	h_dow_Sizer->Add(415, 5, 0, wxGROW | wxALL, 5);

	
	cancel = new wxButton(this, ID_CQ_SETTINGS, _T("Close"));
	h_dow_Sizer->Add(cancel , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	
	editctrl->SetSelection(10,20);

}

QedoEditor::~QedoEditor()
{

};

void QedoEditor::on_save_file(wxCommandEvent& WXUNUSED(event))
{
	if (!(editctrl->SaveFile(file))) 
	{
		wxLogError("Save Error");
	} else {
		wxLogMessage("Save OK");
	}

}

void QedoEditor::on_close(wxCommandEvent& WXUNUSED(event))
{
	if (editctrl->IsModified())
	{
		wxLogMessage("Modified");
	} else {
		delete(this);
	}
}