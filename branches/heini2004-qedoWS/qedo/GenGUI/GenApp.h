#ifndef _GENAPP_H_
#define _GENAPP_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "genapp.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
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
////@end control identifiers

/*!
 * QGenApp class declaration
 */

class GenApp: public wxApp
{    
    DECLARE_CLASS( GenApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    GenApp();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin GenApp event handler declarations

////@end GenApp event handler declarations

////@begin GenApp member function declarations

////@end GenApp member function declarations

////@begin QGenApp member variables
////@end QGenApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(GenApp)
////@end declare app

#endif
    // _GEN_H_
