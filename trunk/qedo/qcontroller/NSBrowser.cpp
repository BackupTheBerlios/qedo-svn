#include "NSBrowser.h"
#include "wx/image.h"
#include "wx/imaglist.h"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"


#include "../qedoutil/ConfigurationReader.h"
// MyTreeCtrl implementation
/*
#if USE_GENERIC_TREECTRL
IMPLEMENT_DYNAMIC_CLASS(NSBrowserTreeCtrl, wxGenericTreeCtrl)
#else
IMPLEMENT_DYNAMIC_CLASS(NSBrowserTreeCtrl, wxTreeCtrl)
#endif
*/
NSBrowserTreeCtrl::NSBrowserTreeCtrl(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxTreeCtrl(parent, id, pos, size, style)
{

	// resolve name service reference
	int dummy = 0;
	CORBA::ORB_var orb = CORBA::ORB_init(dummy,0);

	std::string ns;
	ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );;
	//ns = "corbaloc::tri:12356/NameService";
	CORBA::Object_var obj;
	obj = orb -> string_to_object( ns.c_str() );

	
	nameService = CosNaming::NamingContext::_narrow(obj.in());

	CreateImageList();
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
void NSBrowserTreeCtrl::CreateButtonsImageList(int size)
{
#if USE_GENERIC_TREECTRL || !defined(__WXMSW__)
    if ( size == -1 )
    {
        SetButtonsImageList(NULL);
        return;
    }

    // Make an image list containing small icons
    wxImageList *images = new wxImageList(size, size, TRUE);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[4];
    icons[0] = wxIcon(icon3_xpm);   // closed
    icons[1] = wxIcon(icon3_xpm);   // closed, selected
    icons[2] = wxIcon(icon5_xpm);   // open
    icons[3] = wxIcon(icon5_xpm);   // open, selected

    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    {
        int sizeOrig = icons[i].GetWidth();
        if ( size == sizeOrig )
        {
            images->Add(icons[i]);
        }
        else
        {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignButtonsImageList(images);
#endif
}


void
NSBrowserTreeCtrl::build_tree()
{
    wxTreeItemId rootId = AddRoot(wxT("RootContext"),
                                  TreeCtrlIcon_FolderOpened , TreeCtrlIcon_Folder ,
                                  new NSBrowserTreeItemData(wxT("Root item")));
	
		 AddItemsRecursively(rootId, nameService);
}

void NSBrowserTreeCtrl::AddItemsRecursively(const wxTreeItemId& idParent,
									 CosNaming::NamingContext_ptr context)
{

	// list context
	CosNaming::BindingList_var bl ;
	CosNaming::BindingIterator_var bi;

	context -> list (10, bl, bi);
    wxString str;

	for (CORBA::ULong i = 0; i < bl->length(); i++)
	{
		// if context 
		if ((*bl)[i].binding_type = CosNaming::ncontext)
		{
			CosNaming::NamingContext_var child_context;
			CORBA::Object_var tmp_obj;
			tmp_obj = context -> resolve((*bl)[i].binding_name);
			child_context = CosNaming::NamingContext::_narrow(tmp_obj);
			if (!CORBA::is_nil(child_context))
			{
				str.Printf(wxT("%s %s"), wxT("NamingContext"), wxT((*bl)[i].binding_name[0].id.in()));
				wxTreeItemId id = AppendItem(idParent, str, TreeCtrlIcon_Folder, TreeCtrlIcon_Folder, new NSBrowserTreeItemData(str));

				AddItemsRecursively(id, child_context.in());
			} else {
				str.Printf(wxT("%s %s"), wxT("Object"), wxT((*bl)[i].binding_name[0].id.in()));
				wxTreeItemId id = AppendItem(idParent, str, TreeCtrlIcon_File, TreeCtrlIcon_File, new NSBrowserTreeItemData(str));
			}
		}


		// add to tree
		//wxTreeItemId id = AppendItem(idParent, str, 1, 1, new MyTreeItemData(str));

	}

}
