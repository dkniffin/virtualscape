// GameActionBar.cpp : implementation file
//

#include "StdAfx.h"

#include "GameActionBar.h"

#include "Resource.h"

// The constructor
//
CGameActionBar::CGameActionBar()
{
}

// The destructor
//
CGameActionBar::~CGameActionBar()
{
}

// The windows messaging
BEGIN_MESSAGE_MAP(CGameActionBar, CSizingControlBar)
    //{{AFX_MSG_MAP(CGameActionBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_MOVE()
END_MESSAGE_MAP()

// At the creation
//
int CGameActionBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

	if( !m_wndIcon.Create(NULL,SS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100), this, 2))
		return -1;
	m_bmp.LoadBitmap(IDB_GAMEACTIONVIEW);
	m_wndIcon.SetBitmap( (HBITMAP) m_bmp );

	CString	StrResource;
	StrResource.LoadString( IDS_GAMEACTIONVIEW );
	if( !m_wndText.Create(StrResource,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), this, 2))
		return -1;

    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
            return -1;

	m_wndText.SetFont(&m_font);

	// Define the minimum size of this window
	m_szMin.cx = 200;
	m_szMin.cy = 100;

	// Create the game chat form view
	m_GameActionFV.Create( this );

    return 0;
}

// If modification UI
//
void CGameActionBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);

	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

// When we resize the window
//
void CGameActionBar::OnSize(UINT nType, int cx, int cy) 
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
	m_GameActionFV.OnSize( nType, rc.Width(), rc.Height()-20 );
}

// When the bar move
//
void CGameActionBar::OnMove(int x, int y)
{
	// Call the base class
	CSizingControlBar::OnMove(x, y);

	m_GameActionFV.OnMove( x, y );
}

// Reset all the actions
//
void CGameActionBar::ResetAction()
{
	m_GameActionFV.ResetAction();
}
