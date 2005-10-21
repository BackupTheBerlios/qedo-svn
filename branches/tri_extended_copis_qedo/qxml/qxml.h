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


/*!
 * Includes
 */

////@begin includes
#include "wx/treectrl.h"
#include "wx/statline.h"
#include "ComponentTreeCtrl.h"
//#include "AComponentTreeCtrl.h"
#include "PartitioningTreeCtrl.h"
#include "ConnectionTreeCtrl.h"

////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define SYMBOL_MYDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_MYDIALOG_TITLE _("Dialog")
#define SYMBOL_MYDIALOG_IDNAME ID_DIALOG
#define SYMBOL_MYDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_MYDIALOG_POSITION wxDefaultPosition
#define ID_TREECTRL 10001
#define Badd_ComponentP 10004
#define ID_BUTTON2 10006
#define ID_BUTTON3 10007
#define B_EXIT 10005
#define ID_TREECTRL1 10002
#define ID_TREECTRL3 10008
#define Badd_Part 10010
#define ID_TREECTRL2 10003
#define Badd_con 10009
#define ID_MENU_DELETE 10010
#define ID_MENU_IOR 10011
#define CP_TREE_RD 10012
#define ID_BUTTON_VC 10013
#define ID_ASS_TEXT 10014
#define ID_TEXTCTRL1 10015
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * MyDialog class declaration
 */


class MyDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( MyDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
	enum
    {	
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
		TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened
    };
    MyDialog( );
    MyDialog( wxWindow* parent, wxWindowID id = SYMBOL_MYDIALOG_IDNAME, const wxString& caption = SYMBOL_MYDIALOG_TITLE, const wxPoint& pos = SYMBOL_MYDIALOG_POSITION, const wxSize& size = SYMBOL_MYDIALOG_SIZE, long style = SYMBOL_MYDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MYDIALOG_IDNAME, const wxString& caption = SYMBOL_MYDIALOG_TITLE, const wxPoint& pos = SYMBOL_MYDIALOG_POSITION, const wxSize& size = SYMBOL_MYDIALOG_SIZE, long style = SYMBOL_MYDIALOG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

	
	
////@begin MyDialog event handler declarations
    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnButtonClick( wxCommandEvent& event );
	void OnAdd_Comp( wxCommandEvent& event );
	void OnItem(wxTreeEvent& event);
	void OnButtton_VC( wxCommandEvent& event );
	void OnButton_GA(wxCommandEvent& event );

////@end MyDialog event handler declarations

////@begin MyDialog member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );
	wxString getOutputText();


    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MyDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MyDialog member variables
	 ComponentTreeCtrl* cp_TreeCtrl;
	 wxTreeItemId cp_rootID;
	 AComponentTreeCtrl* a_TreeCtrl;
	 PartitioningTreeCtrl* p_TreeCtrl;
	 ConnectionTreeCtrl* c_TreeCtrl;
	 wxTextCtrl* assemblyid;

////@end MyDialog member variables
};
