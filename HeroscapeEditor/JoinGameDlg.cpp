// JoinGameDlg.cpp : fichier d'implémentation
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "JoinGameDlg.h"

IMPLEMENT_DYNAMIC(CJoinGameDlg, CDialog)

// The constructor
//
CJoinGameDlg::CJoinGameDlg(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CJoinGameDlg::IDD, pParent)
, m_ServerPort(0)
, m_PlayerName(_T(""))
, m_Password(_T(""))
{
}

// The destructor
//
CJoinGameDlg::~CJoinGameDlg()
{
}

// Synchronise data between members and controls
//
void CJoinGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVER_IP_ADDRESS, m_IPAddress);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT_PLAYER_NAME, m_PlayerName);
	DDX_Text(pDX, IDC_EDIT_GAME_PASSWORD, m_Password);
}

// Set the IP and port
//
void CJoinGameDlg::SetIPAndPort( CString IP, int GamePort )
{
	BYTE Byte1, Byte2, Byte3, Byte4;
	int Find1,Find2,Find3;
	Find1 = IP.Find('.');
	Find2 = IP.Find('.',Find1+1);
	Find3 = IP.Find('.',Find2+1);
	Byte1 = _wtoi(IP.Left(Find1));
	Byte2 = _wtoi(IP.Mid(Find1+1));
	Byte3 = _wtoi(IP.Mid(Find2+1));
	Byte4 = _wtoi(IP.Mid(Find3+1));
	m_IPAddress.SetAddress(Byte1,Byte2,Byte3,Byte4);
	m_ServerPort = GamePort;

	UpdateData(FALSE);
}

// Windows message mapping
//
BEGIN_MESSAGE_MAP(CJoinGameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CJoinGameDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// When the user validate
//
void CJoinGameDlg::OnBnClickedOk()
{
	m_IPAddress.GetAddress( m_Byte1, m_Byte2, m_Byte3, m_Byte4 );

	// Call the base class
	OnOK();
}
