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

#ifndef __QEDOEXPLORER_H__
#define __QEDOEXPLORER_H__

#include "qcontroller.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"
#include "wx/string.h"

#include "QCexplorer.h"

// #include "ComponentDeployment.h"

class QedoExplorer : public wxPanel
{
public:
	QedoExplorer(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnStartExplorerButton(wxCommandEvent& WXUNUSED(event));
	void OnStartClientButton(wxCommandEvent& WXUNUSED(event));
	void OnRefreshExplorerTreeBtn(wxCommandEvent& WXUNUSED(event));
	void Test();
	void text_to_ib(wxString t);
private:

	long sexp_pid_;
	
	bool sclp_started_ ;
	bool sexp_started_ ;

	
    
	wxButton* start_explorer_btn;
	wxButton* start_explorer_client_btn;
	wxButton* RefreshExplorerTreeBtn;
	wxTextCtrl* hostname_;
	wxTextCtrl* port_;
	wxTextCtrl* hostname_client_;
	wxTextCtrl* port_client_;
	QCexplorerTreeCtrl* qcexplorer_ ;
	//wxTextCtrl* info_box_;
	
	void start();
	
    DECLARE_EVENT_TABLE()

};
#endif
