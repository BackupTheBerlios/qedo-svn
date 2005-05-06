
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
#include "AComponentTreeCtrl.h"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"

BEGIN_EVENT_TABLE( AComponentTreeCtrl, wxTreeCtrl )
	EVT_RIGHT_DOWN(AComponentTreeCtrl::OnItem)
END_EVENT_TABLE()

AComponentTreeCtrl::AComponentTreeCtrl()
{
}

AComponentTreeCtrl::AComponentTreeCtrl( wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style): wxTreeCtrl(parent, id, pos, size, style)
{
	CreateImageList(16);
	 this->AddRoot(wxT("Components"),TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
	Show();
}

void AComponentTreeCtrl::CreateImageList(int size)
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

void AComponentTreeCtrl::add_implementation(Qedo::Implementation impl,wxString cid,
											wxString link,wxString filearchive,wxString filename )
{	
	wxTreeItemId itemid=
		AppendItem(GetRootItem(),cid,TreeCtrlIcon_Folder,
						TreeCtrlIcon_FolderSelected,NULL);
	wxString text="Fileinarchive: ";
	AppendItem(itemid,text.Append(filearchive),TreeCtrlIcon_File,
						TreeCtrlIcon_FileSelected,NULL); 
	text="Link: ";
	AppendItem(itemid,text.Append(link),TreeCtrlIcon_File,
						TreeCtrlIcon_FileSelected,NULL);
	Expand(GetRootItem());
	Refresh();

    ACData adata;
	adata.file_id=cid;
	adata.impl=impl;
	adata.itemid=itemid;
	adata.link=link;
	adata.filearchive=filearchive;
	adata.filename=filename;

	acdatas.push_back(adata);


}

void AComponentTreeCtrl::OnItem(wxMouseEvent& event) 
{
	CreateImageList(16);
	if (!(this->GetItemText(this->GetSelection()).empty())) 
	{
		if (this->GetSelection()!=this->GetRootItem())
		{
			wxTreeItemId compid = get_CompId(GetSelection());
			
			
			wxMenu *test = new wxMenu("Components",2);
			//test->SetTitle("ComponentPackage");
			wxString text="Edit ";
			text.Append(GetItemText(compid));
			test->Append(ID_MENU_EDIT,text,"edit the ComponentID",TRUE);

			/*if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}*/
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE_AC,"delete this Component","delete this ComponentPackage",TRUE);
	
			this->PopupMenu(test,event.GetPosition());
			
		}
		/*if (this->GetSelection()==this->GetRootItem())
		{
			wxMenu *onlyRoot = new wxMenu("ComponentPackage",2);
			onlyRoot->Append(ID_MENU_ADD,"Add new ComponentPackage","add new ComponentPackage",TRUE);
			this->PopupMenu(onlyRoot,event.GetPosition());
		}*/
	}
} 

wxTreeItemId AComponentTreeCtrl::get_CompId(wxTreeItemId itemid)
{ /* returns the ItemId of the ComponentPackage */
 
	
	while (GetItemParent(itemid)!=GetRootItem())
	{
		itemid=GetItemParent(itemid);
		
	}

	return itemid;

}

wxArrayString AComponentTreeCtrl::get_CompArray()
{
	wxArrayString array;
	
	std::vector <ACData> ::iterator iter;
	for(iter = acdatas.begin(); 
		iter != acdatas.end(); 
			iter++)
			{
				ACData data=(*iter);
				array.Add(data.file_id);
			}

	return array;
}

Qedo::Implementation AComponentTreeCtrl::get_Implementation(wxString fileid)
{
	Qedo::Implementation value;
	std::vector <ACData> ::iterator iter;
	for(iter = acdatas.begin(); 
		iter != acdatas.end(); 
			iter++)
			{
				ACData data=(*iter);
				if (data.file_id==fileid) 
				{
					value=data.impl;
					break;
				}
				
			}

     return value;
}

wxString AComponentTreeCtrl::getLink(wxString fileid)
{
	wxString value;
	std::vector <ACData> ::iterator iter;
	for(iter = acdatas.begin(); 
		iter != acdatas.end(); 
			iter++)
			{
				ACData data=(*iter);
				if (data.file_id==fileid) 
				{
					value=data.link;
					break;
				}
				
			}
	return value;
}

wxString AComponentTreeCtrl::getFilearchive(wxString fileid)
{
	wxString value;
	std::vector <ACData> ::iterator iter;
	for(iter = acdatas.begin(); 
		iter != acdatas.end(); 
			iter++)
			{
				ACData data=(*iter);
				if (data.file_id==fileid) 
				{
					value=data.filearchive;
					break;
				}
				
			}
	return value;
}

wxString AComponentTreeCtrl::getCADData()
{
	char a='"';
	wxString tab="	";
	wxString tabtab="		";
	wxString value;
	std::vector <ACData> ::iterator iter;
	for(iter = acdatas.begin(); 
		iter != acdatas.end(); 
			iter++)
			{
				ACData data=(*iter);
				wxString cstring;
				cstring.Append(tabtab);
				cstring.Append("<componentfile id=");
				cstring.Append(a);
				cstring.Append(data.file_id);
				cstring.Append(a);
				cstring.Append(">\n");
				cstring.Append(tabtab);
				cstring.Append(tab);
				cstring.Append("<fileinarchive name=");
				cstring.Append(a);
				cstring.Append(data.filearchive);
				cstring.Append(a);
				cstring.Append(">\n");
				cstring.Append(tabtab);
				cstring.Append(tabtab);
				cstring.Append("<link href=");
				cstring.Append(a);
				cstring.Append(data.filename);
				cstring.Append(a);
				cstring.Append("/>\n");
				cstring.Append(tabtab);
				cstring.Append(tab);
				cstring.Append("</fileinarchive>\n");
				cstring.Append(tabtab);
				cstring.Append("</componentfile>\n");
				value.Append(cstring);
				
			}
	return value;
}

std::vector <AComponentTreeCtrl::fileinfo> AComponentTreeCtrl::getFiles()
{
	std::vector <AComponentTreeCtrl::fileinfo> filelist;
	std::vector <ACData> ::iterator iter;
	for(iter = acdatas.begin(); 
		iter != acdatas.end(); 
			iter++)
			{
				ACData cdata=(*iter);
				fileinfo fi;
				fi.filename=cdata.filename;
				fi.link=cdata.link;
				filelist.push_back(fi);
			}

  return filelist;

}