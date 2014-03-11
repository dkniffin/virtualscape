#pragma once
#include "afxcmn.h"

#include "Resource.h"

// CChooseLevelDlg dialog

class CChooseLevelDlg : public CDialog
{
	DECLARE_DYNAMIC(CChooseLevelDlg)

public:
	// The constructor
	CChooseLevelDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CChooseLevelDlg();

// Dialog Data
	enum { IDD = IDD_CHOOSELEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_Level;
	CSpinButtonCtrl m_Sp_Level;
	virtual BOOL OnInitDialog();
};
