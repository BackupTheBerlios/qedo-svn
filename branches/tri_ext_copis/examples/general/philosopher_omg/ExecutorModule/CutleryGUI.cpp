// CutleryGUI.cpp : implementation file
//

#include "CutleryExecutor.h"
#include "CutleryGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCutleryGUI dialog


CCutleryGUI::CCutleryGUI(CWnd* pParent /*=NULL*/)
	: CDialog(CCutleryGUI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCutleryGUI)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	empty = TRUE;
	Create(IDD);
	SetWindowText ( "Fork" );
	ShowWindow(SW_SHOW);
}


void CCutleryGUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCutleryGUI)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCutleryGUI, CDialog)
	//{{AFX_MSG_MAP(CCutleryGUI)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCutleryGUI message handlers

void CCutleryGUI::OnPaint() 
{	
	CPaintDC dc(this); // device context for painting
	
	CBitmap empty_bmp,full_bmp, *poldbmp,*current_bmp;
	CDC memdc;
	
	// Load the bitmap resource
	empty_bmp.LoadBitmap( IDB_BITMAP7 );
	// Load the bitmap resource
	full_bmp.LoadBitmap( IDB_BITMAP8 );
	if (empty) current_bmp=&empty_bmp;
	else current_bmp=&full_bmp;
	// Create a compatible memory DC
	memdc.CreateCompatibleDC( &dc );
	
	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject( current_bmp );
	
	// Copy (BitBlt) bitmap from memory DC to screen DC
	dc.BitBlt( 10, 10, 160, 210, &memdc, 0, 0, SRCCOPY );
	
	memdc.SelectObject( poldbmp );
	
	// Do not call CDialog::OnPaint() for painting messages
}
