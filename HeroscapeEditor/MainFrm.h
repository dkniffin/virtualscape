// MainFrm.h : interface de la classe CMainFrame
//

#include "GameActionBar.h"
#include "GameChatBar.h"
#include "GamePlayerBar.h"
#include "InfoListBar.h"
#include "MdiClient.h"
#include "ObjectBar.h"

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)

//************
// The members
//************
protected:
	// The general tool bar
	CToolBar    m_wndToolBar;
	// The 3D view tool bar
	CToolBar	m_wndToolBarView;
	// The 3D view tool bar
	CToolBar	m_wndToolBar3DView;
	// The object tool bar
	CToolBar	m_wndToolBarObject;
	// The game tool bar
	CToolBar	m_wndToolBarGame;
	// The bitmap for the general tool bar
	CBitmap		m_BmpGeneralBar;
	// The bitmap for the view tool bar
	CBitmap		m_BmpViewBar;
	// The bitmap for the 3D view tool bar
	CBitmap		m_Bmp3DViewBar;
	// The bitmap for the object tool bar
	CBitmap		m_BmpObjectBar;
	// The bitmap for the game tool bar
	CBitmap		m_BmpGameBar;
	// To know if the windows was visible when we quit the game mode
	bool		m_IsVisibleToolBar;
	bool		m_IsVisibleToolBarObject;
	bool		m_IsVisibleToolBar3D;
	bool		m_IsVisibleToolBar2D;
	bool		m_IsVisibleObjectBar;
	bool		m_IsVisibleInfoBar;

private:
	// The mdi client
	CMdiClient	m_wndMdiClient;

public:
	// The status bar
	CStatusBar		m_wndStatusBar;
	// The object bar
	CObjectBar		m_wndObjectBar;
	// The info bar
	CInfoListBar	m_wndInfoBar;
	// The game chat bar
	CGameChatBar	m_wndGameChatBar;
	// The game player bar
	CGamePlayerBar	m_wndGamePlayerBar;
	// The game action bar
	CGameActionBar	m_wndGameActionBar;

//************
// The methods
//************
public:
	// The constructor
	CMainFrame();
	// The desctuctor
	virtual			~CMainFrame();
	// When the window is destroy then save all the windows position
	virtual BOOL	DestroyWindow();
	// Set the text in the status bar
	void			SetCurrentTile( CString Str );
	// Display or hide the 2D bar
	afx_msg void OnAffichageBarre2d();
	// Check or uncheck the item about show/hide 2D bar
	afx_msg void OnUpdateAffichageBarre2d(CCmdUI *pCmdUI);
	// Display or hide the object bar
	afx_msg void OnAffichageBarreobjet();
	// Check or uncheck the item about show/hide object bar
	afx_msg void OnUpdateAffichageBarreobjet(CCmdUI *pCmdUI);
	// Display or hide the object docking window
	afx_msg void OnAffichageFenetreObjet();
	// Check or uncheck the item about show/hide object docking window
	afx_msg void OnUpdateAffichageFenetreObjet(CCmdUI *pCmdUI);
	// Display or hide the information docking window
	afx_msg void OnAffichageFenetreinformation();
	// Check or uncheck the item about show/hide information docking window
	afx_msg void OnUpdateAffichageFenetreinformation(CCmdUI *pCmdUI);
	// Display or hide the 3D bar
	afx_msg void OnAffichageBarred3d();
	// Check or uncheck the item about show/hide 3D bar
	afx_msg void OnUpdateAffichageBarred3d(CCmdUI *pCmdUI);
	// Enter in game mode
	void			EnterGameMode();
	// Exit the game mode
	void			ExitGameMode();

// Substitutions
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	// When the window is created
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// When the client area is created
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// Fonctions générées de la table des messages
protected:

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
public:
//	afx_msg void OnDestroy();
public:
	afx_msg void OnViewToolbar();
public:
	afx_msg void OnUpdateViewToolbar(CCmdUI *pCmdUI);
public:
	afx_msg void OnAffichageChat();
public:
	afx_msg void OnUpdateAffichageChat(CCmdUI *pCmdUI);
public:
	afx_msg void OnAffichageWindowplayer();
public:
	afx_msg void OnUpdateAffichageWindowplayer(CCmdUI *pCmdUI);
public:
	afx_msg void OnAffichageWindowAction();
public:
	afx_msg void OnUpdateAffichageWindowAction(CCmdUI *pCmdUI);
};


