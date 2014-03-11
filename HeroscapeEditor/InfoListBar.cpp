// InfoListBar.cpp : implementation file
//

#include "StdAfx.h"

#include "Resource.h"

#include "GlobalIHM.h"
#include "InfoListBar.h"

// The constructor
//
CInfoListBar::CInfoListBar()
{
}

// The destructor
//
CInfoListBar::~CInfoListBar()
{
}

// The windows messaging
BEGIN_MESSAGE_MAP(CInfoListBar, CSizingControlBar)
    //{{AFX_MSG_MAP(CInfoListBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// At the creation
//
int CInfoListBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndMyListCtrl.Create(LVS_REPORT|WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_SINGLESEL|LVS_OWNERDRAWFIXED,CRect(0,0,0,0), this, 30003))
        return -1;

	if( !m_wndIcon.Create(NULL,SS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(0,0,110,100), this, 2))
		return -1;
	m_bmp.LoadBitmap(IDB_INFOLIST);
	m_wndIcon.SetBitmap( (HBITMAP) m_bmp );

	CString StrResource;
	StrResource.LoadString( IDS_INFOBAR );
	if( !m_wndText.Create( StrResource ,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), this, 3))
		return -1;

    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
            return -1;

    m_wndText.SetFont(&m_font);

	// Define the minimum size of this window
	m_szMin.cx = 110;
	m_szMin.cy = 100;

	m_ImageList.Create( IDB_IMAGELIST_INFO, 16, 3, RGB(255,0,255) );

	m_wndMyListCtrl.SetSpecialList( true );

	m_wndMyListCtrl.SetImageList( &m_ImageList, LVSIL_SMALL );
	CString Str;
	Str.LoadStringW( IDS_INFO_COLUMN );
	CGlobalIHM::CreateColumnListCtrl( &m_wndMyListCtrl, Str );
	LVCOLUMN Column;
	Column.mask = LVCF_FMT;
	Column.fmt = LVCFMT_CENTER;
	m_wndMyListCtrl.SetColumn( 1, &Column );

    return 0;
}

// If modification UI
//
void CInfoListBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);

	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

// When we resize the window
//
void CInfoListBar::OnSize(UINT nType, int cx, int cy) 
{
    CSizingControlBar::OnSize(nType, cx, cy);

    CRect rc;

    GetClientRect(rc);
	rc.right = rc.left+16;
	rc.bottom = rc.top+13;
	m_wndIcon.MoveWindow(rc);

    GetClientRect(rc);
	rc.bottom = rc.top+15;
	rc.left += 20;
	m_wndText.MoveWindow(rc);
	m_wndText.RedrawWindow();

    GetClientRect(rc);
	rc.top += 18;
    m_wndMyListCtrl.MoveWindow(rc);
}

// Get the tree control
//
CListCtrl* CInfoListBar::GetListCtrl()
{
	return &m_wndMyListCtrl;
}

// When we receive notification
//
BOOL CInfoListBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// If the notification is in the tree control
	if( ((NMHDR*) lParam)->idFrom == (UINT) m_wndMyListCtrl.GetDlgCtrlID() )
	{
		switch( ((NMHDR*) lParam)->code )
		{
		case NM_RCLICK:
			OnListRightClick();
			// Call the base class
			//return CSizingControlBar::OnNotify(wParam, lParam, pResult);
			return true;
		case NM_CLICK:
			OnListLeftClick();
			// Call the base class
			return CSizingControlBar::OnNotify(wParam, lParam, pResult);
		case NM_DBLCLK:
			OnListDblClick();
			return true;
		case TVN_KEYDOWN:
			OnKeyDown( ((LPNMLISTVIEW) lParam)->iItem );
			// Call the base class
			return CSizingControlBar::OnNotify(wParam, lParam, pResult);
		case TVN_SELCHANGED:
			OnSelChanged( (NMLISTVIEW*) lParam );
			return CSizingControlBar::OnNotify(wParam, lParam, pResult);
			break;
		default:
			// Call the base class
			// TRACE("notif : %i\n", ((NMHDR*) lParam)->code );
			return CSizingControlBar::OnNotify(wParam, lParam, pResult);
		}
	}
	else
	{
		// Call the base class
		return CSizingControlBar::OnNotify(wParam, lParam, pResult);
	}
	
}

// The selection has changed
//
void CInfoListBar::OnSelChanged( NMLISTVIEW* pnmlv )
{
}

// The user clic on an item
//
void CInfoListBar::OnKeyDown( int iItem )
{
}

// When the user right clic on the list
//
void CInfoListBar::OnListRightClick()
{
	// Retreive the item under the mouse
	POINT point;
	POINT point2;
	GetCursorPos(&point);
	GetCursorPos(&point2);
	m_wndMyListCtrl.ScreenToClient(&point);
	UINT flags;
	int item = m_wndMyListCtrl.HitTest( point, &flags );
	CString StrResource;
	if( item!=-1 )
	{
	}
	else
	{
	}
}

// When the user left clic on the list
//
void CInfoListBar::OnListLeftClick()
{
/*	// Retreive the item under the mouse
	POINT point;
	GetCursorPos(&point);
	m_wndSpecialListCtrl.ScreenToClient(&point);
	UINT flags;
	int item = m_wndSpecialListCtrl.HitTest( point, &flags );
	// Select the item under the mouse
	m_wndSpecialListCtrl.SelectItem(item);
	// Change the visibility of the layer if necessary
	if( item != NULL )
	{
	}
*/
}

// When we reveive a command
//
BOOL CInfoListBar::OnCommand(WPARAM wParam, LPARAM lParam) 
{
/*	if( HIWORD(wParam)==0 )
	{
		switch( LOWORD(wParam) )
		{
		}
	}
*/
	// Call the base class
	return CSizingControlBar::OnCommand(wParam, lParam);
}

// When the user move the mouse
//
void CInfoListBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Call the base class
	CSizingControlBar::OnMouseMove(nFlags, point);
}

// When the user release the mouse button
//
void CInfoListBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// Call the base class
	CSizingControlBar::OnLButtonUp(nFlags, point);
}

// When the user double clic on the list
//
void CInfoListBar::OnListDblClick()
{
	// Retreive the item under the mouse
	POINT point;
	GetCursorPos(&point);
	m_wndMyListCtrl.ScreenToClient(&point);
	UINT flags;
	int item = m_wndMyListCtrl.HitTest( point, &flags );
	// Select the item under the mouse
	//m_wndMyListCtrl.SelectItem(item);
	if( item != -1 )
	{
	}
}
