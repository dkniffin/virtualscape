#pragma once
#include "afxcmn.h"
#include "ToDedicatedServerSocket.h"

// CJoinGameListDlg dialog

class CJoinGameListDlg : public CDialog
{
	DECLARE_DYNAMIC(CJoinGameListDlg)
public:
	CString m_PlayerName;
	CString m_IpAddress;
	int		m_Port;

public:
	// The constructor
	CJoinGameListDlg(CWnd* pParent = NULL);
	// The destructor
	virtual ~CJoinGameListDlg();
	// Receive the server list
	void SetServerlist( CToDedicatedServerSocket* m_pSocket );
	// Get the current selected ip address
	CString GetIPAddress();
	// Get the current selected port
	int GetPort();

	// Dialog Data
	enum { IDD = IDD_JOINLISTGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ServerListCtrl;
//	afx_msg void OnHdnItemclickGamelist(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnHdnItemchangedGamelist(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnItemActivateGamelist(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnOdstatechangedGamelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedGamelist(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
};
