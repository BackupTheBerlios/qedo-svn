#ifndef _DESCRIPTORFRAME_H
#define _DESCRIPTORFRAME_H

#include "wx/stattext.h"
#include "wx/treectrl.h"
#include "wx/sizer.h"
#include "wx/listbox.h"
#include "qcontroller.h"
#include "ConfigurationReader.h"
#include "AssemblyData.h"
#include "DestinationData.h"



class DescriptorFrame : public wxDialog
{
	public:
	/**
	 * Constructor: Creates a new DescriptorFrame
	 */

		DescriptorFrame(wxWindow *parent,wxString filename);

    /**
	 * Destructor
	 */

	 virtual ~DescriptorFrame() { };
	 
	 std::string file;	
	 std::string tmp_file;
	 std::string cadfile;
		
	 void OnComponents_to_Server(wxCommandEvent& WXUNUSED(event));
	 void OnComponents_to_Components(wxCommandEvent& WXUNUSED(event));
	 void OnSave_Settings(wxCommandEvent& WXUNUSED(event));
	 void OnQuit(wxCommandEvent& WXUNUSED(event));
	 void OnAllComponentsBack(wxCommandEvent& WXUNUSED(event));
	 void OnSave_as(wxCommandEvent& WXUNUSED(event));

	private:

		enum collocationtyp
		{
			hostcollocation,
			processcollocation,
			homeplacement
		};

		struct noDestinationInfo
		{
			wxTreeItemId itemid;
			int iter;
			collocationtyp typ;
		};

		struct DestinationInfo
		{
			wxTreeItemId itemid;
			wxString node;
			int iter;
			collocationtyp typ;
		};

		struct serverinfo
		{
			std::string servername;
			wxTreeItemId itemid;
		};

		

		std::vector <serverinfo> serverinfolist;
		std::vector <noDestinationInfo> noDestinationInfoList;
		std::vector <DestinationInfo> DestinationInfoList;

		wxString partitioning_str;

		void addServerActivators();
		void addHostcollocation();
		void addProccesscollocation();
		void addHomeplacement();

		void addProcesstoServer(Qedo::ProcessData process, wxTreeItemId itemId,int iter);
		void addProcesstoComponent(Qedo::ProcessData process,wxTreeItemId itemid, int iter);
		void addHometoComponent(Qedo::HomeInstanceData home,wxTreeItemId itemid, int iter);
		void addHometoServer(Qedo::HomeInstanceData home, wxTreeItemId itemid, int iter);
		void addHosttoServer(Qedo::HostData host,wxTreeItemId itemId,int iter);
		void addHosttoComponent(Qedo::HostData host, int iter);

		bool iskown(std::string node);
		bool isunkown_kown(wxString node);
		wxTreeItemId get_unkown_itemid(wxString node);

		wxString getNode(wxTreeItemId itemid);
		wxString edit_partit(wxString partit);

		bool DescriptorFrame::checkselections(wxTreeItemId item,int counter);
		wxTreeItemId getItemId(std::string node);

		void add_component_to_components(DestinationInfo DestInfo);
		void add_component_to_server(noDestinationInfo noDestInfo,wxTreeItemId itemid);

		void delete_nodestination(noDestinationInfo noDestInfo);
		void delete_destination(DestinationInfo DestInfo);

		wxString get_partitioning_str(wxString partit);

	
		wxString get_noDestination_str();
		wxString get_Destination_str();

		wxString get_homeplacement_text(Qedo::HomeInstanceData home,wxString node);
		wxString get_processcollocation_text(Qedo::ProcessData process,wxString node);
		wxString get_hostcollocation_text(Qedo::HostData host,wxString node);

		
		
		wxString get_hostcollocation_str(noDestinationInfo noDestInfo);
		wxString get_hostcollocation_str_d(DestinationInfo DestInfo);
		wxString get_homeplacement_str(noDestinationInfo noDestInfo);
		wxString get_homeplacement_str_d(DestinationInfo dest_iter);
		wxString get_processcollocation_str(noDestinationInfo noDestInfo);
		wxString get_processcollocation_str_d(DestinationInfo DestInfo);

		

		noDestinationInfo getLastParent(wxTreeItemId item);
		DestinationInfo getLastParent_server(wxTreeItemId item);

		void warningserver(wxString server);
		void save();
		bool into_zip(std::string cad,std::string zip);

		CORBA::ORB_var e_orb;
		CosNaming::NamingContext_var nameService;

		std::vector <Qedo::ProcessData> processdatas ;
		std::vector <Qedo::HomeInstanceData> homedatas;
		std::vector <Qedo::HostData> hostdatas;
		wxTreeItemId rootId;
		wxTreeItemId rootId2;
		wxStaticText *d_text;
		wxStaticText* file_text;
		wxTreeCtrl *component_list_;
		wxTextCtrl *tc;
		wxTreeCtrl *server_ctrl_;
		wxButton* components_to_server;
		wxButton* components_to_components;
		wxButton* all_components_to_components;
		wxButton* save_;
		wxButton* save_as_;
		wxButton* cancel_;
		
		// Functions for cad writing
		wxString componentproperties(wxString comp_prop);
		wxString destination(Qedo::DestinationData dest);
		wxString registerwithnaming(wxString naming);
		wxString rules(std::vector<Qedo::RuleData >	rules);
		wxString usagename(wxString usagename);

		DECLARE_EVENT_TABLE()


};

#endif _DESCRIPTORFRAME_H