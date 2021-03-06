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
	NSBrowserTree_Ctrl,
	Launcher_ID,
	DEPLOYMENT_ID,
	NSD,
	ID_PORTNUMBER,
	HF,
	NSD_TREE_REFRESH,
	ASSF,
	SA,
	CI,
	ID_ASSNAME_TEXTCTRL,
	ID_FILE_CHOICE_BUTTON,
	ID_DEPLOY_BUTTON,
	ID_RUNNING_LISTCTRL,
	ID_UNDEPLOY_BUTTON
};

#endif

