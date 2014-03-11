// GameDocServer.cpp : fichier d'implémentation
//

#include "StdAfx.h"

#include "ArmyManager.h"
#include "GameDocServer.h"
#include "HeroscapeEditor.h"
#include "SocketMessageId.h"

// CGameDocServer

IMPLEMENT_DYNCREATE(CGameDocServer, CDocument)

// The constructor
//
CGameDocServer::CGameDocServer()
{
	m_IsServer = true;

	m_CurrentStep = STEP_CONNEXION;

	if( m_BroadcastSocket.Create(5186,SOCK_DGRAM,NULL)==0 )
	{
		m_BroadcastSocket.SocketError();
		return;
	}
	m_BroadcastSocket.AsyncSelect( FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
	m_ConnexionSocket.Create(theApp.m_GamePort);
	m_ConnexionSocket.AsyncSelect( FD_ACCEPT | FD_CONNECT | FD_CLOSE );
	m_ConnexionSocket.Listen();
}

// The destructor
//
CGameDocServer::~CGameDocServer()
{
}

BEGIN_MESSAGE_MAP(CGameDocServer, CDocument)
END_MESSAGE_MAP()

// Add a player to the game
//
void CGameDocServer::AddPlayer( CPlayer* pPlayer )
{
	if( m_PlayerArray.GetCount()== 0 )
		pPlayer->m_Type = CPlayer::PT_SERVER;
	else
		pPlayer->m_Type = CPlayer::PT_CLIENT;

	m_PlayerArray.Add( pPlayer );

	SendAllPlayersToAllClients();

	if( m_PlayerArray.GetCount()>=2 || true )
	{
		theApp.m_pWaitingConnection->m_ButtonLaunch.EnableWindow();
	}
}

// Remove a player from the game
//
void CGameDocServer::RemovePlayer( CPlayer* pPlayer )
{
	if( m_CurrentStep==STEP_CONNEXION )
	{
		for( int i=1; i<m_PlayerArray.GetCount(); i++ )
		{
			if( pPlayer==((CPlayer*) m_PlayerArray.GetAt(i)) )
			{
				m_PlayerArray.RemoveAt(i);
				break;
			}
		}

		// Inform all other player of the new players list
		SendAllPlayersToAllClients();
	}
}

// Send the players list to all the client
//
void CGameDocServer::SendAllPlayersToAllClients()
{
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_PointForArmy = theApp.m_GamePoint;
	}

	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		CString Version = _T("1.0.7.0");
		pPlayer->m_pToClientSocket->WriteType( Version );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_VIRTUALSCAPE_VERSION );
		pPlayer->m_pToClientSocket->CreateBuffer();
		int Nb = m_PlayerArray.GetCount();
		pPlayer->m_pToClientSocket->WriteType( Nb );
		pPlayer->m_pToClientSocket->WriteType( i );
		for( int j=0; j<m_PlayerArray.GetCount(); j++ )
		{
			CPlayer* pPlayer2 = (CPlayer*) m_PlayerArray.GetAt(j);
			pPlayer->m_pToClientSocket->WriteType( pPlayer2->GetName() );
			pPlayer->m_pToClientSocket->WriteType( pPlayer2->m_Type );
		}
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_PLAYERS_LIST );
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( m_BattleFieldName );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_BATTLEFIELD_NAME );
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( theApp.m_GamePlayerMax );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_PLAYER_MAX );
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( theApp.m_GamePoint );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_GAME_POINT );
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( theApp.m_GameType );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_GAME_TYPE );
	}
}

// Send a message text to everybody
//
void CGameDocServer::SendMessageTextToEverybody( int FromIndex, CString From, CString Message )
{
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( FromIndex );
		pPlayer->m_pToClientSocket->WriteType( From );
		pPlayer->m_pToClientSocket->WriteType( Message );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_MESSAGE_TO_EVERYONE );
	}
}

