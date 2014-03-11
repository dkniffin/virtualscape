#pragma once

#include "ArmyCard.h"
#include "ServerSocket.h"

class CPlayer
{
//************
// The defines
//************
protected:

// The draw list ctrl position
#define DLC_PLAYER_NAME_OFFSET_X		5
#define DLC_PLAYER_NAME_OFFSET_Y		5
#define DLC_ARMY_OFFSET_X				10
#define DLC_ARMY_OFFSET_Y				25
#define DLC_ARMY_CARD_HEIGHT			130
#define DLC_ARMY_CARD_WIDTH				160

//**********
// The enums
//**********
public:
	// The player type
	enum PlayerType
	{
		PT_SERVER,
		PT_CLIENT
	};

//************
// The members
//************
protected:
	// The name
	CString			m_Name;

public:
	// The socket
	CServerSocket*	m_pToClientSocket;
	// The state
	int				m_Type;
	// Point for army
	int				m_PointForArmy;
	// The army list
	CPtrArray		m_ArmyList;

//************
// The methods
//************
public:
	// The constructor
	CPlayer(void);
	// The destructor
	~CPlayer(void);
	// Set the name
	void SetName( CString Name );
	// Get the name
	CString GetName();
	// Draw the player state (on list player ctrl)
	void	DrawState( CDC* pDC, int OffsetX, int OffsetY, int PlayerIndex );
	// Return the height (in pixel) for drawing in the list player Ctrl.
	int		GetStateHeight();
	// Return the width (in pixel) for drawing in the list player Ctrl.
	int		GetStateWidth();
	// Add an army to the player
	void	AddArmy( CArmyCard* pArmyCard );
};
