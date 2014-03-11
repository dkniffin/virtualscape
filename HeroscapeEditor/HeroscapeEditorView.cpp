// HeroscapeEditorView.cpp : implémentation de la classe CHeroscapeEditorView
//

#include "StdAfx.h"

#include <Math.h>

#include "ChooseLevelDlg.h"
#include "HeroscapeEditor.h"
#include "HeroscapeEditorDoc.h"
#include "HeroscapeEditorView.h"
#include "MainFrm.h"
#include "TileFigure.h"
#include "TileNumber.h"
#include "TilePerso.h"
#include "ZoomValueDlg.h"

// CHeroscapeEditorView

IMPLEMENT_DYNCREATE(CHeroscapeEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CHeroscapeEditorView, CScrollView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_MYPRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ZOOMIN, &CHeroscapeEditorView::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &CHeroscapeEditorView::OnZoomout)
	ON_COMMAND(ID_ZOOMVALUE, &CHeroscapeEditorView::OnZoomValue)
	ON_COMMAND(ID_FULLVIEW, &CHeroscapeEditorView::OnFullview)
	ON_COMMAND(ID_LEVELUP, &CHeroscapeEditorView::OnLevelup)
	ON_COMMAND(ID_LEVELDOWN, &CHeroscapeEditorView::OnLeveldown)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_UPDATE_COMMAND_UI(ID_LEVELDOWN, &CHeroscapeEditorView::OnUpdateLeveldown)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_ROTATE_LEFT, &CHeroscapeEditorView::OnEditRotateLeft)
	ON_COMMAND(ID_EDIT_ROTATE_RIGHT, &CHeroscapeEditorView::OnEditRotateRight)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATE_LEFT, &CHeroscapeEditorView::OnUpdateEditRotateLeft)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATE_RIGHT, &CHeroscapeEditorView::OnUpdateEditRotateRight)
	ON_COMMAND(ID_EDIT_REMOVE, &CHeroscapeEditorView::OnEditRemove)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REMOVE, &CHeroscapeEditorView::OnUpdateEditRemove)
	ON_COMMAND(ID_SELECT_ALL, &CHeroscapeEditorView::OnSelectAll)
	ON_COMMAND(ID_SELECT_NOTHING, &CHeroscapeEditorView::OnSelectNothing)
	ON_COMMAND(ID_SELECT_INVERSE, &CHeroscapeEditorView::OnSelectInverse)
	ON_COMMAND(ID_SELECT_LEVELUP, &CHeroscapeEditorView::OnSelectLevelup)
	ON_COMMAND(ID_SELECT_LEVELDOWN, &CHeroscapeEditorView::OnSelectLeveldown)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_REVERSE, &CHeroscapeEditorView::OnUpdateOutilsReverse)
	ON_COMMAND(ID_OUTILS_REVERSE, &CHeroscapeEditorView::OnOutilsReverse)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SELECT_LEVEL, &CHeroscapeEditorView::OnSelectLevel)
	ON_UPDATE_COMMAND_UI(ID_SELECT_LEVELUP, &CHeroscapeEditorView::OnUpdateSelectLevelup)
	ON_UPDATE_COMMAND_UI(ID_SELECT_LEVELDOWN, &CHeroscapeEditorView::OnUpdateSelectLeveldown)
	ON_COMMAND(ID_OUTILS_NUMBER, &CHeroscapeEditorView::OnOutilsNumber)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_NUMBER, &CHeroscapeEditorView::OnUpdateOutilsNumber)
	ON_COMMAND(ID_FICHIER_APERCUNUM, &CHeroscapeEditorView::OnFichierApercunum)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHeroscapeEditorView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, &CHeroscapeEditorView::OnFilePrint)
	ON_COMMAND(ID_FICHIER_IMPRIMERNUM, &CHeroscapeEditorView::OnFichierImprimernum)
	ON_COMMAND(ID_OUTILS_REMOVELEVEL, &CHeroscapeEditorView::OnOutilsRemovelevel)
	ON_COMMAND(ID_OUTILS_INSERTLEVEL, &CHeroscapeEditorView::OnOutilsInsertlevel)
	ON_COMMAND(ID_OUTILS_GO_LEVEL, &CHeroscapeEditorView::OnOutilsGoLevel)
	ON_COMMAND(ID_SELECT_SAME_TILE_SAME_LEVEL, &CHeroscapeEditorView::OnSelectSameTileSameLevel)
END_MESSAGE_MAP()

// The constructor
//
CHeroscapeEditorView::CHeroscapeEditorView()
{
	// No Zoom
	m_ZoomLevel = 1.5;
	// Low z level
	m_CurrentZLevel = 0;
	// no bitmap now
	m_pBitmapMemory = NULL;
	m_pBitmapMemory2 = NULL;
	m_pBitmapMemoryUnderCurrentLevel = NULL;
	// No mode now
	m_Mode = MODE_NULL;
	// no offset now
	m_SelectedTileOffset.x = m_SelectedTileOffset.y = 0;
	m_ScrollPosX = m_ScrollPosY = 0;
	// onion skin mode
	m_OnionSkinMode = false;
	// No display number
	m_DisplayNumber = false;
	// To move with key
	m_LastMoveVertical = 0;
	// Default print
	m_PrintState = PS_DEFAULT;
}

// The destructor
//
CHeroscapeEditorView::~CHeroscapeEditorView()
{
	if( m_pBitmapMemory )
		delete m_pBitmapMemory;

	if( m_pBitmapMemory2 )
		delete m_pBitmapMemory2;
}

// Before the window is created
//
BOOL CHeroscapeEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// draw the window
//
void CHeroscapeEditorView::OnDraw(CDC* pDC)
{
	CHeroscapeEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	RECT Rect;
	GetClientRect( &Rect );

	// Create the memory DC
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap2 = dcMemory.SelectObject( m_pBitmapMemory );

	pDC->BitBlt( GetScrollPos( SB_HORZ ), GetScrollPos( SB_VERT ), Rect.right, Rect.bottom, &dcMemory, 0, 0, SRCCOPY );

	dcMemory.SelectObject( pOldBitmap2 );
}

// Prepare the printing job
//
BOOL CHeroscapeEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if( m_PrintState==PS_NUM )
		pInfo->m_nNumPreviewPages = 1;
	else
		pInfo->m_nNumPreviewPages = 2;

	if( !GetDocument()->OnPreparePrinting( pInfo ) )
		return FALSE;

	// préparation par défaut
	return DoPreparePrinting(pInfo);
}

// Begin printing job
//
void CHeroscapeEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	GetDocument()->OnBeginPrinting( pDC, pInfo );
}

// End printing job
//
void CHeroscapeEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO : ajoutez un nettoyage après l'impression
}

// The window is created
//
int CHeroscapeEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetScrollSizes( MM_TEXT, CSize(10000,10000) );
	ShowScrollBar( SB_BOTH );
	RecomputeScrollSize();
	EnableToolTips();

	return 0;
}

// the user use mouse wheel for zoom or unzoom
//
BOOL CHeroscapeEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// Call the base class
	//SetRedraw( FALSE );
	//BOOL Ret = CScrollView::OnMouseWheel(nFlags, zDelta, pt);
	//SetRedraw( TRUE );

	if( zDelta>0 )
		OnEditRotateLeft();
	else
		OnEditRotateRight();

	return TRUE;
}

// Recompute the scroll size
//
void CHeroscapeEditorView::RecomputeScrollSize()
{
	int SizeX = BOARD_MAX_TILE_X * 2 *((int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE)) + 1;
	int SizeY = (int) (BOARD_MAX_TILE_Y * (int) (((int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE)) + m_ZoomLevel*TILE_ORIGINAL_SIZE) + sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE + 1);

	// Set the scroll size
	SetScrollSizes( MM_TEXT, CSize(SizeX,SizeY) );
}

