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

#include "Launcher.h"
#include "qcontroller.h"
#include "wx/process.h"
#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/statbox.h"
#include "wx/stattext.h"
#include "wx/utils.h"
#include "wx/colour.h"
#include "wx/cmndata.h"
#include "wx/statline.h"


BEGIN_EVENT_TABLE(Launcher, wxPanel)
    EVT_BUTTON(NSD, Launcher::OnNSDStartButton)
    EVT_BUTTON(HF, Launcher::OnHFStartButton)
    EVT_BUTTON(ASSF, Launcher::OnASSFStartButton)
    EVT_BUTTON(SA, Launcher::OnSAStartButton)
    EVT_BUTTON(CI, Launcher::OnCIStartButton)

END_EVENT_TABLE()

Launcher::Launcher(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxPanel(parent, id, pos, size, style)
{
	nsd_pid_=0;
	nsd_started_ = false;

	hf_pid_ = 0; 
	hf_started_ = false;

	assf_pid_ = 0; 
	assf_started_ = false;

	sa_pid_ = 0; 
	sa_started_ = false;

	ci_pid_ = 0; 
	ci_started_ = false;

	 wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	//spacer
	sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);

	// static text 
    wxStaticText* domain_text = new wxStaticText( this, wxID_STATIC, _T("Launching Deamons for the whole Domain"), wxDefaultPosition, wxDefaultSize, 0 );
    sizerLauncher->Add(domain_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	// Name Service 
	wxStaticBox *nsbox = new wxStaticBox(this, -1, _T("&Name Service"));
	wxStaticBoxSizer *h_NSD_sizer = new wxStaticBoxSizer(nsbox,wxHORIZONTAL);
	sizerLauncher->Add(h_NSD_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	NSDStartBtn = new wxButton(this, NSD, _T("Start"));
	NSDStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_NSD_sizer-> Add(NSDStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* hostname_text = new wxStaticText( this, wxID_STATIC, _T("on Hostname or IP:"), wxDefaultPosition, wxDefaultSize, 0 );
	h_NSD_sizer->Add(hostname_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	host_name_nsd_ = new wxTextCtrl( this, ID_HOSTNAME_NSD, _T("localhost"), wxDefaultPosition, wxDefaultSize, 0 );
	h_NSD_sizer->Add(host_name_nsd_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* port_text = new wxStaticText( this, wxID_STATIC, _T("Port Number:"), wxDefaultPosition, wxDefaultSize, 0 );
    h_NSD_sizer->Add(port_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	port_number_ = new wxTextCtrl( this, ID_PORTNUMBER, _T("12356"), wxDefaultPosition, wxDefaultSize, 0 );
	h_NSD_sizer->Add(port_number_, 0, wxALIGN_CENTER_VERTICAL|wxALL,5);

	// HomeFinder
	wxStaticBox *hfbox = new wxStaticBox(this, -1, _T("&Home Finder"));
	wxStaticBoxSizer *h_HF_sizer = new wxStaticBoxSizer(hfbox,wxHORIZONTAL);
	sizerLauncher->Add(h_HF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	HFStartBtn = new wxButton(this, HF, _T("Start"));
	HFStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_HF_sizer-> Add(HFStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// AssemblyFactory
	wxStaticBox *assfbox = new wxStaticBox(this, -1, _T("&Assembly Factory"));
	wxStaticBoxSizer *h_ASSF_sizer = new wxStaticBoxSizer(assfbox,wxHORIZONTAL);
	sizerLauncher->Add(h_ASSF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	ASSFStartBtn = new wxButton(this, ASSF, _T("Start"));
	ASSFStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_ASSF_sizer-> Add(ASSFStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// line
//	wxStaticLine* line = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Node Launcher" );
//	sizerLauncher->Add(line , 0, wxGROW|wxALL, 5);
	// spacer
	sizerLauncher->Add(5, 10, 0, wxGROW | wxALL, 5);

	// static text 
    wxStaticText* node_text = new wxStaticText( this, wxID_STATIC, _T("Launching Deamons for this Node "), wxDefaultPosition, wxDefaultSize, 0 );
    sizerLauncher->Add(node_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//Server Activator
	wxStaticBox *sabox = new wxStaticBox(this, -1, _T("&Server Activator"));
	wxStaticBoxSizer *h_SA_sizer = new wxStaticBoxSizer(sabox,wxHORIZONTAL);
	sizerLauncher->Add(h_SA_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	SAStartBtn = new wxButton(this, SA, _T("Start"));
	SAStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_SA_sizer-> Add(SAStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// Component Installation
	wxStaticBox *cibox = new wxStaticBox(this, -1, _T("&Component Installation"));
	wxStaticBoxSizer *h_CI_sizer = new wxStaticBoxSizer(cibox,wxHORIZONTAL);
	sizerLauncher->Add(h_CI_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	CIStartBtn = new wxButton(this, CI, _T("Start"));
	CIStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_CI_sizer-> Add(CIStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


}

void Launcher::OnNSDStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (nsd_started_){
		wxKill (nsd_pid_, wxSIGKILL);
		nsd_started_= false;
		NSDStartBtn->SetLabel("Start");
		NSDStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		NSDStartBtn->Refresh();
	} else
	{
		wxString port_nr = port_number_->GetValue(); 
		

		wxString host_name = host_name_nsd_->GetValue();

		// get the computers name first 

		wxString cmd = "nsd -ORBIIOPAddr inet:";
		cmd.append(host_name);
		cmd.append(":");
		cmd.append(port_nr);

		wxProcess *process = new wxProcess (this);
	//	process->Redirect();
		nsd_pid_ = wxExecute(cmd, wxEXEC_ASYNC, process);
		if ( !nsd_pid_ )
		{
			wxLogError( _T("Execution of '%s' failed."), cmd.c_str() );

			delete process;
		}
		else
		{
			// change Button
			nsd_started_= true;
			NSDStartBtn->SetLabel("Stop");
			NSDStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
			NSDStartBtn->Refresh();


		}

	}
}

void Launcher::OnHFStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (hf_started_){
		wxKill (hf_pid_, wxSIGKILL);
		hf_started_= false;
		HFStartBtn->SetLabel("Start");
		HFStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		HFStartBtn->Refresh();
	} else
	{
		wxProcess *process = new wxProcess (this);
	//	process->Redirect();
		hf_pid_ = wxExecute("homefinder", wxEXEC_ASYNC, process);
		if ( !hf_pid_ )
		{
			wxLogError( _T("Execution of '%s' failed."), "homefinder" );

			delete process;
		}
		else
		{
			// change Button
			hf_started_= true;
			HFStartBtn->SetLabel("Stop");
			HFStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
			HFStartBtn->Refresh();
		}

	}
}

void Launcher::OnASSFStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (assf_started_){
		wxKill (assf_pid_, wxSIGKILL);
		assf_started_= false;
		ASSFStartBtn->SetLabel("Start");
		ASSFStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		ASSFStartBtn->Refresh();
	} else
	{
		wxProcess *process = new wxProcess (this);
	//	process->Redirect();
		assf_pid_ = wxExecute("qassf", wxEXEC_ASYNC, process);
		if ( !assf_pid_ )
		{
			wxLogError( _T("Execution of '%s' failed."), "qassf" );

			delete process;
		}
		else
		{
			// change Button
			assf_started_= true;
			ASSFStartBtn->SetLabel("Stop");
			ASSFStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
			ASSFStartBtn->Refresh();
		}

	}
}

void Launcher::OnSAStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (sa_started_){
		wxKill (sa_pid_, wxSIGKILL);
		sa_started_= false;
		SAStartBtn->SetLabel("Start");
		SAStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		SAStartBtn->Refresh();
	} else
	{
		wxProcess *process = new wxProcess (this);
	//	process->Redirect();
		sa_pid_ = wxExecute("qcsa --terminal", wxEXEC_ASYNC, process);
		if ( !sa_pid_ )
		{
			wxLogError( _T("Execution of '%s' failed."), "qcsa" );

			delete process;
		}
		else
		{
			// change Button
			sa_started_= true;
			SAStartBtn->SetLabel("Stop");
			SAStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
			SAStartBtn->Refresh();
		}

	}
}

void Launcher::OnCIStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (ci_started_){
		wxKill (ci_pid_, wxSIGKILL);
		ci_started_= false;
		CIStartBtn -> SetLabel("Start");
		CIStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		CIStartBtn -> Refresh();
	} else
	{
		wxProcess *process = new wxProcess (this);
	//	process->Redirect();
		ci_pid_ = wxExecute("qci", wxEXEC_ASYNC, process);
		if ( !ci_pid_ )
		{
			wxLogError( _T("Execution of '%s' failed."), "qci" );

			delete process;
		}
		else
		{
			// change Button
			ci_started_= true;
			CIStartBtn->SetLabel("Stop");
			CIStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
			CIStartBtn->Refresh();
		}

	}
}
