#include "wx/treectrl.h"
#include "CSDStruc4qxml.h"
#include "AComponentTreeCtrl.h"

////@begin control identifiers
#define ID_MENU_USE_IMP 10011
#define CP_TREE_RD 10012
#define ID_MENU_DELETE 10010
#define ID_MENU_ADD 10100
////@end control identifiers

class ComponentTreeCtrl : public wxTreeCtrl
{
	DECLARE_EVENT_TABLE()

public:
    enum
    {	
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
		TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened
    };
    ComponentTreeCtrl(); 
	
    ComponentTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);
   // virtual ~ComponentTreeCtrl();
	void add_component_package(wxString file,wxString path);
	void add_implementations(wxTreeItemId ImplementationId,Qedo::CSDData data);
	;
	void ComponentTreeCtrl::setdummy(AComponentTreeCtrl* atc);
	
private:
   int m_imageSize;
   void ComponentTreeCtrl::OnItem(wxMouseEvent& event);
   void ComponentTreeCtrl::CreateImageList(int size);
   AComponentTreeCtrl* ACTreeCtrl;
   void ComponentTreeCtrl::onadd(wxMenuEvent& event);
   void ComponentTreeCtrl::ondelete(wxMenuEvent& event);
   void ComponentTreeCtrl::onuse(wxMenuEvent& event);

   bool ComponentTreeCtrl::isimpl(wxTreeItemId itemid);

   void ComponentTreeCtrl::delete_entry_in_vector(wxTreeItemId compid);
   Qedo::Implementation get_implementation(wxTreeItemId itemid);
   
   wxTreeItemId get_CompId(wxTreeItemId itemid);
   wxTreeItemId RootId;

   

   struct ctrldata
	 {
		 /* CSDData Information */
		 Qedo::CSDData data;
		 /* ItemID of CSDData */
		 wxTreeItemId itemid;
		 /* Path */
		 wxString path;
		 /* CSD File */
		 wxString file;
		 /* Filename */
		 wxString filename;
	 };
   struct impldata
   {
		/* Implementation */
	   Qedo::Implementation implementation;
	   /* ItemId of Implementation */
	   wxTreeItemId itemid;

   };


   std::vector <impldata> implementations;
   std::vector <ctrldata> ctrldatas;

   ctrldata ComponentTreeCtrl::get_CtrData(wxTreeItemId itemid);
    
};
