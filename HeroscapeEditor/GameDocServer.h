#pragma once

#include "ClientSocket.h"
#include "ConnexionSocket.h"
#include "GameDoc.h"
#include "Player.h"
#include "Tile.h"

// Document CGameDocServer

class CGameDocServer : public CGameDoc
{
	DECLARE_DYNCREATE(CGameDocServer)

//**********
// The enums
//**********
public:
	enum Step
	{
		STEP_CONNEXION = 1,
		STEP_CHOOSE_ARMY,
		STEP_FREEGAME
	};

//************
// The members
//************
protected:
	// The broadcast socket
	CConnexionSocket	m_BroadcastSocket;
	// The connexion socket to receive connexion from other players
	CConnexionSocket	m_ConnexionSocket;

public:
	// The current step of the game
	int					m_CurrentStep;

//************
// The methods
//************
public:
	// The constructor
	CGameDocServer();
	// The destructor
	virtual ~CGameDocServer();
	// Add a player to the game
	void AddPlayer( CPlayer* pPlayer );
	// Remove a player from the game
	void RemovePlayer( CPlayer* pPlayer );
	// Send the players list to all the client
	void SendAllPlayersToAllClients();
	// Send a message text to everybody
	void SendMessageTextToEverybody( int FromIndex, CString From, CString Message );
	// Initialise the game
	void InitGame();
	// Send the tiles to all the players
	void SendTilesToAllPlayers();
	// Send all player an action
	void SendAllPlayersAction( int PlayerIndex, CString PlayerName, int Action );
	// Add an army to a player
	void AddArmyToPlayer( int PlayerIndex, int ArmyIndex );
	// Send give army card to all the player
	void SendAllPlayersArmyCard( int PlayerIndex, int ArmyIndex );
	// Place a figure for a player
	void PlaceFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// Move a figure for a player
	void MoveFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// Remove a figure for a player
	void RemoveFigureForPlayer( int PlayerIndex, int RemovedPlayerIndex, int ArmyIndex, int FigureIndex, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// An attack
	void Attack( int PlayerIndex, int AttackPlayerIndex, int AttackArmyIndex, int AttackFigureIndex, int NbEnnemi, CPtrArray* pEnnemiList, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// A defense
	void Defense( int PlayerIndex, int DefensePlayerIndex, int DefenseArmyIndex, int DefenseFigureIndex, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// This is a next turn
	void NextTurn( int PlayerIndex );
	// Increment life of an army
	void IncrementArmy( int PlayerIndex, int IncrementPlayerIndex, int IncrementArmyIndex );
	// Decrement life of an army
	void DecrementArmy( int PlayerIndex, int IncrementPlayerIndex, int IncrementArmyIndex );
	// Add a predicted marquer
	void AddPredictedMarquer( int PlayerIndex, int PredictedPlayerIndex, int PredictedArmyIndex, int PredictedMarquer );
	// Show a predicted marquer
	void ShowPredictedMarquer( int PlayerIndex, int PredictedPlayerIndex, int PredictedArmyIndex, int PredictedMarquer );
	// Remove all marquer
	void RemoveMarquer( int PlayerIndex );
	// Launch a die 20 faces
	void Die20Faces( int PlayerIndex, int DieResult );

	DECLARE_MESSAGE_MAP()
};
