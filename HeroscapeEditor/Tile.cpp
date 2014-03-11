// Tile.cpp : implementation file
//

#include "StdAfx.h"

#include <GL\gl.h>
#include <math.h>

#include "Resource.h"
#include "Tile.h"
#include "TileAsphalt1.h"
#include "TileAsphalt2.h"
#include "TileAsphalt7.h"
#include "TileCastle1.h"
#include "TileCastle7.h"
#include "TileCastle9.h"
#include "TileCastleArch.h"
#include "TileCastleBaseCorner.h"
#include "TileCastleBaseStraight.h"
#include "TileCastleBaseEnd.h"
#include "TileCastleBattlement.h"
#include "TileCastleDoor.h"
#include "TileCastleFlag.h"
#include "TileCastleLadder.h"
#include "TileCastleWallCorner.h"
#include "TileCastleWallStraight.h"
#include "TileCastleWallEnd.h"
#include "TileConcrete1.h"
#include "TileConcrete2.h"
#include "TileConcrete7.h"
#include "TileDungeon1.h"
#include "TileDungeon2.h"
#include "TileDungeon3.h"
#include "TileDungeon7.h"
#include "TileDungeon24.h"
#include "TileFigure.h"
#include "TileFigure2.h"
#include "TileGlacier1_7.h"
#include "TileGlacier3.h"
#include "TileGlacier4.h"
#include "TileGlacier6.h"
#include "TileGlyph1.h"
#include "TileGrass1.h"
#include "TileGrass2.h"
#include "TileGrass3.h"
#include "TileGrass7.h"
#include "TileGrass24.h"
#include "TileHive6.h"
#include "TileIce1.h"
#include "TileLava1.h"
#include "TileLavaField7.h"
#include "TileLavaField2.h"
#include "TileLavaField1.h"
#include "TileMarvelWall6.h"
#include "TileMarvelWall6Breaked.h"
#include "TileOutcrop1_7.h"
#include "TileOutcrop3.h"
#include "TilePalm14.h"
#include "TilePalm15.h"
#include "TilePalm16.h"
#include "TilePerso.h"
#include "TileRoad1.h"
#include "TileRoad2.h"
#include "TileRoad5.h"
#include "TileRock1.h"
#include "TileRock2.h"
#include "TileRock3.h"
#include "TileRock7.h"
#include "TileRock24.h"
#include "TileRuin2.h"
#include "TileRuin3.h"
#include "TileSand1.h"
#include "TileSand2.h"
#include "TileSand3.h"
#include "TileSand7.h"
#include "TileShadow1.h"
#include "TileShadow2.h"
#include "TileSnow1.h"
#include "TileSnow2.h"
#include "TileStart1.h"
#include "TileSwamp1.h"
#include "TileSwamp2.h"
#include "TileSwamp3.h"
#include "TileSwamp7.h"
#include "TileSwamp24.h"
#include "TileSwampWater1.h"
#include "TileTicallaGrass1.h"
#include "TileTree4.h"
#include "TileTree1_10.h"
#include "TileTree1_11.h"
#include "TileTree1_12.h"
#include "TileWater1.h"
#include "TileWater2.h"
#include "TileWall4.h"

#include "Game3DView.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTile::CTile()
{
	// No rotation now
	m_CurrentRotation = 0;
	// No tile
	m_NbTile = 0;
	// No position on the battlefield now
	m_PosX = -1;
	m_PosY = -1;
	m_PosZ = -1;
	// Default size
	m_PixelSizeX = m_PixelSizeY = 1;
	// The tile isn't selected
	m_IsSelected = false;
	// The tile must be display
	m_ToDisplay = true;
	// The tile height by default
	m_TileHeight = TILE3D_ZHEIGHT;
	// Height is 1
	m_Height = 1;
	// No printing transparency
	m_PrintingTransparency = -1;
	// Point are not computed
	m_PointComputed = false;
	m_TextureId = -1;
	m_TextureSideId = -1;
	// This is not an attack figure
	m_IsAttackFigure = false;
	// This is not a defense figure
	m_IsDefenseFigure = false;
	// No Explode Time
	m_ExplodeTime = 0;
	// No Creation Time
	m_CreationTime = -1;
	// No dice number by default
	m_DiceNumber = 0;
	// No attack time
	m_AttackTime = -1;
}

// The destructor
//
CTile::~CTile()
{
	FreeAllTargets();
}

// Draw the sample of the tile
//
void CTile::DrawSample( CDC* pDC, int x, int y )
{
	Draw( pDC, x, y, 6, 12, 3, 11, 14, -1 );
}

