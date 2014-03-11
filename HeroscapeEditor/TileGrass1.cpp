// TileGrass1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileGrass1.h"

// The constructor
//
CTileGrass1::CTileGrass1()
{
	m_NbTile = 1;
	m_Type = TYPE_GRASS*1000+m_NbTile;
	m_TileColor = RGB(0,160,0);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileGrass1::~CTileGrass1()
{
}

// Get a copy of this tile
//
CTile* CTileGrass1::GetCopy()
{
	return new CTileGrass1;
}
