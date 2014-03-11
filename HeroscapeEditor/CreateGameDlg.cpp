#include "stdafx.h"

#include "HeroscapeEditor.h"
#include "CreateGameDlg.h"


IMPLEMENT_DYNAMIC(CCreateGameDlg, CDialog)

// The constructor
//
CCreateGameDlg::CCreateGameDlg(CWnd* pParent /*=NULL*/)
:
// Call the base class
CDialog(CCreateGameDlg::IDD, pParent),
// The default max player
m_PlayerMax(2),
// The default max watcher
m_WatcherMax(256),
// The default number of point for the game (or number of card for a basic game)
m_GamePoint(2),
// The default server port
m_ServerPort(1399),
// The default game type (basic)
m_GameType(0),
// The default password
m_GamePassword(_T(""))
, m_PlayerName(_T(""))
, m_IP_Address(_T(""))
, m_Game_Language(_T(""))
{
	// The default game name
	m_GameName.LoadString( IDS_DEFAULTGAMENAME );	
	// The default welcome message
	m_WelcomeMessage.LoadString( IDS_DEFAULTGAMEWELCOMEMESSAGE );
}

// The destructor
//
CCreateGameDlg::~CCreateGameDlg()
{
}

// Synchronize members and control
//
void CCreateGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN_PLAYERS_MAX, m_SpinPlayerMax);
	DDX_Text(pDX, IDC_EDIT_PLAYERS_MAX, m_PlayerMax);
	DDX_Control(pDX, IDC_SPIN_WATCHER_MAX, m_SpinWatcherMax);
	DDX_Text(pDX, IDC_EDIT_WATCHER_MAX, m_WatcherMax);
	DDX_Control(pDX, IDC_SPIN_GAME_POINT, m_SpinGamePoint);
	DDX_Text(pDX, IDC_EDIT_GAME_POINT, m_GamePoint);
	DDX_Control(pDX, IDC_SPIN_SERVER_PORT, m_SpinPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT_GAME_NAME, m_GameName);
	DDX_CBIndex(pDX, IDC_COMBO_GAME_TYPE, m_GameType);
	DDX_Text(pDX, IDC_EDIT_GAME_PASSWORD, m_GamePassword);
	DDX_Text(pDX, IDC_EDIT_WELCOME_MESSAGE, m_WelcomeMessage);
	DDX_Text(pDX, IDC_EDIT_PLAYER_NAME, m_PlayerName);
	DDX_Control(pDX, IDC_EDIT_PLAYER_NAME, m_Ed_PlayerName);
	DDX_Control(pDX, IDC_EDIT_GAME_NAME, m_Ed_GameName);
	DDX_Control(pDX, IDC_EDIT_GAME_POINT, m_Ed_GamePoint);
	DDX_Control(pDX, IDC_EDIT_PLAYERS_MAX, m_Ed_PlayerMax);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP_Address);
	DDX_Text(pDX, IDC_EDIT_GAME_LANGAGE, m_Game_Language);
}

// The windows message handling
//
BEGIN_MESSAGE_MAP(CCreateGameDlg, CDialog)
END_MESSAGE_MAP()

// The dialog is initializing
//
BOOL CCreateGameDlg::OnInitDialog()
{
	// Call the base class
	CDialog::OnInitDialog();

	// Set the spin range
	m_SpinPlayerMax.SetRange(2,16);
	m_SpinWatcherMax.SetRange(0,256);
	m_SpinGamePoint.SetRange(0,10000);
	m_SpinPort.SetRange(1024,9999);

	return TRUE;
}

// The user want create the game
//
void CCreateGameDlg::OnOK()
{
	// Get all field
	UpdateData( TRUE );

	// Verify that the player name isn't empty
	if( m_PlayerName.IsEmpty() )
	{
		AfxMessageBox( IDS_FILL_PLAYER_NAME );
		m_Ed_PlayerName.SetFocus();
		return;
	}

	// Verify that the game name isn't empty
	if( m_GameName.IsEmpty() )
	{
		AfxMessageBox( IDS_FILL_GAME_NAME );
		m_Ed_GameName.SetFocus();
		return;
	}

	// Verify that the point number is > 0
	if( m_GamePoint<=0 )
	{
		AfxMessageBox( IDS_FILL_GAME_POINT );
		m_Ed_GamePoint.SetFocus();
		return;
	}

	// Verify that the field player max is > 1
	if( m_PlayerMax<=1 )
	{
		AfxMessageBox( IDS_PLAYER_MAX_TOO_LOW );
		m_Ed_PlayerMax.SetFocus();
		return;
	}

	CDialog::OnOK();
}
