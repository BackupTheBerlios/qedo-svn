#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface ""
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/treectrl.h"
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
#define SYMBOL_MYDIALOG_TITLE _("Connection Dialog")
#define SYMBOL_MYDIALOG_PSTATIC1 _("Sourceports")
#define SYMBOL_MYDIALOG_PSTATIC2 _("Sinkports")
#define SYMBOL_MYDIALOG_IDNAME ID_DIALOG
#define SYMBOL_MYDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_MYDIALOG_POSITION wxDefaultPosition
#define ID_LISTCTRL2 10004
#define ID_LISTCTRL3 10005
#define ID_BUTTON 10001
#define ID_BUTTON1 10002
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

class ConnectionDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( ConnectionDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    ConnectionDialog( );
    ConnectionDialog( wxWindow* parent, wxWindowID id = SYMBOL_MYDIALOG_IDNAME, const wxString& caption = SYMBOL_MYDIALOG_TITLE, const wxPoint& pos = SYMBOL_MYDIALOG_POSITION, const wxSize& size = SYMBOL_MYDIALOG_SIZE,
		long style = SYMBOL_MYDIALOG_STYLE, const wxString& portstatic1=SYMBOL_MYDIALOG_PSTATIC1, const wxString& portstatic2=SYMBOL_MYDIALOG_PSTATIC2);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MYDIALOG_IDNAME, const wxString& caption = SYMBOL_MYDIALOG_TITLE, const wxPoint& pos = SYMBOL_MYDIALOG_POSITION, const wxSize& size = SYMBOL_MYDIALOG_SIZE,
		long style = SYMBOL_MYDIALOG_STYLE, const wxString& portstatic1=SYMBOL_MYDIALOG_PSTATIC1, const wxString& portstatic2=SYMBOL_MYDIALOG_PSTATIC2 );

    /// Creates the controls and sizers
    void CreateControls();

////@begin MyDialog event handler declarations
	void OnButtonCancel( wxCommandEvent& event );
	void OnButtonOk( wxCommandEvent& event);
////@end MyDialog event handler declarations

////@begin MyDialog member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

	void setPorts1(wxArrayString portlist);
	void setPorts2(wxArrayString portlist);
    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MyDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MyDialog member variables
	wxStaticText* headline;
	wxTreeCtrl* portlist1;
	wxTreeCtrl* portlist2;
	wxString port1;
	wxString port2;
	wxStaticBox* portstaticbox1;
	wxStaticBox* portstaticbox2;

	wxString pstatic1;
	wxString pstatic2;

////@end MyDialog member variables
};