// Initialise the game
//
void CGameDocServer::InitGame()
{
	CPtrArray* pArray = CArmyManager::GetAllArmy();
	m_ArmyArray.Append( *pArray );
	delete pArray;

	SendTilesToAllPlayers();

	if( !theApp.m_GameWelcomeMessage.IsEmpty() )
		SendMessageTextToEverybody( -1, _T(""), theApp.m_GameWelcomeMessage );

	// Now, this is the step to choose army
	m_CurrentStep = STEP_CHOOSE_ARMY;

	// Send all player the next action (first player must choose army)
	SendAllPlayersAction( 0, ((CPlayer*) m_PlayerArray.GetAt(0))->GetName(), TA_CHOOSE_ARMY );
}

// Send an action to all the player
//
void CGameDocServer::SendAllPlayersAction( int PlayerIndex, CString PlayerName, int ActionType )
{
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( PlayerName );
		pPlayer->m_pToClientSocket->WriteType( ActionType );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_ACTION );
	}
}

// Send the tiles to all the players
//
void CGameDocServer::SendTilesToAllPlayers()
{
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		int NbTile = m_TileList.GetCount();
		pPlayer->m_pToClientSocket->WriteType( NbTile );
		for( int j=0; j<m_TileList.GetCount(); j++ )
		{
			CTile* pTile = (CTile*) m_TileList.GetAt(j);
			pPlayer->m_pToClientSocket->WriteType( pTile->m_Type );
			pTile->SendBySocket( pPlayer->m_pToClientSocket );
		}
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_TILES );
	}
}

// Add an army to a player
//
void CGameDocServer::AddArmyToPlayer( int PlayerIndex, int ArmyIndex )
{
	CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(PlayerIndex);
	CArmyCard* pArmyCard = (CArmyCard*) m_ArmyArray.GetAt(ArmyIndex);

	// Add the Army to the player
	pPlayer->AddArmy( pArmyCard );

	// Remove the army from this list
	m_ArmyArray.RemoveAt( ArmyIndex );

	// Inform all the client to give this army to the player
	SendAllPlayersArmyCard( PlayerIndex, ArmyIndex );

	// Now, this is to the next player to choose his army
	if( ++PlayerIndex>=m_PlayerArray.GetCount() )
		PlayerIndex = 0;
	if( theApp.m_GameType==CGameDoc::GAMETYPE_BASIC )
	{
		if( m_ArmyArray.GetCount()>0 )
		{
			if( ((CPlayer*) m_PlayerArray.GetAt(PlayerIndex))->m_ArmyList.GetCount()<theApp.m_GamePoint )
			{
				SendAllPlayersAction( PlayerIndex, ((CPlayer*) m_PlayerArray.GetAt(PlayerIndex))->GetName(), TA_CHOOSE_ARMY );
				return;
			}
		}
	}
	else if( theApp.m_GameType==CGameDoc::GAMETYPE_EXPERT )
	{
		for( int j=0; j<m_PlayerArray.GetCount(); j++ )
		{
			// Check if there are an army card which cost less or equal than you point
			for( int i=0; i<m_ArmyArray.GetCount(); i++ )
			{
				CArmyCard* pArmyCard = (CArmyCard*) m_ArmyArray.GetAt(i);
				if( pArmyCard->m_ExpertCostPoint<=((CPlayer*) m_PlayerArray.GetAt(PlayerIndex))->m_PointForArmy )
				{
					SendAllPlayersAction( PlayerIndex, ((CPlayer*) m_PlayerArray.GetAt(PlayerIndex))->GetName(), TA_CHOOSE_ARMY );
					return;
				}
			}
			if( ++PlayerIndex>=m_PlayerArray.GetCount() )
				PlayerIndex = 0;
		}
	}

	// Now it's time for next step (free action)
	m_CurrentStep = STEP_FREEGAME;
	SendAllPlayersAction( 0, ((CPlayer*) m_PlayerArray.GetAt(0))->GetName(), TA_FREEGAME );
}