// Draw a tile
//
void CTile::DrawTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4)
{
	POINT Points[6];

	Points[0].x = x;
	Points[0].y = y;
	Points[1].x = x+x2;
	Points[1].y = y-y2;
	Points[2].x = x+x3;
	Points[2].y = y;
	Points[3].x = x+x3;
	Points[3].y = y-y2+y3;
	Points[4].x = x+x2;
	Points[4].y = y-y2+y4;
	Points[5].x = x;
	Points[5].y = y-y2+y3;

	CBrush Brush;
	Brush.CreateSolidBrush( m_TileColor );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	CPen Pen;
	Pen.CreatePen(PS_NULL,1,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	pDC->Polygon( Points, 6 );

	pDC->SelectObject( pOldPen );
	pDC->SelectObject( pOldBrush );
}

// Get the low color depending of level
//
double CTile::GetLowColor( int DrawingLevel )
{
	if( m_PrintingTransparency>=0 )
		return m_PrintingTransparency;

	if( m_PosZ<0 )
		return 0;
	if( m_PosZ+m_Height-1<DrawingLevel-1 )
		return 0.7;
	else if( m_PosZ+m_Height-1==DrawingLevel-1 )
		return 0.5;
	else
		return 0;
}

// Draw the num
//
void CTile::DrawNum( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, double OffsetX, double OffsetY)
{
	for( int i=0; i<m_NbTile; i++ )
	{
		// Draw num
		CString Num,Num2;

		double PosX;
		double OffsetNumX;
		if( (m_TilePosition[i].y)%2==0 )
		{
			PosX = x;
			OffsetNumX = 0;
		}
		else
		{
			PosX = x+x2;
			OffsetNumX = 0.5;
		}

		int Offset = (int) (PosX/x3+m_TilePosition[i].x-1.5);
		if( Offset>25 )
			Num.Format(_T("%c%c"),'A'+((int) (Offset/26))-1,(Offset%26)+'A');
		else
			Num.Format(_T("%c"),Offset+'A');

		Num2.Format( _T("%s%i"), Num, (int) (m_PosY+m_TilePosition[i].y-OffsetY+1) );

		pDC->DrawText( Num2, CRect( (int) (PosX+m_TilePosition[i].x*x3), (int) (y-y2+m_TilePosition[i].y*y3), (int) (PosX+x3+m_TilePosition[i].x*x3), (int) (y+y4-y2+m_TilePosition[i].y*y3)), DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	}
}

// Draw the tiles
//
void CTile::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	if( !m_PointComputed || x!=m_XComputed || y!=m_YComputed || x2!=m_X2Computed )
	{
		m_NbPoint = 1;
		int		TilePos = 0;

		if( m_TilePosition[0].y%2==0 )
			m_Points[0].x = x;
		else
			m_Points[0].x = x+x2;
	
		m_Points[0].y = y;
		int CurrentPosX = m_TilePosition[0].x;
		int CurrentPosY = m_TilePosition[0].y;

		while( m_NbPoint==1 || m_Points[m_NbPoint-1].x!=m_Points[0].x || m_Points[m_NbPoint-1].y!=m_Points[0].y )
		{
			bool	Found=false;
			// Compute next line
		
			int OffsetX;
			if( CurrentPosY%2==1 )
				OffsetX = 1;
			else
				OffsetX = 0;

			bool	t1,t2,t3,t4,t5,t6;
			t1=t2=t3=t4=t5=t6=false;

			// Set six adjacent tile
			for( int i=0; i<m_NbTile; i++ )
			{
				if( m_TilePosition[i].x==CurrentPosX-1+OffsetX && m_TilePosition[i].y==CurrentPosY-1 )
					t1=true;
				if( m_TilePosition[i].x==CurrentPosX+OffsetX && m_TilePosition[i].y==CurrentPosY-1 )
					t2=true;
				if( m_TilePosition[i].x==CurrentPosX+1 && m_TilePosition[i].y==CurrentPosY )
					t3=true;
				if( m_TilePosition[i].x==CurrentPosX+OffsetX && m_TilePosition[i].y==CurrentPosY+1 )
					t4=true;
				if( m_TilePosition[i].x==CurrentPosX-1+OffsetX && m_TilePosition[i].y==CurrentPosY+1 )
					t5=true;
				if( m_TilePosition[i].x==CurrentPosX-1 && m_TilePosition[i].y==CurrentPosY )
					t6=true;
			}

			switch( TilePos )
			{
			case 0:
				if( t1 )
				{
					CurrentPosX = CurrentPosX-1+OffsetX;
					CurrentPosY = CurrentPosY-1;
					TilePos = 5;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x - x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y - y2;
					m_NbPoint++;
				}
				else
				{
					TilePos = 1;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x + x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y - y2;
					m_NbPoint++;
				}
				break;
			case 1:
				if( t2 )
				{
					CurrentPosX = CurrentPosX+OffsetX;
					CurrentPosY = CurrentPosY-1;
					TilePos = 0;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y - y3 + y2;
					m_NbPoint++;
				}
				else
				{
					TilePos = 2;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x + x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y + y2;
					m_NbPoint++;
				}
				break;
			case 2:
				if( t3 )
				{
					CurrentPosX = CurrentPosX+1;
					CurrentPosY = CurrentPosY;
					TilePos = 1;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x + x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y - y2;
					m_NbPoint++;
				}
				else
				{
					TilePos = 3;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y + y3 - y2;
					m_NbPoint++;
				}
				break;
			case 3:
				if( t4 )
				{
					CurrentPosX = CurrentPosX+OffsetX;
					CurrentPosY = CurrentPosY+1;
					TilePos = 2;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x + x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y + y2;
					m_NbPoint++;
				}
				else
				{
					TilePos = 4;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x - x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y + y2;
					m_NbPoint++;
				}
				break;
			case 4:
				if( t5 )
				{
					CurrentPosX = CurrentPosX-1+OffsetX;
					CurrentPosY = CurrentPosY+1;
					TilePos = 3;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y + y3 - y2;
					m_NbPoint++;
				}
				else
				{
					TilePos = 5;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x - x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y - y2;
					m_NbPoint++;
				}
				break;
			case 5:
				if( t6 )
				{
					CurrentPosX = CurrentPosX-1;
					CurrentPosY = CurrentPosY;
					TilePos = 4;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x - x2;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y + y2;
					m_NbPoint++;
				}
				else
				{
					TilePos = 0;
					m_Points[m_NbPoint].x = m_Points[m_NbPoint-1].x;
					m_Points[m_NbPoint].y = m_Points[m_NbPoint-1].y - y3 + y2;
					m_NbPoint++;
				}
				break;
			}
		}
	
		// Now, move each point toward inside
		POINT Vector;
		Vector.x = ((m_Points[0].y-m_Points[m_NbPoint-2].y)+(m_Points[1].y-m_Points[0].y));
		Vector.y = ((m_Points[0].x-m_Points[m_NbPoint-2].x)+(m_Points[1].x-m_Points[0].x));

		double Coef=5;
		if( sqrt((double) ((Vector.x*Vector.x)+(Vector.y*Vector.y)))<10 )
			Coef=sqrt((double) ((Vector.x*Vector.x)+(Vector.y*Vector.y)))/2;

		for( int i=0; i<m_NbPoint; i++ )
		{
			if( i==0 )
			{
				m_Points2[i].x = (LONG) (m_Points[i].x-(int) (((m_Points[i].y-m_Points[m_NbPoint-2].y)+(m_Points[i+1].y-m_Points[i].y))/Coef)+0.5);
				m_Points2[i].y = (LONG) (m_Points[i].y+(int) (((m_Points[i].x-m_Points[m_NbPoint-2].x)+(m_Points[i+1].x-m_Points[i].x))/Coef)+0.5);
			}
			else if( i==m_NbPoint-1 )
			{
				m_Points2[i].x = (LONG) (m_Points[i].x-((m_Points[i].y-m_Points[i-1].y)+(m_Points[0].y-m_Points[i].y))/Coef);
				m_Points2[i].y = (LONG) (m_Points[i].y+((m_Points[i].x-m_Points[i-1].x)+(m_Points[0].x-m_Points[i].x))/Coef);
			}
			else
			{
				m_Points2[i].x = (LONG) (m_Points[i].x-(int) (((m_Points[i].y-m_Points[i-1].y)+(m_Points[i+1].y-m_Points[i].y))/Coef)+0.5);
				m_Points2[i].y = (LONG) (m_Points[i].y+(int) (((m_Points[i].x-m_Points[i-1].x)+(m_Points[i+1].x-m_Points[i].x))/Coef)+0.5);
			}
		}
		m_PointComputed = true;
		m_XComputed=x;
		m_YComputed=y;
		m_X2Computed=x2;
	}

	double LowColor = GetLowColor( DrawingLevel );

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush BlackBrush;
	if( m_IsSelected )
		BlackBrush.CreateSolidBrush( RGB(255,255*LowColor,255*LowColor) );
	else
		BlackBrush.CreateSolidBrush( RGB(255*LowColor,255*LowColor,255*LowColor) );
	CBrush* pOldBrush = pDC->SelectObject( &BlackBrush );

	pDC->Polygon( m_Points, m_NbPoint-1 );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor)+(255-GetRValue(m_TileColor))*LowColor),min(255,GetGValue(m_TileColor)+(255-GetGValue(m_TileColor))*LowColor),min(255,GetBValue(m_TileColor)+(255-GetBValue(m_TileColor))*LowColor)) );
	pDC->SelectObject( &Brush );

	pDC->Polygon( m_Points2, m_NbPoint-1 );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

	// Draw inside tile
	for( int i=0; i<m_NbTile; i++ )
	{
		int PosX;
		if( m_TilePosition[i].y%2==0 )
			PosX = x;
		else
			PosX = x+x2;

		DrawExtendTile( pDC, PosX+x3*m_TilePosition[i].x, y+y3*m_TilePosition[i].y, x2, x3, y2, y3, y4, DrawingLevel);
	}

	DrawExtend( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
}