// The user want zoom in
//
void CHeroscapeEditorView::OnZoomin()
{
	ZoomIn( CPoint(-1,-1) );
}

// The user want zoom out
//
void CHeroscapeEditorView::OnZoomout()
{
	ZoomOut( CPoint(-1,-1) );
}

// The user want choose a zoom value
//
void CHeroscapeEditorView::OnZoomValue()
{
	CZoomValueDlg Dlg;
	Dlg.m_ZoomValue = m_ZoomLevel;

	if( Dlg.DoModal()==IDOK )
	{
		// Compute center of the window
		CRect Rect;
		GetClientRect( &Rect );

		double SizeX = 2 *((int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE));
		double SizeY = (int) ((int) (((int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE)) + m_ZoomLevel*TILE_ORIGINAL_SIZE) + 1);

		double XCenter;
		double YCenter;
		XCenter = (m_ScrollPosX + Rect.Width()/2.0)/SizeX;
		YCenter = (m_ScrollPosY + Rect.Height()/2.0)/SizeY;

		m_ZoomLevel = Dlg.m_ZoomValue;

		LockWindowUpdate();
		RecomputeScrollSize();

		CenterOnPoint( XCenter, YCenter );
		UnlockWindowUpdate();

		OnUpdate( NULL, NULL, NULL );
		RedrawWindow();
	}
}

