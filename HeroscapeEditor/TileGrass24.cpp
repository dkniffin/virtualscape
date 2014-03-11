// TileGrass24.cpp : implementation file
//

#include "StdAfx.h"

#include "TileGrass24.h"

// The constructor
//
CTileGrass24::CTileGrass24()
{
	m_NbTile = 24;
	m_Type = TYPE_GRASS*1000+m_NbTile;
	m_TileColor = RGB(0,160,0);

	Init();
}

// The destructor
//
CTileGrass24::~CTileGrass24()
{
}

// Get a copy of this tile
//
CTile* CTileGrass24::GetCopy()
{
	return new CTileGrass24;
}

// When the rotation change
//
void CTileGrass24::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	case 1:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 7;
		break;
	case 2:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	case 3:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 5;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 5;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 5;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 7;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 7;
		break;
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -4;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -4;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -4;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	}
}
