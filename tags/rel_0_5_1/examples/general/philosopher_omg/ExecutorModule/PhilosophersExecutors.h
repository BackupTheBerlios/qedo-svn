// PhilosophersExecutors.h : main header file for the PHILOSOPHERSEXECUTORS DLL
//

#if !defined(AFX_PHILOSOPHERSEXECUTORS_H__8D6FC5A7_1984_42B8_A83B_AFAD5310720B__INCLUDED_)
#define AFX_PHILOSOPHERSEXECUTORS_H__8D6FC5A7_1984_42B8_A83B_AFAD5310720B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPhilosophersExecutorsApp
// See PhilosophersExecutors.cpp for the implementation of this class
//

class CPhilosophersExecutorsApp : public CWinApp
{
public:
	CPhilosophersExecutorsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhilosophersExecutorsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPhilosophersExecutorsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHILOSOPHERSEXECUTORS_H__8D6FC5A7_1984_42B8_A83B_AFAD5310720B__INCLUDED_)
