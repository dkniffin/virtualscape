// TileTree4.cpp : implementation file
//

#include "StdAfx.h"

#include "Game3DView.h"
#include "TileTree4.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileTree4::CTileTree4()
{
	m_NbTile = 4;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_TREE*1000+m_NbTile;
	m_TileColor = RGB(85,0,0);

	Init();
}

// The destructor
//
CTileTree4::~CTileTree4()
{
}

// Get a copy of this tile
//
CTile* CTileTree4::GetCopy()
{
	return new CTileTree4;
}

// When the rotation change
//
void CTileTree4::OnRotationChange()
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
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 1:
	case 4:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		break;
	case 2:
	case 5:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	}
}

// Draw more on a tile
//
void CTileTree4::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	double LowColor = GetLowColor( DrawingLevel );

	CFont Font;
	Font.CreateFont( (int) (x3/1.5), (int) (x3/2.8), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(255,255,255) );
	pDC->SetBkMode( TRANSPARENT );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,255*LowColor),min(255,85+(255-85)*LowColor),min(255,255*LowColor)) );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	CPen Pen;
	Pen.CreatePen(PS_NULL,1,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	int CenterX;
	int CenterY;
	int CircleSize = x3/2;
	switch( m_CurrentRotation )
	{
	case 0:
	case 3:
		CenterX = x+x3+x2/2;
		CenterY = y+y3-y2+y2/2;
		break;
	case 1:
	case 4:
		CenterX = x+x2;
		CenterY = y+y3+(y3-y2)/2;
		break;
	case 2:
	case 5:
		CenterX = x+x2+x2/2;
		CenterY = y+y3-y2+y2/2;
		break;
	}

	pDC->Ellipse( CenterX-CircleSize, CenterY-CircleSize, CenterX+CircleSize+1, CenterY+CircleSize+1 );
	pDC->DrawText( _T("15"), CRect(CenterX-x3,CenterY-x3,CenterX+x3,CenterY+x3), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldPen );
	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldFont );
}

// Render a tile (3D view)
//
void CTileTree4::Render1( void* pView, bool ForShadow, bool BindTexture )
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

	switch( m_CurrentRotation )
	{
	case 0:
		break;
	case 1:
		glRotated( -60, 0, 0, 1 );
		break;
	case 2:
		glTranslated( TILE3D_WIDTH, 0, 0 );
		glRotated( -120, 0, 0, 1 );
		break;
	case 3:
		glTranslated( TILE3D_WIDTH*1.5, -TILE3D_HEIGHT, 0 );
		glRotated( -180, 0, 0, 1 );
		break;
	case 4:
		glTranslated( 0, -TILE3D_HEIGHT*2, 0 );
		glRotated( -240, 0, 0, 1 );
		break;
	case 5:
		glTranslated( -TILE3D_WIDTH*0.5, -TILE3D_HEIGHT, 0 );
		glRotated( -300, 0, 0, 1 );
		break;
	}

	((CHeroscapeEditor3DView*) pView)->m_pTree15->Render( BindTexture );

	glPopMatrix();
}

