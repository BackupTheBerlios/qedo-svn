// PhilosopherGUI.cpp : implementation file
//

#include "PhilosophersExecutors.h"
#include "PhilosopherGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PhilosopherGUI dialog


PhilosopherGUI::PhilosopherGUI(CWnd* pParent, dinner::PhilosopherSessionImpl* phil )
	: CDialog(PhilosopherGUI::IDD, pParent)
{
	Create(IDD);
	philo = phil;
	SetWindowText ( phil -> name () );
	ShowWindow(SW_SHOW);
}


PhilosopherGUI::PhilosopherGUI(CWnd* pParent /*=NULL*/)
	: CDialog(PhilosopherGUI::IDD, pParent), philo(0)
{
	//{{AFX_DATA_INIT(PhilosopherGUI)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Create(IDD);
	ShowWindow(SW_SHOW);
}


void PhilosopherGUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PhilosopherGUI)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PhilosopherGUI, CDialog)
	//{{AFX_MSG_MAP(PhilosopherGUI)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PhilosopherGUI message handlers

void PhilosopherGUI::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBitmap thinking_bmp, eating_bmp, sleeping_bmp, hungry_bmp, dead_bmp, *poldbmp,*current_bmp;
	CDC memdc;
	
	// Load the bitmap resource
	thinking_bmp.LoadBitmap( IDB_BITMAP4 );
	// Load the bitmap resource
	eating_bmp.LoadBitmap( IDB_BITMAP3 );
	// Load the bitmap resource
	sleeping_bmp.LoadBitmap( IDB_BITMAP1 );
	// Load the bitmap resource
	hungry_bmp.LoadBitmap( IDB_BITMAP2 );
    // Load the bitmap resource
	dead_bmp.LoadBitmap( IDB_BITMAP5 );

    char windowText[256];
    strcpy(windowText, philo->name());
	if (philo -> status == DiningPhilosophers::THINKING)
    {
        strcat(windowText, " is thinking");
        SetWindowText(windowText);
        current_bmp=&thinking_bmp;
    }
	if (philo -> status == DiningPhilosophers::EATING)
    {
        strcat(windowText, " is eating");
        SetWindowText(windowText);
        current_bmp=&eating_bmp;
    }
	if (philo -> status == DiningPhilosophers::STARVING)
    {
        strcat(windowText, " is starving");
        SetWindowText(windowText);
        current_bmp=&sleeping_bmp;
    }
	if (philo -> status == DiningPhilosophers::HUNGRY)
    {
        strcat(windowText, " is hungry");
        SetWindowText(windowText);
        current_bmp=&hungry_bmp;
    }
    if (philo -> status == DiningPhilosophers::DEAD)
    {
        strcat(windowText, " is dead");
        SetWindowText(windowText);
        current_bmp=&dead_bmp;
    }

	// Create a compatible memory DC
	memdc.CreateCompatibleDC( &dc );
	
	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject( current_bmp );
	
	// Copy (BitBlt) bitmap from memory DC to screen DC
	dc.BitBlt( 10, 10, 160, 210, &memdc, 0, 0, SRCCOPY );
	
	memdc.SelectObject( poldbmp );

	// Do not call CDialog::OnPaint() for painting messages
}