// Send give army card to all the player
//
void CGameDocServer::SendAllPlayersArmyCard( int PlayerIndex, int ArmyIndex )
{
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( ArmyIndex );
		pPlayer->m_pToClientSocket->SendMessage( SMI_TOCLIENT_ARMYCHOOSED );
	}
}

// Place a figure for a player
//
void CGameDocServer::PlaceFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Inform all the player that a player has placed a figure
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( ArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( FigureIndex );
		pPlayer->m_pToClientSocket->WriteType( x );
		pPlayer->m_pToClientSocket->WriteType( y );
		pPlayer->m_pToClientSocket->WriteType( z );
		pPlayer->m_pToClientSocket->WriteType( Rotation );
		pPlayer->m_pToClientSocket->WriteType( CameraX );
		pPlayer->m_pToClientSocket->WriteType( CameraY );
		pPlayer->m_pToClientSocket->WriteType( CameraZ );
		pPlayer->m_pToClientSocket->WriteType( LookAtX );
		pPlayer->m_pToClientSocket->WriteType( LookAtY );
		pPlayer->m_pToClientSocket->WriteType( LookAtZ );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_FIGUREPLACED );
	}
}

// Place a figure for a player
//
void CGameDocServer::MoveFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Inform all the player that a player has placed a figure
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( ArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( FigureIndex );
		pPlayer->m_pToClientSocket->WriteType( x );
		pPlayer->m_pToClientSocket->WriteType( y );
		pPlayer->m_pToClientSocket->WriteType( z );
		pPlayer->m_pToClientSocket->WriteType( Rotation );
		pPlayer->m_pToClientSocket->WriteType( CameraX );
		pPlayer->m_pToClientSocket->WriteType( CameraY );
		pPlayer->m_pToClientSocket->WriteType( CameraZ );
		pPlayer->m_pToClientSocket->WriteType( LookAtX );
		pPlayer->m_pToClientSocket->WriteType( LookAtY );
		pPlayer->m_pToClientSocket->WriteType( LookAtZ );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_FIGUREMOVED );
	}
}

// Remove a figure for a player
//
void CGameDocServer::RemoveFigureForPlayer( int PlayerIndex, int RemovedPlayerIndex, int ArmyIndex, int FigureIndex, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Inform all the players that a player has removed a figure
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( RemovedPlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( ArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( FigureIndex );
		pPlayer->m_pToClientSocket->WriteType( CameraX );
		pPlayer->m_pToClientSocket->WriteType( CameraY );
		pPlayer->m_pToClientSocket->WriteType( CameraZ );
		pPlayer->m_pToClientSocket->WriteType( LookAtX );
		pPlayer->m_pToClientSocket->WriteType( LookAtY );
		pPlayer->m_pToClientSocket->WriteType( LookAtZ );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_FIGUREREMOVED );
	}
}

// An attack
//
void CGameDocServer::Attack( int PlayerIndex, int AttackPlayerIndex, int AttackArmyIndex, int AttackFigureIndex, int NbEnnemi, CPtrArray* pEnnemiList, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Inform all the players that a player launch an attack
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( AttackPlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( AttackArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( AttackFigureIndex );
		pPlayer->m_pToClientSocket->WriteType( NbEnnemi );
		for( int i=0; i<pEnnemiList->GetCount(); i++ )
		{
			CGameDoc::FigureInfos* pFigureInfo = (CGameDoc::FigureInfos*) pEnnemiList->GetAt(i);
			pPlayer->m_pToClientSocket->WriteType( pFigureInfo->PlayerIndex );
			pPlayer->m_pToClientSocket->WriteType( pFigureInfo->ArmyIndex );
			pPlayer->m_pToClientSocket->WriteType( pFigureInfo->FigureIndex );
		}
		pPlayer->m_pToClientSocket->WriteType( DiceLaunch );
		pPlayer->m_pToClientSocket->WriteType( DiceResult );
		pPlayer->m_pToClientSocket->WriteType( IsValueForced );
		pPlayer->m_pToClientSocket->WriteType( CameraX );
		pPlayer->m_pToClientSocket->WriteType( CameraY );
		pPlayer->m_pToClientSocket->WriteType( CameraZ );
		pPlayer->m_pToClientSocket->WriteType( LookAtX );
		pPlayer->m_pToClientSocket->WriteType( LookAtY );
		pPlayer->m_pToClientSocket->WriteType( LookAtZ );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_ATTACK );
	}
}

