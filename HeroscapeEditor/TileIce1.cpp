// TileIce1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileIce1.h"

// The constructor
//
CTileIce1::CTileIce1()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_ICE*1000+m_NbTile;
	m_TileColor = RGB(180,180,255);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileIce1::~CTileIce1()
{
}

// Get a copy of this tile
//
CTile* CTileIce1::GetCopy()
{
	return new CTileIce1;
}
