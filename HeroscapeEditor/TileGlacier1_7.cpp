// TileGlacier1_7.cpp : implementation file
//

#include "StdAfx.h"

#include "Game3DView.h"
#include "HeroscapeEditor3DView.h"
#include "TileGlacier1_7.h"

// The constructor
//
CTileGlacier1_7::CTileGlacier1_7()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_GLACIER*1000+m_NbTile;
	m_TileColor = RGB(180,180,255);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileGlacier1_7::~CTileGlacier1_7()
{
}

// Get a copy of this tile
//
CTile* CTileGlacier1_7::GetCopy()
{
	return new CTileGlacier1_7;
}

// Draw more on a tile
//
void CTileGlacier1_7::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (x3/2), (int) (x3/3), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(0,0,0) );
	pDC->SetBkMode( TRANSPARENT );

	int CenterX = x+x2;
	int CenterY = y+(y3-y2)/2;

	pDC->DrawText( _T("7"), CRect(CenterX-x3,CenterY-x3,CenterX+x3+1,CenterY+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );
}

// Render a tile 1 hexagon
//
void CTileGlacier1_7::Render1( void* pView, bool ForShadow, bool BindTexture )
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

	((CHeroscapeEditor3DView*) pView)->m_pGlacier1->Render( BindTexture );

	glPopMatrix();
}
