// TileWall4.cpp : implementation file
//

#include "StdAfx.h"

#include <Math.h>

#include "Game3DView.h"
#include "HeroscapeEditor3DView.h"
#include "TileWall4.h"

// The constructor
//
CTileWall4::CTileWall4()
{
	m_NbTile = 4;
	m_Type = TYPE_WALL*1000+m_NbTile;
	m_TileColor = RGB(120,120,120);

	Init();
}

// The destructor
//
CTileWall4::~CTileWall4()
{
}

// Get a copy of this tile
//
CTile* CTileWall4::GetCopy()
{
	return new CTileWall4;
}

// When the rotation change
//
void CTileWall4::OnRotationChange()
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
		break;
	}
}

// Draw the tiles
//
void CTileWall4::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	POINT	Points[11];
	int		NbPoint = 11;
	int		TilePos = 0;

	double LowColor = GetLowColor( DrawingLevel );

	switch( m_CurrentRotation )
	{
	case 0:
		Points[0].x=x;
		Points[0].y=y+(y3-y2)/2;
		Points[1].x=x;
		Points[1].y=y+y3-y2;
		Points[2].x=x+x2;
		Points[2].y=y+y3;
		Points[3].x=x+x3;
		Points[3].y=y+y3-y2;
		Points[4].x=x+x3+x2;
		Points[4].y=y+y3;
		Points[5].x=x+x3+x3;
		Points[5].y=y+y3-y2;
		Points[6].x=x+x3+x3+x2;
		Points[6].y=y+y3;
		Points[7].x=x+x3+x3+x3;
		Points[7].y=y+y3-y2;
		Points[8].x=x+x3+x3+x3+x2;
		Points[8].y=y+y3;
		Points[9].x=x+x3+x3+x3+x3;
		Points[9].y=y+y3-y2;
		Points[10].x=x+x3+x3+x3+x3;
		Points[10].y=y+(y3-y2)/2;
		break;
	case 1:
		Points[0].x=x+x2/2;
		Points[0].y=y-y2/2;
		Points[1].x=x;
		Points[1].y=y;
		Points[2].x=x;
		Points[2].y=y+y3-y2;
		Points[3].x=x+x2;
		Points[3].y=y+y3;
		Points[4].x=x+x2;
		Points[4].y=y+y3+y3-y2;
		Points[5].x=x+x3;
		Points[5].y=y+y3+y3;
		Points[6].x=x+x3;
		Points[6].y=y+y3+y3+y3-y2;
		Points[7].x=x+x3+x2;
		Points[7].y=y+y3+y3+y3;
		Points[8].x=x+x3+x2;
		Points[8].y=y+y3+y3+y3+y3-y2;
		Points[9].x=x+x3+x3;
		Points[9].y=y+y3+y3+y3+y3;
		Points[10].x=x+x3+x3+x2/2;
		Points[10].y=y+y3+y3+y3+y3-y2/2;
		break;
	case 2:
		Points[0].x=x+x2+x2/2;
		Points[0].y=y-y2/2;
		Points[1].x=x+x2;
		Points[1].y=y-y2;
		Points[2].x=x;
		Points[2].y=y;
		Points[3].x=x;
		Points[3].y=y+y3-y2;
		Points[4].x=x-x2;
		Points[4].y=y+y3;
		Points[5].x=x-x2;
		Points[5].y=y+y3+y3-y2;
		Points[6].x=x-x3;
		Points[6].y=y+y3+y3;
		Points[7].x=x-x3;
		Points[7].y=y+y3+y3+y3-y2;
		Points[8].x=x-x3-x2;
		Points[8].y=y+y3+y3+y3;
		Points[9].x=x-x3-x2;
		Points[9].y=y+y3+y3+y3+y3-y2;
		Points[10].x=x-x3-x2/2;
		Points[10].y=y+y3+y3+y3+y3-y2/2;
		break;
	case 3:
		Points[0].x=x;
		Points[0].y=y+(y3-y2)/2;
		Points[1].x=x;
		Points[1].y=y;
		Points[2].x=x+x2;
		Points[2].y=y-y2;
		Points[3].x=x+x3;
		Points[3].y=y;
		Points[4].x=x+x3+x2;
		Points[4].y=y-y2;
		Points[5].x=x+x3+x3;
		Points[5].y=y;
		Points[6].x=x+x3+x3+x2;
		Points[6].y=y-y2;
		Points[7].x=x+x3+x3+x3;
		Points[7].y=y;
		Points[8].x=x+x3+x3+x3+x2;
		Points[8].y=y-y2;
		Points[9].x=x+x3+x3+x3+x3;
		Points[9].y=y;
		Points[10].x=x+x3+x3+x3+x3;
		Points[10].y=y+(y3-y2)/2;
		break;
	case 4:
		Points[0].x=x+x2/2;
		Points[0].y=y-y2/2;
		Points[1].x=x+x2;
		Points[1].y=y-y2;
		Points[2].x=x+x3;
		Points[2].y=y;
		Points[3].x=x+x3;
		Points[3].y=y+y3-y2;
		Points[4].x=x+x3+x2;
		Points[4].y=y+y3;
		Points[5].x=x+x3+x2;
		Points[5].y=y+y3+y3-y2;
		Points[6].x=x+x3+x3;
		Points[6].y=y+y3+y3;
		Points[7].x=x+x3+x3;
		Points[7].y=y+y3+y3+y3-y2;
		Points[8].x=x+x3+x3+x2;
		Points[8].y=y+y3+y3+y3;
		Points[9].x=x+x3+x3+x2;
		Points[9].y=y+y3+y3+y3+y3-y2;
		Points[10].x=x+x3+x3+x2/2;
		Points[10].y=y+y3+y3+y3+y3-y2/2;
		break;
	case 5:
		Points[0].x=x+x2+x2/2;
		Points[0].y=y-y2/2;
		Points[1].x=x+x3;
		Points[1].y=y;
		Points[2].x=x+x3;
		Points[2].y=y+y3-y2;
		Points[3].x=x+x2;
		Points[3].y=y+y3;
		Points[4].x=x+x2;
		Points[4].y=y+y3+y3-y2;
		Points[5].x=x;
		Points[5].y=y+y3+y3;
		Points[6].x=x;
		Points[6].y=y+y3+y3+y3-y2;
		Points[7].x=x-x2;
		Points[7].y=y+y3+y3+y3;
		Points[8].x=x-x2;
		Points[8].y=y+y3+y3+y3+y3-y2;
		Points[9].x=x-x3;
		Points[9].y=y+y3+y3+y3+y3;
		Points[10].x=x-x3-x2/2;
		Points[10].y=y+y3+y3+y3+y3-y2/2;
		break;
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

	pDC->Polygon( Points, NbPoint );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

}

// Render a tile (3D view)
//
void CTileWall4::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

	glMatrixMode(GL_MODELVIEW);
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
		glTranslated( 0, 0, 0 );
		glRotated( -120, 0, 0, 1 );
		break;
	case 3:
		glTranslated( TILE3D_WIDTH*3, 0, 0 );
		glRotated( -180, 0, 0, 1 );
		break;
	case 4:
		glTranslated( TILE3D_WIDTH*1.5, -TILE3D_HEIGHT*3, 0 );
		glRotated( -240, 0, 0, 1 );
		break;
	case 5:
		glTranslated( -TILE3D_WIDTH*1.5, -TILE3D_HEIGHT*3, 0 );
		glRotated( -300, 0, 0, 1 );
		break;
	}

	((CHeroscapeEditor3DView*) pView)->m_pWall4->Render( BindTexture );

	glPopMatrix();
}

// Verify that something is under the tile
//
void CTileWall4::VerifySomethingUnderTile( void* pTheDoc )
{
}
