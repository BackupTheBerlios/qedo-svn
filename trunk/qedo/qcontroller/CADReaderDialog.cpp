// For compilers that supports precompilation , includes "wx/wx.h"
#include "wx/wxprec.h"

/*
#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif
*/
#include "CADReaderDialog.h"
#include "wx/sizer.h"
#include "wx/listctrl.h"
#include "wx/statline.h"
#include "package.h"

BEGIN_EVENT_TABLE(CadReaderDialogFrame, wxDialog)
	EVT_BUTTON(ID_OK_READING, CadReaderDialogFrame::OnOK)
END_EVENT_TABLE()

CadReaderDialogFrame::CadReaderDialogFrame(wxWindow *parent, wxString filename,bool status) 
			: wxDialog(parent, -1, "Reading CAD File...", wxDefaultPosition,
					   wxSize(300,100),wxDEFAULT_DIALOG_STYLE)
{
	wxBoxSizer *sizerLauncher = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizerLauncher);
    this->SetAutoLayout(TRUE);
	this->file=filename.c_str();
	this->ready=status;


	//spacer
	sizerLauncher->Add(5, 5, 0, wxGROW | wxALL, 5);

	// static text 
	wxStaticText* dialog_text = new wxStaticText( this, wxID_STATIC, _T("Reading CAD File, wait a moment..."), wxDefaultPosition, wxDefaultSize, 0 );
    sizerLauncher->Add(dialog_text , 0, wxALIGN_CENTER |wxALL|wxADJUST_MINSIZE, 5);

	ok_ = new wxButton(this, ID_OK_READING, _T("OK"));
	sizerLauncher->Add(ok_ , 0, wxALIGN_CENTER|wxALL|wxADJUST_MINSIZE, 5);


	// extract CADFile
	std::string package_;
	
	package_=""; 
	wxString tmp_string;
	
	tmp_string=this->file.c_str();
	tmp_string.Replace ("\\","/");
	
	package_.append(tmp_string );
	Qedo::Package *package = new Qedo::Package(package_);
	std::string cadfile_name = package->getFileNameWithSuffix( ".cad" );
	if (cadfile_name=="") {
		
		wxLogMessage("Cannot find CAD File");

	} else {
		wxString label;
		label="Find ";
		label.append(cadfile_name.c_str());
		label.append(", wait a moment...");
		dialog_text->SetLabel(label );
		
		tmp_file="temp_@";
		
		tmp_file.append(Qedo::getFileName(cadfile_name));
		
		
		if (package->extractFile(cadfile_name, tmp_file)!=0) {
			wxLogMessage("Error by extracting");
		} else {
			
			Qedo::CADReader *cadreader = new Qedo::CADReader;

			file=Qedo::getFileName(cadfile_name);

			partitioning=cadreader->getPartitioning(tmp_file);
			
			processdatas=cadreader->getProcesscollocations(tmp_file);

			homedatas=cadreader->getHomeplacements(tmp_file);

			hostdatas=cadreader->getHostcollocations(tmp_file);
			
		}
	}
	
	//dialog_text->SetLabel("Reading CAD File. Ready !");
	ready=true;
	//wxEvtHandler *test=this->GetEventHandler();
	//this->ProcessEvent(wxID_CANCEL);
	
	
}

void CadReaderDialogFrame::OnOK(wxCommandEvent& WXUNUSED(event))
{
	this->EndModal(wxID_OK);
}

