#include "ControllerNotebook.h"
#include "NSBrowser.h"
#include "Launcher.h"


ControllerNotebook::ControllerNotebook(wxWindow *parent, wxWindowID id,
    const wxPoint& pos, const wxSize& size, long style)
    : wxNotebook(parent, id, pos, size, style)
{
    // Empty
}


void ControllerNotebook::CreateControllerPages(wxBoxSizer * sizerFrame)
{
	 sizerNotebook_ = new wxNotebookSizer(this);
	 sizerFrame->Add(sizerNotebook_, 1, wxEXPAND | wxALL, 4);

	 // create launcher
	 wxPanel* launcher_panel = new wxPanel(this);


	 AddPage(launcher_panel, wxT("Launcher"), FALSE,0);



	// create ns_browser page
	ns_browser_panel = new wxPanel(this);
	ns_browser_ = new NSBrowserTreeCtrl (ns_browser_panel, NSBrowserTree_Ctrl, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	wxBoxSizer * ns_browser_panel_sizer = new wxBoxSizer(wxVERTICAL);
	ns_browser_panel -> SetSizer( ns_browser_panel_sizer );
	ns_browser_panel_sizer -> Add(ns_browser_, 1, wxEXPAND | wxALL, 4);

	AddPage( ns_browser_panel, wxT("NS Browser"), FALSE, 0 );



    SetSelection(0);

}