// The user want a full view
//
void CHeroscapeEditorView::OnFullview()
{
	// If no tile then full view is unuseful
	if( GetDocument()->m_TileList.GetCount()==0 )
		return;

	CHeroscapeEditorDoc* pDoc = GetDocument();

	pDoc->ComputeArea(m_DisplayNumber);

	CRect Rect;
	GetClientRect( &Rect );

	double ZoomLevelX = Rect.Width()/(2*cos(30.0*PI/180.0))/pDoc->m_XWidth/TILE_ORIGINAL_SIZE/1.1;
	double ZoomLevelY = Rect.Height()/(2-sin(30.0*PI/180.0))/(pDoc->m_YHeight+1/3.0)/TILE_ORIGINAL_SIZE/1.1;

	m_ZoomLevel = min(ZoomLevelX,ZoomLevelY);

	LockWindowUpdate();
	RecomputeScrollSize();
	UnlockWindowUpdate();

	CenterOnPoint( pDoc->m_XOffset+pDoc->m_XWidth/2.0, pDoc->m_YOffset+pDoc->m_YHeight/2.0 );

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// Zoom in
//
void CHeroscapeEditorView::ZoomIn( CPoint Point )
{
	// Compute center of the window
	CRect Rect;
	GetClientRect( &Rect );

	double SizeX = 2 *((int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE));
	double SizeY = (int) ((int) (((int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE)) + m_ZoomLevel*TILE_ORIGINAL_SIZE) + 1);

	double XCenter;
	double YCenter;
	ScreenToClient( &Point );
	if( Point.x<0 )
	{
		XCenter = (m_ScrollPosX + Rect.Width()/2.0)/SizeX;
		YCenter = (m_ScrollPosY + Rect.Height()/2.0)/SizeY;
	}
	else
	{
		XCenter = (m_ScrollPosX + Point.x)/SizeX;
		YCenter = (m_ScrollPosY + Point.y)/SizeY;
	}

	m_ZoomLevel *= 1.5;

	LockWindowUpdate();
	RecomputeScrollSize();

	CenterOnPoint( XCenter, YCenter );
	UnlockWindowUpdate();

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// Center on a point
//
void CHeroscapeEditorView::CenterOnPoint( double XCenter, double YCenter )
{
	CRect Rect;
	GetClientRect( &Rect );

	double SizeX = 2 *((int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE));
	double SizeY = (int) ((int) (((int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE)) + m_ZoomLevel*TILE_ORIGINAL_SIZE) + 1);

	int ScrollPosX = (int) (XCenter*SizeX-Rect.Width()/2.0);
	int ScrollPosY = (int) (YCenter*SizeY-Rect.Height()/2.0);

	CSize TotalSize = GetTotalSize();
	if( ScrollPosX+Rect.Width()>TotalSize.cx )
		ScrollPosX=TotalSize.cx-Rect.Width();
	if( ScrollPosX<0 )
		ScrollPosX=0;
	if( ScrollPosY+Rect.Height()>TotalSize.cy )
		ScrollPosY=TotalSize.cy-Rect.Height();
	if( ScrollPosY<0 )
		ScrollPosY=0;

	SetScrollPos( SB_VERT, ScrollPosY, TRUE );
	SetScrollPos( SB_HORZ, ScrollPosX, TRUE );
	m_ScrollPosX = ScrollPosX;
	m_ScrollPosY = ScrollPosY;
}

// Zoom out
//
void CHeroscapeEditorView::ZoomOut( CPoint Point )
{
	CRect Rect;
	GetClientRect( &Rect );

	int SizeX = 2 *((int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE));
	int SizeY = (int) ((int) (((int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE)) + m_ZoomLevel*TILE_ORIGINAL_SIZE) + 1);

	double XCenter;
	double YCenter;
	ScreenToClient( &Point );
	if( Point.x<0 )
	{
		XCenter = (m_ScrollPosX + Rect.Width()/2.0)/SizeX;
		YCenter = (m_ScrollPosY + Rect.Height()/2.0)/SizeY;
	}
	else
	{
		XCenter = (m_ScrollPosX + Point.x)/SizeX;
		YCenter = (m_ScrollPosY + Point.y)/SizeY;
	}

	m_ZoomLevel /= 1.5;
	if( m_ZoomLevel<1/1.5 )
		m_ZoomLevel = 1/1.5;

	LockWindowUpdate();
	RecomputeScrollSize();

	CenterOnPoint( XCenter, YCenter );
	UnlockWindowUpdate();

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// The user want level up
//
void CHeroscapeEditorView::OnLevelup()
{
	m_CurrentZLevel += 1;

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// The user want level down
//
void CHeroscapeEditorView::OnLeveldown()
{
	if( m_CurrentZLevel>0 )
	{
		m_CurrentZLevel -= 1;

		OnUpdate( NULL, NULL, NULL );
		RedrawWindow();
	}
}

// Inform the view that a tile is currently moving
//
void CHeroscapeEditorView::InformTileMoving( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY )
{
	// Convert point to client coordinate
	ScreenToClient( &Point );

	CDC* pDC = GetDC();

	// Create the memory DC
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject( m_pBitmapMemory );

	// Create the memory DC 2
	CDC dcMemory2;
	dcMemory2.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap2 = dcMemory2.SelectObject( m_pBitmapMemory2 );

	CRect Rect;
	GetClientRect( &Rect );

	dcMemory2.BitBlt( 0, 0, Rect.Width(), Rect.Height(), &dcMemory, 0, 0, SRCCOPY ); 

	pTile->Draw( &dcMemory2, (int) (Point.x-(pTile->m_PixelSizeX*m_TileStepX3)/2.0-DiffPosTileMouseX*(pTile->m_PixelSizeX*m_TileStepX3)), (int) (Point.y-(pTile->m_PixelSizeY*m_TileStepY3+m_TileStepY2)/2.0-DiffPosTileMouseY*(pTile->m_PixelSizeY*m_TileStepY3+m_TileStepY2)), m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0);  

	pDC->BitBlt( 0, 0, Rect.Width(), Rect.Height(), &dcMemory2, 0, 0, SRCCOPY );

	ReleaseDC( pDC );
}

// Inform the view that a tile is launching
//
bool CHeroscapeEditorView::InformTileLaunch( CTile* pTile, POINT Point, double DiffPosTileMouseX, double DiffPosTileMouseY )
{
	// Convert point to client coordinate
	ScreenToClient( &Point );

	CRect Rect;
	GetClientRect( &Rect );
	if( Point.x>=0 && Point.x<Rect.Width() && Point.y>=0 && Point.y<Rect.Height() )
	{
		// Compute real position and set
		GetTilePosition( CPoint( (int) (Point.x-(pTile->m_PixelSizeX*m_TileStepX3)/2.0-DiffPosTileMouseX*(pTile->m_PixelSizeX*m_TileStepX3)+m_TileStepX2),(int) (Point.y-(pTile->m_PixelSizeY*m_TileStepY3+m_TileStepY2)/2.0-DiffPosTileMouseY*(pTile->m_PixelSizeY*m_TileStepY3+m_TileStepY2)+(m_TileStepY4)/2.0)), pTile->m_PosX, pTile->m_PosY );
		pTile->m_PosZ = m_CurrentZLevel;
		SetFocus();

		return true;
	}

	return false;
}

// The window size change
//
void CHeroscapeEditorView::OnSize(UINT nType, int cx, int cy)
{
	// Call the base class
	SetRedraw( FALSE );
	CScrollView::OnSize(nType, cx, cy);
	SetRedraw( TRUE );

	CDC* pDC = GetDC();

	// Create the bitmaps
	if( m_pBitmapMemory )
		delete m_pBitmapMemory;
	m_pBitmapMemory = new CBitmap();
	m_pBitmapMemory->CreateCompatibleBitmap( pDC, cx, cy );

	if( m_pBitmapMemory2 )
		delete m_pBitmapMemory2;
	m_pBitmapMemory2 = new CBitmap();
	m_pBitmapMemory2->CreateCompatibleBitmap( pDC, cx, cy );

	if( m_pBitmapMemoryUnderCurrentLevel )
		delete m_pBitmapMemoryUnderCurrentLevel;
	m_pBitmapMemoryUnderCurrentLevel = new CBitmap();
	m_pBitmapMemoryUnderCurrentLevel->CreateCompatibleBitmap( pDC, cx, cy );

	ReleaseDC( pDC );

	// Redraw the window
	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// The view need to be update
//
void CHeroscapeEditorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CDC* pDC = GetDC();

	// Create the memory DC
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject( m_pBitmapMemory );

	CRect Rect;
	GetClientRect( &Rect );

	// Clear the memory dc
	dcMemory.FillSolidRect( 0, 0, Rect.Width(), Rect.Height(), theApp.m_BackgroundColor2D );

	// Compute size
	m_TileStepX2 = (int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE);
	m_TileStepX3 = 2*m_TileStepX2;
	m_TileStepY2 = (int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE);
	m_TileStepY3 = (int) (m_TileStepY2+m_ZoomLevel*TILE_ORIGINAL_SIZE);
	m_TileStepY4 = (int) (m_TileStepY3+sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE);

	// Draw the already placed tile under current level
	CHeroscapeEditorDoc* pDoc = GetDocument();
	for( int Level=0; Level<=m_CurrentZLevel-1; Level++ )
	{
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
			if( pTile->m_PosZ==Level )
			{
				int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
				int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
				if( pTile->m_IsSelected )
				{
					PosX += m_SelectedTileOffset.x;
					PosY += m_SelectedTileOffset.y;
				}

				if( pTile->m_PosY%2!=0 )
					PosX += m_TileStepX2;

				pTile->Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
			}
		}
	}

	CPen Pen;
	Pen.CreatePen( PS_SOLID, 1, RGB(192,192,192) );
	CPen* pOldPen = dcMemory.SelectObject( &Pen );
	// Draw the grid
	for( int x=0; x<BOARD_MAX_TILE_X; x++ )
	{
		for( int y=0; y<BOARD_MAX_TILE_Y/2; y++ )
		{
			int OffsetX = x*m_TileStepX3-GetScrollPos(SB_HORZ);
			int OffsetY = y*2*m_TileStepY3-GetScrollPos(SB_VERT);
			dcMemory.MoveTo( OffsetX, OffsetY+m_TileStepY2 );
			dcMemory.LineTo( OffsetX+m_TileStepX2, OffsetY );
			dcMemory.LineTo( OffsetX+m_TileStepX3, OffsetY+m_TileStepY2 );
			dcMemory.LineTo( OffsetX+m_TileStepX3, OffsetY+m_TileStepY3 );
			dcMemory.LineTo( OffsetX+m_TileStepX2, OffsetY+m_TileStepY4 );
			dcMemory.LineTo( OffsetX, OffsetY+m_TileStepY3 );
			dcMemory.LineTo( OffsetX, OffsetY+m_TileStepY2 );
			if( x<BOARD_MAX_TILE_X-1 )
			{
				OffsetX = x*m_TileStepX3+m_TileStepX2-GetScrollPos(SB_HORZ);
				OffsetY = y*2*m_TileStepY3+m_TileStepY3-GetScrollPos(SB_VERT);
				dcMemory.MoveTo( OffsetX, OffsetY+m_TileStepY2 );
				dcMemory.LineTo( OffsetX+m_TileStepX2, OffsetY );
				dcMemory.LineTo( OffsetX+m_TileStepX3, OffsetY+m_TileStepY2 );
				dcMemory.LineTo( OffsetX+m_TileStepX3, OffsetY+m_TileStepY3 );
				dcMemory.LineTo( OffsetX+m_TileStepX2, OffsetY+m_TileStepY4 );
				dcMemory.LineTo( OffsetX, OffsetY+m_TileStepY3 );
				dcMemory.LineTo( OffsetX, OffsetY+m_TileStepY2 );
			}
		}
	}

	// Copy this bitmap to the bitmap under level
	// Create the memory DC
	CDC dcMemory2;
	dcMemory2.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap2 = dcMemory2.SelectObject( m_pBitmapMemoryUnderCurrentLevel );

	dcMemory2.BitBlt( 0, 0, Rect.Width(), Rect.Height(), &dcMemory, 0, 0, SRCCOPY );
	dcMemory2.SelectObject( pOldBitmap2 );


	// Draw the already placed tile unselected on this current level
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
		if( pTile->m_PosZ==m_CurrentZLevel && pTile->m_IsSelected==false )
		{
			int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( pTile->m_IsSelected )
			{
				PosX += m_SelectedTileOffset.x;
				PosY += m_SelectedTileOffset.y;
			}

			if( pTile->m_PosY%2!=0 )
				PosX += m_TileStepX2;

			pTile->Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
		}
	}

	// Draw the already placed tile selected on this current level
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
		if( pTile->m_PosZ==m_CurrentZLevel && pTile->m_IsSelected==true )
		{
			int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( pTile->m_IsSelected )
			{
				PosX += m_SelectedTileOffset.x;
				PosY += m_SelectedTileOffset.y;
			}

			if( pTile->m_PosY%2!=0 )
				PosX += m_TileStepX2;

			pTile->Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
		}
	}

	if( m_OnionSkinMode )
	{
		// If we are in onion skin mode draw the tile at the upper level
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
			if( pTile->m_PosZ==m_CurrentZLevel+1 )
			{
				int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
				int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
				if( pTile->m_IsSelected )
				{
					PosX += m_SelectedTileOffset.x;
					PosY += m_SelectedTileOffset.y;
				}

				if( pTile->m_PosY%2!=0 )
					PosX += m_TileStepX2;

				pTile->DrawOnionSkinMode( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
			}
		}
	}

	// Display Row and column
	if( m_DisplayNumber )
	{
		CTileNumber aTile;

		for( int y=(int) pDoc->m_FirstY; y<(int) pDoc->m_LastY; y++ )
		{
			aTile.m_Text.Format(_T("%i"),(int) (y-pDoc->m_FirstY+1));

			int PosX = ((int) pDoc->m_FirstX-1)*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = y*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( y%2!=0 )
				PosX += m_TileStepX2;

			aTile.Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0 );
		}
		for( int x=(int) (pDoc->m_FirstX); x<(int) pDoc->m_LastX; x++ )
		{
			int Offset = (int) (x-pDoc->m_FirstX+.5);
			if( Offset>25 )
				aTile.m_Text.Format(_T("%c%c"),'A'+((int) (Offset/26))-1,(Offset%26)+'A');
			else
				aTile.m_Text.Format(_T("%c"),Offset+'A');

			int PosX = x*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = ((int) pDoc->m_FirstY-2)*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( ((int) pDoc->m_FirstY-2)%2!=0 )
				PosX += m_TileStepX2;

			aTile.Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0 );

			PosX = x*m_TileStepX3-GetScrollPos(SB_HORZ);
			PosY = ((int) pDoc->m_FirstY-1)*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( ((int) pDoc->m_FirstY-1)%2!=0 )
				PosX += m_TileStepX2;

			aTile.Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0 );
		}

		// Display coordinate of each tile
	}

	dcMemory.SetROP2( R2_COPYPEN );
	dcMemory.SetTextColor( RGB(0,0,0) );

	if( pDoc->m_TileList.GetCount()>0 && !m_DisplayNumber )
	{
		// Draw dimension
		CPen PenDimension;
		PenDimension.CreatePen( PS_SOLID, 1, RGB(128,128,192) );
		dcMemory.SelectObject( &PenDimension );
		int y;
		if( pDoc->m_FirstY>0 )
			y = (int) (pDoc->m_FirstY*m_TileStepY3-(m_TileStepY3-m_TileStepY2)/2.0-GetScrollPos(SB_VERT));
		else
			y = (int) (pDoc->m_LastY*m_TileStepY3+m_TileStepY2+(m_TileStepY3-m_TileStepY2)/2.0-GetScrollPos(SB_VERT));
		int x1,x2;
		x1 = (int) (pDoc->m_FirstX*m_TileStepX3)-GetScrollPos(SB_HORZ);
		x2 = (int) (pDoc->m_LastX*m_TileStepX3)-GetScrollPos(SB_HORZ);
		dcMemory.MoveTo( x1, y );
		dcMemory.LineTo( x2, y );
		dcMemory.LineTo( x2-6, y-3 );
		dcMemory.MoveTo( x2, y );
		dcMemory.LineTo( x2-6, y+4 );
		dcMemory.MoveTo( x1, y );
		dcMemory.LineTo( x1+6, y-3 );
		dcMemory.MoveTo( x1, y );
		dcMemory.LineTo( x1+6, y+4 );
		int x;
		if( pDoc->m_FirstX>0.5 )
			x = (int) ((pDoc->m_FirstX-0.5)*m_TileStepX3-GetScrollPos(SB_HORZ));
		else
			x = (int) ((pDoc->m_LastX+0.5)*m_TileStepX3-GetScrollPos(SB_HORZ));
		int y1,y2;
		y1 = (int) (pDoc->m_FirstY*m_TileStepY3)-GetScrollPos(SB_VERT);
		y2 = (int) (pDoc->m_LastY*m_TileStepY3+m_TileStepY2)-GetScrollPos(SB_VERT);
		dcMemory.MoveTo( x, y1 );
		dcMemory.LineTo( x, y2 );
		dcMemory.LineTo( x-3, y2-6 );
		dcMemory.MoveTo( x, y2 );
		dcMemory.LineTo( x+4, y2-6 );
		dcMemory.MoveTo( x, y1 );
		dcMemory.LineTo( x-3, y1+6 );
		dcMemory.MoveTo( x, y1 );
		dcMemory.LineTo( x+4, y1+6 );

		// Display Dimmension
		CString Str;
		switch( theApp.m_Unit )
		{
		case 0: // Cm
			Str.Format( _T("%0.2f cm"), (pDoc->m_LastX-pDoc->m_FirstX)*TILE_REAL_WIDTH_X_CM );
			break;
		case 1: // Inch
			Str.Format( _T("%0.2f inch"), (pDoc->m_LastX-pDoc->m_FirstX)*TILE_REAL_WIDTH_X_CM/2.55 );
			break;
		case 2: // hex
			Str.Format( _T("%0.2f hex"), (pDoc->m_LastX-pDoc->m_FirstX) );
			break;
		}
		CRect TextRect;
		TextRect.left = x1-100;
		TextRect.right = x2+100;
		if( pDoc->m_FirstY>0 )
		{
			TextRect.top = y-20;
			TextRect.bottom = y;
		}
		else
		{
			TextRect.top = y;
			TextRect.bottom = y+20;
		}
		dcMemory.SetBkMode( TRANSPARENT );
		CFont DimFont;
		DimFont.CreateFont( 12, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
		CFont* pOldFont = dcMemory.SelectObject( &DimFont );
		if( pDoc->m_FirstY>0 )
			dcMemory.DrawText( Str, TextRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER );
		else
			dcMemory.DrawText( Str, TextRect, DT_TOP | DT_SINGLELINE | DT_CENTER );

		switch( theApp.m_Unit )
		{
		case 0: // Cm
			Str.Format( _T("%0.2f cm"), (pDoc->m_LastY-pDoc->m_FirstY-1)*TILE_REAL_HEIGHT1_CM+TILE_REAL_HEIGHT2_CM );
			break;
		case 1: // Inch
			Str.Format( _T("%0.2f inch"), ((pDoc->m_LastY-pDoc->m_FirstY-1)*TILE_REAL_HEIGHT1_CM+TILE_REAL_HEIGHT2_CM)/2.55 );
			break;
		case 2: // Hex
			Str.Format( _T("%0.2f hex"), (pDoc->m_LastY-pDoc->m_FirstY) );
			break;
		}
		CFont DimFont2;
		if( pDoc->m_FirstX>0.5 )
			DimFont2.CreateFont( 10, 0, 900, 900, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
		else
			DimFont2.CreateFont( 10, 0, -900, -900, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
		dcMemory.SelectObject( &DimFont2 );
		if( pDoc->m_FirstX>0.5 )
		{
			TextRect.left = x-100;
			TextRect.right = x;
		}
		else
		{
			TextRect.left = x;
			TextRect.right = x+100;
		}
		TextRect.top = y1;
		TextRect.bottom = y2;
		dcMemory.SetTextAlign( TA_CENTER | TA_BOTTOM );
		dcMemory.TextOut( x, (y1+y2)/2, Str );
		
		dcMemory.SelectObject( pOldFont );
	}

	// Display current level
	CFont	LevelFont;
	LevelFont.CreateFont( 14, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
	CString Str,Str2;
	Str2.LoadString( IDS_LEVELNUMBER );
	Str.Format( Str2, m_CurrentZLevel+1 );
	CRect	TextRect;
	TextRect.left = 0;
	TextRect.right = Rect.right;
	TextRect.top = Rect.bottom - 20;
	TextRect.bottom = Rect.bottom;
	dcMemory.SetTextColor( RGB(0,0,0) );
	CFont* pOldFont = dcMemory.SelectObject( &LevelFont );
	dcMemory.SetTextAlign( TA_LEFT | TA_TOP );
	dcMemory.DrawText( Str, TextRect, DT_RIGHT | DT_BOTTOM );

	dcMemory.SelectObject( pOldFont );
	dcMemory.SelectObject( pOldPen );

	ReleaseDC( pDC );
}

// The view need to be update only for current level or above
//
void CHeroscapeEditorView::OnUpdateFromCurrentLevel(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CDC* pDC = GetDC();

	// Create the memory DC
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dcMemory.SelectObject( m_pBitmapMemory );

	CRect Rect;
	GetClientRect( &Rect );

	// Compute size
	m_TileStepX2 = (int) (cos(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE);
	m_TileStepX3 = 2*m_TileStepX2;
	m_TileStepY2 = (int) (sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE);
	m_TileStepY3 = (int) (m_TileStepY2+m_ZoomLevel*TILE_ORIGINAL_SIZE);
	m_TileStepY4 = (int) (m_TileStepY3+sin(30.0*PI/180.0)*m_ZoomLevel*TILE_ORIGINAL_SIZE);

	// Copy under level bitmap to the memory bitmap 
	// Create the memory DC
	CDC dcMemory2;
	dcMemory2.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap2 = dcMemory2.SelectObject( m_pBitmapMemoryUnderCurrentLevel );

	dcMemory.BitBlt( 0, 0, Rect.Width(), Rect.Height(), &dcMemory2, 0, 0, SRCCOPY );
	dcMemory2.SelectObject( pOldBitmap2 );

	CHeroscapeEditorDoc* pDoc = GetDocument();

	// Draw the already placed tile unselected on this current level
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
		if( pTile->m_PosZ==m_CurrentZLevel && pTile->m_IsSelected==false )
		{
			int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( pTile->m_IsSelected )
			{
				PosX += m_SelectedTileOffset.x;
				PosY += m_SelectedTileOffset.y;
			}

			if( pTile->m_PosY%2!=0 )
				PosX += m_TileStepX2;

			pTile->Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
		}
	}

	// Draw the already placed tile selected on this current level
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
		if( pTile->m_PosZ==m_CurrentZLevel && pTile->m_IsSelected==true )
		{
			int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( pTile->m_IsSelected )
			{
				PosX += m_SelectedTileOffset.x;
				PosY += m_SelectedTileOffset.y;
			}

			if( pTile->m_PosY%2!=0 )
				PosX += m_TileStepX2;

			pTile->Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
		}
	}

	if( m_OnionSkinMode )
	{
		// If we are in onion skin mode draw the tile at the upper level
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);
			if( pTile->m_PosZ==m_CurrentZLevel+1 )
			{
				int PosX = pTile->m_PosX*m_TileStepX3-GetScrollPos(SB_HORZ);
				int PosY = pTile->m_PosY*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
				if( pTile->m_IsSelected )
				{
					PosX += m_SelectedTileOffset.x;
					PosY += m_SelectedTileOffset.y;
				}

				if( pTile->m_PosY%2!=0 )
					PosX += m_TileStepX2;

				pTile->DrawOnionSkinMode( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, m_CurrentZLevel );
			}
		}
	}

	// Display Row and column
	if( m_DisplayNumber )
	{
		CTileNumber aTile;

		for( int y=(int) pDoc->m_FirstY; y<(int) pDoc->m_LastY; y++ )
		{
			aTile.m_Text.Format(_T("%i"),(int) (y-pDoc->m_FirstY+1));

			int PosX = ((int) pDoc->m_FirstX-1)*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = y*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( y%2!=0 )
				PosX += m_TileStepX2;

			aTile.Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0 );
		}
		for( int x=(int) (pDoc->m_FirstX); x<(int) pDoc->m_LastX; x++ )
		{
			int Offset = (int) (x-pDoc->m_FirstX+.5);
			if( Offset>25 )
				aTile.m_Text.Format(_T("%c%c"),'A'+((int) (Offset/26))-1,(Offset%26)+'A');
			else
				aTile.m_Text.Format(_T("%c"),Offset+'A');

			int PosX = x*m_TileStepX3-GetScrollPos(SB_HORZ);
			int PosY = ((int) pDoc->m_FirstY-2)*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( ((int) pDoc->m_FirstY-2)%2!=0 )
				PosX += m_TileStepX2;

			aTile.Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0 );

			PosX = x*m_TileStepX3-GetScrollPos(SB_HORZ);
			PosY = ((int) pDoc->m_FirstY-1)*m_TileStepY3+m_TileStepY2-GetScrollPos(SB_VERT);
			if( ((int) pDoc->m_FirstY-1)%2!=0 )
				PosX += m_TileStepX2;

			aTile.Draw( &dcMemory, PosX, PosY, m_TileStepX2, m_TileStepX3, m_TileStepY2, m_TileStepY3, m_TileStepY4, 0 );
		}

		// Display coordinate of each tile
	}

	dcMemory.SetROP2( R2_COPYPEN );
	dcMemory.SetTextColor( RGB(0,0,0) );

	if( pDoc->m_TileList.GetCount()>0 && !m_DisplayNumber )
	{
		// Draw dimension
		CPen PenDimension;
		PenDimension.CreatePen( PS_SOLID, 1, RGB(128,128,192) );
		dcMemory.SelectObject( &PenDimension );
		int y;
		if( pDoc->m_FirstY>0 )
			y = (int) (pDoc->m_FirstY*m_TileStepY3-(m_TileStepY3-m_TileStepY2)/2.0-GetScrollPos(SB_VERT));
		else
			y = (int) (pDoc->m_LastY*m_TileStepY3+m_TileStepY2+(m_TileStepY3-m_TileStepY2)/2.0-GetScrollPos(SB_VERT));
		int x1,x2;
		x1 = (int) (pDoc->m_FirstX*m_TileStepX3)-GetScrollPos(SB_HORZ);
		x2 = (int) (pDoc->m_LastX*m_TileStepX3)-GetScrollPos(SB_HORZ);
		dcMemory.MoveTo( x1, y );
		dcMemory.LineTo( x2, y );
		dcMemory.LineTo( x2-6, y-3 );
		dcMemory.MoveTo( x2, y );
		dcMemory.LineTo( x2-6, y+4 );
		dcMemory.MoveTo( x1, y );
		dcMemory.LineTo( x1+6, y-3 );
		dcMemory.MoveTo( x1, y );
		dcMemory.LineTo( x1+6, y+4 );
		int x;
		if( pDoc->m_FirstX>0.5 )
			x = (int) ((pDoc->m_FirstX-0.5)*m_TileStepX3-GetScrollPos(SB_HORZ));
		else
			x = (int) ((pDoc->m_LastX+0.5)*m_TileStepX3-GetScrollPos(SB_HORZ));
		int y1,y2;
		y1 = (int) (pDoc->m_FirstY*m_TileStepY3)-GetScrollPos(SB_VERT);
		y2 = (int) (pDoc->m_LastY*m_TileStepY3+m_TileStepY2)-GetScrollPos(SB_VERT);
		dcMemory.MoveTo( x, y1 );
		dcMemory.LineTo( x, y2 );
		dcMemory.LineTo( x-3, y2-6 );
		dcMemory.MoveTo( x, y2 );
		dcMemory.LineTo( x+4, y2-6 );
		dcMemory.MoveTo( x, y1 );
		dcMemory.LineTo( x-3, y1+6 );
		dcMemory.MoveTo( x, y1 );
		dcMemory.LineTo( x+4, y1+6 );

		// Display Dimmension
		CString Str;
		switch( theApp.m_Unit )
		{
		case 0: // Cm
			Str.Format( _T("%0.2f cm"), (pDoc->m_LastX-pDoc->m_FirstX)*TILE_REAL_WIDTH_X_CM );
			break;
		case 1: // Inch
			Str.Format( _T("%0.2f inch"), (pDoc->m_LastX-pDoc->m_FirstX)*TILE_REAL_WIDTH_X_CM/2.55 );
			break;
		case 2: // hex
			Str.Format( _T("%0.2f hex"), (pDoc->m_LastX-pDoc->m_FirstX) );
			break;
		}
		CRect TextRect;
		TextRect.left = x1-100;
		TextRect.right = x2+100;
		if( pDoc->m_FirstY>0 )
		{
			TextRect.top = y-20;
			TextRect.bottom = y;
		}
		else
		{
			TextRect.top = y;
			TextRect.bottom = y+20;
		}
		dcMemory.SetBkMode( TRANSPARENT );
		CFont DimFont;
		DimFont.CreateFont( 12, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
		CFont* pOldFont = dcMemory.SelectObject( &DimFont );
		if( pDoc->m_FirstY>0 )
			dcMemory.DrawText( Str, TextRect, DT_BOTTOM | DT_SINGLELINE | DT_CENTER );
		else
			dcMemory.DrawText( Str, TextRect, DT_TOP | DT_SINGLELINE | DT_CENTER );

		switch( theApp.m_Unit )
		{
		case 0: // Cm
			Str.Format( _T("%0.2f cm"), (pDoc->m_LastY-pDoc->m_FirstY-1)*TILE_REAL_HEIGHT1_CM+TILE_REAL_HEIGHT2_CM );
			break;
		case 1: // Inch
			Str.Format( _T("%0.2f inch"), ((pDoc->m_LastY-pDoc->m_FirstY-1)*TILE_REAL_HEIGHT1_CM+TILE_REAL_HEIGHT2_CM)/2.55 );
			break;
		case 2: // Hex
			Str.Format( _T("%0.2f hex"), (pDoc->m_LastY-pDoc->m_FirstY) );
			break;
		}
		CFont DimFont2;
		if( pDoc->m_FirstX>0.5 )
			DimFont2.CreateFont( 10, 0, 900, 900, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
		else
			DimFont2.CreateFont( 10, 0, -900, -900, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
		dcMemory.SelectObject( &DimFont2 );
		if( pDoc->m_FirstX>0.5 )
		{
			TextRect.left = x-100;
			TextRect.right = x;
		}
		else
		{
			TextRect.left = x;
			TextRect.right = x+100;
		}
		TextRect.top = y1;
		TextRect.bottom = y2;
		dcMemory.SetTextAlign( TA_CENTER | TA_BOTTOM );
		dcMemory.TextOut( x, (y1+y2)/2, Str );
		
		dcMemory.SelectObject( pOldFont );
	}

	// Display current level
	CFont	LevelFont;
	LevelFont.CreateFont( 14, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, _T("Arial") );
	CString Str,Str2;
	Str2.LoadString( IDS_LEVELNUMBER );
	Str.Format( Str2, m_CurrentZLevel+1 );
	CRect	TextRect;
	TextRect.left = 0;
	TextRect.right = Rect.right;
	TextRect.top = Rect.bottom - 20;
	TextRect.bottom = Rect.bottom;
	dcMemory.SetTextColor( RGB(0,0,0) );
	CFont* pOldFont = dcMemory.SelectObject( &LevelFont );
	dcMemory.SetTextAlign( TA_LEFT | TA_TOP );
	dcMemory.DrawText( Str, TextRect, DT_RIGHT | DT_BOTTOM );

	dcMemory.SelectObject( pOldFont );

	ReleaseDC( pDC );
}

// Don't need to erase the background
//
BOOL CHeroscapeEditorView::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}

// When the user scroll
//
void CHeroscapeEditorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SetRedraw( FALSE );
	// Call the base class
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	SetRedraw( TRUE );

	m_ScrollPosX = GetScrollPos( SB_HORZ );

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// When the user scroll
//
void CHeroscapeEditorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SetRedraw( FALSE );
	// Call the base class
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	SetRedraw( TRUE );

	m_ScrollPosY = GetScrollPos( SB_VERT );

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// Can go under level 0
//
void CHeroscapeEditorView::OnUpdateLeveldown(CCmdUI *pCmdUI)
{
	if( m_CurrentZLevel>0 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// The user select a tile
//
void CHeroscapeEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	int PosX, PosY;
	GetTilePosition( point, PosX, PosY );

	// Find the tile
	CTile* pFindTile = NULL;
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ==m_CurrentZLevel )
		{
			if( pTile->ContainPos( PosX, PosY ) )
				pFindTile = pTile;
		}
	}

	if( !pFindTile && (nFlags&MK_CONTROL)==0 )
	{
		// No tile is find so unselect all tile and set the last used tile
		pDoc->UnselectAllTile();

		CTile* pTile = CTile::GetNewTile( ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastUsedTileType );
		if( pTile!=NULL )
		{
			if( pTile->m_Type/1000==TYPE_STARTAREA )
				pTile->m_TileColor = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastStartAreaColor;
			else if( pTile->m_Type/1000==TYPE_PERSONAL )
			{
				pTile->m_TileColor = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileColor;
				pTile->m_PersonalTexture = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileTexture;
				pTile->m_PersonalTextureSide = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileTextureSide;
				pTile->m_NbTile =  ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalNbTile;
				((CTilePerso*) pTile)->m_Char = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileChar;
				((CTilePerso*) pTile)->m_Name = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileName;
				pTile->Init();
			}
			else if( pTile->m_Type/1000==TYPE_FIGURE )
			{
				((CTileFigure*) pTile)->m_FigureFile = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastFigureFile;
				((CTileFigure*) pTile)->m_FigureName = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastFigureName;
				((CTileFigure*) pTile)->m_NbTile = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastFigureNbTile;
				pTile->Init();
			}
			// Compute real position and set
			GetTilePosition( point, pTile->m_PosX, pTile->m_PosY );
			pTile->m_PosZ = m_CurrentZLevel;
			pTile->m_IsSelected = true;
			pDoc->AddTile( pTile );

			pDoc->UpdateAllViews( this );
			OnUpdateFromCurrentLevel( NULL, NULL, NULL );
			pDoc->RedrawAllViews();

			m_Mode = MODE_ADD_ON_MOVE;
		}
		pDoc->DisplaySelectedCount();
	}

	if( pFindTile )
	{
		if( !pFindTile->m_IsSelected && (nFlags&MK_CONTROL)==0 )
			pDoc->UnselectAllTile();

		pFindTile->m_IsSelected = true;

		pDoc->DisplaySelectedCount();

		pDoc->UpdateAllViews( this );
		OnUpdateFromCurrentLevel( NULL, NULL, NULL );
		pDoc->RedrawAllViews();

		m_LastLButtonDownPos = point;
		if( (nFlags&MK_CONTROL)==0 )
			m_Mode = MODE_DRAG;
	}

	// Call the base class
	CScrollView::OnLButtonDown(nFlags, point);
}

