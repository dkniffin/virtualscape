// TileSnow1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSnow1.h"

// The constructor
//
CTileSnow1::CTileSnow1()
{
	m_NbTile = 1;
	m_Type = TYPE_SNOW*1000+m_NbTile;
	m_TileColor = RGB(255,255,255);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileSnow1::~CTileSnow1()
{
}

// Get a copy of this tile
//
CTile* CTileSnow1::GetCopy()
{
	return new CTileSnow1;
}
