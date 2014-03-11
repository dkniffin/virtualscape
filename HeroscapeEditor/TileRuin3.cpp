// TileRuin3.cpp : implementation file
//

#include "StdAfx.h"

#include <Math.h>

#include "Game3DView.h"
#include "TileRuin3.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileRuin3::CTileRuin3()
{
	m_NbTile = 3;
	m_Type = TYPE_RUIN*1000+m_NbTile;
	m_TileColor = RGB(160,0,0);

	Init();
}

// The destructor
//
CTileRuin3::~CTileRuin3()
{
}

// Get a copy of this tile
//
CTile* CTileRuin3::GetCopy()
{
	return new CTileRuin3;
}

// When the rotation change
//
void CTileRuin3::OnRotationChange()
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
		break;
	case 1:
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		break;
	case 2:
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		break;
	}
}

// Draw the tiles
//
void CTileRuin3::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	POINT	Points[16];
	int		NbPoint = 8;
	int		TilePos = 0;

	double LowColor = GetLowColor( DrawingLevel );

	switch( m_CurrentRotation )
	{
	case 0:
		Points[0].x=x+x3+x3+x3;
		Points[0].y=y+y3-y2;
		Points[1].x=x+x3+x3+x2;
		Points[1].y=y+y3;
		Points[2].x=x+x3+x3;
		Points[2].y=y+y3-y2;
		Points[3].x=x+x3+x2;
		Points[3].y=y+y3;
		Points[4].x=x+x3;
		Points[4].y=y+y3-y2;
		Points[5].x=x+x2;
		Points[5].y=y+y3;
		Points[6].x=x;
		Points[6].y=y+y3-y2;
		Points[7].x=x;
		Points[7].y=y;
		break;
	case 1:
		Points[0].x=x+x3+x2;
		Points[0].y=y+y3+y3+y3;
		Points[1].x=x+x3;
		Points[1].y=y+y3+y3+y3-y2;
		Points[2].x=x+x3;
		Points[2].y=y+y3+y3;
		Points[3].x=x+x2;
		Points[3].y=y+y3+y3-y2;
		Points[4].x=x+x2;
		Points[4].y=y+y3;
		Points[5].x=x;
		Points[5].y=y+y3-y2;
		Points[6].x=x;
		Points[6].y=y;
		Points[7].x=x+x2;
		Points[7].y=y-y2;
		break;
	case 2:
		Points[0].x=x-x3;
		Points[0].y=y+y3+y3+y3-y2;
		Points[1].x=x-x3;
		Points[1].y=y+y3+y3;
		Points[2].x=x-x2;
		Points[2].y=y+y3+y3-y2;
		Points[3].x=x-x2;
		Points[3].y=y+y3;
		Points[4].x=x;
		Points[4].y=y+y3-y2;
		Points[5].x=x;
		Points[5].y=y;
		Points[6].x=x+x2;
		Points[6].y=y-y2;
		Points[7].x=x+x3;
		Points[7].y=y;
		break;
	case 3:
		Points[0].x=x-x3-x3+x3+x3;
		Points[0].y=y;
		Points[1].x=x-x3-x2+x3+x3;
		Points[1].y=y-y2;
		Points[2].x=x-x3+x3+x3;
		Points[2].y=y;
		Points[3].x=x-x2+x3+x3;
		Points[3].y=y-y2;
		Points[4].x=x+x3+x3;
		Points[4].y=y;
		Points[5].x=x+x2+x3+x3;
		Points[5].y=y-y2;
		Points[6].x=x+x3+x3+x3;
		Points[6].y=y;
		Points[7].x=x+x3+x3+x3;
		Points[7].y=y+y3-y2;
		break;
	case 4:
		Points[0].x=x-x2+x3;
		Points[0].y=y-y4-y3+y3+y3;
		Points[1].x=x+x3;
		Points[1].y=y-y4-y3+y2+y3+y3;
		Points[2].x=x+x3;
		Points[2].y=y-y4+y3+y3;
		Points[3].x=x+x2+x3;
		Points[3].y=y-y3+y3+y3;
		Points[4].x=x+x2+x3;
		Points[4].y=y-y2+y3+y3;
		Points[5].x=x+x3+x3;
		Points[5].y=y+y3+y3;
		Points[6].x=x+x3+x3;
		Points[6].y=y+y3-y2+y3+y3;
		Points[7].x=x+x2+x3;
		Points[7].y=y+y3+y3+y3;
		break;
	case 5:
		Points[0].x=x+x3+x3-x3;
		Points[0].y=y-y3-y3+y3+y3;
		Points[1].x=x+x3+x3-x3;
		Points[1].y=y-y4+y3+y3;
		Points[2].x=x+x3+x2-x3;
		Points[2].y=y-y3+y3+y3;
		Points[3].x=x+x3+x2-x3;
		Points[3].y=y-y2+y3+y3;
		Points[4].x=x+x3-x3;
		Points[4].y=y+y3+y3;
		Points[5].x=x+x3-x3;
		Points[5].y=y+y3-y2+y3+y3;
		Points[6].x=x+x2-x3;
		Points[6].y=y+y3+y3+y3;
		Points[7].x=x-x3;
		Points[7].y=y+y3-y2+y3+y3;
		break;
	}

	// Now, move each point toward inside
	POINT	Points2[8];

	POINT Vector;
	Vector.x = ((Points[2].y-Points[1].y)+(Points[1].y-Points[0].y));
	Vector.y = ((Points[2].x-Points[1].x)+(Points[1].x-Points[0].x));

	double Coef=5;
	if( sqrt((double) ((Vector.x*Vector.x)+(Vector.y*Vector.y)))<10 )
		Coef=sqrt((double) ((Vector.x*Vector.x)+(Vector.y*Vector.y)))/2;

	for( int i=0; i<NbPoint; i++ )
	{
		if( i==0 )
		{
			Points2[i].x = (LONG) (Points[i].x-(int) (((Points[i+1].y-Points[i].y)/Coef*1.5)+0.5));
			Points2[i].y = (LONG) (Points[i].y+(int) (((Points[i+1].x-Points[i].x)/Coef*1.5)+0.5));
		}
		else if( i==NbPoint-1 )
		{
			Points2[i].x = (LONG) (Points[i].x-(Points[i].y-Points[i-1].y)/Coef*1.5);
			Points2[i].y = (LONG) (Points[i].y+(Points[i].x-Points[i-1].x)/Coef*1.5);
		}
		else
		{
			Points2[i].x = (LONG) (Points[i].x-(int) (((Points[i].y-Points[i-1].y)+(Points[i+1].y-Points[i].y))/Coef)+0.5);
			Points2[i].y = (LONG) (Points[i].y+(int) (((Points[i].x-Points[i-1].x)+(Points[i+1].x-Points[i].x))/Coef)+0.5);
		}
	}

	for( int i=0; i<NbPoint; i++ )
		Points[i+NbPoint] = Points2[NbPoint-i-1];

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	if( m_IsSelected )
		Brush.CreateSolidBrush( RGB(255,255*LowColor,255*LowColor) );
	else
		Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor)+(255-GetRValue(m_TileColor))*LowColor),min(255,GetGValue(m_TileColor)+(255-GetGValue(m_TileColor))*LowColor),min(255,GetBValue(m_TileColor)+(255-GetBValue(m_TileColor))*LowColor)) );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	pDC->Polygon( Points, NbPoint*2 );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

}

// Render a tile 1 hexagon
//
void CTileRuin3::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

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

	switch( m_CurrentRotation )
	{
	case 0:
		break;
	case 1:
		glRotated( -60, 0, 0, 1 );
		break;
	case 2:
		glRotated( -120, 0, 0, 1 );
		break;
	case 3:
		glTranslated( TILE3D_WIDTH*2, 0, 0 );
		glRotated( -180, 0, 0, 1 );
		break;
	case 4:
		glTranslated( TILE3D_WIDTH, -TILE3D_HEIGHT*2, 0 );
		glRotated( -240, 0, 0, 1 );
		break;
	case 5:
		glTranslated( TILE3D_X1*2, -TILE3D_HEIGHT*2, 0 );
		glRotated( -300, 0, 0, 1 );
		break;
	}

	((CHeroscapeEditor3DView*) pView)->m_pRuin3->Render( BindTexture );

	glPopMatrix();
}

