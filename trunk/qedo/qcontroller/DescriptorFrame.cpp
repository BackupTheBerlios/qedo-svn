// For compilers that supports precompilation , includes "wx/wx.h"
#include "wx/wxprec.h"

/*
#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif
*/

#include "DescriptorFrame.h"
#include "CADReaderDialog.h"
#include "wx/sizer.h"
#include "wx/listctrl.h"
#include "wx/statline.h"
#include "wx/process.h"
#include "wx/utils.h"

BEGIN_EVENT_TABLE(DescriptorFrame, wxDialog)
   EVT_BUTTON(ID_COMPONENTS_TO_SERVER, DescriptorFrame::OnComponents_to_Server)
   EVT_BUTTON(ID_COMPONENTS_TO_COMPONENTS, DescriptorFrame::OnComponents_to_Components)
   EVT_BUTTON(ID_SAVE_SETTINGS, DescriptorFrame::OnSave_Settings )
   EVT_BUTTON(ID_CANCEL, DescriptorFrame::OnQuit)
   EVT_BUTTON(ID_ALL_TO_COMPONENTS, DescriptorFrame::OnAllComponentsBack)
   EVT_BUTTON(ID_SAVE_SETTINGS_AS, DescriptorFrame::OnSave_as)
END_EVENT_TABLE()

