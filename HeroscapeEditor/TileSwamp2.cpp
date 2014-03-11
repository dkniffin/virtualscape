// TileSWAMP2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSwamp2.h"

// The constructor
//
CTileSwamp2::CTileSwamp2()
{
	m_NbTile = 2;
	m_Type = TYPE_SWAMP*1000+m_NbTile;
	m_TileColor = RGB(111,105,21);

	Init();
}

// The destructor
//
CTileSwamp2::~CTileSwamp2()
{
}

// Get a copy of this tile
//
CTile* CTileSwamp2::GetCopy()
{
	return new CTileSwamp2;
}

// When the rotation change
//
void CTileSwamp2::OnRotationChange()
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
