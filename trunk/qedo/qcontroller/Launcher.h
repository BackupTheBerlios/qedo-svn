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

#ifndef __LAUNCHER_H__
#define __LAUNCHER_H__

#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"

class Launcher : public wxPanel
{
public:
	Launcher(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnNSDStartButton(wxCommandEvent& WXUNUSED(event));
	void OnHFStartButton(wxCommandEvent& WXUNUSED(event));
	void OnASSFStartButton(wxCommandEvent& WXUNUSED(event));
	void OnSAStartButton(wxCommandEvent& WXUNUSED(event));
	void OnCIStartButton(wxCommandEvent& WXUNUSED(event));
	void OnEdit_conf_Button(wxCommandEvent& WXUNUSED(event));
	void OnDomain_start(wxCommandEvent& WXUNUSED(event));
	void OnNode_start(wxCommandEvent& WXUNUSED(event));
	void OnExplorer_start(wxCommandEvent& WXUNUSED(event));
	//wxTextCtrl* port_number_;

private:
	long nsd_pid_; 
	bool nsd_started_;
	long hf_pid_; 
	bool hf_started_;
	long assf_pid_; 
	bool assf_started_;
	long sa_pid_; 
	bool sa_started_;
	long ci_pid_; 
	bool ci_started_;
	long sexp_pid_;
	bool sexp_started_ ;

	wxButton *NodeStartBtn;
	wxButton *DomainStartBtn;
	wxButton *EditConfBtn;
	wxButton *NSDStartBtn; 
	wxButton *HFStartBtn;
	wxButton *ASSFStartBtn;
	wxButton *SAStartBtn;
	wxButton *CIStartBtn;
	wxButton *QedoExplorerBtn;
	wxTextCtrl* host_name_nsd_;
	wxTextCtrl* port_number_;
	
	// domain
	void startNSD();
	void startHF();
	void startASSF();
	void startEXP();

	// node
	void startSA();
	void startCI();
	
	
	
    DECLARE_EVENT_TABLE()
};

#endif
