#include "qcexplorer.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/statbox.h"
#include "explore.h"
#include "QedoExplorer.h"

#include "icon1.xpm"
#include "icon2.xpm"
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
          : wxTreeCtrl(parent, id, pos, size, style)

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
QCexplorerTreeCtrl::build_tree()
{

	
	CreateImageList();
	int dummy=0;
	try {
		CORBA::ORB_var orb = CORBA::ORB_init(dummy,0);
	
		// resolve the naming service
		
		//CORBA::Object_var nsobj= orb->resolve_initial_references("NameService");
		std::string ns;
			
		
		ns=cmd_ns.c_str();
		
		CORBA::Object_var nsobj;
		nsobj = orb -> string_to_object( ns.c_str() );

	if (CORBA::is_nil(nsobj)) {
			//std::cerr << "Cannot resolve NameService" << endl;
			exit(1);
	}
		
		//narrow the root naming context
	CosNaming::NamingContext_var nc=CosNaming::NamingContext::_narrow(nsobj);



	//create a name component
	CosNaming::Name name;
	name.length(1);
	name[0].id=CORBA::string_dup("ExploreServer");
	name[0].kind=CORBA::string_dup("");

	//resolve the name component with the naming service
	CORBA::Object_var obj=nc->resolve(name);

		
	
	// Narrow
	Explore_var exp = Explore::_narrow(obj);
	ComponentServerActivatorInfoList* CSAIL=exp->explore_qedo();

	ComponentServerActivatorInfoList test=CSAIL[0];

	//Info t = new Info;
	


    wxTreeItemId rootId = AddRoot(wxT("ServerActivators"),
                                  TreeCtrlIcon_FolderOpened , TreeCtrlIcon_Folder ,
                                  new QCexplorerTreeItemData(wxT("NIL")));
	//t.Item = rootId ;
	//t.Text="Root";
//	Infoliste.addElemet(t);


	

	for (int i=1; i<=test.length(); i++) {
		wxTreeItemId idParent=rootId;
		ComponentServerActivatorInfo sa = test[i-1];
		wxString str ;
		str.Printf(wxT("%s"), wxT(sa.host_name));
		


		wxTreeItemId idServerActivator = AppendItem(idParent, str , TreeCtrlIcon_Folder, 
								TreeCtrlIcon_Folder,new QCexplorerTreeItemData(str));
		ComponentServerInfoList csil=sa.my_component_servers;
		
		for (int z=1; z<=csil.length(); z++) 
		{	
			
			ComponentServerInfo csi=csil[z-1];
			wxString str;
			wxString csi_tmp ;
			csi_tmp="ComponentServer ";
			

			csi_tmp.append(wxString::Format("%d",z));
			csi_tmp.append(" on ");
			csi_tmp.append(csi.host_name);
			str.Printf(wxT("%s"),wxT(csi_tmp));
			
			wxTreeItemId idComponentServer = AppendItem(idServerActivator, str , TreeCtrlIcon_Folder, 
								TreeCtrlIcon_Folder,new QCexplorerTreeItemData(str));

			ContainerInstanceInfoList ciil=csi.my_containers;
			for (int y=1; y<=ciil.length(); y++) {

				ContainerInstanceInfo cii=ciil[y-1];
				wxString str;
				wxString cii_tmp;
				cii_tmp="Container ";
				cii_tmp.append(wxString::Format("%d",y));
				cii_tmp.append(" - ");
				cii_tmp.append(cii.short_name);
				str.Printf(wxT("%s"),wxT(cii_tmp));

				wxTreeItemId idContainerInstance = AppendItem(idComponentServer, str , TreeCtrlIcon_Folder, 
								TreeCtrlIcon_Folder,new QCexplorerTreeItemData(str));
				
				HomeInstanceInfoList hiil=cii.my_homes;

				for (int a=1; a<=hiil.length(); a++) {

					HomeInstanceInfo hii=hiil[a-1];
					wxString str;
					str="";
					wxString hii_tmp;
					
					hii_tmp=(hii.short_name);
					str.Printf(wxT("%s"),wxT(hii_tmp));

					wxTreeItemId idHomeInstance = AppendItem(idContainerInstance, str , TreeCtrlIcon_Folder, 
									TreeCtrlIcon_Folder,new QCexplorerTreeItemData(str));

					ComponentInstanceInfoList coiil=hii.my_components;
					for (int b=1; b<=coiil.length(); b++) {

						ComponentInstanceInfo coii=coiil[b-1];
						wxString str;
						str="";
						wxString coii_tmp;
					
						coii_tmp=(coii.short_name);
						str.Printf(wxT("%s"),wxT(coii_tmp));

						wxTreeItemId idComponentInstance = AppendItem(idHomeInstance, str ,  TreeCtrlIcon_File, TreeCtrlIcon_File,
							new QCexplorerTreeItemData(str));

					}
				}

			}
		}

	}

	
	}
	catch (const CORBA::SystemException_catch& ex) {
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

void QCexplorerTreeCtrl::OnItem( ) {
	
	wxTreeItemId item=this->GetSelection() ;
	wxString str;
	str=GetItemText(item);

	info_box->Clear();			
	info_box->WriteText(str);
	
}

void QCexplorerTreeCtrl::set_info_box(wxTextCtrl* info_box_ref) {
	info_box=info_box_ref;
};



