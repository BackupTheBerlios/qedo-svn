#ifndef _CADREADERDIALOG_H
#define _CADREADERDIALOG_H


#include "wx/stattext.h"
#include "wx/treectrl.h"
#include "wx/sizer.h"
#include "wx/listbox.h"
#include "qcontroller.h"

#include "CADReader.h"
#include "AssemblyData.h"
#include "DestinationData.h"



class CadReaderDialogFrame : public wxDialog
{
	public:
	/**
	 * Constructor: Creates a new DescriptorFrame
	 */

	 CadReaderDialogFrame(wxWindow *parent,wxString filename, bool status);

    /**
	 * Destructor
	 */

	 virtual ~CadReaderDialogFrame() { };

	  void OnOK(wxCommandEvent& WXUNUSED(event));

	 std::string file;
	 std::string tmp_file;
	 std::vector <Qedo::ProcessData> processdatas;
	 std::vector <Qedo::HomeInstanceData> homedatas;
	 std::vector <Qedo::HostData> hostdatas;
	 Qedo::Partitioning partitioning;
	 bool ready;

	


	private:

		wxStaticText *d_text;
		wxButton* ok_;
		
		
	DECLARE_EVENT_TABLE()	


};

#endif _CADREADERDIALOGFRAME_H