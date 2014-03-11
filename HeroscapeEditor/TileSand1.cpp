// TileSand1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSand1.h"

// The constructor
//
CTileSand1::CTileSand1()
{
	m_NbTile = 1;
	m_Type = TYPE_SAND*1000+m_NbTile;
	m_TileColor = RGB(206,172,40);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileSand1::~CTileSand1()
{
}

// Get a copy of this tile
//
CTile* CTileSand1::GetCopy()
{
	return new CTileSand1;
}
