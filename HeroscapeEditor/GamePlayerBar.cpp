// GamePlayerBar.cpp : implementation file
//

#include "StdAfx.h"

#include "GamePlayerBar.h"

#include "Resource.h"

// The constructor
//
CGamePlayerBar::CGamePlayerBar()
{
	m_pListCtrlPlayer = NULL;
}

// The destructor
//
CGamePlayerBar::~CGamePlayerBar()
{
}

// The windows messaging
BEGIN_MESSAGE_MAP(CGamePlayerBar, CSizingControlBar)
    //{{AFX_MSG_MAP(CGamePlayerBar)
    ON_WM_CREATE()
    ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_MOVE()
END_MESSAGE_MAP()

// At the creation
//
int CGamePlayerBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

	if( !m_wndIcon.Create(NULL,SS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100), this, 2))
		return -1;
	m_bmp.LoadBitmap(IDB_GAMEPLAYERVIEW);
	m_wndIcon.SetBitmap( (HBITMAP) m_bmp );

	CString	StrResource;
	StrResource.LoadString( IDS_GAMEPLAYERVIEW );
	if( !m_wndText.Create(StrResource,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0), this, 2))
		return -1;

    if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
            return -1;

	m_wndText.SetFont(&m_font);

	m_pListCtrlPlayer = new CListCtrlPlayer;
    if (!m_pListCtrlPlayer->Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,CRect(0,20,1000,1000),this, 30008))
        return -1;

	// Define the minimum size of this window
	m_szMin.cx = 212;
	m_szMin.cy = 200;

    return 0;
}

// If modification UI
//
void CGamePlayerBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CSizingControlBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);

	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

// When we resize the window
//
void CGamePlayerBar::OnSize(UINT nType, int cx, int cy) 
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
	m_pListCtrlPlayer->SetWindowPos( NULL, 0, 20, cx-10, cy-20, SWP_NOZORDER|SWP_NOACTIVATE );
}

// When the bar move
//
void CGamePlayerBar::OnMove(int x, int y)
{
	// Call the base class
	CSizingControlBar::OnMove(x, y);
}

