// TileSand2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSand2.h"

// The constructor
//
CTileSand2::CTileSand2()
{
	m_NbTile = 2;
	m_Type = TYPE_SAND*1000+m_NbTile;
	m_TileColor = RGB(206,172,40);

	Init();
}

// The destructor
//
CTileSand2::~CTileSand2()
{
}

// Get a copy of this tile
//
CTile* CTileSand2::GetCopy()
{
	return new CTileSand2;
}

// When the rotation change
//
void CTileSand2::OnRotationChange()
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
