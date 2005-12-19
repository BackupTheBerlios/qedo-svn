/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
/*                                                                         */
/* Copyright (C) 2002-2005 by the Qedo Team                                */
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


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/choicdlg.h"

#include "ConnectionTreeCtrl.h"
#include "PartitioningTreeCtrl.h"
#include "CCDReader4qxml.h"
#include "CCDStruc4qxml.h"
#include "ConfigurationReader.h"
#include "ConnectionDialog.h"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"

extern std::string Qedo::g_qedo_dir;

BEGIN_EVENT_TABLE( ConnectionTreeCtrl, wxTreeCtrl )
	EVT_RIGHT_DOWN(ConnectionTreeCtrl::OnItem)
	EVT_MENU(ID_MENU_ADD_C_B,ConnectionTreeCtrl::onadd_b)
	EVT_MENU(ID_MENU_ADD_C_C,ConnectionTreeCtrl::onadd_c)
	EVT_MENU(ID_MENU_ADD_C_E,ConnectionTreeCtrl::onadd_e)
	EVT_MENU(ID_MENU_ADD_C_NS,ConnectionTreeCtrl::onadd_ns)
END_EVENT_TABLE()

ConnectionTreeCtrl::ConnectionTreeCtrl()
{
}

ConnectionTreeCtrl::ConnectionTreeCtrl( wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style): wxTreeCtrl(parent, id, pos, size, style)
{
	CreateImageList(16);
	 this->AddRoot(wxT("Connections"),TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
	Show();
	//
	// get the qedo dir
	//
	Qedo::g_qedo_dir = Qedo::getEnvironment( "QEDO" );
	if(Qedo::g_qedo_dir == "")
	{
	    std::cout << "Missing Environment Variable QEDO" << std::endl;
	    Qedo::g_qedo_dir = Qedo::getCurrentDirectory();
	}
	std::cout << "..... Qedo directory is " << Qedo::g_qedo_dir << std::endl;


	// get temporal directory
	m_temp_path = Qedo::ConfigurationReader::instance()->lookup_config_value ("General/TempDir");

	if ( m_temp_path.empty() )
	{
		m_temp_path =  Qedo::g_qedo_dir + "/qedo_temp" ;
	}
	m_temp_path += "/";

}

void ConnectionTreeCtrl::CreateImageList(int size)
{
    if ( size == -1 )
    {
        SetImageList(NULL);
        return;
    }
    if ( size == 0 )
        size = m_imageSize;
    else
        m_imageSize = size;

    // Make an image list containing small icons
    wxImageList *images = new wxImageList(size, size, TRUE);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[5];
    icons[0] = wxIcon(icon1_xpm);
    icons[1] = wxIcon(icon2_xpm);
    icons[2] = wxIcon(icon3_xpm);
    icons[3] = wxIcon(icon4_xpm);
    icons[4] = wxIcon(icon5_xpm);

    int sizeOrig = icons[0].GetWidth();
    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    {
        if ( size == sizeOrig )
        {
            images->Add(icons[i]);
        }
        else
        {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignImageList(images);
}

void ConnectionTreeCtrl::OnItem(wxMouseEvent& event) 
{
	CreateImageList(16);
	if (!(this->GetItemText(this->GetSelection()).empty())) 
	{
		if (this->GetSelection()!=this->GetRootItem())
		{
			wxTreeItemId compid = get_CompId(GetSelection());
			
			
			wxMenu *test = new wxMenu("Connections",2);
			//test->SetTitle("ComponentPackage");
			wxString text="Edit ";
			text.Append(GetItemText(compid));
		//	test->Append(ID_MENU_EDIT,text,"edit the ComponentID",TRUE);

			/*if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}*/
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE_C,"delete this Connection","delete this Connection",TRUE);
	
			this->PopupMenu(test,event.GetPosition());
			
		}
		if (this->GetSelection()==this->GetRootItem())
		{
			std::vector <PartitioningTreeCtrl::Comp> components=PTreeCtrl->get_Comp4Con();
			if (components.size()>0) {
			wxMenu *onlyRoot = new wxMenu("ComponentPackage",2);
			onlyRoot->Append(ID_MENU_ADD_C_E,"Add new Event connection","add new Event connection",TRUE);
			onlyRoot->Append(ID_MENU_ADD_C_C,"Add new Interface connection","add new Interface connection",TRUE);
			onlyRoot->Append(ID_MENU_ADD_C_B,"Add new Stream connection","add new Stream connection",TRUE);
			onlyRoot->Append(ID_MENU_ADD_C_NS,"Add new NameService connection","add new NameService connection",TRUE);

			get_portinformation(components);
			if (!(isEvent(components))) {
				onlyRoot->Enable(ID_MENU_ADD_C_E,FALSE);
			}
			if (!(isStream(components))) {
				onlyRoot->Enable(ID_MENU_ADD_C_B,FALSE);
			}
			if (!(isInterface(components))) {
				onlyRoot->Enable(ID_MENU_ADD_C_C,FALSE);
			}

			if (!(isReceptacle(components))) {
				onlyRoot->Enable(ID_MENU_ADD_C_NS,FALSE);
			}

			//			componentlist=components;
			this->PopupMenu(onlyRoot,event.GetPosition());
			}
			
		}
		
	}
} 

void 
ConnectionTreeCtrl::get_portinformation(std::vector <PartitioningTreeCtrl::Comp> components)
{  
	cports.clear();
	// get information of ports
	std::vector <PartitioningTreeCtrl::Comp> ::iterator iter;
	for(iter = components.begin(); 
		iter != components.end(); 
			iter++)
			{
				PartitioningTreeCtrl::Comp tempc=(*iter);
				ConnectionTreeCtrl::CPort cport;
				cport.idref=tempc.idref;
				cport.instantiations=tempc.instantiations;
				
				std::string package_;
				std::string ccdfile_name;
				package_=""; 
				wxString tmp_string;
				std::string path=tempc.file_archive.c_str();
				tmp_string=tempc.link.c_str();
				tmp_string.Replace ("\\","/");
	
				package_.append(tmp_string.c_str() );
		
				Qedo::Package *package = new Qedo::Package(package_);
		
				ccdfile_name = package->getFileNameWithSuffix( ".ccd" );
			
				Qedo::CCDReader4qxml *ccdreader = 
					new Qedo::CCDReader4qxml(package_,m_temp_path.c_str());
				cport.ccddata = ccdreader->getCCD();

				
				cports.push_back(cport);

			}
}



wxTreeItemId ConnectionTreeCtrl::get_CompId(wxTreeItemId itemid)
{ /* returns the ItemId of the ComponentPackage */
 
	
	while (GetItemParent(itemid)!=GetRootItem())
	{
		itemid=GetItemParent(itemid);
		
	}

	return itemid;

}


void 
ConnectionTreeCtrl::setdummy(PartitioningTreeCtrl* ptc)
{
	PTreeCtrl = ptc;
}



bool 
ConnectionTreeCtrl::isEvent(std::vector <PartitioningTreeCtrl::Comp> components)
{
	bool value=false;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::consumesport) 
					{
						value=true;
						break;
					}
					if (ccdport.type==Qedo::publishesport)
					{
						value=true;
						break;
					}
				}
			}
	return value;
}