// A defense
//
void CGameDocServer::Defense( int PlayerIndex, int DefensePlayerIndex, int DefenseArmyIndex, int DefenseFigureIndex, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ )
{
	// Inform all the players that a player launch a defense
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( DefensePlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( DefenseArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( DefenseFigureIndex );
		pPlayer->m_pToClientSocket->WriteType( DiceLaunch );
		pPlayer->m_pToClientSocket->WriteType( DiceResult );
		pPlayer->m_pToClientSocket->WriteType( IsValueForced );
		pPlayer->m_pToClientSocket->WriteType( CameraX );
		pPlayer->m_pToClientSocket->WriteType( CameraY );
		pPlayer->m_pToClientSocket->WriteType( CameraZ );
		pPlayer->m_pToClientSocket->WriteType( LookAtX );
		pPlayer->m_pToClientSocket->WriteType( LookAtY );
		pPlayer->m_pToClientSocket->WriteType( LookAtZ );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_DEFENSE );
	}
}

// This is a next turn
//
void CGameDocServer::NextTurn( int PlayerIndex )
{
	// Inform all the players that a player launch a defense
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_NEXT_TURN );
	}
}

// Increment life of an army
//
void CGameDocServer::IncrementArmy( int PlayerIndex, int IncrementPlayerIndex, int IncrementArmyIndex )
{
	// Inform all the players that a player incremente life
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( IncrementPlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( IncrementArmyIndex );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_INCREMENT_LIFE );
	}
}

// Decrement life of an army
//
void CGameDocServer::DecrementArmy( int PlayerIndex, int DecrementPlayerIndex, int DecrementArmyIndex )
{
	// Inform all the players that a player incremente life
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( DecrementPlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( DecrementArmyIndex );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_DECREMENT_LIFE );
	}
}

// Add a predicted marquer
//
void CGameDocServer::AddPredictedMarquer( int PlayerIndex, int PredictedPlayerIndex, int PredictedArmyIndex, int PredictedMarquer )
{
	// Inform all the players that a predicted marquer is add
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( PredictedPlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( PredictedArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( PredictedMarquer );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_ADD_PREDICTED_MARQUER );
	}
}

// Remove all marquer
//
void CGameDocServer::RemoveMarquer( int PlayerIndex )
{
	// Inform all the players that marquer are remove
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_REMOVE_MARQUER );
	}
}

// Show a predicted marquer
//
void CGameDocServer::ShowPredictedMarquer( int PlayerIndex, int PredictedPlayerIndex, int PredictedArmyIndex, int PredictedMarquer )
{
	// Inform all the players that a predicted marquer is add
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( PredictedPlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( PredictedArmyIndex );
		pPlayer->m_pToClientSocket->WriteType( PredictedMarquer );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_SHOW_PREDICTED_MARQUER );
	}
}

// Launch a die 20 faces
//
void CGameDocServer::Die20Faces( int PlayerIndex, int DieResult )
{
	// Inform all the players that a die 20 faces has been launch
	for( int i=0; i<m_PlayerArray.GetCount(); i++ )
	{
		CPlayer* pPlayer = (CPlayer*) m_PlayerArray.GetAt(i);
		pPlayer->m_pToClientSocket->CreateBuffer();
		pPlayer->m_pToClientSocket->WriteType( PlayerIndex );
		pPlayer->m_pToClientSocket->WriteType( DieResult );
		pPlayer->m_pToClientSocket->SendMessageW( SMI_TOCLIENT_DIE_20_FACES );
	}
}



