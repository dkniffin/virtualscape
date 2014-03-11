// TileLavaField1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileLavaField1.h"

// The constructor
//
CTileLavaField1::CTileLavaField1()
{
	m_NbTile = 1;
	m_Type = TYPE_LAVAFIELD*1000+m_NbTile;
	m_TileColor = RGB(160,32,32);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileLavaField1::~CTileLavaField1()
{
}

// Get a copy of this tile
//
CTile* CTileLavaField1::GetCopy()
{
	return new CTileLavaField1;
}
