#ifndef __QCONTROLLER_H__
#define __QCONTROLLER_H__

#include "wx/app.h"

// Define a new application
class QedoController : public wxApp
{
public:
    bool OnInit();
    void OnAssert(const wxChar *file,
                          int line,
                          const wxChar *cond,
                          const wxChar *msg);


};

DECLARE_APP(QedoController)


enum ID_CONTROLS
{
    ID_NOTEBOOK = wxID_HIGHEST,
	NSBrowserTree_Ctrl
};

#endif

