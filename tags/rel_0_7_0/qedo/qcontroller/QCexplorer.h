#ifndef __QC_EXPLORER_H__
#define __QC_EXPLORER_H__

#include "qcontroller.h"
//#include "wx/treebase.h"
#include "wx/treectrl.h"


#include "coss/CosNaming.h"
#include "wx/notebook.h"
#include "wx/button.h"
#include "wx/string.h"
#include <vector>



class QCexplorerTreeItemData : public wxTreeItemData
{
public:
    QCexplorerTreeItemData(const wxString& desc) : m_desc(desc) { }

    void ShowInfo(wxTreeCtrl *tree);
    const wxChar *GetDesc() const { return m_desc.c_str(); }

private:
    wxString m_desc;
};


class QCexplorerTreeCtrl : public wxTreeCtrl
{
public:
    enum
    {
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
        TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened
    };

    QCexplorerTreeCtrl() { }
    QCexplorerTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);
    virtual ~QCexplorerTreeCtrl();
	void OnExplorerRefresh();
	void OnItem();
	void set_info_box(wxTextCtrl* info_box_ref);
	
	
	void clear();
	int e_argc;
	char** e_argv;
	wxString cmd_ns;
	//std::string ns;

	

private:
		wxButton *ERefreshBtn;
		wxButton *StartExplorerBtn;
		wxTextCtrl* info_box;

		int m_imageSize;
		CosNaming::NamingContext_var nameService;
		void CreateImageList(int size = 16);
		void build_tree();
		struct Info
		{ wxTreeItemId Item;
		  wxString Text;
		};
//		vector<Info> Infoliste;

		
	    DECLARE_EVENT_TABLE()

};

#endif
