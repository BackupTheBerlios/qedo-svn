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


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "qxml.h"
#include "qedoutil.h"
#include "Package.h"
#include "CSDReader4qxml.h"
#include "CSDStruc4qxml.h"
#include "ViewCADDialog.h"
#include "wx/utils.h"
#include "wx/file.h"
#include "wx/process.h"
////@end includes

////@begin XPM images

////@end XPM images

/*!
 * MyDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( MyDialog, wxDialog )


/*!
 * MyDialog event table definition
 */

BEGIN_EVENT_TABLE( MyDialog, wxDialog )

////@begin MyDialog event table entries
    EVT_BUTTON( B_EXIT, MyDialog::OnButtonClick )
	EVT_BUTTON( Badd_ComponentP, MyDialog::OnAdd_Comp )
	EVT_BUTTON( ID_BUTTON_VC, MyDialog::OnButtton_VC)
	EVT_BUTTON( ID_BUTTON2, MyDialog::OnButton_GA)
	
	

////@end MyDialog event table entries

END_EVENT_TABLE()
/*
BEGIN_EVENT_TABLE(ComponentTreeCtrl,wxTreeCtrl)
	EVT_RIGHT_DOWN(MyDialog::OnItem)
END_EVENT_TABLE()
*/
/*!
 * MyDialog constructors
 */


MyDialog::MyDialog( )
{
}

MyDialog::MyDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

/*!
 * MyDialog creator
 */

bool MyDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MyDialog member initialisation
////@end MyDialog member initialisation

////@begin MyDialog creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end MyDialog creation
	//Show();
    return TRUE;
}

/*!
 * Control creation for MyDialog
 */