// Draw the tiles at the upper level
//
void CTile::DrawOnionSkinMode( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	POINT	Points[100];
	int		NbPoint = 1;
	int		TilePos = 0;

	double LowColor = GetLowColor( DrawingLevel );

	if( m_TilePosition[0].y%2==0 )
		Points[0].x = x;
	else
		Points[0].x = x+x2;
	Points[0].y = y;
	int CurrentPosX = m_TilePosition[0].x;
	int CurrentPosY = m_TilePosition[0].y;

	while( NbPoint==1 || Points[NbPoint-1].x!=Points[0].x || Points[NbPoint-1].y!=Points[0].y )
	{
		bool	Found=false;
		// Compute next line
		
		int OffsetX;
		if( CurrentPosY%2==1 )
			OffsetX = 1;
		else
			OffsetX = 0;

		bool	t1,t2,t3,t4,t5,t6;
		t1=t2=t3=t4=t5=t6=false;

		// Set six adjacent tile
		for( int i=0; i<m_NbTile; i++ )
		{
			if( m_TilePosition[i].x==CurrentPosX-1+OffsetX && m_TilePosition[i].y==CurrentPosY-1 )
				t1=true;
			if( m_TilePosition[i].x==CurrentPosX+OffsetX && m_TilePosition[i].y==CurrentPosY-1 )
				t2=true;
			if( m_TilePosition[i].x==CurrentPosX+1 && m_TilePosition[i].y==CurrentPosY )
				t3=true;
			if( m_TilePosition[i].x==CurrentPosX+OffsetX && m_TilePosition[i].y==CurrentPosY+1 )
				t4=true;
			if( m_TilePosition[i].x==CurrentPosX-1+OffsetX && m_TilePosition[i].y==CurrentPosY+1 )
				t5=true;
			if( m_TilePosition[i].x==CurrentPosX-1 && m_TilePosition[i].y==CurrentPosY )
				t6=true;
		}

		switch( TilePos )
		{
		case 0:
			if( t1 )
			{
				CurrentPosX = CurrentPosX-1+OffsetX;
				CurrentPosY = CurrentPosY-1;
				TilePos = 5;
				Points[NbPoint].x = Points[NbPoint-1].x - x2;
				Points[NbPoint].y = Points[NbPoint-1].y - y2;
				NbPoint++;
			}
			else
			{
				TilePos = 1;
				Points[NbPoint].x = Points[NbPoint-1].x + x2;
				Points[NbPoint].y = Points[NbPoint-1].y - y2;
				NbPoint++;
			}
			break;
		case 1:
			if( t2 )
			{
				CurrentPosX = CurrentPosX+OffsetX;
				CurrentPosY = CurrentPosY-1;
				TilePos = 0;
				Points[NbPoint].x = Points[NbPoint-1].x;
				Points[NbPoint].y = Points[NbPoint-1].y - y3 + y2;
				NbPoint++;
			}
			else
			{
				TilePos = 2;
				Points[NbPoint].x = Points[NbPoint-1].x + x2;
				Points[NbPoint].y = Points[NbPoint-1].y + y2;
				NbPoint++;
			}
			break;
		case 2:
			if( t3 )
			{
				CurrentPosX = CurrentPosX+1;
				CurrentPosY = CurrentPosY;
				TilePos = 1;
				Points[NbPoint].x = Points[NbPoint-1].x + x2;
				Points[NbPoint].y = Points[NbPoint-1].y - y2;
				NbPoint++;
			}
			else
			{
				TilePos = 3;
				Points[NbPoint].x = Points[NbPoint-1].x;
				Points[NbPoint].y = Points[NbPoint-1].y + y3 - y2;
				NbPoint++;
			}
			break;
		case 3:
			if( t4 )
			{
				CurrentPosX = CurrentPosX+OffsetX;
				CurrentPosY = CurrentPosY+1;
				TilePos = 2;
				Points[NbPoint].x = Points[NbPoint-1].x + x2;
				Points[NbPoint].y = Points[NbPoint-1].y + y2;
				NbPoint++;
			}
			else
			{
				TilePos = 4;
				Points[NbPoint].x = Points[NbPoint-1].x - x2;
				Points[NbPoint].y = Points[NbPoint-1].y + y2;
				NbPoint++;
			}
			break;
		case 4:
			if( t5 )
			{
				CurrentPosX = CurrentPosX-1+OffsetX;
				CurrentPosY = CurrentPosY+1;
				TilePos = 3;
				Points[NbPoint].x = Points[NbPoint-1].x;
				Points[NbPoint].y = Points[NbPoint-1].y + y3 - y2;
				NbPoint++;
			}
			else
			{
				TilePos = 5;
				Points[NbPoint].x = Points[NbPoint-1].x - x2;
				Points[NbPoint].y = Points[NbPoint-1].y - y2;
				NbPoint++;
			}
			break;
		case 5:
			if( t6 )
			{
				CurrentPosX = CurrentPosX-1;
				CurrentPosY = CurrentPosY;
				TilePos = 4;
				Points[NbPoint].x = Points[NbPoint-1].x - x2;
				Points[NbPoint].y = Points[NbPoint-1].y + y2;
				NbPoint++;
			}
			else
			{
				TilePos = 0;
				Points[NbPoint].x = Points[NbPoint-1].x;
				Points[NbPoint].y = Points[NbPoint-1].y - y3 + y2;
				NbPoint++;
			}
			break;
		}
	}

	// Now, move each point toward inside
	POINT	Points2[100];

	POINT Vector;
	Vector.x = ((Points[0].y-Points[NbPoint-2].y)+(Points[1].y-Points[0].y));
	Vector.y = ((Points[0].x-Points[NbPoint-2].x)+(Points[1].x-Points[0].x));

	double Coef=5;
	if( sqrt((double) ((Vector.x*Vector.x)+(Vector.y*Vector.y)))<10 )
		Coef=sqrt((double) ((Vector.x*Vector.x)+(Vector.y*Vector.y)))/2;

	for( int i=0; i<NbPoint; i++ )
	{
		if( i==0 )
		{
			Points2[i].x = (LONG) (Points[i].x-(int) (((Points[i].y-Points[NbPoint-2].y)+(Points[i+1].y-Points[i].y))/Coef)+0.5);
			Points2[i].y = (LONG) (Points[i].y+(int) (((Points[i].x-Points[NbPoint-2].x)+(Points[i+1].x-Points[i].x))/Coef)+0.5);
		}
		else if( i==NbPoint-1 )
		{
			Points2[i].x = (LONG) (Points[i].x-((Points[i].y-Points[i-1].y)+(Points[0].y-Points[i].y))/Coef);
			Points2[i].y = (LONG) (Points[i].y+((Points[i].x-Points[i-1].x)+(Points[0].x-Points[i].x))/Coef);
		}
		else
		{
			Points2[i].x = (LONG) (Points[i].x-(int) (((Points[i].y-Points[i-1].y)+(Points[i+1].y-Points[i].y))/Coef)+0.5);
			Points2[i].y = (LONG) (Points[i].y+(int) (((Points[i].x-Points[i-1].x)+(Points[i+1].x-Points[i].x))/Coef)+0.5);
		}
	}

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	pDC->SetBkMode( TRANSPARENT );

	CBitmap bmp;
	bmp.LoadBitmap( IDB_BRUSH_ONION );

	CBrush BlackBrush;
	BlackBrush.CreatePatternBrush( &bmp );
	CBrush* pOldBrush = pDC->SelectObject( &BlackBrush );

	pDC->SetTextColor( RGB(0,0,0) );
	pDC->SetBkColor( RGB(255,255,255) );
	pDC->SetROP2( R2_MASKPEN );
	pDC->Polygon( Points, NbPoint-1 );

	if( m_IsSelected )
		pDC->SetTextColor( RGB(255,255*LowColor,255*LowColor) );
	else
		pDC->SetTextColor( RGB(255*LowColor,255*LowColor,255*LowColor) );

	pDC->SetBkColor( RGB(0,0,0) );
	pDC->SetROP2( R2_MERGEPEN );
	pDC->Polygon( Points, NbPoint-1 );

	pDC->SetTextColor( RGB(min(255,GetRValue(m_TileColor)+(255-GetRValue(m_TileColor))*LowColor),min(255,GetGValue(m_TileColor)+(255-GetGValue(m_TileColor))*LowColor),min(255,GetBValue(m_TileColor)+(255-GetBValue(m_TileColor))*LowColor)) );

	pDC->Polygon( Points2, NbPoint-1 );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

	// Draw inside tile
	for( int i=0; i<m_NbTile; i++ )
	{
		int PosX;
		if( m_TilePosition[i].y%2==0 )
			PosX = x;
		else
			PosX = x+x2;

		DrawExtendTile( pDC, PosX+x3*m_TilePosition[i].x, y+y3*m_TilePosition[i].y, x2, x3, y2, y3, y4, DrawingLevel);
	}

	DrawExtend( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
}

// Init the tile
//
void CTile::Init()
{
	OnRotationChange();

	int MinX = 1000;
	int MinY = 1000;
	int MaxX = -1000;
	int MaxY = -1000;

	for( int i=0; i<m_NbTile; i++ )
	{
		if( m_TilePosition[i].x>MaxX )
			MaxX = m_TilePosition[i].x;
		if( m_TilePosition[i].y>MaxY )
			MaxY = m_TilePosition[i].y;
		if( m_TilePosition[i].x<MinX )
			MinX = m_TilePosition[i].x;
		if( m_TilePosition[i].y<MinY )
			MinY = m_TilePosition[i].y;
	}

	m_PixelSizeX = MaxX-MinX+1;
	m_PixelSizeY = MaxY-MinY+1;
}

// To know if this tile contain this position on the battlefield
//
bool CTile::ContainPos( int PosX, int PosY )
{
	for( int i=0; i<m_NbTile; i++ )
	{
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[i].y%2==1 )
			{
				if( m_TilePosition[i].x+m_PosX+1==PosX && m_TilePosition[i].y+m_PosY==PosY )
					return true;
			}
			else
				if( m_TilePosition[i].x+m_PosX==PosX && m_TilePosition[i].y+m_PosY==PosY )
					return true;
		}
		else
			if( m_TilePosition[i].x+m_PosX==PosX && m_TilePosition[i].y+m_PosY==PosY )
				return true;
	}

	return false;
}

