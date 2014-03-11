// TilePalm1.cpp : implementation file
//

#include "StdAfx.h"

#include "TilePalm14.h"
#include "HeroscapeEditor3DView.h"
#include "Game3DView.h"

// The constructor
//
CTilePalm14::CTilePalm14()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT;
	m_Type = TYPE_TICALLA*1000+14;
	m_TileColor = RGB(120,255,120);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTilePalm14::~CTilePalm14()
{
}

// Get a copy of this tile
//
CTile* CTilePalm14::GetCopy()
{
	return new CTilePalm14;
}

// Draw more on a tile
//
void CTilePalm14::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (x3/2), (int) (x3/3), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(255,255,255) );
	pDC->SetBkMode( TRANSPARENT );

	int CenterX = x+x2;
	int CenterY = y+(y3-y2)/2;

	pDC->DrawText( _T("14"), CRect(CenterX-x3,CenterY-x3,CenterX+x3,CenterY+x3), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );

	double LowColor = GetLowColor( DrawingLevel );

	double cosa;
	double sina;
	switch( m_CurrentRotation )
	{
	case 3:
		cosa = 1;
		sina = 0;
		break;
	case 4:
		cosa = cos(60/180.0*PI);
		sina = sin(60/180.0*PI);
		break;
	case 5:
		cosa = cos(120/180.0*PI);
		sina = sin(120/180.0*PI);
		break;
	case 0:
		cosa = cos(180/180.0*PI);
		sina = sin(180/180.0*PI);
		break;
	case 1:
		cosa = cos(240/180.0*PI);
		sina = sin(240/180.0*PI);
		break;
	case 2:
		cosa = cos(300/180.0*PI);
		sina = sin(300/180.0*PI);
		break;
	}

	CPen Pen1;
	Pen1.CreatePen(PS_SOLID,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen1 );

	pDC->MoveTo( x+x2, y+(y3-y2)/2 );
	int xDest = (int) (x+x2+cosa*x2*(-1)-sina*0);
	int yDest = (int) (y+(y3-y2)/2.0+sina*x2*(-1)+cosa*0);
	pDC->LineTo( xDest, yDest );

	pDC->SelectObject( pOldPen );
}

// Render a tile 1 hexagon
//
void CTilePalm14::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

	// Call the base class
	CTile::Render1( pView, ForShadow, BindTexture );

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

	glDisable( GL_CULL_FACE );
	((CHeroscapeEditor3DView*) pView)->m_pPalm1->Render( BindTexture );
	glEnable( GL_CULL_FACE );

	glPopMatrix();
}

