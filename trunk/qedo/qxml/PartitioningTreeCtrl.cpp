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
#include "PartitioningTreeCtrl.h"
#include "AComponentTreeCtrl.h"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"

BEGIN_EVENT_TABLE( PartitioningTreeCtrl, wxTreeCtrl )
	EVT_RIGHT_DOWN(PartitioningTreeCtrl::OnItem)
	EVT_MENU(ID_MENU_ADD_P_P,PartitioningTreeCtrl::onadd_p)
	EVT_MENU(ID_MENU_ADD_P_HO,PartitioningTreeCtrl::onadd_ho)
	EVT_MENU(ID_MENU_ADD_P_H,PartitioningTreeCtrl::onadd_h)
	EVT_MENU(ID_MENU_ADD_P_C,PartitioningTreeCtrl::onadd_c)
	EVT_MENU(ID_MENU_ADD_P_C_I,PartitioningTreeCtrl::onadd_ci)
END_EVENT_TABLE()

PartitioningTreeCtrl::PartitioningTreeCtrl()
{
}

PartitioningTreeCtrl::PartitioningTreeCtrl( wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style): wxTreeCtrl(parent, id, pos, size, style)
{
	CreateImageList(16);
	 this->AddRoot(wxT("Partitioning"),TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
	Show();
}

void PartitioningTreeCtrl::CreateImageList(int size)
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

void PartitioningTreeCtrl::OnItem(wxMouseEvent& event) 
{
	CreateImageList(16);
	if (!(this->GetItemText(this->GetSelection()).empty())) 
	{
		if (this->GetSelection()!=this->GetRootItem())
		{

			ElementType etype=GetType(GetSelection());
			
			if (etype==process) {
				wxMenu *test = new wxMenu("Partitioning Processcollocation",2);
			//test->SetTitle("ComponentPackage");
			wxString text="Edit ";
			//text.Append(GetItemText(compid));
			test->Append(ID_MENU_ADD_P_P,"Edit Usagename","edit Usagename",TRUE);
			test->Append(ID_MENU_ADD_P_H,"Add Homeplacement","Add Homeplacement",TRUE);

			/*if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}*/
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE_P,"delete this Processcollocation","delete this Processcollocation",TRUE);
			
	
			this->PopupMenu(test,event.GetPosition());
			}

			if (etype==host) {
				wxMenu *test = new wxMenu("Partitioning Processcollocation",2);
			//test->SetTitle("ComponentPackage");
			wxString text="Edit ";
			//text.Append(GetItemText(compid));
			test->Append(ID_MENU_EDIT_P_U,"Edit Usagename","edit Usagename",TRUE);
			test->Append(ID_MENU_ADD_P_P,"Add Processcollocation","Add Processcollocation",TRUE);

			test->Append(ID_MENU_ADD_P_H,"Add Homeplacement","Add Homeplacement",TRUE);

			/*if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}*/
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE_P,"delete this Hostcollocation","delete this Processcollocation",TRUE);
			
	
			this->PopupMenu(test,event.GetPosition());
			}

			if (etype==home) {

				wxArrayString temp = ACTreeCtrl->get_CompArray();
				
				wxMenu *test = new wxMenu("Partitioning Homeplacement",2);
			//test->SetTitle("ComponentPackage");
			wxString text="Edit ";
			//text.Append(GetItemText(compid));
			test->Append(ID_MENU_EDIT_P_U,"Edit Usagename","edit Usagename",TRUE);
			
			test->Append(ID_MENU_ADD_P_C,"Add Component","Add Component",TRUE);
			if (temp.GetCount() == 0)  {
				test->Enable(ID_MENU_ADD_P_C,FALSE);
			}
			if (this->ExistsComp(GetSelection())) {
				test->Enable(ID_MENU_ADD_P_C,FALSE);
			}
			//test->Append(ID_MENU_ADD_P_H,"Add Homeplacement","Add Homeplacement",TRUE);
	
			/*if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}*/
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE_P,"delete this Homeplacement","delete this Homeplacementcollocation",TRUE);
			
	
			this->PopupMenu(test,event.GetPosition());
			}

			if (etype==comp) {
				wxMenu *test = new wxMenu("Partitioning Component",2);
			//test->SetTitle("ComponentPackage");
			wxString text="Edit ";
			//text.Append(GetItemText(compid));
			//test->Append(ID_MENU_EDIT_P_U,"Edit Usagename","edit Usagename",TRUE);
			test->Append(ID_MENU_ADD_P_C_I,"Add Instantiation","Add ComponentInstantiation",TRUE);

			//test->Append(ID_MENU_ADD_P_H,"Add Homeplacement","Add Homeplacement",TRUE);

			/*if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}*/
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE_P,"delete this Component","delete this Component",TRUE);
			
	
			this->PopupMenu(test,event.GetPosition());
			}
		}
		if (this->GetSelection()==this->GetRootItem())
		{
			wxMenu *onlyRoot = new wxMenu("Partitioning",2);
			onlyRoot->Append(ID_MENU_ADD_P_P,"Add new Processcollocation","add new Processcollocation",TRUE);
			onlyRoot->Append(ID_MENU_ADD_P_H,"Add new Homeplacement","add new Homeplacement",TRUE);
			onlyRoot->Append(ID_MENU_ADD_P_HO,"Add new Hostcollocation","add new Hostcollocation",TRUE);
			
			
			
			this->PopupMenu(onlyRoot,event.GetPosition());
		}
	}
} 

