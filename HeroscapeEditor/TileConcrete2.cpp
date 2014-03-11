// TileConcrete2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileConcrete2.h"

// The constructor
//
CTileConcrete2::CTileConcrete2()
{
	m_NbTile = 2;
	m_Type = TYPE_CONCRETE*1000+m_NbTile;
	m_TileColor = RGB(220,220,220);

	Init();
}

// The destructor
//
CTileConcrete2::~CTileConcrete2()
{
}

// Get a copy of this tile
//
CTile* CTileConcrete2::GetCopy()
{
	return new CTileConcrete2;
}

// When the rotation change
//
void CTileConcrete2::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
	case 3:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		break;
	case 1:
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 2:
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	}
}
