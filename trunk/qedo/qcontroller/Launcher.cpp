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


BEGIN_EVENT_TABLE(Launcher, wxPanel)
    EVT_BUTTON(NSD, Launcher::OnNSDStartButton)
    EVT_BUTTON(HF, Launcher::OnHFStartButton)


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


	 wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);

	// Name Service 
	wxStaticBox *nsbox = new wxStaticBox(this, -1, _T("&Name Service"));
	wxStaticBoxSizer *h_NSD_sizer = new wxStaticBoxSizer(nsbox,wxHORIZONTAL);
	sizerLauncher->Add(h_NSD_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	NSDStartBtn = new wxButton(this, NSD, _T("Start NameService"));
	h_NSD_sizer-> Add(NSDStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* port_text = new wxStaticText( this, wxID_STATIC, _T("Port Number:"), wxDefaultPosition, wxDefaultSize, 0 );
    h_NSD_sizer->Add(port_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	port_number_ = new wxTextCtrl( this, ID_PORTNUMBER, _T("12356"), wxDefaultPosition, wxDefaultSize, 0 );
	h_NSD_sizer->Add(port_number_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// HomeFinder
	wxStaticBox *hfbox = new wxStaticBox(this, -1, _T("&HomeFinder"));
	wxStaticBoxSizer *h_HF_sizer = new wxStaticBoxSizer(hfbox,wxHORIZONTAL);
	sizerLauncher->Add(h_HF_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	HFStartBtn = new wxButton(this, HF, _T("Start HomeFinder"));
	h_HF_sizer-> Add(HFStartBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	// AssemblyFactory

}

void Launcher::OnNSDStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (nsd_started_){
		wxKill (nsd_pid_, wxSIGKILL);
		nsd_started_= false;
		NSDStartBtn->SetLabel("Start NameService");
		NSDStartBtn->Refresh();
	} else
	{
		wxString port_nr = port_number_->GetValue(); 
		
		wxString host_name = wxGetHostName();
		// get the computers name first 

		wxString cmd = "nsd -ORBIIOPAddr inet:";
		cmd.append(host_name);
		cmd.append(":");
		cmd.append(port_nr);

		wxProcess *process = new wxProcess (this);
		process->Redirect();
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
			NSDStartBtn->SetLabel("Stop NameService");
			NSDStartBtn->Refresh();


		}

	}
}

void Launcher::OnHFStartButton(wxCommandEvent& WXUNUSED(event)) 
{
	if (hf_started_){
		wxKill (hf_pid_, wxSIGKILL);
		hf_started_= false;
		HFStartBtn->SetLabel("Start HomeFinder");
		HFStartBtn->Refresh();
	} else
	{
		wxProcess *process = new wxProcess (this);
		process->Redirect();
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
			HFStartBtn->SetLabel("Stop HomeFinder");
			HFStartBtn->Refresh();
		}

	}
}

