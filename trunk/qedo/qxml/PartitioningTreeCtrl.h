#ifndef __PARTITIONING_TREE_CTRL_H
#define __PARTITIONING_TREE_CTRL_H



#include "wx/treectrl.h"
#include "CSDStruc4qxml.h"

#include "AComponentTreeCtrl.h"

////@begin control identifiers
#define ID_MENU_DELETE_P 10300
#define ID_MENU_ADD_P_P 10310
#define ID_MENU_ADD_P_H 10311
#define ID_MENU_ADD_P_HO 10312
#define ID_MENU_EDIT_P_U 10320
#define ID_MENU_ADD_P_C 10313
#define ID_MENU_ADD_P_C_I 10314

////@end control identifiers

class PartitioningTreeCtrl : public wxTreeCtrl
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
    PartitioningTreeCtrl(); 
	PartitioningTreeCtrl( const PartitioningTreeCtrl &s )  
		// copy ctor
        { m_nValue = s.m_nValue; }
	PartitioningTreeCtrl& operator=( const PartitioningTreeCtrl &s ) 
		// assignment operator
       { m_nValue = s.m_nValue; return *this; }

    PartitioningTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);

	void setdummy(AComponentTreeCtrl* atc);
	wxString getCADData();

	struct Instantiation
   {
	   /* ID */
	   wxString id;
	   /* filearchive */
	   wxString file;
	   /* Item Id*/
	   wxTreeItemId itemid;
   };

   struct Comp
   {
	   /* ItemID */
	   wxTreeItemId itemid;
	   /* component idref */
	   wxString idref;
	   /* link to file */
	   wxString link;
	   /* filearchive */
	   wxString filearchive;
	   /* implementation */
	   Qedo::Implementation impl;
	   /* instantiations */
	   std::vector <Instantiation> instantiations;	 
	   
	   
   };

	// get components for connections 
	std::vector <Comp> get_Comp4Con();
private:
   int m_imageSize;
   void PartitioningTreeCtrl::CreateImageList(int size);
   short m_nValue;
   AComponentTreeCtrl* ACTreeCtrl;
   void OnItem(wxMouseEvent& event);
   wxTreeItemId get_CompId(wxTreeItemId itemid);
   void onadd_p(wxMenuEvent& event);
   void onadd_ho(wxMenuEvent& event);
   void onadd_h(wxMenuEvent& event);
   void onadd_c(wxMenuEvent& event);
   void onadd_ci(wxMenuEvent& event);
   bool ExistsComp(wxTreeItemId itemid);

   wxString homedata(wxTreeItemId itemid);
   wxString hostdata(wxTreeItemId itemid);
   wxString processdata(wxTreeItemId itemid);

   wxString compdata(wxTreeItemId itemid);
   



   enum ElementType
   {
      inst,
      comp,
      process,
      home,
      host
   };

   struct ItemTyp
   {
	   /* ItemID */
	   wxTreeItemId itemid;
	   /* ElementTyp */;
	   ElementType type;
	   /* Usagename */
	   wxString usagename;
   };

   struct homeinfo
   {
	   /* Component */
	   Comp component;
   };

   struct processinfo
   {
	   /* processcollocation */
	   std::vector <homeinfo> homelist;
   };

   struct hostinfo
   {
	   /* processcollocation */
	   std::vector <processinfo> processlist;
	   /* homeplacement */
	   std::vector <homeinfo> homelist;
   };

   struct partiinfo
   {
	   /* processcollocation */
	   std::vector <processinfo> processlist;
	   /* hostcollocation */
	   std::vector <hostinfo> hostlist;
	   /* homeplacement */
	   std::vector <homeinfo> homeist;
   };


   std::vector <ItemTyp> itemtypes;
   std::vector <Comp> comps;

   partiinfo pinfo;

   ElementType GetType(wxTreeItemId itemid);
   ItemTyp GetItemInfo(wxTreeItemId itemid);
   Comp get_Comp(wxTreeItemId itemid);
   void replace_component(Comp component);

};

#endif