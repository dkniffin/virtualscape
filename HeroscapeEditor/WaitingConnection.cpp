// WaitingConnection.cpp : fichier d'implémentation
//

#include "StdAfx.h"

#include "GlobalIHM.h"
#include "HeroscapeEditor.h"
#include "SocketMessageId.h"
#include "WaitingConnection.h"

// Boîte de dialogue CWaitingConnection

IMPLEMENT_DYNAMIC(CWaitingConnection, CDialog)

// The constructor
//
CWaitingConnection::CWaitingConnection(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CWaitingConnection::IDD, pParent)
, m_MessageText(_T(""))
, m_IsServer( false )
, m_BattleFieldName(_T(""))
, m_PlayerMax(_T(""))
, m_GamePoint(_T(""))
, m_ChatText2(_T(""))
{
}

// The destructor
//
CWaitingConnection::~CWaitingConnection()
{
}

// Synchronize members and control
//
void CWaitingConnection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLAYERS_CONNECTED, m_PlayerList);
	DDX_Control(pDX, IDC_LIST_WATCHER_CONNECTED, m_WatcherList);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_MessageText);
	DDX_Text(pDX, IDC_BATTLEFIELD_NAME, m_BattleFieldName);
	DDX_Text(pDX, IDC_PLAYER_MAX, m_PlayerMax);
	DDX_Text(pDX, IDC_GAME_POINT, m_GamePoint);
	DDX_Control(pDX, IDOK, m_ButtonLaunch);
	DDX_Control(pDX, IDC_RICHEDIT_CHAT, m_ChatList);
	DDX_Text(pDX, IDC_RICHEDIT_CHAT, m_ChatText2);
}

// Windows messages handling
//
BEGIN_MESSAGE_MAP(CWaitingConnection, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEND_MESSAGE, &CWaitingConnection::OnBnClickedButtonSendMessage)
END_MESSAGE_MAP()

// Initialise the dialog
//
BOOL CWaitingConnection::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	// Set column for report
	CString Str;
	Str.LoadStringW( IDS_COLUMN_HEADER_PLAYER );
	CGlobalIHM::CreateColumnListCtrl( &m_PlayerList, Str );
	Str.LoadStringW( IDS_COLUMN_HEADER_WATCHER );
	CGlobalIHM::CreateColumnListCtrl( &m_WatcherList, Str );

	if( m_IsServer )
	{
		CWnd* pWnd = GetDlgItem(IDOK);
		pWnd->ShowWindow( SW_SHOW );
	}

	CDC* pDC = GetDC();
	m_ChatList.SetTargetDevice( pDC->m_hDC, ::MulDiv(530, 1440, pDC->GetDeviceCaps(LOGPIXELSX)) );
	ReleaseDC( pDC );

	theApp.FreeChatMessage();

	return TRUE;
}

// Refresh the players list
//
void CWaitingConnection::RefreshPlayersList()
{
	if( !::IsWindow( m_PlayerList.m_hWnd ) )
		return;

	m_PlayerList.DeleteAllItems();

	for( int i=0; i<m_pGameDoc->m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_pGameDoc->m_PlayerArray.GetAt(i);
	
		CString Str;
		CString Type;
		switch( pPlayer->m_Type )
		{
		case CPlayer::PT_CLIENT:
			Type.LoadStringW( IDS_PT_CLIENT );
			break;
		case CPlayer::PT_SERVER:
			Type.LoadStringW( IDS_PT_SERVER );
			break;
		}
		Str.Format( _T("%s;%s"), pPlayer->GetName(), Type );
		CGlobalIHM::AddListItem( &m_PlayerList, Str, -1, -1);
	}
}

// The user want send a message to all the other players
//
void CWaitingConnection::OnBnClickedButtonSendMessage()
{
	// Get the message text
	UpdateData( TRUE );

	// Do nothing if the text box is empty
	if( m_MessageText.IsEmpty() )
		return;

	m_pGameDoc->m_ToServerSocket.CreateBuffer();
	m_pGameDoc->m_ToServerSocket.WriteType( m_pGameDoc->m_PlayerIndex );
	m_pGameDoc->m_ToServerSocket.WriteType( ((CPlayer*) m_pGameDoc->m_PlayerArray.GetAt(m_pGameDoc->m_PlayerIndex))->GetName() );
	m_pGameDoc->m_ToServerSocket.WriteType( m_MessageText );
	m_pGameDoc->m_ToServerSocket.SendMessage( SMI_TOSERVER_MESSAGE_TO_EVERYONE );

	m_MessageText = "";
	UpdateData( FALSE );
}

// Add a message receive from other players
//
void CWaitingConnection::AddMessage( int FromIndex, CString From, CString Message )
{
	CString Str;
	Str.Format( _T("%s > %s"), From, Message );

	UpdateData( TRUE );

	if( !m_ChatText2.IsEmpty() )
		Str = _T("\n")+Str;
	m_ChatText2 += Str;

	m_ChatMessageList += Message;

	// Set text to the richedit control
	long Last = m_ChatList.GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP );
	m_ChatList.ReplaceSel( Str );
	m_ChatList.SetSel( Last, m_ChatList.GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP ) );
	if( FromIndex==m_pGameDoc->m_PlayerIndex )
	{
		CHARFORMAT2 cf;

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		m_ChatList.GetSelectionCharFormat( cf );

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = RGB(0,128,0);
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		m_ChatList.SetSelectionCharFormat( cf );
	}
	else
	{
		CHARFORMAT2 cf;

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		m_ChatList.GetSelectionCharFormat( cf );

		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = RGB(0,0,0);
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		m_ChatList.SetSelectionCharFormat( cf );
	}
	m_ChatList.SetSel( m_ChatList.GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP ), m_ChatList.GetTextLengthEx(GTL_DEFAULT|GTL_PRECISE|GTL_NUMCHARS,CP_ACP )+1 );
	m_ChatList.LineScroll( m_ChatList.GetLineCount()-m_ChatList.GetFirstVisibleLine()-8 );
}

// Set the BattleField name
//
void CWaitingConnection::SetBattleFieldName( CString BattleFieldName )
{
	m_BattleFieldName = BattleFieldName;

	UpdateData( FALSE );
}

// Set the player max for this game
//
void CWaitingConnection::SetPlayerMax( int PlayerMax )
{
	m_PlayerMax.Format( _T("%d"), PlayerMax );

	UpdateData( FALSE );
}

// Set the game point for this game
//
void CWaitingConnection::SetGamePoint( int GamePoint )
{
	m_GamePoint.Format( _T("%d"), GamePoint );

	UpdateData( FALSE );
}

// Cancel the connexion
//
void CWaitingConnection::Cancel()
{
	OnCancel();
}

// The server launch the game
//
void CWaitingConnection::OnOK()
{
	// Call the base class
	CDialog::OnOK();
}
