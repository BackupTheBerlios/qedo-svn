
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

#ifndef _QEDOEDITOR_H
#define _QEDOEDITOR_H


#include "wx/button.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"

class QedoEditor : public wxDialog
{
public:
    QedoEditor(wxWindow *parent,wxString titel, wxString file);

    virtual ~QedoEditor();
	void on_save_file(wxCommandEvent& WXUNUSED(event));
	void on_close(wxCommandEvent& WXUNUSED(event));
	

private:
	

	wxTextCtrl* editctrl;
	wxButton* save;
	wxButton* cancel;

	wxString file;

	DECLARE_EVENT_TABLE()
};

#endif // _QEDOEDITOR_H

