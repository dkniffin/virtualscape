// TileSwamp24.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSwamp24.h"

// The constructor
//
CTileSwamp24::CTileSwamp24()
{
	m_NbTile = 24;
	m_Type = TYPE_SWAMP*1000+m_NbTile;
	m_TileColor = RGB(111,105,21);

	Init();
}

// The destructor
//
CTileSwamp24::~CTileSwamp24()
{
}

// Get a copy of this tile
//
CTile* CTileSwamp24::GetCopy()
{
	return new CTileSwamp24;
}

// When the rotation change
//
void CTileSwamp24::OnRotationChange()
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
