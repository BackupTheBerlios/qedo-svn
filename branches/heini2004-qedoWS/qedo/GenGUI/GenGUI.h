
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface ""
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
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
#define ID_GenGUI 10001
#define SYMBOL_GENGUI_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_GENGUI_TITLE _("QedoGenGUI")
#define SYMBOL_GENGUI_IDNAME ID_GenGUI
#define SYMBOL_GENGUI_SIZE wxSize(800, 600)
#define SYMBOL_GENGUI_POSITION wxDefaultPosition
#define ID_LOADMENUITEM 10002
#define ID_EXITMENUITEM 10002
#define ID_COMPONENTTREECTRL 10002
#define ID_addBUTTON 10002
#define ID_addallBUTTON 10002
#define ID_removeBUTTON 10002
#define ID_removeallBUTTON 10002
#define ID_GENERATERRADIOBOX 10002
#define ID_CHECKBOX_XML 10002
#define ID_CHECKBOX_BUSINESS 10002
#define ID_CHECKBOX_SERVANT 10002
#define ID_TARGETSTREECTRL 10002
#define ID_GenerateBUTTON 10002
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * GenGUI class declaration
 */

class GenGUI: public wxFrame
{    
    DECLARE_CLASS( GenGUI )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    GenGUI( );
    GenGUI( wxWindow* parent, wxWindowID id = SYMBOL_GENGUI_IDNAME, const wxString& caption = SYMBOL_GENGUI_TITLE, const wxPoint& pos = SYMBOL_GENGUI_POSITION, const wxSize& size = SYMBOL_GENGUI_SIZE, long style = SYMBOL_GENGUI_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GENGUI_IDNAME, const wxString& caption = SYMBOL_GENGUI_TITLE, const wxPoint& pos = SYMBOL_GENGUI_POSITION, const wxSize& size = SYMBOL_GENGUI_SIZE, long style = SYMBOL_GENGUI_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin GenGUI event handler declarations
////@end GenGUI event handler declarations

////@begin GenGUI member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end GenGUI member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();
	

////@begin GenGUI member variables
	void GenGUI::OnLoadmenuitemClick(wxCommandEvent& event );
////@end GenGUI member variables
};