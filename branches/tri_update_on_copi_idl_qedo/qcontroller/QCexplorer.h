/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
/*                                                                         */
/* Copyright (C) 2002-2004 by the Qedo Team                                */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

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
        TreeCtrlIcon_Component,
        TreeCtrlIcon_ComponentSelected,
        TreeCtrlIcon_Home,
        TreeCtrlIcon_HomeSelected,
        TreeCtrlIcon_Container,
        TreeCtrlIcon_ContainerSelected,
        TreeCtrlIcon_ComponentServer,
        TreeCtrlIcon_ComponentServerSelected,
        TreeCtrlIcon_Node,
        TreeCtrlIcon_NodeSelected,
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
	void OnItem(wxMouseEvent& event);
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
