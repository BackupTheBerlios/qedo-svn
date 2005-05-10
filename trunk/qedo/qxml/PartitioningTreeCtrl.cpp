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
#include "CCDReader4qxml.h"
#include "ConfigurationReader.h"


#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"

/**
 * qedo namespace
 */
namespace Qedo {

	/** the Qedo directory */
	std::string g_qedo_dir;
};

BEGIN_EVENT_TABLE( PartitioningTreeCtrl, wxTreeCtrl )
	EVT_RIGHT_DOWN(PartitioningTreeCtrl::OnItem)
	EVT_MENU(ID_MENU_ADD_P_P,PartitioningTreeCtrl::onadd_p)
	EVT_MENU(ID_MENU_ADD_P_HO,PartitioningTreeCtrl::onadd_ho)
	EVT_MENU(ID_MENU_ADD_P_H,PartitioningTreeCtrl::onadd_h)
	EVT_MENU(ID_MENU_ADD_P_C,PartitioningTreeCtrl::onadd_c)
	EVT_MENU(ID_MENU_ADD_P_C_I,PartitioningTreeCtrl::onadd_ci)
	EVT_MENU(ID_MENU_ADD_P_H_I,PartitioningTreeCtrl::onadd_if)
	EVT_MENU(ID_MENU_ADD_R_A_N,PartitioningTreeCtrl::onregister_at_name_service)
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
			if (etype==inst) {
				wxMenu* component_instance_menu = new wxMenu("Component Instance",2);

				wxString text="Edit ";
				component_instance_menu->Append(ID_MENU_ADD_P_H_I,"Add Filearchive","Add Filearchive",TRUE);

				component_instance_menu -> AppendSeparator();

				component_instance_menu -> Append (ID_MENU_ADD_R_A_N,"Register at NameService","Register at NameService",TRUE);

				component_instance_menu -> AppendSeparator();

				component_instance_menu -> Append(ID_MENU_DELETE_P,"delete this Component","delete this Component",TRUE);
			
				if (this->ExistsProp(GetSelection())) {
					component_instance_menu -> Enable(ID_MENU_ADD_P_H_I,FALSE);
					component_instance_menu -> Enable(ID_MENU_ADD_R_A_N,FALSE);
				}
	
				this->PopupMenu(component_instance_menu,event.GetPosition());
			}
			if (etype==facet) {
				wxMenu* facet_menu = new wxMenu("Register",2);

				facet_menu -> Append(ID_MENU_ADD_R_A_N,"Register at NameService","Register at NameService",TRUE);


				if (this->ExistsProp(GetSelection())) {
					facet_menu->Enable(ID_MENU_ADD_R_A_N,FALSE);
				}
	
				this->PopupMenu(facet_menu,event.GetPosition());
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

wxTreeItemId 
PartitioningTreeCtrl::get_CompId(wxTreeItemId itemid)
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

void PartitioningTreeCtrl::onadd_if(wxMenuEvent& event)
{
	wxFileDialog* filedialog=new wxFileDialog(this,"Choose a filearchive","","","*.*",0,wxDefaultPosition);
	int t=filedialog->ShowModal();
	wxString fullfile,filename,filepath;
	
	if (t==wxID_OK) {
		filename=filedialog->GetFilename();
		fullfile=filedialog->GetPath();
		filepath=filedialog->GetDirectory();
		
		Comp component=get_Comp(GetSelection());
		wxString text="filearchive: ";
		text.Append(fullfile);
		wxTreeItemId itemid = AppendItem(GetSelection(),text,
			TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);
		Expand(GetSelection());
		Refresh();

		ItemTyp itype;
		itype.itemid=itemid;
		itype.type=inst_prop;

		itemtypes.push_back(itype);
		
		Instantiation i = get_Instantiation(GetSelection());
		filearchive fa;
		fa.filename=filename;
		fa.path=filepath;
		i.filearchive=fa;

		replace_Instantiation(i);				
	}
	filedialog->~wxFileDialog();
}

void PartitioningTreeCtrl::onregister_at_name_service(wxMenuEvent& event)
{

	// opens dialog
	// request full scoped Naming Context name to register at
	wxString ns_name = wxGetTextFromUser("Enter a name for registering at Name Service","Register at NameService",
	"", this,-1,-1,TRUE);
	wxString text="NameService: ";
	text.Append(ns_name);

	// add name to tree
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetRootItem());
	Refresh();
	ItemTyp itype;
	itype.itemid=itemid;
	itype.type=registration;
	itype.usagename=ns_name;

	itemtypes.push_back(itype);

	// add information to instance or port

	ElementType etype=GetType(GetSelection());
	
	if (etype==inst) {
		// get instance
		Instantiation curr_instance = get_Instantiation(GetSelection());

		// add register Info to instance
		curr_instance.component_registration = ns_name;
		replace_Instantiation(curr_instance);				

	}

	if (etype==facet) {
		// get instance
		Instantiation curr_instance = get_Instantiation(GetItemParent(GetSelection()));


		// create new facet-registration
		PartitioningTreeCtrl::ItemTyp  facet_item = GetItemInfo(GetSelection());
		FacetRegistration fr;
		fr.facet_name = facet_item.usagename;
		fr.ns_name = ns_name;
		// add register Info to instance
		
		curr_instance.facet_registrations.push_back(fr);

		replace_Instantiation(curr_instance);				

	}


}

