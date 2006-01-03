#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "genapp.h"
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
////@end includes

#include "GenApp.h"
#include "GenGUI.h"

////@begin XPM images

////@end XPM images

/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( GenApp )
////@end implement app

/*!
 * QGenApp type definition
 */

IMPLEMENT_CLASS( GenApp, wxApp )

/*!
 * QGenApp event table definition
 */

BEGIN_EVENT_TABLE( GenApp, wxApp )

////@begin QGenApp event table entries
////@end QGenApp event table entries

END_EVENT_TABLE()

/*!
 * Constructor for QGenApp
 */

GenApp::GenApp()
{
////@begin QGenApp member initialisation
////@end QGenApp member initialisation
}

/*!
 * Initialisation for QGenApp
 */

bool GenApp::OnInit()
{    
////@begin QGenApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
////@end QGenApp initialisation

    GenGUI *gengui = new GenGUI(NULL,-1,"Qedo Generator GUI",wxPoint(50,50), wxSize(780,600), wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN );
	gengui->Show(true);
	
	return true;
}

/*!
 * Cleanup for QGenApp
 */
int GenApp::OnExit()
{    
////@begin QGenApp cleanup
    return wxApp::OnExit();
////@end QGenApp cleanup
}

