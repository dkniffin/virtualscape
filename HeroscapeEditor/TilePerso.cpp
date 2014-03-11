// TilePerso.cpp : implementation file
//

#include "StdAfx.h"

#include "TilePerso.h"
#include "Resource.h"

// The constructor
//
CTilePerso::CTilePerso()
{
	m_Name.LoadStringW( IDS_NONAME );
	m_NbTile = 1;
	m_Quantity = 0;
	m_Type = TYPE_PERSONAL*1000;
	m_TileColor = RGB(160,160,160);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTilePerso::~CTilePerso()
{
}

// Get a copy of this tile
//
CTile* CTilePerso::GetCopy()
{
	CTilePerso* pTile = new CTilePerso;
	pTile->m_Name = m_Name;
	pTile->m_NbTile = m_NbTile;
	pTile->m_Quantity = m_Quantity;
	pTile->m_PersonalTexture = m_PersonalTexture;
	pTile->m_PersonalTextureSide = m_PersonalTextureSide;
	pTile->m_Char = m_Char;
	pTile->m_TileColor = m_TileColor;

	pTile->Init();

	return pTile;
}

// When the rotation change
//
void CTilePerso::OnRotationChange()
{
	int CurrentPos = 0;

	switch( m_NbTile )
	{
	case 1:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		break;
	case 2:
		switch( m_CurrentRotation )
		{
		case 0:
		case 3:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 0;
			break;
		case 1:
		case 4:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			break;
		case 2:
		case 5:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 1;
			break;
		}
		break;
	case 3:
		switch( m_CurrentRotation )
		{
		case 0:
		case 2:
		case 4:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			break;
		case 1:
		case 3:
		case 5:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			break;
		}
		break;
	case 7:
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 0;
		m_TilePosition[CurrentPos].x = -1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 1;
		m_TilePosition[CurrentPos].x = 0;
		m_TilePosition[CurrentPos++].y = 2;
		m_TilePosition[CurrentPos].x = 1;
		m_TilePosition[CurrentPos++].y = 2;
		break;
	case 24:
		switch( m_CurrentRotation )
		{
		case 0:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 5;
			break;
		case 1:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -3;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -3;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 6;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 6;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 7;
			break;
		case 2:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -3;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 5;
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
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 5;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 5;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 5;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 3;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 4;
			m_TilePosition[CurrentPos++].y = 5;
			break;
		case 4:
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
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 5;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 6;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 6;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 6;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 6;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 7;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 7;
			break;
		case 5:
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = 2;
			m_TilePosition[CurrentPos++].y = 0;
			m_TilePosition[CurrentPos].x = -4;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -3;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 1;
			m_TilePosition[CurrentPos].x = -4;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -3;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = 1;
			m_TilePosition[CurrentPos++].y = 2;
			m_TilePosition[CurrentPos].x = -4;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -3;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 3;
			m_TilePosition[CurrentPos].x = -2;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = 0;
			m_TilePosition[CurrentPos++].y = 4;
			m_TilePosition[CurrentPos].x = -1;
			m_TilePosition[CurrentPos++].y = 5;
			break;
		}
		break;
	}
}

// Get the name of the tile
//
CString CTilePerso::GetName()
{
	CString Name;
	Name.Format( _T("%s %i"), m_Name, m_NbTile );

	return Name;
}

// Draw more on a tile
//
void CTilePerso::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (x3/2), (int) (x3/3), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	pDC->SetTextColor( RGB(255,255,255) );
	pDC->SetBkMode( TRANSPARENT );

	int CenterX = x+x2;
	int CenterY = y+(y3-y2)/2;

	pDC->DrawText( m_Char, CRect(CenterX-x3,CenterY-x3,CenterX+x3,CenterY+x3), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );
}

// Fill the members with members of an other tile
//
void CTilePerso::FillCopy( CTile* pTile )
{
	CTile::FillCopy( pTile );
	m_Char = ((CTilePerso*) pTile)->m_Char;
	m_Name = ((CTilePerso*) pTile)->m_Name;
	m_Quantity = ((CTilePerso*) pTile)->m_Quantity;
}
