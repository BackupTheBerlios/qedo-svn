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

#include "Deployment.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/statline.h"
#include "wx/log.h"
//#include "MainFrame.h"




BEGIN_EVENT_TABLE(Deployment, wxPanel)
   EVT_BUTTON(ID_DEPLOY_BUTTON, Deployment::OnDeployButton)
   EVT_BUTTON(ID_FILE_CHOICE_BUTTON, Deployment::OnFileChoiseButton)
   EVT_BUTTON(ID_UNDEPLOY_BUTTON, Deployment::OnUndeployButton)
 
END_EVENT_TABLE()

Deployment::Deployment(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxPanel(parent, id, pos, size, style)
{

    wxBoxSizer* item2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(item2);
    this->SetAutoLayout(TRUE);

    wxBoxSizer* item3 = new wxBoxSizer(wxVERTICAL);
    item2->Add(item3, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* item4 = new wxBoxSizer(wxHORIZONTAL);
    item3->Add(item4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxStaticText* item5 = new wxStaticText( this, wxID_STATIC, _T("Assembly\nLocation"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add(item5, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    assembly_name_ = new wxTextCtrl( this, ID_ASSNAME_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(300, -1), 0 );
    item4->Add(assembly_name_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    file_choice_btn = new wxButton( this, ID_FILE_CHOICE_BUTTON, _T("Choose File"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add(file_choice_btn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* item8 = new wxBoxSizer(wxHORIZONTAL);
    item3->Add(item8, 0, wxALIGN_LEFT|wxALL, 0);

    deploy_btn = new wxButton( this, ID_DEPLOY_BUTTON, _T("Deploy"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add(deploy_btn, 0, wxGROW|wxALL, 5);

    wxStaticLine* item10 = new wxStaticLine( this, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    item2->Add(item10, 0, wxGROW|wxALL, 5);

    wxBoxSizer* item11 = new wxBoxSizer(wxVERTICAL);
    item2->Add(item11, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* item12 = new wxBoxSizer(wxHORIZONTAL);
    item11->Add(item12, 0, wxALIGN_LEFT|wxALL, 0);

    wxStaticText* item13 = new wxStaticText( this, wxID_STATIC, _T("Running \nAssemblies"), wxDefaultPosition, wxDefaultSize, 0 );
    item12->Add(item13, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    running_ass_list = new wxListCtrl( this, ID_RUNNING_LISTCTRL, wxDefaultPosition, wxSize(400, 100), wxLC_LIST  );
    item12->Add(running_ass_list, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* undeploy_btn = new wxButton( this, ID_UNDEPLOY_BUTTON, _T("Undeploy"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add(undeploy_btn, 0, wxALIGN_LEFT|wxALL, 5);

	assemblies_counter_=0;
	

}

void Deployment::OnFileChoiseButton(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog* file_dialog=new wxFileDialog(this,"Choose a file","","","*.zip",0,wxDefaultPosition);
	int t=file_dialog->ShowModal();
	if (t==wxID_OK) {
		assembly_name_->Clear();
		assembly_name_->WriteText(file_dialog->GetPath());
	}
	file_dialog->~wxFileDialog();

}

void 
Deployment::OnDeployButton(wxCommandEvent& WXUNUSED(event))

{
	//
	// init ORB
	//
	
	int dummy=0;
	orb = CORBA::ORB_init (dummy, 0);

	//
	// Register valuetype factories
	//
	 CORBA::ValueFactoryBase* factory;

	


	factory = new Qedo::CookieFactory_impl();
    orb -> register_value_factory ( "IDL:omg.org/Components/Cookie:1.0", factory );
	std::string package;
	
	package="file:///";
	wxString tmp_string;
	
	tmp_string=assembly_name_->GetValue();
	tmp_string.Replace ("\\","/");
	
	package.append( tmp_string  );


	//
	// deploy the assembly
	//

	
	Qedo::ComponentDeployment *current_assembly = new Qedo::ComponentDeployment(package);
	try
	{
		wxBusyCursor wait_for_deployment;
		current_assembly->deploy();
		assembly_name_->Clear();

		// update internal List of pointers
		r_assemblies new_r_assembly;
		new_r_assembly.id=assemblies_counter_;
		new_r_assembly.reference=current_assembly;

		running_assemblies.push_back(new_r_assembly);

		// update running assemblies list
		running_ass_list->InsertItem(assemblies_counter_,package.c_str());
		assemblies_counter_++;
		
	}
	catch(Qedo::ComponentDeployment::DeploymentFailure&)
	{
		wxLogMessage ("Cannot deploy ");
	//	orb->destroy();
	//	exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "Cannot deploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}
	

	
	

	
	
}

void Deployment::OnUndeployButton(wxCommandEvent& WXUNUSED(event))
{	
	long item=-1;
	for(int t=0;t<=running_ass_list->GetSelectedItemCount();t++)
	{
		item=running_ass_list->GetNextItem(item,
										   wxLIST_NEXT_ALL,
										   wxLIST_STATE_SELECTED);
		//wxLogMessage("%ld und %ld",item,running_ass_list->GetSelectedItemCount());
		if (item!=-1)
			break;

	}
	//wxLogMessage("%ld",item);

	
	r_assemblies tmp_a;
	std::list< r_assemblies >::iterator it = running_assemblies.begin();
	
	for (;it!=running_assemblies.end();it++)
	{
		tmp_a=(*it);
		
		if (tmp_a.id==item) {
			//wxLogMessage ("%ld ",tmp_a.id) ;
			Qedo::ComponentDeployment *current_assembly=tmp_a.reference;

			try
			{
				wxBusyCursor wait_for_undeployment;
				current_assembly->undeploy();
				running_ass_list->DeleteItem(item);
				assemblies_counter_--;

			}
			catch(Qedo::ComponentDeployment::DeploymentFailure&)
			{
				wxLogMessage ("Cannot undeploy ") ;
	
			}
			catch(CORBA::SystemException&)
			{
				wxLogMessage ("Cannot undeploy ") ;
	
			}

			
		}


	}


	
	//wxListItem listitem = running_ass_list->GetSelection();

	//running_ass_list->
	/*
	

	try
	{
		current_assembly->undeploy();
	}
	catch(Qedo::ComponentDeployment::DeploymentFailure&)
	{
		std::cerr << "Cannot undeploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "Cannot undeploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}
	*/
}
