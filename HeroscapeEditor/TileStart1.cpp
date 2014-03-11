// TileStart1.cpp : implementation file
//

#include "StdAfx.h"

#include <GL\Glu.h>

#include "TileStart1.h"

// The constructor
//
CTileStart1::CTileStart1( CString Name, COLORREF Color )
{
	m_StartName = Name;
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_STARTAREA*1000+m_NbTile;
	m_TileColor = Color;
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileStart1::~CTileStart1()
{
}

// Get a copy of this tile
//
CTile* CTileStart1::GetCopy()
{
	return new CTileStart1( m_StartName, m_TileColor );
}

// Draw the tiles
//
void CTileStart1::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	double LowColor = GetLowColor( DrawingLevel );

	CBrush BlackBrush;
	if( m_IsSelected )
		BlackBrush.CreateSolidBrush( RGB(255,255*LowColor,255*LowColor) );
	else
		BlackBrush.CreateSolidBrush( RGB(255*LowColor,255*LowColor,255*LowColor) );
	CBrush* pOldBrush = pDC->SelectObject( &BlackBrush );

	pDC->Ellipse( (int) (x+x2*0.2+1), (int) (y+(y3-y2)/2-x2+x2*0.2+1), (int) (x+x3-x2*0.2), (int) (y+(y3-y2)/2+x2-x2*0.2) );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor)+(255-GetRValue(m_TileColor))*LowColor),min(255,GetGValue(m_TileColor)+(255-GetGValue(m_TileColor))*LowColor),min(255,GetBValue(m_TileColor)+(255-GetBValue(m_TileColor))*LowColor)) );
	pDC->SelectObject( &Brush );

	pDC->Ellipse( (int) (x+x2-x2*0.5+0.5)+1, (int) (y+(y3-y2)/2-x2*0.5+0.5)+1, (int) (x+x2+x2*0.5), (int) (y+(y3-y2)/2+x2*0.5) );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

}

// Render a tile 1 hexagon
//
void CTileStart1::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	if( !BindTexture )
		return; 

	double TileExplode = 1.00;

	GLfloat Color[4];
	glGetFloatv( GL_CURRENT_COLOR, Color );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4d( GetRValue(m_TileColor)/255.0, GetGValue(m_TileColor)/255.0, GetBValue(m_TileColor)/255.0, 0.4 );

	glMatrixMode( GL_MODELVIEW );
	for( int i=0; i<m_NbTile; i++ )
	{
		glPushMatrix();
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[i].y%2==0 )
				glTranslated( (m_PosX+m_TilePosition[i].x)*TILE3D_WIDTH*TileExplode+TILE3D_X3, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode+TILE3D_ZHEIGHT/10.0 );
			else
				glTranslated( (m_PosX+m_TilePosition[i].x+1)*TILE3D_WIDTH*TileExplode, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode+TILE3D_ZHEIGHT/10.0 );
		}
		else
		{
			if( m_TilePosition[i].y%2==1 )
				glTranslated( (m_PosX+m_TilePosition[i].x)*TILE3D_WIDTH*TileExplode+TILE3D_X3, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode+TILE3D_ZHEIGHT/10.0 );
			else
				glTranslated( (m_PosX+m_TilePosition[i].x)*TILE3D_WIDTH*TileExplode, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT*TileExplode, m_PosZ*TILE3D_ZHEIGHT*TileExplode+TILE3D_ZHEIGHT/10.0 );
		}

		GLUquadricObj* pObj = gluNewQuadric();
		gluDisk( pObj, 0, TILE3D_X3*0.6, 20, 1 );
		gluDeleteQuadric( pObj );

		glPopMatrix();
	}
	glColor4fv( Color );

	glEnable( GL_TEXTURE_2D );
	glDisable( GL_COLOR_MATERIAL );
	glDisable( GL_BLEND );
}

