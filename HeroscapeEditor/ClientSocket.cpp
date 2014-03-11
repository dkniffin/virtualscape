// ClientSocket.cpp : implementation file
//

#include "StdAfx.h"

#include "ArmyCard.h"
#include "ClientSocket.h"
#include "HeroscapeEditor.h"
#include "MainFrm.h"
#include "SocketMessageId.h"

// The constructor
//
CClientSocket::CClientSocket()
{
	// No buffer now
	m_BufferSend = NULL;
	m_BufferSendSize = 0;
	m_BufferReceive = NULL;
	m_BufferReceiveSize = 0;
	m_ReplayPosition = 0;
	m_ReplayMode = false;
}

// The destructor
//
CClientSocket::~CClientSocket()
{
	if( m_BufferSend )
	{
		free( m_BufferSend );
		m_BufferSend = NULL;
	}
	if( m_BufferReceive )
	{
		free( m_BufferReceive );
		m_BufferReceive = NULL;
	}
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

// If the socket is close
//
void CClientSocket::OnClose(int nErrorCode) 
{
	// Call the base class
	CSocket::OnClose(nErrorCode);
}

// We receive message from other application
//
void CClientSocket::OnReceive(int nErrorCode) 
{
	CString IP;
	UINT	Port;

	DWORD DataToRead;
	if( IOCtl( FIONREAD, &DataToRead )!=0 )
	{
		// Read data in the buffer
		if( m_BufferReceive )
		{
			char* BufferTemp = (char*) malloc( m_BufferReceiveSize+DataToRead );
			memcpy( BufferTemp, m_BufferReceive, m_BufferReceiveSize );
			free( m_BufferReceive );
			m_BufferReceive = BufferTemp;
		}
		else
		{
			m_BufferReceive = (char*) malloc( DataToRead );
			m_BufferReceiveSize = 0;
		}

		ReceiveFrom( &m_BufferReceive[m_BufferReceiveSize], DataToRead, IP, Port );
		memcpy( &m_ReplayBuffer[m_ReplayPosition], &m_BufferReceive[m_BufferReceiveSize], DataToRead );
		m_ReplayPosition += DataToRead;
		m_BufferReceiveSize += DataToRead;

		// If we have the type and len of the message
		while( m_BufferReceiveSize>=sizeof(short)+sizeof(int) )
		{
			// Verify that the message is complete
			int Len;
			memcpy( &Len, &m_BufferReceive[sizeof(short)], sizeof(Len) );
			short Id;
			memcpy( &Id, m_BufferReceive, sizeof(Id) );

			//CString Str;
			//Str.Format( _T("Recu message. Taille attendu : %i / Taille recue : %i"), Len+6, m_BufferReceiveSize );
			//AfxMessageBox( Str );

			if( m_BufferReceiveSize>=(int) (Len+sizeof(short)+sizeof(int)) )
			{
				// Save the message in a file for debug
				{
					//CString Str, Str2;
					//Str.Format( _T("Message %i (len=%i) : "), (int) Id, Len );
					//for( int i=0; i<(int) (Len+sizeof(short)+sizeof(int)); i++ )
					//{
					//	Str2.Format( _T("%02x "), m_BufferReceive[i] );
					//	Str += Str2;
					//}
					//Str += _T("\n");
					//CStdioFile f(_T("c:\\tracelima.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite );
					//f.SeekToEnd();
					//f.WriteString(Str);				
					//f.Close();
				}
				ReadAMessage( IP, Port );
				DoEvents();
			}
			else
				break;
		}
	}

	// Call the base class
	CSocket::OnReceive(nErrorCode);
}

// Read a message
//
void CClientSocket::ReadAMessage( CString IP, int Port )
{
	CString Str;
	int GamePort;

	short	MessageId;
	int		Len;

	ReadType( MessageId );
	ReadType( Len );

	TRACE( _T("Client message Id %i\n"), MessageId );

	switch( MessageId )
	{
	case SMI_TOCLIENT_GAME_NAME:
		ReadType( Str );
		ReadType( GamePort );
		//Set IP and port on dialog box
		// Remove comment of these 3 next lines when Hasbro will get authorisation
		//if( !m_ReplayMode )
		//	if( theApp.m_pJoinGameDlg!=NULL )
		//		theApp.m_pJoinGameDlg->SetIPAndPort( IP, GamePort );
		break;
	case SMI_TOCLIENT_GET_PLAYER_NAME:
		if( !m_ReplayMode )
		{
			CreateBuffer();
			WriteType(theApp.m_PlayerName);
			SendMessage(SMI_TOSERVER_SET_PLAYER_NAME);
		}
		break;
	case SMI_TOCLIENT_PLAYERS_LIST:
		if( !m_ReplayMode )
			theApp.m_pGameDoc->ReceivePlayersList( this );
		else
		{
			// Read all the players
			int Nb;
			int Index;
			ReadType( Nb );
			ReadType( Index );
			for( int i=0; i<Nb; i++ )
			{
				CString Str;
				ReadType( Str );
				ReadType( Index );
			}
		}
		break;
	case SMI_TOCLIENT_MESSAGE_TO_EVERYONE:
		{
			int FromIndex;
			CString From;
			CString Message;
			ReadType( FromIndex );
			ReadType( From );
			ReadType( Message );
			bool IsMine = (theApp.m_pGameDoc->m_PlayerIndex==FromIndex);
			if( theApp.m_pWaitingConnection!=NULL )
				theApp.m_pWaitingConnection->AddMessage( FromIndex, From, Message );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameChatBar.AddMessage( IsMine, From, Message );

			theApp.AddChatMessage( IsMine, From, Message );
		}
		break;
	case SMI_TOCLIENT_BATTLEFIELD_NAME:
		{
			CString BattleFieldName;
			ReadType( BattleFieldName );
			if( !m_ReplayMode )
				theApp.m_pWaitingConnection->SetBattleFieldName( BattleFieldName );
		}
		break;
	case SMI_TOCLIENT_PLAYER_MAX:
		{
			int	PlayerMax;
			ReadType( PlayerMax );
			if( !m_ReplayMode )
				theApp.m_pWaitingConnection->SetPlayerMax( PlayerMax );
		}
		break;
	case SMI_TOCLIENT_GAME_POINT:
		{
			int	GamePoint;
			ReadType( GamePoint );
			if( !m_ReplayMode )
			{
				theApp.m_pWaitingConnection->SetGamePoint( GamePoint );
				theApp.m_pGameDoc->SetGamePoint( GamePoint );
			}
		}
		break;
	case SMI_TOCLIENT_GAME_TYPE:
		{
			int	GameType;
			ReadType( GameType );
			if( !m_ReplayMode )
			{
				theApp.m_pGameDoc->SetGameType( GameType );
			}
		}
		break;
	case SMI_TOCLIENT_VIRTUALSCAPE_VERSION:
		{
			CString Version;
			ReadType( Version );
			if( !m_ReplayMode )
			{
				if( Version!=_T("1.0.7.0") )
				{
					AfxMessageBox( IDS_BAD_SERVER_VERSION_FOR_GAME );
					Close();
					theApp.m_pWaitingConnection->Cancel();
				}
				// When we are in game mode all the unusefull tool window must be hide.
				theApp.EnterGameMode();
			}
		}
		break;
	case SMI_TOCLIENT_TILES:
		{
			int NbTile;
			ReadType( NbTile );
			for( int i=0; i<NbTile; i++ )
			{
				int TileType;
				ReadType( TileType );

				CTile* NewTile = CTile::GetNewTile( TileType );
				NewTile->ReceiveBySocket( this );
				NewTile->Init();
				if( !m_ReplayMode )
					theApp.m_pGameDoc->AddTile( NewTile );
				else
					delete NewTile;
			}
			if( !m_ReplayMode )
			{
				if( theApp.m_pWaitingConnection!=NULL )
					theApp.m_pWaitingConnection->OnOK();

				// Inform the game doc that the view can be created
				theApp.m_pGameDoc->Init();
			}
		}
		break;
	case SMI_TOCLIENT_ACTION:
		{
			int PlayerIndex;
			int ActionType;
			CString PlayerName;
			ReadType( PlayerIndex );
			ReadType( PlayerName );
			ReadType( ActionType );
			if( !m_ReplayMode )
			{
				bool IsMine = (PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex); 
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddAction( IsMine , PlayerName, ActionType );
				switch( ActionType )
				{
				case CGameDoc::TA_CHOOSE_ARMY:
					if( IsMine )
						theApp.m_pGameDoc->ChooseArmy();
					break;
				case CGameDoc::TA_FREEGAME:
					theApp.m_pGameDoc->FreeGame();
					break;
				}
			}
		}
		break;
	case SMI_TOCLIENT_ARMYCHOOSED:
		{
			int PlayerIndex;
			int ArmyIndex;
			ReadType( PlayerIndex );
			ReadType( ArmyIndex );
			if( !m_ReplayMode )
			{
				theApp.m_pGameDoc->AddArmyToPlayer( PlayerIndex, ArmyIndex );
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
			}
		}
		break;
	case SMI_TOCLIENT_FIGUREPLACED:
		{
			int PlayerIndex;
			int ArmyIndex;
			int FigureIndex;
			int x;
			int y;
			int z;
			int Rotation;
			double CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ;
			ReadType( PlayerIndex );
			ReadType( ArmyIndex );
			ReadType( FigureIndex );
			ReadType( x );
			ReadType( y );
			ReadType( z );
			ReadType( Rotation );
			ReadType( CameraX );
			ReadType( CameraY );
			ReadType( CameraZ );
			ReadType( LookAtX );
			ReadType( LookAtY );
			ReadType( LookAtZ );
			theApp.m_pGameDoc->PlaceFigureForPlayer( PlayerIndex, ArmyIndex, FigureIndex, x, y, z, Rotation, CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ );
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2;
			Str.LoadStringW( IDS_PLACED_ARMY );
			CFigureObject* pFigure = (CFigureObject*) (((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->m_ArmyList.GetAt(ArmyIndex))->GetFiguresList()->GetAt(FigureIndex));
			Str2.Format( Str, pFigure->m_FigureName );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_FIGUREREMOVED:
		{
			int PlayerIndex;
			int RemovedPlayerIndex;
			int ArmyIndex;
			int FigureIndex;
			double CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ;
			ReadType( PlayerIndex );
			ReadType( RemovedPlayerIndex );
			ReadType( ArmyIndex );
			ReadType( FigureIndex );
			ReadType( CameraX );
			ReadType( CameraY );
			ReadType( CameraZ );
			ReadType( LookAtX );
			ReadType( LookAtY );
			ReadType( LookAtZ );
			theApp.m_pGameDoc->RemoveFigureForPlayer( RemovedPlayerIndex, ArmyIndex, FigureIndex, CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ );
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2;
			Str.LoadStringW( IDS_REMOVED_ARMY );
			CFigureObject* pFigure = (CFigureObject*) (((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(RemovedPlayerIndex))->m_ArmyList.GetAt(ArmyIndex))->GetFiguresList()->GetAt(FigureIndex));
			Str2.Format( Str, pFigure->m_FigureName );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_FIGUREMOVED:
		{
			int PlayerIndex;
			int ArmyIndex;
			int FigureIndex;
			int x;
			int y;
			int z;
			int Rotation;
			double CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ;
			ReadType( PlayerIndex );
			ReadType( ArmyIndex );
			ReadType( FigureIndex );
			ReadType( x );
			ReadType( y );
			ReadType( z );
			ReadType( Rotation );
			ReadType( CameraX );
			ReadType( CameraY );
			ReadType( CameraZ );
			ReadType( LookAtX );
			ReadType( LookAtY );
			ReadType( LookAtZ );
			theApp.m_pGameDoc->MoveFigureForPlayer( PlayerIndex, ArmyIndex, FigureIndex, x, y, z, Rotation, CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ );
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2;
			Str.LoadStringW( IDS_MOVED_ARMY );
			CFigureObject* pFigure = (CFigureObject*) (((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->m_ArmyList.GetAt(ArmyIndex))->GetFiguresList()->GetAt(FigureIndex));
			Str2.Format( Str, pFigure->m_FigureName );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_ATTACK:
		{
			int	PlayerIndex;
			int AttackPlayerIndex;
			int AttackArmyIndex;
			int AttackFigureIndex;
			int NbEnnemi;
			int DiceLaunch;
			int DiceResult;
			int IsValueForced;
			double CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ;
			CPtrArray EnnemiList;
			ReadType( PlayerIndex );
			ReadType( AttackPlayerIndex );
			ReadType( AttackArmyIndex );
			ReadType( AttackFigureIndex );
			ReadType( NbEnnemi );
			for( int i=0; i<NbEnnemi; i++ )
			{
				CGameDoc::FigureInfos* pFigureInfos = (CGameDoc::FigureInfos*) malloc( sizeof(CGameDoc::FigureInfos) );
				ReadType( pFigureInfos->PlayerIndex );
				ReadType( pFigureInfos->ArmyIndex );
				ReadType( pFigureInfos->FigureIndex );
				EnnemiList.Add( pFigureInfos );
			}
			ReadType( DiceLaunch );
			ReadType( DiceResult );
			ReadType( IsValueForced );
			ReadType( CameraX );
			ReadType( CameraY );
			ReadType( CameraZ );
			ReadType( LookAtX );
			ReadType( LookAtY );
			ReadType( LookAtZ );
			theApp.m_pGameDoc->Attack( PlayerIndex, AttackPlayerIndex, AttackArmyIndex, AttackFigureIndex, NbEnnemi, &EnnemiList, DiceLaunch, DiceResult, IsValueForced, CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ );
			// Add attack string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2,Str3;
			Str.LoadStringW( IDS_ATTACK_LAUNCH );
			CFigureObject* pFigure = (CFigureObject*) (((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(AttackPlayerIndex))->m_ArmyList.GetAt(AttackArmyIndex))->GetFiguresList()->GetAt(AttackFigureIndex));
			for( int i=0; i<NbEnnemi; i++ )
			{
				CGameDoc::FigureInfos* pFigureInfos = (CGameDoc::FigureInfos*) EnnemiList.GetAt(i);
				CFigureObject* pFigure = (CFigureObject*) (((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(pFigureInfos->PlayerIndex))->m_ArmyList.GetAt(pFigureInfos->ArmyIndex))->GetFiguresList()->GetAt(pFigureInfos->FigureIndex));
				if( i>0 )
					Str3.Append(_T(","));
				Str3.Append(pFigure->m_FigureName);
			}
			Str2.Format( Str, pFigure->m_FigureName, Str3 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
			// Add launch dice string in action list
			Str.LoadStringW( IDS_ATTACK_DICE );
			if( IsValueForced )
				Str3.LoadStringW( IDS_DICE_FORCED );
			else
				Str3.LoadStringW( IDS_DICE_NOT_FORCED );
			Str2.Format( Str, DiceResult, DiceLaunch, Str3 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_DEFENSE:
		{
			int	PlayerIndex;
			int DefensePlayerIndex;
			int DefenseArmyIndex;
			int DefenseFigureIndex;
			int DiceLaunch;
			int DiceResult;
			int IsValueForced;
			double CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ;
			ReadType( PlayerIndex );
			ReadType( DefensePlayerIndex );
			ReadType( DefenseArmyIndex );
			ReadType( DefenseFigureIndex );
			ReadType( DiceLaunch );
			ReadType( DiceResult );
			ReadType( IsValueForced );
			ReadType( CameraX );
			ReadType( CameraY );
			ReadType( CameraZ );
			ReadType( LookAtX );
			ReadType( LookAtY );
			ReadType( LookAtZ );
			theApp.m_pGameDoc->Defense( PlayerIndex, DefensePlayerIndex, DefenseArmyIndex, DefenseFigureIndex, DiceLaunch, DiceResult, IsValueForced, CameraX, CameraY, CameraZ, LookAtX, LookAtY, LookAtZ );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2,Str3;
			Str.LoadStringW( IDS_DEFENSE_LAUNCH );
			CFigureObject* pFigure = (CFigureObject*) (((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(DefensePlayerIndex))->m_ArmyList.GetAt(DefenseArmyIndex))->GetFiguresList()->GetAt(DefenseFigureIndex));
			if( IsValueForced )
				Str3.LoadStringW( IDS_DICE_FORCED );
			else
				Str3.LoadStringW( IDS_DICE_NOT_FORCED );
			Str2.Format( Str, pFigure->m_FigureName, DiceResult, DiceLaunch, Str3 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_NEXT_TURN:
		{
			int	PlayerIndex;
			ReadType( PlayerIndex );
			theApp.m_pGameDoc->NextTurn( PlayerIndex );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str;
			Str.LoadStringW( IDS_NEXT_TURN );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_INCREMENT_LIFE:
		{
			int	PlayerIndex;
			int IncrementPlayerIndex;
			int IncrementArmyIndex;
			ReadType( PlayerIndex );
			ReadType( IncrementPlayerIndex );
			ReadType( IncrementArmyIndex );
			theApp.m_pGameDoc->IncrementLife( IncrementPlayerIndex, IncrementArmyIndex );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2,Str3,Str4;
			Str2 = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(IncrementPlayerIndex))->GetName();
			Str3 = ((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(IncrementPlayerIndex))->m_ArmyList.GetAt(IncrementArmyIndex))->m_Name;
			Str.LoadStringW( IDS_INCREMENT_ARMY_LIFE );
			Str4.Format( Str, Str3, Str2 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str4 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str4 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_DECREMENT_LIFE:
		{
			int	PlayerIndex;
			int DecrementPlayerIndex;
			int DecrementArmyIndex;
			ReadType( PlayerIndex );
			ReadType( DecrementPlayerIndex );
			ReadType( DecrementArmyIndex );
			theApp.m_pGameDoc->DecrementLife( DecrementPlayerIndex, DecrementArmyIndex );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2,Str3,Str4;
			Str2 = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(DecrementPlayerIndex))->GetName();
			Str3 = ((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(DecrementPlayerIndex))->m_ArmyList.GetAt(DecrementArmyIndex))->m_Name;
			Str.LoadStringW( IDS_DECREMENT_ARMY_LIFE );
			Str4.Format( Str, Str3, Str2 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str4 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str4 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_ADD_PREDICTED_MARQUER:
		{
			int	PlayerIndex;
			int PredictedPlayerIndex;
			int PredictedArmyIndex;
			int PredictedMarquer;
			ReadType( PlayerIndex );
			ReadType( PredictedPlayerIndex );
			ReadType( PredictedArmyIndex );
			ReadType( PredictedMarquer );
			theApp.m_pGameDoc->AddPredictedMarquer( PredictedPlayerIndex, PredictedArmyIndex, PredictedMarquer );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2,Str3;
			Str2 = ((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PredictedPlayerIndex))->m_ArmyList.GetAt(PredictedArmyIndex))->m_Name;
			Str.LoadStringW( IDS_ADD_PREDICTED_MARQUER );
			Str3.Format( Str, Str2 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str3 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str3 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_SHOW_PREDICTED_MARQUER:
		{
			int	PlayerIndex;
			int PredictedPlayerIndex;
			int PredictedArmyIndex;
			int PredictedMarquer;
			ReadType( PlayerIndex );
			ReadType( PredictedPlayerIndex );
			ReadType( PredictedArmyIndex );
			ReadType( PredictedMarquer );
			theApp.m_pGameDoc->ShowPredictedMarquer( PredictedPlayerIndex, PredictedArmyIndex, PredictedMarquer );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2,Str3;
			Str2 = ((CArmyCard*) ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PredictedPlayerIndex))->m_ArmyList.GetAt(PredictedArmyIndex))->m_Name;
			Str.LoadStringW( IDS_SHOW_PREDICTED_MARQUER );
			Str3.Format( Str, Str2 );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str3 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str3 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	case SMI_TOCLIENT_REMOVE_MARQUER:
		{
			int	PlayerIndex;
			ReadType( PlayerIndex );
			theApp.m_pGameDoc->RemoveMarquer( PlayerIndex );
		}
		break;
	case SMI_TOCLIENT_DIE_20_FACES:
		{
			int	PlayerIndex;
			int DieResult;
			ReadType( PlayerIndex );
			ReadType( DieResult );
			// Add string in action list
			CString PlayerName = ((CPlayer*) theApp.m_pGameDoc->m_PlayerArray.GetAt(PlayerIndex))->GetName();
			CString Str,Str2;
			Str.LoadStringW( IDS_DIE_20_FACES );
			Str2.Format( Str, DieResult );
			if( PlayerIndex==theApp.m_pGameDoc->m_PlayerIndex )
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( true , PlayerName, Str2 );
			else
				((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.AddString( false , PlayerName, Str2 );
			((CMainFrame*) theApp.m_pMainWnd)->m_wndGameActionBar.m_GameActionFV.CloseLastAction();
		}
		break;
	default:
		{
			TRACE( _T("Receive a unknow message id=%d\n"), MessageId );
			char a;
			for( int i=0; i<Len; i++ )
				ReadType( a );
		}
	}
}

// Send a message to the other application
//
void CClientSocket::SendMessage( short ID )
{
	char* Buffer = (char*) malloc( m_BufferSendSize+sizeof(short)+sizeof(int) );

	char* pBuffer = Buffer;

	memcpy( pBuffer, &ID, sizeof(ID) );
	pBuffer += sizeof(ID);
	memcpy( pBuffer, &m_BufferSendSize, sizeof(m_BufferSendSize) );
	pBuffer += sizeof(m_BufferSendSize);
	if( m_BufferSendSize>0 && m_BufferSend!=NULL )
	{
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize );
		pBuffer += m_BufferSendSize;
	}

	Send( Buffer, m_BufferSendSize+sizeof(short)+sizeof(int)  );

	free( Buffer );

	DoEvents();
}

// A Do event
//
void CClientSocket::DoEvents(void)
{
	MSG	msg;

	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// Send a message to the other application
//
void CClientSocket::SendMessageTo( short ID, int Port, CString* IP )
{
	char* Buffer = (char*) malloc( m_BufferSendSize+sizeof(short)+sizeof(int) );

	char* pBuffer = Buffer;

	memcpy( pBuffer, &ID, sizeof(ID) );
	pBuffer += sizeof(ID);
	memcpy( pBuffer, &m_BufferSendSize, sizeof(m_BufferSendSize) );
	pBuffer += sizeof(m_BufferSendSize);
	if( m_BufferSendSize>0 && m_BufferSend!=NULL )
	{
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize );
		pBuffer += m_BufferSendSize;
	}

	if( IP==NULL )
		SendTo( Buffer, m_BufferSendSize+sizeof(short)+sizeof(int), Port );
	else
		SendTo( Buffer, m_BufferSendSize+sizeof(short)+sizeof(int), Port, IP->GetBuffer(0) );

	free( Buffer );
}

// Read a short
//
void CClientSocket::ReadType( short& s )
{
	memcpy( &s, m_BufferReceive, sizeof(s) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(s) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(s)], m_BufferReceiveSize-sizeof(s) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(s);
}

// Read a char
//
void CClientSocket::ReadType( char& c )
{
	memcpy( &c, m_BufferReceive, sizeof(c) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(c) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(c)], m_BufferReceiveSize-sizeof(c) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(c);
}

// Read a double
//
void CClientSocket::ReadType( double& d )
{
	memcpy( &d, m_BufferReceive, sizeof(d) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(d) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(d)], m_BufferReceiveSize-sizeof(d) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(d);
}

// Read a double array
//
void CClientSocket::ReadType( double* d, int Size )
{

	memcpy( d, m_BufferReceive, sizeof(double)*Size );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(double)*Size );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(double)*Size], m_BufferReceiveSize-sizeof(double)*Size );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(double)*Size;
}

// Read a int64
//
void CClientSocket::ReadType( __int64& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a int
//
void CClientSocket::ReadType( int& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a UINT
//
void CClientSocket::ReadType( UINT& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a LONG
//
void CClientSocket::ReadType( LONG& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a BYTE
//
void CClientSocket::ReadType( BYTE& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a string
//
void CClientSocket::ReadType( CString& Str )
{
	short	Len;
	ReadType( Len );

	char* Buf = (char*) malloc(Len+1);
	if( Buf==NULL )
	{
		CString Str;
		Str.Format( _T("La tentative d'allouer %i octets à échouée"), Len );
		AfxMessageBox( Str );
		return;
	}
	memcpy( Buf, m_BufferReceive, Len );
	Buf[Len] = 0;

	Str = Buf;

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-Len );
	memcpy( BufferTemp, &m_BufferReceive[Len], m_BufferReceiveSize-Len );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= Len;
	free( Buf );
}

// Read datas
//
void CClientSocket::ReadDatas( char* pBuf, int Size )
{
	memcpy( pBuf, m_BufferReceive, Size );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-Size );
	memcpy( BufferTemp, &m_BufferReceive[Size], m_BufferReceiveSize-Size );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= Size;
}

// Create a Buffer for send data
//
void CClientSocket::CreateBuffer()
{
	if( m_BufferSend )
	{
		free( m_BufferSend );
		m_BufferSend = NULL;
	}
	m_BufferSendSize = 0;
}

// Write a short
//
void CClientSocket::WriteType( short s )
{
	m_BufferSendSize += sizeof(s);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(s) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(short), &s, sizeof(s) );
}

// Write a int64
//
void CClientSocket::WriteType( __int64 i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(__int64) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(__int64), &i, sizeof(i) );
}

// Write a double
//
void CClientSocket::WriteType( double d )
{
	m_BufferSendSize += sizeof(d);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(d) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(d), &d, sizeof(d) );
}

// Write a int
//
void CClientSocket::WriteType( int i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a UINT
//
void CClientSocket::WriteType( UINT i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a LONG
//
void CClientSocket::WriteType( LONG i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a BYTE
//
void CClientSocket::WriteType( BYTE i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a char
//
void CClientSocket::WriteType( char c )
{
	m_BufferSendSize += sizeof(c);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(c) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(c), &c, sizeof(c) );
}

// Write a CString
//
void CClientSocket::WriteType( CString Str )
{
	short Len = Str.GetLength();
	WriteType( Len );
	m_BufferSendSize += Str.GetLength();
	char* pStr = theApp.GetAsciiString( Str );
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-Str.GetLength() );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-Str.GetLength(), pStr, Str.GetLength() );
	free( pStr );
}

// An error occur (display the error)
//
void CClientSocket::SocketError()
{
	CString Str;
	int SocketError = GetLastError();

	switch( SocketError )
	{
	case WSANOTINITIALISED:
		Str = "A successful AfxSocketInit must occur before using this API.";
		break;
	case WSAENETDOWN:
		Str = "The Windows Sockets implementation detected that the network subsystem failed.";
		break;
	case WSAENOTCONN:
		Str = "The socket is not connected.";
		break;
	case WSAEINPROGRESS:
		Str = "A blocking Windows Sockets operation is in progress.";
		break;
	case WSAENOTSOCK:
		Str = "The descriptor is not a socket.";
		break;
	case WSAEOPNOTSUPP:
		Str = "MSG_OOB was specified, but the socket is not of type SOCK_STREAM.";
		break;
	case WSAESHUTDOWN:
		Str = "The socket has been shut down; it is not possible to call Receive on a socket after ShutDown has been invoked with nHow set to 0 or 2.";
		break;
	case WSAEWOULDBLOCK:
		Str = "The socket is marked as nonblocking and the Receive operation would block.";
		break;
	case WSAEMSGSIZE:
		Str = "The datagram was too large to fit into the specified buffer and was truncated.";
		break;
	case WSAEINVAL:
		Str = "The socket has not been bound with Bind.";
		break;
	case WSAECONNABORTED:
		Str = "The virtual circuit was aborted due to timeout or other failure.";
		break;
	case WSAECONNRESET:
		Str = "The virtual circuit was reset by the remote side.";
		break;
	default:
		Str.Format( _T("A unknown socket error occur : %i"), SocketError );
	}
}

void CClientSocket::OnConnect(int nErrorCode)
{
	CSocket::OnConnect(nErrorCode);

	CreateBuffer();
	WriteType( theApp.m_PlayerName );
	SendMessage(SMI_TOSERVER_SET_PLAYER_NAME);
}

void CClientSocket::OnAccept(int nErrorCode)
{
	// TODO : ajoutez ici votre code spécialisé et/ou l'appel de la classe de base

	CSocket::OnAccept(nErrorCode);
}

// Replay all the received message
//
void CClientSocket::Replay( bool ReplayToFile, CString ReplayFile )
{
	m_ReplayHighSpeed = false;
	m_ReplayToFile = ReplayToFile;
	m_ReplayFile = ReplayFile;

	m_ReplayMode = true;
	m_CurrentImage = 0;

	if( m_BufferReceive )
		free( m_BufferReceive );

	m_BufferReceive = (char*) malloc( m_ReplayPosition );
	memcpy( m_BufferReceive, m_ReplayBuffer, m_ReplayPosition );
	m_BufferReceiveSize = m_ReplayPosition;

	POSITION pos = theApp.m_pGameDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = theApp.m_pGameDoc->GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			((CGame3DView*) pView)->m_IsReplayMode = true;

			LARGE_INTEGER	CurrentTimer;
			QueryPerformanceCounter( &CurrentTimer );
			((CGame3DView*) pView)->m_LastKeyTime = CurrentTimer.QuadPart;
		}
	}
}

// Show next replay
//
void CClientSocket::NextReplay()
{
	// The game view
	CGame3DView* pGameView;
	POSITION pos = theApp.m_pGameDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = theApp.m_pGameDoc->GetNextView(pos);
		if( pView->IsKindOf( RUNTIME_CLASS(CGame3DView) ) )
		{
			pGameView = ((CGame3DView*) pView);
		}
	}

	if( pGameView->m_Mode!=CHeroscapeEditor3DView::MODE3D_NULL )
	{
		if( m_ReplayToFile )
			WaitViewReadyToFile(pGameView);
		else
			WaitViewReady(pGameView);
	}
	else if( m_BufferReceiveSize>=sizeof(short)+sizeof(int) )
	{
		// Verify that the message is complete
		int Len;
		memcpy( &Len, &m_BufferReceive[sizeof(short)], sizeof(Len) );
		short Id;
		memcpy( &Id, m_BufferReceive, sizeof(Id) );

		if( m_BufferReceiveSize>=(int) (Len+sizeof(short)+sizeof(int)) )
			ReadAMessage( _T(""), 0 );

		// Wait that view is ready
		if( m_ReplayToFile )
			WaitViewReadyToFile(pGameView);
		else
			WaitViewReady(pGameView);
	}
	else
	{
		pGameView->m_IsReplayMode = false;
		m_ReplayMode = false;
		theApp.m_pGameDoc->m_AnimationType = theApp.m_pGameDoc->m_OldAnimationType;
	}
}

// Wait that the view is ready for next replay
//
void CClientSocket::WaitViewReady( void* pGView )
{
	CGame3DView* pGameView = (CGame3DView*) pGView;

	LARGE_INTEGER	CurrentTimer;
	QueryPerformanceCounter( &CurrentTimer );
	__int64 LastKeyTime = CurrentTimer.QuadPart;

	if( GetAsyncKeyState(VK_ESCAPE)&0x8000 )
	{
		// The user want stop the replay so replay everything at high speed
		m_ReplayHighSpeed = true;
	}
	QueryPerformanceCounter( &CurrentTimer );
	if( m_ReplayHighSpeed )
	{
		pGameView->m_LastKeyTime += pGameView->m_frequency;
		LastKeyTime = CurrentTimer.QuadPart;
		pGameView->ComputeMoveAuto();
		pGameView->RedrawWindow();
	}
	else
	{
		LastKeyTime = CurrentTimer.QuadPart;
		pGameView->m_LastKeyTime = CurrentTimer.QuadPart;
		pGameView->ComputeMoveAuto();
		pGameView->RedrawWindow();
	}
}

// Wait that the view is ready for next replay
//
void CClientSocket::WaitViewReadyToFile( void* pGView )
{
	CGame3DView* pGameView = (CGame3DView*) pGView;

	LARGE_INTEGER	CurrentTimer;
	QueryPerformanceCounter( &CurrentTimer );
	__int64 LastKeyTime = CurrentTimer.QuadPart;

	if( GetAsyncKeyState(VK_ESCAPE)&0x8000 )
	{
		// The user want stop the replay so replay everything at high speed
		m_ReplayHighSpeed = true;
	}
	QueryPerformanceCounter( &CurrentTimer );
	if( m_ReplayHighSpeed )
	{
		pGameView->m_LastKeyTime += pGameView->m_frequency;
		LastKeyTime = CurrentTimer.QuadPart;
		pGameView->ComputeMoveAuto();
		pGameView->RedrawWindow();
	}
	else
	{
		LastKeyTime = CurrentTimer.QuadPart;
		pGameView->m_LastKeyTime += pGameView->m_frequency/10;
		
		pGameView->ComputeMoveAuto();
		//((CGame3DView*) pView)->RedrawWindow();
		pGameView->OnOutilsVuehautequalite();

		// Copy from OpenGL 
		glPixelStorei( GL_PACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

		// Copy from OpenGL
		glReadBuffer( GL_FRONT );
		::glReadPixels(0,0,pGameView->m_i_Width,pGameView->m_i_Heigth,GL_RGB,GL_UNSIGNED_BYTE,(GLvoid*) pGameView->m_pViewPoint); 
		glReadBuffer( GL_BACK );

		// Save the computed image
		CString myFileName;
		myFileName.Format( _T("%s%06i.bmp"), m_ReplayFile, m_CurrentImage++ );

		char FileName[1000];
		size_t i;
		wcstombs_s( &i, FileName, 1000, myFileName.GetBuffer(0), 1000 );

		pGameView->SaveImage( FileName );
	}
}