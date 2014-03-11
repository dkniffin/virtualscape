#pragma once
#include "afxcmn.h"


// CProgressDlg dialog

class CProgressDlg : public CDialog
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	// The constructor
	CProgressDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CProgressDlg();

// Dialog Data
	enum { IDD = IDD_PROGRESS };

protected:
	// Synchronize data between control and members
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_ProgressBar;
};