// Rotate right
//
void CTile::RotateRight()
{
	if( ++m_CurrentRotation>=6 )
		m_CurrentRotation = 0;

	m_PointComputed = false;
	OnRotationChange();
}

// Rotate left
//
void CTile::RotateLeft()
{
	if( --m_CurrentRotation<0 )
		m_CurrentRotation = 5;

	m_PointComputed = false;
	OnRotationChange();
}

// When the rotation change
//
void CTile::OnRotationChange()
{
}

// Get a new tyle of a particular type
//
CTile* CTile::GetNewTile( int Type )
{
	if( Type>TYPE_GLYPH*1000+1 && Type<TYPE_GLYPH*1000+255 )
		return new CTileGlyph1( Type-(TYPE_GLYPH*1000) );

	switch( Type )
	{
	case TYPE_GRASS*1000+1:
		return new CTileGrass1;
		break;
	case TYPE_GRASS*1000+2:
		return new CTileGrass2;
		break;
	case TYPE_GRASS*1000+3:
		return new CTileGrass3;
		break;
	case TYPE_GRASS*1000+7:
		return new CTileGrass7;
		break;
	case TYPE_GRASS*1000+24:
		return new CTileGrass24;
		break;
	case TYPE_ICE*1000+1:
		return new CTileIce1;
		break;
	case TYPE_LAVA*1000+1:
		return new CTileLava1;
		break;
	case TYPE_LAVAFIELD*1000+1:
		return new CTileLavaField1;
		break;
	case TYPE_LAVAFIELD*1000+2:
		return new CTileLavaField2;
		break;
	case TYPE_LAVAFIELD*1000+7:
		return new CTileLavaField7;
		break;
	case TYPE_ROAD*1000+1:
		return new CTileRoad1;
		break;
	case TYPE_ROAD*1000+2:
		return new CTileRoad2;
		break;
	case TYPE_ROAD*1000+5:
		return new CTileRoad5;
		break;
	case TYPE_ROCK*1000+1:
		return new CTileRock1;
		break;
	case TYPE_ROCK*1000+2:
		return new CTileRock2;
		break;
	case TYPE_ROCK*1000+3:
		return new CTileRock3;
		break;
	case TYPE_ROCK*1000+7:
		return new CTileRock7;
		break;
	case TYPE_ROCK*1000+24:
		return new CTileRock24;
		break;
	case TYPE_SAND*1000+1:
		return new CTileSand1;
		break;
	case TYPE_SAND*1000+2:
		return new CTileSand2;
		break;
	case TYPE_SAND*1000+3:
		return new CTileSand3;
		break;
	case TYPE_SAND*1000+7:
		return new CTileSand7;
		break;
	case TYPE_WATER*1000+1:
		return new CTileWater1;
		break;
	case TYPE_WATER*1000+2:
		return new CTileWater2;
		break;
	case TYPE_SNOW*1000+1:
		return new CTileSnow1;
		break;
	case TYPE_SNOW*1000+2:
		return new CTileSnow2;
		break;
	case TYPE_TREE*1000+4:
		return new CTileTree4;
		break;
	case TYPE_TREE*1000+1+10:
		return new CTileTree1_10;
		break;
	case TYPE_TREE*1000+1+11:
		return new CTileTree1_11;
		break;
	case TYPE_TREE*1000+1+12:
		return new CTileTree1_12;
		break;
	case TYPE_RUIN*1000+2:
		return new CTileRuin2;
		break;
	case TYPE_RUIN*1000+3:
		return new CTileRuin3;
		break;
	case TYPE_RUIN*1000+6:
		return new CTileMarvelWall6;
		break;
	case TYPE_RUIN*1000+7:
		return new CTileMarvelWall6Breaked;
		break;
	case TYPE_WALL*1000+4:
		return new CTileWall4;
		break;
	case TYPE_GLACIER*1000+1:
		return new CTileGlacier1_7;
		break;
	case TYPE_GLACIER*1000+3:
		return new CTileGlacier3;
		break;
	case TYPE_GLACIER*1000+4:
		return new CTileGlacier4;
		break;
	case TYPE_GLACIER*1000+6:
		return new CTileGlacier6;
		break;
	case TYPE_GLYPH*1000+1:
		return new CTileGlyph1( '?' );
		break;
	case TYPE_STARTAREA*1000+1:
		return new CTileStart1( _T(""), RGB(0,0,0) );
		break;
	case TYPE_CASTLE*1000+1:
		return new CTileCastle1;
		break;
	case TYPE_CASTLE*1000+7:
		return new CTileCastle7;
		break;
	case TYPE_CASTLE*1000+9:
		return new CTileCastle9;
		break;
	case TYPE_CASTLE*1000+101:
		return new CTileCastleBaseCorner;
		break;
	case TYPE_CASTLE*1000+102:
		return new CTileCastleBaseStraight;
		break;
	case TYPE_CASTLE*1000+103:
		return new CTileCastleBaseEnd;
		break;
	case TYPE_CASTLE*1000+201:
		return new CTileCastleWallCorner;
		break;
	case TYPE_CASTLE*1000+202:
		return new CTileCastleWallStraight;
		break;
	case TYPE_CASTLE*1000+203:
		return new CTileCastleWallEnd;
		break;
	case TYPE_CASTLE*1000+301:
		return new CTileCastleBattlement;
		break;
	case TYPE_CASTLE*1000+401:
		return new CTileCastleDoor;
		break;
	case TYPE_CASTLE*1000+402:
		return new CTileCastleLadder;
		break;
	case TYPE_CASTLE*1000+403:
		return new CTileCastleFlag;
		break;
	case TYPE_CASTLE*1000+404:
		return new CTileCastleArch;
		break;
	case TYPE_PERSONAL*1000:
		return new CTilePerso;
		break;
	case TYPE_FIGURE*1000+1:
		return new CTileFigure;
		break;
	case TYPE_FIGURE*1000+2:
		return new CTileFigure2;
		break;
	case TYPE_SWAMP*1000+1:
		return new CTileSwamp1;
		break;
	case TYPE_SWAMP*1000+2:
		return new CTileSwamp2;
		break;
	case TYPE_SWAMP*1000+3:
		return new CTileSwamp3;
		break;
	case TYPE_SWAMP*1000+7:
		return new CTileSwamp7;
		break;
	case TYPE_SWAMP*1000+24:
		return new CTileSwamp24;
		break;
	case TYPE_SWAMPWATER*1000+1:
		return new CTileSwampWater1;
		break;
	case TYPE_CONCRETE*1000+1:
		return new CTileConcrete1;
		break;
	case TYPE_CONCRETE*1000+2:
		return new CTileConcrete2;
		break;
	case TYPE_CONCRETE*1000+7:
		return new CTileConcrete7;
		break;
	case TYPE_ASPHALT*1000+1:
		return new CTileAsphalt1;
		break;
	case TYPE_ASPHALT*1000+2:
		return new CTileAsphalt2;
		break;
	case TYPE_ASPHALT*1000+7:
		return new CTileAsphalt7;
		break;
	case TYPE_HIVE*1000+6:
		return new CTileHive6;
		break;
	case TYPE_TICALLA*1000+14:
		return new CTilePalm14;
		break;
	case TYPE_TICALLA*1000+1: // For compatibility
	case TYPE_TICALLA*1000+15:
		return new CTilePalm15;
		break;
	case TYPE_TICALLA*1000+16:
		return new CTilePalm16;
		break;
	case TYPE_TICALLA*1000+2:
		return new CTileTicallaGrass1;
		break;
	case TYPE_SHADOW*1000+1:
		return new CTileShadow1;
		break;
	case TYPE_SHADOW*1000+2:
		return new CTileShadow2;
		break;
	case TYPE_DUNGEON*1000+1:
		return new CTileDungeon1;
		break;
	case TYPE_DUNGEON*1000+2:
		return new CTileDungeon2;
		break;
	case TYPE_DUNGEON*1000+3:
		return new CTileDungeon3;
		break;
	case TYPE_DUNGEON*1000+7:
		return new CTileDungeon7;
		break;
	case TYPE_DUNGEON*1000+24:
		return new CTileDungeon24;
		break;
	case TYPE_OUTCROP*1000+1:
		return new CTileOutcrop1_7;
		break;
	case TYPE_OUTCROP*1000+3:
		return new CTileOutcrop3;
		break;
	default:
		AfxMessageBox( _T("Tile unknown") );
		break;
	}

	return NULL;
}

