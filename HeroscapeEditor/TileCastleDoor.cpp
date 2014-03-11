// TileCastleDoor.cpp : implementation file
//

#include "StdAfx.h"

#include <math.h>

#include "HeroscapeEditor.h"
#include "TileCastleDoor.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileCastleDoor::CTileCastleDoor()
{
	m_NbTile = 3;
	m_Type = TYPE_CASTLE*1000+401;
	m_TileColor = RGB(220,220,220);
	m_TileColor2 = RGB(50,50,50);
	m_Height = 10;

	Init();
}

// The destructor
//
CTileCastleDoor::~CTileCastleDoor()
{
}

// Get a copy of this tile
//
CTile* CTileCastleDoor::GetCopy()
{
	return new CTileCastleDoor;
}

// When the rotation change
//
void CTileCastleDoor::OnRotationChange()
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
void CTileCastleDoor::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	POINT	Points1[12];
	POINT	Points2[6];
	int		NbPoint1 = 12;
	int		NbPoint2 = 6;
	int		TilePos = 0;

	double LowColor = GetLowColor( DrawingLevel );

	Points1[0].x=x;
	Points1[0].y=y+y3-y2;
	Points1[1].x=x;
	Points1[1].y=y;
	Points1[2].x=x+x2;
	Points1[2].y=y-y2;
	Points1[3].x=(int) (x+x2+x2/2.0);
	Points1[3].y=(int) (y-y2/2.0);
	Points1[4].x=(int) (x+x3+x3+x2/2.0);
	Points1[4].y=(int) (y-y2/2.0);
	Points1[5].x=x+x3+x3+x2;
	Points1[5].y=y-y2;
	Points1[6].x=x+x3+x3+x3;
	Points1[6].y=y;
	Points1[7].x=x+x3+x3+x3;
	Points1[7].y=y+y3-y2;
	Points1[8].x=(int) (x+x3+x3+x3-x2/3.0);
	Points1[8].y=(int) (y+y3-y2-x2/3.0);
	Points1[9].x=(int) (x+x3+x3+x3-x2/2.0);
	Points1[9].y=y;
	Points1[10].x=(int) (x+x2/2.0);
	Points1[10].y=y;
	Points1[11].x=(int) (x+x2/3.0);
	Points1[11].y=(int) (y+y3-y2-x2/3.0);

	Points2[0].x=x+x2;
	Points2[0].y=y+y3;
	Points2[1].x=(int) (x+x2+x2/2.0);
	Points2[1].y=(int) (y+y3-y2/2.0);
	Points2[2].x=(int) (x+x3+x3+x2/2.0);
	Points2[2].y=(int) (y+y3-y2/2.0);
	Points2[3].x=x+x3+x3+x2;
	Points2[3].y=y+y3;
	Points2[4].x=(int) (x+x3+x3+x2/2.0);
	Points2[4].y=y+y3-y2;
	Points2[5].x=(int) (x+x2+x2/2.0);
	Points2[5].y=y+y3-y2;

	double cosa;
	double sina;
	int OffsetX=0;
	int OffsetY=0;
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
		OffsetX=x3+x3;
		OffsetY=0;
		break;
	case 4:
		cosa = cos(240/180.0*PI);
		sina = sin(240/180.0*PI);
		OffsetX=x3;
		OffsetY=y3+y3;
		break;
	case 5:
		cosa = cos(300/180.0*PI);
		sina = sin(300/180.0*PI);
		OffsetX=-x3;
		OffsetY=y3+y3;
		break;
	}

	if( m_CurrentRotation!=0 )
	{
		for( int i=0; i<NbPoint1; i++ )
		{
			int x1,y1;

			x1 = (int) (cosa*(Points1[i].x-x-x2)-sina*(Points1[i].y-y-(y3-y2)/2));
			y1 = (int) (sina*(Points1[i].x-x-x2)+cosa*(Points1[i].y-y-(y3-y2)/2));
			Points1[i].x = x+x2+x1+OffsetX;
			Points1[i].y = y+(y3-y2)/2+y1+OffsetY;
		}
		for( int i=0; i<NbPoint2; i++ )
		{
			int x1,y1;

			x1 = (int) (cosa*(Points2[i].x-x-x2)-sina*(Points2[i].y-y-(y3-y2)/2));
			y1 = (int) (sina*(Points2[i].x-x-x2)+cosa*(Points2[i].y-y-(y3-y2)/2));
			Points2[i].x = x+x2+x1+OffsetX;
			Points2[i].y = y+(y3-y2)/2+y1+OffsetY;
		}
	}

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	if( m_IsSelected )
		Brush.CreateSolidBrush( RGB(255,255*LowColor,255*LowColor) );
	else
		Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor2)+(255-GetRValue(m_TileColor2))*LowColor),min(255,GetGValue(m_TileColor2)+(255-GetGValue(m_TileColor2))*LowColor),min(255,GetBValue(m_TileColor2)+(255-GetBValue(m_TileColor2))*LowColor)) );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	pDC->Polygon( Points1, NbPoint1 );
	pDC->Polygon( Points2, NbPoint2 );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

	DrawExtend( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
}

// Render a tile
//
void CTileCastleDoor::Render1( void* pView, bool ForShadow, bool BindTexture )
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

	switch( m_CurrentRotation )
	{
	case 0:
	case 1:
	case 2:
		break;
	case 3:
		glTranslated( TILE3D_WIDTH*2, 0, 0 );
		break;
	case 4:
		glTranslated( TILE3D_WIDTH, -TILE3D_HEIGHT*2, 0 );
		break;
	case 5:
		glTranslated( -TILE3D_WIDTH, -TILE3D_HEIGHT*2, 0 );
		break;
	}

	glRotated( -m_CurrentRotation*60, 0, 0, 1 );

	((CHeroscapeEditor3DView*) pView)->m_pCastleDoor->Render( BindTexture );

	glPopMatrix();
}

// Fill the members with members of an other tile
//
void CTileCastleDoor::FillCopy( CTile* pTile )
{
	CTile::FillCopy( pTile );
	m_TileColor2 = ((CTileCastleDoor*) pTile)->m_TileColor2;
}
