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

#include "QCexplorer.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/statbox.h"
#include "explore.h"
#include "QedoExplorer.h"
#include "../qedoutil/qedoutil.h"


#include "component.xpm"
#include "component_selected.xpm"
#include "home.xpm"
#include "home_selected.xpm"
#include "container.xpm"
#include "container_selected.xpm"
#include "component_server.xpm"
#include "component_server_selected.xpm"
#include "node.xpm"
#include "node_selected.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"


//#include "../qedoutil/ConfigurationReader.h"

BEGIN_EVENT_TABLE(QCexplorerTreeCtrl, wxTreeCtrl)
    //EVT_BUTTON(EXPLORER_TREE_REFRESH, QCexplorerTreeCtrl::OnExplorerRefresh)
	//EVT_TREE_BEGIN_RDRAG(ID_ITEM_DOUBLECLICK, QCexplorerTreeCtrl::OnExplorerRefresh)
	//EVT_TREE_ITEM_RIGHT_CLICK(ID_ITEM_RIGHTCLICK, OnItem)
	EVT_RIGHT_DCLICK(QCexplorerTreeCtrl::OnItem)
END_EVENT_TABLE()


QCexplorerTreeCtrl::QCexplorerTreeCtrl(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxTreeCtrl(parent, id, pos, size, wxTR_HIDE_ROOT | wxTR_HAS_BUTTONS )

{
}

QCexplorerTreeCtrl::~QCexplorerTreeCtrl()
{

}
void QCexplorerTreeCtrl::CreateImageList(int size)
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
    wxIcon icons[13];
    icons[0] = wxIcon(component_xpm);
    icons[1] = wxIcon(component_selected_xpm);
    icons[2] = wxIcon(home_xpm);
    icons[3] = wxIcon(home_selected_xpm);
    icons[4] = wxIcon(container_xpm);
    icons[5] = wxIcon(container_selected_xpm);
    icons[6] = wxIcon(component_server_xpm);
    icons[7] = wxIcon(component_server_selected_xpm);
    icons[8] = wxIcon(node_xpm);
    icons[9] = wxIcon(node_selected_xpm);
    icons[10] = wxIcon(icon3_xpm);
    icons[11] = wxIcon(icon4_xpm);
    icons[12] = wxIcon(icon5_xpm);

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


void
QCexplorerTreeCtrl::build_tree()
{

	
	CreateImageList();
	int dummy=0;
	try {
	    CORBA::ORB_var orb = Qedo::get_created_ORB();
	
		// resolve the naming service
		std::string ns;
		ns=cmd_ns.c_str();
		
		CORBA::Object_var nsobj;
		nsobj = orb -> string_to_object( ns.c_str() );

		if (CORBA::is_nil(nsobj)) {
				//std::cerr << "Cannot resolve NameService" << endl;
				return;
		}
		
		//narrow the root naming context
		CosNaming::NamingContext_var nc=CosNaming::NamingContext::_narrow(nsobj);


		//create a name component
		CosNaming::Name name;
		name.length(2);
		name[0].id=CORBA::string_dup("Qedo");
		name[0].kind=CORBA::string_dup("");
		name[1].id=CORBA::string_dup("ExploreServer");
		name[1].kind=CORBA::string_dup("");

		CORBA::Object_var obj;
		try {
			//resolve the name component with the naming service
			obj=nc->resolve(name);		
		} catch (...)
		{
			return;
		}
		// Narrow
		Explore_var exp = Explore::_narrow(obj);
		ComponentServerActivatorInfoList* CSAIL=exp->explore_qedo();

		if (! (CSAIL -> length()))
		{
			return;
		}
		ComponentServerActivatorInfoList test=CSAIL[0];

	    wxTreeItemId rootId = AddRoot(wxT("ServerActivators"),
                                  TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected,
                                  new QCexplorerTreeItemData(wxT("NIL")));

		CORBA::ULong i = 0;
		for (i=0; i < test.length(); i++)
		{
			wxTreeItemId idParent=rootId;
			ComponentServerActivatorInfo sa = test[i];
			wxString str ;
			str.Printf(wxT("%s"), wxT(sa.host_name.in()));

			wxTreeItemId idServerActivator = AppendItem(idParent, str , TreeCtrlIcon_Node, 
				TreeCtrlIcon_NodeSelected, new QCexplorerTreeItemData(str));

			ComponentServerInfoList csil=sa.my_component_servers;
			
			CORBA::ULong z = 0;
			for (z = 0; z < csil.length(); z++) 
			{	
			
				ComponentServerInfo csi=csil[z];
				wxString str;
				wxString csi_tmp ;
				csi_tmp="ComponentServer ";

				csi_tmp.append(wxString::Format("%u",z));
				csi_tmp.append(" on ");
				csi_tmp.append(csi.host_name.in());
				str.Printf(wxT("%s"),wxT(csi_tmp.c_str()));
			
				wxTreeItemId idComponentServer = AppendItem(idServerActivator, str , TreeCtrlIcon_ComponentServer, 
					TreeCtrlIcon_ComponentServerSelected, new QCexplorerTreeItemData(str));

				ContainerInstanceInfoList ciil=csi.my_containers;

				CORBA::ULong y = 0;
				for (y = 0; y < ciil.length(); y++)
				{
					ContainerInstanceInfo cii = ciil[y];
					wxString str;
					wxString cii_tmp;
					cii_tmp="Container ";
					cii_tmp.append(wxString::Format("%u",y));
					cii_tmp.append(" - ");
					cii_tmp.append(cii.short_name);
					str.Printf(wxT("%s"),wxT(cii_tmp.c_str()));

					wxTreeItemId idContainerInstance = AppendItem(idComponentServer, str , TreeCtrlIcon_Container, 
						TreeCtrlIcon_ContainerSelected, new QCexplorerTreeItemData(str));
				
					HomeInstanceInfoList hiil=cii.my_homes;

					CORBA::ULong a = 0;
					for (a = 0; a < hiil.length(); a++) 
					{
						HomeInstanceInfo hii=hiil[a];
						wxString str;
						str="";
						wxString hii_tmp;
					
						hii_tmp=(hii.short_name);
						str.Printf(wxT("%s"),wxT(hii_tmp.c_str()));

						wxTreeItemId idHomeInstance = AppendItem(idContainerInstance, str , TreeCtrlIcon_Home, 
							TreeCtrlIcon_HomeSelected, new QCexplorerTreeItemData(str));

						ComponentInstanceInfoList coiil=hii.my_components;
						CORBA::ULong b = 0;
						for (b = 0; b < coiil.length(); b++) 
						{
							ComponentInstanceInfo coii=coiil[b];
							wxString str;
							str="";
							wxString coii_tmp;
					
							coii_tmp=(coii.short_name);
							str.Printf(wxT("%s"),wxT(coii_tmp.c_str()));

							wxTreeItemId idComponentInstance = AppendItem(idHomeInstance, str ,  TreeCtrlIcon_Component, TreeCtrlIcon_ComponentSelected,
								new QCexplorerTreeItemData(str));

						}
					}
				}
			}
		}
	
	} catch (const CORBA::SystemException& ex)
	{
		/*
		ex._print(std::cerr);
		cerr << endl;
		cerr << "Uncaught CORBA exception" << endl;
		*/
	}
}



void 
QCexplorerTreeCtrl::OnExplorerRefresh()
{

		this->DeleteAllItems();
		this->build_tree();
		this->Refresh();


};

void QCexplorerTreeCtrl::clear() {
	this->DeleteAllItems();
	this->Refresh();
	
};

void QCexplorerTreeCtrl::OnItem(wxMouseEvent& event) {
	
	wxTreeItemId item=this->GetSelection() ;
	wxString str;
	str=GetItemText(item);

	info_box->Clear();			
	info_box->WriteText(str);
	
}

void QCexplorerTreeCtrl::set_info_box(wxTextCtrl* info_box_ref) {
	info_box=info_box_ref;
};



