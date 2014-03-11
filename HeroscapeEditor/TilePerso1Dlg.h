#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTilePerso1Dlg dialog

class CTilePerso1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTilePerso1Dlg)
//************
// The members
//************
public:
	// The nb hex
	int		m_NbHex;
	// The current texture
	CString m_Texture;
	// The current side texture
	CString	m_TextureSide;
	// The 2D color
	COLORREF	m_Color2D;

//************
// The methods
//************
public:
	// The constructor
	CTilePerso1Dlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CTilePerso1Dlg();

// Dialog Data
	enum { IDD = IDD_TILEPERSO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
public:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cb_NbHex;
public:
	int m_NbDispo;
public:
	CSpinButtonCtrl m_sp_NbDispo;
public:
	CString m_Character;
public:
	CComboBox m_cb_Texture;
public:
	CComboBox m_cb_TextureSide;
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnBnClickedBtColor2d();
protected:
	virtual void OnOK();
};