// Get the tile position for a pixel
//
void CHeroscapeEditorView::GetTilePosition( POINT Point, int& PosX, int& PosY )
{
	// Compute 4 more near tile
	int PosX1,PosY1,PosX2,PosY2,PosX3,PosY3,PosX4,PosY4;

	PosY1 = (int) ((Point.y+m_ScrollPosY-m_TileStepY2)/m_TileStepY3);
	PosY2 = PosY1;
	PosY3 = PosY1+1;
	PosY4 = PosY3;

	if( PosY1%2==0 )
	{
		PosX1 = (int) ((Point.x+m_ScrollPosX-m_TileStepX2)/m_TileStepX3);
		PosX2 = PosX1+1;
		PosX3 = PosX1;
		PosX4 = PosX2;
	}
	else
	{
		PosX1 = (int) ((Point.x+m_ScrollPosX-m_TileStepX2*2)/m_TileStepX3);
		PosX2 = PosX1+1;
		PosX3 = PosX1;
		PosX4 = PosX1+1;
	}

	double Dist1,Dist2,Dist3,Dist4;

	if( PosY1%2==0 )
	{
		Dist1 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX1*m_TileStepX3+m_TileStepX2)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY1*m_TileStepY3+m_TileStepY4/2)),2));
		Dist2 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX2*m_TileStepX3+m_TileStepX2)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY2*m_TileStepY3+m_TileStepY4/2)),2));
		Dist3 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX3*m_TileStepX3+m_TileStepX3)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY3*m_TileStepY3+m_TileStepY4/2)),2));
		Dist4 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX4*m_TileStepX3+m_TileStepX3)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY4*m_TileStepY3+m_TileStepY4/2)),2));
	}
	else
	{
		Dist1 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX1*m_TileStepX3+m_TileStepX3)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY1*m_TileStepY3+m_TileStepY4/2)),2));
		Dist2 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX2*m_TileStepX3+m_TileStepX3)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY2*m_TileStepY3+m_TileStepY4/2)),2));
		Dist3 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX3*m_TileStepX3+m_TileStepX2)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY3*m_TileStepY3+m_TileStepY4/2)),2));
		Dist4 = sqrt((double) pow((double) (Point.x+m_ScrollPosX-(PosX4*m_TileStepX3+m_TileStepX2)),2)+pow((double) (Point.y+m_ScrollPosY-(PosY4*m_TileStepY3+m_TileStepY4/2)),2));
	}

	if( Dist1<Dist2 && Dist1<Dist3 && Dist1<Dist4 )
	{
		PosX = PosX1;
		PosY = PosY1;
	}
	else if( Dist2<Dist3 && Dist2<Dist4 )
	{
		PosX = PosX2;
		PosY = PosY2;
	}
	else if( Dist3<Dist4 )
	{
		PosX = PosX3;
		PosY = PosY3;
	}
	else
	{
		PosX = PosX4;
		PosY = PosY4;
	}
}

