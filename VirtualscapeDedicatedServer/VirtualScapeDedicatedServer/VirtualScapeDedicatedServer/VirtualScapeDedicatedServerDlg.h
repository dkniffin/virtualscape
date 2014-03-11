// VirtualScapeDedicatedServerDlg.h : fichier d'en-tête
//

#pragma once
#include "afxcmn.h"

#include "ConnexionSocket.h"
#include "MySocket.h"

// boîte de dialogue CVirtualScapeDedicatedServerDlg
class CVirtualScapeDedicatedServerDlg : public CDialog
{
	// The waiting connexion socket
	CConnexionSocket* m_pConnexionSocket;

// Construction
public:
	CVirtualScapeDedicatedServerDlg(CWnd* pParent = NULL);	// constructeur standard
	// Add a new server to the list
	void AddNewServer( CString GameName, CString GameLanguage, CString GPlayerName, CString GNewServerIP, int NewServerPort, int ServerType, CMySocket* pSocket );
	// Remove a server from the list
	void RemoveServer( CMySocket* pSocket );
	// Get the server list
	void GetServerList( CMySocket* pSocket );
	// A game begin
	void GameBegin( CMySocket* pSocket );
	// A game end
	void GameEnd( CMySocket* pSocket );

// Données de boîte de dialogue
	enum { IDD = IDD_VIRTUALSCAPEDEDICATEDSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CListCtrl m_ServerListCtrl;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
