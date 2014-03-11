// ListCtrlArmy.cpp : implementation file
//

#include "StdAfx.h"

#include "ArmyCard.h"
#include "HeroscapeEditor.h"
#include "ListCtrlArmy.h"

// CListCtrlPlayer

IMPLEMENT_DYNCREATE(CListCtrlArmy, CScrollView)

// The constructor
//
CListCtrlArmy::CListCtrlArmy()
{
	// No Scroll
	SetScrollSizes(MM_TEXT, CSize(1,1) );
	// No bitmap
	m_pBitmapMemory = NULL;
	// No document
	m_pArmyList = NULL;
	// No selected index
	m_SelectedIndex = -1;
}

// The destructor
//
CListCtrlArmy::~CListCtrlArmy()
{
	if( m_pBitmapMemory )
		delete m_pBitmapMemory;
}

BEGIN_MESSAGE_MAP(CListCtrlArmy, CScrollView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CListCtrlPlayer drawing
//
void CListCtrlArmy::OnDraw(CDC* pDC)
{
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

		int PosX = 5;
		int PosY = 5;
		int Cy = 1;

		if( m_pArmyList!=NULL )
		{
			for( int i=0; i<m_pArmyList->GetCount(); i++ )
			{
				if( i%2==0 )
					dcMemory.FillSolidRect( PosX-GetScrollPos(SB_HORZ), PosY, 200, 170, RGB(255,255,230) );
				else
					dcMemory.FillSolidRect( PosX-GetScrollPos(SB_HORZ), PosY, 200, 170, RGB(255,230,255) );

				CArmyCard* pArmyCard = (CArmyCard*) m_pArmyList->GetAt( i );

				pArmyCard->Draw( &dcMemory, PosX-GetScrollPos(SB_HORZ), PosY, 200, 170, m_SelectedIndex==i, 0 );

				PosX += 200+10;
			}

			if( PosX>Rect.right )
				SetScrollSizes( MM_TEXT, CSize(PosX,Cy) );
		}

		GetClientRect( &Rect2 );
	}

	pDC->BitBlt( GetScrollPos( SB_HORZ ), GetScrollPos( SB_VERT ), Rect.right, Rect.bottom, &dcMemory, 0, 0, SRCCOPY );
}

// Compute the scroll size
//
void CListCtrlArmy::ComputeScrollSize()
{
	int cx = 1;
	int cy = 1;

	if( m_pArmyList!=NULL )
		cx = m_pArmyList->GetCount()*210;

	SetScrollSizes( MM_TEXT, CSize(cx, cy) );
}

// the windows is resized
//
void CListCtrlArmy::OnSize(UINT nType, int cx, int cy)
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

	RedrawWindow();
}

// Don't need to erase because double buffering
//
BOOL CListCtrlArmy::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}

// Set the army list
//
void CListCtrlArmy::SetArmyList( CPtrArray* pArmyList )
{
	m_pArmyList = pArmyList;

	ComputeScrollSize();

	RedrawWindow();
}

int CListCtrlArmy::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO : ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels

	return 1; //CScrollView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

// The user want select an army
//
void CListCtrlArmy::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_SelectedIndex = (point.x+GetScrollPos(SB_HORZ)-5)/210;
	if( m_SelectedIndex>m_pArmyList->GetCount()-1 )
		m_SelectedIndex = -1;
	Invalidate();

	// Call the base class
	CScrollView::OnLButtonDown(nFlags, point);
}
