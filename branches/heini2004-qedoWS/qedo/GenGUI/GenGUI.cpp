
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation ""
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"

#endif


////@begin includes
#include "GenGUI.h"
#include <iostream>
#include "CIDLRepository_impl.h"
#include "Debug.h"
#include "frontend.h"
////@end includes

// global reference
CIDL::CIDLRepository_ptr repository;

////@begin XPM images

////@end XPM images
using namespace std;
/*!
 * GenGUI type definition
 */

IMPLEMENT_DYNAMIC_CLASS( GenGUI, wxFrame )

/*!
 * GenGUI event table definition
 */

BEGIN_EVENT_TABLE( GenGUI, wxFrame )

////@begin GenGUI event table entries
 EVT_MENU( ID_LOADMENUITEM, GenGUI::OnLoadmenuitemClick )
////@end GenGUI event table entries

END_EVENT_TABLE()

/*!
 * GenGUI constructors
 */

GenGUI::GenGUI( )
{
}

GenGUI::GenGUI( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create( parent, id, caption, pos, size, style );
}

/*!
 * GenGUI creator
 */

bool GenGUI::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin GenGUI member initialisation
////@end GenGUI member initialisation

////@begin GenGUI creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
////@end GenGUI creation
    return true;
}

/*!
 * Control creation for GenGUI
 */