bool ConnectionTreeCtrl::isStream
		(std::vector <PartitioningTreeCtrl::Comp> components)
{
	bool value=false;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::sinkport) 
					{
						value=true;
						break;
					}
					if (ccdport.type==Qedo::sourceport)
					{
						value=true;
						break;
					}
				}
			}
	return value;
}

bool ConnectionTreeCtrl::isInterface
		(std::vector <PartitioningTreeCtrl::Comp> components)
{
	bool value=false;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::usesport ) 
					{
						value=true;
						break;
					}
					if (ccdport.type==Qedo::providesport)
					{
						value=true;
						break;
					}
				}
			}
	return value;
}

bool 
ConnectionTreeCtrl::isReceptacle(std::vector <PartitioningTreeCtrl::Comp> components)
{
	bool value=false;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::usesport ) 
					{
						value=true;
						break;
					}
				}
			}
	return value;
}

void ConnectionTreeCtrl::onadd_b(wxCommandEvent& event)
{   
	ConnectionDialog *cdialog = new ConnectionDialog(this,-1,
		"Streamport Binding",wxPoint(50,50), wxSize(450,350),wxDEFAULT_DIALOG_STYLE);
	cdialog->headline->SetLabel("Choose streamports for binding");
	cdialog->setPorts1(getSourceports());
	cdialog->setPorts2(getSinkports());

	cdialog->Show();
	
	if (cdialog->ShowModal() == wxID_OK)
    {
		wxString port1=cdialog->port1;
		wxString port2=cdialog->port2;
		int mid=port1.Find("::");      

		wxString inst1=port1.SubString(0,mid-1);
		wxString portname1=port1.SubString(mid+2,port1.Len());
		wxString inst2=port2.SubString(0,mid-1);
		wxString portname2=port2.SubString(mid+2,port2.Len());

		wxString binding="Binding ";
		binding.Append(inst1);
		binding.Append("-");
		binding.Append(inst2);
		wxTreeItemId itemid=AppendItem(GetRootItem(),binding,TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
		
		ConPort p1;
		p1.idref=inst1;
		p1.portname=portname1;
		ConPort p2;
		p2.idref=inst2;
		p2.portname=portname2;
		// SOURCEPORT
		wxTreeItemId bindingid=AppendItem(itemid,"Sourceport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		wxString text="Port: ";
		text.Append(portname1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);

		// SINKPORT
		bindingid=AppendItem(itemid,"Sinkport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		text="Port: ";
		text.Append(portname2);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst2);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		Connect c;
		c.port1=p1;
		c.port2=p2;

		connections.bindings.push_back(c);

		
    }
    cdialog->Destroy();
    //return true;
    
}

void ConnectionTreeCtrl::onadd_c(wxCommandEvent& event)
{   
	ConnectionDialog *cdialog = new ConnectionDialog(this,-1,
		"Port connection",wxPoint(50,50), wxSize(450,350),wxDEFAULT_DIALOG_STYLE,"Receptacles","Facets");
	cdialog->headline->SetLabel("Choose ports for connections");
	
	cdialog->setPorts1(getUseports());
	cdialog->setPorts2(getProvideports());

	cdialog->Show();
	
	if (cdialog->ShowModal() == wxID_OK)
    {
		wxString port1=cdialog->port1;
		wxString port2=cdialog->port2;
		int mid=port1.Find("::");      
		int mid2=port2.Find("::");

		wxString inst1=port1.SubString(0,mid-1);
		wxString portname1=port1.SubString(mid+2,port1.Len());
		wxString inst2=port2.SubString(0,mid2-1);
		wxString portname2=port2.SubString(mid2+2,port2.Len());

		wxString binding="Connectinterface ";
		binding.Append(inst1);
		binding.Append("-");
		binding.Append(inst2);
		wxTreeItemId itemid=AppendItem(GetRootItem(),binding,TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
		
		ConPort p1;
		p1.idref=inst1;
		p1.portname=portname1;
		ConPort p2;
		p2.idref=inst2;
		p2.portname=portname2;
		// PROVIDEPORT
		wxTreeItemId bindingid=AppendItem(itemid,"Provideport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		wxString text="Port: ";
		text.Append(portname1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);

		// SINKPORT
		bindingid=AppendItem(itemid,"Useport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		text="Port: ";
		text.Append(portname2);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst2);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		Connect c;
		c.port1=p1;
		c.port2=p2;

		connections.interfaces.push_back(c);

		
    }
    cdialog->Destroy();
    //return true;
    
}


void ConnectionTreeCtrl::onadd_e(wxCommandEvent& event)
{   
	ConnectionDialog *cdialog = new ConnectionDialog(this,-1,
		"Port connection",wxPoint(50,50), wxSize(450,350),wxDEFAULT_DIALOG_STYLE,"Publishports","Consumeports");
	cdialog->headline->SetLabel("Choose ports for connections");
	
	cdialog->setPorts1(getPublishports());
	cdialog->setPorts2(getConsumeports());

	cdialog->Show();
	
	if (cdialog->ShowModal() == wxID_OK)
    {
		wxString port1=cdialog->port1;
		wxString port2=cdialog->port2;
		int mid=port1.Find("::");      

		wxString inst1=port1.SubString(0,mid-1);
		wxString portname1=port1.SubString(mid+2,port1.Len());

		mid=port2.Find("::");
		wxString inst2=port2.SubString(0,mid-1);
		wxString portname2=port2.SubString(mid+2,port2.Len());

		wxString binding="Connectevent ";
		binding.Append(inst1);
		binding.Append("-");
		binding.Append(inst2);
		wxTreeItemId itemid=AppendItem(GetRootItem(),binding,TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
		
		ConPort p1;
		p1.idref=inst1;
		p1.portname=portname1;
		ConPort p2;
		p2.idref=inst2;
		p2.portname=portname2;
		// PUBLISHPORT
		wxTreeItemId bindingid=AppendItem(itemid,"Publishport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		wxString text="Port: ";
		text.Append(portname1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);

		// CONSUMEPORT
		bindingid=AppendItem(itemid,"Comsumeport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		text="Port: ";
		text.Append(portname2);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst2);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		Connect c;
		c.port1=p1;
		c.port2=p2;

		connections.events.push_back(c);

		
    }
    cdialog->Destroy();
    //return true;
    
}


void 
ConnectionTreeCtrl::onadd_ns(wxCommandEvent& event)
{   
	// create a wxString array
	// TODO : can be improved with new WxWidgets
	wxArrayString temp_ports = getUseports();
	wxString choices [1000]; 
	for (size_t i=0; i < temp_ports.GetCount(); i++){
        	choices[i] = temp_ports[i];
	}

	//display selction of receptacles
	wxSingleChoiceDialog receptacle_dialog(this, "select a port", "Selection", 1, choices);
	
	receptacle_dialog.Show();
	
	if (receptacle_dialog.ShowModal() == wxID_OK)
    {
		wxString port_name = receptacle_dialog.GetStringSelection();

		// ask for naming context
		wxString ns_context = wxGetTextFromUser("Enter a NameService Context","Context","", this,-1,-1,TRUE);

		int mid=port_name.Find("::");      

		wxString inst1=port_name.SubString(0,mid-1);
		wxString portname1=port_name.SubString(mid+2,port_name.Len());

		wxString binding="Connectinterface ";
		binding.Append(inst1);
		binding.Append("-");
		binding.Append(ns_context);
		wxTreeItemId itemid=AppendItem(GetRootItem(),binding,TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
		
		ConPort p1;
		p1.idref=inst1;
		p1.portname=portname1;

		// PROVIDEPORT
		wxTreeItemId bindingid=AppendItem(itemid,"NS_Reference",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		wxString text="Port: ";
		text.Append(ns_context);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);

		// SINKPORT
		bindingid=AppendItem(itemid,"Useport",TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, NULL);
		text="Port: ";
		text.Append(portname1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		text="Componentinstantiation: ";
		text.Append(inst1);
		AppendItem(bindingid,text,TreeCtrlIcon_File, TreeCtrlIcon_FileSelected,NULL);
		
		NS_Connect c;
		c.port1=p1;
		c.ns_context=ns_context;

		connections.ns_connections.push_back(c);



	}
}

wxArrayString 
ConnectionTreeCtrl::getSinkports()
{
	wxArrayString stringarray;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type== Qedo::sinkport ) 
					{
						std::vector <PartitioningTreeCtrl::Instantiation>
														::	iterator iiter;
						for(iiter = cport.instantiations.begin(); 
							iiter != cport.instantiations.end(); 
							iiter++)
						{
							PartitioningTreeCtrl::Instantiation inst=(*iiter);
							wxString text=inst.id;
							text.Append("::");
							text.Append(ccdport.identifier.c_str());
                            stringarray.Add(text);
							
						}
						
					}
					
				}
			}
	return stringarray;
}

wxArrayString ConnectionTreeCtrl::getSourceports()
{
	wxArrayString stringarray;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::sourceport ) 
					{
						std::vector <PartitioningTreeCtrl::Instantiation>
														::	iterator iiter;
						for(iiter = cport.instantiations.begin(); 
							iiter != cport.instantiations.end(); 
							iiter++)
						{
							PartitioningTreeCtrl::Instantiation inst=(*iiter);
							wxString text=inst.id;
							text.Append("::");
							text.Append(ccdport.identifier.c_str());
                            stringarray.Add(text);
							
						}
						
					}
					
				}
			}
	return stringarray;
}

wxArrayString ConnectionTreeCtrl::getProvideports()
{
	wxArrayString stringarray;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::providesport ) 
					{
						std::vector <PartitioningTreeCtrl::Instantiation>
														::	iterator iiter;
						for(iiter = cport.instantiations.begin(); 
							iiter != cport.instantiations.end(); 
							iiter++)
						{
							PartitioningTreeCtrl::Instantiation inst=(*iiter);
							wxString text=inst.id;
							text.Append("::");
							text.Append(ccdport.identifier.c_str());
                            stringarray.Add(text);
							
						}
						
					}
					
				}
			}
	return stringarray;
}

