/*!
 * Includes
 */

////@begin includes
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
#define SYMBOL_VIEWCADDIALOG_SIZE wxSize(600, 400)
#define SYMBOL_MYDIALOG_POSITION wxDefaultPosition
#define ID_TEXTCTRL 10001
#define ID_BUTTON 10002
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

class ViewCADDialog: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( ViewCADDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    ViewCADDialog( );
    ViewCADDialog( wxWindow* parent, wxWindowID id = SYMBOL_MYDIALOG_IDNAME, const wxString& caption = SYMBOL_MYDIALOG_TITLE, const wxPoint& pos = SYMBOL_MYDIALOG_POSITION, const wxSize& size = SYMBOL_VIEWCADDIALOG_SIZE, long style = SYMBOL_MYDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MYDIALOG_IDNAME, const wxString& caption = SYMBOL_MYDIALOG_TITLE, const wxPoint& pos = SYMBOL_MYDIALOG_POSITION, const wxSize& size = SYMBOL_VIEWCADDIALOG_SIZE, long style = SYMBOL_MYDIALOG_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin MyDialog event handler declarations
	void onclose(wxCommandEvent& event);
////@end MyDialog event handler declarations

////@begin MyDialog member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MyDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MyDialog member variables
	wxTextCtrl* textctrl;
////@end MyDialog member variables
};
