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
#include "wx/log.h"
#include "QedoEditor.h"
#include "qedoutil.h"
#include "ConfigurationReader.h"



BEGIN_EVENT_TABLE(Launcher, wxPanel)
    EVT_BUTTON(NSD, Launcher::OnNSDStartButton)
    EVT_BUTTON(HF, Launcher::OnHFStartButton)
    EVT_BUTTON(ASSF, Launcher::OnASSFStartButton)
    EVT_BUTTON(SA, Launcher::OnSAStartButton)
    EVT_BUTTON(CI, Launcher::OnCIStartButton)
	EVT_BUTTON(ID_EDIT_CONF_START, Launcher::OnEdit_conf_Button)
	EVT_BUTTON(ID_DOMAIN_START, Launcher::OnDomain_start)
	EVT_BUTTON(ID_NODE_START, Launcher::OnNode_start)
	EVT_BUTTON(QEDOEXP, Launcher::OnExplorer_start)

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

	sexp_pid_=0;
	sexp_started_ = false;


	 wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	//spacer
	//sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);

	// static text 
    //wxStaticText* start_text = new wxStaticText( this, wxID_STATIC, _T("The Qedo Start Center "), wxDefaultPosition, wxDefaultSize, 0 );
  //  sizerLauncher->Add(start_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	wxBoxSizer *hori_sizer=new wxBoxSizer(wxHORIZONTAL);
	sizerLauncher->Add(hori_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);


	// Qedo start center 
	wxStaticBox *stbox = new wxStaticBox(this, -1, _T("&The Qedo start center"));
	wxStaticBoxSizer *h_st_sizer = new wxStaticBoxSizer(stbox,wxVERTICAL);
	hori_sizer->Add(h_st_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxBoxSizer *w_h_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_st_sizer->Add(w_h_sizer,0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxStaticText* d_text = new wxStaticText( this, wxID_STATIC, _T("Start the deamons for the whole domain:"), wxDefaultPosition, wxDefaultSize, 0 );
	w_h_sizer->Add(d_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	DomainStartBtn = new wxButton(this, ID_DOMAIN_START, _T("Start deamons"));
	DomainStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	w_h_sizer-> Add(DomainStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// line
	wxStaticLine* line = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Node Launcher" );
	h_st_sizer->Add(line , 0, wxGROW|wxALL, 5);

	

	// new line deamons for this node
	wxBoxSizer *w_h2_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_st_sizer->Add(w_h2_sizer,0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxStaticText* n_text = new wxStaticText( this, wxID_STATIC, _T("Start the deamons for the this node       :"), wxDefaultPosition, wxDefaultSize, 0 );
	w_h2_sizer->Add(n_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	NodeStartBtn = new wxButton(this, ID_NODE_START, _T("Start deamons"));
	NodeStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	w_h2_sizer-> Add(NodeStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5); 

	

    // the sizer for edit button
	wxStaticBox *edbox = new wxStaticBox(this, -1, _T("&The Qedo edit center"));
	wxStaticBoxSizer *h_ed_sizer = new wxStaticBoxSizer(edbox,wxVERTICAL);
	hori_sizer->Add(h_ed_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	

	// edit button for qedo conf
	
	wxBoxSizer *w_h3_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_ed_sizer->Add(w_h3_sizer,0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);
	
	wxStaticText* e_q_text = new wxStaticText( this, wxID_STATIC, _T("Edit the file qedo.conf:"), wxDefaultPosition, wxDefaultSize, 0 );
	w_h3_sizer->Add(e_q_text , 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	EditConfBtn = new wxButton(this, ID_EDIT_CONF_START, _T("Edit conf"));
	//EditConfBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	w_h3_sizer-> Add(EditConfBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5); 

		
	//spacer
	//sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);

	// static text 
	//wxStaticText* domain_text = new wxStaticText( this, wxID_STATIC, _T("You can manual launching deamons for the whole domain:"), wxDefaultPosition, wxDefaultSize, 0 );
    //sizerLauncher->Add(domain_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	// Name Service 
	wxStaticBox *nsbox = new wxStaticBox(this, -1, _T("&You can manual launching deamons for the whole domain:"));
	wxStaticBoxSizer *h_whole_domain_sizer = new wxStaticBoxSizer(nsbox,wxVERTICAL);
    
	sizerLauncher->Add(h_whole_domain_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxBoxSizer *h_NSD_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_whole_domain_sizer->Add(h_NSD_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxStaticText* nsd_text = new wxStaticText( this, wxID_STATIC, _T("Name Service          :"), wxDefaultPosition, wxDefaultSize, 0 );
	h_NSD_sizer->Add(nsd_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	NSDStartBtn = new wxButton(this, NSD, _T("Start"));
	NSDStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_NSD_sizer-> Add(NSDStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* hostname_text = new wxStaticText( this, wxID_STATIC, _T("on Hostname or IP:"), wxDefaultPosition, wxDefaultSize, 0 );
	h_NSD_sizer->Add(hostname_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	host_name_nsd_ = new wxTextCtrl( this, ID_HOSTNAME_NSD, _T("localhost"), wxDefaultPosition, wxSize(80,21), 0 );
	h_NSD_sizer->Add(host_name_nsd_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	host_name_nsd_->Clear();
	host_name_nsd_->AppendText(wxGetFullHostName());
	

    wxStaticText* port_text = new wxStaticText( this, wxID_STATIC, _T("Port Number:"), wxDefaultPosition, wxDefaultSize, 0 );
    h_NSD_sizer->Add(port_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	port_number_ = new wxTextCtrl( this, ID_PORTNUMBER, _T("12356"), wxDefaultPosition, wxSize(65,21), 0 );
	h_NSD_sizer->Add(port_number_, 0, wxALIGN_CENTER_VERTICAL|wxALL,5);

	// HomeFinder
	//wxStaticBox *hfbox = new wxStaticBox(this, -1, _T("&Home Finder"));
	//wxStaticBoxSizer *h_HF_sizer = new wxStaticBoxSizer(hfbox,wxHORIZONTAL);
//	sizerLauncher->Add(h_HF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);
	wxStaticLine* line2 = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Line2" );
	h_whole_domain_sizer->Add(line2 , 0, wxGROW|wxALL, 5);

	wxBoxSizer *h_HF_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_whole_domain_sizer->Add(h_HF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	

	wxStaticText* hf_text = new wxStaticText( this, wxID_STATIC, _T("Home Finder            :"), wxDefaultPosition, wxDefaultSize, 0 );
	h_HF_sizer->Add(hf_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	HFStartBtn = new wxButton(this, HF, _T("Start"));
	HFStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_HF_sizer-> Add(HFStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//line
	wxStaticLine* line3 = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Line3" );
	
	h_whole_domain_sizer->Add(line3 , 0, wxGROW|wxALL, 5);



	// AssemblyFactory

	wxBoxSizer *h_ASSF_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_whole_domain_sizer->Add(h_ASSF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	//wxStaticBox *assfbox = new wxStaticBox(this, -1, _T("&Assembly Factory"));
	//wxStaticBoxSizer *h_ASSF_sizer = new wxStaticBoxSizer(assfbox,wxHORIZONTAL);
	//sizerLauncher->Add(h_ASSF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxStaticText* assf_text = new wxStaticText( this, wxID_STATIC, _T("Assembly Factory    :"), wxDefaultPosition, wxDefaultSize, 0 );
	h_ASSF_sizer->Add(assf_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	ASSFStartBtn = new wxButton(this, ASSF, _T("Start"));
	ASSFStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_ASSF_sizer-> Add(ASSFStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//line
	wxStaticLine* line3b = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Line3" );
	
	h_whole_domain_sizer->Add(line3b , 0, wxGROW|wxALL, 5);

	wxBoxSizer *h_exp_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_whole_domain_sizer->Add(h_exp_sizer,0,wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND,5);

	wxStaticText* expl_text = new wxStaticText( this, wxID_STATIC, _T("Qedo Explorer         :"), wxDefaultPosition, wxDefaultSize, 0 );
	h_exp_sizer->Add(expl_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	QedoExplorerBtn = new wxButton(this, QEDOEXP, _T("Start"));
	QedoExplorerBtn -> SetBackgroundColour(wxColour(255,0,0));
	h_exp_sizer->Add(QedoExplorerBtn,0,wxALIGN_CENTER_VERTICAL|wxALL,5);

	// static text 
	//wxStaticText* node_text = new wxStaticText( this, wxID_STATIC, _T("You can manual launching deamons for this node: "), wxDefaultPosition, wxDefaultSize, 0 );
    //sizerLauncher->Add(node_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//Server Activator
	wxStaticBox *sabox = new wxStaticBox(this, -1, _T("&You can manual launching deamons for this node: "));
	wxStaticBoxSizer *h_node_sizer = new wxStaticBoxSizer(sabox,wxVERTICAL);
	sizerLauncher->Add(h_node_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxBoxSizer *h_SA_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_node_sizer->Add(h_SA_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxStaticText* sa_text = new wxStaticText( this, wxID_STATIC, _T("Server Activator      :"), wxDefaultPosition, wxDefaultSize, 0 );
	h_SA_sizer->Add(sa_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	SAStartBtn = new wxButton(this, SA, _T("Start"));
	SAStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_SA_sizer-> Add(SAStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//line
	wxStaticLine* line4 = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Line4" );
	
	h_node_sizer->Add(line4 , 0, wxGROW|wxALL, 5);




	// Component Installation

	wxBoxSizer *h_CI_sizer = new wxBoxSizer(wxHORIZONTAL);
	h_node_sizer->Add(h_CI_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);


	//wxStaticBox *cibox = new wxStaticBox(this, -1, _T("&Component Installation"));
	//wxStaticBoxSizer *h_CI_sizer = new wxStaticBoxSizer(cibox,wxHORIZONTAL);
	//sizerLauncher->Add(h_CI_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	wxStaticText* ci_text = new wxStaticText( this, wxID_STATIC, _T("Component Installer:"), wxDefaultPosition, wxDefaultSize, 0 );
	h_CI_sizer->Add(ci_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	CIStartBtn = new wxButton(this, CI, _T("Start"));
	CIStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
	h_CI_sizer-> Add(CIStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);



}

void Launcher::OnNSDStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	startNSD();
}

void Launcher::OnHFStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	startHF();
}

void Launcher::OnASSFStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	startASSF();
}

void Launcher::OnExplorer_start(wxCommandEvent& WXUNUSED(event))
{
	startEXP();
}

void Launcher::OnSAStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	startSA();
}

void Launcher::OnCIStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	startCI();
}

void Launcher::OnEdit_conf_Button(wxCommandEvent& WXUNUSED(event))
{
	wxString titel="Qedo Editor ";
	
	std::string qedo_config = Qedo::getEnvironment ("QEDO");

	#ifdef _WIN32
		qedo_config += "\\etc\\Qedo.conf";
	#else
		qedo_config += "/etc/Qedo.conf";
	#endif

	titel.Append(qedo_config.c_str());
	QedoEditor *qedoedit = new QedoEditor(this,titel, qedo_config.c_str());
	
	int t=qedoedit->ShowModal();
	if (t==wxID_OK) {
		
	}

	if (t==wxID_CANCEL) {
		
		qedoedit->~QedoEditor();
	}
}

void Launcher::OnDomain_start(wxCommandEvent& WXUNUSED(event))
{
	if (nsd_started_ & hf_started_ & assf_started_ & sexp_started_)
	{
		startNSD();
		startHF();
		startASSF();
		startEXP();
		DomainStartBtn->SetLabel("Start");
		DomainStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		DomainStartBtn->Refresh();
	} else {
		startNSD();
		startHF();
		startASSF();
		startEXP();
		DomainStartBtn->SetLabel("Stop");
		DomainStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
		DomainStartBtn->Refresh();


	}


}

void Launcher::OnNode_start(wxCommandEvent& WXUNUSED(event))
{
	if (sa_started_ & ci_started_)
	{
		startSA();
		startCI();
		NodeStartBtn->SetLabel("Start");
		NodeStartBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		NodeStartBtn->Refresh();
	} else {
		startSA();
		startCI();
		NodeStartBtn->SetLabel("Stop");
		NodeStartBtn -> SetBackgroundColour(wxColour(0, 255, 0));
		NodeStartBtn->Refresh();


	}

}

void Launcher::startNSD()
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

void Launcher::startHF()
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

void Launcher::startASSF()
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
void Launcher::startEXP()
{
	if (sexp_started_){
		wxKill (sexp_pid_, wxSIGKILL);
		sexp_started_= false;
		QedoExplorerBtn->SetLabel("Start");
		QedoExplorerBtn -> SetBackgroundColour(wxColour(255, 0, 0));
		QedoExplorerBtn->Refresh();
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
			QedoExplorerBtn ->SetLabel("Stop");
			QedoExplorerBtn ->SetBackgroundColour(wxColour(0, 255, 0));
			QedoExplorerBtn ->Refresh();
		}

	}
}
void Launcher::startSA()
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

void Launcher::startCI()
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