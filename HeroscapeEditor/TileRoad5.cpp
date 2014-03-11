// TileRoad5.cpp : implementation file
//

#include "StdAfx.h"

#include "TileRoad5.h"

// The constructor
//
CTileRoad5::CTileRoad5()
{
	m_NbTile = 5;
	m_Type = TYPE_ROAD*1000+m_NbTile;
	m_TileColor = RGB(160,160,160);

	Init();
}

// The destructor
//
CTileRoad5::~CTileRoad5()
{
}

// Get a copy of this tile
//
CTile* CTileRoad5::GetCopy()
{
	return new CTileRoad5;
}

// When the rotation change
//
void CTileRoad5::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
	case 3:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 0;
		break;
	case 1:
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	case 2:
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	}
}

// Draw more on a tile
//
void CTileRoad5::DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	POINT Points[10];

	double LowColor = GetLowColor( DrawingLevel );

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,120+(255-120)*LowColor),min(255,120+(255-120)*LowColor),min(255,120+(255-120)*LowColor)) );
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
