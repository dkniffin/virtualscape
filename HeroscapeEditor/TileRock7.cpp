// TileRock7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileRock7.h"

// The constructor
//
CTileRock7::CTileRock7()
{
	m_NbTile = 7;
	m_Type = TYPE_ROCK*1000+m_NbTile;
	m_TileColor = RGB(170,170,170);
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
CTileRock7::~CTileRock7()
{
}

// Get a copy of this tile
//
CTile* CTileRock7::GetCopy()
{
	return new CTileRock7;
}
