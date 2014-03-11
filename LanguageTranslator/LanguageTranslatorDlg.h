// LanguageTranslatorDlg.h : header file
//

#if !defined(AFX_LANGUAGETRANSLATORDLG_H__D1B98DD7_D342_4449_B447_016F4C0ACD8C__INCLUDED_)
#define AFX_LANGUAGETRANSLATORDLG_H__D1B98DD7_D342_4449_B447_016F4C0ACD8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLanguageTranslatorDlg dialog

class CLanguageTranslatorDlg : public CDialog
{
CMapStringToString m_TranslateTable;

// Construction
public:
	CLanguageTranslatorDlg(CWnd* pParent = NULL);	// standard constructor
	// Load the translator file
	void	LoadTranslatorFile();
	// Traduct the file
	void	TraductFile();


// Dialog Data
	//{{AFX_DATA(CLanguageTranslatorDlg)
	enum { IDD = IDD_LANGUAGETRANSLATOR_DIALOG };
	CListBox	m_cb_Log;
	CString	m_cs_OriginFile;
	CString	m_cs_DestinationFile;
	CString	m_cs_TraductionFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLanguageTranslatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLanguageTranslatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonTraduction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANGUAGETRANSLATORDLG_H__D1B98DD7_D342_4449_B447_016F4C0ACD8C__INCLUDED_)
