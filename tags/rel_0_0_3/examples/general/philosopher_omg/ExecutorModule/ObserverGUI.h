#if !defined(AFX_OBSERVERGUI_H__F4B60E10_DDAA_4A33_8F03_6041335D1824__INCLUDED_)
#define AFX_OBSERVERGUI_H__F4B60E10_DDAA_4A33_8F03_6041335D1824__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObserverGUI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ObserverGUI dialog

class ObserverGUI : public CDialog
{
// Construction
public:
	ObserverGUI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ObserverGUI)
	enum { IDD = IDD_DIALOG1 };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ObserverGUI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ObserverGUI)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBSERVERGUI_H__F4B60E10_DDAA_4A33_8F03_6041335D1824__INCLUDED_)
