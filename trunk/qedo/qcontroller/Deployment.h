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

#ifndef __DEPLOYMENT_H__
#define __DEPLOYMENT_H__

#include "qcontroller.h"
#include "wx/panel.h"
#include "wx/button.h"
#include "wx/textctrl.h"
#include "wx/listctrl.h"
#include "wx/filedlg.h"
#include "wx/textctrl.h"

#include "descriptorframe.h"

#include "ComponentDeployment.h"

class Deployment : public wxPanel
{
public:
	Deployment(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style);

	void OnDeployButton(wxCommandEvent& WXUNUSED(event));
	void OnFileChoiseButton(wxCommandEvent& WXUNUSED(event));
	void OnUndeployButton(wxCommandEvent& WXUNUSED(event));
	void OnDecriptButton (wxCommandEvent& WXUNUSED(event));
	void OnInstanceButton (wxCommandEvent& WXUNUSED(event));

private:
	
	struct instanceinfo
	{
		wxTreeItemId itemid;
		Qedo::ComponentDeployment* reference;
	};

	struct r_assemblies
	{
		wxTreeItemId itemid;
		std::string package;
		std::vector < instanceinfo > instanceinfo_list;
	};


	typedef std::vector < r_assemblies > running_assemblies_;
	running_assemblies_ running_assemblies;
	
	//long assemblies_counter_;
	
	CORBA::ORB_var orb;
	wxTextCtrl* assembly_name_;
	wxButton* file_choice_btn;
	wxButton* deploy_btn;
//	wxButton* instance_btn;
	wxButton* descript_btn;
	wxListCtrl* running_ass_list;
	wxButton* undeploy_btn;
	wxFileDialog* file_dialog;
	DescriptorFrame* descriptor_frame;

	wxTreeCtrl *assemblie_list_;
	wxTreeItemId rootId;

	r_assemblies getAssembly(wxTreeItemId itemid);
	r_assemblies getAssembly_by_Instance(wxTreeItemId itemid);
	
	//Qedo::ComponentDeployment *GetSelectedInstance (std::vector<instanceinfo> iinfo,wxTreeItemId itemid);
	//bool isInstance(wxTreeItemId itemid);
	//std::vector<instanceinfo> deleteItem(std::vector<instanceinfo> iinfo,wxTreeItemId itemid);
	void delete_assemblie(wxTreeItemId itemid);
	void undeploy_assembly(r_assemblies assemblie);

	// erase function

	

    DECLARE_EVENT_TABLE()

};
#endif
