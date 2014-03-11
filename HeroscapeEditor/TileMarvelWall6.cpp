// TileMarvelWall6.cpp : implementation file
//

#include "StdAfx.h"

#include "Game3DView.h"
#include "TileMarvelWall6.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileMarvelWall6::CTileMarvelWall6()
{
	m_NbTile = 6;
	m_TileHeight = TILE3D_ZHEIGHT;
	m_Type = TYPE_RUIN*1000+m_NbTile;
	m_TileColor = RGB(220,220,220);

	Init();
}

// The destructor
//
CTileMarvelWall6::~CTileMarvelWall6()
{
}

// Get a copy of this tile
//
CTile* CTileMarvelWall6::GetCopy()
{
	return new CTileMarvelWall6;
}

// When the rotation change
//
void CTileMarvelWall6::OnRotationChange()
{
	int CurrentPos = 0;
	switch( m_CurrentRotation )
	{
	case 0:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
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
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
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
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
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
		m_TilePosition[CurrentPos].x = 2;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 3;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 4;
		break;
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = -3;
		m_TilePosition[CurrentPos++].y = 3;
		m_TilePosition[CurrentPos].x = -2;
		m_TilePosition[CurrentPos++].y = 3;
		break;
	}
}

// Draw more on a tile
//
void CTileMarvelWall6::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{

	double LowColor = GetLowColor( DrawingLevel );

	CPen Pen;
	Pen.CreatePen(PS_SOLID,(int) (x3/10.0),RGB(127+128*LowColor,127+128*LowColor,127+128*LowColor));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	int LineX1,LineY1,LineX2,LineY2,LineX3,LineY3;
	switch( m_CurrentRotation )
	{
	case 0:
	default:
		LineX1 = x+x3;
		LineY1 = (int) (y);
		LineX2 = LineX1;
		LineY2 = (int) (y+y3-y2+y4/2.0);
		LineX3 = (int) (x+x3*4.5);
		LineY3 = LineY2;
		break;
	case 1:
		LineX1 = x+x3;
		LineY1 = (int) (y+y3-y2);
		LineX2 = x;
		LineY2 = (int) (y+y3-y2+y4/2.0);
		LineX3 = (int) (x+x3+x2+x2/2.0);
		LineY3 = y+y3*4+y3-y2+y2/2;
		break;
	case 2:
		LineX1 = x+x3+x2;
		LineY1 = (int) (y+y3);
		LineX2 = x+x2;
		LineY2 = (int) (y+(y3-y2)/2.0);
		LineX3 = (int) (x-x3-x2/2.0);
		LineY3 = y+y3*3+y3-y2+y2/2;
		break;
	case 3:
		LineX1 = x+x3*3+x2;
		LineY1 = (int) (y+y3+y3-y2);
		LineX2 = LineX1;
		LineY2 = (int) (y+(y3-y2)/2.0);
		LineX3 = x;
		LineY3 = LineY2;
		break;
	case 4:
		LineX1 = x+x3;
		LineY1 = (int) (y+y3*4);
		LineX2 = x+x3*2;
		LineY2 = (int) (y+y3*3+(y3-y2)/2.0);
		LineX3 = (int) (x+x2/2.0);
		LineY3 = (int) (y-y2/2.0);
		break;
	case 5:
		LineX1 = (int) (x-x3*2);
		LineY1 = (int) (y+y3*2+y3-y2);
		LineX2 = x-x3;
		LineY2 = (int) (y+y3*3+(y3-y2)/2.0);
		LineX3 = (int) (x+x3-x2/2.0);
		LineY3 = (int) (y-y2/2.0);
		break;
	}

	pDC->MoveTo(LineX1,LineY1);
	pDC->LineTo(LineX2,LineY2);
	pDC->LineTo(LineX3,LineY3);

	pDC->SelectObject( pOldPen );
}

// Render a tile (3D view)
//
void CTileMarvelWall6::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

	// Call the base class
	CTile::Render1( pView, ForShadow, BindTexture );

	glPushMatrix();
	if( m_PosY%2==1 )
	{
		if( m_TilePosition[0].y%2==0 )
			glTranslated( (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH*TileExplode+TILE3D_X3, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, (m_PosZ+1)*TILE3D_ZHEIGHT*TileExplode );
		else
			glTranslated( (m_PosX+m_TilePosition[0].x+1)*TILE3D_WIDTH*TileExplode, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, (m_PosZ+1)*TILE3D_ZHEIGHT*TileExplode );
	}
	else
	{
		if( m_TilePosition[0].y%2==1 )
			glTranslated( (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH*TileExplode+TILE3D_X3, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, (m_PosZ+1)*TILE3D_ZHEIGHT*TileExplode );
		else
			glTranslated( (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH*TileExplode, -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT*TileExplode, (m_PosZ+1)*TILE3D_ZHEIGHT*TileExplode );
	}

	switch( m_CurrentRotation )
	{
	case 0:
		glTranslated( TILE3D_WIDTH, 0, 0 );
		break;
	case 1:
		glRotated( -60, 0, 0, 1 );
		glTranslated( TILE3D_WIDTH, 0, 0 );
		break;
	case 2:
		glRotated( -120, 0, 0, 1 );
		glTranslated( TILE3D_WIDTH*0.5, TILE3D_HEIGHT, 0 );
		break;
	case 3:
		glRotated( -180, 0, 0, 1 );
		glTranslated( -TILE3D_WIDTH*2.5, TILE3D_HEIGHT, 0 );
		break;
	case 4:
		glRotated( -240, 0, 0, 1 );
		glTranslated( -TILE3D_WIDTH*2.5, TILE3D_HEIGHT, 0 );
		break;
	case 5:
		glRotated( -300, 0, 0, 1 );
		glTranslated( -TILE3D_WIDTH*2.5, TILE3D_HEIGHT, 0 );
		break;
	}

	((CHeroscapeEditor3DView*) pView)->m_pMarvelRuin6->Render( BindTexture );

	glPopMatrix();
}

