// JoinGameListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GlobalIHM.h"
#include "HeroscapeEditor.h"
#include "JoinGameListDlg.h"
#include "SocketMessageId.h"


// CJoinGameListDlg dialog

IMPLEMENT_DYNAMIC(CJoinGameListDlg, CDialog)

CJoinGameListDlg::CJoinGameListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinGameListDlg::IDD, pParent)
{

}

CJoinGameListDlg::~CJoinGameListDlg()
{
}

void CJoinGameListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PLAYER_NAME, m_PlayerName);
	DDX_Control(pDX, IDC_GAMELIST, m_ServerListCtrl);
}


BEGIN_MESSAGE_MAP(CJoinGameListDlg, CDialog)
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CJoinGameListDlg::OnHdnItemclickGamelist)
//ON_NOTIFY(HDN_ITEMCHANGED, 0, &CJoinGameListDlg::OnHdnItemchangedGamelist)
//ON_NOTIFY(LVN_ITEMACTIVATE, IDC_GAMELIST, &CJoinGameListDlg::OnLvnItemActivateGamelist)
//ON_NOTIFY(LVN_ODSTATECHANGED, IDC_GAMELIST, &CJoinGameListDlg::OnLvnOdstatechangedGamelist)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_GAMELIST, &CJoinGameListDlg::OnLvnItemchangedGamelist)
ON_BN_CLICKED(IDC_BUTTON1, &CJoinGameListDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CJoinGameListDlg message handlers

BOOL CJoinGameListDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	// Positionne toute les colonnes
	CString Str;
	Str.LoadStringW( IDS_SERVER_LIST_COLUMNS );
	CGlobalIHM::CreateColumnListCtrl( &m_ServerListCtrl, Str );

	int opt = 1;

	// Register this server to the dedicated Server
	theApp.m_pToDedicatedServerSocket = new CToDedicatedServerSocket();
	theApp.m_pToDedicatedServerSocket->Create();
	theApp.m_pToDedicatedServerSocket->SetSockOpt( SO_DONTLINGER, (const void*) &opt, sizeof( bool), SOL_SOCKET );
	if( theApp.m_pToDedicatedServerSocket->Connect(_T("88.186.169.121"),2811)==0 )
	{
		theApp.m_pToDedicatedServerSocket->SocketError();
		AfxMessageBox( _T("Unable to connect to dedicated server !") );
		OnCancel();
	}

	// Send information to the dedicated server
	theApp.m_pToDedicatedServerSocket->CreateBuffer();
	theApp.m_pToDedicatedServerSocket->SendMessageW( SMI_TODEDICATEDSERVER_GET_SERVER_LIST );

	return TRUE;
}

// Receive the server list
//
void CJoinGameListDlg::SetServerlist( CToDedicatedServerSocket* m_pSocket )
{
	m_ServerListCtrl.DeleteAllItems();

	int NbServer;
	m_pSocket->ReadType( NbServer );
	for( int i=0; i<NbServer; i++ )
	{
		CString Str, GameName, PlayerName, ServerIP, RulesType, Language;
		UINT ServerPort;
		int ServerType;
		m_pSocket->ReadType( GameName );
		m_pSocket->ReadType( Language );
		m_pSocket->ReadType( PlayerName );
		m_pSocket->ReadType( ServerIP );
		m_pSocket->ReadType( ServerPort );
		m_pSocket->ReadType( ServerType );
		if( ServerType==0 )
			RulesType.LoadStringW( IDS_BASICRULES );
		else
			RulesType.LoadStringW( IDS_EXPERTRULES );

		Str.Format( _T("%s;%s;%s;%i;%s;%s"), GameName, PlayerName, ServerIP, ServerPort, RulesType, Language );
		CGlobalIHM::AddListItem( &m_ServerListCtrl, Str, -1, -1 );
	}
}

void CJoinGameListDlg::OnLvnItemchangedGamelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if( m_ServerListCtrl.GetSelectedCount()>0 )
		GetDlgItem( IDOK )->EnableWindow();
	else
		GetDlgItem( IDOK )->EnableWindow(FALSE);

	*pResult = 0;
}

// Get the current selected ip address
//
CString CJoinGameListDlg::GetIPAddress()
{
	return m_IpAddress;
}

// Get the current selected port
//
int CJoinGameListDlg::GetPort()
{
	return m_Port;
}

// The user want join a game
//
void CJoinGameListDlg::OnOK()
{
	int Index = m_ServerListCtrl.GetSelectionMark();

	m_IpAddress = m_ServerListCtrl.GetItemText( Index, 2 );
	m_Port = _ttoi(static_cast<LPCTSTR>(m_ServerListCtrl.GetItemText( Index, 3 )));

	CDialog::OnOK();
}

void CJoinGameListDlg::OnBnClickedButton1()
{
	// Send information to the dedicated server
	theApp.m_pToDedicatedServerSocket->CreateBuffer();
	theApp.m_pToDedicatedServerSocket->SendMessageW( SMI_TODEDICATEDSERVER_GET_SERVER_LIST );
}
