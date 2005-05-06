#if !defined(AFX_PHILOSOPHERGUI_H__F2B72A24_FF35_4E21_AAEB_F7648927C105__INCLUDED_)
#define AFX_PHILOSOPHERGUI_H__F2B72A24_FF35_4E21_AAEB_F7648927C105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhilosopherGUI.h : header file
//

class PhilosopherGUI;

#ifndef WIN32
#include "HU_Container.h"
#include CORBA_H
#include CORBA_STUB_HEADER(dinner_implied)
#else
#include <OB/CORBA.h>
//#include "dinner_implied.h"
#endif

#include "dinner_PhilosopherImpl.h"

/////////////////////////////////////////////////////////////////////////////
// PhilosopherGUI dialog

class PhilosopherGUI : public CDialog
{
// Construction
public:
	dinner::PhilosopherSessionImpl* philo;
	PhilosopherGUI(CWnd* pParent, dinner::PhilosopherSessionImpl* phil );
	PhilosopherGUI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PhilosopherGUI)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PhilosopherGUI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PhilosopherGUI)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHILOSOPHERGUI_H__F2B72A24_FF35_4E21_AAEB_F7648927C105__INCLUDED_)
