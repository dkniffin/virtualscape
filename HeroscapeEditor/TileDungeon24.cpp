// TileDungeon24.cpp : implementation file
//

#include "StdAfx.h"

#include "TileDungeon24.h"

// The constructor
//
CTileDungeon24::CTileDungeon24()
{
	m_NbTile = 24;
	m_Type = TYPE_DUNGEON*1000+m_NbTile;
	m_TileColor = RGB(220,220,220);

	Init();
}

// The destructor
//
CTileDungeon24::~CTileDungeon24()
{
}

// Get a copy of this tile
//
CTile* CTileDungeon24::GetCopy()
{
	return new CTileDungeon24;
}

// When the rotation change
//
void CTileDungeon24::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
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
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	case 1:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 7;
		break;
	case 2:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
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
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 5;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 5;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 5;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 4;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	case 4:
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
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 5;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 6;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 7;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 7;
		break;
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -4;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -4;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -4;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 4;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 5;
		break;
	}
}

// Draw more on a tile
//
void CTileDungeon24::DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
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
