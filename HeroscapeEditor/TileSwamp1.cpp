// TileSwamp1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileSwamp1.h"

// The constructor
//
CTileSwamp1::CTileSwamp1()
{
	m_NbTile = 1;
	m_Type = TYPE_SWAMP*1000+m_NbTile;
	m_TileColor = RGB(111,105,21);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileSwamp1::~CTileSwamp1()
{
}

// Get a copy of this tile
//
CTile* CTileSwamp1::GetCopy()
{
	return new CTileSwamp1;
}
