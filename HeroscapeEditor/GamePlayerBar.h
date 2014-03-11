#ifndef _GAMEPLAYERBAR_H_
#define _GAMEPLAYERBAR_H_

#include "ListCtrlPlayer.h"
#include "SizeCBar.h"

class CGamePlayerBar : public CSizingControlBar
{
//************
// The members
//************

protected:
	// The icon
	CStatic				m_wndIcon;
	// The text
	CStatic				m_wndText;
	// The font for the m_wndText
    CFont				m_font;
	// The bitmap for the window symbol
	CBitmap				m_bmp;

public:
	// The display ctrl of players
	CListCtrlPlayer*	m_pListCtrlPlayer;

public:

//************
// The methods
//************
public:
	// The constructor
	CGamePlayerBar();
	// The destructor
    virtual ~CGamePlayerBar();
	// Redraw the control
	void			RedrawCtrl();
	// When the bar is moved
	afx_msg void	OnMove(int x, int y);
	// When the bar is resize
    afx_msg void	OnSize(UINT nType, int cx, int cy);

// Attributes
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGamePlayerBar)
	//}}AFX_VIRTUAL

// Implementation
public:

    // Generated message map functions
protected:
    //{{AFX_MSG(CGamePlayerBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:
};

#endif // #ifndef _GAMEPLAYERBAR_H_
