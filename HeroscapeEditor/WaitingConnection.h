#pragma once

#include "AfxCmn.h"

#include "GameDoc.h"
#include "Resource.h"
#include "afxwin.h"

// CWaitingConnection Dialog

class CWaitingConnection : public CDialog
{
	DECLARE_DYNAMIC(CWaitingConnection)

//************
// The members
//************
public:
	// The game document
	CGameDoc*	m_pGameDoc;
	// The player list control
	CListCtrl	m_PlayerList;
	// The watcher list control
	CListCtrl	m_WatcherList;
	// To know if this is the dialog box for server or client
	bool		m_IsServer;
	// The message list
	CString		m_ChatMessageList;

//************
// The methods
//************
public:
	// The constructor
	CWaitingConnection(CWnd* pParent = NULL);
	// The destructor
	virtual ~CWaitingConnection();
	// The dialog is initialize
	virtual BOOL	OnInitDialog();
	// Refresh the players list
	void			RefreshPlayersList();
	// Add a message receive from other players
	void			AddMessage( int FromIndex, CString From, CString Message );
	// Set the BattleField name
	void			SetBattleFieldName( CString BattleFieldName );
	// Set the player max for this game
	void			SetPlayerMax( int PlayerMax );
	// Set the game point for this game
	void			SetGamePoint( int GamePoint );
	// Cancel the connexion
	void			Cancel();

	// Données de boîte de dialogue
	enum { IDD = IDD_WAITINGPLAYERS };

protected:
	// Synchronize members and control
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSendMessage();
public:
	CString m_MessageText;
public:
	CString m_BattleFieldName;
public:
	CString m_PlayerMax;
public:
	CString m_GamePoint;
public:
	virtual void OnOK();
public:
	CButton m_ButtonLaunch;
public:
	CRichEditCtrl m_ChatList;
public:
	CString m_ChatText2;
};
