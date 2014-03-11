// TileFigure2.cpp : implementation file
//

#include "StdAfx.h"

#include <math.h>

#include "HeroscapeEditor.h"
#include "HeroscapeEditor3DView.h"
#include "Object3D.h"
#include "Smoke.h"
#include "StaticGraphicalLib.h"
#include "TileFigure2.h"

// The constructor
//
CTileFigure2::CTileFigure2()
{
	m_NbTile = 2;
	m_Type = TYPE_FIGURE*1000+m_NbTile;
	m_TileColor = RGB(255,255,255);
	int CurrentPos = 0;

	for( int i=0; i<100; i++ )
		m_SmokeDiceList[i] = NULL;

	Init();
}

// The destructor
//
CTileFigure2::~CTileFigure2()
{
	// Remove smoke if there exist
	DeleteSmokeObjects();

	DeleteSmokeDice();
}

// Delete smoke dice
//
void CTileFigure2::DeleteSmokeDice()
{
	for( int i=0; i<100; i++ )
		if( m_SmokeDiceList[i]!=NULL )
		{
			for( int j=0; j<m_SmokeList.GetCount(); )
			{
				delete (CSmoke*) m_SmokeDiceList[i]->GetAt(j);
				m_SmokeDiceList[i]->RemoveAt(0);
			}

			delete (CPtrArray*) m_SmokeDiceList[i];
			m_SmokeDiceList[i] = NULL;
		}
}

// Get a copy of this tile
//
CTile* CTileFigure2::GetCopy()
{
	CTileFigure2* pTile = new CTileFigure2;

	pTile->m_FigureName = m_FigureName;
	pTile->m_FigureFile = m_FigureFile;

	return pTile;
}

// Get the name of the tile
//
CString CTileFigure2::GetName()
{
	return m_FigureName;
}

// Render the tile
//
void CTileFigure2::Render1( void* pView, bool ForShadow, bool BindTexture )
{
	if( m_ExplodeTime>0.5 && m_ExplodeTime<1 )
		return;

	if( !m_ToDisplay )
		return;

	double TileExplode = 1.00;

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
	case 1:
	case 2:
		break;
	case 3:
		glTranslated( TILE3D_WIDTH, 0, 0 );
		break;
	case 4:
		glTranslated( TILE3D_WIDTH/2.0, -TILE3D_HEIGHT, 0 );
		break;
	case 5:
		glTranslated( -TILE3D_WIDTH/2.0, -TILE3D_HEIGHT, 0 );
		break;
	}

	glRotated( -m_CurrentRotation*60, 0, 0, 1 );

	glLoadName( m_PosX*1000000+m_PosY*1000+m_PosZ );

	CObject3D* pObject3D = ((CHeroscapeEditor3DView*) pView)->GetFigureObject( m_FigureFile );
	if( pObject3D!=NULL )
	{
		// Display in creation mode
		if( m_CreationTime>=0 && m_CreationTime<0.7 )
		{
			glLoadName( 999999999 );
			DeleteSmokeDice();
			double Size = min(1,fabs(sin(m_CreationTime/0.5*PI*8.5)));
			if( m_CreationTime>0.5 )
				pObject3D->RenderAsExplodedPoint( 1 );
			else
				pObject3D->RenderAsExplodedPoint( Size );
		}
		// Display in normal mode
		else
			pObject3D->Render( BindTexture );

		// Display the selected mode
		if( m_IsSelected && theApp.m_IsInGameMode )
			pObject3D->RenderSelected();
	}

	if( m_IsAttackFigure )
	{
		if( BindTexture )
			glBindTexture( GL_TEXTURE_2D, ((CHeroscapeEditor3DView*) pView)->m_TextureIdAttack );
		glTranslated( 0, 0, pObject3D->m_Height+0.4 );
		if( m_DiceNumber==0 )
		{
			glScaled( 0.2, 0.2, 0.2 );
			CStaticGraphicalLib::DrawCube();
		}
		else
		{
			for( int i=0; i<m_DiceNumber; i++ )
			{
				if( m_AttackTime==-1 || (m_DiceNumber-i)*m_AttackTimeOnDice+0.2>m_AttackTime || (m_DiceNumber-i)*m_AttackTimeOnDice+0.2>0.7 )
				{
					glPushMatrix();
					glTranslated( 0, 0, i*0.5 );
					glScaled( 0.4, 0.4, 0.4 );
					CStaticGraphicalLib::DrawCube();
					glTranslated( 0, 0, 0.4 );
					glPopMatrix();
				}
			}
		}
	}

	if( m_IsDefenseFigure )
	{
		if( BindTexture )
			glBindTexture( GL_TEXTURE_2D, ((CHeroscapeEditor3DView*) pView)->m_TextureIdDefense );
		glTranslated( 0, 0, pObject3D->m_Height+0.4 );
		if( m_DiceNumber==0 )
		{
			glScaled( 0.2, 0.2, 0.2 );
			CStaticGraphicalLib::DrawCube();
		}
		else
		{
			for( int i=0; i<m_DiceNumber; i++ )
			{
				if( m_AttackTime==-1 || (m_DiceNumber-i)*m_AttackTimeOnDice+0.2>m_AttackTime || (m_DiceNumber-i)*m_AttackTimeOnDice+0.2>0.7 )
				{
					glPushMatrix();
					glTranslated( 0, 0, i*0.5 );
					glScaled( 0.4, 0.4, 0.4 );
					CStaticGraphicalLib::DrawCube();
					glTranslated( 0, 0, 0.4 );
					glPopMatrix();
				}
			}
		}
	}

	glPopMatrix();
}

