// TileSnow2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSnow2.h"

// The constructor
//
CTileSnow2::CTileSnow2()
{
	m_NbTile = 2;
	m_Type = TYPE_SNOW*1000+m_NbTile;
	m_TileColor = RGB(255,255,255);

	Init();
}

// The destructor
//
CTileSnow2::~CTileSnow2()
{
}

// Get a copy of this tile
//
CTile* CTileSnow2::GetCopy()
{
	return new CTileSnow2;
}

// When the rotation change
//
void CTileSnow2::OnRotationChange()
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
