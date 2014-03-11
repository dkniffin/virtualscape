// TileWater2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileWater2.h"

// The constructor
//
CTileWater2::CTileWater2()
{
	m_NbTile = 2;
	m_Type = TYPE_WATER*1000+2;
	m_TileColor = RGB(32,32,255);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileWater2::~CTileWater2()
{
}

// Get a copy of this tile
//
CTile* CTileWater2::GetCopy()
{
	return new CTileWater2;
}

// Render a tile
//
void CTileWater2::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	m_NbTile = 1;
	CTile::Render1( pView, ForShadow, BindTexture );
	m_NbTile = 2;
}

