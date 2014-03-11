// TileAsphalt7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileAsphalt7.h"

// The constructor
//
CTileAsphalt7::CTileAsphalt7()
{
	m_NbTile = 7;
	m_Type = TYPE_ASPHALT*1000+m_NbTile;
	m_TileColor = RGB(120,120,120);
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
CTileAsphalt7::~CTileAsphalt7()
{
}

// Get a copy of this tile
//
CTile* CTileAsphalt7::GetCopy()
{
	return new CTileAsphalt7;
}
