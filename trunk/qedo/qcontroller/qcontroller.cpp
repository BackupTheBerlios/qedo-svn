// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/imaglist.h"
#include "wx/artprov.h"
#include "qcontroller.h"
#include "MainFrame.h"

IMPLEMENT_APP(QedoController)

bool QedoController::OnInit()
{
    wxSize main_size(800,600);
    wxPoint main_point(0,0);
    // Create the main window
    MainFrame *frame = new MainFrame( wxT("Qedo Controller") , main_point, main_size);

    // Problem with generic wxNotebook implementation whereby it doesn't size
    // properly unless you set the size again
#if defined(__WIN16__) || defined(__WXMOTIF__)
    int width, height;
    frame->GetSize(& width, & height);
    frame->SetSize(-1, -1, width, height);
#endif

    frame->Show();

    return TRUE;
}

void
QedoController::OnAssert(const wxChar *file,
                          int line,
                          const wxChar *cond,
                          const wxChar *msg)
 {

 }

