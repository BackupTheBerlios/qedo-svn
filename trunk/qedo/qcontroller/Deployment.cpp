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
#include "wx/datetime.h"

//#include "MainFrame.h"




BEGIN_EVENT_TABLE(Deployment, wxPanel)
   EVT_BUTTON(ID_DEPLOY_BUTTON, Deployment::OnDeployButton)
   EVT_BUTTON(ID_FILE_CHOICE_BUTTON, Deployment::OnFileChoiseButton)
   EVT_BUTTON(ID_UNDEPLOY_BUTTON, Deployment::OnUndeployButton)
   EVT_BUTTON(ID_DESCRIPT_BUTTON, Deployment::OnDecriptButton)
  // EVT_BUTTON(ID_INSTANCE_BUTTON, Deployment::OnInstanceButton)
 
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

	descript_btn = new wxButton( this, ID_DESCRIPT_BUTTON, _T("Edit Destination"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add(descript_btn, 0, wxGROW|wxALL, 5);

    wxStaticLine* item10 = new wxStaticLine( this, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    item2->Add(item10, 0, wxGROW|wxALL, 5);

    wxBoxSizer* item11 = new wxBoxSizer(wxVERTICAL);
    item2->Add(item11, 0, wxALIGN_LEFT|wxALL, 5);

	wxStaticText* item13 = new wxStaticText( this, wxID_STATIC, _T("Running \nAssemblies"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add(item13, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


    wxBoxSizer* item12 = new wxBoxSizer(wxHORIZONTAL);
    item11->Add(item12, 0, wxALIGN_LEFT|wxALL, 0);

	

 //   running_ass_list = new wxListCtrl( this, ID_RUNNING_LISTCTRL, wxDefaultPosition, wxSize(400, 100), wxLC_LIST  );
   // item12->Add(running_ass_list, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* treectrl_sizer=new wxBoxSizer(wxVERTICAL);
	item12->Add(treectrl_sizer,0,wxALIGN_LEFT|wxALL,0);

	wxBoxSizer* button_sizer=new wxBoxSizer(wxVERTICAL);
	item12->Add(button_sizer,0,wxALIGN_LEFT|wxALL,0);
    

	assemblie_list_= new wxTreeCtrl(this,-1,wxDefaultPosition,wxSize(320,300),wxTR_MULTIPLE |wxTR_HAS_BUTTONS ,
								  wxDefaultValidator,_T("TreeCtrl2"));



	treectrl_sizer->Add(assemblie_list_,0,wxALIGN_CENTER_VERTICAL|wxALL,5);

	rootId = assemblie_list_->AddRoot(wxT("Running assemblies"),
                                  -1 , -1 , NULL);

	//wxButton* instance_btn = new wxButton( this, ID_INSTANCE_BUTTON, _T("Start new instance"), wxDefaultPosition, wxSize(120,25), 0 );
    //button_sizer->Add(instance_btn, 0, wxALIGN_LEFT|wxALL, 5);

	//spacer
	//button_sizer->Add(5, 15, 0, wxGROW | wxALL, 5);

	wxButton* undeploy_btn = new wxButton( this, ID_UNDEPLOY_BUTTON, _T("Undeploy"), wxDefaultPosition, wxSize(120,25), 0 );
    button_sizer->Add(undeploy_btn, 0, wxALIGN_LEFT|wxALL, 5);


	//assemblies_counter_=0;


	

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
		wxTreeItemId asId=assemblie_list_->AppendItem(rootId,package.c_str(), -1,-1,NULL);
		wxString instancetext="Instance started at ";
		// Get current time and date
		wxDateTime *datetime = new wxDateTime();
		wxDateTime today=datetime->Today();
		wxDateTime time=datetime->Now();


		instancetext.Append(time.FormatISOTime());
		instancetext.Append(" on ");
		instancetext.Append(today.FormatISODate());
		wxTreeItemId inId=assemblie_list_->AppendItem(asId,instancetext,-1,-1,NULL);

		// update internal List of pointers
		instanceinfo new_instance;
		new_instance.itemid=inId;
		new_instance.reference=current_assembly;

		r_assemblies new_r_assembly;
		new_r_assembly.itemid=asId;
		new_r_assembly.package=package;
		new_r_assembly.instanceinfo_list.push_back(new_instance);
		//new_r_assembly.id=assemblies_counter_;
		//new_r_assembly.reference=current_assembly;

		running_assemblies.push_back(new_r_assembly);

		// update running assemblies list
		//running_ass_list->InsertItem(assemblies_counter_,package.c_str());
		//assemblies_counter_++;
		assemblie_list_->Refresh();
		assemblie_list_->Expand(rootId);
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
	wxArrayTreeItemIds selected_;
	int s_s = assemblie_list_->GetSelections(selected_);

	if(s_s>0)
	{
		
		for (int i=0;i<s_s;i++) 
		{
			wxTreeItemId itemid = selected_[i];
			if (assemblie_list_->GetItemText(itemid)!="Running assemblies") 
			{
				r_assemblies assemblie=getAssembly(itemid);
				undeploy_assembly(assemblie);
			
			/*
			if (isInstance(itemid)) {
				std::vector <instanceinfo> iinfo=assemblie.instanceinfo_list;
				

				Qedo::ComponentDeployment *current_assembly=GetSelectedInstance(iinfo,itemid);
				
				try
				{
					wxBusyCursor wait_for_undeployment;
					current_assembly->undeploy();
					std::vector <instanceinfo> list=deleteItem(assemblie.instanceinfo_list,itemid);
					
					assemblie.instanceinfo_list=list;
					
					assemblie_list_->Delete(itemid);
					if (assemblie.instanceinfo_list.empty())
					{
						
						assemblie_list_->Delete(assemblie.itemid);
						delete_assemblie(assemblie.itemid);
						
					}
						//running_ass_list->DeleteItem(item);
				}
				catch(Qedo::ComponentDeployment::DeploymentFailure&)
				{
					wxLogMessage ("Cannot undeploy ") ;
				}
				catch(CORBA::SystemException&)
				{
					wxLogMessage ("Cannot undeploy ") ;
				}

			} else {
				undeploy_assembly(assemblie);
			}
			*/
			}
		}

	}

			
	
}
/*
bool Deployment::isInstance(wxTreeItemId itemid)
{
	bool retrn=true;
	
	if ((assemblie_list_->GetItemParent(itemid))==rootId)
	{
		retrn=false;
	}

	return retrn;
}
*/

/*
Qedo::ComponentDeployment 
	*Deployment::GetSelectedInstance
	(std::vector <instanceinfo> iinfo,wxTreeItemId itemid)
{
	Qedo::ComponentDeployment *retrn;
	std::vector<instanceinfo>::iterator i_iter;
	for(i_iter = iinfo.begin(); 
		i_iter != iinfo.end();
		i_iter++)
		{	
			if ((*i_iter).itemid==itemid)
			{
				retrn=(*i_iter).reference;
			}
		}

	return retrn;
}
*/

/*
std::vector <Deployment::instanceinfo> Deployment::deleteItem(std::vector<Deployment::instanceinfo> iinfo,wxTreeItemId itemid)
{
	std::vector<instanceinfo> ::iterator i_iter;
	std::vector<instanceinfo> ::iterator i_iter_two;
	
	for(i_iter = iinfo.begin(); 
		i_iter != iinfo.end();
		i_iter++)
		{	
			
			if ((*i_iter).itemid==itemid)
			{
				i_iter_two=i_iter;
				break;
			}
		}
		
	iinfo.erase(i_iter_two);
	
	return iinfo;

}
*/
void Deployment::delete_assemblie(wxTreeItemId itemid)
{
	std::vector<r_assemblies>::iterator a_iter;
	std::vector<r_assemblies>::iterator a_iter_two;
	for(a_iter = running_assemblies.begin(); 
		a_iter != running_assemblies.end();
		a_iter++)
		{	
			if ((*a_iter).itemid==itemid)
			{
				a_iter_two=a_iter;
				break;
				
			}
		}

		running_assemblies.erase(a_iter_two);
}


void Deployment::OnDecriptButton (wxCommandEvent& WXUNUSED(event)) 
{
	if (!(assembly_name_->GetValue().empty()))
	{
		DescriptorFrame *descriptor_frame = new DescriptorFrame(this,assembly_name_->GetValue());
		//descriptor_frame->SetFile(assembly_name_->GetValue().c_str() );
	
		int t=descriptor_frame->ShowModal();
		if (t==wxID_OK) {
		
		}
		if (t==wxID_CANCEL) {
			descriptor_frame->~DescriptorFrame();
		}
	}

}

/*
void Deployment::OnInstanceButton (wxCommandEvent& WXUNUSED(event))
{
	wxArrayTreeItemIds selected_;
	int s_s = assemblie_list_->GetSelections(selected_);

	if (s_s >0) 
	{
		for (int i=0;i<s_s;i++) 
		{
			wxTreeItemId itemid=selected_[i];
			r_assemblies assemblie=getAssembly(itemid);
			
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
			Qedo::ComponentDeployment *current_assembly = new Qedo::ComponentDeployment(assemblie.package);
			try
			{
				wxBusyCursor wait_for_deployment;
				current_assembly->deploy();
		
				wxString instancetext="Instance started at ";
				// Get current time and date
				wxDateTime *datetime = new wxDateTime();
				wxDateTime today=datetime->Today();
				wxDateTime time=datetime->Now();


				instancetext.Append(time.FormatISOTime());
				instancetext.Append(" on ");
				instancetext.Append(today.FormatISODate());
				wxTreeItemId inId=assemblie_list_->AppendItem(assemblie.itemid,instancetext,-1,-1,NULL);


				// update internal List of pointers
				r_assemblies new_assemblies;
				new_assemblies.itemid=assemblie.itemid;
				new_assemblies.package=assemblie.package;
				new_assemblies.instanceinfo_list=assemblie.instanceinfo_list;
				instanceinfo new_instance;
				new_instance.itemid=inId;
				new_instance.reference=current_assembly;
				delete_assemblie(assemblie.itemid);
				new_assemblies.instanceinfo_list.push_back(new_instance);
				running_assemblies.push_back(new_assemblies);

		
		
			}
			catch(Qedo::ComponentDeployment::DeploymentFailure&)
			{
				wxLogMessage ("Cannot create new instance ");
				//	orb->destroy();
				//	exit(1);
			}
			catch(CORBA::SystemException&)
			{
				std::cerr << "Cannot deploy " << assemblie.package << std::endl;
			//	orb->destroy();
			//	exit(1);
			}

			
		}

	}
}
*/


Deployment::r_assemblies Deployment::getAssembly(wxTreeItemId itemid)
{
	
	std::vector <r_assemblies> ::iterator a_iter;
	for(a_iter = running_assemblies.begin(); 
		a_iter != running_assemblies.end();
		a_iter++)
		{	
			if ((*a_iter).itemid==itemid) 
			{
				return (*a_iter);
			}
		}		

	return getAssembly_by_Instance(itemid);
	
}

Deployment::r_assemblies Deployment::getAssembly_by_Instance(wxTreeItemId itemid)
{
	wxTreeItemId parent = assemblie_list_->GetItemParent(itemid);
	return getAssembly(parent);
}

void Deployment::undeploy_assembly(r_assemblies assemblie)
{
	try
	{
		std::vector<instanceinfo>::iterator i_iter;
		i_iter=assemblie.instanceinfo_list.begin();
		instanceinfo i = (*i_iter);
		i.reference->undeploy();
		assemblie_list_->Delete(assemblie.itemid);
		delete_assemblie(assemblie.itemid);
		assemblie_list_->Refresh();
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

