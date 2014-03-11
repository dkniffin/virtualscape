// TileAsphalt2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileAsphalt2.h"

// The constructor
//
CTileAsphalt2::CTileAsphalt2()
{
	m_NbTile = 2;
	m_Type = TYPE_ASPHALT*1000+m_NbTile;
	m_TileColor = RGB(120,120,120);

	Init();
}

// The destructor
//
CTileAsphalt2::~CTileAsphalt2()
{
}

// Get a copy of this tile
//
CTile* CTileAsphalt2::GetCopy()
{
	return new CTileAsphalt2;
}

// When the rotation change
//
void CTileAsphalt2::OnRotationChange()
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
