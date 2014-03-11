// TileWater1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileWater1.h"

// The constructor
//
CTileWater1::CTileWater1()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_WATER*1000+m_NbTile;
	m_TileColor = RGB(32,32,255);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileWater1::~CTileWater1()
{
}

// Get a copy of this tile
//
CTile* CTileWater1::GetCopy()
{
	return new CTileWater1;
}
