/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
/*                                                                         */
/* Copyright (C) 2002-2005 by the Qedo Team                                */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

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
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

	pstatic1=portstatic1;
	pstatic2=portstatic2;
    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();

	return TRUE;
}

/*!
 * Control creation for MyDialog
 */

void ConnectionDialog::CreateControls()
{    

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
    return wxNullBitmap;
}

/*!
 * Get icon resources
 */

wxIcon ConnectionDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
    return wxNullIcon;
}

void ConnectionDialog::OnButtonCancel( wxCommandEvent& event )
{
	this->EndModal(wxID_CANCEL);
	event.Skip();
	
    
}

void ConnectionDialog::OnButtonOk( wxCommandEvent& event )
{

	if (portlist1->GetSelection()!=portlist1->GetRootItem())
	{
		if (portlist2->GetSelection()!=portlist2->GetRootItem())
		{
			wxTreeItemId p1 = portlist1->GetSelection();
			wxTreeItemId p2 = portlist2->GetSelection();
			if (portlist1->GetItemParent(p1)==portlist1->GetRootItem())
			{
				if (portlist2->GetItemParent(p2)==portlist2->GetRootItem())
				{
					port1=portlist1->GetItemText(p1);
					port2=portlist2->GetItemText(p2);
					this->EndModal(wxID_OK);
					event.Skip();
				}
			}
		}
	}
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