// Save or load a tile
//
void CTile::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// Save the version
		double Version = 0.0003;
		ar << Version;

		ar << m_CurrentRotation;
		ar << m_PosX;
		ar << m_PosY;
		ar << m_PosZ;
		ar << m_GlyphLetter;
		// For compatibility
		CString GlyphName=_T("");
		ar << GlyphName;
		// End of compatibility
		ar << m_StartName;
		ar << m_TileColor;
		if( m_Type==TYPE_PERSONAL*1000 )
		{
			ar << m_NbTile;
			ar << m_PersonalTexture;
			ar << m_PersonalTextureSide;
			ar << ((CTilePerso*) this)->m_Char;
			ar << ((CTilePerso*) this)->m_Name;
		}
		else if( (m_Type/1000)==TYPE_FIGURE )
		{
			ar << ((CTileFigure*) this)->m_FigureName;
			ar << ((CTileFigure*) this)->m_FigureFile;
		}
	}
	else
	{
		// Read the document version
		double Version;
		ar >> Version;

		if( Version==0.0001 )
			LoadVersion0_0001( ar );
		else if( Version==0.0002 )
			LoadVersion0_0002( ar );
		else if( Version==0.0003 )
			LoadVersion0_0003( ar );
		else
		{
			CString Str;
			Str.LoadString( IDS_FILEVERSION_TOO_RECENT );
			AfxMessageBox( Str );
		}
	}
}

// Load the document
//
void CTile::LoadVersion0_0003( CArchive& ar )
{
	ar >> m_CurrentRotation;
	ar >> m_PosX;
	ar >> m_PosY;
	ar >> m_PosZ;
	ar >> m_GlyphLetter;
	// For compatibility
	CString GlyphName;
	ar >> GlyphName;
	// End of compatibility
	ar >> m_StartName;
	ar >> m_TileColor;
	if( m_Type==TYPE_PERSONAL*1000 )
	{
		ar >> m_NbTile;
		ar >> m_PersonalTexture;
		ar >> m_PersonalTextureSide;
		ar >> ((CTilePerso*) this)->m_Char;
		ar >> ((CTilePerso*) this)->m_Name;
	}
	else if( (m_Type/1000)==TYPE_FIGURE )
	{
		ar >> ((CTileFigure*) this)->m_FigureName;
		ar >> ((CTileFigure*) this)->m_FigureFile;
	}

	OnRotationChange();
}

// Load the document
//
void CTile::LoadVersion0_0002( CArchive& ar )
{
	ar >> m_CurrentRotation;
	ar >> m_PosX;
	ar >> m_PosY;
	ar >> m_PosZ;
	ar >> m_GlyphLetter;
	// For compatibility
	CString GlyphName;
	ar >> GlyphName;
	// End of compatibility
	ar >> m_StartName;

	OnRotationChange();
}

// Load the document
//
void CTile::LoadVersion0_0001( CArchive& ar )
{
	ar >> m_CurrentRotation;
	ar >> m_PosX;
	ar >> m_PosY;
	ar >> m_PosZ;

	OnRotationChange();
}

// Draw more on each hex
//
void CTile::DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
}

// Draw more on the entire tile
//
void CTile::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
}