DescriptorFrame::DescriptorFrame(wxWindow *parent,wxString filename) 
			: wxDialog(parent, -1, "Edit Destinitation", wxDefaultPosition,
					   wxSize(650,510),wxDEFAULT_DIALOG_STYLE)
{
	wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);
	this->file=filename.c_str() ;


	//spacer
	sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);

	// static text 
	wxStaticText *e_text = new wxStaticText( this, wxID_STATIC, _T("Change the destination of hostcollocation, processcollocation or homeplacements in:"), wxDefaultPosition, wxDefaultSize, 0 );
    sizerLauncher->Add(e_text, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	file_text=new wxStaticText(this,wxID_STATIC, _T(file.c_str()),wxDefaultPosition,wxDefaultSize,0);
	sizerLauncher->Add(file_text,0,wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE,5);

	wxBoxSizer *midSizer=new wxBoxSizer(wxHORIZONTAL);
	sizerLauncher->Add(midSizer, 0, wxALIGN_CENTER_VERTICAL| wxALL, 5);
	
	// Explorer Tree Controll
	wxStaticBox *exp_tree_ctrl_box = new wxStaticBox(this, -1, _T("&Process or homeplacements without destination"));
	wxStaticBoxSizer *h_TC_sizer = new wxStaticBoxSizer(exp_tree_ctrl_box,wxHORIZONTAL);
	midSizer->Add(h_TC_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	component_list_= new wxTreeCtrl(this,-1,wxDefaultPosition,wxSize(220,300),wxTR_MULTIPLE |wxTR_HAS_BUTTONS ,
								  wxDefaultValidator,_T("TreeCtrl2"));
	h_TC_sizer->Add(component_list_,0,wxALIGN_CENTER_VERTICAL|wxALL,5);

	rootId2 = component_list_->AddRoot(wxT("Placements without Destination"),
                                  -1 , -1 , NULL);
	
	//Transfer Buttons

	wxBoxSizer *midmidSizer=new wxBoxSizer(wxVERTICAL);
	midSizer->Add(midmidSizer, 0, wxALIGN_CENTER_VERTICAL| wxALL, 5);

	// >>> Button
	components_to_server = new wxButton(this, ID_COMPONENTS_TO_SERVER, _T("   Selection to server >>>"));
	midmidSizer->Add(components_to_server , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//spacer
	midmidSizer->Add(5, 30, 0, wxGROW | wxALL, 5);

	// line
	wxStaticLine* line = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "Node Launcher" );
	midmidSizer->Add(line , 0, wxGROW|wxALL, 5);
	
	//spacer
	midmidSizer->Add(5, 15, 0, wxGROW | wxALL, 5);

	// <<< Components without destination
	components_to_components = new wxButton(this, ID_COMPONENTS_TO_COMPONENTS, _T("<<< back to components"));
	midmidSizer->Add(components_to_components , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//spacer
	midmidSizer->Add(5, 15, 0, wxGROW | wxALL, 5);

	all_components_to_components = new wxButton(this, ID_ALL_TO_COMPONENTS, _T("<<< all components back"));
	midmidSizer->Add(all_components_to_components , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	// ServerActivator 
	wxStaticBox *expbox = new wxStaticBox(this, -1, _T("&ServerActivators"));
	wxStaticBoxSizer *h_exp_sizer = new wxStaticBoxSizer(expbox,wxHORIZONTAL);
	midSizer->Add(h_exp_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	server_ctrl_ = new wxTreeCtrl(this,-1,wxDefaultPosition,wxSize(200,300),wxTR_MULTIPLE |wxTR_HAS_BUTTONS,
								  wxDefaultValidator,_T("TreeCtrl"));
	h_exp_sizer->Add(server_ctrl_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    rootId = server_ctrl_->AddRoot(wxT("Destination Nodes"),
                                  -1 , -1 , NULL);
	// Save and Exit

	wxBoxSizer *downSizer=new wxBoxSizer(wxHORIZONTAL);
	sizerLauncher->Add(downSizer, 0, wxALIGN_CENTER_VERTICAL| wxALL, 5);

	wxStaticBox *downbox = new wxStaticBox(this, -1, _T("&Save or Cancel"));
	wxStaticBoxSizer *h_dow_Sizer = new wxStaticBoxSizer(downbox,wxHORIZONTAL);
	
	downSizer->Add(h_dow_Sizer, 0, wxALIGN_CENTER_VERTICAL| wxALL, 5);

	save_ = new wxButton(this, ID_SAVE_SETTINGS, _T("Save settings"));
	h_dow_Sizer->Add(save_ , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//spacer
	h_dow_Sizer->Add(45, 5, 0, wxGROW | wxALL, 5);

	save_as_ = new wxButton(this, ID_SAVE_SETTINGS_AS, _T("Save as"));
	h_dow_Sizer->Add(save_as_ , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	//spacer
	h_dow_Sizer->Add(290, 5, 0, wxGROW | wxALL, 5);

	cancel_ = new wxButton(this, ID_CANCEL, _T("Quit"));
	h_dow_Sizer->Add(cancel_ , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);


	
	CadReaderDialogFrame *cadreader_frame = new CadReaderDialogFrame(this,file.c_str(),false );
	
	// cadreader_frame->ShowModal():

	//partitioning = cadreader_frame->partitioning;
		processdatas = cadreader_frame->processdatas;
		homedatas = cadreader_frame->homedatas;
		hostdatas = cadreader_frame->hostdatas;
		tmp_file=cadreader_frame->tmp_file;
		cadfile=cadreader_frame->file;

		cadreader_frame->~CadReaderDialogFrame();

    			
		addServerActivators();

		addHostcollocation();

		addProccesscollocation();

		addHomeplacement();
	
		
		server_ctrl_->Refresh();
		server_ctrl_->Expand(rootId);
	
	
	
}


void DescriptorFrame::addHomeplacement()
{
	std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
	int itercounter=-1;
	for(home_iter = homedatas.begin(); 
			home_iter != homedatas.end();
			home_iter++)
			{
				itercounter++;
				if ((*home_iter).dest.specified) {

					
					wxTreeItemId itemid = getItemId((*home_iter).dest.node.c_str());
					addHometoServer(*home_iter,itemid,itercounter);
					
					server_ctrl_->Refresh();
					server_ctrl_->Expand(rootId);

				}

				if (!(*home_iter).dest.specified) {
					
					addHometoComponent(*home_iter,rootId2,itercounter);
					
					component_list_->Refresh();
					component_list_->Expand(rootId2);
				}

			}

}
void DescriptorFrame::addHometoComponent(Qedo::HomeInstanceData home, wxTreeItemId itemid,int iter)
{
    
	wxString tmp_string="Homeplacement";
	tmp_string.append("(");
	tmp_string.append(home.id.c_str());
	tmp_string.append(")");
	wxTreeItemId coId=component_list_->AppendItem(itemid,tmp_string, -1,-1,NULL);

	
		if (itemid==rootId2) {

			noDestinationInfo noDeli;
			noDeli.itemid=coId;
			noDeli.iter=iter;
			noDeli.typ=homeplacement;
		
			noDestinationInfoList.push_back(noDeli);

			component_list_->SetItemBold(coId,TRUE);

		}

}


void DescriptorFrame::addHometoServer(Qedo::HomeInstanceData home,wxTreeItemId itemid, int iter)
{
	wxString tmp_string="Homeplacement";
	

	// first adding by reading cad file
	if (itemid==rootId) 
		{
				// Destination is known
				if (iskown(home.dest.node.c_str())) {

					tmp_string.append("(");
					tmp_string.append(home.id.c_str());
					tmp_string.append(")");
					wxTreeItemId apId = server_ctrl_->AppendItem(itemid, tmp_string,		
															-1,-1,NULL);
					itemid=apId;

				// Destination is unkown
				} else {
					
					wxString tmp2_string=home.dest.node.c_str();
					
					if (isunkown_kown(tmp2_string))
					{
						itemid=get_unkown_itemid(tmp2_string);
						
					} else {
						tmp2_string.append("(unkown)");
						wxTreeItemId i = server_ctrl_->AppendItem(itemid, tmp2_string,
															-1,-1,NULL);
						server_ctrl_->SetItemBold(i,TRUE);
						itemid=i;
					}
				}
		}
		
		tmp_string.append("(");
		tmp_string.append(home.id.c_str());
		tmp_string.append(")");
		wxTreeItemId apId = server_ctrl_->AppendItem(itemid, tmp_string,-1,-1,NULL);

		// if iter==-1 then item has a parent
		// if no parent, then add to DestinationInfo
		if (!(iter==-1))
		{
			DestinationInfo deli;
			deli.itemid=apId;
			deli.iter=iter;
			deli.node=getNode(itemid);
			deli.typ=homeplacement;
			DestinationInfoList.push_back(deli);	
		}
}

void DescriptorFrame::addHostcollocation()
{
	std::vector <Qedo::HostData> ::iterator host_iter;
    int itercounter=0;
	for(host_iter = hostdatas.begin(); 
			host_iter != hostdatas.end();
			host_iter++)
			{
				
				if ((*host_iter).dest.specified) {

					addHosttoServer(*host_iter,rootId,itercounter);
					
					server_ctrl_->Refresh();
					server_ctrl_->Expand(rootId);

				}
				

				if (!(*host_iter).dest.specified) {

					addHosttoComponent(*host_iter,itercounter);

					component_list_->Refresh();
					component_list_->Expand(rootId2);
					
				}
				itercounter++;
			}



}

void DescriptorFrame::addHosttoServer(Qedo::HostData host,wxTreeItemId itemId,int iter)
{
	std::vector <Qedo::ProcessData> processes=host.processes;
	std::vector <Qedo::ProcessData> ::iterator process_iter;
	wxTreeItemId apId_tmp;
	wxTreeItemId item_dest_id;
	
	// first adding after reading cad file
	if (itemId==rootId) 
	{
		if (iskown(host.dest.node.c_str())) {

			item_dest_id = getItemId(host.dest.node.c_str());
			wxTreeItemId apId = server_ctrl_->AppendItem(item_dest_id, _T("Hostcollocation"),
														-1,-1,NULL);
			apId_tmp=apId;
		} else {
			wxString tmp_string=host.dest.node.c_str();
			tmp_string.append("(unkown)");

			item_dest_id = server_ctrl_->AppendItem(rootId, tmp_string,-1,-1,NULL);
			server_ctrl_->SetItemBold(item_dest_id,TRUE);
			wxTreeItemId apId = server_ctrl_->AppendItem(item_dest_id, _T("Hostcollocation"),
														-1,-1,NULL);
			apId_tmp=apId;
		}

	} else {
			apId_tmp = server_ctrl_->AppendItem(itemId, _T("Hostcollocation"),-1,-1,NULL);
			item_dest_id=itemId;
	}

	// put hostcollocation to DestinationInfo
	DestinationInfo deli1;
	deli1.itemid=apId_tmp;
	deli1.node=getNode(item_dest_id);
	deli1.iter=iter;
	deli1.typ=hostcollocation;

	DestinationInfoList.push_back(deli1);

	// add processcollocation
	for(process_iter = processes.begin(); 
			process_iter != processes.end();
			process_iter++)
			{
				addProcesstoServer(*process_iter,apId_tmp,-1);

			}

}

void DescriptorFrame::addHosttoComponent(Qedo::HostData host, int iter)
{
	wxTreeItemId coId=component_list_->AppendItem(rootId2,_T("Hostcollocation"), -1,-1,NULL);

	noDestinationInfo deli;
	deli.itemid=coId;
	deli.iter=iter;
	deli.typ=hostcollocation;

	noDestinationInfoList.push_back(deli);
		
	component_list_->SetItemBold(coId,TRUE);

	std::vector <Qedo::ProcessData> processes=host.processes;
	std::vector <Qedo::ProcessData> ::iterator process_iter;
	
	for(process_iter = processes.begin(); 
			process_iter != processes.end();
			process_iter++)
			{
				addProcesstoComponent(*process_iter,coId,-1);
			}

					
}

void DescriptorFrame::addProccesscollocation()
{
	std::vector <Qedo::ProcessData> ::iterator process_iter;
	int itercounter=-1;
	for(process_iter = processdatas.begin(); 
			process_iter != processdatas.end();
			process_iter++)
			{
				itercounter++;
				if ((*process_iter).dest.specified) {

					addProcesstoServer(*process_iter,rootId,itercounter);
					
					server_ctrl_->Refresh();
					server_ctrl_->Expand(rootId);

				}

				if (!(*process_iter).dest.specified) {

					addProcesstoComponent(*process_iter,rootId2,itercounter);
					
					component_list_->Refresh();
					component_list_->Expand(rootId2);
					
				}

			}

}
void DescriptorFrame::addProcesstoComponent(Qedo::ProcessData process,wxTreeItemId itemid,int iter)
{

	wxTreeItemId coId=component_list_->AppendItem(itemid,_T("Processcollocation"), -1,-1,NULL);

	if (itemid==rootId2) {
		
		noDestinationInfo noDestList;
		noDestList.itemid=coId;
		noDestList.iter=iter;
		noDestList.typ=processcollocation;
		noDestinationInfoList.push_back(noDestList);
		component_list_->SetItemBold(coId,TRUE);

	}


	std::vector <Qedo::HomeInstanceData> homes = process.homes;
	std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
	
	for(home_iter = homes.begin(); 
		home_iter != homes.end();
		home_iter++)
		{
			addHometoComponent(*home_iter,coId,-1);
		}		

}
void DescriptorFrame::addProcesstoServer(Qedo::ProcessData process,wxTreeItemId itemId,int iter)
{
	std::vector <Qedo::HomeInstanceData> homes = process.homes;
	std::vector <Qedo::HomeInstanceData> ::iterator home_iter;

	wxTreeItemId apId;
	wxTreeItemId item_dest_id;

	// first adding after reading cad file
	if (itemId==rootId) {

		// Destination node is kown
		if (iskown(process.dest.node.c_str())) {

			item_dest_id = getItemId(process.dest.node.c_str());

			apId = server_ctrl_->AppendItem(item_dest_id, _T("Processcollocation"),
															-1,-1,NULL);
		// Destination node is unkown
		} else { 

			wxString tmp_string=process.dest.node.c_str();
			tmp_string.append("(unkown)");

			item_dest_id = server_ctrl_->AppendItem(rootId, tmp_string,-1,-1,NULL);
			server_ctrl_->SetItemBold(item_dest_id,TRUE);
			apId = server_ctrl_->AppendItem(item_dest_id, _T("Processcollocation"),
											-1,-1,NULL);
		}	

	// if a destination node selected			
	} else {

		apId = server_ctrl_->AppendItem(itemId, _T("Processcollocation"),
													-1,-1,NULL);
		item_dest_id=itemId;
	}


	// add homes of processcollocation
	for(home_iter = homes.begin(); 
		home_iter != homes.end();
		home_iter++)
		{	
			addHometoServer(*home_iter,apId,-1);
		}	

	// if processcollocation have no hostcollocation 
	// then add to DestinationInfo

	if (!(iter==-1)) 
	{
		DestinationInfo delist;
		delist.itemid=apId;
		delist.iter=iter;
		delist.node=getNode(item_dest_id);
		delist.typ=processcollocation;
		DestinationInfoList.push_back(delist);		
    }
}

bool DescriptorFrame::iskown(std::string node)
{
	std::vector <serverinfo> ::iterator server_iter;
	bool retrn = false;
	for(server_iter = serverinfolist.begin(); 
			server_iter != serverinfolist.end();
			server_iter++)
			{
				if ((*server_iter).servername==node) {
					
					retrn=true;
					break;
				}
			}

	return retrn;
}

bool DescriptorFrame::isunkown_kown(wxString node)
{	bool retrn=false;
	
	std::vector <DestinationInfo>::iterator DestInfo_iter;
		for (DestInfo_iter = DestinationInfoList.begin();
			 DestInfo_iter != DestinationInfoList.end();
			 DestInfo_iter++)
			{
				if ((*DestInfo_iter).node.c_str()==node) 
				{
					retrn=true;
					break;
				}
			}
	return retrn;
}

wxTreeItemId DescriptorFrame::get_unkown_itemid(wxString node)
{
	wxTreeItemId itemid;
	std::vector <DestinationInfo>::iterator DestInfo_iter;
		for (DestInfo_iter = DestinationInfoList.begin();
			 DestInfo_iter != DestinationInfoList.end();
			 DestInfo_iter++)
			{
				if ((*DestInfo_iter).node==node) 
				{
					itemid=server_ctrl_->GetParent((*DestInfo_iter).itemid);
					break;
				}
			}
	
	
	return itemid;
}

wxTreeItemId DescriptorFrame::getItemId(std::string node)
{
	std::vector <serverinfo> ::iterator server_iter;
	wxTreeItemId retrn=rootId;
	for(server_iter = serverinfolist.begin(); 
			server_iter != serverinfolist.end();
			server_iter++)
			{
				if ((*server_iter).servername==node) {
					retrn=(*server_iter).itemid;
				}
			}
	return retrn;
}


void DescriptorFrame::addServerActivators() 
{
	//
	// init ORB
	//
	
	int dummy=0;
	e_orb = CORBA::ORB_init (dummy, 0);

	// get name services reference

	std::string ns;
	ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );

	CORBA::Object_var obj;
	obj = e_orb -> string_to_object( ns.c_str() );
	

	try {
		nameService = CosNaming::NamingContext::_narrow(obj.in());
	} catch (CORBA::SystemException) {};
		if (!CORBA::is_nil(nameService))
		{
			CosNaming::Name cname;
			cname.length(2);
			cname[0].id=CORBA::string_dup("Qedo");
			cname[0].kind=CORBA::string_dup("");
			cname[1].id=CORBA::string_dup("Activators");
			cname[1].kind=CORBA::string_dup("");
	
		
			CosNaming::NamingContext_var ncQA = CosNaming::NamingContext::_nil();
			CORBA::Object_var obj = nameService->resolve(cname);
			ncQA = CosNaming::NamingContext::_narrow (obj);
		
			try {
		
			CosNaming::BindingList *test;
			CosNaming::BindingIterator *test2;
			ncQA->list(100,test,test2);

			CosNaming::BindingList_var bl = test;
			CosNaming::BindingIterator_var bi = test2;
			
			DescriptorFrame::serverinfo si ;
			for (CORBA::ULong as=0;as<bl->length();as++) {

			
				CosNaming::Binding b=bl->operator [](as);
							
				wxTreeItemId id = server_ctrl_->AppendItem(rootId, _T(CORBA::string_dup( b.binding_name[0].id) ),-1,-1,NULL);
				server_ctrl_->SetItemBold(id,TRUE);
				si.servername=CORBA::string_dup( b.binding_name[0].id);
				si.itemid=id;
				serverinfolist.push_back(si);


			}
			} catch (CORBA::SystemException&)
			{ }
		 
	}
}

void DescriptorFrame::OnComponents_to_Components(wxCommandEvent& WXUNUSED(event))
{
	wxArrayTreeItemIds selected;
	int t=server_ctrl_->GetSelections(selected);
	
	for (int i=0;i<t; i++) {
		wxTreeItemId item = selected[i];
		if ( (!(server_ctrl_->IsBold(item))) )
		{
			if (!(item==rootId)) {

				DestinationInfo destinfo = getLastParent_server(item);
				add_component_to_components(destinfo);

				
			}
		}

	
	}
	
}
	

void DescriptorFrame::OnComponents_to_Server(wxCommandEvent& WXUNUSED(event))
{
	wxArrayTreeItemIds server_selected_;
	int s_s = server_ctrl_->GetSelections(server_selected_);

	if ( s_s>0) 
	{
		wxTreeItemId item =server_selected_[0];

		wxString server_string=server_ctrl_->GetItemText(item);

		wxArrayTreeItemIds selected;
		int t=component_list_->GetSelections(selected);

		// check selections
		if (checkselections(item,t)) {
		
			warningserver(server_string);

			for (int i=0;i<t;i++) {

				wxString tmp_string=component_list_->GetItemText(selected[i]);
				if (!(tmp_string=="Process or homeplacements without destination")) 
				{
					if (!(selected[i]==rootId2))
					{
						noDestinationInfo tmp_item=getLastParent(selected[i]);
						wxString tmp_string2 = component_list_->GetItemText(tmp_item.itemid);
						if (tmp_item.itemid==selected[i]) {

						add_component_to_server(tmp_item,item);


					} else {
					
						wxString message;
						message=tmp_string;
						message.append(" is bound on ");
						message.append(tmp_string2);
						message.append(". Only ");
						message.append(tmp_string2);
						message.append(" can be added to ");
						message.append(server_string);
						message.append(". Make further ?");

						wxMessageDialog* mess_dialog=new wxMessageDialog(this,message,"Message box",wxYES_NO | wxCENTRE | wxICON_QUESTION, wxDefaultPosition);
						int t=mess_dialog->ShowModal();
						if (t==wxID_YES) {

							add_component_to_server(tmp_item,item);
						}
						mess_dialog->~wxMessageDialog();
					}
				}

			}
			
		}
		
		wxString tmp_string=component_list_->GetItemText(selected[0]);
	}
	
	}
}

void DescriptorFrame::add_component_to_components(DestinationInfo DestInfo)
{
	if (DestInfo.typ==homeplacement)
	{
		std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
		int itercounter=0;
		for(home_iter = homedatas.begin(); 
				home_iter != homedatas.end();
				home_iter++)
				{	
					if (itercounter==DestInfo.iter) {
						addHometoComponent(*home_iter,rootId2,itercounter);
						server_ctrl_->Delete(DestInfo.itemid);
						
					}
					itercounter++;
					
				}		
	}

	if (DestInfo.typ==processcollocation)
	{
		std::vector <Qedo::ProcessData> ::iterator process_iter;
		int itercounter=0;
		for(process_iter = processdatas.begin(); 
				process_iter != processdatas.end();
				process_iter++)
				{
					
					if (itercounter==DestInfo.iter) {
						
						addProcesstoComponent(*process_iter,rootId2,itercounter);
						server_ctrl_->Delete(DestInfo.itemid);
						
					}
					itercounter++;
					
				}		
	}

	if (DestInfo.typ==hostcollocation) 
	{
		std::vector <Qedo::HostData> ::iterator host_iter;
		int itercounter=0;
		for(host_iter = hostdatas.begin(); 
				host_iter != hostdatas.end();
				host_iter++)
				{
					
					if (itercounter==DestInfo.iter) {
						addHosttoComponent(*host_iter,itercounter);
						server_ctrl_->Delete(DestInfo.itemid);
						
					}
					itercounter++;
					
				}		

	}

	delete_destination(DestInfo);
	component_list_->Refresh();
	server_ctrl_->Refresh();


}

void DescriptorFrame::add_component_to_server(noDestinationInfo noDestInfo,wxTreeItemId itemid)
{
	if (noDestInfo.typ==homeplacement)
	{
		std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
		int itercounter=0;
		for(home_iter = homedatas.begin(); 
				home_iter != homedatas.end();
				home_iter++)
				{
					if (itercounter==noDestInfo.iter) {
						addHometoServer(*home_iter,itemid,itercounter);
						component_list_->Delete(noDestInfo.itemid);
						
					}
					itercounter++;
					
				}		
	}

	if (noDestInfo.typ==processcollocation)
	{
		std::vector <Qedo::ProcessData> ::iterator process_iter;
		int itercounter=0;
		for(process_iter = processdatas.begin(); 
				process_iter != processdatas.end();
				process_iter++)
				{
					if (itercounter==noDestInfo.iter) {
						addProcesstoServer(*process_iter,itemid,itercounter);
						component_list_->Delete(noDestInfo.itemid);
						
					}
					itercounter++;
					
				}		
	}

	if (noDestInfo.typ==hostcollocation) 
	{
		std::vector <Qedo::HostData> ::iterator host_iter;
		int itercounter=0;

		for(host_iter = hostdatas.begin(); 
			host_iter != hostdatas.end();
			host_iter++)
			{
					if (itercounter==noDestInfo.iter) {
						addHosttoServer(*host_iter,itemid,itercounter);
						component_list_->Delete(noDestInfo.itemid);
					}
					itercounter++;
					
				}		

	}
    
	delete_nodestination(noDestInfo);
	component_list_->Refresh();
	server_ctrl_->Refresh();

}


DescriptorFrame::noDestinationInfo DescriptorFrame::getLastParent(wxTreeItemId item)
{ 
	std::vector <noDestinationInfo> ::iterator nodest_iter;
	noDestinationInfo retrn;
	bool value=true;

	for(nodest_iter = noDestinationInfoList.begin(); 
			nodest_iter != noDestinationInfoList.end();
			nodest_iter++)
			{
				if ((*nodest_iter).itemid==item) {
					retrn=(*nodest_iter);
					value=true;
					break;
				} else
				{
					value=false;
				}
			}

		if (!(value)) 
		{
			retrn=getLastParent(component_list_->GetItemParent(item));
		}
		
		return retrn;
	
}

DescriptorFrame::DestinationInfo DescriptorFrame::getLastParent_server(wxTreeItemId item)
{
	std::vector <DestinationInfo> ::iterator dest_iter;
	DestinationInfo retrn;
	
	bool value=true;
		
		for(dest_iter = DestinationInfoList.begin(); 
				dest_iter != DestinationInfoList.end();
				dest_iter++)
				{
					
					if ((*dest_iter).itemid==item) {
						retrn=(*dest_iter);
						value=true;
						break;
					} else
					{
						value=false;
					}
				}
		if (!(value)) 
		{
			retrn=getLastParent_server(component_list_->GetItemParent(item));
		}
		
	return retrn;
	
}

void DescriptorFrame::delete_nodestination(noDestinationInfo noDestInfo) 
{
	std::vector <noDestinationInfo> ::iterator nodest_iter;
	for(nodest_iter = noDestinationInfoList.begin(); 
				nodest_iter != noDestinationInfoList.end();
				nodest_iter++)
				{
					if ( (*nodest_iter).itemid==noDestInfo.itemid )
					{
						noDestinationInfoList.erase(nodest_iter);
						break;
					}
				}

}

void DescriptorFrame::delete_destination(DestinationInfo DestInfo) 
{
	std::vector <DestinationInfo> ::iterator dest_iter;
	for(dest_iter = DestinationInfoList.begin(); 
				dest_iter != DestinationInfoList.end();
				dest_iter++)
				{
					if ( (*dest_iter).itemid==DestInfo.itemid )
					{
						DestinationInfoList.erase(dest_iter);
						break;
					}
				}

}

wxString DescriptorFrame::getNode(wxTreeItemId item)
{

	wxString tmp_string=server_ctrl_->GetItemText(item);
	tmp_string.Replace("(unkown)","",TRUE);
	return tmp_string;


}


bool DescriptorFrame::checkselections(wxTreeItemId item,int counter) 
{
	bool retrn=true;


	if (!(server_ctrl_->IsBold(item))) { retrn=false;	}

    if (counter<1) { retrn=false; }


	return retrn;
}

void DescriptorFrame::warningserver(wxString server) 
{
	if (server.substr(strlen(server)-8,strlen(server))=="(unkown)") 
	{
		wxString message="The Destination (";
		wxString tmp=server.substr(0,strlen(server)-8 );

		message.append(tmp);
		message.append(") is unkown. The Deployment could not function !");
		wxMessageDialog* mess_dialog=new wxMessageDialog(this,message,"Warning box",wxOK | wxCENTRE | wxICON_EXCLAMATION, wxDefaultPosition);
						int t=mess_dialog->ShowModal();
						if (t==wxID_OK) {

							// do bla bla
						}
		mess_dialog->~wxMessageDialog();
	}

}

bool DescriptorFrame::into_zip(std::string cad,std::string zip)
{
	bool value;
	wxProcess *process = new wxProcess(this);

	
			
    wxString cmd = "zip -m ";
	cmd.append(zip.c_str());
	cmd.append(" ");
	cmd.append(cad.c_str());
	
	
	value = wxExecute(cmd, wxEXEC_SYNC, NULL);
	delete process;
	
	return value;
}

void DescriptorFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	delete(this);
}

void DescriptorFrame::OnAllComponentsBack(wxCommandEvent& WXUNUSED(event))
{
	if (!(DestinationInfoList.empty())) 
	{
		std::vector <DestinationInfo> ::iterator dest_iter;
		std::vector <DestinationInfo> tmp_list;
	
		for(dest_iter = DestinationInfoList.begin(); 
			dest_iter != DestinationInfoList.end();
			dest_iter++)
			{
				tmp_list.push_back(*dest_iter);
			}
		for (dest_iter = tmp_list.begin();
			 dest_iter != tmp_list.end();
			 dest_iter++)
			{
				add_component_to_components(*dest_iter);
			}
		server_ctrl_->Refresh();
		server_ctrl_->Expand(rootId);
		component_list_->Refresh();
		component_list_->Expand(rootId2);
	}
	
}
void DescriptorFrame::OnSave_as(wxCommandEvent& WXUNUSED(event))
{
	wxString path;
	wxFileDialog* file_dialog=new wxFileDialog(this,"Choose a file or enter a name","","","*.zip",wxSAVE,wxDefaultPosition);
	int t=file_dialog->ShowModal();
	if (t==wxID_OK)
	{	
		// copy old file to new 
		path=file_dialog->GetPath();
		if (!(wxCopyFile(file.c_str(),path,TRUE))) 
		{
			wxString message="Writing error ";
			message.Append(path);
			wxLogMessage(message);
		} else {
			file=path.c_str();
			file_text->SetLabel(this->file.c_str() );
			save();
		}
	}
	file_dialog->~wxFileDialog();
	
	
	


}


void DescriptorFrame::OnSave_Settings(wxCommandEvent& WXUNUSED(event))
{
	save();
}

void DescriptorFrame::save()
{
	bool empty=true;
	FILE *cadfile_;
	FILE *outputfile;
	char line[100];
	

	// check unbound components
	if (!(noDestinationInfoList.size()==0)) {
		empty=false;
		wxString message="placements without destination are left. Continue ?";
		wxMessageDialog* mess_dialog=new wxMessageDialog(this,message,"Message box",wxYES_NO | wxCENTRE | wxICON_QUESTION, wxDefaultPosition);
		int t=mess_dialog->ShowModal();
		if (t==wxID_YES)
		{
			empty=true;
		}
		mess_dialog->~wxMessageDialog();
	}


	cadfile_=fopen(tmp_file.c_str(),"r");
	wxString c_file="meta-inf/";
	c_file.Append(cadfile.c_str());
	outputfile=fopen(c_file,"w+");
		
	wxString tmp_string;
	wxString tmp_before_partit;
	wxString tmp_after_partit;
	wxString tmp_partit;

	// reading the cadfile 
	while (!feof(cadfile_))
	{
		fgets(line,100,cadfile_);
		tmp_string.Append(line);
	}

	// erase old partitioning
	// divide into two strings
	
	int erase_start=tmp_string.find("<partitioning>");
	int erase_end=tmp_string.find("</partitioning>")+15;

	tmp_before_partit=tmp_string.Mid(0,erase_start);
	tmp_after_partit=tmp_string.Mid(erase_end,wxSTRING_MAXLEN);
	tmp_partit=tmp_string.Mid(erase_start,erase_end-erase_start);
	

	tmp_string.Empty();

	// put new partitioning 
	tmp_string.Append(tmp_before_partit);
	tmp_string.Append(get_partitioning_str(tmp_partit));
	tmp_string.Append(tmp_after_partit);

	// write into cad file
	if (fputs(tmp_string ,outputfile) > -1) 
	{ 
		//wxLogMessage(_T(line));

	} else {
		wxLogMessage(_T("Error writing"));		
	}
	
	fclose(outputfile);
	fclose(cadfile_);

    // cadfile into assembly zip
	into_zip(c_file.c_str(),file);

	// delete tmp_cadfile

    wxLogMessage("Save OK");

}


wxString DescriptorFrame::get_partitioning_str(wxString partit)
{
	wxString tmp_string;

	tmp_string.Append("<partitioning>\n");
	tmp_string.Append(edit_partit(partit));
	tmp_string.Append(get_noDestination_str());
	tmp_string.Append(get_Destination_str());
		
	tmp_string.Append("</partitioning>\n");
	return tmp_string;
	
}


wxString DescriptorFrame::edit_partit(wxString partit)
{
	
	int erase_s=partit.Replace("<partitioning>","");
	int erase_e=partit.Replace("</partitioning>","");


	int erase_start=partit.find("<hostcollocation>");
		while (erase_start>0)
		{
			erase_start=partit.find("<hostcollocation>");
			int erase_end=partit.find("</hostcollocation>")+18;
			if (erase_end>18) 
			{
				partit.Remove(erase_start,erase_end-erase_start);
			}

		} 

		

	erase_start=0;
	erase_start=partit.find("<processcollocation");
		while (erase_start>0)
		{
			erase_start=partit.find("<processcollocation");
			int erase_end=partit.find("</processcollocation>")+21;

			if (erase_end>21)
			{
				partit.Remove(erase_start,erase_end-erase_start);
			}
			
		}	

		
	erase_start=0;
	erase_start=partit.find("<homeplacement");
		while (erase_start>0)
		{
			erase_start=1;
			erase_start=partit.find("<homeplacement");
			int erase_end=partit.find("</homeplacement>")+16;
			if (erase_end>16)
			{
				partit.Remove(erase_start,erase_end-erase_start);
			}
						
		}
		
	
	return partit;

}


wxString DescriptorFrame::get_Destination_str()
{
	wxString tmp_string;
	std::vector <DestinationInfo> ::iterator dest_iter;

	for(dest_iter = DestinationInfoList.begin(); 
		dest_iter != DestinationInfoList.end();
		dest_iter++)
		{
			if ((*dest_iter).typ==homeplacement) 
			{
				tmp_string.Append(get_homeplacement_str_d(*dest_iter));
			}
			if ((*dest_iter).typ==hostcollocation)
			{
				tmp_string.Append(get_hostcollocation_str_d(*dest_iter));
			}
			if ((*dest_iter).typ==processcollocation)
			{
				tmp_string.Append(get_processcollocation_str_d(*dest_iter));
			}
		}



	return tmp_string;

}

wxString DescriptorFrame::get_noDestination_str()
{
	wxString tmp_string;
	std::vector <noDestinationInfo> ::iterator nodest_iter;

	for(nodest_iter = noDestinationInfoList.begin(); 
		nodest_iter != noDestinationInfoList.end();
		nodest_iter++)
		{
			if ((*nodest_iter).typ==homeplacement) 
			{
				tmp_string.Append(get_homeplacement_str(*nodest_iter));
			}
			if ((*nodest_iter).typ==hostcollocation)
			{
				tmp_string.Append(get_hostcollocation_str(*nodest_iter));
			}
			if ((*nodest_iter).typ==processcollocation)
			{
				tmp_string.Append(get_processcollocation_str(*nodest_iter));
			}
		}



	return tmp_string;
}


wxString DescriptorFrame::get_homeplacement_str(noDestinationInfo noDestInfo)
{
	
	wxString tmp_string;
	wxString node="NODESTINFO_110878";
	
	std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
	int itercounter=0;
	for(home_iter = homedatas.begin(); 
		home_iter != homedatas.end();
		home_iter++)
		{
			if (noDestInfo.iter==itercounter)
			{
				tmp_string=get_homeplacement_text(*home_iter,node);

			}
			itercounter++;
		}
	
	
	return tmp_string;
}

wxString DescriptorFrame::get_homeplacement_str_d(DestinationInfo DestInfo)
{
	
	wxString tmp_string;
	wxString node=DestInfo.node;
	
	
	std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
	int itercounter=0;
	for(home_iter = homedatas.begin(); 
		home_iter != homedatas.end();
		home_iter++)
		{
			if (DestInfo.iter==itercounter)
			{
				tmp_string=get_homeplacement_text(*home_iter,node);

			}
			itercounter++;
		}
	
	
	return tmp_string;
}

wxString DescriptorFrame::get_processcollocation_str(noDestinationInfo noDestInfo)
{
	wxString tmp_string;
	wxString node="NODESTINFO_110878";
	
	std::vector <Qedo::ProcessData> ::iterator process_iter;
	int itercounter=0;
	for(process_iter = processdatas.begin(); 
		process_iter != processdatas.end();
		process_iter++)
		{
			if (noDestInfo.iter==itercounter)
			{
				tmp_string=get_processcollocation_text(*process_iter,node);

			}
			itercounter++;
		}
	
	
	return tmp_string;

}

wxString DescriptorFrame::get_processcollocation_str_d(DestinationInfo DestInfo)
{
	wxString tmp_string;
	wxString node=DestInfo.node;
	
	std::vector <Qedo::ProcessData> ::iterator process_iter;
	int itercounter=0;
	for(process_iter = processdatas.begin(); 
		process_iter != processdatas.end();
		process_iter++)
		{
			if (DestInfo.iter==itercounter)
			{
				tmp_string=get_processcollocation_text(*process_iter,node);

			}
			itercounter++;
		}
	
	
	return tmp_string;

}

wxString DescriptorFrame::get_hostcollocation_str(noDestinationInfo noDestInfo)
{

	wxString tmp_string;
	wxString node="NODESTINFO_110878";
	
	std::vector <Qedo::HostData> ::iterator host_iter;
	int itercounter=0;
	for(host_iter = hostdatas.begin(); 
		host_iter != hostdatas.end();
		host_iter++)
		{
			if (noDestInfo.iter==itercounter)
			{
				tmp_string=get_hostcollocation_text(*host_iter,node);

			}
			itercounter++;
		}
	
	
	return tmp_string;
}

wxString DescriptorFrame::get_hostcollocation_str_d(DestinationInfo DestInfo)
{
	wxString tmp_string;
	wxString node=DestInfo.node;
	
	std::vector <Qedo::HostData> ::iterator host_iter;
	int itercounter=0;
	for(host_iter = hostdatas.begin(); 
		host_iter != hostdatas.end();
		host_iter++)
		{
			if (DestInfo.iter==itercounter)
			{
				tmp_string=get_hostcollocation_text(*host_iter,node);

			}
			itercounter++;
		}
	
	
	return tmp_string;

}



wxString DescriptorFrame::get_homeplacement_text(Qedo::HomeInstanceData home,wxString node)
{
	wxString tmp_string;
	char a='"';

	// Homeplacement id
	tmp_string.Append("\t");
	tmp_string.Append("<homeplacement id=");
	tmp_string.Append(a);
	tmp_string.Append(home.id.c_str());
	tmp_string.Append(a);

	// cardinality		
	if (!home.cardinality==-1) 
	{
		tmp_string.Append(" cardinality="); 
		tmp_string.Append(a);
		tmp_string.Append(home.cardinality);
		tmp_string.Append(a);
		tmp_string.Append(">\n");
	} else {
		tmp_string.Append(">\n");
	}
				
	// usagename
	if(!home.usage_name.empty())
	{
		tmp_string.Append(usagename(home.usage_name.c_str()));
		
	}

	// componentfileref
	if (!home.file.empty())
	{
		tmp_string.Append("\t \t");
		tmp_string.Append("<componentfileref idref=");
		tmp_string.Append(a);
		tmp_string.Append(home.file.c_str());
		tmp_string.Append(a);
		tmp_string.Append("/> \n");
	}

	// componentimplref
	if (!home.impl_id.empty())
	{
		tmp_string.Append("\t \t");
		tmp_string.Append("<componentimplref idref=");
		tmp_string.Append(a);
		tmp_string.Append(home.impl_id.c_str());
		tmp_string.Append(a);
		tmp_string.Append("/> \n");
	}

	// homeproperties
	// !!!! only filename is present. CADReader have to extending
	if (!home.home_prop.empty())
	{
		tmp_string.Append("\t \t");
		tmp_string.Append("<homeproperties>\n");
		tmp_string.Append("\t \t \t <fileinarchive name=");
		tmp_string.Append(a);
		tmp_string.Append(home.home_prop.c_str());
		tmp_string.Append(a);
		tmp_string.Append("> \n ");
		tmp_string.Append("\t \t \t </fileinarchive> \n");
		tmp_string.Append("\t \t </homeproperties>\n");
	}

	//componentproperties
	if (!home.comp_prop.empty())
	{
		tmp_string.Append(componentproperties(home.comp_prop.c_str()));
	}

	// registerwithhomefinder
	if (!home.finder.empty())
	{
		tmp_string.Append("\t \t");
		tmp_string.Append("<registerwithnaming name=");
		tmp_string.Append(a);
		tmp_string.Append(home.finder.c_str());
		tmp_string.Append(a);
		tmp_string.Append("/> \n ");

	}

	// registerwithnaming
	if (!home.naming.empty())
	{
		tmp_string.Append(registerwithnaming(home.naming.c_str()));
	}

	// registerwithtrader
	if (!home.trader.empty())
	{
		tmp_string.Append("\t \t");
		tmp_string.Append("<registerwithtrader tradername=");
		tmp_string.Append(a);
		tmp_string.Append(home.trader.c_str());
		tmp_string.Append(a);
		tmp_string.Append("/> \n"); 
	}

	// componentinstantiation
	std::vector < Qedo::ComponentInstanceData >::iterator InstanceData;
	
	for(InstanceData =home.instances.begin(); 
		InstanceData != home.instances.end();
		InstanceData++)
		{
			// componentinstantiation

			// id
			tmp_string.Append("\t \t<componentinstantiation id=");
			tmp_string.Append(a);
			tmp_string.Append((*InstanceData).id.c_str());
			tmp_string.Append(a);
			tmp_string.Append(">\n");
			
			// usagename
			if (!((*InstanceData).usage_name.empty())) 
			{
				tmp_string.Append(usagename((*InstanceData).usage_name.c_str()));
			}
			
			// componentproperties
			if (!((*InstanceData).comp_prop.empty()))
			{
				tmp_string.Append(componentproperties((*InstanceData).comp_prop.c_str()));
			}			

			// registercomponent
			std::vector< Qedo::NamingRegistrationData > ::iterator naming_reg;
			for(naming_reg =(*InstanceData).naming_registrations.begin(); 
				naming_reg != (*InstanceData).naming_registrations.end();
				naming_reg++)
				{
					tmp_string.Append("\t \t <registercomponent>\n");
					if ((*naming_reg).port_kind==Qedo::PortKind(2))
					{
						tmp_string.Append("\t \t \t");
						tmp_string.Append("<emitsidentifier>");
						tmp_string.Append((*naming_reg).port.c_str());
						tmp_string.Append("</emitsidentifier> \n");
					}

					if ((*naming_reg).port_kind==Qedo::PortKind(1))
					{
						tmp_string.Append("\t \t \t");
						tmp_string.Append("<providesidentifier>");
						tmp_string.Append((*naming_reg).port.c_str());
						tmp_string.Append("</providesidentifier>");
					}

					if ((*naming_reg).port_kind==Qedo::PortKind(3))
					{
						tmp_string.Append("\t \t \t");
						tmp_string.Append("<publishesidentifier>");
						tmp_string.Append((*naming_reg).port.c_str());
						tmp_string.Append("</publishesidentifier>");
					}

					// register with naming
					if (!((*naming_reg).name.empty())) 
					{
						tmp_string.Append(registerwithnaming((*naming_reg).name.c_str()));
					}
					tmp_string.Append("\t \t </registercomponent>\n");
				} // end registercomponents

			// rules
		    if (!((*InstanceData).rules.empty()))
			{
				tmp_string.Append(rules((*InstanceData).rules));
			}

			// extension not in ComponentInstanceData
			
		tmp_string.Append("\t \t</componentinstantiation>\n");
		} // end componentinstantiation
		
	// Destination
	if (!(node=="NODESTINFO_110878"))
	{
		Qedo::DestinationData tmp_dest=home.dest;
		tmp_dest.node=node;
		tmp_string.Append(destination(tmp_dest));
	}

	// rules
	if (!(home.rules.empty())) 
	{
		tmp_string.Append(rules(home.rules));

	}

	tmp_string.Append("\t</homeplacement>\n \n");
	return tmp_string;
}

wxString DescriptorFrame::get_hostcollocation_text(Qedo::HostData host,wxString node)
{
	wxString tmp_string;
	char a='"';

	// hostcollocation id
	if (!(host.id.empty())) 
	{
		tmp_string.Append("\t");
		tmp_string.Append("<hostcollocation id=");
		tmp_string.Append(a);
		tmp_string.Append(host.id.c_str());
		tmp_string.Append(a);
		tmp_string.Append(">\n");
	} else {
		tmp_string.Append("\t<hostcollcation>\n");
	}

	// usagename
	if(!host.usage_name.empty())
	{
		tmp_string.Append(usagename(host.usage_name.c_str()));
		
	}

	// processcollocation
	std::vector <Qedo::ProcessData> ::iterator process_iter;
	for(process_iter = host.processes.begin(); 
		process_iter != host.processes.end();
		process_iter++)
		{
			tmp_string.Append(get_processcollocation_text(*process_iter,"NODESTINFO_110878"));
		}


	// destination
	if (!(node=="NODESTINFO_110878"))
	{
		Qedo::DestinationData tmp_dest=host.dest;
		tmp_dest.node=node;
		tmp_string.Append(destination(tmp_dest));
	}

	tmp_string.Append("\t </hostcollocation>\n \n");

	return tmp_string;

}

wxString DescriptorFrame::get_processcollocation_text(Qedo::ProcessData process,wxString node)
{
	wxString tmp_string;
	char a='"';

	
	// processcollocation id
	if (!(process.id.empty())) 
	{
		tmp_string.Append("\t");
		tmp_string.Append("<processcollocation id=");
		tmp_string.Append(a);
		tmp_string.Append(process.id.c_str());
		tmp_string.Append(a);
		tmp_string.Append(">\n");
	} else {
							
		tmp_string.Append("\t<processcollocation>\n");
	}
	
	// usagename
	if(!process.usage_name.empty())
	{
		tmp_string.Append(usagename(process.usage_name.c_str()));
		
	}

	// homeplacements
	std::vector <Qedo::HomeInstanceData> ::iterator home_iter;
	for(home_iter = process.homes.begin(); 
		home_iter != process.homes.end();
		home_iter++)
		{
			tmp_string.Append(get_homeplacement_text(*home_iter,"NODESTINFO_110878"));
		}
	
	// destination
	if (!(node=="NODESTINFO_110878"))
	{
		Qedo::DestinationData tmp_dest=process.dest;
		tmp_dest.node=node;
		tmp_string.Append(destination(tmp_dest));
	}

	tmp_string.Append("\t </processcollocation>\n \n");

	return tmp_string;
}

wxString DescriptorFrame::componentproperties(wxString comp_prop)
{
	wxString tmp_string;
	char a='"';

	tmp_string.Append("\t \t");
	tmp_string.Append("<componentproperties>\n");
	tmp_string.Append("\t \t \t <fileinarchive name=");
	tmp_string.Append(a);
	tmp_string.Append(comp_prop);
	tmp_string.Append(a);
	tmp_string.Append("> \n ");
	tmp_string.Append("\t \t \t </fileinarchive> \n");
	tmp_string.Append("\t \t </componentproperties>\n");

	return tmp_string;

}

wxString DescriptorFrame::destination(Qedo::DestinationData dest)
{	
	wxString tmp_string;
	char a='"';

	tmp_string.Append("\t \t");
	tmp_string.Append("<destination> \n");
	tmp_string.Append("\t \t \t <node name=");
	tmp_string.Append(a);
	tmp_string.Append(dest.node.c_str());
	tmp_string.Append(a);
	tmp_string.Append("/> \n");
	tmp_string.Append("\t \t");
	tmp_string.Append("</destination> \n");

	return tmp_string;

}

wxString DescriptorFrame::registerwithnaming(wxString naming)
{
	wxString tmp_string;
	char a='"';

	tmp_string.Append("\t \t");
	tmp_string.Append("<registerwithnaming name=");
	tmp_string.Append(a);
	tmp_string.Append(naming);
	tmp_string.Append(a);
	tmp_string.Append("/> \n");

	return tmp_string;
}

wxString DescriptorFrame::rules(std::vector<Qedo::RuleData> rules)
{
	wxString tmp_string;
	char a='"';
	
	std::vector< Qedo::RuleData > ::iterator rule_iter;
			for(rule_iter =rules.begin(); 
				rule_iter != rules.end();
				rule_iter++)
				{
					// rule name
					tmp_string.Append("\t \t");
					tmp_string.Append("<rule name=");
					tmp_string.Append(a);
					tmp_string.Append((*rule_iter).name.c_str());
					tmp_string.Append(a);

					// rule interval
					if ((*rule_iter).interval>0)
					{
						tmp_string.Append(" interval=");
						tmp_string.Append(a);
						tmp_string.Append(">\n");
					} else {
						tmp_string.Append(">\n");
					}

					// condition
					if (!((*rule_iter).condition.language.empty()))
					{
						tmp_string.Append("\t \t \t");
						tmp_string.Append("<condition language=");
						tmp_string.Append(a);
						tmp_string.Append((*rule_iter).condition.language.c_str());
						tmp_string.Append(a);
						tmp_string.Append(">\n");
						tmp_string.Append("\t \t \t \t");
						tmp_string.Append("<scriptcode>");
						tmp_string.Append((*rule_iter).condition.code.c_str());
						tmp_string.Append("</scriptcoder>\n");
						tmp_string.Append("\t \t \t");
						tmp_string.Append("</condition>\n");
					}

					// action
					if (!((*rule_iter).action.language.empty()))
					{
						tmp_string.Append("\t \t \t");
						tmp_string.Append("<action language=");
						tmp_string.Append(a);
						tmp_string.Append((*rule_iter).action.language.c_str());
						tmp_string.Append(a);
						tmp_string.Append("\t \t \t \t");
						tmp_string.Append("<scriptcode>");
						tmp_string.Append((*rule_iter).action.code.c_str());
						tmp_string.Append("</scriptcoder>\n");
						tmp_string.Append("\t \t \t");
						tmp_string.Append("</action>\n");
					}
			tmp_string.Append("\t \t </rule>");
			} // end rules

	return tmp_string;
}

wxString DescriptorFrame::usagename(wxString usagename)
{
	wxString tmp_string;

	tmp_string.Append("\t \t");
	tmp_string.Append("<usagename>");
	tmp_string.Append(usagename);
	tmp_string.Append("</usagename>\n");

	return tmp_string;
}
