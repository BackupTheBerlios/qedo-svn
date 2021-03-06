#include "ControllerNotebook.h"
#include "NSBrowser.h"
#include "wx/button.h"
#include "Launcher.h"
#include "Deployment.h"
#include "Qcexplorer.h"
#include "QedoExplorer.h"


BEGIN_EVENT_TABLE(ControllerNotebook, wxNotebook)
    EVT_BUTTON(NSD_TREE_REFRESH,  ControllerNotebook::OnNSDRefresh)
	EVT_BUTTON(EXPLORER_TREE_REFRESH, ControllerNotebook::OnExplorerRefresh)

END_EVENT_TABLE()

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
	 launcher_panel_ = new Launcher (this, Launcher_ID, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	 AddPage(launcher_panel_, wxT("Launcher"), FALSE,0);

	// create ns_browser page
	ns_browser_panel = new wxPanel(this);
	ns_browser_ = new NSBrowserTreeCtrl (ns_browser_panel, NSBrowserTree_Ctrl, wxDefaultPosition, wxSize(400,400), wxTR_DEFAULT_STYLE );
	AddPage( ns_browser_panel, wxT("NS Browser"), FALSE, 0 );

	// create Deployment page
	 deployment_panel_ = new Deployment(this, DEPLOYMENT_ID, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	 AddPage(deployment_panel_, wxT("Deployment"), FALSE,0);

    // create Explorer page
	 //qcexplorer_panel = new wxPanel(this);
	// qcexplorer_=new QCexplorerTreeCtrl (qcexplorer_panel, QCexplorerTree_Ctrl, wxDefaultPosition, wxSize(200,200), wxTR_DEFAULT_STYLE);
	// AddPage(qcexplorer_panel, wxT("Explorer"), FALSE,0);

	// create Explorer page
	 explorer_panel=new QedoExplorer(this, QEDOEXPLORER_ID, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);
	 AddPage(explorer_panel,wxT("Explorer"), FALSE,0);


    SetSelection(2);

}

void 
ControllerNotebook::OnNSDRefresh(wxCommandEvent& WXUNUSED(event))
{
//	int sel = event.GetSelection();
//	if (sel == 1)
//	{
		// rebiuld NS Browser Tree
	ns_browser_ -> OnNSDRefresh();
//	};

};

void
ControllerNotebook::OnExplorerRefresh(wxCommandEvent& WXUNUSED(event))
{

	qcexplorer_ -> OnExplorerRefresh();

}