wxArrayString ConnectionTreeCtrl::getUseports()
{
	wxArrayString stringarray;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::usesport ) 
					{
						std::vector <PartitioningTreeCtrl::Instantiation>
														::	iterator iiter;
						for(iiter = cport.instantiations.begin(); 
							iiter != cport.instantiations.end(); 
							iiter++)
						{
							PartitioningTreeCtrl::Instantiation inst=(*iiter);
							wxString text=inst.id;
							text.Append("::");
							text.Append(ccdport.identifier.c_str());
                            stringarray.Add(text);
							
						}
						
					}
					
				}
			}
	return stringarray;
}

wxArrayString ConnectionTreeCtrl::getPublishports()
{
	wxArrayString stringarray;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::publishesport ) 
					{
						std::vector <PartitioningTreeCtrl::Instantiation>
														::	iterator iiter;
						for(iiter = cport.instantiations.begin(); 
							iiter != cport.instantiations.end(); 
							iiter++)
						{
							PartitioningTreeCtrl::Instantiation inst=(*iiter);
							wxString text=inst.id;
							text.Append("::");
							text.Append(ccdport.identifier.c_str());
                            stringarray.Add(text);
							
						}
						
					}
					
				}
			}
	return stringarray;
}

wxArrayString ConnectionTreeCtrl::getConsumeports()
{
	wxArrayString stringarray;
	std::vector <ConnectionTreeCtrl::CPort> ::iterator iter;
	for(iter = cports.begin(); 
		iter != cports.end(); 
			iter++)
			{
				ConnectionTreeCtrl::CPort cport=(*iter);
				std::vector < Qedo::CCDPort > :: iterator portiter;
				for(portiter = cport.ccddata.ports.begin(); 
					portiter != cport.ccddata.ports.end(); 
					portiter++)
				{
					
					Qedo::CCDPort ccdport=(*portiter);
					if (ccdport.type==Qedo::consumesport ) 
					{
						std::vector <PartitioningTreeCtrl::Instantiation>
														::	iterator iiter;
						for(iiter = cport.instantiations.begin(); 
							iiter != cport.instantiations.end(); 
							iiter++)
						{
							PartitioningTreeCtrl::Instantiation inst=(*iiter);
							wxString text=inst.id;
							text.Append("::");
							text.Append(ccdport.identifier.c_str());
                            stringarray.Add(text);
							
						}
						
					}
					
				}
			}
	return stringarray;
}

