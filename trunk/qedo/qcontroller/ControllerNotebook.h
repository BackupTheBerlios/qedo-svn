#include "wx/notebook.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "NSBrowser.h"

#ifndef __CONTROLLERNOTEBOOK_H__
#define __CONTROLLERNOTEBOOK_H__

class ControllerNotebook : public wxNotebook
{
public:
    ControllerNotebook(wxWindow *parent, wxWindowID id = -1,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0);

    void CreateControllerPages(wxBoxSizer * sizerFrame);
private:

		wxNotebookSizer *sizerNotebook_;


	//name-service browser page
	wxPanel *ns_browser_panel;
	NSBrowserTreeCtrl *ns_browser_;

};

#endif
