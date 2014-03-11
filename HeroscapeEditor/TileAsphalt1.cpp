// TileAsphalt1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileAsphalt1.h"

// The constructor
//
CTileAsphalt1::CTileAsphalt1()
{
	m_NbTile = 1;
	m_Type = TYPE_ASPHALT*1000+m_NbTile;
	m_TileColor = RGB(120,120,120);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileAsphalt1::~CTileAsphalt1()
{
}

// Get a copy of this tile
//
CTile* CTileAsphalt1::GetCopy()
{
	return new CTileAsphalt1;
}
