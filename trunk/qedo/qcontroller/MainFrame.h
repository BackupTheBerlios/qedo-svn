#include "qcontroller.h"
#include "wx/frame.h"
#include "wx/sizer.h"
#include "ControllerNotebook.h"




class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);

    virtual ~MainFrame();

private:
	wxPanel *panel_;
    wxBoxSizer *sizerFrame_;


	ControllerNotebook *notebook_;


};
