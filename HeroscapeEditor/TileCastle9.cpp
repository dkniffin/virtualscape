// TileCastle9.cpp : implementation file
//

#include "StdAfx.h"

#include "TileCastle9.h"

// The constructor
//
CTileCastle9::CTileCastle9()
{
	m_NbTile = 9;
	m_Type = TYPE_CASTLE*1000+m_NbTile;
	m_TileColor = RGB(190,190,190);

	Init();
}

// The destructor
//
CTileCastle9::~CTileCastle9()
{
}

// Get a copy of this tile
//
CTile* CTileCastle9::GetCopy()
{
	return new CTileCastle9;
}

// When the rotation change
//
void CTileCastle9::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
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
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 1:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	case 2:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	case 3:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	}
}

// Draw more on a tile
//
void CTileCastle9::DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	POINT Points[10];

	double LowColor = GetLowColor( DrawingLevel );

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,220+(255-220)*LowColor),min(255,220+(255-220)*LowColor),min(255,220+(255-220)*LowColor)) );
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

// Verify that something is under the tile
//
void CTileCastle9::VerifySomethingUnderTile( void* pTheDoc )
{
}
