// ListCtrlObject.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "HeroscapeEditorDoc.h"
#include "HeroscapeEditorView.h"
#include "ListCtrlObject.h"
#include "MainFrm.h"
#include "TileFigure.h"
#include "TilePerso.h"

// CListCtrlObject

IMPLEMENT_DYNCREATE(CListCtrlObject, CScrollView)

// The constructor
//
CListCtrlObject::CListCtrlObject()
{
	// No Scroll
	SetScrollSizes(MM_TEXT, CSize(1,1) );
	// No current tile
	m_pCurrentTile = NULL;
	// No special mode now
	m_Mode = MODE_NULL;
	// No bitmap
	m_pBitmapMemory = NULL;
	// No document now
	m_pDoc = NULL;
	// No current tile now
	m_LastUsedTileType = 0;
}

// The destructor
//
CListCtrlObject::~CListCtrlObject()
{
	if( m_pBitmapMemory )
		delete m_pBitmapMemory;

	RemoveAllObjects();
}

BEGIN_MESSAGE_MAP(CListCtrlObject, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
//	ON_WM_NCMOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CListCtrlObject drawing

void CListCtrlObject::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	CRect Rect;
	CRect Rect2;
	Rect.left = Rect.right = 0;
	Rect2.left = 0;
	Rect2.right = 1;

	// Create the memory DC
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap2 = dcMemory.SelectObject( m_pBitmapMemory );

	while( Rect.Width()!=Rect2.Width() )
	{
		GetClientRect( &Rect );
		DWORD ColorFace = ::GetSysColor(COLOR_WINDOW);
		dcMemory.FillSolidRect( Rect, ColorFace );

		int PosX = Rect.Width()/2;
		int PosY = 20;

		for( int i=0; i<m_ObjectList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) m_ObjectList.GetAt( i );

			// PosY += 20;

			pTile->DrawSample( &dcMemory, (int) (PosX-(pTile->m_PixelSizeX*12)/2.0), PosY-GetScrollPos(SB_VERT) );

			PosY += (pTile->m_PixelSizeY*11+2);

			CString	Str;
			if( m_pDoc!=NULL )
			{
				if( theApp.m_MaterialNb[pTile->m_Type]>=500 )
				{
					Str = pTile->GetName();
					dcMemory.SetTextColor( RGB(0,0,120) );
				}
				else
				{
					if( pTile->m_Type==TYPE_CASTLE*1000+404 )
					{
						Str.Format( _T("%s (%i/%i)"), pTile->GetName(), ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[TYPE_CASTLE*1000+401], theApp.m_MaterialNb[TYPE_CASTLE*1000+401] );
						if( ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[TYPE_CASTLE*1000+401]>theApp.m_MaterialNb[TYPE_CASTLE*1000+401] )
							dcMemory.SetTextColor( RGB(200,0,0) );
						else if( ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[TYPE_CASTLE*1000+401]==theApp.m_MaterialNb[TYPE_CASTLE*1000+401] )
							dcMemory.SetTextColor( RGB(0,120,0) );
						else
							dcMemory.SetTextColor( RGB(0,0,120) );
					}
					else if( pTile->m_Type==TYPE_WATER*1000+2 )
					{
						Str.Format( _T("%s (%i/%i)"), pTile->GetName(), ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[TYPE_WATER*1000+1], theApp.m_MaterialNb[TYPE_WATER*1000+1] );
						if( ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[TYPE_WATER*1000+1]>theApp.m_MaterialNb[TYPE_WATER*1000+1] )
							dcMemory.SetTextColor( RGB(200,0,0) );
						else if( ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[TYPE_WATER*1000+1]==theApp.m_MaterialNb[TYPE_WATER*1000+1] )
							dcMemory.SetTextColor( RGB(0,120,0) );
						else
							dcMemory.SetTextColor( RGB(0,0,120) );
					}
					else
					{
						if( pTile->m_Type==TYPE_PERSONAL*1000 )
						{
							Str.Format( _T("%s (%i/%i)"), pTile->GetName(), ((CHeroscapeEditorDoc*) m_pDoc)->GetPersonalTileOfType((CTilePerso*) theApp.m_TilePersoList.GetAt(i)), ((CTilePerso*) theApp.m_TilePersoList.GetAt(i))->m_Quantity );
							if( ((CHeroscapeEditorDoc*) m_pDoc)->GetPersonalTileOfType((CTilePerso*) theApp.m_TilePersoList.GetAt(i))>((CTilePerso*) theApp.m_TilePersoList.GetAt(i))->m_Quantity )
								dcMemory.SetTextColor( RGB(200,0,0) );
							else if( ((CHeroscapeEditorDoc*) m_pDoc)->GetPersonalTileOfType((CTilePerso*) theApp.m_TilePersoList.GetAt(i))==((CTilePerso*) theApp.m_TilePersoList.GetAt(i))->m_Quantity )
								dcMemory.SetTextColor( RGB(0,120,0) );
							else
								dcMemory.SetTextColor( RGB(0,0,120) );
						}
						else
						{
							Str.Format( _T("%s (%i/%i)"), pTile->GetName(), ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[pTile->m_Type], theApp.m_MaterialNb[pTile->m_Type] );
							if( ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[pTile->m_Type]>theApp.m_MaterialNb[pTile->m_Type] )
								dcMemory.SetTextColor( RGB(200,0,0) );
							else if( ((CHeroscapeEditorDoc*) m_pDoc)->m_MaterialNb[pTile->m_Type]==theApp.m_MaterialNb[pTile->m_Type] )
								dcMemory.SetTextColor( RGB(0,120,0) );
							else
								dcMemory.SetTextColor( RGB(0,0,120) );
						}
					}
				}
			}
			else
			{
				if( theApp.m_MaterialNb[pTile->m_Type]>=500 )
				{
					Str = pTile->GetName();
					dcMemory.SetTextColor( RGB(0,0,120) );
				}
				else
				{
					if( pTile->m_Type==TYPE_CASTLE*1000+404 )
						Str.Format( _T("%s (%i)"), pTile->GetName(), theApp.m_MaterialNb[TYPE_CASTLE*1000+401] );
					else if( pTile->m_Type==TYPE_WATER*1000+2 )
						Str.Format( _T("%s (%i)"), pTile->GetName(), theApp.m_MaterialNb[TYPE_WATER*1000+1] );
					else
					{
						if( pTile->m_Type==TYPE_PERSONAL*1000 )
							Str.Format( _T("%s (%i)"), pTile->GetName(), ((CTilePerso*) theApp.m_TilePersoList.GetAt(i))->m_Quantity );
						else
							Str.Format( _T("%s (%i)"), pTile->GetName(), theApp.m_MaterialNb[pTile->m_Type] );
					}
					dcMemory.SetTextColor( RGB(0,0,120) );
				}
			}
			dcMemory.DrawText( Str, CRect(0,PosY-GetScrollPos(SB_VERT),Rect.Width(),PosY-GetScrollPos(SB_VERT)+20), DT_CENTER );

			PosY += 30;
		}

		if( m_pCurrentTile!=NULL )
		{
			m_pCurrentTile->DrawSample( &dcMemory, (int) (m_CurrentTilePosition.x-(m_pCurrentTile->m_PixelSizeX*12)/2.0-m_DiffPosTileMouseX*(m_pCurrentTile->m_PixelSizeX*12)), (int) (m_CurrentTilePosition.y-(m_pCurrentTile->m_PixelSizeY*11+3)/2.0-m_DiffPosTileMouseY*(m_pCurrentTile->m_PixelSizeY*11+3)) );
		}

		if( PosY>Rect.bottom )
			SetScrollSizes( MM_TEXT, CSize(1,PosY) );

		GetClientRect( &Rect2 );
	}

	pDC->BitBlt( GetScrollPos( SB_HORZ ), GetScrollPos( SB_VERT ), Rect.right, Rect.bottom, &dcMemory, 0, 0, SRCCOPY );
}

