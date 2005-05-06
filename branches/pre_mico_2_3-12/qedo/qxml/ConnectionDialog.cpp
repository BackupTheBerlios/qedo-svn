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
#include "ConnectionDialog.h"
////@end includes

////@begin XPM images

////@end XPM images

/*!
 * MyDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ConnectionDialog, wxDialog )

/*!
 * MyDialog event table definition
 */

BEGIN_EVENT_TABLE( ConnectionDialog, wxDialog )

////@begin MyDialog event table entries
	EVT_BUTTON( ID_BUTTON1, ConnectionDialog::OnButtonCancel )
	EVT_BUTTON( ID_BUTTON, ConnectionDialog::OnButtonOk)
////@end MyDialog event table entries

END_EVENT_TABLE()

/*!
 * MyDialog constructors
 */

ConnectionDialog::ConnectionDialog( )
{
}

ConnectionDialog::ConnectionDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, 
								   const wxSize& size, long style, const wxString& portstatic1, const wxString& portstatic2 )
{
    Create(parent, id, caption, pos, size, style,portstatic1,portstatic2);
}

/*!
 * MyDialog creator
 */

bool ConnectionDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, 
							  const wxSize& size, long style, const wxString& portstatic1, const wxString& portstatic2 )
{
////@begin MyDialog member initialisation
////@end MyDialog member initialisation

////@begin MyDialog creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

	pstatic1=portstatic1;
	pstatic2=portstatic2;
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

void ConnectionDialog::CreateControls()
{    
////@begin MyDialog content construction

    ConnectionDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_LEFT|wxALL, 5);

    headline = new wxStaticText( itemDialog1, wxID_STATIC, _("Choose the ports for connecting"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(headline, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer5, 0, 0, 0);

    portstaticbox1 = new wxStaticBox(itemDialog1, wxID_ANY, _(pstatic1));
	
    wxStaticBoxSizer* itemStaticBoxSizer6 = new wxStaticBoxSizer(portstaticbox1, wxHORIZONTAL);
    itemBoxSizer5->Add(itemStaticBoxSizer6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    portlist1 = new wxTreeCtrl(itemDialog1, ID_LISTCTRL2, wxDefaultPosition, wxSize(200, 200),wxTR_SINGLE );
    itemStaticBoxSizer6->Add(portlist1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	portlist1->AddRoot(wxT("Portlist"),-1 , -1 , NULL);

    portstaticbox2 = new wxStaticBox(itemDialog1, wxID_ANY, _(pstatic2));
    wxStaticBoxSizer* itemStaticBoxSizer8 = new wxStaticBoxSizer(portstaticbox2, wxHORIZONTAL);
    itemBoxSizer5->Add(itemStaticBoxSizer8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    portlist2 = new wxTreeCtrl( itemDialog1, ID_LISTCTRL3, wxDefaultPosition, wxSize(200, 200), wxTR_SINGLE );
    itemStaticBoxSizer8->Add(portlist2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	portlist2->AddRoot(wxT("Portlist"),-1 , -1 , NULL);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer10, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemDialog1, ID_BUTTON, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(itemButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer10->Add(10, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemDialog1, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(itemButton13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end MyDialog content construction
}

/*!
 * Should we show tooltips?
 */

bool ConnectionDialog::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap ConnectionDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MyDialog bitmap retrieval
    return wxNullBitmap;
////@end MyDialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon ConnectionDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MyDialog icon retrieval
    return wxNullIcon;
////@end MyDialog icon retrieval
}

void ConnectionDialog::OnButtonCancel( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in MyDialog.
    // Before editing this code, remove the block markers.
	this->EndModal(wxID_CANCEL);
	event.Skip();
	
    
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in MyDialog. 
}

void ConnectionDialog::OnButtonOk( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in MyDialog.
    // Before editing this code, remove the block markers.

	if (portlist1->GetSelection()!=portlist1->GetRootItem())
	{
		if (portlist2->GetSelection()!=portlist2->GetRootItem())
		{
			wxTreeItemId p1 = portlist1->GetSelection();
			wxTreeItemId p2 = portlist2->GetSelection();
			if (portlist1->GetParent(p1)==portlist1->GetRootItem())
			{
				if (portlist2->GetParent(p2)==portlist2->GetRootItem())
				{
					port1=portlist1->GetItemText(p1);
					port2=portlist2->GetItemText(p2);
					this->EndModal(wxID_OK);
					event.Skip();
				}
			}
		}
	}
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in MyDialog. 
}

void ConnectionDialog::setPorts1(wxArrayString portlist)
{
	for (int i=0; i<portlist.GetCount();i++)
	{
		portlist1->AppendItem(portlist1->GetRootItem(),portlist.Item(i),-1,-1,NULL);
		
		
	}
	portlist1->Expand(portlist1->GetRootItem());
	portlist1->Refresh();

}

void ConnectionDialog::setPorts2( wxArrayString portlist)
{
	for (int i=0; i<portlist.GetCount();i++)
	{
		portlist2->AppendItem(portlist2->GetRootItem(),portlist.Item(i),-1,-1,NULL);
	}

	portlist2->Expand(portlist2->GetRootItem());
	portlist2->Refresh();
}