#include "Deployment.h"
#include "qcontroller.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/statline.h"

#include "ComponentDeployment.h"


BEGIN_EVENT_TABLE(Deployment, wxPanel)
   EVT_BUTTON(ID_DEPLOY_BUTTON, Deployment::OnDeployButton)
 
END_EVENT_TABLE()

Deployment::Deployment(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxPanel(parent, id, pos, size, style)
{

    wxBoxSizer* item2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(item2);
    this->SetAutoLayout(TRUE);

    wxBoxSizer* item3 = new wxBoxSizer(wxVERTICAL);
    item2->Add(item3, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* item4 = new wxBoxSizer(wxHORIZONTAL);
    item3->Add(item4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxStaticText* item5 = new wxStaticText( this, wxID_STATIC, _T("Assembly\nLocation"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add(item5, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    assembly_name_ = new wxTextCtrl( this, ID_ASSNAME_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(300, -1), 0 );
    item4->Add(assembly_name_, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    file_choice_btn = new wxButton( this, ID_FILE_CHOICE_BUTTON, _T("Choose File"), wxDefaultPosition, wxDefaultSize, 0 );
    item4->Add(file_choice_btn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* item8 = new wxBoxSizer(wxHORIZONTAL);
    item3->Add(item8, 0, wxALIGN_LEFT|wxALL, 0);

    deploy_btn = new wxButton( this, ID_DEPLOY_BUTTON, _T("Deploy"), wxDefaultPosition, wxDefaultSize, 0 );
    item8->Add(deploy_btn, 0, wxGROW|wxALL, 5);

    wxStaticLine* item10 = new wxStaticLine( this, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    item2->Add(item10, 0, wxGROW|wxALL, 5);

    wxBoxSizer* item11 = new wxBoxSizer(wxVERTICAL);
    item2->Add(item11, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* item12 = new wxBoxSizer(wxHORIZONTAL);
    item11->Add(item12, 0, wxALIGN_LEFT|wxALL, 0);

    wxStaticText* item13 = new wxStaticText( this, wxID_STATIC, _T("Running \nAssemblies"), wxDefaultPosition, wxDefaultSize, 0 );
    item12->Add(item13, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxADJUST_MINSIZE, 5);

    wxListCtrl* running_ass_list = new wxListCtrl( this, ID_RUNNING_LISTCTRL, wxDefaultPosition, wxSize(400, 100), 0 );
    item12->Add(running_ass_list, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* undeploy_btn = new wxButton( this, ID_UNDEPLOY_BUTTON, _T("Undeploy"), wxDefaultPosition, wxDefaultSize, 0 );
    item11->Add(undeploy_btn, 0, wxALIGN_LEFT|wxALL, 5);

}

void 
Deployment::OnDeployButton(wxCommandEvent& WXUNUSED(event))
{
	std::string package;
	package = "file:///c:/devel/berlios_cvs/Main_test/examples/general/hello_world/hello_win32_assembly.zip";


		//
	// init ORB
	//
	int dummy=0;
	CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);

	//
	// Register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb -> register_value_factory ( "IDL:omg.org/Components/Cookie:1.0", factory );

	//
	// deploy the assembly
	//
	Qedo::ComponentDeployment ass(package);
	try
	{
		std::cerr << "..... deploy " << package << std::endl;
		ass.deploy();
	}
	catch(Qedo::ComponentDeployment::DeploymentFailure&)
	{
		std::cerr << "Cannot deploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "Cannot deploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}

	// this code has to be moved
	try
	{
		ass.undeploy();
	}
	catch(Qedo::ComponentDeployment::DeploymentFailure&)
	{
		std::cerr << "Cannot undeploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "Cannot undeploy " << package << std::endl;
	//	orb->destroy();
	//	exit(1);
	}


}

