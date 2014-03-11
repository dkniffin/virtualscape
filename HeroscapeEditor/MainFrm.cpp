// MainFrm.cpp : implémentation de la classe CMainFrame
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "MainFrm.h"

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_AFFICHAGE_BARRE2D, &CMainFrame::OnAffichageBarre2d)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_BARRE2D, &CMainFrame::OnUpdateAffichageBarre2d)
	ON_COMMAND(ID_AFFICHAGE_BARREOBJET, &CMainFrame::OnAffichageBarreobjet)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_BARREOBJET, &CMainFrame::OnUpdateAffichageBarreobjet)
	ON_COMMAND(ID_AFFICHAGE_FENETRE_OBJET, &CMainFrame::OnAffichageFenetreObjet)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_FENETRE_OBJET, &CMainFrame::OnUpdateAffichageFenetreObjet)
	ON_COMMAND(ID_AFFICHAGE_FENETREINFORMATION, &CMainFrame::OnAffichageFenetreinformation)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_FENETREINFORMATION, &CMainFrame::OnUpdateAffichageFenetreinformation)
	ON_COMMAND(ID_AFFICHAGE_BARRED3D, &CMainFrame::OnAffichageBarred3d)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_BARRED3D, &CMainFrame::OnUpdateAffichageBarred3d)
//	ON_WM_SYSCOMMAND()
//ON_WM_DESTROY()
ON_COMMAND(ID_VIEW_TOOLBAR, &CMainFrame::OnViewToolbar)
ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, &CMainFrame::OnUpdateViewToolbar)
ON_COMMAND(ID_AFFICHAGE_CHAT, &CMainFrame::OnAffichageChat)
ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_CHAT, &CMainFrame::OnUpdateAffichageChat)
ON_COMMAND(ID_AFFICHAGE_WINDOWPLAYER, &CMainFrame::OnAffichageWindowplayer)
ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_WINDOWPLAYER, &CMainFrame::OnUpdateAffichageWindowplayer)
ON_COMMAND(ID_AFFICHAGE_WINDOW_ACTION, &CMainFrame::OnAffichageWindowAction)
ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_WINDOW_ACTION, &CMainFrame::OnUpdateAffichageWindowAction)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,				// indicateur de la ligne d'état
	ID_INDICATOR_CURRENT_TILE,	// Info about current tile (to add if you click on map)
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// The constructor
//
CMainFrame::CMainFrame()
{
	// TODO : ajoutez ici le code d'une initialisation de membre
}

// The destructor
//
CMainFrame::~CMainFrame()
{
}