// When the mouse move
//
void CHeroscapeEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	int PosX, PosY;
	GetTilePosition( point, PosX, PosY );

	if( m_Mode==MODE_DRAG )
	{
		m_SelectedTileOffset.x = point.x-m_LastLButtonDownPos.x;
		m_SelectedTileOffset.y = point.y-m_LastLButtonDownPos.y;

		OnUpdateFromCurrentLevel( NULL, NULL, NULL );
		RedrawWindow();
	}
	else if( m_Mode==MODE_ADD_ON_MOVE )
	{
		CTile* pTile = CTile::GetNewTile( ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastUsedTileType );
		if( pTile!=NULL )
		{
			if( pTile->m_Type/1000==TYPE_STARTAREA )
				pTile->m_TileColor = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastStartAreaColor;
			else if( pTile->m_Type/1000==TYPE_PERSONAL )
			{
				pTile->m_TileColor = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileColor;
				pTile->m_PersonalTexture = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileTexture;
				pTile->m_PersonalTextureSide = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileTextureSide;
				pTile->m_NbTile =  ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalNbTile;
				((CTilePerso*) pTile)->m_Char = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileChar;
				((CTilePerso*) pTile)->m_Name = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastPersonalTileName;
				pTile->Init();
			}
			else if( pTile->m_Type/1000==TYPE_FIGURE )
			{
				((CTileFigure*) pTile)->m_FigureFile = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastFigureFile;
				((CTileFigure*) pTile)->m_FigureName = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastFigureName;
				((CTileFigure*) pTile)->m_NbTile = ((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.m_ObjectFV.m_pObjectList->m_LastFigureNbTile;
				pTile->Init();
			}
			if( pTile->m_NbTile==1 )
			{
				// Verify that no tile are on this position
				int PosX,PosY;
				GetTilePosition( point, PosX, PosY );
				CHeroscapeEditorDoc* pDoc = GetDocument();
				if( !pDoc->IsPositionUsed( PosX, PosY, m_CurrentZLevel ) )
				{
					pTile->m_PosX = PosX;
					pTile->m_PosY = PosY;
					pTile->m_PosZ = m_CurrentZLevel;
					pTile->m_IsSelected = true;
					pDoc->AddTile( pTile );

					pDoc->UpdateAllViews( this );
					OnUpdateFromCurrentLevel( NULL, NULL, NULL );
					pDoc->RedrawAllViews();
				}
				else
					delete pTile;
			}
			else
				delete pTile;
		}
	}
	else
	{
		// If the ctrl key is down then select tile
		if( (nFlags&MK_CONTROL)!=0 && (nFlags&MK_LBUTTON)!=0 )
		{
			CHeroscapeEditorDoc* pDoc = GetDocument();

			// Find the tile
			CTile* pFindTile = NULL;
			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( pTile->m_PosZ==m_CurrentZLevel )
				{
					if( pTile->ContainPos( PosX, PosY ) )
						pFindTile = pTile;
				}
			}

			if( pFindTile!=NULL )
			{
				pFindTile->m_IsSelected=true;

				pDoc->DisplaySelectedCount();

				pDoc->UpdateAllViews( this );
				OnUpdateFromCurrentLevel( NULL, NULL, NULL );
				pDoc->RedrawAllViews();
			}
		}
	}

	// Call the base class
	CScrollView::OnMouseMove(nFlags, point);
}

