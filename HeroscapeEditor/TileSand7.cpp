// TileSand7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSand7.h"

// The constructor
//
CTileSand7::CTileSand7()
{
	m_NbTile = 7;
	m_Type = TYPE_SAND*1000+m_NbTile;
	m_TileColor = RGB(206,172,40);
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
CTileSand7::~CTileSand7()
{
}

// Get a copy of this tile
//
CTile* CTileSand7::GetCopy()
{
	return new CTileSand7;
}
