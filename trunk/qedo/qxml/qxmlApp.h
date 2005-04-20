/////////////////////////////////////////////////////////////////////////////
// Name:        qxmlApp.h
// Purpose:     
// Author:      HEINI
// Modified by: 
// Created:     04/07/05 20:32:02
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _QXMLAPP_H_
#define _QXMLAPP_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "qxmlApp.cpp"
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
 * QxmlApp class declaration
 */

class QxmlApp: public wxApp
{    
    DECLARE_CLASS( QxmlApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    QxmlApp();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin QxmlApp event handler declarations

////@end QxmlApp event handler declarations

////@begin QxmlApp member function declarations

////@end QxmlApp member function declarations

////@begin QxmlApp member variables
////@end QxmlApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(QxmlApp)
////@end declare app

#endif
    // _QXMLAPP_H_