/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
/*                                                                         */
/* Copyright (C) 2002-2004 by the Qedo Team                                */
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

#include "qcontroller.h"
#include "wx/frame.h"
#include "wx/sizer.h"
#include "wx/log.h"
#include "ControllerNotebook.h"
#include "HelpFrame.h"



class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);

    virtual ~MainFrame();

	void onHelp(wxCommandEvent& event);
	void onClose(wxCommandEvent& event);

private:
	wxPanel *panel_;
    wxBoxSizer *sizerFrame_;
	wxButton *help;
	wxButton *quit;
	HelpFrame *hf;

	ControllerNotebook *notebook_;

	DECLARE_EVENT_TABLE()
};
