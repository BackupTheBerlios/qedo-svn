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

#include "NSBrowser.h"

#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/sizer.h"
#include "wx/statbox.h"
#include "wx/stattext.h"
#include "wx/menu.h"
#include "wx/log.h"
#include "wx/textctrl.h"


#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"



#include "ConfigurationReader.h"


BEGIN_EVENT_TABLE(NSBrowserTreeCtrl, wxTreeCtrl)
    EVT_BUTTON(NSD_TREE_REFRESH, NSBrowserTreeCtrl::OnNSDRefresh)
	EVT_RIGHT_DOWN(NSBrowserTreeCtrl::OnItem)
	EVT_MENU(ID_MENU_IOR,NSBrowserTreeCtrl::onior)
	EVT_MENU(ID_MENU_DELETE,NSBrowserTreeCtrl::ondelete)

END_EVENT_TABLE()


NSBrowserTreeCtrl::NSBrowserTreeCtrl(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxTreeCtrl(parent, id, pos, size, style)
{
	wxBoxSizer *h_sizer = new wxBoxSizer(wxHORIZONTAL);
	parent -> SetSizer (h_sizer);
    parent->SetAutoLayout(TRUE);

	wxBoxSizer * left_sizer = new wxBoxSizer(wxVERTICAL);

	left_sizer -> Add(this, 0, wxGROW|wxALL|wxEXPAND , 5);
	h_sizer -> Add(left_sizer, 0, wxEXPAND | wxALL, 5);

	wxStaticBox *mesbox = new wxStaticBox(parent, -1, _T("&NSBrowser Message:"));
	wxStaticBoxSizer *mes_sizer = new wxStaticBoxSizer(mesbox,wxVERTICAL);

	left_sizer->Add(mes_sizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

	message_nsbrowser = new wxTextCtrl( parent, ID_HOSTNAME_NSD, _T("Name Service Message"), wxDefaultPosition, wxSize(400,130),wxTE_MULTILINE);
	mes_sizer->Add(message_nsbrowser, 0, wxALIGN_RIGHT|wxALL, 5);

	wxBoxSizer * rigth_sizer = new wxBoxSizer(wxVERTICAL);
	h_sizer -> Add(rigth_sizer, 0, wxALIGN_RIGHT | wxALL, 5);

	RefreshBtn = new wxButton(parent, NSD_TREE_REFRESH, _T("Refresh"));
	rigth_sizer-> Add(RefreshBtn , 0, wxALIGN_RIGHT|wxALL, 5);

	wxStaticBox *lp_box = new wxStaticBox(parent, -1, _T("&Browse on:"));
	wxStaticBoxSizer *lp_sizer = new wxStaticBoxSizer(lp_box,wxVERTICAL);

	rigth_sizer->Add(lp_sizer, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5);
	
	wxStaticText* host_text = new wxStaticText( parent, wxID_STATIC, _T("hostname:"), wxDefaultPosition, wxDefaultSize, 0 );
	lp_sizer->Add(host_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	host_nsbrowser = new wxTextCtrl( parent, ID_HOSTNAME_NSD, _T("localhost"), wxDefaultPosition, wxSize(80,20), 0 );
	lp_sizer->Add(host_nsbrowser, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticText* port_text = new wxStaticText( parent, wxID_STATIC, _T("port:"), wxDefaultPosition, wxDefaultSize, 0 );
	lp_sizer->Add(port_text , 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

	port_nsbrowser = new wxTextCtrl( parent, ID_HOSTNAME_NSD, _T("12356"), wxDefaultPosition, wxSize(80,20), 0 );
	lp_sizer->Add(port_nsbrowser, 0, wxALIGN_RIGHT|wxALL, 5);

	get_host_and_ip();
	
	//build_tree();
	
}

NSBrowserTreeCtrl::~NSBrowserTreeCtrl()
{

}
void NSBrowserTreeCtrl::CreateImageList(int size)
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


void
NSBrowserTreeCtrl::build_tree()
{
	// resolve name service reference
	
	int dummy = 0;
	orbns = CORBA::ORB_init(dummy,0);

	wxString ns;

    //ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );;
	//ns = "corbaloc::localhost:12356/NameService";
	//CORBA::ORB_var tmp = CORBA::ORB::_duplicate(QedoController::global_orb);
	ns.Append("corbaloc::");
	ns.Append(this->host_nsbrowser->GetValue());
	ns.Append(":");
	ns.Append(this->port_nsbrowser->GetValue());
	ns.Append("/NameService");
	
	wxString mes=message_nsbrowser->GetValue();
	message_nsbrowser->SetValue(mes+"\n"+"Refresh NameService"+"\n"+ns);

	CORBA::Object_var obj;
	try {
	obj = orbns -> string_to_object( ns.c_str() );
	
	CreateImageList();


	try {
		nameService = CosNaming::NamingContext::_narrow(obj.in());
	} catch (CORBA::SystemException) {
	    wxString mes="Error: Cannot narrow NameService under ";
		mes.Append(ns);
		this->message_nsbrowser->SetValue(mes);
	
	};
	if (!CORBA::is_nil(nameService))
	{
    wxTreeItemId rootId = AddRoot(wxT("RootContext"),
                                  TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected,
                                  new NSBrowserTreeItemData(wxT("Root item")));

		 AddItemsRecursively(rootId, nameService);
	}
	
		
	} catch (CORBA::SystemException) {
		wxString mes="Error: Cannot find NameService under ";
		mes.Append(ns);
		this->message_nsbrowser->SetValue(mes);};

	
}

void NSBrowserTreeCtrl::AddItemsRecursively(const wxTreeItemId& idParent,
									 CosNaming::NamingContext_ptr context)
{
	try {
		// list context
		CosNaming::BindingList_var bl ;
		CosNaming::BindingIterator_var bi;

		context -> list (10, bl, bi);
		wxString str;

		for (CORBA::ULong i = 0; i < bl->length(); i++)
		{
			// if context
	//		if ((*bl)[i].binding_type == CosNaming::ncontext)
	//		{
				CosNaming::NamingContext_var child_context;
				CORBA::Object_var tmp_obj;
				tmp_obj = context -> resolve((*bl)[i].binding_name);
				try {
					child_context = CosNaming::NamingContext::_narrow(tmp_obj);
				} catch (CORBA::SystemException e) {}
				if (!CORBA::is_nil(child_context))
				{
					
					str.Printf(wxT("%s"), wxT((*bl)[i].binding_name[0].id.in()));
					wxTreeItemId id = AppendItem(idParent, str, TreeCtrlIcon_Folder, TreeCtrlIcon_FolderSelected, new NSBrowserTreeItemData(str));
					
					AddItemsRecursively(id, child_context.in());
				} else {
					str.Printf(wxT("%s"), wxT((*bl)[i].binding_name[0].id.in()));
					wxTreeItemId id = AppendItem(idParent, str, TreeCtrlIcon_File, TreeCtrlIcon_FileSelected, new NSBrowserTreeItemData(str));
				}
	//		}


			// add to tree
			//wxTreeItemId id = AppendItem(idParent, str, 1, 1, new MyTreeItemData(str));

		}
	} catch (CORBA::SystemException&)
	{ }
}

void 
NSBrowserTreeCtrl::OnNSDRefresh()
{
//	int sel = event.GetSelection();
//	if (sel == 1)
//	{
		// rebiuld NS Browser Tree
		this->DeleteAllItems();
		this->build_tree();
		this->Refresh();
//	};

}

void 
NSBrowserTreeCtrl::get_host_and_ip()
{
	std::string ns;

	ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );

	//corbaloc::schlepptop:12356/NameService
	wxString tmpstring=ns.c_str();
	tmpstring.Replace("corbaloc::","");
	tmpstring.Replace("/NameService","");

	int mid=tmpstring.Find(":");

	this->host_nsbrowser->SetValue((tmpstring.Mid(0,mid)).c_str());
	this->port_nsbrowser->SetValue((tmpstring.Mid(mid+1,wxSTRING_MAXLEN)).c_str());
	//this->message_nsbrowser->SetValue(tmpstring.c_str());
}

void NSBrowserTreeCtrl::OnItem(wxMouseEvent& event) 
{
	if (!(this->GetItemText(this->GetSelection()).empty())) 
	{
		if (this->GetSelection()!=this->GetRootItem())
		{
			wxMenu *test = new wxMenu("",0);
			test->Append(ID_MENU_IOR,"Show IOR","shows the IOR in the message box",TRUE);
			test->AppendSeparator();
			wxString mes="delete ";
			mes.Append(this->GetItemText(this->GetSelection()));

			test->Append(ID_MENU_DELETE,mes.c_str(),"delete this entry",TRUE);
	
			this->PopupMenu(test,event.GetPosition());
		}
	}

}

wxString NSBrowserTreeCtrl::getNSPath(wxTreeItemId item)
{
	wxString tmp;
	if (item!=this->GetRootItem())
	{
		tmp=getNSPath(this->GetItemParent(item)).Append("/").Append(this->GetItemText(item));
	}

	return tmp;
}

CosNaming::Name NSBrowserTreeCtrl::getNameContext(wxString path)
{
	CosNaming::NamingContext_var context; 
	CosNaming::Name contextName;
	int len=path.Freq('/');
		
	contextName.length(len+1);
	CORBA::ULong t=0;
	while (t<=len)
	{
		int pos=path.Find("/");
			
		if (pos==-1) {pos=path.Length();}
			
		contextName[t].id = CORBA::string_dup(path.Mid(0,pos));
		contextName[t].kind = CORBA::string_dup("");
		path=path.Mid(pos+1,wxSTRING_MAXLEN); 
		t++;
	}

	return contextName;
}

void NSBrowserTreeCtrl::ior(wxString path)
{
		
		int dummy = 0;
		orbns = CORBA::ORB_init(dummy,0);

		wxString ns;
		CosNaming::Name name=getNameContext(path);
    
		ns.Append("corbaloc::");
		ns.Append(this->host_nsbrowser->GetValue());
		ns.Append(":");
		ns.Append(this->port_nsbrowser->GetValue());
		ns.Append("/NameService");
		
		CORBA::Object_var nsobj;
		try {
		nsobj = orbns -> string_to_object( ns.c_str() );
		CORBA::Object_var obj;
			try {
			//resolve the name component with the naming service
			CosNaming::NamingContext_var nc=CosNaming::NamingContext::_narrow(nsobj);
			obj=nc->resolve(name);
			wxString mes="Show IOR of "+path+": \n"+
				         "======================================== \n";
			if (CORBA::is_nil (obj)) {
				mes.Append("Error is nil");
		
			} else {

				mes.Append(orbns->object_to_string (obj));
				mes.Append("\n");
				mes.Append("========================================");
			}
			message_nsbrowser->SetValue(mes);
			} catch(...) {};

		} catch (CORBA::SystemException) {
	    wxString mes2="Error: Cannot narrow NameService under ";
		mes2.Append(ns);
		this->message_nsbrowser->SetValue(mes2);
	
		};



}

void NSBrowserTreeCtrl::delete_entry(wxString path)
{
		
		int dummy = 0;
		orbns = CORBA::ORB_init(dummy,0);

		wxString ns;
		CosNaming::Name name=getNameContext(path);
    
		ns.Append("corbaloc::");
		ns.Append(this->host_nsbrowser->GetValue());
		ns.Append(":");
		ns.Append(this->port_nsbrowser->GetValue());
		ns.Append("/NameService");
		
		CORBA::Object_var nsobj;
		try {
		nsobj = orbns -> string_to_object( ns.c_str() );
		
			try {
			//resolve the name component with the naming service
			CosNaming::NamingContext_var nc=CosNaming::NamingContext::_narrow(nsobj);
			nc->unbind(name); 
			wxString mes="Delete "+path+": \n";
						    mes.Append(GetItemText(GetSelection())+" was deleted by user.");
			
			message_nsbrowser->SetValue(mes);
			OnNSDRefresh();
			} catch(...) {};

		} catch (CORBA::SystemException) {
	    wxString mes2="Error: Cannot narrow NameService under ";
		mes2.Append(ns);
		this->message_nsbrowser->SetValue(mes2);
	
		};



}


void NSBrowserTreeCtrl::onior(wxMenuEvent& event)
{
	wxString nspath=getNSPath(this->GetSelection()).Mid(1,wxSTRING_MAXLEN);
	
	ior(nspath);

}

void NSBrowserTreeCtrl::ondelete(wxMenuEvent& event)
{
	wxString nspath=getNSPath(this->GetSelection()).Mid(1,wxSTRING_MAXLEN);
	delete_entry(nspath);

}
