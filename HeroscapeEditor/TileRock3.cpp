// TileRock3.cpp : implementation file
//

#include "StdAfx.h"

#include "TileRock3.h"

// The constructor
//
CTileRock3::CTileRock3()
{
	m_NbTile = 3;
	m_Type = TYPE_ROCK*1000+m_NbTile;
	m_TileColor = RGB(170,170,170);

	Init();
}

// The destructor
//
CTileRock3::~CTileRock3()
{
}

// Get a copy of this tile
//
CTile* CTileRock3::GetCopy()
{
	return new CTileRock3;
}

// When the rotation change
//
void CTileRock3::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
	case 2:
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 1:
	case 3:
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	}
}
