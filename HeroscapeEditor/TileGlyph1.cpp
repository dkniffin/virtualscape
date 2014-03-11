// TileGlyph1.cpp : implementation file
//

#include "StdAfx.h"

#include "TileGlyph1.h"

// The constructor
//
CTileGlyph1::CTileGlyph1( char Letter )
{
	m_GlyphLetter = Letter;
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_GLYPH*1000+Letter;
	m_TileColor = RGB(64,0,0);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileGlyph1::~CTileGlyph1()
{
}

// Get a copy of this tile
//
CTile* CTileGlyph1::GetCopy()
{
	return new CTileGlyph1( m_GlyphLetter );
}

// Draw more on a tile
//
void CTileGlyph1::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (x3/1.5), (int) (x3/3), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(255,255,255) );
	pDC->SetBkMode( TRANSPARENT );

	int CenterX = x+x2;
	int CenterY = y+(y3-y2)/2;

	CString Letter;
	Letter.Format( _T("%c"), m_GlyphLetter );

	pDC->DrawText( Letter, CRect(CenterX-x3,CenterY-x3,CenterX+x3+1,CenterY+x3+2), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );
}
