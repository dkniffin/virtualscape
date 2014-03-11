#pragma once
#include "afxcmn.h"


// CLaunchDiceDlg dialog

class CLaunchDiceDlg : public CDialog
{
	DECLARE_DYNAMIC(CLaunchDiceDlg)

public:
	// The constructor
	CLaunchDiceDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CLaunchDiceDlg();

// Dialog Data
	enum { IDD = IDD_GET_DICE_RESULT };

protected:
	// Synchronise members and control value
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CSpinButtonCtrl m_Sp_NumberResult;
	CSpinButtonCtrl m_Sp_DiceNumberToLaunch;
	virtual BOOL OnInitDialog();
	int m_i_DiceNumberToLaunch;
	int m_i_DiceNumberResult;
	BOOL m_b_ForceResult;
	afx_msg void OnBnClickedBtLaunchDice();
};
