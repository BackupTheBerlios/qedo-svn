// ObserverGUI.cpp : implementation file
//

#include "PhilosophersExecutors.h"
#include "ObserverGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ObserverGUI dialog


ObserverGUI::ObserverGUI(CWnd* pParent /*=NULL*/)
	: CDialog(ObserverGUI::IDD, pParent)
{
	//{{AFX_DATA_INIT(ObserverGUI)
	//}}AFX_DATA_INIT
	
	Create(IDD);

	SetWindowText ( "Observer" );
	ShowWindow (SW_SHOW);
}


void ObserverGUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ObserverGUI)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ObserverGUI, CDialog)
	//{{AFX_MSG_MAP(ObserverGUI)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ObserverGUI message handlers

void ObserverGUI::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
