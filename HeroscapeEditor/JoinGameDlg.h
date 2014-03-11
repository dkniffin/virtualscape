#pragma once

#include "resource.h"
#include "afxcmn.h"

class CJoinGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CJoinGameDlg)

public:
	// The ip address
	BYTE	m_Byte1, m_Byte2, m_Byte3, m_Byte4;

public:
	// The constructor
	CJoinGameDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CJoinGameDlg();
	// Set the IP and port
	void	SetIPAndPort( CString IP, int GamePort );

// Données de boîte de dialogue
	enum { IDD = IDD_JOINGAME };

protected:
	// Synchronize data between members and controls
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_IPAddress;
public:
	int m_ServerPort;
public:
	CString m_PlayerName;
public:
	CString m_Password;
public:
	afx_msg void OnBnClickedOk();
};
