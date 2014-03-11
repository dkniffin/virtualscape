#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "Player.h"

// The constructor
//
CPlayer::CPlayer(void)
{
	m_Name = "---";
	m_Type = PT_CLIENT;
	m_pToClientSocket = new CServerSocket( this );
}

// The destructor
//
CPlayer::~CPlayer(void)
{
	m_pToClientSocket->Close();
	delete m_pToClientSocket;
}

// Set the name
//
void CPlayer::SetName( CString Name )
{
	m_Name = Name;
}

// Get the name
//
CString CPlayer::GetName()
{
	return m_Name;
}

// Draw the player state (on list player ctrl)
//
void CPlayer::DrawState( CDC* pDC, int OffsetX, int OffsetY, int PlayerIndex )
{
	// Draw Name
	pDC->FillSolidRect( OffsetX, OffsetY, 2000, DLC_ARMY_OFFSET_Y, RGB(0,0,255) );
	pDC->SetTextColor( RGB(255,255,255) );
	pDC->TextOutW(OffsetX+DLC_PLAYER_NAME_OFFSET_X,OffsetY+DLC_PLAYER_NAME_OFFSET_Y, m_Name );

	pDC->SetTextColor( RGB(0,0,0) );
	pDC->SetBkMode( TRANSPARENT );
	int PosX = OffsetX+DLC_ARMY_OFFSET_X;
	int PosY = OffsetY+DLC_ARMY_OFFSET_Y;

	for( int i=0; i<m_ArmyList.GetCount(); i++ )
	{
		CArmyCard* pArmyCard = (CArmyCard*) m_ArmyList.GetAt(i);
		pArmyCard->Draw( pDC, PosX, PosY, DLC_ARMY_CARD_WIDTH, DLC_ARMY_CARD_HEIGHT, false, PlayerIndex );
		PosY += DLC_ARMY_CARD_HEIGHT+5;
	}
}

// Return the height (in pixel) for drawing in the list player Ctrl.
//
int CPlayer::GetStateHeight()
{
	return DLC_ARMY_OFFSET_Y+(DLC_ARMY_CARD_HEIGHT+5)*m_ArmyList.GetCount();
}

// Return the width (in pixel) for drawing in the list player Ctrl.
//
int CPlayer::GetStateWidth()
{
	return DLC_ARMY_OFFSET_X+DLC_ARMY_CARD_WIDTH+5;
}

// Add an army to the player
//
void CPlayer::AddArmy( CArmyCard* pArmyCard )
{
	m_ArmyList.Add( pArmyCard );
	if( theApp.m_GameType==CGameDoc::GAMETYPE_EXPERT )
		m_PointForArmy -= pArmyCard->m_ExpertCostPoint;
}

