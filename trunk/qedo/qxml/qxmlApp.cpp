/////////////////////////////////////////////////////////////////////////////
// Name:        qxmlApp.cpp
// Purpose:     
// Author:      HEINI
// Modified by: 
// Created:     04/07/05 20:32:02
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

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

////@begin includes
#include "qxml.h"
////@end includes

#include "qxmlApp.h"
//#include "qedoutil.h"

////@begin XPM images
////@end XPM images

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

	MyDialog *dialog = new MyDialog(NULL,-1,"QXML",wxPoint(50,50), wxSize(450,350),wxDEFAULT_DIALOG_STYLE);
    

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

