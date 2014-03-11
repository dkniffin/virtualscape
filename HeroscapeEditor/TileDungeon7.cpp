// TileDungeon7.cpp : implementation file
//

#include "StdAfx.h"

#include "TileDungeon7.h"

// The constructor
//
CTileDungeon7::CTileDungeon7()
{
	m_NbTile = 7;
	m_Type = TYPE_DUNGEON*1000+m_NbTile;
	m_TileColor = RGB(220,220,220);
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
CTileDungeon7::~CTileDungeon7()
{
}

// Get a copy of this tile
//
CTile* CTileDungeon7::GetCopy()
{
	return new CTileDungeon7;
}

// Draw more on a tile
//
void CTileDungeon7::DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	POINT Points[10];

	double LowColor = GetLowColor( DrawingLevel );

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,10+(255-10)*LowColor),min(255,10+(255-10)*LowColor),min(255,10+(255-10)*LowColor)) );
	CBrush* poldBrush = pDC->SelectObject( &Brush );

	int CurrentPoint = 0;
	Points[CurrentPoint].x = (int) (x+x2/2.5);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)/4);
	Points[CurrentPoint].x = (int) (x+x2/1.4);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)/3);
	Points[CurrentPoint].x = (int) (x+x2/1.5);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)/1.5);
	Points[CurrentPoint].x = (int) (x+x2/2.1);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)/1.4);

	pDC->Polygon( Points, CurrentPoint );

	CurrentPoint = 0;
	Points[CurrentPoint].x = (int) (x+x2);
	Points[CurrentPoint++].y = y;
	Points[CurrentPoint].x = (int) (x+x2+x2/2);
	Points[CurrentPoint++].y = (int) (y+y2/2);
	Points[CurrentPoint].x = (int) (x+x2+x2/2.5);
	Points[CurrentPoint++].y = (int) (y+y2/1);
	Points[CurrentPoint].x = (int) (x+x2/1.1);
	Points[CurrentPoint++].y = (int) (y+y2/1.4);

	pDC->Polygon( Points, CurrentPoint );

	CurrentPoint = 0;
	Points[CurrentPoint].x = (int) (x+x2);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)-y2/1);
	Points[CurrentPoint].x = (int) (x+x2+x2/2);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)-y2/1.1);
	Points[CurrentPoint].x = (int) (x+x2+x2/2.5);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)-y2/4.2);
	Points[CurrentPoint].x = (int) (x+x2/1.1);
	Points[CurrentPoint++].y = (int) (y+(y3-y2)-y2/5);

	pDC->Polygon( Points, CurrentPoint );

	pDC->SelectObject( poldBrush );
	pDC->SelectObject( pOldPen );
}
