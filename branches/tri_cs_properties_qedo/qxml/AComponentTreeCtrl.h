/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
/*                                                                         */
/* Copyright (C) 2002-2005 by the Qedo Team                                */
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


#ifndef __ACOMPONENT_TREE_CTRL_H
#define __ACOMPONENT_TREE_CTRL_H


#include "wx/treectrl.h"
#include "CSDStruc4qxml.h"
//#include "PartitioningTreeCtrl.h"

////@begin control identifiers
#define ID_MENU_DELETE_AC 10210
#define ID_MENU_EDIT 10200
////@end control identifiers

class AComponentTreeCtrl : public wxTreeCtrl
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
    AComponentTreeCtrl(); 
	AComponentTreeCtrl( const AComponentTreeCtrl &s )  
		// copy ctor
        { m_nValue = s.m_nValue; }
	AComponentTreeCtrl& operator=( const AComponentTreeCtrl &s ) 
		// assignment operator
       { m_nValue = s.m_nValue; return *this; }

    AComponentTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);

	void add_implementation(Qedo::Implementation impl,wxString cid,
											wxString link,wxString filearchive,wxString filename);
	wxArrayString get_CompArray();
	Qedo::Implementation get_Implementation(wxString fileid);
	wxString getLink(wxString fileid);
	wxString getFilearchive(wxString fileid);
	wxString getCADData();

   struct ACData
   {
	   /* File ID */
	   wxString file_id;
	   /* Implementation */
	   Qedo::Implementation impl;
	   /* ItemID */
	   wxTreeItemId itemid;
	   /* Link */
	   wxString link;
	   /* CSD filearchive */
	   wxString filearchive ;
	   /* Filename */
	   wxString filename;
   };

   struct fileinfo
   {
	   /* Link */
	   wxString link;
	   /* Filename */
	   wxString filename;
   };

   
   std::vector <ACData> acdatas;

   std::vector <fileinfo> getFiles();
   
private:
   int m_imageSize;
   void AComponentTreeCtrl::CreateImageList(int size);
   short m_nValue;
   void OnItem(wxMouseEvent& event);
   wxTreeItemId get_CompId(wxTreeItemId itemid);
   
   

};

#endif
