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
#include "ViewCADDialog.h"
////@end includes

////@begin XPM images

////@end XPM images

/*!
 * MyDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ViewCADDialog, wxDialog )

/*!
 * MyDialog event table definition
 */

BEGIN_EVENT_TABLE( ViewCADDialog, wxDialog )

////@begin MyDialog event table entries
	EVT_BUTTON( ID_BUTTON, ViewCADDialog::onclose)
////@end MyDialog event table entries

END_EVENT_TABLE()

/*!
 * MyDialog constructors
 */

ViewCADDialog::ViewCADDialog( )
{
}

ViewCADDialog::ViewCADDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * MyDialog creator
 */

bool ViewCADDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MyDialog member initialisation
////@end MyDialog member initialisation

////@begin MyDialog creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end MyDialog creation
    return TRUE;
}

/*!
 * Control creation for MyDialog
 */

void ViewCADDialog::CreateControls()
{    
////@begin MyDialog content construction

    ViewCADDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    textctrl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(600, 400), wxTE_MULTILINE );
    itemBoxSizer2->Add(textctrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton4 = new wxButton( itemDialog1, ID_BUTTON, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemButton4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end MyDialog content construction
}

/*!
 * Should we show tooltips?
 */

bool ViewCADDialog::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap ViewCADDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MyDialog bitmap retrieval
    return wxNullBitmap;
////@end MyDialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon ViewCADDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MyDialog icon retrieval
    return wxNullIcon;
////@end MyDialog icon retrieval
}

void ViewCADDialog::onclose(wxCommandEvent& event)
{
	EndModal(wxID_OK);
	event.Skip();
}