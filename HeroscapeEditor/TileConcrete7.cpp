// TileConcrete7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileConcrete7.h"

// The constructor
//
CTileConcrete7::CTileConcrete7()
{
	m_NbTile = 7;
	m_Type = TYPE_CONCRETE*1000+m_NbTile;
	m_TileColor = RGB(220,220,220);
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
CTileConcrete7::~CTileConcrete7()
{
}

// Get a copy of this tile
//
CTile* CTileConcrete7::GetCopy()
{
	return new CTileConcrete7;
}
