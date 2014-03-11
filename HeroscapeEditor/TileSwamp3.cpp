// TileSwamp3.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSwamp3.h"

// The constructor
//
CTileSwamp3::CTileSwamp3()
{
	m_NbTile = 3;
	m_Type = TYPE_SWAMP*1000+m_NbTile;
	m_TileColor = RGB(111,105,21);

	Init();
}

// The destructor
//
CTileSwamp3::~CTileSwamp3()
{
}

// Get a copy of this tile
//
CTile* CTileSwamp3::GetCopy()
{
	return new CTileSwamp3;
}

// When the rotation change
//
void CTileSwamp3::OnRotationChange()
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
