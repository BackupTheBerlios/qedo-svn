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

#include "QedoExplorer.h"
#include "QCexplorer.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/statline.h"
#include "wx/statbox.h"
#include "wx/colour.h"
#include "wx/log.h"
#include "wx/string.h"
#include "wx/process.h"
#include "stdio.h"

#include "ConfigurationReader.h"


BEGIN_EVENT_TABLE(QedoExplorer, wxPanel)
   EVT_BUTTON(ID_START_EXPLORER_BUTTON, QedoExplorer::OnStartExplorerButton)
   EVT_BUTTON(ID_START_CLIENT_BUTTON, QedoExplorer::OnStartClientButton)
   EVT_BUTTON(ID_REFRESH_EXPLORER_TREE, QedoExplorer::OnRefreshExplorerTreeBtn)
  // EVT_TREE_ITEM_ACTIVATED(ID_ITEM_DOUBLECLICK, QedoExplorer::OnRefreshExplorerTreeBtn)
  //(ID_ITEM_RIGHTCLICK, QedoExplorer::Test)
  
END_EVENT_TABLE()

QedoExplorer::QedoExplorer(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxPanel(parent, id, pos, size, style)
{
	sexp_pid_=0;
	sexp_started_ = false;
	sclp_started_ = false;

	wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	//spacer
	sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);

	// static text 
//    wxStaticText* explorer_text = new wxStaticText( this, wxID_STATIC, _T("Qedo Explorer Settings"), wxDefaultPosition, wxDefaultSize, 0 );
//    sizerLauncher->Add(explorer_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	// Explorer Server Settings 
	wxStaticBox *expbox = new wxStaticBox(this, -1, _T("&Explorer Server Settings"));
	wxStaticBoxSizer *h_exp_sizer = new wxStaticBoxSizer(expbox,wxHORIZONTAL);
	sizerLauncher->Add(h_exp_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	start_explorer_btn = new wxButton(this, ID_START_EXPLORER_BUTTON, _T("Start ExploreServer"));
	start_explorer_btn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_exp_sizer-> Add(start_explorer_btn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//wxStaticText* hostname_text = new wxStaticText( this, wxID_STATIC, _T("on Hostname or IP:"), wxDefaultPosition, wxDefaultSize, 0 );
    //h_exp_sizer->Add(hostname_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//hostname_ = new wxTextCtrl( this, ID_HOSTNAME, _T("localhost"), wxDefaultPosition, wxDefaultSize, 0 );
	//h_exp_sizer->Add(hostname_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//wxStaticText* portnumber_text = new wxStaticText( this, wxID_STATIC, _T("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
    //h_exp_sizer->Add(portnumber_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//port_ = new wxTextCtrl( this, ID_PORT, _T("12356"), wxDefaultPosition, wxDefaultSize, 0 );
	//h_exp_sizer->Add(port_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Explore Client Settings

	wxStaticBox *exp_c_box = new wxStaticBox(this, -1, _T("&Explore Client Settings"));
	wxStaticBoxSizer *h_exp_c_sizer = new wxStaticBoxSizer(exp_c_box,wxHORIZONTAL);
	sizerLauncher->Add(h_exp_c_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	start_explorer_client_btn = new wxButton(this, ID_START_CLIENT_BUTTON, _T("Start ExplorerClient "));
	start_explorer_client_btn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_exp_c_sizer-> Add(start_explorer_client_btn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//wxStaticText* hostname_client_text = new wxStaticText( this, wxID_STATIC, _T("on Hostname or IP:"), wxDefaultPosition, wxDefaultSize, 0 );
    //h_exp_c_sizer->Add(hostname_client_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//hostname_client_ = new wxTextCtrl( this, ID_HOSTNAME_CLIENT, _T("localhost"), wxDefaultPosition, wxDefaultSize, 0 );
	//h_exp_c_sizer->Add(hostname_client_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//wxStaticText* portnumber_client_text = new wxStaticText( this, wxID_STATIC, _T("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
    //h_exp_c_sizer->Add(portnumber_client_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//port_client_ = new wxTextCtrl( this, ID_PORT_CLIENT, _T("12356"), wxDefaultPosition, wxDefaultSize, 0 );
	//h_exp_c_sizer->Add(port_client_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	
	// Explorer Tree Controll
	wxStaticBox *exp_tree_ctrl_box = new wxStaticBox(this, -1, _T("&Explorer Tree Controll"));
	wxStaticBoxSizer *h_TC_sizer = new wxStaticBoxSizer(exp_tree_ctrl_box,wxHORIZONTAL);
	sizerLauncher->Add(h_TC_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	qcexplorer_= new QCexplorerTreeCtrl (this, QCexplorerTree_Ctrl, wxDefaultPosition, wxSize(340,300), wxTR_DEFAULT_STYLE);
	h_TC_sizer->Add(qcexplorer_,0,wxALIGN_CENTER_VERTICAL|wxALL,5);

	

	wxBoxSizer * rigth_sizer = new wxBoxSizer(wxVERTICAL);
	h_TC_sizer -> Add(rigth_sizer, 0, wxALIGN_RIGHT | wxALL, 5);
	
	
	RefreshExplorerTreeBtn = new wxButton(this, ID_REFRESH_EXPLORER_TREE, _T("Refresh Explorer Tree "));
	

	rigth_sizer-> Add(RefreshExplorerTreeBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
/*
	wxStaticText* infobox_text = new wxStaticText( this, wxID_STATIC, _T("Infobox:"), wxDefaultPosition, wxDefaultSize, 0 );
	rigth_sizer->Add(infobox_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	info_box_ = new wxTextCtrl(this,wxID_STATIC,"",wxDefaultPosition,wxSize(165,240),wxTR_DEFAULT_STYLE);
	rigth_sizer->Add(info_box_,0,wxALIGN_CENTER_VERTICAL|wxALL,5);*/

//	qcexplorer_->set_info_box(info_box_);



}



void QedoExplorer::OnStartExplorerButton(wxCommandEvent& WXUNUSED(event))
{
	if (sexp_started_){
		wxKill (sexp_pid_, wxSIGKILL);
		sexp_started_= false;
		start_explorer_btn->SetLabel("Start ExploreServer");
		start_explorer_btn -> SetBackgroundColour(wxColour(255, 0, 0));
		start_explorer_btn->Refresh();
	} else
	{
		wxProcess *process = new wxProcess (this);

		// wxString portnr = port_->GetValue();
		// wxString host_name = hostname_->GetValue();

		wxString cmd = "explore_server -ORBInitRef NameService="; //corbaloc::";
		std::string ns;
		ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );
		cmd.append(ns.c_str());

		//cmd.append(host_name);
		//cmd.append(":");
		//cmd.append(portnr);
		//cmd.append("/NameService");

		sexp_pid_ = wxExecute(cmd, wxEXEC_ASYNC | wxEXEC_NOHIDE, process);
		if ( !sexp_pid_ )
		{
			wxLogError( _T("Execution of '%s' failed."), "explore_server" );

			delete process;
		}
		else
		{
			// change Button
			sexp_started_ = true;
			start_explorer_btn ->SetLabel("Stop ExploreServer");
			start_explorer_btn ->SetBackgroundColour(wxColour(0, 255, 0));
			start_explorer_btn ->Refresh();
		}

	}

}

void QedoExplorer::OnStartClientButton(wxCommandEvent& WXUNUSED(event))
{
	if (sclp_started_){

		sclp_started_= false;
		start_explorer_client_btn->SetLabel("Start ExploreClient");
		start_explorer_client_btn -> SetBackgroundColour(wxColour(255, 0, 0));
		start_explorer_client_btn->Refresh();
		qcexplorer_->clear();


	} else {
		// change Button
		sclp_started_ = true;
		start_explorer_client_btn ->SetLabel("Stop ExploreClient");
		start_explorer_client_btn ->SetBackgroundColour(wxColour(0, 255, 0));
		start_explorer_client_btn->Refresh();

		std::string ns;
		ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );

//		qcexplorer_->cmd_ns="corbaloc::";
//		wxString portnr_c=port_client_->GetValue();
//		wxString hostname_c=hostname_client_->GetValue();
//		qcexplorer_->cmd_ns.append(hostname_c);
//		qcexplorer_->cmd_ns.append(":");
//		qcexplorer_->cmd_ns.append(portnr_c);
//		qcexplorer_->cmd_ns.append("/NameService");

		qcexplorer_->cmd_ns=ns.c_str();
        qcexplorer_->OnExplorerRefresh();
	}
}

void QedoExplorer::OnRefreshExplorerTreeBtn(wxCommandEvent& WXUNUSED(event)) {
	qcexplorer_->clear();
	qcexplorer_->OnExplorerRefresh();
}


void QedoExplorer::Test() {
//	info_box_->WriteText("Test");
}
void QedoExplorer::text_to_ib(wxString t) {

	//info_box_->WriteText(t);

}


