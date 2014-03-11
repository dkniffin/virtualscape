// TileNumber.cpp : implementation file
//

#include "StdAfx.h"

#include "TileNumber.h"
#include "HeroscapeEditor3DView.h"
#include "Game3DView.h"

// The constructor
//
CTileNumber::CTileNumber()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_TREE*1000+41;
	m_TileColor = RGB(80,80,80);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileNumber::~CTileNumber()
{
}

// Get a copy of this tile
//
CTile* CTileNumber::GetCopy()
{
	return new CTileNumber;
}

// Draw more on a tile
//
void CTileNumber::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (x3/2), (int) (x3/3), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(255,255,255) );
	pDC->SetBkMode( TRANSPARENT );

	int CenterX = x+x2;
	int CenterY = y+(y3-y2)/2;

	pDC->DrawText( m_Text, CRect(CenterX-x3,CenterY-x3,CenterX+x3,CenterY+x3), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );
}