// The user release the button
//
void CHeroscapeEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	if( m_Mode==MODE_DRAG )
	{
		double DiffX = m_SelectedTileOffset.x/((double) m_TileStepX3);
		if( DiffX>0 )
			DiffX += 0.5;
		else
			DiffX -= 0.5;
		double DiffY = m_SelectedTileOffset.y/((double) m_TileStepY3);
		if( DiffY>0 )
			DiffY += 0.5;
		else
			DiffY -= 0.5;

		int	PosX1, PosY1, PosX2, PosY2;
		GetTilePosition( m_LastLButtonDownPos, PosX1, PosY1 );
		GetTilePosition( point, PosX2, PosY2 );

		if( (((int) DiffY)%2==1 || ((int) DiffY)%2==-1) )
			DiffX += 0.5;

		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

			if( pTile->m_IsSelected )
			{
				if( (((int) DiffY)%2==1 || ((int) DiffY)%2==-1) && pTile->m_PosY%2==0 )
					pTile->m_PosX += (int) DiffX-1;
				else
					pTile->m_PosX += (int) DiffX;
				pTile->m_PosY += (int) DiffY;
				pDoc->SetModifiedFlag();
			}
		}

		m_Mode = MODE_NULL;
		m_SelectedTileOffset.x = m_SelectedTileOffset.y = 0;

		pDoc->ComputeArea(m_DisplayNumber);
		pDoc->UpdateAll3DViews();
		pDoc->UpdateAllViews( this );
		OnUpdateFromCurrentLevel( NULL, NULL, NULL );
		pDoc->RedrawAllViews();
	}
	else if( m_Mode==MODE_ADD_ON_MOVE )
	{
		m_Mode = MODE_NULL ;
	}

	// Call the base class
	CScrollView::OnLButtonUp(nFlags, point);
}

