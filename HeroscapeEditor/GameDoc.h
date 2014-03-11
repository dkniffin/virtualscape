#pragma once

#include "ClientSocket.h"
#include "ConnexionSocket.h"
#include "FigureObject.h"
#include "HeroscapeEditorDoc.h"
#include "Player.h"
#include "Tile.h"

// Document CGameDoc

class CGameDoc : public CHeroscapeEditorDoc
{
	DECLARE_DYNCREATE(CGameDoc)

//**********
// The enums
//**********
public:
	// Action type
	enum ActionType
	{
		TA_NONE = 0,
		TA_CHOOSE_ARMY,
		TA_FREEGAME
	};

	// The game mode
	enum GameMode
	{
		GAMEMODE_NULL = 0,
		GAMEMODE_FREE,
		GAMEMODE_PLACEFIGURE,
		GAMEMODE_REMOVEFIGURE,
		GAMEMODE_MOVEFIGURE,
		GAMEMODE_ATTACK_CHOOSEFIGUREATTACK,
		GAMEMODE_ATTACK_CHOOSEFIGUREENEMI,
		GAMEMODE_DEFENSEFIGURE
	};

	// The animation type
	enum AnimationType
	{
		ANIMATIONTYPE_TURNING = 0,
		ANIMATIONTYPE_SIMPLE,
		ANIMATIONTYPE_REPLAY
	};

	// The game type
	enum GameType
	{
		GAMETYPE_BASIC = 0,
		GAMETYPE_EXPERT
	};

