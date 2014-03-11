// TileSwampWater1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSwampWater1.h"

// The constructor
//
CTileSwampWater1::CTileSwampWater1()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_SWAMPWATER*1000+m_NbTile;
	m_TileColor = RGB(222,210,42);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileSwampWater1::~CTileSwampWater1()
{
}

// Get a copy of this tile
//
CTile* CTileSwampWater1::GetCopy()
{
	return new CTileSwampWater1;
}
