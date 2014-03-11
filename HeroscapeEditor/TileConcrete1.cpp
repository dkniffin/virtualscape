// TileConcrete1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileConcrete1.h"

// The constructor
//
CTileConcrete1::CTileConcrete1()
{
	m_NbTile = 1;
	m_Type = TYPE_CONCRETE*1000+m_NbTile;
	m_TileColor = RGB(220,220,220);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileConcrete1::~CTileConcrete1()
{
}

// Get a copy of this tile
//
CTile* CTileConcrete1::GetCopy()
{
	return new CTileConcrete1;
}
