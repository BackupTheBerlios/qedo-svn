#ifndef __QCONTROLLER_H__
#define __QCONTROLLER_H__

#include "wx/app.h"
#include "coss/CosNaming.h"


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
	QCexplorerTree_Ctrl,
	Launcher_ID,
	DEPLOYMENT_ID,
	QEDOEXPLORER_ID,
	START_EXPLORER_BUTTON,
	ID_START_EXPLORER_BUTTON,
	ID_START_CLIENT_BUTTON,
	ID_HOSTNAME,
	ID_PORT,
	ID_HOSTNAME_CLIENT,
	ID_PORT_CLIENT,
	ID_REFRESH_EXPLORER_TREE,
	NSD,
	ID_PORTNUMBER,
	HF,
	NSD_TREE_REFRESH,
	EXPLORER_TREE_REFRESH,
	ASSF,
	SA,
	CI,
	ID_ASSNAME_TEXTCTRL,
	ID_FILE_CHOICE_BUTTON,
	ID_DEPLOY_BUTTON,
	ID_RUNNING_LISTCTRL,
	ID_UNDEPLOY_BUTTON,
	ID_ITEM_DOUBLECLICK,
	ID_ITEM_RIGHTCLICK,
	ID_HOSTNAME_NSD
	
};

#endif