std::vector <PartitioningTreeCtrl::Comp> 
PartitioningTreeCtrl::get_Comp4Con()
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

void 
PartitioningTreeCtrl::onadd_ci(wxMenuEvent& event)
{

	wxString cid= wxGetTextFromUser("Enter an identifier of instantiation","Identifier",
	"", this,-1,-1,TRUE);
	Comp component=get_Comp(GetSelection());
	wxString text="Instantiation(";
	text.Append(cid);
	text.Append(")");
	wxTreeItemId itemid = AppendItem(GetSelection(),text,
		TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	Expand(GetSelection());
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

	// get component information
	// get from connectioncontroll
	
	add_ports_to_component_instance(component, itemid);

}

void
PartitioningTreeCtrl::add_ports_to_component_instance(PartitioningTreeCtrl::Comp component, wxTreeItemId parent_itemid) {

	// get port information
	PartitioningTreeCtrl::CPort cport;
	cport.idref=component.idref;
	cport.instantiations=component.instantiations;
	
	std::string package_;
	std::string ccdfile_name;
	package_=""; 
	wxString tmp_string;

	tmp_string=component.link.c_str();
	tmp_string.Replace ("\\","/");

	package_.append(tmp_string.c_str() );

	Qedo::Package *package = new Qedo::Package(package_);

	ccdfile_name = package->getFileNameWithSuffix( ".ccd" );

	Qedo::CCDReader4qxml *ccdreader = 
		new Qedo::CCDReader4qxml(package_,m_temp_path.c_str());
	cport.ccddata = ccdreader->getCCD();

	

	// now adding ports to the tree
	std::vector < Qedo::CCDPort > :: iterator portiter;
	for(portiter = cport.ccddata.ports.begin(); 
		portiter != cport.ccddata.ports.end(); 
		portiter++)
	{
		
		Qedo::CCDPort ccdport=(*portiter);
		if (ccdport.type==Qedo::providesport ) 
		{
			{
				//add to tree
				wxString text="Facet ";
				text.Append(ccdport.identifier.c_str());
				wxTreeItemId itemid = AppendItem(parent_itemid,text,
					TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
				Expand(GetSelection());
				Refresh();
				ItemTyp itype;
				itype.itemid=itemid;
				itype.type=facet;
				itype.usagename = ccdport.identifier.c_str();

				itemtypes.push_back(itype);

			}
			
		}
		
	}
};


PartitioningTreeCtrl::ElementType 
PartitioningTreeCtrl::GetType(wxTreeItemId itemid)
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

PartitioningTreeCtrl::ItemTyp 
PartitioningTreeCtrl::GetItemInfo(wxTreeItemId itemid)
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

bool PartitioningTreeCtrl::ExistsProp(wxTreeItemId itemid)
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

PartitioningTreeCtrl::Comp 
PartitioningTreeCtrl::get_Comp(wxTreeItemId itemid)
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
	
	value.Append("<homeplacement id=");
	value.Append(a);
	value.Append(ityp.usagename);
	value.Append(a);
	value.Append(">\n");
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

				if (!(insta.filearchive.filename.IsEmpty())) {

					// properties
					value.Append(tabtab);
					value.Append(tab);
					value.Append("<componentproperties>\n");
					value.Append(tabtab);
					value.Append(tabtab);
					value.Append("<fileinarchive name=");
					value.Append(a);
					value.Append("meta-inf/");
					value.Append(insta.filearchive.filename);
					value.Append(a);
					value.Append(">\n");
					value.Append(tabtab);
					value.Append(tabtab);
					value.Append("</fileinarchive>\n");
					value.Append(tabtab);
					value.Append(tab);
					value.Append("</componentproperties>\n");
				}
				
				//check for registering component
				if (!(insta.component_registration.IsEmpty())) {
					value.Append(tabtab);
					value.Append(tab);
					value.Append("<registercomponent>\n");
					value.Append(tabtab);
					value.Append(tabtab);
					value.Append("<registerwithnaming name=\"");
					value.Append(insta.component_registration);
					value.Append("\"/>\n");
					value.Append(tabtab);
					value.Append(tab);
					value.Append("</registercomponent>\n");
				}

				//
				// print out facet registrations
				//
				std::vector<FacetRegistration> ::iterator facet_iter;
				for(facet_iter = insta.facet_registrations.begin(); 
					facet_iter != insta.facet_registrations.end(); 
					facet_iter++)
				{
					value.Append(tabtab);
					value.Append(tab);
					value.Append("<registercomponent>\n");
					value.Append(tabtab);
					value.Append(tabtab);
					value.Append("<providesidentifier>");
					value.Append((*facet_iter).facet_name);
					value.Append("</providesidentifier>\n");
					value.Append(tabtab);
					value.Append(tabtab);
					value.Append("<registerwithnaming name=\"");
					value.Append((*facet_iter).ns_name);
					value.Append("\"/>\n");
					value.Append(tabtab);
					value.Append(tab);
					value.Append("</registercomponent>\n");
				}
				

				value.Append(tabtab);
				value.Append(tab);
				value.Append("</componentinstantiation>\n");
			}
	
	return value;

}