// The user want rotate selection to left
//
void CHeroscapeEditorView::OnEditRotateLeft()
{
	GetDocument()->RotateSelectionLeft();
}

// The user want rotate selection to right
//
void CHeroscapeEditorView::OnEditRotateRight()
{
	GetDocument()->RotateSelectionRight();
}

// To know if we can rotate to left
//
void CHeroscapeEditorView::OnUpdateEditRotateLeft(CCmdUI *pCmdUI)
{
	if( GetDocument()->GetNbSelectedTile()>0 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// To know if we can rotate to right
//
void CHeroscapeEditorView::OnUpdateEditRotateRight(CCmdUI *pCmdUI)
{
	if( GetDocument()->GetNbSelectedTile()>0 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// The user want remove all the selection from the document
//
void CHeroscapeEditorView::OnEditRemove()
{
	GetDocument()->RemoveSelection();
}

// To know if we can remove selection
//
void CHeroscapeEditorView::OnUpdateEditRemove(CCmdUI *pCmdUI)
{
	if( GetDocument()->GetNbSelectedTile()>0 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// When the view is activate or deactivate
//
void CHeroscapeEditorView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	if( bActivate==TRUE )
	{
		((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.SetCurrentDoc( GetDocument() );
		((CMyListCtrl*) ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl())->m_pView = this;
	}
	else
	{
		if(pActivateView==pDeactiveView)
		{
			((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.SetCurrentDoc( NULL );
			((CMyListCtrl*) ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl())->m_pView = NULL;
		}
	}

	// Call the base class
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

// Print the document
//
void CHeroscapeEditorView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if( m_PrintState == PS_DEFAULT )
		GetDocument()->OnPrint( pDC, pInfo );
	else
		GetDocument()->OnPrintNum( pDC, pInfo );
}

// Select all the tile
//
void CHeroscapeEditorView::OnSelectAll()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		pTile->m_IsSelected = true;
	}

	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}

// Select nothing
//
void CHeroscapeEditorView::OnSelectNothing()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		pTile->m_IsSelected = false;
	}

	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}

// Select nothing
//
void CHeroscapeEditorView::OnSelectInverse()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		pTile->m_IsSelected = !pTile->m_IsSelected;
	}

	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}

// Level up for the selection
//
void CHeroscapeEditorView::OnSelectLevelup()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_IsSelected )
			pTile->m_PosZ += 1;
	}

	pDoc->UpdateAll3DViews();
	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}

