// ListCtrlPlayer.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "ListCtrlPlayer.h"

// CListCtrlPlayer

IMPLEMENT_DYNCREATE(CListCtrlPlayer, CScrollView)

// The constructor
//
CListCtrlPlayer::CListCtrlPlayer()
{
	// No Scroll
	SetScrollSizes(MM_TEXT, CSize(1,1) );
	// No bitmap
	m_pBitmapMemory = NULL;
	// No document
	m_pGameDoc = NULL;
}

// The destructor
//
CListCtrlPlayer::~CListCtrlPlayer()
{
	if( m_pBitmapMemory )
		delete m_pBitmapMemory;
}

BEGIN_MESSAGE_MAP(CListCtrlPlayer, CScrollView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
//	ON_WM_RBUTTONDBLCLK()
ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CListCtrlPlayer drawing

void CListCtrlPlayer::OnDraw(CDC* pDC)
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
		DWORD ColorFace = RGB(255,255,255);
		dcMemory.FillSolidRect( Rect, ColorFace );

		int PosX = 0;
		int PosY = 0;
		int Cx = 1;

		if( m_pGameDoc!=NULL )
		{
			for( int i=0; i<m_pGameDoc->m_PlayerArray.GetCount(); i++ )
			{
				CPlayer* pPlayer = (CPlayer*) m_pGameDoc->m_PlayerArray.GetAt( i );

				if( i%2==0 )
					dcMemory.FillSolidRect( 0, PosY-GetScrollPos(SB_VERT), 2000, pPlayer->GetStateHeight(), RGB(255,255,230) );
				else
					dcMemory.FillSolidRect( 0, PosY-GetScrollPos(SB_VERT), 2000, pPlayer->GetStateHeight(), RGB(255,230,255) );

				pPlayer->DrawState( &dcMemory, PosX-GetScrollPos(SB_HORZ), PosY-GetScrollPos(SB_VERT), i );

				PosY += pPlayer->GetStateHeight();
				Cx = pPlayer->GetStateWidth();

				PosY += 10;
			}

			if( PosY>Rect.bottom )
				SetScrollSizes( MM_TEXT, CSize(1,PosY) );
		}

		GetClientRect( &Rect2 );
	}

	pDC->BitBlt( GetScrollPos( SB_HORZ ), GetScrollPos( SB_VERT ), Rect.right, Rect.bottom, &dcMemory, 0, 0, SRCCOPY );
}

// Compute the scroll size
//
void CListCtrlPlayer::ComputeScrollSize()
{
	int cx = 1;
	int cy = 0;

	if( m_pGameDoc!=NULL )
	{
		for( int i=0; i<m_pGameDoc->m_PlayerArray.GetCount(); i++ )
		{
			CPlayer* pPlayer = (CPlayer*) m_pGameDoc->m_PlayerArray.GetAt( i );

			cy += pPlayer->GetStateHeight();
			cy += 10;
			cx = pPlayer->GetStateWidth();
		}
	}

	if( cy==0 )
		cy = 1;

	SetScrollSizes( MM_TEXT, CSize(cx, cy) );
}

// the windows is resized
//
void CListCtrlPlayer::OnSize(UINT nType, int cx, int cy)
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

	//TRACE("Size list ctrl player : %i %i\n", cx, cy );

	RedrawWindow();
}

// Don't need to erase because double buffering
//
BOOL CListCtrlPlayer::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}

// Set the current game document
//
void CListCtrlPlayer::SetCurrentGameDoc( CGameDoc* pGameDoc )
{
	m_pGameDoc = pGameDoc;

	ComputeScrollSize();

	RedrawWindow();
}

// When the user right click, display a contextual menu
//
void CListCtrlPlayer::OnRButtonUp(UINT nFlags, CPoint point)
{
	int cy = 0;

	if( m_pGameDoc!=NULL )
	{
		for( int i=0; i<m_pGameDoc->m_PlayerArray.GetCount(); i++ )
		{
			CPlayer* pPlayer = (CPlayer*) m_pGameDoc->m_PlayerArray.GetAt( i );

			cy += 0;
			cy += DLC_ARMY_OFFSET_Y;

			for( int j=0; j<pPlayer->m_ArmyList.GetCount() ; j++ )
			{
				cy += (DLC_ARMY_CARD_HEIGHT+5);
				if( point.y+GetScrollPos( SB_VERT )<cy )
				{
					m_pGameDoc->m_CurrentPlayerIndexCM = i;
					m_pGameDoc->m_CurrentArmyIndexCM = j;

					// Create and display contextual menu
					CString Str;				
					CMenu myMenu;
				
					CPoint Point2 = point;
					ClientToScreen( &Point2 );
					myMenu.CreatePopupMenu();
	
					Str.LoadStringW( IDS_CONTEXTUALMENU_ADDONELIFE );
					myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10001, Str );
					Str.LoadStringW( IDS_CONTEXTUALMENU_REMOVEONELIFE );
					myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10002, Str );
					if( i==m_pGameDoc->m_PlayerIndex )
					{
						// Predicted only for current player
						myMenu.AppendMenuW( MF_SEPARATOR );
						Str.LoadStringW( IDS_CONTEXTUALMENU_ADDPREDICTEDX );
						myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10003, Str );
						Str.LoadStringW( IDS_CONTEXTUALMENU_ADDPREDICTED1 );
						myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10004, Str );
						Str.LoadStringW( IDS_CONTEXTUALMENU_ADDPREDICTED2 );
						myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10005, Str );
						Str.LoadStringW( IDS_CONTEXTUALMENU_ADDPREDICTED3 );
						myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10006, Str );
						Str.LoadStringW( IDS_CONTEXTUALMENU_SHOWPREDICTED );
						myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10007, Str );
						Str.LoadStringW( IDS_CONTEXTUALMENU_REMOVEMARKER );
						myMenu.AppendMenuW( MF_STRING | MF_ENABLED, 10008, Str );
					}
					
					switch( myMenu.TrackPopupMenu( TPM_RETURNCMD, Point2.x, Point2.y, this ) )
					{
					case 10001:
						m_pGameDoc->OnIncrementLife(i,j);
						break;
					case 10002:
						m_pGameDoc->OnDecrementLife(i,j);
						break;
					case 10003:
						m_pGameDoc->OnAddPredictedMarquer(i,j,0);
						break;
					case 10004:
						m_pGameDoc->OnAddPredictedMarquer(i,j,1);
						break;
					case 10005:
						m_pGameDoc->OnAddPredictedMarquer(i,j,2);
						break;
					case 10006:
						m_pGameDoc->OnAddPredictedMarquer(i,j,3);
						break;
					case 10007:
						m_pGameDoc->OnShowPredictedMarquer(i,j);
						break;
					case 10008:
						m_pGameDoc->OnRemoveMarquer(i,j);
						break;
					}

					CScrollView::OnRButtonUp(nFlags, point);
					return;
				}
			}
		}
	}

	CScrollView::OnRButtonUp(nFlags, point);
}
