// TileCastleBattlement.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "TileCastleBattlement.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileCastleBattlement::CTileCastleBattlement()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT;
	m_Type = TYPE_CASTLE*1000+301;
	m_TileColor = RGB(80,80,80);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileCastleBattlement::~CTileCastleBattlement()
{
}

// Get a copy of this tile
//
CTile* CTileCastleBattlement::GetCopy()
{
	return new CTileCastleBattlement;
}

// Draw the tiles
//
void CTileCastleBattlement::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	POINT	Points1[4];
	int		NbPoint1 = 4;
	int		TilePos = 0;

	double LowColor = GetLowColor( DrawingLevel );

	Points1[0].x=x+x2;
	Points1[0].y=y-y2;
	Points1[1].x=x+x3;
	Points1[1].y=y;
	Points1[2].x=(int) (x+x3-x2/4.0);
	Points1[2].y=(int) (y+y2/4.0);
	Points1[3].x=x+x2;
	Points1[3].y=(int) (y-y2/2.0);

	double cosa;
	double sina;
	switch( m_CurrentRotation )
	{
	case 0:
		break;
	case 1:
		cosa = cos(60/180.0*PI);
		sina = sin(60/180.0*PI);
		break;
	case 2:
		cosa = cos(120/180.0*PI);
		sina = sin(120/180.0*PI);
		break;
	case 3:
		cosa = cos(180/180.0*PI);
		sina = sin(180/180.0*PI);
		break;
	case 4:
		cosa = cos(240/180.0*PI);
		sina = sin(240/180.0*PI);
		break;
	case 5:
		cosa = cos(300/180.0*PI);
		sina = sin(300/180.0*PI);
		break;
	}

	if( m_CurrentRotation!=0 )
	{
		for( int i=0; i<NbPoint1; i++ )
		{
			int x1,y1;

			x1 = (int) (cosa*(Points1[i].x-x-x2)-sina*(Points1[i].y-y-(y3-y2)/2));
			y1 = (int) (sina*(Points1[i].x-x-x2)+cosa*(Points1[i].y-y-(y3-y2)/2));
			Points1[i].x = x+x2+x1;
			Points1[i].y = y+(y3-y2)/2+y1;
		}
	}

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	if( m_IsSelected )
		Brush.CreateSolidBrush( RGB(255,255*LowColor,255*LowColor) );
	else
		Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor)+(255-GetRValue(m_TileColor))*LowColor),min(255,GetGValue(m_TileColor)+(255-GetGValue(m_TileColor))*LowColor),min(255,GetBValue(m_TileColor)+(255-GetBValue(m_TileColor))*LowColor)) );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	pDC->Polygon( Points1, NbPoint1 );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

	DrawExtend( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
}

// Render a tile 1 hexagon
//
void CTileCastleBattlement::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

	// Call the base class
	//CTile::Render1( pView, ForShadow, BindTexture );

	glPushMatrix();
	if( m_PosY%2==1 )
	{
		if( m_TilePosition[0].y%2==0 )
			glTranslated( (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH*TileExplode+TILE3D_X3, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode );
		else
			glTranslated( (m_PosX+m_TilePosition[0].x+1)*TILE3D_WIDTH*TileExplode, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode );
	}
	else
	{
		if( m_TilePosition[0].y%2==1 )
			glTranslated( (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH*TileExplode+TILE3D_X3, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode );
		else
			glTranslated( (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH*TileExplode, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode );
	}

	glRotated( -m_CurrentRotation*60, 0, 0, 1 );
	((CHeroscapeEditor3DView*) pView)->m_pCastleBattlement->Render( BindTexture );

	glPopMatrix();
}

// Verify that something is under the tile
//
void CTileCastleBattlement::VerifySomethingUnderTile( void* pTheDoc )
{
}
