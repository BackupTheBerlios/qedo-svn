#ifndef __NS_BROWSER_H__
#define __NS_BROWSER_H__

#include "qcontroller.h"
//#include "wx/treebase.h"
#include "wx/treectrl.h"
#include "coss/CosNaming.h"


class NSBrowserTreeItemData : public wxTreeItemData
{
public:
    NSBrowserTreeItemData(const wxString& desc) : m_desc(desc) { }

    void ShowInfo(wxTreeCtrl *tree);
    const wxChar *GetDesc() const { return m_desc.c_str(); }

private:
    wxString m_desc;
};


class NSBrowserTreeCtrl : public wxTreeCtrl
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

    NSBrowserTreeCtrl() { }
    NSBrowserTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);
    virtual ~NSBrowserTreeCtrl();

private:
		int m_imageSize;
		CosNaming::NamingContext_var nameService;
		void CreateImageList(int size = 16);
		void build_tree();
		void AddItemsRecursively(const wxTreeItemId& idParent,
									 CosNaming::NamingContext_ptr context);
};

#endif
