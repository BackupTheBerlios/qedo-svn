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

private:
	long nsd_pid_; 
	bool nsd_started_;

	long hf_pid_; 
	bool hf_started_;

	wxButton *NSDStartBtn; 
	wxButton *HFStartBtn;
	wxTextCtrl* port_number_;
    DECLARE_EVENT_TABLE()
};

#endif