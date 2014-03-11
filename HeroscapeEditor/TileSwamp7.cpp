// TileSwamp7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSwamp7.h"

// The constructor
//
CTileSwamp7::CTileSwamp7()
{
	m_NbTile = 7;
	m_Type = TYPE_SWAMP*1000+m_NbTile;
	m_TileColor = RGB(111,105,21);
	int CurrentPos = 0;
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

	Init();
}

// The destructor
//
CTileSwamp7::~CTileSwamp7()
{
}

// Get a copy of this tile
//
CTile* CTileSwamp7::GetCopy()
{
	return new CTileSwamp7;
}
