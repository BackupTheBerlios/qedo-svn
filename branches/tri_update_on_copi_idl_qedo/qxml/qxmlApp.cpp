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

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "qxmlApp.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "qxml.h"
#include "version.h"

#include "qxmlApp.h"


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( QxmlApp )
////@end implement app

/*!
 * QxmlApp type definition
 */

IMPLEMENT_CLASS( QxmlApp, wxApp )

/*!
 * QxmlApp event table definition
 */

BEGIN_EVENT_TABLE( QxmlApp, wxApp )

////@begin QxmlApp event table entries
////@end QxmlApp event table entries

END_EVENT_TABLE()

/*!
 * Constructor for QxmlApp
 */

QxmlApp::QxmlApp()
{
////@begin QxmlApp member initialisation
////@end QxmlApp member initialisation
}

/*!
 * Initialisation for QxmlApp
 */

bool QxmlApp::OnInit()
{    
////@begin QxmlApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

    // Create the main window
    wxString window_title = "Qedo qxml ";
    window_title.append(QEDO_VERSION);

	MyDialog *dialog = new MyDialog(NULL,-1,window_title,wxPoint(50,50), wxSize(450,350),wxDEFAULT_DIALOG_STYLE);
    

#if wxUSE_XPM
    wxImage::AddHandler( new wxXPMHandler );
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler( new wxPNGHandler );
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler( new wxJPEGHandler );
#endif
#if wxUSE_GIF
    wxImage::AddHandler( new wxGIFHandler );
#endif
////@end QxmlApp initialisation
	if (dialog->ShowModal() == wxID_OK)
     {
        
      }
      dialog->Destroy();
    return true;
}

/*!
 * Cleanup for QxmlApp
 */
int QxmlApp::OnExit()
{    
////@begin QxmlApp cleanup
	
    return wxApp::OnExit();
////@end QxmlApp cleanup
}

