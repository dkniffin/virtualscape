#ifndef _TILEPERSODLG_H_
#define _TILEPERSODLG_H_

#include "resource.h"
#include "afxcmn.h"

// CTilePersoDlg dialog

class CTilePersoDlg : public CDialog
{
	DECLARE_DYNAMIC(CTilePersoDlg)

public:
	// The constructor
	CTilePersoDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CTilePersoDlg();

// Dialog Data
	enum { IDD = IDD_TILEPERSOLIST };

protected:
	// Synchronize data and members
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CListCtrl m_lc_TileList;
public:
	afx_msg void OnBnClickedButtonAddtileperso();
public:
	afx_msg void OnBnClickedButtonRemove();
public:
	afx_msg void OnBnClickedButtonModify();
};

#endif // #ifndef _TILEPERSODLG_H_