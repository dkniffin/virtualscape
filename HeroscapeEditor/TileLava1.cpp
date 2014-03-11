// TileLava1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileLava1.h"

// The constructor
//
CTileLava1::CTileLava1()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_LAVA*1000+m_NbTile;
	m_TileColor = RGB(255,64,64);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileLava1::~CTileLava1()
{
}

// Get a copy of this tile
//
CTile* CTileLava1::GetCopy()
{
	return new CTileLava1;
}
