#include "wx/notebook.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "NSBrowser.h"
#include "QCexplorer.h"

#ifndef __CONTROLLERNOTEBOOK_H__
#define __CONTROLLERNOTEBOOK_H__

class ControllerNotebook : public wxNotebook
{
public:
    ControllerNotebook(wxWindow *parent, wxWindowID id = -1,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0);

    void CreateControllerPages(wxBoxSizer * sizerFrame);

	void OnNSDRefresh(wxCommandEvent& WXUNUSED(event));

	void OnExplorerRefresh(wxCommandEvent& WXUNUSED(event));



private:

		wxNotebookSizer *sizerNotebook_;


	//name-service browser page
	wxPanel *ns_browser_panel;
	wxPanel *deployment_panel_;
	NSBrowserTreeCtrl *ns_browser_;
	wxPanel * launcher_panel_;
	wxPanel * qcexplorer_panel;
	QCexplorerTreeCtrl *qcexplorer_;
	wxPanel * explorer_panel;

	    DECLARE_EVENT_TABLE()

};

#endif