// This windows is created
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Call the base class
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the general toolbar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Impossible de créer la toolbar générale\n");
		return -1;      // échec de la création
	}

	// Create the 2D view toolbar
	if (!m_wndToolBarView.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(0,0,0,0), AFX_IDW_TOOLBAR+2) || !m_wndToolBarView.LoadToolBar(IDR_TOOLBARVIEW))
	{
		TRACE0("Impossible de créer la toolbar des vues\n");
		return -1;      // échec de la création
	}

	// Create the 3D view toolbar
	if (!m_wndToolBar3DView.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(0,0,0,0), AFX_IDW_TOOLBAR+4) || !m_wndToolBar3DView.LoadToolBar(IDR_TOOLBAR3DVIEW))
	{
		TRACE0("Impossible de créer la toolbar des vues 3D\n");
		return -1;      // échec de la création
	}

	// Create the object toolbar
	if (!m_wndToolBarObject.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(0,0,0,0), AFX_IDW_TOOLBAR+3) || !m_wndToolBarObject.LoadToolBar(IDR_TOOLBAROBJECT))
	{
		TRACE0("Impossible de créer la toolbar des objets\n");
		return -1;      // échec de la création
	}

	// Create the game toolbar
	if (!m_wndToolBarGame.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(0,0,0,0), AFX_IDW_TOOLBAR+5) || !m_wndToolBarGame.LoadToolBar(IDR_TOOLBARGAME))
	{
		TRACE0("Impossible de créer la toolbar de jeu\n");
		return -1;      // échec de la création
	}

	// Create the status bar
	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Impossible de créer la barre d'état\n");
		return -1;      // échec de la création
	}

	// Set pane info size for current tile
	m_wndStatusBar.SetPaneInfo( 1, -1, SBPS_NORMAL, 300 );

	// Dock the general toolbar
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Change color and dock general toolbar
	m_BmpGeneralBar.LoadBitmap( IDB_GENERALTOOLBAR );
	unsigned char* pBits = (unsigned char*) malloc( 32*192*4 );
	m_BmpGeneralBar.GetBitmapBits( 32*192*4, pBits );
	DWORD ColorFace = ::GetSysColor(COLOR_BTNFACE);
	for( int i=0; i<32*192; i++ )
	{
		if( pBits[i*4]==255 && pBits[i*4+1]==0 && pBits[i*4+2]==255 )
		{
			pBits[i*4] = GetBValue(ColorFace);
			pBits[i*4+1] = GetGValue(ColorFace);
			pBits[i*4+2] = GetRValue(ColorFace);
		}
	}
	m_BmpGeneralBar.SetBitmapBits( 32*192*4, pBits );
	free( pBits );
	m_wndToolBar.SetBitmap( (HBITMAP) m_BmpGeneralBar.GetSafeHandle() );
	m_wndToolBar.SetSizes( CSize(39,38), CSize(32,32) );
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	CString Str;
	Str.LoadString( IDS_GENERALTOOLBARTITLE );
	m_wndToolBar.SetWindowText( Str );
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Change color and dock 2D view toolbar
	m_BmpViewBar.LoadBitmap( IDB_VIEWTOOLBAR );
	pBits = (unsigned char*) malloc( 32*224*4 );
	m_BmpViewBar.GetBitmapBits( 32*224*4, pBits );
	for( int i=0; i<32*224; i++ )
	{
		if( pBits[i*4]==255 && pBits[i*4+1]==0 && pBits[i*4+2]==255 )
		{
			pBits[i*4] = GetBValue(ColorFace);
			pBits[i*4+1] = GetGValue(ColorFace);
			pBits[i*4+2] = GetRValue(ColorFace);
		}
	}
	m_BmpViewBar.SetBitmapBits( 32*224*4, pBits );
	free( pBits );
	m_wndToolBarView.SetBitmap( (HBITMAP) m_BmpViewBar.GetSafeHandle() );
	m_wndToolBarView.SetSizes( CSize(39,38), CSize(32,32) );
	m_wndToolBarView.EnableDocking(CBRS_ALIGN_ANY);
	Str.LoadString( IDS_VIEW2DTOOLBARTITLE );
	m_wndToolBarView.SetWindowText( Str );
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarView);

	// Change color and dock 3D view toolbar
	m_Bmp3DViewBar.LoadBitmap( IDB_3DVIEWTOOLBAR );
	pBits = (unsigned char*) malloc( 384*32*4 );
	m_Bmp3DViewBar.GetBitmapBits( 384*32*4, pBits );
	for( int i=0; i<384*32; i++ )
	{
		if( pBits[i*4]==255 && pBits[i*4+1]==0 && pBits[i*4+2]==255 )
		{
			pBits[i*4] = GetBValue(ColorFace);
			pBits[i*4+1] = GetGValue(ColorFace);
			pBits[i*4+2] = GetRValue(ColorFace);
		}
	}
	m_Bmp3DViewBar.SetBitmapBits( 384*32*4, pBits );
	free( pBits );
	m_wndToolBar3DView.SetBitmap( (HBITMAP) m_Bmp3DViewBar.GetSafeHandle() );
	m_wndToolBar3DView.SetSizes( CSize(39,38), CSize(32,32) );
	m_wndToolBar3DView.EnableDocking(CBRS_ALIGN_ANY);
	Str.LoadString( IDS_VIEW3DTOOLBARTITLE );
	m_wndToolBar3DView.SetWindowText( Str );
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar3DView);

	// Change color and dock object toolbar
	m_BmpObjectBar.LoadBitmap( IDB_OBJECTTOOLBAR );
	pBits = (unsigned char*) malloc( 32*128*4 );
	m_BmpObjectBar.GetBitmapBits( 32*128*4, pBits );
	for( int i=0; i<32*128; i++ )
	{
		if( pBits[i*4]==255 && pBits[i*4+1]==0 && pBits[i*4+2]==255 )
		{
			pBits[i*4] = GetBValue(ColorFace);
			pBits[i*4+1] = GetGValue(ColorFace);
			pBits[i*4+2] = GetRValue(ColorFace);
		}
	}
	m_BmpObjectBar.SetBitmapBits( 32*128*4, pBits );
	free( pBits );
	m_wndToolBarObject.SetBitmap( (HBITMAP) m_BmpObjectBar.GetSafeHandle() );
	m_wndToolBarObject.SetSizes( CSize(39,38), CSize(32,32) );
	m_wndToolBarObject.EnableDocking(CBRS_ALIGN_ANY);
	Str.LoadString( IDS_OBJECTTOOLBARTITLE );
	m_wndToolBarObject.SetWindowText( Str );
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarObject);

	// Change color and dock game toolbar
	m_BmpGameBar.LoadBitmap( IDB_GAMETOOLBAR );
	pBits = (unsigned char*) malloc( 32*416*4 );
	m_BmpGameBar.GetBitmapBits( 32*416*4, pBits );
	for( int i=0; i<32*416; i++ )
	{
		if( pBits[i*4]==255 && pBits[i*4+1]==0 && pBits[i*4+2]==255 )
		{
			pBits[i*4] = GetBValue(ColorFace);
			pBits[i*4+1] = GetGValue(ColorFace);
			pBits[i*4+2] = GetRValue(ColorFace);
		}
	}
	m_BmpGameBar.SetBitmapBits( 32*416*4, pBits );
	free( pBits );
	m_wndToolBarGame.SetBitmap( (HBITMAP) m_BmpGameBar.GetSafeHandle() );
	m_wndToolBarGame.SetSizes( CSize(39,38), CSize(32,32) );
	m_wndToolBarGame.EnableDocking(CBRS_ALIGN_ANY);
	Str.LoadString( IDS_GAMETOOLBARTITLE );
	m_wndToolBarGame.SetWindowText( Str );
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarGame);

	// The Object Bar
	CString StrResource;
	StrResource.LoadString( IDS_OBJECTWINDOW );
    if (!m_wndObjectBar.Create( StrResource, this, CSize(200, 200), TRUE, 125))
    {
	    TRACE0("Impossible de créer la barre d'objet\n");
        return -1;      // fail to create
    }

	// Dock the object bar
    m_wndObjectBar.SetBarStyle(m_wndObjectBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndObjectBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar( &m_wndObjectBar, AFX_IDW_DOCKBAR_LEFT );

	// The Info Bar
	StrResource.LoadString( IDS_INFOWINDOW );
    if (!m_wndInfoBar.Create( StrResource, this, CSize(160, 80), TRUE, 126))
    {
	    TRACE0("Failed to create info list bar\n");
        return -1;      // fail to create
    }

    m_wndInfoBar.SetBarStyle(m_wndInfoBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndInfoBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar( &m_wndInfoBar, AFX_IDW_DOCKBAR_BOTTOM );

	// The Game chat bar
	StrResource.LoadString( IDS_GAMECHATWINDOW );
    if (!m_wndGameChatBar.Create( StrResource, this, CSize(260, 180), TRUE, 127))
    {
	    TRACE0("Failed to create game chat bar\n");
        return -1;      // fail to create
    }

    m_wndGameChatBar.SetBarStyle(m_wndGameChatBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndGameChatBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar( &m_wndGameChatBar, AFX_IDW_DOCKBAR_BOTTOM );

	// The Game player bar
	StrResource.LoadString( IDS_GAMEPLAYERWINDOW );
    if (!m_wndGamePlayerBar.Create( StrResource, this, CSize(200, 200), TRUE, 128))
    {
	    TRACE0("Failed to create game player bar\n");
        return -1;      // fail to create
    }

    m_wndGamePlayerBar.SetBarStyle(m_wndGamePlayerBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndGamePlayerBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar( &m_wndGamePlayerBar, AFX_IDW_DOCKBAR_LEFT );

	// The Game action bar
	StrResource.LoadString( IDS_GAMEACTIONWINDOW );
    if (!m_wndGameActionBar.Create( StrResource, this, CSize(200, 200), TRUE, 129))
    {
	    TRACE0("Failed to create game action bar\n");
        return -1;      // fail to create
    }

    m_wndGameActionBar.SetBarStyle(m_wndGameActionBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
    m_wndGameActionBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar( &m_wndGameActionBar, AFX_IDW_DOCKBAR_BOTTOM );

	// Load the position of the window
	int PosX = theApp.GetProfileInt( _T("MainWindow"), _T("PosX"), 0);
	int PosY = theApp.GetProfileInt( _T("MainWindow"), _T("PosY"), 0);
	int Width = theApp.GetProfileInt( _T("MainWindow"), _T("Width"), 700);
	int Height = theApp.GetProfileInt( _T("MainWindow"), _T("Height"), 500);
	SetWindowPos( NULL, PosX, PosY, Width, Height, SWP_NOZORDER );
	int ShowState = theApp.GetProfileInt( _T("MainWindow"),_T("State"), SW_SHOWNORMAL );
	ShowWindow( ShowState );

	// Load the favorite position
	LoadBarState(_T("BarState"));
	m_wndObjectBar.LoadState(_T("DockBarState"));
	m_wndInfoBar.LoadState(_T("DockBarState"));
	m_wndGameChatBar.LoadState(_T("DockBarState"));
	m_wndGamePlayerBar.LoadState(_T("DockBarState"));
	m_wndGameActionBar.LoadState(_T("DockBarState"));

	// Now hide all the unusefull windows
	ShowControlBar( &m_wndGameChatBar, FALSE, FALSE );
	ShowControlBar( &m_wndGamePlayerBar, FALSE, FALSE );
	ShowControlBar( &m_wndGameActionBar, FALSE, FALSE );
	ShowControlBar( &m_wndToolBarGame, FALSE, FALSE );

	RecalcLayout();

	CRect Rect;
	m_wndObjectBar.GetWindowRect( &Rect );
	if( m_wndObjectBar.IsFloating() )
	{
		Rect.right = Rect.left+m_wndObjectBar.m_szFloat.cx;
		Rect.bottom = Rect.top+m_wndObjectBar.m_szFloat.cy;
		m_wndObjectBar.GetParentFrame()->SetWindowPos( NULL, 0, 0, m_wndObjectBar.m_szFloat.cx, m_wndObjectBar.m_szFloat.cy, SWP_NOZORDER|SWP_NOMOVE);
		m_wndObjectBar.RedrawWindow();
	}
	m_wndObjectBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );
	m_wndObjectBar.m_ObjectFV.Init();

	m_wndInfoBar.GetWindowRect( &Rect );
	if( m_wndInfoBar.IsFloating() )
	{
		Rect.right = Rect.left+m_wndInfoBar.m_szFloat.cx;
		Rect.bottom = Rect.top+m_wndInfoBar.m_szFloat.cy;
		m_wndInfoBar.GetParentFrame()->SetWindowPos( NULL, 0, 0, m_wndInfoBar.m_szFloat.cx, m_wndInfoBar.m_szFloat.cy, SWP_NOZORDER|SWP_NOMOVE);
		m_wndInfoBar.RedrawWindow();
	}
	m_wndInfoBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	m_wndGameChatBar.GetWindowRect( &Rect );
	m_wndGameChatBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	m_wndGamePlayerBar.GetWindowRect( &Rect );
	m_wndGamePlayerBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	m_wndGameActionBar.GetWindowRect( &Rect );
	m_wndGameActionBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	return 0;
}

// Before the window is created
//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO : changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return TRUE;
}

// Set the text in the status bar
//
void CMainFrame::SetCurrentTile( CString Str )
{
	m_wndStatusBar.SetPaneText( 1, Str );
}

// When the window is destroy save all the environment
//
BOOL CMainFrame::DestroyWindow()
{
	if( theApp.m_IsInGameMode )
		theApp.ExitGameMode();

	// Save bar position
	SaveBarState(_T("BarState"));
	m_wndObjectBar.SaveState(_T("DockBarState"));
	m_wndInfoBar.SaveState(_T("DockBarState"));

	// Save position of the main window;
	WINDOWPLACEMENT wndpl;
	GetWindowPlacement( &wndpl );
	if( wndpl.rcNormalPosition.left>-30000 )
		theApp.WriteProfileInt( _T("MainWindow"),_T("PosX"),wndpl.rcNormalPosition.left);
	if( wndpl.rcNormalPosition.top>-30000 )
		theApp.WriteProfileInt( _T("MainWindow"),_T("PosY"),wndpl.rcNormalPosition.top);
	theApp.WriteProfileInt( _T("MainWindow"),_T("Width"),wndpl.rcNormalPosition.right-wndpl.rcNormalPosition.left);
	theApp.WriteProfileInt( _T("MainWindow"),_T("Height"),wndpl.rcNormalPosition.bottom-wndpl.rcNormalPosition.top);
	theApp.WriteProfileInt( _T("MainWindow"),_T("State"),wndpl.showCmd);

	return CMDIFrameWnd::DestroyWindow();
}

// When the client is created
//
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (CreateClient(lpcs, NULL))
	{
		m_wndMdiClient.SubclassWindow(m_hWndMDIClient);
		m_wndMdiClient.SetBitmap(IDB_BACKGROUND);
		return TRUE;
	}
	else
		return FALSE;
}

// Display or hide the 2D view toolbar
//
void CMainFrame::OnAffichageBarre2d()
{
	if( m_wndToolBarView.IsWindowVisible() )
		ShowControlBar( &m_wndToolBarView, FALSE, FALSE );
	else
		ShowControlBar( &m_wndToolBarView, TRUE, FALSE );

	RecalcLayout();
}

// check if the 2d view toolbar is visible
//
void CMainFrame::OnUpdateAffichageBarre2d(CCmdUI *pCmdUI)
{
	if( theApp.m_IsInGameMode )
		pCmdUI->Enable(false);
	if( m_wndToolBarView.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// Display or hide the object toolbar
//
void CMainFrame::OnAffichageBarreobjet()
{
	if( m_wndToolBarObject.IsWindowVisible() )
	{
		ShowControlBar( &m_wndToolBarObject, FALSE, FALSE );
		RecalcLayout();
	}
	else
	{
		ShowControlBar( &m_wndToolBarObject, TRUE, FALSE );
		RecalcLayout();
	}
}

// Check if the object toolbar is visible
//
void CMainFrame::OnUpdateAffichageBarreobjet(CCmdUI *pCmdUI)
{
	if( theApp.m_IsInGameMode )
		pCmdUI->Enable(false);
	if( m_wndToolBarObject.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// Display or hide the object window
//
void CMainFrame::OnAffichageFenetreObjet()
{
	if( m_wndObjectBar.IsWindowVisible() )
		ShowControlBar( &m_wndObjectBar, false, false );
	else
		ShowControlBar( &m_wndObjectBar, true, false );
	RecalcLayout();
}

// To know if the object window is displayed or not
//
void CMainFrame::OnUpdateAffichageFenetreObjet(CCmdUI *pCmdUI)
{
	if( theApp.m_IsInGameMode )
		pCmdUI->Enable(false);
	pCmdUI->SetCheck( m_wndObjectBar.IsWindowVisible()?1:0 );
}

// Display or hide the information window
//
void CMainFrame::OnAffichageFenetreinformation()
{
	if( m_wndInfoBar.IsWindowVisible() )
		ShowControlBar( &m_wndInfoBar, false, false );
	else
		ShowControlBar( &m_wndInfoBar, true, false );
	RecalcLayout();
}

// To know if the information window is displayed or not
//
void CMainFrame::OnUpdateAffichageFenetreinformation(CCmdUI *pCmdUI)
{
	if( theApp.m_IsInGameMode )
		pCmdUI->Enable(false);
	pCmdUI->SetCheck( m_wndInfoBar.IsWindowVisible()?1:0 );
}

// Display or hide the 3d view toolbar
//
void CMainFrame::OnAffichageBarred3d()
{
	if( m_wndToolBar3DView.IsWindowVisible() )
	{
		ShowControlBar( &m_wndToolBar3DView, FALSE, FALSE );
		RecalcLayout();
	}
	else
	{
		ShowControlBar( &m_wndToolBar3DView, TRUE, FALSE );
		RecalcLayout();
	}
}

// Check if the 3d view toolbar is visible
//
void CMainFrame::OnUpdateAffichageBarred3d(CCmdUI *pCmdUI)
{
	if( theApp.m_IsInGameMode )
		pCmdUI->Enable(false);
	if( m_wndToolBar3DView.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// Enter in game mode
//
void CMainFrame::EnterGameMode()
{
	// Save the windows state
	m_IsVisibleToolBar = m_wndToolBar.IsVisible()?true:false;
	m_IsVisibleToolBarObject = m_wndToolBarObject.IsVisible()?true:false;
	m_IsVisibleToolBar3D = m_wndToolBar3DView.IsVisible()?true:false;
	m_IsVisibleToolBar2D = m_wndToolBarView.IsVisible()?true:false;
	m_IsVisibleObjectBar = m_wndObjectBar.IsWindowVisible()?true:false;
	m_IsVisibleInfoBar = m_wndInfoBar.IsWindowVisible()?true:false;

	// Now hide all the unusefull windows
	ShowControlBar( &m_wndToolBar, FALSE, FALSE );
	ShowControlBar( &m_wndToolBarObject, FALSE, FALSE );
	ShowControlBar( &m_wndToolBar3DView, FALSE, FALSE );
	ShowControlBar( &m_wndToolBarView, FALSE, FALSE );
	ShowControlBar( &m_wndObjectBar, FALSE, FALSE );
	ShowControlBar( &m_wndInfoBar, FALSE, FALSE );
	
	// Now show all the usefull windows
	ShowControlBar( &m_wndGameChatBar, TRUE, FALSE );
	ShowControlBar( &m_wndGamePlayerBar, TRUE, FALSE );
	ShowControlBar( &m_wndGameActionBar, TRUE, FALSE );
	ShowControlBar( &m_wndToolBarGame, TRUE, FALSE );

	CRect Rect;
	m_wndGameChatBar.GetWindowRect( &Rect );
	m_wndGameChatBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	m_wndGamePlayerBar.GetWindowRect( &Rect );
	m_wndGamePlayerBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	m_wndGameActionBar.GetWindowRect( &Rect );
	m_wndGameActionBar.PostMessage( WM_SIZE, SIZE_RESTORED, MAKELPARAM(Rect.Width(),Rect.Height()) );

	RecalcLayout();
}

// Exit the game mode
//
void CMainFrame::ExitGameMode()
{
	m_wndGameChatBar.SaveState(_T("DockBarState"));
	m_wndGamePlayerBar.SaveState(_T("DockBarState"));
	m_wndGameActionBar.SaveState(_T("DockBarState"));

	ShowControlBar( &m_wndToolBar, m_IsVisibleToolBar, FALSE );
	ShowControlBar( &m_wndToolBarObject, m_IsVisibleToolBarObject, FALSE );
	ShowControlBar( &m_wndToolBar3DView, m_IsVisibleToolBar3D, FALSE );
	ShowControlBar( &m_wndToolBarView, m_IsVisibleToolBar2D, FALSE );
	ShowControlBar( &m_wndObjectBar, m_IsVisibleObjectBar, FALSE );
	ShowControlBar( &m_wndInfoBar, m_IsVisibleInfoBar, FALSE );
	
	// Now hide all the unusefull windows
	ShowControlBar( &m_wndGameChatBar, FALSE, FALSE );
	ShowControlBar( &m_wndGamePlayerBar, FALSE, FALSE );
	ShowControlBar( &m_wndGameActionBar, FALSE, FALSE );
	ShowControlBar( &m_wndToolBarGame, FALSE, FALSE );

	RecalcLayout();
	RedrawWindow();
}

// Hide or show the general toolbar
//
void CMainFrame::OnViewToolbar()
{
	if( m_wndToolBar.IsWindowVisible() )
		ShowControlBar( &m_wndToolBar, FALSE, FALSE );
	else
		ShowControlBar( &m_wndToolBar, TRUE, FALSE );

	RecalcLayout();
}

// To know if the tool bar menu item must be checked or not
//
void CMainFrame::OnUpdateViewToolbar(CCmdUI *pCmdUI)
{
	if( theApp.m_IsInGameMode )
		pCmdUI->Enable(false);
	if( m_wndToolBar.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// The user want show or hide the chat window
//
void CMainFrame::OnAffichageChat()
{
	if( m_wndGameChatBar.IsWindowVisible() )
		ShowControlBar( &m_wndGameChatBar, FALSE, FALSE );
	else
		ShowControlBar( &m_wndGameChatBar, TRUE, FALSE );

	RecalcLayout();
}

// To know if the chat window is displayed or not
//
void CMainFrame::OnUpdateAffichageChat(CCmdUI *pCmdUI)
{
	if( m_wndGameChatBar.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// The user want show or hide the player window
//
void CMainFrame::OnAffichageWindowplayer()
{
	if( m_wndGamePlayerBar.IsWindowVisible() )
		ShowControlBar( &m_wndGamePlayerBar, FALSE, FALSE );
	else
		ShowControlBar( &m_wndGamePlayerBar, TRUE, FALSE );

	RecalcLayout();
}

// To know if the player window is displayed or not
//
void CMainFrame::OnUpdateAffichageWindowplayer(CCmdUI *pCmdUI)
{
	if( m_wndGamePlayerBar.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// The user want show or hide the action window
//
void CMainFrame::OnAffichageWindowAction()
{
	if( m_wndGameActionBar.IsWindowVisible() )
		ShowControlBar( &m_wndGameActionBar, FALSE, FALSE );
	else
		ShowControlBar( &m_wndGameActionBar, TRUE, FALSE );

	RecalcLayout();
}

// To know if the action window is displayed or not
//
void CMainFrame::OnUpdateAffichageWindowAction(CCmdUI *pCmdUI)
{
	if( m_wndGameActionBar.IsVisible() )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}