// Level down for the selection
//
void CHeroscapeEditorView::OnSelectLeveldown()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	// First verify that low level is superior to 0
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_IsSelected )
			if( pTile->m_PosZ<=0 )
			{
				AfxMessageBox( IDS_CANT_LOW_LEVEL );
				return;
			}
	}

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_IsSelected )
			pTile->m_PosZ -= 1;
	}

	pDoc->UpdateAll3DViews();
	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}

// To know if we are in onion skin mode
//
void CHeroscapeEditorView::OnUpdateOutilsReverse(CCmdUI *pCmdUI)
{
	if( m_OnionSkinMode )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// Change the onion skin mode state
//
void CHeroscapeEditorView::OnOutilsReverse()
{
	m_OnionSkinMode = !m_OnionSkinMode;

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();
}

// Use key to move selected tile
//
void CHeroscapeEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CHeroscapeEditorDoc* pDoc = GetDocument();
	bool NeedRedraw=false;

	switch( nChar )
	{
	case VK_UP:
		// Move all the selected tile upper
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

			if( pTile->m_IsSelected )
			{
				if( pTile->m_PosY%2==1 )
					pTile->m_PosX+=1;
				pTile->m_PosY -= 1;
				if( m_LastMoveVertical%2==0 )
					pTile->m_PosX -= 1;
				NeedRedraw = true;
			}
		}
		m_LastMoveVertical++;
		break;
	case VK_DOWN:
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

			if( pTile->m_IsSelected )
			{
				if( pTile->m_PosY%2==1 )
					pTile->m_PosX+=1;
				pTile->m_PosY += 1;
				if( m_LastMoveVertical%2==0 )
					pTile->m_PosX -= 1;
				NeedRedraw = true;
			}
		}
		m_LastMoveVertical++;
		break;
	case VK_LEFT:
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

			if( pTile->m_IsSelected )
			{
				pTile->m_PosX -= 1;
				NeedRedraw = true;
			}
		}
		break;
	case VK_RIGHT:
		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

			if( pTile->m_IsSelected )
			{
				pTile->m_PosX += 1;
				NeedRedraw = true;
			}
		}
		break;
	}

	if( NeedRedraw )
	{
		pDoc->ComputeArea(m_DisplayNumber);
		pDoc->UpdateAll3DViews();
		pDoc->UpdateAllViews( NULL );
		pDoc->RedrawAllViews();
	}

	// Call the base class
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Select all the tile of the level
//
void CHeroscapeEditorView::OnSelectLevel()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ==m_CurrentZLevel )
			pTile->m_IsSelected = true;
		else
			pTile->m_IsSelected = false;
	}

	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}

// Center on a position and blink
//
void CHeroscapeEditorView::CenterOnPosAndBlink( int x, int y, int z )
{
	m_CurrentZLevel = z;
	CenterOnPoint( x+1, y+.5 );

	OnUpdate( NULL, NULL, NULL );
	RedrawWindow();

	CRect Rect;
	GetClientRect( &Rect );

	int MiddleX = x*m_TileStepX3+m_TileStepX2-GetScrollPos(SB_HORZ);
	int MiddleY = (int) (y*m_TileStepY3+(m_TileStepY3-m_TileStepY2)/2.0+m_TileStepY2-GetScrollPos(SB_VERT));

	if( y%2!=0 )
		MiddleX += m_TileStepX2;

	CDC* pDC = GetDC();

	for( int i=0; i<5; i++ )
	{
		if( (i%2)==0 )
			pDC->Ellipse( MiddleX-m_TileStepX2, MiddleY-m_TileStepX2, MiddleX+m_TileStepX2, MiddleY+m_TileStepX2 );

		Sleep( 200 );
		RedrawWindow();
	}

	ReleaseDC( pDC );
}

// The button up the selection of one level must be grayed if nothing is selected
//
void CHeroscapeEditorView::OnUpdateSelectLevelup(CCmdUI *pCmdUI)
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	if( pDoc!=NULL )
		if( pDoc->GetNbSelectedTile()>0 )
		{
			pCmdUI->Enable( TRUE );
			return;
		}

	pCmdUI->Enable( FALSE );
}

// The button down the selection of one level must be grayed if nothing is selected
//
void CHeroscapeEditorView::OnUpdateSelectLeveldown(CCmdUI *pCmdUI)
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	if( pDoc!=NULL )
		if( pDoc->GetNbSelectedTile()>0 )
		{
			pCmdUI->Enable( TRUE );
			return;
		}

	pCmdUI->Enable( FALSE );
}

// Display or not the row and column number
//
void CHeroscapeEditorView::OnOutilsNumber()
{
	m_DisplayNumber = !m_DisplayNumber;

	if( m_DisplayNumber )
		GetDocument()->ComputeArea(m_DisplayNumber);

	GetDocument()->UpdateAllViews( NULL );
	GetDocument()->RedrawAllViews();
}

// To know if we must display row and column number or not
//
void CHeroscapeEditorView::OnUpdateOutilsNumber(CCmdUI *pCmdUI)
{
	if( m_DisplayNumber )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// User want see printed page with num
//
void CHeroscapeEditorView::OnFichierApercunum()
{
	m_PrintState = PS_NUM;
	CScrollView::OnFilePrintPreview();
}

// User want see printed page without num
//
void CHeroscapeEditorView::OnFilePrintPreview()
{
	m_PrintState = PS_DEFAULT;
	CScrollView::OnFilePrintPreview();
}

// User want print page without num
//
void CHeroscapeEditorView::OnFilePrint()
{
	m_PrintState = PS_DEFAULT;
	CScrollView::OnFilePrint();
}

// User want print page with num
//
void CHeroscapeEditorView::OnFichierImprimernum()
{
	m_PrintState = PS_NUM;
	CScrollView::OnFilePrint();
}

// Remove the current level
//
void CHeroscapeEditorView::OnOutilsRemovelevel()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ==m_CurrentZLevel )
		{
			pDoc->RemoveTileIndex(i);
			i--;
		}
	}

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ>m_CurrentZLevel )
			pTile->m_PosZ--;
	}

	pDoc->ComputeArea(m_DisplayNumber);
	pDoc->UpdateAll3DViews();
	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();
}

// Insert a level at current pos
//
void CHeroscapeEditorView::OnOutilsInsertlevel()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ>=m_CurrentZLevel )
			pTile->m_PosZ++;
	}

	pDoc->ComputeArea(m_DisplayNumber);
	pDoc->UpdateAll3DViews();
	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();
}

// Go to a level directly
//
void CHeroscapeEditorView::OnOutilsGoLevel()
{
	CChooseLevelDlg Dlg;

	Dlg.m_Level = m_CurrentZLevel+1;

	if( Dlg.DoModal()==IDOK )
	{
		if( Dlg.m_Level>0 )
		{
			m_CurrentZLevel = Dlg.m_Level-1;
			OnUpdate( NULL, NULL, NULL );
			RedrawWindow();
		}

	}
}

// User want select same tile type on same level
//
void CHeroscapeEditorView::OnSelectSameTileSameLevel()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ==m_CurrentZLevel )
		{
			// Check if a tile of this type is already selected
			for( int j=0; j<pDoc->m_TileList.GetCount(); j++ )
			{
				CTile* pTile2 = (CTile*) pDoc->m_TileList.GetAt(j);
				if( pTile2->m_IsSelected && pTile2->m_Type==pTile->m_Type )
				{
					pTile->m_IsSelected = true;
					break;
				}
			}
		}
		else
			pTile->m_IsSelected = false;
	}

	pDoc->UpdateAllViews( NULL );
	pDoc->RedrawAllViews();

	pDoc->DisplaySelectedCount();
}
