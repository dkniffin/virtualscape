// TileCastleBaseStraight.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "TileCastleBaseStraight.h"
#include "HeroscapeEditor3DView.h"

// The constructor
//
CTileCastleBaseStraight::CTileCastleBaseStraight()
{
	m_NbTile = 1;
	m_TileHeight = TILE3D_ZHEIGHT2;
	m_Type = TYPE_CASTLE*1000+102;
	m_TileColor = RGB(220,220,220);
	m_TileColor2 = RGB(50,50,50);
	int CurrentPos = 0;
	m_TilePosition[CurrentPos].x = 0;
	m_TilePosition[CurrentPos++].y = 0;

	Init();
}

// The destructor
//
CTileCastleBaseStraight::~CTileCastleBaseStraight()
{
}

// Get a copy of this tile
//
CTile* CTileCastleBaseStraight::GetCopy()
{
	return new CTileCastleBaseStraight;
}

// Draw the tiles
//
void CTileCastleBaseStraight::Draw( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
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

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor)+(255-GetRValue(m_TileColor))*LowColor),min(255,GetGValue(m_TileColor)+(255-GetGValue(m_TileColor))*LowColor),min(255,GetBValue(m_TileColor)+(255-GetBValue(m_TileColor))*LowColor)) );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	pDC->Polygon( Points, NbPoint-1 );

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

	DrawSurround( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
	DrawExtend( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
}

// Draw the tiles
//
void CTileCastleBaseStraight::DrawSurround( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	// Compute polyline around tiles
	POINT	Points1[7];
	POINT	Points2[7];
	int		NbPoint1 = 7;
	int		NbPoint2 = 7;
	int		TilePos = 0;

	double LowColor = GetLowColor( DrawingLevel );

	if( x2<15 )
	{
		NbPoint1=3;
		NbPoint2=3;
	}

	Points1[0].x=x;
	Points1[0].y=y+1;
	Points1[1].x=x+x2;
	Points1[1].y=y-y2;
	Points1[2].x=x+x3;
	Points1[2].y=y+1;
	Points1[3].x=(int) (x+x2+x2/2.0);
	Points1[3].y=y;
	Points1[4].x=(int) (x+x2+x2/2.0);
	Points1[4].y=(int) (y-y2*0.3);
	Points1[5].x=(int) (x+x2/2.0);
	Points1[5].y=(int) (y-y2*0.3);
	Points1[6].x=(int) (x+x2/2.0);
	Points1[6].y=y;

	Points2[0].x=x;
	Points2[0].y=y+y3-y2;
	Points2[1].x=x+x2;
	Points2[1].y=y+y3;
	Points2[2].x=x+x3;
	Points2[2].y=y+y3-y2;
	Points2[3].x=(int) (x+x2+x2/2.0);
	Points2[3].y=y+y3-y2;
	Points2[4].x=(int) (x+x2+x2/2.0);
	Points2[4].y=(int) (y+y3-y2+y2*0.3);
	Points2[5].x=(int) (x+x2/2.0);
	Points2[5].y=(int) (y+y3-y2+y2*0.3);
	Points2[6].x=(int) (x+x2/2.0);
	Points2[6].y=y+y3-y2;

	double cosa;
	double sina;
	switch( m_CurrentRotation )
	{
	case 0:
		break;
	case 1:
		cosa = cos(60/180.0*PI);
		sina = sin(60/180.0*PI);
		break;
	case 2:
		cosa = cos(120/180.0*PI);
		sina = sin(120/180.0*PI);
		break;
	case 3:
		cosa = cos(180/180.0*PI);
		sina = sin(180/180.0*PI);
		break;
	case 4:
		cosa = cos(240/180.0*PI);
		sina = sin(240/180.0*PI);
		break;
	case 5:
		cosa = cos(300/180.0*PI);
		sina = sin(300/180.0*PI);
		break;
	}

	if( m_CurrentRotation!=0 )
	{
		for( int i=0; i<NbPoint1; i++ )
		{
			int x1,y1;

			x1 = (int) (cosa*(Points1[i].x-x-x2)-sina*(Points1[i].y-y-(y3-y2)/2));
			y1 = (int) (sina*(Points1[i].x-x-x2)+cosa*(Points1[i].y-y-(y3-y2)/2));
			Points1[i].x = x+x2+x1;
			Points1[i].y = y+(y3-y2)/2+y1;
		}
		for( int i=0; i<NbPoint2; i++ )
		{
			int x1,y1;

			x1 = (int) (cosa*(Points2[i].x-x-x2)-sina*(Points2[i].y-y-(y3-y2)/2));
			y1 = (int) (sina*(Points2[i].x-x-x2)+cosa*(Points2[i].y-y-(y3-y2)/2));
			Points2[i].x = x+x2+x1;
			Points2[i].y = y+(y3-y2)/2+y1;
		}
	}

	CPen Pen;
	Pen.CreatePen(PS_NULL,0,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	CBrush Brush;
	if( m_IsSelected )
		Brush.CreateSolidBrush( RGB(255,255*LowColor,255*LowColor) );
	else
		Brush.CreateSolidBrush( RGB(min(255,GetRValue(m_TileColor2)+(255-GetRValue(m_TileColor2))*LowColor),min(255,GetGValue(m_TileColor2)+(255-GetGValue(m_TileColor2))*LowColor),min(255,GetBValue(m_TileColor2)+(255-GetBValue(m_TileColor2))*LowColor)) );
	CBrush* pOldBrush = pDC->SelectObject( &Brush );

	pDC->Polygon( Points1, NbPoint1 );
	pDC->Polygon( Points2, NbPoint2 );

	pDC->SelectObject( pOldBrush );
	pDC->SelectObject( pOldPen );

	DrawExtend( pDC, x, y, x2, x3, y2, y3, y4, DrawingLevel);
}

// Draw more on a tile
//
void CTileCastleBaseStraight::DrawExtend( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	CFont Font;
	Font.CreateFont( (int) (y3), (int) (x3/2.5), 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, FF_DONTCARE, _T("Arial") );

	CFont* pOldFont = pDC->SelectObject( &Font );

	double LowColor = GetLowColor( DrawingLevel );

	pDC->SetTextColor( RGB(min(255,255*LowColor),min(255,255*LowColor),min(255,255*LowColor)) );
	pDC->SetBkMode( TRANSPARENT );

	int CenterX = x+x2;
	int CenterY = y+(y3-y2)/2;

	pDC->DrawText( _T("B"), CRect(CenterX-x3,CenterY-x3,CenterX+x3,CenterY+x3), DT_CENTER | DT_VCENTER | DT_SINGLELINE );

	pDC->SelectObject( pOldFont );
}

// Render a tile 1 hexagon
//
void CTileCastleBaseStraight::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	double TileExplode = 1.00;

	// Call the base class
	//CTile::Render1( pView, ForShadow, BindTexture );

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
	((CHeroscapeEditor3DView*) pView)->m_pCastleBaseStraight->Render( BindTexture );

	glPopMatrix();
}

// Fill the members with members of an other tile
//
void CTileCastleBaseStraight::FillCopy( CTile* pTile )
{
	CTile::FillCopy( pTile );
	m_TileColor2 = ((CTileCastleBaseStraight*) pTile)->m_TileColor2;
}
