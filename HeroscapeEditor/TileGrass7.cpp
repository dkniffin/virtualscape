// TileGrass7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileGrass7.h"

// The constructor
//
CTileGrass7::CTileGrass7()
{
	m_NbTile = 7;
	m_Type = TYPE_GRASS*1000+m_NbTile;
	m_TileColor = RGB(0,160,0);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;
	m_TilePosition[CurrentPos].x = 1;
	m_TilePosition[CurrentPos++].y = 0;
	m_TilePosition[CurrentPos].x = -1;
	m_TilePosition[CurrentPos++].y = 1;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 1;
	m_TilePosition[CurrentPos].x = 1;
	m_TilePosition[CurrentPos++].y = 1;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 2;
	m_TilePosition[CurrentPos].x = 1;
	m_TilePosition[CurrentPos++].y = 2;

	Init();
}

// The destructor
//
CTileGrass7::~CTileGrass7()
{
}

// Get a copy of this tile
//
CTile* CTileGrass7::GetCopy()
{
	return new CTileGrass7;
}
