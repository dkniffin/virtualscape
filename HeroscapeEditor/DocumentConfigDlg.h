#ifndef _DOCUMENTCONFIGDLG_H_
#define _DOCUMENTCONFIGDLG_H_

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

class CDocumentConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CDocumentConfigDlg)

//************
// The methods
//************
public:
	// The number of level by page
	int		m_NbLevelByPage;
	// To know if we must display grid or not
	BOOL	m_PrintingGrid;
	// The buffer for scenario
	char	m_ScenarioBuffScenario[100000];
	// The buffer position
	int		m_ScenarioBufferPos;
	// The write buffer position
	int		m_ScenarioWriteBufferPos;
	// The text color
	COLORREF m_ColorText;
	// The background color
	COLORREF m_ColorBack;

	CString m_BattleFieldName;
	CString m_Author;
	UINT m_PrintTransparency;
	CComboBox m_ComboLevelByPage;
	CSpinButtonCtrl m_Sp_PrintTransparency;
	CString m_PlayerNumber;
	CString m_Scenario;
	CRichEditCtrl m_re_Scenario;
	CString m_reScenario;

//************
// The members
//************
public:
	// The constructor
	CDocumentConfigDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CDocumentConfigDlg();
	// Read the data of the richedit text
	static DWORD CALLBACK MyStreamOutCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	// Write the data to the richedit ctrl
	static DWORD CALLBACK MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

// Dialog Data
	enum { IDD = IDD_CONFIG_DOC };

protected:
	// Synchronize data and members
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButtonBold();
public:
	afx_msg void OnBnClickedButtonUnderline();
public:
	afx_msg void OnBnClickedButtonItalic();
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnBnClickedButtonTextcolor();
public:
	afx_msg void OnBnClickedButtonBackcolor();
public:
	afx_msg void OnEnSelchangeRicheditScenario(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL m_PrintTileNumber;
	BOOL m_b_PrintStartAreaAsLevel;
};

#endif // #ifndef _DOCUMENTCONFIGDLG_H_