// Get the name of the tile
//
CString CTile::GetName()
{
	CString Name;

	int Type = (int) (m_Type/1000);

	switch( Type )
	{
	case TYPE_GRASS:
		Name.LoadString( IDS_GRASS );
		break;
	case TYPE_ICE:
		Name.LoadString( IDS_ICE );
		break;
	case TYPE_LAVA:
		Name.LoadString( IDS_LAVA );
		break;
	case TYPE_LAVAFIELD:
		Name.LoadString( IDS_LAVAFIELD );
		break;
	case TYPE_ROAD:
		Name.LoadString( IDS_ROAD );
		break;
	case TYPE_ROCK:
		Name.LoadString( IDS_ROCK );
		break;
	case TYPE_SAND:
		Name.LoadString( IDS_SAND );
		break;
	case TYPE_WATER:
		Name.LoadString( IDS_WATER );
		break;
	case TYPE_SWAMP:
		Name.LoadString( IDS_SWAMP );
		break;
	case TYPE_SWAMPWATER:
		Name.LoadString( IDS_SWAMPWATER );
		break;
	case TYPE_CONCRETE:
		Name.LoadString( IDS_CONCRETE );
		break;
	case TYPE_ASPHALT:
		Name.LoadString( IDS_ASPHALT );
		break;
	case TYPE_SNOW:
		Name.LoadString( IDS_SNOW );
		break;
	case TYPE_TREE:
		Name.LoadString( IDS_TREE );
		break;
	case TYPE_RUIN:
		Name.LoadString( IDS_RUIN );
		if( m_Type==TYPE_RUIN*1000+7 )
			Name.LoadString( IDS_RUINBREAKED );
		break;
	case TYPE_WALL:
		Name.LoadString( IDS_WALL );
		break;
	case TYPE_GLACIER:
		Name.LoadString( IDS_GLACIER );
		break;
	case TYPE_GLYPH:
		{
			CString Str;
			switch( m_Type%1000 )
			{
			case '?':
				Str.LoadString( IDS_UNKNOWN_GLYPH );
				break;
			case 'A':
				Str.LoadString( IDS_ASTRID_GLYPH );
				break;
			case 'G':
				Str.LoadString( IDS_GERDA_GLYPH );
				break;
			case 'I':
				Str.LoadString( IDS_IVOR_GLYPH );
				break;
			case 'V':
				Str.LoadString( IDS_VALDA_GLYPH );
				break;
			case 'D':
				Str.LoadString( IDS_DRAGMAR_GLYPH );
				break;
			case 'B':
				Str.LoadString( IDS_BRANDAR_GLYPH );
				break;
			case 'K':
				Str.LoadString( IDS_KELDA_GLYPH );
				break;
			case 'E':
				Str.LoadString( IDS_ERLAND_GLYPH );
				break;
			case 'M':
				Str.LoadString( IDS_MITONSOUL_GLYPH );
				break;
			case 'L':
				Str.LoadString( IDS_LODIN_GLYPH );
				break;
			case 'S':
				Str.LoadString( IDS_STURLA_GLYPH );
				break;
			case 'R':
				Str.LoadString( IDS_RANNVEIG_GLYPH );
				break;
			case 'J':
				Str.LoadString( IDS_JALGARD_GLYPH );
				break;
			case 'W':
				Str.LoadString( IDS_WANNOK_GLYPH );
				break;
			case 'P':
				Str.LoadString( IDS_PROFTAKA_GLYPH );
				break;
			case 'O':
				Str.LoadString( IDS_ORELD_GLYPH );
				break;
			case 'N':
				Str.LoadString( IDS_NILREND_GLYPH );
				break;
			case 'C':
				Str.LoadString( IDS_CREVCOR_GLYPH );
				break;
			case 'T':
				Str.LoadString( IDS_THORIAN_GLYPH );
				break;
			case 'U':
				Str.LoadString( IDS_ULANIVA_GLYPH );
				break;
			break;
			}
			return Str;
		}
	case TYPE_STARTAREA:
		return m_StartName;
		break;
	case TYPE_CASTLE:
		switch( m_Type-Type*1000 )
		{
		case 101:
			Name.LoadString( IDS_CASTLE_BASE_CORNER );
			return Name;
		case 102:
			Name.LoadString( IDS_CASTLE_BASE_STRAIGHT );
			return Name;
		case 103:
			Name.LoadString( IDS_CASTLE_BASE_END );
			return Name;
		case 201:
			Name.LoadString( IDS_CASTLE_WALL_CORNER );
			return Name;
		case 202:
			Name.LoadString( IDS_CASTLE_WALL_STRAIGHT );
			return Name;
		case 203:
			Name.LoadString( IDS_CASTLE_WALL_END );
			return Name;
		case 301:
			Name.LoadString( IDS_CASTLE_BATTLEMENT );
			return Name;
		case 401:
			Name.LoadString( IDS_CASTLE_DOOR );
			return Name;
		case 402:
			Name.LoadString( IDS_CASTLE_LADDER );
			return Name;
		case 403:
			Name.LoadString( IDS_CASTLE_FLAG );
			return Name;
		case 404:
			Name.LoadString( IDS_CASTLE_ARCH );
			return Name;
		default:
			Name.LoadString( IDS_CASTLE_WALL_WALK );
		}
		break;
	case TYPE_HIVE:
		Name.LoadString( IDS_HIVE );
		break;
	case TYPE_FIGURE:
		return m_FigureName;
		break;
	case TYPE_TICALLA:
		switch( m_Type-Type*1000 )
		{
		case 14:
		case 15:
		case 16:
			Name.LoadString( IDS_TICALLA_PALM );
			break;
		case 2:
			Name.LoadString( IDS_TICALLA_GRASS );
			break;
		}
		break;
	case TYPE_SHADOW:
		Name.LoadString( IDS_SHADOW );
		break;
	case TYPE_DUNGEON:
		Name.LoadString( IDS_DUNGEON );
		break;
	case TYPE_OUTCROP:
		Name.LoadString( IDS_OUTCROP );
		break;
	}

	CString Name2;
	Name2.Format( _T("%s %i"), Name, m_NbTile );

	return Name2;
}

// Render for 3D View
//
void CTile::Render( void* pView, bool ForShadow, bool BindTexture )
{
	Render1( pView, ForShadow, BindTexture );

	RenderWeapons();
}

// Render a tile 1 hexagon
//
void CTile::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	GLuint	TextureId = -1;
	GLuint	SideTextureId = -1;

	if( BindTexture )
	{
		if( m_TextureId==-1 )
		{
			int Type = (int) (m_Type/1000);

			switch( Type )
			{
			case TYPE_GRASS:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Grass.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("GroundSide.bmp"),255);
				break;
			case TYPE_ICE:
			case TYPE_GLACIER:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Ice.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("IceSide.bmp"),255);
				break;
			case TYPE_LAVA:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Lava.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("LavaSide.bmp"),255);
				break;
			case TYPE_LAVAFIELD:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("LavaField.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("LavaFieldSide.bmp"),255);
				break;
			case TYPE_ROAD:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Road.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("RoadSide.bmp"),255);
				break;
			case TYPE_ROCK:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Rock.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("GroundSide.bmp"),255);
				break;
			case TYPE_ASPHALT:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Asphalt.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("AsphaltSide.bmp"),255);
				break;
			case TYPE_RUIN:
			case TYPE_CONCRETE:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Concrete.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("RoadSide.bmp"),255);
				break;
			case TYPE_SAND:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Sand.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("GroundSide.bmp"),255);
				break;
			case TYPE_WATER:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Water.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("WaterSide.bmp"),255);
				break;
			case TYPE_SWAMPWATER:
			case TYPE_HIVE:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("SwampWater.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("SwampWaterSide.bmp"),255);
				break;
			case TYPE_SWAMP:
			case TYPE_TICALLA:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Swamp.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("SwampWaterSide.bmp"),255);
				break;
			case TYPE_SNOW:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Snow.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("SnowSide.bmp"),255);
				break;
			case TYPE_TREE:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Tree.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Tree.bmp"),255);
				break;
			case TYPE_GLYPH:
				{
					CString FileName;
					if( m_GlyphLetter=='?' )
					{
						FileName=_T("GlyphUnknown.bmp");
						TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(FileName,255);
					}
					else
					{
						FileName.Format( _T("Glyph%c.bmp"), m_GlyphLetter );
						TextureId = ((CHeroscapeEditor3DView*) pView)->GetGlyphTextureId(FileName);
					}
					SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("GlyphSide.bmp"),255);
				}
				break;
			case TYPE_CASTLE:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Castle.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("CastleSide.bmp"),255);
				break;
			case TYPE_PERSONAL:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetPersonalTextureId( m_PersonalTexture );
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetPersonalTextureId( m_PersonalTextureSide );
				break;
			case TYPE_SHADOW:
			case TYPE_OUTCROP:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Shadow.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("ShadowSide.bmp"),255);
				break;
			case TYPE_DUNGEON:
				TextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("Dungeon.bmp"),255);
				SideTextureId = ((CHeroscapeEditor3DView*) pView)->GetTextureId(_T("DungeonSide.bmp"),255);
				break;
			}
			m_TextureId = TextureId;
			m_TextureSideId = SideTextureId;
		}
		else
		{
			TextureId = m_TextureId;
			SideTextureId = m_TextureSideId;
		}
	}

	glMatrixMode( GL_MODELVIEW );
	for( int i=0; i<m_NbTile; i++ )
	{
		glPushMatrix();
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[i].y%2==0 )
				glTranslated( (m_PosX+m_TilePosition[i].x)*TILE3D_WIDTH+TILE3D_X3, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT, m_PosZ*TILE3D_ZHEIGHT );
			else
				glTranslated( (m_PosX+m_TilePosition[i].x+1)*TILE3D_WIDTH, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT, m_PosZ*TILE3D_ZHEIGHT );
		}
		else
		{
			if( m_TilePosition[i].y%2==1 )
				glTranslated( (m_PosX+m_TilePosition[i].x)*TILE3D_WIDTH+TILE3D_X3, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT, m_PosZ*TILE3D_ZHEIGHT );
			else
				glTranslated( (m_PosX+m_TilePosition[i].x)*TILE3D_WIDTH, -(m_PosY+m_TilePosition[i].y)*TILE3D_HEIGHT, m_PosZ*TILE3D_ZHEIGHT );
		}

		glScalef( 1, 1, (GLfloat) (m_TileHeight/TILE3D_ZHEIGHT) );
		if( m_PosY%2==1 && m_TilePosition[i].y%2==1 )
			glLoadName( (m_PosX+m_TilePosition[i].x+1)*1000000+(m_PosY+m_TilePosition[i].y)*1000+m_PosZ );
		else
			glLoadName( (m_PosX+m_TilePosition[i].x)*1000000+(m_PosY+m_TilePosition[i].y)*1000+m_PosZ );

		if( BindTexture && TextureId!=-1 )
			glBindTexture( GL_TEXTURE_2D, TextureId );
		glCallList( ((CHeroscapeEditor3DView*) pView)->m_TileUpDownGLList );
		if( BindTexture && SideTextureId!=-1  )
			glBindTexture( GL_TEXTURE_2D, SideTextureId );
		glCallList( ((CHeroscapeEditor3DView*) pView)->m_TileSideGLList );

		glPopMatrix();
	}
}