	// A figure info
	typedef struct FigureInfosTag
	{
		CFigureObject*	pFigure;
		int				FigureIndex;
		int				ArmyIndex;
		int				PlayerIndex;
	}FigureInfos;

//************
// The members
//************
public:
	// The players array
	CPtrArray			m_PlayerArray;
	// The army array
	CPtrArray			m_ArmyArray;
	// To know if this gamedoc is server game doc
	bool				m_IsServer;
	// The socket toward server if we are a client
	CClientSocket		m_ToServerSocket;
	// The player index
	int					m_PlayerIndex;
	// The Battlefield Name
	CString				m_BattleFieldName;
	// The game mode
	GameMode			m_GameMode;
	// To know current figure
	int					m_CurrentFigurePlayerIndex;
	int					m_CurrentFigureArmyIndex;
	int					m_CurrentFigureIndex;
	CFigureObject*		m_pCurrentFigure;
	CTile*				m_pCurrentFigureTile;
	// The attack figure for attack 
	FigureInfos			m_FigureAttack;
	// The defense figure list
	CPtrArray			m_FigureDefenseList;
	// When we receive a defence dice, need to memorise who attack and who defense for display animation of attack
	CFigureObject*		m_pCurrentFigureAttack;
	CFigureObject*		m_pCurrentFigureDefense;
	// The animation type
	AnimationType		m_AnimationType;
	// The old animation type (use by replay)
	AnimationType		m_OldAnimationType;
	// The current player index for Contextual menu
	int					m_CurrentPlayerIndexCM;
	// The current army index for contextual menu
	int					m_CurrentArmyIndexCM;
	// The current game point
	int					m_GamePoint;


//************
// The methods
//************
public:
	// The constructor
	CGameDoc();
	// The destructor
	virtual ~CGameDoc();
	// Save or load game
	virtual void Serialize(CArchive& ar);
	// Receive the players list
	void ReceivePlayersList( CClientSocket* pSocket );
	// Add a tile to the list
	void AddTile( CTile* pTile );
	// Init the game doc
	void Init();
	// Compute the differents param
	void ComputeArea();
	// Compute the level Max
	void ComputeLevelMax();
	// Load all the necessary objects (as figures)
	void LoadNecessaryObjects( void* pView );
	// Redraw all the views
	void UpdateAll3DViews();
	// Choose your army
	void ChooseArmy();
	// Set the point for army in this game
	void SetGamePoint( int GamePoint );
	// Add an army to a player
	virtual void AddArmyToPlayer( int PlayerIndex, int ArmyIndex );
	// Place a figure for a player
	virtual void PlaceFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// Move a figure for a player
	virtual void MoveFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, int x, int y, int z, int Rotation, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// Enter in free game mode
	virtual void FreeGame();
	// The user has choose a position
	virtual void SetCurrentSelectedPosition( int x, int y, int z, int Rotation );
	// The user has choose a figure
	virtual void SetCurrentSelectedFigure( CFigureObject* pFigure );
	// To know if a tile is already in the list
	bool IsTileInTileList( CTile* pTile );
	// Get the figure at a particular pos
	CFigureObject* GetFigureAtPos( int PositionX, int PositionY, int PositionZ );
	// Remove a figure from the map
	void RemoveFigureFromMap( CFigureObject* pFigure );
	// Remove a tile to the list
	void RemoveTile( CTile* pTile );
	// Remove a figure for a player
	void RemoveFigureForPlayer( int PlayerIndex, int ArmyIndex, int FigureIndex, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// An attack
	void Attack( int PlayerIndex, int AttackPlayerIndex, int AttackArmyIndex, int AttackFigureIndex, int NbEnnemi, CPtrArray* pEnnemiList, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// A defense
	void Defense( int PlayerIndex, int DefensePlayerIndex, int DefenseArmyIndex, int DefenseFigureIndex, int DiceLaunch, int DiceResult, int IsValueForced, double CameraX, double CameraY, double CameraZ, double LookAtX, double LookAtY, double LookAtZ );
	// Set all the figures to normal state
	void ResetAllFigure();
	// Receive a message that this is next turn
	void NextTurn( int PlayerIndex );
	// Set all the figures to normal state but not displayed
	void ResetAllFigureToBegining();
	// Set the game type
	void SetGameType( int GameType );
	// Increment life of an army
	void OnIncrementLife( int PlayerIndex, int ArmyIndex );
	// Decrement life of an army
	void OnDecrementLife( int PlayerIndex, int ArmyIndex );
	// Receive message to increment life of an army
	void IncrementLife( int IncrementPlayerIndex, int IncrementArmyIndex );
	// Receive message to decrement life of an army
	void DecrementLife( int DecrementPlayerIndex, int DecrementArmyIndex );
	// Add a predicted marquer
	void OnAddPredictedMarquer( int PlayerIndex, int ArmyIndex, int PredictedMarquer );
	// Receive message to add a predicted marquer
	void AddPredictedMarquer( int PlayerIndex, int ArmyIndex, int PredictedMarquer );
	// Show a predicted marquer
	void OnShowPredictedMarquer( int PlayerIndex, int ArmyIndex );
	// Receive message to show a predicted marquer
	void ShowPredictedMarquer( int PlayerIndex, int ArmyIndex, int PredictedMarquer );
	// Remove marquer
	void OnRemoveMarquer( int PlayerIndex, int ArmyIndex );
	// Remove marquer
	void RemoveMarquer( int PlayerIndex );
	// Reset all the army card
	void ResetAllArmyCard();
	// Reset all the chat
	void ResetAllChat();
	// Reset all the action
	void ResetAllAction();
	// Remove all the marquer
	void ResetAllMarquer();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnJouerQuitterlejeu();
	afx_msg void OnPlaceFigureOnMap();
	afx_msg void OnRemoveFigureFromMap();
	afx_msg void OnMoveFigure();
	afx_msg void OnAttackChooseFigure();
	afx_msg void OnAttackDice();
	afx_msg void OnDefenseDice();
	afx_msg void OnNextTurn();
	afx_msg void OnOutilsAnimationssimples();
	afx_msg void OnUpdateOutilsAnimationssimples(CCmdUI *pCmdUI);
	afx_msg void OnOutilsAnimationstournante();
	afx_msg void OnUpdateOutilsAnimationstournante(CCmdUI *pCmdUI);
	afx_msg void OnReplayGame();
	afx_msg void OnReplayToFile();
	afx_msg void OnDie20Faces();
};
