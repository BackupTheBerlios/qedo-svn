#ifndef __LAUNCHER_H__
#define __LAUNCHER_H__

#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"

class Launcher : public wxPanel
{
public:
	Launcher(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnNSDStartButton(wxCommandEvent& WXUNUSED(event));
	void OnHFStartButton(wxCommandEvent& WXUNUSED(event));
	void OnASSFStartButton(wxCommandEvent& WXUNUSED(event));
	void OnSAStartButton(wxCommandEvent& WXUNUSED(event));
	void OnCIStartButton(wxCommandEvent& WXUNUSED(event));
	//wxTextCtrl* port_number_;

private:
	long nsd_pid_; 
	bool nsd_started_;
	long hf_pid_; 
	bool hf_started_;
	long assf_pid_; 
	bool assf_started_;
	long sa_pid_; 
	bool sa_started_;
	long ci_pid_; 
	bool ci_started_;

	wxButton *NSDStartBtn; 
	wxButton *HFStartBtn;
	wxButton *ASSFStartBtn;
	wxButton *SAStartBtn;
	wxButton *CIStartBtn;
	//wxTextCtrl* host_name_nsd_;
	wxTextCtrl* port_number_;
	
	
	
	
    DECLARE_EVENT_TABLE()
};

#endif