// Verify a tile
//
void CTile::Verify( void* pTheDoc )
{
	// Verify that something is under tile
	VerifySomethingUnderTile( pTheDoc );

	// Verify that there are not another tile at the same place
	VerifyOtherTileAtSamePlace( pTheDoc );
}

// Verify that something is under the tile
//
void CTile::VerifySomethingUnderTile( void* pTheDoc )
{
	if( m_PosZ==0 )
		return;

	CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) pTheDoc;

	int PosX, PosY;
	int NbTileUnder=0;
	for( int i=0; i<m_NbTile; i++ )
	{
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[i].y%2==1 )
			{
				PosX=m_TilePosition[i].x+m_PosX+1;
				PosY=m_TilePosition[i].y+m_PosY;
			}
			else
			{
				PosX=m_TilePosition[i].x+m_PosX;
				PosY=m_TilePosition[i].y+m_PosY;
			}
		}
		else
		{
			PosX=m_TilePosition[i].x+m_PosX;
			PosY=m_TilePosition[i].y+m_PosY;
		}
		if( pDoc->IsPositionUsed( PosX, PosY, m_PosZ-1 ) )
			NbTileUnder++;
	}

	if( NbTileUnder==0 )
	{
		CString Str;
		Str.LoadStringW( IDS_NOTHING_UNDER_TILE );
		pDoc->AddInformation( CHeroscapeEditorDoc::IB_WARNING, m_PosZ, GetName(), Str, m_PosX, m_PosY, m_PosZ );
	}
}

// Verify that there arn't another tile at the same place
//
void CTile::VerifyOtherTileAtSamePlace( void* pTheDoc )
{
	CHeroscapeEditorDoc* pDoc = (CHeroscapeEditorDoc*) pTheDoc;

	int PosX, PosY;
	for( int i=0; i<m_NbTile; i++ )
	{
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[i].y%2==1 )
			{
				PosX=m_TilePosition[i].x+m_PosX+1;
				PosY=m_TilePosition[i].y+m_PosY;
			}
			else
			{
				PosX=m_TilePosition[i].x+m_PosX;
				PosY=m_TilePosition[i].y+m_PosY;
			}
		}
		else
		{
			PosX=m_TilePosition[i].x+m_PosX;
			PosY=m_TilePosition[i].y+m_PosY;
		}

		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
			if( pTile!=this )
			{
				if( pTile->ContainPos( PosX, PosY ) && pTile->m_PosZ==m_PosZ )
				{
					int Type = m_Type/1000;
					int TileType = pTile->m_Type/1000;

					bool Error = true;

					if( (Type==TYPE_STARTAREA && TileType!=TYPE_STARTAREA) || (Type!=TYPE_STARTAREA && TileType==TYPE_STARTAREA) )
						Error=false;

					if( (m_Type==TYPE_CASTLE*1000+301 || m_Type==TYPE_CASTLE*1000+402) && (pTile->m_Type==TYPE_CASTLE*1000+301 || pTile->m_Type==TYPE_CASTLE*1000+402) && m_CurrentRotation!=pTile->m_CurrentRotation )
						Error=false;

					if( Error )
					{
						CString StrFormat;
						StrFormat.LoadStringW( IDS_OTHER_TILE_AT_SAME_PLACE );
						CString Str;
						Str.Format( StrFormat, pTile->GetName() );
						pDoc->AddInformation( CHeroscapeEditorDoc::IB_CRITICAL, m_PosZ, GetName(), Str, PosX, PosY, m_PosZ );
					}
				}
			}
		}
	}
}

// Load the necessary object
//
void CTile::LoadNecessaryObjects( void* pView )
{
}

// Get an exact copy of this tile (with placement and other)
//
CTile* CTile::GetExactCopy()
{
	CTile* pTile = GetCopy();
	pTile->FillCopy( this );
	pTile->Init();

	return pTile;
}

// Get an exact copy of the object
// Each sub class must copy special members
//
void CTile::FillCopy( CTile* pTile )
{
	m_CurrentRotation = pTile->m_CurrentRotation;
	m_FigureFile = pTile->m_FigureFile;
	m_FigureName = pTile->m_FigureName;
	m_GlyphLetter = pTile->m_GlyphLetter;
	m_Height = pTile->m_Height;
	m_IsSelected = pTile->m_IsSelected;
	m_PersonalTexture = pTile->m_PersonalTexture;
	m_PersonalTextureSide = pTile->m_PersonalTextureSide;
	m_PixelSizeX = pTile->m_PixelSizeX;
	m_PixelSizeY = pTile->m_PixelSizeY;
	m_PosX = pTile->m_PosX;
	m_PosY = pTile->m_PosY;
	m_PosZ = pTile->m_PosZ;
	m_StartName = pTile->m_StartName;
	m_TileColor = pTile->m_TileColor;
	m_TileHeight = pTile->m_TileHeight;
	m_Type = pTile->m_Type;
}

// Begin to define the targets points
//
void CTile::BeginTargetPoint( double BeginX, double BeginY, double BeginZ)
{
	FreeAllTargets();

	m_AttackSource.x = BeginX;
	m_AttackSource.y = BeginY;
	m_AttackSource.z = BeginZ;

	if( m_PosY%2==1 )
	{
		m_AttackSource.x = (m_PosX+1)*TILE3D_WIDTH-TILE3D_X3;
		m_AttackSource.y = -(m_PosY)*TILE3D_HEIGHT;
		m_AttackSource.z = m_PosZ*TILE3D_ZHEIGHT;
	}
	else
	{
		m_AttackSource.x = (m_PosX)*TILE3D_WIDTH;
		m_AttackSource.y = -(m_PosY)*TILE3D_HEIGHT;
		m_AttackSource.z = m_PosZ*TILE3D_ZHEIGHT;
	}
}

