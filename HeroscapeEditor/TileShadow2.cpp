// TileShadow2.cpp : implementation file
//

#include "StdAfx.h"

#include "TileShadow2.h"

// The constructor
//
CTileShadow2::CTileShadow2()
{
	m_NbTile = 2;
	m_Type = TYPE_SHADOW*1000+2;
	m_TileColor = RGB(0,0,0);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileShadow2::~CTileShadow2()
{
}

// Get a copy of this tile
//
CTile* CTileShadow2::GetCopy()
{
	return new CTileShadow2;
}

// Render a tile
//
void CTileShadow2::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	m_NbTile = 1;
	CTile::Render1( pView, ForShadow, BindTexture );
	m_NbTile = 2;
}

