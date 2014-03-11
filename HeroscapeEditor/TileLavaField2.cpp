// TileLavaField2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileLavaField2.h"

// The constructor
//
CTileLavaField2::CTileLavaField2()
{
	m_NbTile = 2;
	m_Type = TYPE_LAVAFIELD*1000+m_NbTile;
	m_TileColor = RGB(160,32,32);

	Init();
}

// The destructor
//
CTileLavaField2::~CTileLavaField2()
{
}

// Get a copy of this tile
//
CTile* CTileLavaField2::GetCopy()
{
	return new CTileLavaField2;
}

// When the rotation change
//
void CTileLavaField2::OnRotationChange()
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
