#include "wx/treectrl.h"
#include "CSDStruc4qxml.h"
#include "CCDStruc4qxml.h"

#include "PartitioningTreeCtrl.h"

////@begin control identifiers
#define ID_MENU_ADD_C_C 10400
#define ID_MENU_ADD_C_E 10401
#define ID_MENU_ADD_C_B 10402
#define ID_MENU_ADD_C_NS 10403
#define ID_MENU_DELETE_C 10410


////@end control identifiers

class ConnectionTreeCtrl : public wxTreeCtrl
{
	DECLARE_EVENT_TABLE()

private:
	/** the temporary path for extrating data from zip files */
	std::string m_temp_path;

public:
    enum
    {	
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
		TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened
    };
    ConnectionTreeCtrl(); 
	ConnectionTreeCtrl( const ConnectionTreeCtrl &s )  
		// copy ctor
        { m_nValue = s.m_nValue; }
	ConnectionTreeCtrl& operator=( const ConnectionTreeCtrl &s ) 
		// assignment operator
       { m_nValue = s.m_nValue; return *this; }

    ConnectionTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);

	void setdummy(PartitioningTreeCtrl* ptc);
	void OnItem(wxMouseEvent& event);
	wxString getCADData();
	

	struct ConPort
	{
		/* Portname */
		wxString	portname;
		/* component instantiation */
		wxString	idref;
	};

	struct Connect
	{
		/* Port 1 */
	  ConPort port1;
		/* Port 2 */
	  ConPort port2;
	
	};

	struct NS_Connect
	{
		/** Port1 receptacle */
		ConPort port1;

		/** NameService NameContext */
		wxString ns_context;
	};

	struct Connection
	{
		/* Stream Bindings */
		std::vector <Connect> bindings;

		/* Event connections */
		std::vector <Connect> events;

		/* Interface connections */
		std::vector <Connect> interfaces;

		/** NameService connections */
		std::vector <NS_Connect> ns_connections;

	};

	Connection connections;

	wxString getConnection(Connect c, wxString Typ);
	wxString getNSConnection(NS_Connect c);

private:
   int m_imageSize;
   void ConnectionTreeCtrl::CreateImageList(int size);
   short m_nValue;
   PartitioningTreeCtrl* PTreeCtrl;
   wxTreeItemId get_CompId(wxTreeItemId itemid);
   void get_portinformation(std::vector <PartitioningTreeCtrl::Comp> components);

//   std::vector <PartititioningTreeCtrl::Comp> componentlist;
   bool isEvent(std::vector <PartitioningTreeCtrl::Comp> components);
   bool isStream(std::vector <PartitioningTreeCtrl::Comp> components);
   bool isInterface(std::vector <PartitioningTreeCtrl::Comp> components);
   bool isReceptacle(std::vector <PartitioningTreeCtrl::Comp> components);

   void onadd_b(wxMenuEvent& event);
   void onadd_c(wxMenuEvent& event);
   void onadd_e(wxMenuEvent& event);
   void onadd_ns(wxMenuEvent& event);
   
   wxArrayString getSourceports();
   wxArrayString getSinkports();

   wxArrayString getProvideports();
   wxArrayString getUseports();

   wxArrayString getPublishports();
   wxArrayString getConsumeports();


   struct CPort
   {
	   /* Component idref */
	   wxString idref;
	   /* instantiations */
	   std::vector <PartitioningTreeCtrl::Instantiation> instantiations;
	   /* ports */
	   Qedo::CCDData ccddata;
   };

   std::vector <CPort> cports;


   

};