// Add a target point
//
void CTile::AddTargetPoint( double TargetX, double TargetY, double TargetZ)
{
	// Create a new target object
	Target* pNewTarget = (Target*) malloc( sizeof(Target) );

	pNewTarget->TargetPoint.x = TargetX;
	pNewTarget->TargetPoint.y = TargetY;
	pNewTarget->TargetPoint.z = TargetZ;

	// read the current time
	LARGE_INTEGER	CurrentTimer;
	QueryPerformanceCounter( &CurrentTimer );

	pNewTarget->LaunchTime = CurrentTimer.QuadPart;

	pNewTarget->CurrentPosition.x = TargetX;
	pNewTarget->CurrentPosition.y = TargetY;
	pNewTarget->CurrentPosition.z = TargetZ;

	// Set a random weapon speed
	LARGE_INTEGER	Ret;
	QueryPerformanceFrequency( &Ret );
	__int64 frequency = Ret.QuadPart;

	pNewTarget->Speed = (__int64) (((((double) rand())/RAND_MAX)*0+2)*frequency);
	pNewTarget->Speed2 = (__int64) (((((double) rand())/RAND_MAX)*0+1)*frequency);

	// Add the target to the list
	m_TargetList.Add(pNewTarget);
}

// Compute the new position of all the weapon
//
bool CTile::ComputeWeapons()
{
	if( m_TargetList.IsEmpty() )
		return false;

	LARGE_INTEGER	CurrentTimer;
	QueryPerformanceCounter( &CurrentTimer );

	for( int i=0; i<m_TargetList.GetCount(); i++ )
	{
		Target* pTarget = (Target*) m_TargetList.GetAt(i);

		pTarget->CurrentTime = CurrentTimer.QuadPart;
		if( CurrentTimer.QuadPart-pTarget->LaunchTime>pTarget->Speed )
		{
			if( CurrentTimer.QuadPart-pTarget->LaunchTime>pTarget->Speed+pTarget->Speed2 )
			{
				// The weapon is dead because he is at the target
				free( pTarget );
				m_TargetList.RemoveAt(i);
				i--;
			}
		}
		else
		{
			double MaxZ = max(m_AttackSource.z+5,pTarget->TargetPoint.z+5);
			pTarget->CurrentPosition.x = m_AttackSource.x+(pTarget->TargetPoint.x-m_AttackSource.x)*(CurrentTimer.QuadPart-pTarget->LaunchTime)/((double) pTarget->Speed);
			pTarget->CurrentPosition.y = m_AttackSource.y+(pTarget->TargetPoint.y-m_AttackSource.y)*(CurrentTimer.QuadPart-pTarget->LaunchTime)/((double) pTarget->Speed);
			if( CurrentTimer.QuadPart-pTarget->LaunchTime<pTarget->Speed/2 )
				pTarget->CurrentPosition.z = m_AttackSource.z+sin((CurrentTimer.QuadPart-pTarget->LaunchTime)/((double) pTarget->Speed)*PI)*(MaxZ-m_AttackSource.z);
			else
				pTarget->CurrentPosition.z = pTarget->TargetPoint.z+sin((CurrentTimer.QuadPart-pTarget->LaunchTime)/((double) pTarget->Speed)*PI)*(MaxZ-pTarget->TargetPoint.z);
		}
	}

	return true;
}

// End to define the targets points
//
void CTile::EndTargetPoint()
{
}

// Free memory used by  all target
//
void CTile::FreeAllTargets()
{
	for( int i=0; i<m_TargetList.GetCount(); i++ )
	{
		Target* pTarget = (Target*) m_TargetList.GetAt(i);
		free( pTarget );
	}
	m_TargetList.RemoveAll();
}

// Render the weapon if necessary
//
void CTile::RenderWeapons()
{
	if( m_TargetList.IsEmpty() )
		return;

	for( int i=0; i<m_TargetList.GetCount(); i++ )
	{
		Target* pTarget = (Target*) m_TargetList.GetAt(i);

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();

		if( pTarget->CurrentTime<pTarget->LaunchTime+pTarget->Speed )
		{
			glTranslated( pTarget->CurrentPosition.x, pTarget->CurrentPosition.y, pTarget->CurrentPosition.z );

			glScalef( 1, 1, 1 );

			GLUquadricObj* pquadric = gluNewQuadric();
			gluSphere( pquadric, 0.1, 10, 8 );
			gluDeleteQuadric( pquadric );
		}
		else
		{
			// Explosion time
			for( int j=0; j<20; j++ )
			{
				double x, y, z;
				x = cos( j/20.0*PI*2 )*(((double) (pTarget->CurrentTime-pTarget->LaunchTime-pTarget->Speed))/pTarget->Speed2)*0.3;
				y = sin( j/20.0*PI*2 )*(((double) (pTarget->CurrentTime-pTarget->LaunchTime-pTarget->Speed))/pTarget->Speed2)*0.3;
				z = sin( ((double) (pTarget->CurrentTime-pTarget->LaunchTime-pTarget->Speed))/pTarget->Speed2*PI )*1;
				glPopMatrix();
				glPushMatrix();
				glTranslated( pTarget->TargetPoint.x+x, pTarget->TargetPoint.y+y, pTarget->TargetPoint.z+z );

				glScalef( 1, 1, 1 );

				GLUquadricObj* pquadric = gluNewQuadric();
				gluSphere( pquadric, 0.05, 5, 3 );
				gluDeleteQuadric( pquadric );
			}
		}
		glPopMatrix();
	}
}

// To know if this tile is available for a game
//
bool CTile::IsGameAvailable()
{
	return true;
}

// Send the tile by socket
//
void CTile::SendBySocket( CServerSocket* pSocket )
{
	pSocket->WriteType( m_CurrentRotation );
	pSocket->WriteType( m_Height );
	pSocket->WriteType( m_NbTile );
	pSocket->WriteType( m_PersonalTexture );
	pSocket->WriteType( m_PersonalTextureSide );
	pSocket->WriteType( m_PosX );
	pSocket->WriteType( m_PosY );
	pSocket->WriteType( m_PosZ );
	pSocket->WriteType( m_TileHeight );
	pSocket->WriteType( m_GlyphLetter );
	pSocket->WriteType( m_StartName );
	short r,g,b;
	r=GetRValue(m_TileColor);
	g=GetGValue(m_TileColor);
	b=GetBValue(m_TileColor);
	pSocket->WriteType( r );
	pSocket->WriteType( g );
	pSocket->WriteType( b );
}

// Receive the tile by socket
//
void CTile::ReceiveBySocket( CClientSocket* pSocket )
{
	pSocket->ReadType( m_CurrentRotation );
	pSocket->ReadType( m_Height );
	pSocket->ReadType( m_NbTile );
	pSocket->ReadType( m_PersonalTexture );
	pSocket->ReadType( m_PersonalTextureSide );
	pSocket->ReadType( m_PosX );
	pSocket->ReadType( m_PosY );
	pSocket->ReadType( m_PosZ );
	pSocket->ReadType( m_TileHeight );
	pSocket->ReadType( m_GlyphLetter );
	pSocket->ReadType( m_StartName );
	short r,g,b;
	pSocket->ReadType( r );
	pSocket->ReadType( g );
	pSocket->ReadType( b );
	m_TileColor = RGB(r,g,b);
}

// Reset the texture id
//
void CTile::ResetTextureId()
{
	m_TextureId = -1;
	m_TextureSideId = -1;
}

// Set the selected state
//
void CTile::SetSelectedState( bool State )
{
	m_IsSelected = State;
}

// Generate smoke for an explode tile
//
void CTile::GenerateSmokeForExplode()
{
}

// delete smoke objects
//
void CTile::DeleteSmokeObjects()
{
}

// delete smoke for dice
//
void CTile::DeleteSmokeDice()
{
}

// Render explode if necessary
//
void CTile::RenderExplode( void* pView, bool BindTexture )
{
}

