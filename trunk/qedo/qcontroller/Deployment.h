#ifndef __DEPLOYMENT_H__
#define __DEPLOYMENT_H__

#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"
#include "wx/listctrl.h"

class Deployment : public wxPanel
{
public:
	Deployment(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnDeployButton(wxCommandEvent& WXUNUSED(event));

private:
	wxTextCtrl* assembly_name_;
	wxButton* file_choice_btn;
	wxButton* deploy_btn;
	wxListCtrl* running_ass_list;
	wxButton* undeploy_btn;
    DECLARE_EVENT_TABLE()

};
#endif