// Add an object to the list
//
void CListCtrlObject::AddObject( CTile* pTile )
{
	m_ObjectList.Add( pTile );

	ComputeScrollSize();
}

// Remove all the objects in this tab list
//
void CListCtrlObject::RemoveAllObjects()
{
	for( int i=0; i<m_ObjectList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_ObjectList.GetAt( i );
		delete pTile;
	}
	m_ObjectList.RemoveAll();

	ComputeScrollSize();
}

// Compute the scroll size
//
void CListCtrlObject::ComputeScrollSize()
{
	int cx = 1;
	int cy = 0;

	for( int i=0; i<m_ObjectList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) m_ObjectList.GetAt( i );
		if( pTile->m_PixelSizeX>cx )
			cx = pTile->m_PixelSizeX;
		cy += pTile->m_PixelSizeY;
	}

	if( cy==0 )
		cy = 1;

	SetScrollSizes( MM_TEXT, CSize(cx, cy) );
}

// The user click to take an object
//
void CListCtrlObject::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Choose the object under mouse
	CRect Rect;
	GetClientRect( &Rect );
	int PosY = 15-GetScrollPos(SB_VERT);

	int i;
	CTile* pTile = NULL;
	for( i=0; i<m_ObjectList.GetCount(); i++ )
	{
		pTile = (CTile*) m_ObjectList.GetAt( i );

		if( point.y>PosY && point.y<PosY+pTile->m_PixelSizeY*11+25 )
			break;

		PosY += pTile->m_PixelSizeY*11+32;
	}

	if( i<m_ObjectList.GetCount() )
	{
		m_pCurrentTile = pTile->GetCopy();
		m_pCurrentTile->m_IsSelected = true;

		m_DiffPosTileMouseX = (point.x-Rect.Width()/2.0)/(pTile->m_PixelSizeX*12);
		m_DiffPosTileMouseY = (point.y-PosY-5-(pTile->m_PixelSizeY*11+3)/2.0)/(pTile->m_PixelSizeY*11+3);

		theApp.UnselectAllTile();

		// Set my drag mode
		m_Mode = MODE_DRAG;

		SetCapture();

		m_LastUsedTileType = m_pCurrentTile->m_Type;
		if( m_LastUsedTileType/1000==TYPE_STARTAREA )
			m_LastStartAreaColor = m_pCurrentTile->m_TileColor;
		else if( m_LastUsedTileType/1000==TYPE_PERSONAL )
		{
			m_LastPersonalTileColor = m_pCurrentTile->m_TileColor;
			m_LastPersonalTileTexture = m_pCurrentTile->m_PersonalTexture;
			m_LastPersonalTileTextureSide = m_pCurrentTile->m_PersonalTextureSide;
			m_LastPersonalTileChar = ((CTilePerso*) m_pCurrentTile)->m_Char;
			m_LastPersonalTileName = ((CTilePerso*) m_pCurrentTile)->m_Name;
			m_LastPersonalNbTile = m_pCurrentTile->m_NbTile;
		}
		else if( m_LastUsedTileType/1000==TYPE_FIGURE )
		{
			m_LastFigureFile = ((CTileFigure*) m_pCurrentTile)->m_FigureFile;
			m_LastFigureName = ((CTileFigure*) m_pCurrentTile)->m_FigureName;
			m_LastFigureNbTile = ((CTileFigure*) m_pCurrentTile)->m_NbTile;
		}

		((CMainFrame*) theApp.m_pMainWnd)->SetCurrentTile( m_pCurrentTile->GetName() );

		RedrawWindow();
	}

	// Call the base class
	CScrollView::OnLButtonDown(nFlags, point);
}

