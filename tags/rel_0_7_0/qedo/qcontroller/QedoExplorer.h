#ifndef __QEDOEXPLORER_H__
#define __QEDOEXPLORER_H__

#include "qcontroller.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"
#include "wx/string.h"

#include "qcexplorer.h"

// #include "ComponentDeployment.h"

class QedoExplorer : public wxPanel
{
public:
	QedoExplorer(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnStartExplorerButton(wxCommandEvent& WXUNUSED(event));
	void OnStartClientButton(wxCommandEvent& WXUNUSED(event));
	void OnRefreshExplorerTreeBtn(wxCommandEvent& WXUNUSED(event));
	void Test();
	void text_to_ib(wxString t);
private:

	long sexp_pid_;
	
	bool sclp_started_ ;
	bool sexp_started_ ;

	
    
	wxButton* start_explorer_btn;
	wxButton* start_explorer_client_btn;
	wxButton* RefreshExplorerTreeBtn;
	wxTextCtrl* hostname_;
	wxTextCtrl* port_;
	wxTextCtrl* hostname_client_;
	wxTextCtrl* port_client_;
	QCexplorerTreeCtrl* qcexplorer_ ;
	//wxTextCtrl* info_box_;
	
	
	
    DECLARE_EVENT_TABLE()

};
#endif