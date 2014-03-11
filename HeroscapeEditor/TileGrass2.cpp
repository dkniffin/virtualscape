// TileGrass2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileGrass2.h"

// The constructor
//
CTileGrass2::CTileGrass2()
{
	m_NbTile = 2;
	m_Type = TYPE_GRASS*1000+m_NbTile;
	m_TileColor = RGB(0,160,0);

	Init();
}

// The destructor
//
CTileGrass2::~CTileGrass2()
{
}

// Get a copy of this tile
//
CTile* CTileGrass2::GetCopy()
{
	return new CTileGrass2;
}

// When the rotation change
//
void CTileGrass2::OnRotationChange()
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