void GenGUI::CreateControls()
{    
////@begin GenGUI content construction
    // Generated by DialogBlocks, 01/02/06 10:09:13 (unregistered)

    GenGUI* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* itemMenu3 = new wxMenu;
    itemMenu3->Append(ID_LOADMENUITEM, _("Load CIDL"), _T(""), wxITEM_NORMAL);
    itemMenu3->AppendSeparator();
    itemMenu3->Append(ID_EXITMENUITEM, _("Exit"), _T(""), wxITEM_NORMAL);
    menuBar->Append(itemMenu3, _("File"));
    wxMenu* itemMenu7 = new wxMenu;
    menuBar->Append(itemMenu7, _("About"));
    itemFrame1->SetMenuBar(menuBar);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
    itemFrame1->SetSizer(itemBoxSizer8);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemFrame1->SetSizer(itemBoxSizer9);

    wxStaticBox* itemStaticBoxSizer10Static = new wxStaticBox(itemFrame1, wxID_ANY, _("Components"));
    wxStaticBoxSizer* itemStaticBoxSizer10 = new wxStaticBoxSizer(itemStaticBoxSizer10Static, wxHORIZONTAL);
    itemBoxSizer9->Add(itemStaticBoxSizer10, 0, wxGROW|wxALL, 5);

    wxTreeCtrl* itemTreeCtrl11 = new wxTreeCtrl( itemFrame1, ID_COMPONENTTREECTRL, wxDefaultPosition, wxSize(300, 100), wxTR_SINGLE );
    itemStaticBoxSizer10->Add(itemTreeCtrl11, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer9->Add(itemBoxSizer12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemFrame1, ID_addBUTTON, _("add to targets >>"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton13, 0, wxGROW|wxALL, 5);

    wxButton* itemButton14 = new wxButton( itemFrame1, ID_addallBUTTON, _("add all to targets >>"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton14, 0, wxGROW|wxALL, 5);

    wxButton* itemButton15 = new wxButton( itemFrame1, ID_removeBUTTON, _("<< remove from targets"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton15->SetDefault();
    itemBoxSizer12->Add(itemButton15, 0, wxGROW|wxALL, 5);

    wxButton* itemButton16 = new wxButton( itemFrame1, ID_removeallBUTTON, _("<< remove all from targets"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemButton16, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer17Static = new wxStaticBox(itemFrame1, wxID_ANY, _("Generation Settings"));
    wxStaticBoxSizer* itemStaticBoxSizer17 = new wxStaticBoxSizer(itemStaticBoxSizer17Static, wxHORIZONTAL);
    itemBoxSizer9->Add(itemStaticBoxSizer17, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxVERTICAL);
    itemStaticBoxSizer17->Add(itemBoxSizer18, 0, wxGROW|wxALL, 5);

    wxString itemRadioBox19Strings[] = {
        _("&VC7 projects"),
        _("&Makefiles")
    };
    wxRadioBox* itemRadioBox19 = new wxRadioBox( itemFrame1, ID_GENERATERRADIOBOX, _("Generate"), wxDefaultPosition, wxDefaultSize, 2, itemRadioBox19Strings, 1, wxRA_SPECIFY_ROWS );
    itemBoxSizer18->Add(itemRadioBox19, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer20Static = new wxStaticBox(itemFrame1, wxID_ANY, _("Options"));
    wxStaticBoxSizer* itemStaticBoxSizer20 = new wxStaticBoxSizer(itemStaticBoxSizer20Static, wxVERTICAL);
    itemBoxSizer18->Add(itemStaticBoxSizer20, 0, wxGROW|wxALL, 5);

    wxCheckBox* itemCheckBox21 = new wxCheckBox( itemFrame1, ID_CHECKBOX_XML, _("generate XML Descriptor skeletons"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    itemCheckBox21->SetValue(false);
    itemStaticBoxSizer20->Add(itemCheckBox21, 0, wxGROW|wxALL, 5);

    wxCheckBox* itemCheckBox22 = new wxCheckBox( itemFrame1, ID_CHECKBOX_BUSINESS, _("generate business code skeletons"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    itemCheckBox22->SetValue(false);
    itemStaticBoxSizer20->Add(itemCheckBox22, 0, wxGROW|wxALL, 5);

    wxCheckBox* itemCheckBox23 = new wxCheckBox( itemFrame1, ID_CHECKBOX_SERVANT, _("generate servant code"), wxDefaultPosition, wxDefaultSize, wxCHK_2STATE );
    itemCheckBox23->SetValue(false);
    itemStaticBoxSizer20->Add(itemCheckBox23, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer24Static = new wxStaticBox(itemFrame1, wxID_ANY, _("Targets"));
    wxStaticBoxSizer* itemStaticBoxSizer24 = new wxStaticBoxSizer(itemStaticBoxSizer24Static, wxVERTICAL);
    itemBoxSizer18->Add(itemStaticBoxSizer24, 0, wxGROW|wxALL, 5);

    wxTreeCtrl* itemTreeCtrl25 = new wxTreeCtrl( itemFrame1, ID_TARGETSTREECTRL, wxDefaultPosition, wxSize(200, 280), wxTR_SINGLE );
    itemStaticBoxSizer24->Add(itemTreeCtrl25, 0, wxGROW|wxALL, 5);

    wxButton* itemButton26 = new wxButton( itemFrame1, ID_GenerateBUTTON, _("Generate"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemButton26, 0, wxGROW|wxALL, 5);

	
////@end GenGUI content construction
}

/*!
 * Should we show tooltips?
 */

bool GenGUI::ShowToolTips()
{
    return true;
}

void GenGUI::OnLoadmenuitemClick(wxCommandEvent& event )
{
	wxFileDialog* file_dialog=new wxFileDialog(this,"Load CIDL file...","","","*.cidl",wxOPEN,wxDefaultPosition);
	int t=file_dialog->ShowModal();
	
	wxString file;
	wxString path;
	wxString filename;
	if (t==wxID_OK) {
		
		file=file_dialog->GetPath();
		path=file_dialog->GetDirectory();
		filename=file_dialog->GetFilename();
		
		CORBA::ORB_var orb;
		int argc=8;
		char* argv[8] ;
		argv[0] = "";
		argv[1] = strdup("-DMICO_ORB");
		argv[2] = strdup("-DMICO_CIDL_GEN");
		argv[3] = strdup("-IC:\\opt\\qedo_debug\\idl");
		argv[4] = strdup("-IC:\\opt\\qedo_debug\\include\\mico");
		argv[5] = strdup("-IC:\\opt\\qedo_debug\\include\\mico\\mico");
		argv[6] = strdup("-IC:\\devel\\berl_test\\trunk\\examples\\general\\compute");
		argv[7] = strdup(file.wx_str()); 
		
		try
		{
			
			orb = CORBA::ORB_init ( argc, argv );
			
		}
		catch ( ... )
		{
			std::cerr << "Error during ORB_init()" << std::endl;
			
		}
		PortableServer::POA_var root_poa;
		try
		{
			CORBA::Object_var root_poa_obj = orb->resolve_initial_references ( "RootPOA" );
			root_poa = PortableServer::POA::_narrow ( root_poa_obj );
		}
		catch ( ... )
		{
			std::cerr << "Error during getting root POA" << std::endl;
			orb -> destroy();
			
		}
		PortableServer::POAManager_var root_poa_manager;
		try
		{
			root_poa_manager = root_poa -> the_POAManager();
		}
		catch ( ... )
		{
			std::cerr << "Error getting root POA manager" << std::endl;
			orb->destroy();
			
		}

		root_poa_manager -> activate();


		repository = CIDL::CIDLRepository::_narrow( (new QEDO_ComponentRepository::CIDLRepository_impl ( orb, root_poa )) -> _this());
		try {
		// feed repository
			if (frontend_feed( argc, argv, repository ))
			{
				wxMessageDialog* dialog_error = new wxMessageDialog(this, "Can not parse input file","Message Box",wxOK, wxDefaultPosition);
				dialog_error->ShowModal();

			}
		} catch (...) 
		{
			std::cout << "Problem in parser occured ... exiting." << std::endl;
			orb->destroy();
			wxMessageDialog* dialog = new wxMessageDialog(this,file,"Message Box",wxOK | wxCANCEL, wxDefaultPosition);
			dialog->ShowModal();
		}
		
		
		
	}

	delete file_dialog;

}

/*!
 * Get bitmap resources
 */

wxBitmap GenGUI::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin GenGUI bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end GenGUI bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon GenGUI::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin GenGUI icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end GenGUI icon retrieval
}