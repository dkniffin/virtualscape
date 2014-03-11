// ObjectBar.cpp : implementation file
//

#include "stdafx.h"
#include "ObjectBar.h"

#include "Resource.h"

// The constructor
//
CObjectBar::CObjectBar()
{
}

// The destructor
//
CObjectBar::~CObjectBar()
{
}

// The windows messaging
BEGIN_MESSAGE_MAP(CObjectBar, CSizingControlBar)
    //{{AFX_MSG_MAP(CObjectBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_MOVE()
END_MESSAGE_MAP()

// At the creation
//
int CObjectBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

	if( !m_wndIcon.Create(NULL,SS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100), this, 2))
		return -1;
	m_bmp.LoadBitmap(IDB_OBJECTVIEW);
	m_wndIcon.SetBitmap( (HBITMAP) m_bmp );

	CString	StrResource;
	StrResource.LoadString( IDS_OBJECT );
	if( !m_wndText.Create(StrResource,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), this, 2))
		return -1;

    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
            return -1;

	m_wndText.SetFont(&m_font);

	// Define the minimum size of this window
	m_szMin.cx = 200;
	m_szMin.cy = 200;

	// Create the Info form view
	m_ObjectFV.Create( this );

    return 0;
}

// If modification UI
//
void CObjectBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);

	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

// When we resize the window
//
void CObjectBar::OnSize(UINT nType, int cx, int cy) 
{
	// Call the base class
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
	m_ObjectFV.OnSize( nType, rc.Width(), rc.Height()-20 );

	TRACE("Size object bar : %i, %i %i\n", nType, rc.Width(), rc.Height() );
}

// When the bar move
//
void CObjectBar::OnMove(int x, int y)
{
	// Call the base class
	CSizingControlBar::OnMove(x, y);

	m_ObjectFV.OnMove( x, y );
}

// Set the current document
//
void CObjectBar::SetCurrentDoc( void* pDoc )
{
	m_ObjectFV.SetCurrentDoc( pDoc );
}

// Redraw the object control
//
void CObjectBar::RedrawObjectCtrl()
{
	m_ObjectFV.RedrawObjectCtrl();
}