wxTreeItemId PartitioningTreeCtrl::get_CompId(wxTreeItemId itemid)
{ /* returns the ItemId of the ComponentPackage */
 
	
	while (GetItemParent(itemid)!=GetRootItem())
	{
		itemid=GetItemParent(itemid);
		
	}

	return itemid;

}

void PartitioningTreeCtrl::onadd_p(wxMenuEvent& event)
{
	wxString cid= wxGetTextFromUser("Enter a usagename of processcollocation","Usagename",
	"", this,-1,-1,TRUE);
	wxString text="Processcollocation(";
	text.Append(cid);
	text.Append(")");
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetRootItem());
	Refresh();
	ItemTyp itype;
	itype.itemid=itemid;
	itype.type=process;
	itype.usagename=cid;

	itemtypes.push_back(itype);

}

void PartitioningTreeCtrl::onadd_ho(wxMenuEvent& event)
{
	wxString cid= wxGetTextFromUser("Enter a usagename of hostcollocation","Usagename",
	"", this,-1,-1,TRUE);
	wxString text="Hostcollocation(";
	text.Append(cid);
	text.Append(")");
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetRootItem());
	Refresh();
	ItemTyp itype;
	itype.itemid=itemid;
	itype.type=host;
	itype.usagename=cid;

	itemtypes.push_back(itype);

}

void PartitioningTreeCtrl::onadd_h(wxMenuEvent& event)
{
	wxString cid= wxGetTextFromUser("Enter a usagename of homeplacement","Usagename",
	"", this,-1,-1,TRUE);
	wxString text="Homeplacement(";
	text.Append(cid);
	text.Append(")");
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetRootItem());
	Refresh();
	ItemTyp itype;
	itype.itemid=itemid;
	itype.type=home;
	itype.usagename=cid;

	itemtypes.push_back(itype);

}

void PartitioningTreeCtrl::onadd_c(wxMenuEvent& event)
{
	wxArrayString ac = ACTreeCtrl->get_CompArray();
	
	wxString cid= wxGetSingleChoice("Choose the component",
					"Add Component",ac,this,-1, -1, TRUE,150, 200);
	Qedo::Implementation impl = ACTreeCtrl->get_Implementation(cid);
	
	wxString text="Component(";
	text.Append(cid);
	text.Append(")");
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetSelection());
	Refresh();
	ItemTyp itype;
	itype.itemid=itemid;
	itype.type=comp;

	itemtypes.push_back(itype);

	Comp c;
	c.idref=cid;
	c.impl=impl;
	
	c.link=ACTreeCtrl->getLink(cid);
	c.filearchive=ACTreeCtrl->getFilearchive(cid);
	c.itemid=itemid;
	comps.push_back(c);

}

std::vector <PartitioningTreeCtrl::Comp> PartitioningTreeCtrl::get_Comp4Con()
{
	std::vector <Comp> c;

	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				if (tempc.instantiations.size()>0) {
					c.push_back(tempc);
					
				}
			}

	return c;
}

void PartitioningTreeCtrl::onadd_ci(wxMenuEvent& event)
{

	wxString cid= wxGetTextFromUser("Enter an identifier of instantiation","Identifier",
	"", this,-1,-1,TRUE);
	Comp component=get_Comp(GetSelection());
	wxString text="Instantiation(";
	text.Append(cid);
	text.Append(")");
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetRootItem());
	Refresh();
	ItemTyp itype;
	itype.itemid=itemid;
	itype.type=inst;

	itemtypes.push_back(itype);

	Instantiation i;
	i.id=cid;
	i.itemid=itemid;

	component.instantiations.push_back(i);

	

	replace_component(component);

}



PartitioningTreeCtrl::ElementType PartitioningTreeCtrl::GetType(wxTreeItemId itemid)
{
	ElementType etype;
	std::vector <ItemTyp> ::iterator iter;
	for(iter = itemtypes.begin(); 
		iter != itemtypes.end(); 
			iter++)
			{
				ItemTyp itype=(*iter);
				if (itype.itemid==itemid) {
					etype=itype.type;
					break;
				}
			}

   return etype;
}

PartitioningTreeCtrl::ItemTyp PartitioningTreeCtrl::GetItemInfo(wxTreeItemId itemid)
{
	ItemTyp etype;
	std::vector <ItemTyp> ::iterator iter;
	for(iter = itemtypes.begin(); 
		iter != itemtypes.end(); 
			iter++)
			{
				ItemTyp itype=(*iter);
				if (itype.itemid==itemid) {
					etype=itype;
					break;
				}
			}

   return etype;
}

