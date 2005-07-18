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