void MyDialog::CreateControls()
{    
////@begin MyDialog content construction

    MyDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("ComponentPackages"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxALIGN_TOP|wxALL, 5);

    cp_TreeCtrl = new ComponentTreeCtrl( itemDialog1, ID_TREECTRL, wxDefaultPosition, wxSize(400, 306), wxTR_SINGLE );
    itemStaticBoxSizer3->Add(cp_TreeCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	

    wxButton* itemButton5 = new wxButton( itemDialog1, Badd_ComponentP, _("Add ComponentPackages"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer3->Add(itemButton5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer6Static = new wxStaticBox(itemDialog1, wxID_ANY, _("General"));
    wxStaticBoxSizer* itemStaticBoxSizer6 = new wxStaticBoxSizer(itemStaticBoxSizer6Static, wxVERTICAL);
    itemStaticBoxSizer3->Add(itemStaticBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	
    wxButton* itemButton7 = new wxButton( itemDialog1, ID_BUTTON2, _("Generate Assembly Package"), wxDefaultPosition, wxSize(200,20), 0 );
    itemStaticBoxSizer6->Add(itemButton7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxButton* viewCAD = new wxButton( itemDialog1, ID_BUTTON_VC, _("View CAD"), wxDefaultPosition, wxSize(200,20), 0 );
    itemStaticBoxSizer6->Add(viewCAD, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton8 = new wxButton( itemDialog1, ID_BUTTON3, _("Help"), wxDefaultPosition, wxSize(200,20), 0 );
    itemStaticBoxSizer6->Add(itemButton8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton9 = new wxButton( itemDialog1, B_EXIT, _("Exit"), wxDefaultPosition, wxSize(200,20), 0 );
    itemStaticBoxSizer6->Add(itemButton9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemStaticBoxSizer6->Add(200, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer11Static = new wxStaticBox(itemDialog1, wxID_ANY, _("AssemblyView"));


    wxStaticBoxSizer* itemStaticBoxSizer11 = new wxStaticBoxSizer(itemStaticBoxSizer11Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	 wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemStaticBoxSizer11->Add(itemBoxSizer12, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer12->Add(itemBoxSizer13, 0, wxALIGN_LEFT|wxALL, 5);

	wxStaticText* itemStaticText14 = new wxStaticText( itemDialog1, wxID_STATIC, _("AssemblyID:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add(itemStaticText14, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    assemblyid = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add(assemblyid, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	/*
    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer12->Add(itemBoxSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
*/
	/*
    wxStaticText* itemStaticText17 = new wxStaticText( itemDialog1, wxID_STATIC, _("Static text"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(itemStaticText17, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxTextCtrl* itemTextCtrl18 = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(itemTextCtrl18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	*/
    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Components:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 5);

    a_TreeCtrl = new AComponentTreeCtrl( itemDialog1, ID_TREECTRL1, wxDefaultPosition, wxSize(350, 125), wxTR_SINGLE );
    itemStaticBoxSizer11->Add(a_TreeCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	cp_TreeCtrl->setdummy(a_TreeCtrl);

    wxStaticLine* itemStaticLine14 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxSize(350, -1), wxLI_HORIZONTAL );
    itemStaticBoxSizer11->Add(itemStaticLine14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemDialog1, wxID_STATIC, _("Partioning"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer11->Add(itemStaticText15, 0, wxALIGN_LEFT|wxALL|wxADJUST_MINSIZE, 5);

    p_TreeCtrl = new PartitioningTreeCtrl( itemDialog1, ID_TREECTRL3, wxDefaultPosition, wxSize(350, 125), wxTR_SINGLE );
    itemStaticBoxSizer11->Add(p_TreeCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    p_TreeCtrl->setdummy(a_TreeCtrl);

    //wxButton* itemButton17 = new wxButton( itemDialog1, Badd_Part, _("Add new Partioning element"), wxDefaultPosition, wxDefaultSize, 0 );
    //itemStaticBoxSizer11->Add(itemButton17, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticLine* itemStaticLine18 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxSize(350, -1), wxLI_HORIZONTAL );
    itemStaticBoxSizer11->Add(itemStaticLine18, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText19 = new wxStaticText( itemDialog1, wxID_STATIC, _("Connections:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer11->Add(itemStaticText19, 0, wxALIGN_LEFT|wxADJUST_MINSIZE, 5);

    c_TreeCtrl = new ConnectionTreeCtrl( itemDialog1, ID_TREECTRL2, wxDefaultPosition, wxSize(350, 125), wxTR_SINGLE );
    itemStaticBoxSizer11->Add(c_TreeCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	c_TreeCtrl->setdummy(p_TreeCtrl);

    //wxButton* itemButton21 = new wxButton( itemDialog1, Badd_con, _("Add new connection"), wxDefaultPosition, wxDefaultSize, 0 );
    //itemStaticBoxSizer11->Add(itemButton21, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	

////@end MyDialog content construction
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void MyDialog::OnButtonClick( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in MyDialog.
    // Before editing this code, remove the block markers.
	this->EndModal(wxID_OK);
	event.Skip();
	
    
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON in MyDialog. 
}

void MyDialog::OnAdd_Comp( wxCommandEvent& event )
{
	wxString file; // Full path+file
	wxString path; // only path without file
	
	wxString default_dir = "";
	wxString default_file = "";
	wxFileDialog* file_dialog=new wxFileDialog(this, "Choose a componentfile", default_dir, default_file, "*.zip", 0, wxDefaultPosition);
	int t=file_dialog->ShowModal();
	
	
	if (t==wxID_OK) {
		file=file_dialog->GetPath();
		path=file_dialog->GetDirectory();

		cp_TreeCtrl->add_component_package(file,path);
		
	}
	file_dialog->~wxFileDialog();
		
}




/*!
 * Should we show tooltips?
 */

bool MyDialog::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap MyDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MyDialog bitmap retrieval
    return wxNullBitmap;
////@end MyDialog bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon MyDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MyDialog icon retrieval
    return wxNullIcon;
////@end MyDialog icon retrieval
}

void MyDialog::OnItem(wxTreeEvent& event) 
{
	wxLogMessage("Rechte Maustaste");
	if (!(cp_TreeCtrl->GetItemText(cp_TreeCtrl->GetSelection()).empty())) 
	{
		if (cp_TreeCtrl->GetSelection()!=cp_TreeCtrl->GetRootItem())
		{
			wxMenu *test = new wxMenu("",0);
			test->Append(ID_MENU_IOR,"Show IOR","shows the IOR in the message box",TRUE);
			test->AppendSeparator();
			wxString mes="delete ";
			mes.Append(cp_TreeCtrl->GetItemText(cp_TreeCtrl->GetSelection()));

			test->Append(ID_MENU_DELETE,mes.c_str(),"delete this entry",TRUE);
	
			cp_TreeCtrl->PopupMenu(test,10,20);
		}
	}

}


wxString MyDialog::getOutputText()
{
	char a='"';
	wxString tab="	";
	wxString output;
	output.Append ("<?xml version = '1.0' ?> \n");
	output.Append ("<!DOCTYPE componentassembly PUBLIC ");
	output.Append (a);
	output.Append ("-//OMG//DTD Component Assembly Descriptor");
	output.Append (a);
	output.Append (" ");
	output.Append (a);
	output.Append ("http://cif.sourceforge.net/componentassembly.dtd");
	output.Append (a);
	output.Append ("> \n \n");
	output.Append ("<componentassembly id=");
	output.Append (a);
	output.Append (assemblyid->GetValue() );
	output.Append (a);
	output.Append ("> \n");
	output.Append (tab);
	output.Append ("<description></description>\n");

	output.Append ("\n");

	// COMPONENTFILES
	output.Append (tab);
	output.Append ("<componentfiles>\n");
	output.Append (a_TreeCtrl->getCADData());
	output.Append (tab);
	output.Append ("</componentfiles>\n");

	output.Append ("\n");

	// PARTITIONING
	output.Append (tab);
	output.Append ("<partitioning>\n");
	output.Append (p_TreeCtrl->getCADData());
	output.Append (tab);
	output.Append ("</partitioning>\n");

	output.Append ("\n");

	// CONNECTIONS
	output.Append (tab);
	output.Append ("<connections>\n");
	output.Append (c_TreeCtrl->getCADData());
	output.Append (tab);
	output.Append ("</connections>\n");

	output.Append ("</componentassembly>");

	return output;
}


void MyDialog::OnButtton_VC( wxCommandEvent& event )
{
	ViewCADDialog* vc = new ViewCADDialog(this,-1,"View CAD",wxDefaultPosition,wxSize(600,400));
	
	wxString outputtext=getOutputText();
	vc->textctrl->WriteText (outputtext);
	
	if (vc->ShowModal()==wxID_OK) { 
	}
	vc->~ViewCADDialog();
}

void MyDialog::OnButton_GA(wxCommandEvent& event )
{
	wxString aid=assemblyid->GetValue();
	if (aid.IsEmpty()) 
	{
		wxLogMessage("Sorry, you have to specify an AssemblyID !");
	} else {
	wxFileDialog* file_dialog=new wxFileDialog(this,"Save AssemblyPackage as...","","","*.zip",wxSAVE,wxDefaultPosition);
	int t=file_dialog->ShowModal();
	
	wxString file;
	wxString path;
	wxString filename;
	if (t==wxID_OK) {
		
		file=file_dialog->GetPath();
		path=file_dialog->GetDirectory();
		filename=file_dialog->GetFilename();
		
		wxString current_directory=wxGetCwd();
		std::vector <AComponentTreeCtrl::fileinfo> filelist=a_TreeCtrl->getFiles();

		std::vector <AComponentTreeCtrl::fileinfo> ::iterator iter;
		for(iter = filelist.begin(); 
		iter != filelist.end(); 
			iter++)
			{
				AComponentTreeCtrl::fileinfo finfo=(*iter);
				
				if (!(wxDirExists("tempqxml"))) 
				{
					wxMkdir("tempqxml");
				}
				//wxSetWorkingDirectory(current_directory.Append("tempqxml"));

				wxString temp="tempqxml/";
				
				wxCopyFile(finfo.link,temp.Append(finfo.filename), TRUE);

				
			}

			if (!(wxDirExists("tempqxml/meta-inf")))
			{
					wxMkdir("tempqxml/meta-inf");
			}
			
			// copy the instantiation properties fillearchives
			p_TreeCtrl->copy_filearchive("tempqxml/meta-inf");

			wxString cadfile="tempqxml/meta-inf/";
			cadfile.Append(filename);
			cadfile.Replace(".zip",".cad",TRUE);

			wxFile* outputfile = new wxFile(cadfile,wxFile::write);
			outputfile->Write(getOutputText().c_str(),wxConvLibc);
			outputfile->Close();

			wxString newDirectory=current_directory;
			newDirectory.Append("\\");
			newDirectory.Append("tempqxml");
			wxSetWorkingDirectory(newDirectory);
						
			//bool value;
			wxProcess *process = new wxProcess(this);
					
			wxString cmd = "zip -u  ";
			cmd.append(filename);
			cmd.append(" ");
			cmd.append("*.*");
	
			std::cout << cmd.c_str() << std::endl;
	
			wxExecute(cmd, wxEXEC_SYNC, NULL);
			cadfile.Replace("tempqxml/","",TRUE);
			wxString cmd2 = "zip -u ";
			cmd2.append(filename);
			cmd2.append(" ");
			cmd2.append("meta-inf/*.*");
			
			wxExecute(cmd2, wxEXEC_SYNC, NULL);
			delete process;
			
			wxCopyFile(filename,file, TRUE);
			
			wxRemoveFile(filename);

			for(iter = filelist.begin(); 
			iter != filelist.end(); 
			iter++)
			{
				AComponentTreeCtrl::fileinfo finfo=(*iter);
				
				wxRemoveFile(finfo.filename);
								
			}

			p_TreeCtrl->remove_files();
			wxRemoveFile(cadfile);
			wxRmdir("meta-inf");

			
			
	}

	file_dialog->~wxFileDialog();
	}
}