PartitioningTreeCtrl::Instantiation 
	PartitioningTreeCtrl::get_Instantiation(wxTreeItemId itemid)
{
	Instantiation value;
	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				std::vector <Instantiation>::iterator inst_iter;
				for(inst_iter = tempc.instantiations.begin();
					inst_iter != tempc.instantiations.end();
					inst_iter++)
				{
					Instantiation inst = (*inst_iter);
					if (inst.itemid==itemid)
					{
						value=inst;
						break;
					}
				}
				
			}
	return value;
}

void PartitioningTreeCtrl::replace_Instantiation
		(PartitioningTreeCtrl::Instantiation instantiation)
{
	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				std::vector <Instantiation>::iterator inst_iter;
				for(inst_iter = tempc.instantiations.begin();
					inst_iter != tempc.instantiations.end();
					inst_iter++)
				{
					Instantiation inst = (*inst_iter);
					if (inst.itemid==instantiation.itemid)
					{
						tempc.instantiations.erase(inst_iter);
						tempc.instantiations.push_back(instantiation);

						comps.erase(iter);
						comps.push_back(tempc);
						break;
					}
				}
				
			}

}

void PartitioningTreeCtrl::copy_filearchive(wxString path)
{
	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				std::vector <Instantiation>::iterator inst_iter;
				for(inst_iter = tempc.instantiations.begin();
					inst_iter != tempc.instantiations.end();
					inst_iter++)
				{
					Instantiation inst = (*inst_iter);
					if (!(inst.filearchive.filename.IsEmpty()))
					{
						wxString source=inst.filearchive.path;
						source.Append("/");
					    source.Append(inst.filearchive.filename);
						
						wxString target=path;
						target.Append("/");
						target.Append(inst.filearchive.filename);
						wxCopyFile(source,target,TRUE);
						
					}
				}
				
			}

}
void PartitioningTreeCtrl::remove_files()
{
	std::vector <Comp> ::iterator iter;
	for(iter = comps.begin(); 
		iter != comps.end(); 
			iter++)
			{
				Comp tempc=(*iter);
				std::vector <Instantiation>::iterator inst_iter;
				for(inst_iter = tempc.instantiations.begin();
					inst_iter != tempc.instantiations.end();
					inst_iter++)
				{
					Instantiation inst = (*inst_iter);
					if (!(inst.filearchive.filename.IsEmpty()))
					{
						wxString file="meta-inf/";
						file.Append(inst.filearchive.filename);
						wxRemoveFile(file);
						
					}
				}
				
			}
}

void PartitioningTreeCtrl::setdummy(AComponentTreeCtrl* atc)
{
	ACTreeCtrl = atc;
}