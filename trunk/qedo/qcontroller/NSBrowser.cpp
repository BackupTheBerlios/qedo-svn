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

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"



#include "ConfigurationReader.h"


BEGIN_EVENT_TABLE(NSBrowserTreeCtrl, wxTreeCtrl)
    EVT_BUTTON(NSD_TREE_REFRESH, NSBrowserTreeCtrl::OnNSDRefresh)

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

	wxBoxSizer * rigth_sizer = new wxBoxSizer(wxVERTICAL);
	h_sizer -> Add(rigth_sizer, 0, wxALIGN_RIGHT | wxALL, 5);

	RefreshBtn = new wxButton(parent, NSD_TREE_REFRESH, _T("Refresh"));
	rigth_sizer-> Add(RefreshBtn , 0, wxALIGN_RIGHT|wxALL, 5);

	build_tree();
	
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

	std::string ns;

	ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );;
	//ns = "corbaloc::localhost:12356/NameService";
	//CORBA::ORB_var tmp = CORBA::ORB::_duplicate(QedoController::global_orb);

	CORBA::Object_var obj;
	obj = orbns -> string_to_object( ns.c_str() );
	CreateImageList();


	try {
		nameService = CosNaming::NamingContext::_narrow(obj.in());
	} catch (CORBA::SystemException) {};
	if (!CORBA::is_nil(nameService))
	{
    wxTreeItemId rootId = AddRoot(wxT("RootContext"),
                                  TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected,
                                  new NSBrowserTreeItemData(wxT("Root item")));

		 AddItemsRecursively(rootId, nameService);
	}
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

};