// When the mouse is moved
//
void CListCtrlObject::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT Point2 = point;
	ClientToScreen( &Point2 );
	// Inform each view that a tile is moved
	if( m_pCurrentTile!=NULL )
		theApp.InformEachViewTileMoving( m_pCurrentTile, Point2, m_DiffPosTileMouseX, m_DiffPosTileMouseY );

	m_CurrentTilePosition.x = point.x;
	m_CurrentTilePosition.y = point.y;

	RedrawWindow();

	// Call the base class
	CScrollView::OnMouseMove(nFlags, point);
}

// The user release the button
//
void CListCtrlObject::OnLButtonUp(UINT nFlags, CPoint point)
{
	if( m_pCurrentTile!=NULL )
	{
		POINT Point2 = point;
		ClientToScreen( &Point2 );
	
		// Add this tile to a document if the user launch it on a view
		if( !theApp.InformEachViewTileLaunch( m_pCurrentTile, Point2, m_DiffPosTileMouseX, m_DiffPosTileMouseY ) )
			delete m_pCurrentTile;

		m_pCurrentTile=NULL;
	}

	m_Mode = MODE_NULL;

	ReleaseCapture();

	// Call the base class
	CScrollView::OnLButtonUp(nFlags, point);
}

// the windows is resized
//
void CListCtrlObject::OnSize(UINT nType, int cx, int cy)
{
	// Call the base class
	SetRedraw( FALSE );
	CScrollView::OnSize(nType, cx, cy);
	SetScrollSizes(MM_TEXT, CSize(1,1) );
	SetRedraw( TRUE );

	CDC* pDC = GetDC();

	// Create the bitmaps
	if( m_pBitmapMemory )
		delete m_pBitmapMemory;
	m_pBitmapMemory = new CBitmap();
	m_pBitmapMemory->CreateCompatibleBitmap( pDC, cx, cy );

	ReleaseDC( pDC );

	//TRACE("Size list ctrl object : %i\n", cx );

	RedrawWindow();
}

// Don't need to erase because double buffering
//
BOOL CListCtrlObject::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}

// Set the current document
//
void CListCtrlObject::SetCurrentDoc( void* pDoc )
{
	m_pDoc = pDoc;
	RedrawWindow();
}
