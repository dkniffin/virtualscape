// TileRock1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileRock1.h"

// The constructor
//
CTileRock1::CTileRock1()
{
	m_NbTile = 1;
	m_Type = TYPE_ROCK*1000+m_NbTile;
	m_TileColor = RGB(170,170,170);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileRock1::~CTileRock1()
{
}

// Get a copy of this tile
//
CTile* CTileRock1::GetCopy()
{
	return new CTileRock1;
}