// When the rotation change
//
void CTileFigure2::OnRotationChange()
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
}

// Draw more on a tile
//
void CTileFigure2::DrawExtendTile( CDC* pDC, int x, int y, int x2, int x3, int y2, int y3, int y4, int DrawingLevel)
{
	double LowColor = GetLowColor( DrawingLevel );

	CPen Pen;
	Pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject( &Pen );

	double cosa;
	double sina;
	switch( m_CurrentRotation )
	{
	case 0:
		cosa = 1;
		sina = 0;
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

	CPen Pen1;
	Pen1.CreatePen(PS_SOLID,0,RGB(0,0,0));
	pDC->SelectObject( &Pen1 );

	pDC->MoveTo( x+x2, y+(y3-y2)/2 );
	int xDest = (int) (x+x2+cosa*x2*(-1)-sina*0);
	int yDest = (int) (y+(y3-y2)/2.0+sina*x2*(-1)+cosa*0);
	pDC->LineTo( xDest, yDest );

	pDC->SelectObject( pOldPen );
}

// Load the necessary object
//
void CTileFigure2::LoadNecessaryObjects( void* pView )
{
	((CHeroscapeEditor3DView*) pView)->GetFigureObject( m_FigureFile );
}

// To know if this tile is available for a game
//
bool CTileFigure2::IsGameAvailable()
{
	return false;
}

// Generate smoke for an explode figure
//
void CTileFigure2::GenerateSmokeForExplode( CHeroscapeEditor3DView* pView )
{
	int SmokeNumber = 0;

	DeleteSmokeObjects();

	CObject3D* pObject3D = ((CHeroscapeEditor3DView*) pView)->GetFigureObject( m_FigureFile );
	if( pObject3D!=NULL )
		SmokeNumber = (int) (pObject3D->m_Width*pObject3D->m_Height*5);

	if( SmokeNumber<10 )
		SmokeNumber = 10;

	TRACE( _T("Nombre de fumée : %i\n"), SmokeNumber );

	for( int i=0; i<SmokeNumber; i++ )
	{
		double PositionX, PositionY, PositionZ;
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[0].y%2==0 )
			{
				PositionX = (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH+TILE3D_X3;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
			else
			{
				PositionX = (m_PosX+m_TilePosition[0].x+1)*TILE3D_WIDTH;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
		}
		else
		{
			if( m_TilePosition[0].y%2==1 )
			{
				PositionX = (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH+TILE3D_X3;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
			else
			{
				PositionX = (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
		}

		if( pObject3D!=NULL )
		{
			PositionX += (((double) rand())/RAND_MAX)*pObject3D->m_Width+pObject3D->m_XMin;
			PositionY += (((double) rand())/RAND_MAX)*pObject3D->m_Depth+pObject3D->m_YMin;
			PositionZ += (((double) rand())/RAND_MAX)*pObject3D->m_Height+pObject3D->m_ZMin;
		}

		CSmoke* pSmoke = new CSmoke( PositionX, PositionY, PositionZ, CSmoke::SC_BLACK, pView );
		m_SmokeList.Add( pSmoke );
	}
}

// Delete smoke object
//
void CTileFigure2::DeleteSmokeObjects()
{
	for( int i=0; i<m_SmokeList.GetCount(); )
	{
		delete (CSmoke*) m_SmokeList.GetAt(i);
		m_SmokeList.RemoveAt(0);
	}
	m_ExplodeTime=0;
}

// Render explode
//
void CTileFigure2::RenderExplode( void* pView, bool BindTexture )
{
	if( m_ExplodeTime>0.5 && m_ExplodeTime<1 )
	{
		if( m_SmokeList.GetCount()==0 )
			GenerateSmokeForExplode( (CHeroscapeEditor3DView*) pView );

		for( int i=0; i<m_SmokeList.GetCount(); i++ )
		{
			CSmoke* pSmoke = (CSmoke*) m_SmokeList.GetAt(i);
			pSmoke->Render( (int) ((m_ExplodeTime-0.5)*2000), (CHeroscapeEditor3DView*) pView, BindTexture );
		}
	}

	// Render explode dice
	for( int i=0; i<m_DiceNumber; i++ )
	{
		if( m_AttackTime==-1 || (m_DiceNumber-i)*m_AttackTimeOnDice+0.2>m_AttackTime || (m_DiceNumber-i)*m_AttackTimeOnDice+0.2>0.7 )
		{
		}
		else
		{
			// Smoke
			if( m_SmokeDiceList[i]==NULL )
			{
				m_SmokeDiceList[i] = new CPtrArray();

				GenerateSmokeForDice( (CHeroscapeEditor3DView*) pView, i );
			}

			RenderExplodeDice( pView, BindTexture, i, (m_AttackTime-(m_DiceNumber-i)*m_AttackTimeOnDice-0.2)/m_AttackTimeOnDice );
		}
	}
}

// Generate smoke for an explode dice
//
void CTileFigure2::GenerateSmokeForDice( CHeroscapeEditor3DView* pView, int DiceIndex )
{
	int SmokeNumber = 10;

	for( int i=0; i<SmokeNumber; i++ )
	{
		double PositionX, PositionY, PositionZ;
		if( m_PosY%2==1 )
		{
			if( m_TilePosition[0].y%2==0 )
			{
				PositionX = (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH+TILE3D_X3;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
			else
			{
				PositionX = (m_PosX+m_TilePosition[0].x+1)*TILE3D_WIDTH;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
		}
		else
		{
			if( m_TilePosition[0].y%2==1 )
			{
				PositionX = (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH+TILE3D_X3;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
			else
			{
				PositionX = (m_PosX+m_TilePosition[0].x)*TILE3D_WIDTH;
				PositionY = -(m_PosY+m_TilePosition[0].y)*TILE3D_HEIGHT;
				PositionZ = m_PosZ*TILE3D_ZHEIGHT;
			}
		}

		CObject3D* pObject3D = ((CHeroscapeEditor3DView*) pView)->GetFigureObject( m_FigureFile );
		PositionX += (((double) rand())/RAND_MAX)*1-.5;
		PositionY += (((double) rand())/RAND_MAX)*1-.5;
		PositionZ += (((double) rand())/RAND_MAX)*1-.5 + pObject3D->m_Height+0.4 + DiceIndex*.5;

		CSmoke* pSmoke;
		if( m_IsAttackFigure )
			pSmoke = new CSmoke( PositionX, PositionY, PositionZ, CSmoke::SC_RED, pView );
		else
			pSmoke = new CSmoke( PositionX, PositionY, PositionZ, CSmoke::SC_BLUE, pView );

		((CPtrArray*) m_SmokeDiceList[DiceIndex])->Add( pSmoke );
	}
}

// Render explode dice
//
void CTileFigure2::RenderExplodeDice( void* pView, bool BindTexture, int DiceIndex, double Time )
{
	if( Time>1 )
		return;

	for( int i=0; i<m_SmokeDiceList[DiceIndex]->GetCount(); i++ )
	{
		CSmoke* pSmoke = (CSmoke*) m_SmokeDiceList[DiceIndex]->GetAt(i);
		pSmoke->Render( (int) (Time*1000), (CHeroscapeEditor3DView*) pView, BindTexture );
	}
}