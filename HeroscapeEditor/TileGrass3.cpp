// TileGrass3.cpp : implementation file
//

#include "StdAfx.h"

#include "TileGrass3.h"

// The constructor
//
CTileGrass3::CTileGrass3()
{
	m_NbTile = 3;
	m_Type = TYPE_GRASS*1000+m_NbTile;
	m_TileColor = RGB(0,160,0);

	Init();
}

// The destructor
//
CTileGrass3::~CTileGrass3()
{
}

// Get a copy of this tile
//
CTile* CTileGrass3::GetCopy()
{
	return new CTileGrass3;
}

// When the rotation change
//
void CTileGrass3::OnRotationChange()
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
