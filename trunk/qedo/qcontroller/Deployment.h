#ifndef __DEPLOYMENT_H__
#define __DEPLOYMENT_H__

#include "qcontroller.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"
#include "wx/listctrl.h"
#include "wx/filedlg.h"

#include "ComponentDeployment.h"

class Deployment : public wxPanel
{
public:
	Deployment(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnDeployButton(wxCommandEvent& WXUNUSED(event));
	void OnFileChoiseButton(wxCommandEvent& WXUNUSED(event));
	void OnUndeployButton(wxCommandEvent& WXUNUSED(event));

private:
	struct r_assemblies{
		int id;
		Qedo::ComponentDeployment* reference;
	};

	typedef std::list < r_assemblies > running_assemblies_;
	running_assemblies_ running_assemblies;
	long assemblies_counter_;
	
	CORBA::ORB_var orb; 
	wxTextCtrl* assembly_name_;
	wxButton* file_choice_btn;
	wxButton* deploy_btn;
	wxListCtrl* running_ass_list;
	wxButton* undeploy_btn;
	wxFileDialog* file_dialog;
	

    DECLARE_EVENT_TABLE()

};
#endif