#pragma once

#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"

// CCreateGameDlg dialog

class CCreateGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateGameDlg)


public:
	// The constructor
	CCreateGameDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CCreateGameDlg();
	// The dialog bos is initialise
	virtual BOOL OnInitDialog();

	// Données de boîte de dialogue
	enum { IDD = IDD_CREATEGAME };

protected:
	// Synchronize members and control
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	CSpinButtonCtrl m_SpinPlayerMax;
	int m_PlayerMax;
	CSpinButtonCtrl m_SpinWatcherMax;
	int m_WatcherMax;
	CSpinButtonCtrl m_SpinGamePoint;
	int m_GamePoint;
	CSpinButtonCtrl m_SpinPort;
	int m_ServerPort;
	CString m_GameName;
	int m_GameType;
	CString m_GamePassword;
	CString m_WelcomeMessage;
public:
	CString m_PlayerName;
protected:
	virtual void OnOK();
public:
	CEdit m_Ed_PlayerName;
public:
	CEdit m_Ed_GameName;
public:
	CEdit m_Ed_GamePoint;
public:
	CEdit m_Ed_PlayerMax;
	CString m_IP_Address;
	CString m_Game_Language;
};
