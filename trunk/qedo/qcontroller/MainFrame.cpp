#include "MainFrame.h"
#include "ControllerNotebook.h"
#include "qcontroller.h"
#include "wx/artprov.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                 long style)
    : wxFrame((wxWindow *) NULL, -1, title, pos, size, style)
{

	  panel_ = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize,
        wxTAB_TRAVERSAL | wxCLIP_CHILDREN | wxNO_BORDER);

	 notebook_ = new ControllerNotebook(panel_, ID_NOTEBOOK);

	 // create image list
	wxSize imagesize (32,32);
	wxImageList* notebook_image_list = new wxImageList(imagesize.GetWidth(), imagesize.GetHeight(), TRUE);

	notebook_image_list -> Add ( wxArtProvider::GetIcon(wxART_INFORMATION, wxART_OTHER, imagesize));

	notebook_ -> SetImageList(notebook_image_list);


	 sizerFrame_ = new wxBoxSizer(wxBOTH);
	 panel_->SetSizer(sizerFrame_);

	 notebook_ -> CreateControllerPages(sizerFrame_);


//	 sizerNotebook_ = new wxNotebookSizer(notebook_);
//	 sizerFrame_->Add(sizerNotebook_, 1, wxEXPAND | wxALL, 4);

	 panel_->SetAutoLayout(TRUE);

//	 sizerFrame_->Fit(this);

//	 Centre(wxBOTH);


}

MainFrame::~MainFrame() {

};

