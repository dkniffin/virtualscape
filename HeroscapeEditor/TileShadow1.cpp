// TileShadow1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileShadow1.h"

// The constructor
//
CTileShadow1::CTileShadow1()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_SHADOW*1000+m_NbTile;
	m_TileColor = RGB(0,0,0);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileShadow1::~CTileShadow1()
{
}

// Get a copy of this tile
//
CTile* CTileShadow1::GetCopy()
{
	return new CTileShadow1;
}
