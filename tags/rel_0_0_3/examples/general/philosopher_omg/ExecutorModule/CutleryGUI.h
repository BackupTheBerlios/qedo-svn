#if !defined(AFX_CUTLERYGUI_H__401CC473_E7D1_4479_9A10_25A01FEA613E__INCLUDED_)
#define AFX_CUTLERYGUI_H__401CC473_E7D1_4479_9A10_25A01FEA613E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CutleryGUI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCutleryGUI dialog

class CCutleryGUI : public CDialog
{
// Construction
public:
	BOOL empty;
	CCutleryGUI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCutleryGUI)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCutleryGUI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCutleryGUI)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUTLERYGUI_H__401CC473_E7D1_4479_9A10_25A01FEA613E__INCLUDED_)
