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
#include "ComponentTreeCtrl.h"
#include "CSDReader4qxml.h"
#include "CSDStruc4qxml.h"
//#include "AComponentTreeCtrl.h"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"

BEGIN_EVENT_TABLE( ComponentTreeCtrl, wxTreeCtrl )
	EVT_RIGHT_DOWN(ComponentTreeCtrl::OnItem)
	EVT_MENU(ID_MENU_DELETE,ComponentTreeCtrl::ondelete)
	EVT_MENU(ID_MENU_ADD,ComponentTreeCtrl::onadd)
	EVT_MENU(ID_MENU_USE_IMP,ComponentTreeCtrl::onuse)
END_EVENT_TABLE()

ComponentTreeCtrl::ComponentTreeCtrl()
{
}

ComponentTreeCtrl::ComponentTreeCtrl( wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style): wxTreeCtrl(parent, id, pos, size, style)
{
	CreateImageList(16);
	RootId = this->AddRoot(wxT("ComponentPackages"),TreeCtrlIcon_Folder , TreeCtrlIcon_FolderSelected , NULL);
	Show();
}

void ComponentTreeCtrl::CreateImageList(int size)
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

void ComponentTreeCtrl::add_component_package(wxString file,wxString path)
{
	wxTreeItemId itemid = this->AppendItem(RootId,file,TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
	std::string package_;
	std::string cadfile_name;
		package_=""; 
		wxString tmp_string;
		
		tmp_string=file.c_str();
		tmp_string.Replace ("\\","/");
	
		package_.append(tmp_string.c_str() );
		//wxLogMessage(package_.c_str());
		Qedo::Package *package = new Qedo::Package(package_);
		//package->;
		cadfile_name = package->getFileNameWithSuffix( ".csd" );
		
	
		Qedo::CSDReader4qxml *csdreader = 
			new Qedo::CSDReader4qxml(package_,path.c_str());
		Qedo::CSDData data = csdreader->getCSD();

		wxTreeItemId DescriptionItemId = this->AppendItem(itemid,"Description",
			TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);
		wxString text="Title: ";
		this->AppendItem(DescriptionItemId,text.Append(data.title.c_str()),
			TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);
		text="Author: ";
		this->AppendItem(DescriptionItemId,text.Append(data.author.c_str()),
			TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);
		text="PKGType: ";
		this->AppendItem(DescriptionItemId,text.Append(data.pkgtype.c_str()),
			TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);


		wxTreeItemId ImplementationId = this->AppendItem(itemid,"Implementations",
			TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);

		add_implementations(ImplementationId,data);

		ctrldata ctdata;
		ctdata.data=data;
		ctdata.itemid=itemid;
		ctdata.file.Append(cadfile_name.c_str());
		ctdata.path.Append(file);
		wxString filename=file;
		//wxChar* b ='\\';
		filename.Replace(path,"",TRUE);
		filename.Replace("\\","",TRUE);
		ctdata.filename.Append(filename);
		
		this->ctrldatas.push_back(ctdata);

		this->Refresh();

}

void ComponentTreeCtrl::add_implementations(wxTreeItemId ImplementationId,Qedo::CSDData data)
{
	
	std::vector <Qedo::Implementation> ::iterator impl_iter;
	
	for(impl_iter = data.implementations.begin(); 
		impl_iter != data.implementations.end(); 
			impl_iter++)
			{
				wxTreeItemId ImpId = this->AppendItem(ImplementationId,
								(*impl_iter).id.c_str(),TreeCtrlIcon_Folder,
								TreeCtrlIcon_FolderSelected,NULL);
				wxString os="OS: ";
				this->AppendItem(ImpId,os.Append((*impl_iter).os_name.c_str()),
					TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);
				
				wxTreeItemId desId = this->AppendItem(ImpId,"Descriptor",
					TreeCtrlIcon_Folder,TreeCtrlIcon_FolderSelected,NULL);

				os="Type: ";
				this->AppendItem(desId,os.Append((*impl_iter).descriptor.type.c_str()),
					TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);
				os="Filearchive: ";
				this->AppendItem(desId,os.Append((*impl_iter).descriptor.filearchive.c_str()),
					TreeCtrlIcon_File,TreeCtrlIcon_FileSelected,NULL);
				
				impldata impld;
				impld.itemid=ImpId;
				impld.implementation=(*impl_iter);

				implementations.push_back(impld);
				
			}
	
}

void ComponentTreeCtrl::onadd(wxMenuEvent& event)
{	wxString file; // Full path+file
	wxString path; // only path without file
	
	wxFileDialog* file_dialog=new wxFileDialog(this,"Choose a componentfile","","","*.zip",0,wxDefaultPosition);
	int t=file_dialog->ShowModal();
	
	
	if (t==wxID_OK) {
		file=file_dialog->GetPath();
		path=file_dialog->GetDirectory();

		add_component_package(file,path);
		
	}
	file_dialog->~wxFileDialog();
	

}

void ComponentTreeCtrl::OnItem(wxMouseEvent& event) 
{
	CreateImageList(16);
	if (!(this->GetItemText(this->GetSelection()).empty())) 
	{
		if (this->GetSelection()!=this->GetRootItem())
		{
			wxTreeItemId compid = get_CompId(GetSelection());
			
			
			wxMenu *test = new wxMenu("ComponentPackage",2);
			//test->SetTitle("ComponentPackage");
			test->Append(ID_MENU_ADD,"Add new ComponentPackage","add new ComponentPackage",TRUE);

			if (isimpl(GetSelection())) {
				test->Append(ID_MENU_USE_IMP,"Use Implementation for Assembly","add this implementation to AssemblyView",TRUE);
			}
			test->AppendSeparator();
			test->Append(ID_MENU_DELETE,"delete this ComponentPackage","delete this ComponentPackage",TRUE);
	
			this->PopupMenu(test,event.GetPosition());
			
		}
		if (this->GetSelection()==this->GetRootItem())
		{
			wxMenu *onlyRoot = new wxMenu("ComponentPackage",2);
			onlyRoot->Append(ID_MENU_ADD,"Add new ComponentPackage","add new ComponentPackage",TRUE);
			this->PopupMenu(onlyRoot,event.GetPosition());
		}
	}
}

bool ComponentTreeCtrl::isimpl(wxTreeItemId itemid)
{
	bool value=false;
	std::vector <impldata> ::iterator iter;
	for(iter = implementations.begin(); 
		iter != implementations.end(); 
			iter++)
			{
				impldata idata=(*iter);
				if (idata.itemid==itemid) {
					value=true;
					break;
				}
			}
    return value;
}

wxTreeItemId ComponentTreeCtrl::get_CompId(wxTreeItemId itemid)
{ /* returns the ItemId of the ComponentPackage */
 
	
	while (GetItemParent(itemid)!=GetRootItem())
	{
		itemid=GetItemParent(itemid);
		
	}

	return itemid;

}

void ComponentTreeCtrl::ondelete(wxMenuEvent& event)
{
	wxTreeItemId compid = get_CompId(GetSelection());
	delete_entry_in_vector(compid);
	Delete(compid);
	Refresh();
}

void ComponentTreeCtrl::onuse(wxMenuEvent& event)
{

	wxString cid= wxGetTextFromUser("Enter a componentfile ID","ComponentFile ID",
	"", this,-1,-1,TRUE);
	ctrldata ctdata=get_CtrData(get_CompId(GetSelection()));
	
	ACTreeCtrl->add_implementation(get_implementation(GetSelection()),
		cid,ctdata.path,ctdata.file,ctdata.filename);
	
}

void ComponentTreeCtrl::delete_entry_in_vector(wxTreeItemId compid)
{
	std::vector <ctrldata> ::iterator iter;
	for(iter = ctrldatas.begin(); 
		iter != ctrldatas.end(); 
			iter++)
			{
				ctrldata ctdata=(*iter);
				if (ctdata.itemid==compid) {
					ctrldatas.erase(iter);
					break;
				}
			}
}

ComponentTreeCtrl::ctrldata ComponentTreeCtrl::get_CtrData(wxTreeItemId itemid)
{
	ctrldata cdata;
	std::vector <ctrldata> ::iterator iter;
	for(iter = ctrldatas.begin(); 
		iter != ctrldatas.end(); 
			iter++)
			{
				ctrldata ctdata=(*iter);
				if (ctdata.itemid==itemid) {
					cdata=ctdata;
					break;
				}
			}
   return cdata;
}

Qedo::Implementation ComponentTreeCtrl::get_implementation(wxTreeItemId itemid)
{
	Qedo::Implementation value;
	std::vector <impldata> ::iterator iter;
	for(iter = implementations.begin(); 
		iter != implementations.end(); 
			iter++)
			{
				impldata idata=(*iter);
				if (idata.itemid==itemid) {
					value=idata.implementation;
					break;
				}
			}
    return value;
}


void ComponentTreeCtrl::setdummy(AComponentTreeCtrl* atc)
{
	ACTreeCtrl = atc;
}