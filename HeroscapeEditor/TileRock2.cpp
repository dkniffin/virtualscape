// TileRock2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileRock2.h"

// The constructor
//
CTileRock2::CTileRock2()
{
	m_NbTile = 2;
	m_Type = TYPE_ROCK*1000+m_NbTile;
	m_TileColor = RGB(170,170,170);

	Init();
}

// The destructor
//
CTileRock2::~CTileRock2()
{
}

// Get a copy of this tile
//
CTile* CTileRock2::GetCopy()
{
	return new CTileRock2;
}

// When the rotation change
//
void CTileRock2::OnRotationChange()
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
