// TileLavaField7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileLavaField7.h"

// The constructor
//
CTileLavaField7::CTileLavaField7()
{
	m_NbTile = 7;
	m_Type = TYPE_LAVAFIELD*1000+m_NbTile;
	m_TileColor = RGB(160,32,32);
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
CTileLavaField7::~CTileLavaField7()
{
}

// Get a copy of this tile
//
CTile* CTileLavaField7::GetCopy()
{
	return new CTileLavaField7;
}
