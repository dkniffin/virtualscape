// TileGlacier6.cpp : implementation file
//

#include "StdAfx.h"

#include "Game3DView.h"
#include "TileGlacier6.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileGlacier6::CTileGlacier6()
{
	m_NbTile = 6;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_GLACIER*1000+m_NbTile;
	m_TileColor = RGB(180,180,255);

	Init();
}

// The destructor
//
CTileGlacier6::~CTileGlacier6()
{
}

// Get a copy of this tile
//
CTile* CTileGlacier6::GetCopy()
{
	return new CTileGlacier6;
}

// When the rotation change
//
void CTileGlacier6::OnRotationChange()
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
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		break;
	case 1:
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
		break;
	case 2:
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
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 3;
		break;
	}
}

// Draw more on a tile
//
void CTileGlacier6::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (x3/2), (int) (x3/3), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(0,0,0) );
	pDC->SetBkMode( TRANSPARENT );

	POINT Point1,Point2,Point3,Point4,Point5,Point6;

	switch( m_CurrentRotation )
	{
	case 0:
	case 3:
		Point1.x=x;
		Point1.y=y+y3+(y3-y2)/2;
		Point2.x=x+x2;
		Point2.y=y+(y3-y2)/2;
		Point3.x=x+x3+x2;
		Point3.y=y+(y3-y2)/2;
		Point4.x=x+x3;
		Point4.y=y+y3+(y3-y2)/2;
		Point5.x=x+x3+x3;
		Point5.y=y+y3+(y3-y2)/2;
		Point6.x=x+x3+x3+x2;
		Point6.y=y+(y3-y2)/2;
		break;
	case 1:
	case 4:
		Point1.x=x+x2;
		Point1.y=y+(y3-y2)/2;
		Point2.x=x+x3+x2;
		Point2.y=y+(y3-y2)/2;
		Point3.x=x+x3;
		Point3.y=y+y3+(y3-y2)/2;
		Point4.x=x+x3+x3;
		Point4.y=y+y3+(y3-y2)/2;
		Point5.x=x+x3+x2;
		Point5.y=y+y3+y3+(y3-y2)/2;
		Point6.x=x+x3+x3+x2;
		Point6.y=y+y3+y3+(y3-y2)/2;
		break;
	case 2:
	case 5:
		Point1.x=x+x2;
		Point1.y=y+(y3-y2)/2;
		Point2.x=x;
		Point2.y=y+y3+(y3-y2)/2;
		Point3.x=x+x3;
		Point3.y=y+y3+(y3-y2)/2;
		Point4.x=x-x2;
		Point4.y=y+y3+y3+(y3-y2)/2;
		Point5.x=x+x2;
		Point5.y=y+y3+y3+(y3-y2)/2;
		Point6.x=x;
		Point6.y=y+y3+y3+y3+(y3-y2)/2;
		break;
	}

	pDC->DrawText( _T("9"), CRect(Point1.x-x3,Point1.y-x3,Point1.x+x3+1,Point1.y+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->DrawText( _T("17"), CRect(Point2.x-x3,Point2.y-x3,Point2.x+x3+1,Point2.y+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->DrawText( _T("17"), CRect(Point3.x-x3,Point3.y-x3,Point3.x+x3+1,Point3.y+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->DrawText( _T("17"), CRect(Point4.x-x3,Point4.y-x3,Point4.x+x3+1,Point4.y+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->DrawText( _T("17"), CRect(Point5.x-x3,Point5.y-x3,Point5.x+x3+1,Point5.y+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	pDC->DrawText( _T("9"), CRect(Point6.x-x3,Point6.y-x3,Point6.x+x3+1,Point6.y+x3+1), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );
}

// Render a tile (3D view)
//
void CTileGlacier6::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

	// Call the base class
	CTile::Render1( pView, ForShadow, BindTexture );

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
		glTranslated( TILE3D_WIDTH, 0, 0 );
		glRotated( -60, 0, 0, 1 );
		break;
	case 2:
		glTranslated( TILE3D_WIDTH*.5, -TILE3D_Y1*2+TILE3D_Y2, 0 );
		glRotated( -120, 0, 0, 1 );
		break;
	case 3:
		glTranslated( TILE3D_WIDTH*1.5, -TILE3D_Y1*2+TILE3D_Y2, 0 );
		glRotated( -180, 0, 0, 1 );
		break;
	case 4:
		glTranslated( TILE3D_WIDTH, -TILE3D_HEIGHT*2, 0 );
		glRotated( -240, 0, 0, 1 );
		break;
	case 5:
		glTranslated( -TILE3D_WIDTH, 2*(-TILE3D_Y1*2+TILE3D_Y2), 0 );
		glRotated( -300, 0, 0, 1 );
		break;
	}

	((CHeroscapeEditor3DView*) pView)->m_pGlacier6->Render( BindTexture );

	glPopMatrix();
}