bool PartitioningTreeCtrl::ExistsComp(wxTreeItemId itemid)
{
	bool value=false;
	std::vector <ItemTyp> ::iterator iter;
	long cookie;
	wxTreeItemId childitem = GetFirstChild(itemid,cookie);

	for(iter = itemtypes.begin(); 
		iter != itemtypes.end(); 
			iter++)
			{
				ItemTyp itype=(*iter);
				if (itype.itemid==childitem) {
					value=true;
					break;
				}
			}
	return value;
}

PartitioningTreeCtrl::Comp PartitioningTreeCtrl::get_Comp(wxTreeItemId itemid)
{
	Comp c;
	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				if (tempc.itemid==itemid) {
					c=tempc;
					break;
				}
			}

   return c;

}

void PartitioningTreeCtrl::replace_component(Comp component)
{
	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				if (tempc.itemid==component.itemid) {
					comps.erase(iter);
					comps.push_back(component);
					break;
				}
			}
}

wxString PartitioningTreeCtrl::getCADData()
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	
	wxTreeItemId root = GetRootItem();
	long cookie;
	wxTreeItemId itemid = GetFirstChild(root,cookie);

	while (!(GetItemText(itemid).IsEmpty())) {
		
		if (GetType(itemid)==host) {
			value.Append(hostdata(itemid));
		}
		if (GetType(itemid)==process) {
			value.Append(processdata(itemid));
		}
		if (GetType(itemid)==home) {
			value.Append(homedata(itemid));
		}
	   
	   itemid=GetNextChild(root,cookie);
	}

	

	return value;
}

wxString PartitioningTreeCtrl::processdata(wxTreeItemId itemid)
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;

	ItemTyp ityp=GetItemInfo(itemid);
	value.Append(tabtab);
	
	value.Append("<processcollocation>\n");
	value.Append(tabtab);
	value.Append("<usagename>");
	value.Append(ityp.usagename);
	value.Append("</usagename>\n");

	long cookie;
	wxTreeItemId childid = GetFirstChild(itemid,cookie);

	while (!(GetItemText(childid).IsEmpty())) {
		
		if (GetType(childid)==home) {
			value.Append(homedata(childid));
		}

		childid=GetNextChild(itemid,cookie);
	}
	value.Append(tabtab);
	value.Append("</processcollocation>\n");
	return value;
}

wxString PartitioningTreeCtrl::homedata(wxTreeItemId itemid)
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	ItemTyp ityp=GetItemInfo(itemid);
	value.Append(tabtab);
	
	value.Append("<homeplacement>\n");
	value.Append(tabtab);
	value.Append("<usagename>");
	value.Append(ityp.usagename);
	value.Append("</usagename>\n");

	long cookie;
	wxTreeItemId childid = GetFirstChild(itemid,cookie);

	while (!(GetItemText(childid).IsEmpty())) {
		
		if (GetType(childid)==comp) {
			value.Append(compdata(childid));
		}

		childid=GetNextChild(itemid,cookie);
	}
	value.Append(tabtab);
	
	value.Append("</homeplacement>\n");
	return value;

}

wxString PartitioningTreeCtrl::hostdata(wxTreeItemId itemid)
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;

	ItemTyp ityp=GetItemInfo(itemid);
	value.Append(tabtab);
	
	value.Append("<hostcollocation>\n");
	value.Append(tabtab);
	value.Append("<usagename>");
	value.Append(ityp.usagename);
	value.Append("</usagename>\n");

	long cookie;
	wxTreeItemId childid = GetFirstChild(itemid,cookie);

	while (!(GetItemText(childid).IsEmpty())) {
		
		if (GetType(childid)==home) {
			value.Append(homedata(childid));
		}
		if (GetType(childid)==process) {
			value.Append(processdata(childid));
		}

		childid=GetNextChild(itemid,cookie);
	}
	value.Append(tabtab);
	value.Append("</hostcollocation>\n");

	return value;

}

wxString PartitioningTreeCtrl::compdata(wxTreeItemId itemid)
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	ItemTyp ityp=GetItemInfo(itemid);
	Comp c = get_Comp(itemid);
	value.Append(tabtab);
	value.Append(tab);
	value.Append("<componentfileref idref=");
	value.Append(a);
	value.Append(c.idref);
	value.Append(a);
	value.Append("/>\n");

	value.Append(tabtab);
	value.Append(tab);
	value.Append("<componentimplref idref=");
	value.Append(a);
	value.Append(c.impl.id.c_str());
	value.Append(a);
	value.Append("/>\n");
	

	std::vector <Instantiation> ::iterator iter;
	for(iter = c.instantiations.begin(); 
		iter != c.instantiations.end(); 
			iter++)
			{
				Instantiation insta=(*iter);
				value.Append(tabtab);
				value.Append(tab);
				value.Append("<componentinstantiation id=");
				value.Append(a);
				value.Append(insta.id);
				value.Append(a);
				value.Append(">\n");
				value.Append(tabtab);
				value.Append(tab);
				value.Append("</componentinstantiation>\n");
			}
	
	return value;

}


void PartitioningTreeCtrl::setdummy(AComponentTreeCtrl* atc)
{
	ACTreeCtrl = atc;
}