wxString ConnectionTreeCtrl::getCADData()
{
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	std::vector <Connect> ::iterator iter;
	for(iter = connections.bindings.begin(); 
		iter != connections.bindings.end(); 
			iter++)
			{
				value.Append(getConnection((*iter),"BINDING"));

			}
	for(iter = connections.events.begin(); 
		iter != connections.events.end(); 
			iter++)
			{
				value.Append(getConnection((*iter),"EVENT"));

			}
	for(iter = connections.interfaces.begin(); 
		iter != connections.interfaces.end(); 
			iter++)
			{
				value.Append(getConnection((*iter),"INTERFACE"));

			}
	std::vector <NS_Connect> ::iterator ns_iter;
	for(ns_iter = connections.ns_connections.begin(); 
		ns_iter != connections.ns_connections.end(); 
		ns_iter++)
			{
				value.Append(getNSConnection((*ns_iter)));

			}
	return value;
}

wxString ConnectionTreeCtrl::getConnection(Connect c, wxString Typ)
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	wxString port1,port2,port1name,port2name,ctyp;

	if (Typ=="BINDING") {
		ctyp="binding";
		port1="sourceport";
		port2="sinkport";
		port1name="sourceportname";
		port2name="sinkportname";
	}

	if (Typ=="EVENT") {
		ctyp="connectevent";
		port1="publishesport";
		port2="consumesport";
		port1name="publishesidentifier";
		port2name="consumesidentifier";
	}
	
	if (Typ=="INTERFACE") {
		ctyp="connectinterface";

		port1="usesport";
		port2="providesport";
		
		port1name="usesidentifier";
		port2name="providesidentifier";
		
	}

	value.Append(tabtab);
	value.Append("<");
	value.Append(ctyp);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("<");
	value.Append(port1);
	value.Append(">\n");
    value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<");
	value.Append(port1name);
	value.Append(">");
	value.Append(c.port1.portname);
	value.Append("</");
	value.Append(port1name);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<componentinstantiationref idref=");
	value.Append(a);
	value.Append(c.port1.idref);
	value.Append(a);
	value.Append("/>\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("</");
	value.Append(port1);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("<");
	value.Append(port2);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<");
	value.Append(port2name);
	value.Append(">");
	value.Append(c.port2.portname);
	value.Append("</");
	value.Append(port2name);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<componentinstantiationref idref=");
	value.Append(a);
	value.Append(c.port2.idref);
	value.Append(a);
	value.Append("/>\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("</");
	value.Append(port2);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append("</");
	value.Append(ctyp);
	value.Append(">\n");


	return value;
}

wxString 
ConnectionTreeCtrl::getNSConnection(NS_Connect c)
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	wxString port1,port2,port1name,port2name,ctyp;

	ctyp="connectinterface";

	port1="usesport";
	port2="existinginterface";
	
	port1name="usesidentifier";
	port2name="findby";
		
	value.Append(tabtab);
	value.Append("<");
	value.Append(ctyp);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("<");
	value.Append(port1);
	value.Append(">\n");
    value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<");
	value.Append(port1name);
	value.Append(">");
	value.Append(c.port1.portname);
	value.Append("</");
	value.Append(port1name);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<componentinstantiationref idref=");
	value.Append(a);
	value.Append(c.port1.idref);
	value.Append(a);
	value.Append("/>\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("</");
	value.Append(port1);
	value.Append(">\n");


	value.Append(tabtab);
	value.Append(tab);
	value.Append("<");
	value.Append(port2);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append("<findby>\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append(tab);
	value.Append("<namingservice name=\"");
	value.Append(c.ns_context);
	value.Append("\"/>\n");
	value.Append(tabtab);
	value.Append(tabtab);
	value.Append("</findby>\n");
	value.Append(tabtab);
	value.Append(tab);
	value.Append("</");
	value.Append(port2);
	value.Append(">\n");
	value.Append(tabtab);
	value.Append("</");
	value.Append(ctyp);
	value.Append(">\n");


	return value;
}

